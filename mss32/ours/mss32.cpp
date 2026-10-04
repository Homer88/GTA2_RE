/*
 * mss32.cpp - clean-room реализация Miles Sound System 5.0r для GTA2.
 *
 * Собственного микшера в gta2.exe нет (все 52 импорта вызываются только из
 * SoundCard, ни timeSetEvent, ни CreateThread, ни raw waveOut* в EXE нет),
 * поэтому смешивание, ресемплинг и 3D выполняются здесь.
 *
 * Формат вывода: 22050 Hz, стерео, 16-bit знаковый (blockAlign 4).
 * Источники:
 *   - 2D/3D семплы: 8-битный unsigned PCM, mono, произвольная rate (4500..22050)
 *   - потоки (музыка/вокалы): WAV WAVE_FORMAT_IMA_ADPCM -> декодируются в 16-bit
 *
 * Частота вывода берётся как nAvgBytesPerSec / nBlockAlign: GTA2 передаёт
 * WAVEFORMATEX с НЕинициализированным nSamplesPerSec (gta2.exe.c:150865-150886),
 * заполняя только nAvgBytesPerSec, nBlockAlign и wBitsPerSample.
 */
#include "mss32_abi.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>

#define MIX_FRAMES     1024        /* кадров на один буфер waveOut */
#define MIX_BUFFERS    4
#define MAX_2D         32          /* игра берёт 1 (свой) + 16 (SFX) = 17 */
#define MAX_3D         16          /* пул 3D (игра клампит 8..16) */
#define MAX_STREAMS    32         /* ВАЖНО: игра держит ~8 хендлов одновременно
                                       (радио-треки + вокал). При лимите 2
                                       лишние open возвращали 0 -> start(0) и
                                       status(0) -> music manager думал что
                                       трек не играет и переоткрывал его
                                       каждый кадр (заикание). */
#define OBJ_MAGIC      0x4D533231  /* 'MS21' */

static CRITICAL_SECTION g_lock;
static int              g_init = 0;

/* ---------------- источник звука ---------------- */
/* 8-битный unsigned mono ИЛИ 16-bit знаковый (1/2 канала), ADPCM уже декодирован */
struct Src {
    const BYTE *raw8;      /* 8-bit unsigned mono */
    const short*raw16;     /* 16-bit signed, channels = chans */
    int         chans;
    int         is16;      /* 1 = данные 16-bit, 0 = 8-bit (AIL_set_sample_type) */
    U32         len;       /* всего сэмплов (фреймов) в источнике */
    double      rate;      /* частота источника */
};

/* ---------------- голос ---------------- */
struct Voice {
    Src         src;
    double      pos;       /* позиция в исходных сэмплах (дробная) */
    double      step;      /* исходных сэмплов на один выходной */
    S32         volume;    /* 0..127 */
    S32         pan;       /* 0..127, 64 = центр */
    S32         loopCount; /* 0 = один раз, <0 = бесконечно, >0 = доп. повторов */
    S32         loopsDone;
    U32         len, loopStart, loopEnd;  /* в исходных сэмплах */
    U32         status;    /* SMP_* */
    int         is3D;
    /* 3D */
    F32         x, y, z;
    F32         dFrontMin, dFrontMax, dBackMin, dBackMax;
    F32         vol3D;     /* 0..1, вычисляется из позиции */
    /* поток */
    U32         totalMs;
    int         cacheIdx;   /* индекс в кэше декодированных WAV (-1 = свой) */
};

struct Obj {
    DWORD magic;
    Voice v;
    short* owned;   /* буфер в собственности потока (режим -2, не кэшированный) */
};

/* ---------------- драйвер ---------------- */
struct Driver {
    DWORD       magic;
    HWAVEOUT    wo;
    WAVEFORMATEX fmt;
    S32         masterVol;   /* 0..127 */
    S32         pref[64];
    int         suspended;
};

/* ---------------- состояние ---------------- */
static Driver      g_drv;
static Obj         g_s2d[MAX_2D];
static Obj         g_s3d[MAX_3D];
/* Живые потоки (объекты в куче, хендлы уникальны - как в retail Miles) */
static Obj*        g_strLive[MAX_STREAMS];
static int         g_strCount = 0;

/* счётчики диагностики WAV-кэша (объявлены здесь, т.к. используются в MixerThread) */
static DWORD       g_wcClock = 0;
static DWORD       g_wcHits = 0, g_wcMiss = 0, g_wcOpenCalls = 0;
static DWORD       g_wcStartCalls = 0;
static DWORD       g_wcCloseCalls = 0;
static DWORD       g_wcStatCalls = 0;
static HPROVIDER   g_3dProvider = 0;
static int         g_3dOpen = 0;
static int         g_3dHandles = 0;

static HANDLE      g_thread = 0;
static HANDLE      g_stopEv = 0;
static HANDLE      g_wakeEv = 0;
static HANDLE      g_memBlock = 0;
static void       *g_memPtr = 0;
static HANDLE      g_startup = 0;
static volatile LONG g_running = 0;

/* ---------------- лог ---------------- */
static CRITICAL_SECTION g_logLock;
static LONG             g_logReady = 0;

static void L(const char* fmt, ...)
{
    char buf[512], t[32];
    va_list ap;
    SYSTEMTIME st;
    FILE* f;

    if (!InterlockedCompareExchange(&g_logReady, 1, 0)) {
        InitializeCriticalSection(&g_logLock);
    }
    GetLocalTime(&st);
    _snprintf(t, sizeof(t), "%02d:%02d:%02d.%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    va_start(ap, fmt);
    _vsnprintf(buf, sizeof(buf) - 40, fmt, ap);
    va_end(ap);

    EnterCriticalSection(&g_logLock);
    f = fopen("mss32_ours.log", "a");
    if (f) { fprintf(f, "[%s] %s\n", t, buf); fclose(f); }
    LeaveCriticalSection(&g_logLock);
}

/* ================= IMA ADPCM ================= */
static const int s_idxTab[16] = { -1,-1,-1,-1,2,4,6,8,-1,-1,-1,-1,2,4,6,8 };
static const int s_stepTab[89] = {
    7,8,9,10,11,12,13,14,16,17,19,21,23,25,28,31,34,37,41,45,50,55,60,66,73,
    80,88,97,107,118,130,143,157,173,190,209,230,253,279,307,337,371,408,449,
    494,544,598,658,724,796,876,963,1060,1166,1282,1411,1552,1707,1878,2066,
    2272,2499,2749,3024,3327,3660,4026,4428,4871,5358,5894,6484,7132,7845,
    8630,9493,10442,11487,12635,13899,15289,16818,18500,20350,22385,24623,
    27086,29794,32767
};

/* Декодирует ОДИН канал блока Microsoft IMA ADPCM.
   hdr - 4-байтовый заголовок канала, data - начало данных канала,
   dataBytes - число байт данных канала в блоке, byteStep - шаг между
   байтами канала (для стерео 2: байты каналов чередуются).
   MS-IMA блок: [заголовки каналов по 4 байта][данные, байт на канал в цикл].
   Раскладывает сэмплы канала ch с шагом stride в out. */
static void ImaDecodeChannel(const BYTE* hdr, const BYTE* data, int dataBytes,
                             int byteStep, short* out, int nOut,
                             int stride, int ch, int* pred, int* index)
{
    int i, n;
    *pred  = (short)(hdr[0] | (hdr[1] << 8));
    *index = hdr[2];
    if (*index > 88) *index = 88;

    if (nOut <= 0 || !out) return;
    out[ch] = (short)*pred;
    n = 1;

    for (i = 0; i < dataBytes && n < nOut; ++i) {
        int g;
        BYTE b = data[i * byteStep];
        for (g = 0; g < 2 && n < nOut; ++g) {
            int nib = g ? ((b >> 4) & 0x0F) : (b & 0x0F);
            int step = s_stepTab[*index];
            int diff = step >> 3;
            if (nib & 1) diff += step >> 2;
            if (nib & 2) diff += step >> 1;
            if (nib & 4) diff += step;
            if (nib & 8) diff = -diff;
            *pred += diff;
            if (*pred >  32767) *pred =  32767;
            if (*pred < -32768) *pred = -32768;
            *index += s_idxTab[nib];
            if (*index < 0)  *index = 0;
            if (*index > 88) *index = 88;
            out[n * stride + ch] = (short)*pred;
            ++n;
        }
    }
}

/* читает WAV и декодирует IMA ADPCM в 16-bit; PCM тоже поддерживается */
static int LoadWav(const char* fn, short** outSamples, int* outChans, U32* outLen, U32* outRate)
{
    FILE* f = fopen(fn, "rb");
    BYTE  hdr[12];
    WORD  tag = 0, chans = 0, bits = 0, blockAlign = 0;
    DWORD rate = 0, dataOff = 0, dataLen = 0;
    short* out = 0;
    int   cap = 0, n = 0;

    if (!f) { L("LoadWav: cannot open %s", fn); return -1; }
    if (fread(hdr, 1, 12, f) != 12) { fclose(f); return -1; }
    if (memcmp(hdr, "RIFF", 4) || memcmp(hdr + 8, "WAVE", 4)) { fclose(f); L("LoadWav: %s not RIFF/WAVE", fn); return -1; }

    for (;;) {
        BYTE ch[8];
        DWORD sz;
        if (fread(ch, 1, 8, f) != 8) break;
        sz = ch[4] | (ch[5] << 8) | (ch[6] << 16) | ((DWORD)ch[7] << 24);
        if (!memcmp(ch, "fmt ", 4)) {
            BYTE fmt[40];
            DWORD rd = sz < sizeof(fmt) ? sz : sizeof(fmt);
            if (fread(fmt, 1, rd, f) != rd) break;
            tag        = fmt[0] | (fmt[1] << 8);
            chans      = fmt[2] | (fmt[3] << 8);
            rate       = fmt[4] | (fmt[5] << 8) | (fmt[6] << 16) | ((DWORD)fmt[7] << 24);
            blockAlign = fmt[12] | (fmt[13] << 8);
            bits       = fmt[14] | (fmt[15] << 8);
            if (sz > rd) fseek(f, (long)(sz - rd), SEEK_CUR);
        } else if (!memcmp(ch, "data", 4)) {
            dataOff = (DWORD)ftell(f);
            dataLen = sz;
            break;
        } else {
            fseek(f, (long)sz + (sz & 1), SEEK_CUR);
        }
    }
    L("LoadWav %s tag=%u ch=%u rate=%u bits=%u blockAlign=%u dataLen=%u",
      fn, tag, chans, rate, bits, blockAlign, dataLen);
    if (!dataLen || !chans || !rate) { fclose(f); return -1; }

    /* Читаем весь data-чанк ОДНИМ fread. Раньше читалось по байту через fgetc,
       из-за чего d.wav (6.5 МБ) декодировался 51 секунду и игра висла. */
    {
        BYTE* raw = (BYTE*)malloc(dataLen);
        if (!raw) { fclose(f); return -1; }
        fseek(f, (long)dataOff, SEEK_SET);
        if (fread(raw, 1, dataLen, f) != dataLen) { free(raw); fclose(f); return -1; }
        fclose(f);

        if (tag == PCM_FMT_PCM) {
            int bytes = bits / 8;
            DWORD i;
            if (bytes < 1) { free(raw); return -1; }
            if (bytes == 1) {
                n = (int)(dataLen / chans);
                out = (short*)malloc((size_t)n * chans * sizeof(short));
                if (!out) { free(raw); return -1; }
                __try {
                    for (i = 0; i < (DWORD)n * chans; ++i)
                        out[i] = (short)(((int)raw[i] - 128) << 8);
                } __except (EXCEPTION_EXECUTE_HANDLER) {
                    L("LoadWav %s: AV in PCM8 decode out=%p n=%d", fn, (void*)out, n);
                    free(out); out = 0; free(raw); return -1;
                }
            } else {
                n = (int)(dataLen / (bytes * chans));
                out = (short*)malloc((size_t)n * chans * sizeof(short));
                if (!out) { free(raw); return -1; }
                __try {
                    for (i = 0; i < (DWORD)n * chans; ++i)
                        out[i] = (short)(raw[i * 2] | (raw[i * 2 + 1] << 8));
                } __except (EXCEPTION_EXECUTE_HANDLER) {
                    L("LoadWav %s: AV in PCM16 decode out=%p n=%d", fn, (void*)out, n);
                    free(out); out = 0; free(raw); return -1;
                }
            }
        } else if (tag == PCM_FMT_ADPCM) {
            int perChanBytes, perBlock, nBlocks, b, c;
            int pred2[2] = {0, 0}, index2[2] = {0, 0};
            /* MS-IMA: blockAlign = размер блока на ВСЕ каналы (respectis.wav:
               ch=2, blockAlign=1024 -> по 1024 байта на блок, заголовки 2*4 байта,
               далее байты каналов чередуются). */
            if (blockAlign < 4 * chans + 2 || chans < 1 || chans > 2) { free(raw); L("LoadWav %s: bad ima geometry", fn); return -1; }
            perChanBytes = (blockAlign - 4 * chans) / chans; /* байт данных на канал в блоке */
            perBlock     = perChanBytes * 2;                  /* сэмплов на канал в блоке */
            nBlocks      = (int)(dataLen / blockAlign);
            if (nBlocks <= 0) { free(raw); return -1; }
            cap = nBlocks * perBlock;
            out = (short*)malloc((size_t)cap * chans * sizeof(short));
            if (!out) { free(raw); return -1; }
            {
                MEMORY_BASIC_INFORMATION mbi;
                if (VirtualQuery(out, &mbi, sizeof(mbi)))
                    L("LoadWav %s: VQ out=%p base=%p base2=%p state=%lx prot=%lx apr=%lx type=%lx",
                      fn, (void*)out, mbi.BaseAddress, mbi.AllocationBase,
                      (unsigned long)mbi.State, (unsigned long)mbi.Protect,
                      (unsigned long)mbi.AllocationProtect, (unsigned long)mbi.Type);
                L("LoadWav %s: heap=%d out=%p cap=%d bytes=%u", fn,
                  (int)HeapValidate(GetProcessHeap(), 0, NULL), (void*)out, cap,
                  (unsigned)((size_t)cap * chans * sizeof(short)));
                __try {
                    short* p = out;
                    p[0] = 0;
                    p[(size_t)cap * chans - 1] = 0;
                } __except (EXCEPTION_EXECUTE_HANDLER) {
                    L("LoadWav %s: PROBE AV out=%p cap=%d -> fail", fn, (void*)out, cap);
                    free(out); out = 0; free(raw);
                    return -1;
                }
            }
            /* Оберегаем игру: если куча уже повреждена (чужой OOB-write до нас),
               магазин в out может упасть. Ловим, логируем факт и возвращаем
               ошибку вместо краха всей игры. */
            __try {
                for (b = 0, n = 0; b < nBlocks; ++b) {
                    const BYTE* blk = raw + (size_t)b * blockAlign;
                    for (c = 0; c < chans; ++c) {
                        ImaDecodeChannel(blk + 4 * c, blk + 4 * chans + c,
                                        perChanBytes, chans,
                                        out + (size_t)n * perBlock * chans, perBlock,
                                        chans, c, &pred2[c], &index2[c]);
                    }
                    n += perBlock;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                L("LoadWav %s: AV in IMA decode (heap corruption?) out=%p cap=%d "
                  "perChanBytes=%d perBlock=%d nBlocks=%d chans=%d dataLen=%u",
                  fn, (void*)out, cap, perChanBytes, perBlock, nBlocks, chans, dataLen);
                free(out);
                out = 0;
                free(raw);
                return -1;
            }
            n = cap;
        } else {
            free(raw);
            L("LoadWav %s: unsupported tag %u", fn, tag);
            return -1;
        }
        free(raw);
    }

    *outSamples = out;
    *outChans   = chans;
    *outLen     = (U32)n;
    *outRate    = rate;
    L("LoadWav %s decoded: %u frames ch=%d rate=%u", fn, (unsigned)n, chans, rate);
    return 0;
}

/* ================= выборка с ресемплингом ================= */
static inline int SrcRead(const Src* s, double pos, int ch, int* ok)
{
    long i0 = (long)pos;
    double fr = pos - (double)i0;
    int s0, s1 = 0;
    if (i0 < 0) { *ok = 0; return 0; }
    if (i0 >= (long)s->len) { *ok = 0; return 0; }
    if (s->is16 && s->raw16) {
        s0 = s->raw16[(size_t)i0 * s->chans + (ch < s->chans ? ch : 0)];
        if (i0 + 1 < (long)s->len)
            s1 = s->raw16[(size_t)(i0 + 1) * s->chans + (ch < s->chans ? ch : 0)];
    } else if (s->raw8) {
        s0 = ((int)s->raw8[i0] - 128) << 8;
        if (i0 + 1 < (long)s->len) s1 = ((int)s->raw8[i0 + 1] - 128) << 8;
    } else if (s->raw16) {
        s0 = s->raw16[(size_t)i0 * s->chans + (ch < s->chans ? ch : 0)];
        if (i0 + 1 < (long)s->len)
            s1 = s->raw16[(size_t)(i0 + 1) * s->chans + (ch < s->chans ? ch : 0)];
    } else { *ok = 0; return 0; }
    *ok = 1;
    return s0 + (int)((s1 - s0) * fr);
}

/* ================= 3D ================= */
static void Update3D(Voice* v)
{
    F32 dist = (F32)sqrt((double)(v->x * v->x + v->y * v->y + v->z * v->z));
    F32 fmin = v->dFrontMin, fmax = v->dFrontMax;
    F32 bmin = v->dBackMin,  bmax = v->dBackMax;
    F32 att;

    if (v->z < 0) { fmin = bmin; fmax = bmax; }
    if (fmax <= fmin) { fmin = 1.0f; fmax = 1000.0f; }   /* GTA2 передаёт (0,-1) */

    att = (fmax - dist) / (fmax - fmin);
    if (att < 0.0f) att = 0.0f;
    if (att > 1.0f) att = 1.0f;
    v->vol3D = att;
}

/* ================= микшер ================= */
static void MixOne(short* buf, int frames, Voice* vo, F32 outRate)
{
    F32 gain;
    int vol, panL, panR, f;

    if (vo->status != SMP_PLAYING || !vo->src.len) return;
    if (vo->src.rate <= 0) return;
    vo->step = vo->src.rate / (double)outRate;
    if (vo->step <= 0) return;

    if (vo->is3D) {
        Update3D(vo);
        gain = (F32)vo->volume * vo->vol3D;
        panL = panR = 64 + (int)(vo->x * 32.0f);
        if (panL < 0) panL = 0; if (panL > 127) panL = 127;
        if (panR < 0) panR = 0; if (panR > 127) panR = 127;
    } else {
        gain = (F32)vo->volume;
        panL = 127 - vo->pan;
        panR = vo->pan;
    }
    if (gain < 0) gain = 0;
    if (gain > 127) gain = 127;
    vol = (int)gain;
    if (vol <= 0) { vo->pos += vo->step; return; }

    for (f = 0; f < frames; ++f) {
        int ok, l, r;
        if (vo->pos >= (double)vo->len) {
            if (vo->loopCount == 0) {
                vo->status = SMP_DONE; break;
            } else if (vo->loopCount < 0) {
                vo->pos = (double)vo->loopStart;
            } else if (vo->loopsDone < vo->loopCount) {
                ++vo->loopsDone;
                vo->pos = (double)vo->loopStart;
            } else {
                vo->status = SMP_DONE; break;
            }
        }
        l = SrcRead(&vo->src, vo->pos, 0, &ok);
        if (!ok) { vo->status = SMP_DONE; break; }
        if (vo->src.chans > 1) {
            r = SrcRead(&vo->src, vo->pos, 1, &ok);
            if (!ok) r = l;
        } else {
            r = l;
        }
        buf[f * 2]     += (short)((l * vol * panL) / (127 * 127));
        buf[f * 2 + 1] += (short)((r * vol * panR) / (127 * 127));
        vo->pos += vo->step;
    }
}

/* ---------------- кэш декодированных WAV ----------------
   Игра открывает/закрывает потоки многократно (в т.ч. один и тот же d.wav),
   а декодирование 6.5 МБ даже после оптимизации нежелательно делать повторно.
   Объявлено здесь, т.к. используется в MixInto (общий транспорт). */
#define WAVCACHE_N 6
struct WavCache {
    char   name[80];
    short* data;
    int    chans;
    U32    len, rate;
    int    refs;
    DWORD  used;
    /* Общий транспорт файла. Игра делает open->start->close ~30 раз в секунду
       на ОДНОМ и том же d.wav, из-за чего поток успевает проиграть только
       первый буфер (1024 кадра = 46 мс) и музыка зацикливается щелчком.
       Позиция и состояние живут здесь, а не в хендле: close
       хендла больше не обрывает звук. */
    Voice  tv;
    int    transport;      /* 1 = транспорт играет */
    S32    vol, pan;
};
static WavCache g_wc[WAVCACHE_N];

static void MixInto(short* buf, int frames, int outRate)
{
    int f, i, masterL, masterR;

    masterL = masterR = g_drv.masterVol;
    memset(buf, 0, (size_t)frames * 2 * sizeof(short));

    for (i = 0; i < MAX_2D; ++i)
        if (g_s2d[i].magic == OBJ_MAGIC) MixOne(buf, frames, &g_s2d[i].v, (F32)outRate);
    for (i = 0; i < MAX_3D; ++i)
        if (g_s3d[i].magic == OBJ_MAGIC) MixOne(buf, frames, &g_s3d[i].v, (F32)outRate);
    /* потоки живут в куче: обходим только актуальный список.
       Потоки с cacheIdx >= 0 играют через общий транспорт в кэше
       (см. AIL_start_stream), их собственный голос не смешиваем. */
    for (i = 0; i < g_strCount; ++i)
        if (g_strLive[i] && g_strLive[i]->v.cacheIdx < 0)
            MixOne(buf, frames, &g_strLive[i]->v, (F32)outRate);
    for (i = 0; i < WAVCACHE_N; ++i)
        if (g_wc[i].transport && g_wc[i].data) {
            g_wc[i].tv.volume = g_wc[i].vol;
            g_wc[i].tv.pan    = g_wc[i].pan;
            MixOne(buf, frames, &g_wc[i].tv, (F32)outRate);
        }

    for (f = 0; f < frames; ++f) {
        int l = buf[f * 2], r = buf[f * 2 + 1];
        l = l * masterL / 127;
        r = r * masterR / 127;
        if (l >  32767) l =  32767;
        if (l < -32768) l = -32768;
        if (r >  32767) r =  32767;
        if (r < -32768) r = -32768;
        buf[f * 2] = (short)l;
        buf[f * 2 + 1] = (short)r;
    }
}

static unsigned __stdcall MixerThread(LPVOID p)
{
    WAVEHDR hdr[MIX_BUFFERS];
    BYTE*   data[MIX_BUFFERS];
    int     i, outRate;

    outRate = (int)g_drv.fmt.nSamplesPerSec;
    if (outRate < 4000) outRate = 22050;
    L("mixer thread start rate=%d fmt tag=%u ch=%u bits=%u blockAlign=%u",
      outRate, g_drv.fmt.wFormatTag, g_drv.fmt.nChannels,
      g_drv.fmt.wBitsPerSample, g_drv.fmt.nBlockAlign);

    for (i = 0; i < MIX_BUFFERS; ++i) {
        memset(&hdr[i], 0, sizeof(WAVEHDR));
        /* ВАЖНО: без этого флага поток зависнет в ожидании свободного буфера,
           т.к. изначально dwFlags == 0. */
        hdr[i].dwFlags = WHDR_DONE;
        data[i] = (BYTE*)malloc(MIX_FRAMES * 2 * sizeof(short));
        if (!data[i]) { L("mixer: out of memory"); return 1; }
    }

    while (g_running) {
        int idx = -1;
        for (;;) {
            if (!g_running) break;
            idx = -1;
            EnterCriticalSection(&g_lock);
            for (i = 0; i < MIX_BUFFERS; ++i) {
                if (hdr[i].dwFlags & WHDR_DONE) { idx = i; break; }
            }
            LeaveCriticalSection(&g_lock);
            if (idx >= 0) break;
            WaitForSingleObject(g_wakeEv, 5);
        }
        if (!g_running || idx < 0) break;

        EnterCriticalSection(&g_lock);
        MixInto((short*)data[idx], MIX_FRAMES, outRate);
        LeaveCriticalSection(&g_lock);

        /* Диагностический пульс: раз в ~2 секунды сообщаем, играют ли голоса
           и есть ли ненулевая амплитуда. Подтверждает, что звук реально
           генерируется, даже если у пользователя нет наушников. */
        {
            static DWORD lastBeat = 0;
            DWORD now = GetTickCount();
            if (now - lastBeat >= 2000) {
                int n2 = 0, n3 = 0, ns = 0, pk = 0, i2;
                const short* b = (const short*)data[idx];
                for (i2 = 0; i2 < MIX_FRAMES * 2; ++i2) {
                    int a = b[i2] < 0 ? -b[i2] : b[i2];
                    if (a > pk) pk = a;
                }
                for (i2 = 0; i2 < MAX_2D; ++i2) if (g_s2d[i2].magic == OBJ_MAGIC && g_s2d[i2].v.status == SMP_PLAYING) ++n2;
                for (i2 = 0; i2 < MAX_3D; ++i2) if (g_s3d[i2].magic == OBJ_MAGIC && g_s3d[i2].v.status == SMP_PLAYING) ++n3;
                for (i2 = 0; i2 < g_strCount; ++i2) if (g_strLive[i2] && g_strLive[i2]->v.status == SMP_PLAYING) ++ns;
                {
                    double fpos = -1; U32 tlen = 0; int fvol = -1, fin = -1, fsrc = -1, fra = -1, fpk = -1;
                    for (i2 = 0; i2 < WAVCACHE_N; ++i2) {
                        if (g_wc[i2].transport) {
                            fpos = g_wc[i2].tv.pos; tlen = g_wc[i2].len;
                            fvol = g_wc[i2].tv.volume; fin = g_wc[i2].tv.src.chans;
                            fra = (int)g_wc[i2].tv.src.rate;
                            {
                                int pm = 0, ok = 0;
                                for (int k = 0; k < 96; ++k) {
                                    int s = SrcRead(&g_wc[i2].tv.src, g_wc[i2].tv.pos + k, 0, &ok);
                                    if (!ok) break;
                                    if (s < 0) s = -s;
                                    if (s > pm) pm = s;
                                }
                                fpk = pm;
                            }
                            break;
                        }
                    }
                    if (n2 || n3 || ns || pk > 8) {
                        L("pulse: 2d=%d 3d=%d stream=%d peak=%d master=%d | s2d[0] vol=%d rate=%d len=%u pk=%d | trans vol=%d ch=%d rate=%d srcpk=%d | opens=%lu closes=%lu | wcHits=%lu wcMiss=%lu | begins=%lu pos=%.0f/%.0f",
                          n2, n3, ns, pk, g_drv.masterVol,
                          (g_s2d[0].magic == OBJ_MAGIC) ? (int)g_s2d[0].v.volume : -1,
                          (g_s2d[0].magic == OBJ_MAGIC) ? (int)g_s2d[0].v.src.rate : -1,
                          (g_s2d[0].magic == OBJ_MAGIC) ? (unsigned)g_s2d[0].v.len : 0u,
                          (g_s2d[0].magic == OBJ_MAGIC) ? (int)g_s2d[0].v.volume : -1,
                          fvol, fin, fra, fpk,
                          g_wcOpenCalls, g_wcCloseCalls,
                          g_wcHits, g_wcMiss,
                          g_wcStartCalls, fpos, (double)tlen);
                        lastBeat = now;
                    }
                }
            }
        }

        if (hdr[idx].dwFlags & WHDR_PREPARED) {
            waveOutUnprepareHeader(g_drv.wo, &hdr[idx], sizeof(WAVEHDR));
        }
        memset(&hdr[idx], 0, sizeof(WAVEHDR));
        hdr[idx].lpData        = (LPSTR)data[idx];
        hdr[idx].dwBufferLength = MIX_FRAMES * 2 * sizeof(short);
        if (waveOutPrepareHeader(g_drv.wo, &hdr[idx], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
            continue;
        if (waveOutWrite(g_drv.wo, &hdr[idx], hdr[idx].dwBufferLength) != MMSYSERR_NOERROR) {
            waveOutUnprepareHeader(g_drv.wo, &hdr[idx], sizeof(WAVEHDR));
            hdr[idx].dwFlags = WHDR_DONE;
        }
    }

    for (i = 0; i < MIX_BUFFERS; ++i) {
        if (hdr[i].dwFlags & WHDR_PREPARED)
            waveOutUnprepareHeader(g_drv.wo, &hdr[i], sizeof(WAVEHDR));
        free(data[i]);
    }
    L("mixer thread exit");
    return 0;
}

/* ================= startup ================= */
int AILCALL AIL_startup(void)
{
    DWORD  pid = GetCurrentProcessId();

    if (g_init) { L("AIL_startup: already up"); return 1; }
    InitializeCriticalSection(&g_lock);
    g_stopEv = CreateEventA(0, TRUE, FALSE, 0);
    g_wakeEv = CreateEventA(0, FALSE, FALSE, 0);
    memset(&g_s2d, 0, sizeof(g_s2d));
    memset(&g_s3d, 0, sizeof(g_s3d));
    g_strCount = 0;
    g_drv.masterVol = GTA2_MASTER_VOL;

    /* не даём переинициализировать, если уже в процессе */
    g_init = 1;
    L("AIL_startup pid=%lu", pid);
    return 1;
}

void AILCALL AIL_shutdown(void)
{
    if (!g_init) return;
    L("AIL_shutdown");
    g_running = 0;
    SetEvent(g_stopEv);
    SetEvent(g_wakeEv);
    if (g_thread) { WaitForSingleObject(g_thread, 2000); CloseHandle(g_thread); g_thread = 0; }
    /* устройство не закрываем - см. AIL_waveOutClose (краш wdmaud.drv на Win10) */
    if (g_memPtr)  { VirtualFree(g_memPtr, 0, MEM_RELEASE); g_memPtr = 0; g_memBlock = 0; }
    if (g_startup) { ReleaseMutex(g_startup); CloseHandle(g_startup); g_startup = 0; }
    if (g_wakeEv)  { CloseHandle(g_wakeEv);  g_wakeEv = 0; }
    if (g_stopEv)  { CloseHandle(g_stopEv);  g_stopEv = 0; }
    DeleteCriticalSection(&g_lock);
    g_init = 0;
}

int AILCALL AIL_set_preference(U32 number, S32 value)
{
    if (number < 64) g_drv.pref[number] = value;
    L("AIL_set_preference(%u, %d)", number, value);
    return 0;
}

void AILCALL AIL_delay(S32 intervals)
{
    if (intervals > 0) Sleep((DWORD)intervals);
}

void* AILCALL AIL_mem_alloc_lock(U32 size_or_addr)
{
    /* Miles v5: AIL_mem_alloc_lock(S32 *size) принимает УКАЗАТЕЛЬ на размер,
       выделяет *size байт и записывает обратно фактический размер.
       GTA2 передаёт &gBufferSize (gta2.exe.c:150890). */
    U32 size = 0, raw = 0;
    void* p = 0;
    __try { raw = *(U32*)size_or_addr; } __except (EXCEPTION_EXECUTE_HANDLER) { raw = 0; }
    size = raw;
    /* gBufferSize - это ЛИМИТ размера SFX-файла, который игра сама проверяет
       перед записью (gta2.exe.c:150788). Поэтому даже если значение
       нечитаемо/нулевое, меньше 8 МБ выделять нельзя - иначе игра запишет
       в буфер больше, чем мы дали. */
    if (size < 8u * 1024 * 1024) size = 8u * 1024 * 1024;
    if (size > 64u * 1024 * 1024) size = 64u * 1024 * 1024;
    if (g_memPtr) return g_memPtr;
    p = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (p) {
        g_memPtr = p;
        __try { *(U32*)size_or_addr = size; } __except (EXCEPTION_EXECUTE_HANDLER) {}
    }
    L("AIL_mem_alloc_lock(arg=%08lX) raw=%lu -> %p size=%lu", size_or_addr, raw, p, size);
    return p;
}

void AILCALL AIL_mem_free_lock(void* p)
{
    L("AIL_mem_free_lock(%p)", p);
    if (p && p == g_memPtr) { VirtualFree(g_memPtr, 0, MEM_RELEASE); g_memPtr = 0; }
}

int AILCALL AIL_waveOutOpen(HDIGDRIVER* drvr, LPHWAVEOUT* lphWaveOut,
                            S32 wDeviceID, LPWAVEFORMAT lpFormat)
{
    WAVEFORMATEX fmt;
    MMRESULT r;
    int rate;
    /* снимок входных полей для лога: GTA2 не инициализирует nSamplesPerSec */
    WORD  in_tag = 0, in_ch = 0, in_blk = 0, in_bits = 0;
    DWORD in_avg = 0, in_rate = 0;

    if (!drvr || !lpFormat) return 1;   /* 1 = ошибка: у GTA2 0 означает успех */
    in_tag  = lpFormat->wFormatTag;
    in_ch   = lpFormat->nChannels;
    in_rate = lpFormat->nSamplesPerSec;
    in_avg  = lpFormat->nAvgBytesPerSec;
    in_blk  = lpFormat->nBlockAlign;
    /* GTA2 заполняет 16 байт как PCMWAVEFORMAT: tag, ch, nSamplesPerSec(МУСОР),
       nAvgBytesPerSec, nBlockAlign, wBitsPerSample. В этом SDK wBitsPerSample
       лежит в PCMWAVEFORMAT, а не в WAVEFORMAT. */
    in_bits = ((PCMWAVEFORMAT*)lpFormat)->wBitsPerSample;
    memset(&fmt, 0, sizeof(fmt));
    memcpy(&fmt, lpFormat, 16);   /* GTA2 кладёт 16 байт */

    /* nSamplesPerSec у GTA2 не инициализирован -> берём из AvgBytes/BlockAlign */
    rate = (int)fmt.nSamplesPerSec;
    if (fmt.nBlockAlign > 0) {
        int derived = (int)(fmt.nAvgBytesPerSec / fmt.nBlockAlign);
        if (derived >= 4000 && derived <= 192000) rate = derived;
    }
    if (rate < 4000 || rate > 192000) rate = 22050;
    /* GTA2 всегда запрашивает стерео 16-bit (nBlockAlign=4), а MixInto пишет
       ровно 2 канала, поэтому выход всегда стерео. */
    fmt.nSamplesPerSec   = (DWORD)rate;
    fmt.wFormatTag       = WAVE_FORMAT_PCM;
    fmt.nChannels        = 2;
    fmt.wBitsPerSample   = 16;
    fmt.nBlockAlign      = 4;
    fmt.nAvgBytesPerSec  = (DWORD)rate * 4;

    g_drv.wo = 0;
    r = waveOutOpen(&g_drv.wo, WAVE_MAPPER, &fmt, 0, 0, CALLBACK_NULL);
    if (r != MMSYSERR_NOERROR || !g_drv.wo) {
        L("AIL_waveOutOpen: waveOutOpen failed %u (tag=%u ch=%u rate=%lu avg=%lu blk=%u bits=%u)",
          (unsigned)r, in_tag, in_ch, in_rate, in_avg, in_blk, in_bits);
        g_drv.wo = 0;
        return 1;                      /* ошибка: GTA2 делает if(ret) return 0 */
    }

    g_drv.fmt = fmt;
    g_drv.magic = OBJ_MAGIC;
    g_drv.masterVol = GTA2_MASTER_VOL;
    *drvr = (HDIGDRIVER)&g_drv;
    if (lphWaveOut) *lphWaveOut = (LPHWAVEOUT)g_drv.wo;

    g_running = 1;
    g_thread = (HANDLE)_beginthreadex(0, 0, MixerThread, 0, 0, 0);
    L("AIL_waveOutOpen ok rate=%d wo=%p thread=%p", rate, g_drv.wo, g_thread);
    return 0;                          /* 0 = успех (Inverse logic GTA2) */
}

void AILCALL AIL_waveOutClose(HDIGDRIVER drvr)
{
    L("AIL_waveOutClose(%p)", drvr);
    g_running = 0;
    SetEvent(g_wakeEv);
    if (g_thread) { WaitForSingleObject(g_thread, 2000); CloseHandle(g_thread); g_thread = 0; }
    /* НЕ закрываем waveOut-устройство: на Win10 waveOutReset/Close дёргает
       helper-поток winmm, который валится внутри wdmaud.drv (AV 0x8A8C при
       выходе из игры). Устройство освободится вместе с процессом. */
    g_3dOpen = 0;
}

int AILCALL AIL_digital_handle_release(HDIGDRIVER drvr)
{
    L("AIL_digital_handle_release(%p)", drvr);
    return 1;
}

int AILCALL AIL_digital_handle_reacquire(HDIGDRIVER drvr)
{
    L("AIL_digital_handle_reacquire(%p)", drvr);
    return 1;
}

void AILCALL AIL_set_digital_master_volume(HDIGDRIVER dig, S32 volume)
{
    L("AIL_set_digital_master_volume(%p, %d)", dig, volume);
    if (volume < 0) volume = 0;
    if (volume > 127) volume = 127;
    g_drv.masterVol = volume;
}

/* ================= 2D семплы ================= */
HSAMPLE AILCALL AIL_allocate_sample_handle(HDIGDRIVER dig)
{
    int i;
    for (i = 0; i < MAX_2D; ++i) {
        if (g_s2d[i].magic != OBJ_MAGIC) {
            memset(&g_s2d[i], 0, sizeof(Obj));
            g_s2d[i].magic = OBJ_MAGIC;
            g_s2d[i].v.status = SMP_FREE;
            g_s2d[i].v.volume = GTA2_MASTER_VOL;
            g_s2d[i].v.pan    = GTA2_PAN_CENTER;
            g_s2d[i].v.loopCount = 0;
            L("AIL_allocate_sample_handle -> slot %d (%p)", i, (void*)&g_s2d[i]);
            return (HSAMPLE)&g_s2d[i];
        }
    }
    L("AIL_allocate_sample_handle: pool full");
    return 0;
}

void AILCALL AIL_release_sample_handle(HSAMPLE S)
{
    if (!S) return;
    ((Obj*)S)->magic = 0;
    ((Obj*)S)->v.status = SMP_FREE;
}

void AILCALL AIL_init_sample(HSAMPLE S)
{
    if (!S) return;
    L("AIL_init_sample(%p)", S);
    ((Obj*)S)->v.status = SMP_STOPPED;
}

void AILCALL AIL_set_sample_address(HSAMPLE S, void const* start, U32 len)
{
    if (!S) return;
    EnterCriticalSection(&g_lock);
    {
        /* Тип (is16/chans) уже задан через AIL_set_sample_type: только обновляем
           указатель и длину. По умолчанию (0) = mono 8-bit. */
        Obj* o = (Obj*)S;
        const void* base = start;
        if (o->v.src.is16) {
            o->v.src.raw8 = 0;
            o->v.src.raw16 = (const short*)base;
        } else {
            o->v.src.raw8 = (const BYTE*)base;
            o->v.src.raw16 = 0;
        }
        if (o->v.src.chans < 1) o->v.src.chans = 1;
        o->v.len       = len;
        o->v.loopStart = 0;
        o->v.loopEnd   = len;
    }
    LeaveCriticalSection(&g_lock);
    L("AIL_set_sample_address(%p, %p, %lu)", S, start, len);
    {
        static int s_nAddrDbg = 0;
        if (s_nAddrDbg < 30 && len >= 8) {
            ++s_nAddrDbg;
            const BYTE* p = (const BYTE*)start;
            L("  addr data[0..7]=%02X %02X %02X %02X %02X %02X %02X %02X",
              p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        }
    }
}

void AILCALL AIL_set_sample_type(HSAMPLE S, S32 format, U32 flags)
{
    if (!S) return;
    EnterCriticalSection(&g_lock);
    {
        Obj* o = (Obj*)S;
        const void* base = o->v.src.raw8 ? (const void*)o->v.src.raw8
                                         : (const void*)o->v.src.raw16;
        /* Раскладка DIG_F_*: бит0 = 16-bit, бит1 = стерео. GTA2 передаёт 0 и 1. */
        o->v.src.is16  = (format & 1) ? 1 : 0;
        o->v.src.chans = (format & 2) ? 2 : 1;
        if (o->v.src.is16) {
            o->v.src.raw8  = 0;
            o->v.src.raw16 = (const short*)base;
        } else {
            o->v.src.raw16 = 0;
            o->v.src.raw8  = (const BYTE*)base;
        }
        L("AIL_set_sample_type(%p, %d, %08lX) -> is16=%d ch=%d base=%p", S, format,
          (unsigned long)flags, o->v.src.is16, o->v.src.chans, base);
    }
    LeaveCriticalSection(&g_lock);
}

void AILCALL AIL_start_sample(HSAMPLE S)
{
    if (!S) return;
    EnterCriticalSection(&g_lock);
    ((Obj*)S)->v.pos = 0;
    ((Obj*)S)->v.loopsDone = 0;
    ((Obj*)S)->v.status = SMP_PLAYING;
    LeaveCriticalSection(&g_lock);
    SetEvent(g_wakeEv);
    L("AIL_start_sample(%p) len=%lu rate=%.0f", S,
      ((Obj*)S)->v.len, ((Obj*)S)->v.src.rate);
}

void AILCALL AIL_end_sample(HSAMPLE S)
{
    if (!S) return;
    ((Obj*)S)->v.status = SMP_STOPPED;
}

U32 AILCALL AIL_sample_status(HSAMPLE S)
{
    if (!S) return SMP_FREE;
    return ((Obj*)S)->v.status;
}

void AILCALL AIL_set_sample_playback_rate(HSAMPLE S, S32 rate)
{
    if (!S) return;
    if (rate > 0) ((Obj*)S)->v.src.rate = (double)rate;
    L("AIL_set_sample_playback_rate(%p, %d)", S, rate);
}

void AILCALL AIL_set_sample_loop_count(HSAMPLE S, S32 loop_count)
{
    if (!S) return;
    ((Obj*)S)->v.loopCount = loop_count;
    ((Obj*)S)->v.loopsDone = 0;
    L("AIL_set_sample_loop_count(%p, %d)", S, loop_count);
}

void AILCALL AIL_set_sample_loop_block(HSAMPLE S, S32 start_offset, S32 end_offset)
{
    if (!S) return;
    ((Obj*)S)->v.loopStart = (U32)(start_offset < 0 ? 0 : start_offset);
    ((Obj*)S)->v.loopEnd   = (U32)(end_offset   < 0 ? (S32)((Obj*)S)->v.len : end_offset);
    L("AIL_set_sample_loop_block(%p, %d, %d)", S, start_offset, end_offset);
}

void AILCALL AIL_set_sample_volume(HSAMPLE S, S32 volume)
{
    if (!S) return;
    if (volume < 0) volume = 0;
    if (volume > 127) volume = 127;
    if (((Obj*)S)->v.volume != volume) {
        L("AIL_set_sample_volume(%p, %d %d)", S, volume, ((Obj*)S)->v.volume);
        ((Obj*)S)->v.volume = volume;
    }
}

void AILCALL AIL_set_sample_pan(HSAMPLE S, S32 pan)
{
    if (!S) return;
    if (pan < 0) pan = 0;
    if (pan > 127) pan = 127;
    ((Obj*)S)->v.pan = pan;
}

/* ================= потоки ================= */
/* Возврат: [0..WAVCACHE_N) - кэшировано (refs++); -1 - ошибка;
   -2 - не кэшировано, вызывающий ВЛАДЕЕТ *data и должен его освободить. */
static int WavCacheGet(const char* fn, short** data, int* chans, U32* len, U32* rate)
{
    int i, victim = -1;
    DWORD oldest = 0xFFFFFFFFu;

    for (i = 0; i < WAVCACHE_N; ++i) {
        /* ВАЖНО: НЕ проверять refs>0 при поиске. Игра постоянно
           открывает/закрывает поток, refs после close всегда 0, и с
           проверкой refs кэш не срабатывал НИКОГДА (декодирование 6.5 МБ
           по 100 раз в секунду). */
        if (g_wc[i].data && !_stricmp(g_wc[i].name, fn)) {
            ++g_wc[i].refs;
            g_wc[i].used = ++g_wcClock;
            *data = g_wc[i].data; *chans = g_wc[i].chans;
            *len = g_wc[i].len;   *rate = g_wc[i].rate;
            g_wcHits++;
            return i;
        }
    }
    /* Ищем свободный слот или кандидата на вытеснение.
       НЕ трогаем слоты, где играет общий транспорт (mixer читает c->data)
       или есть живые хендлы (o->v.src.raw16 == c->data). */
    for (i = 0; i < WAVCACHE_N; ++i) {
        if (!g_wc[i].data) { victim = i; break; }
        if (g_wc[i].refs == 0 && !g_wc[i].transport && g_wc[i].used < oldest) {
            oldest = g_wc[i].used; victim = i;
        }
    }
    g_wcMiss++;
    if (victim < 0) {
        /* Кэш забит занятыми слотами: декодируем НЕ кэшируя, владение
           буфером переходит вызывающему (AIL_open_stream/close_stream). */
        if (LoadWav(fn, data, chans, len, rate) != 0 || !*data) return -1;
        return -2;
    }
    if (g_wc[victim].data) {
        free(g_wc[victim].data);
        g_wc[victim].data = 0;
    }
    if (LoadWav(fn, data, chans, len, rate) != 0 || !*data) return -1;
    memset(&g_wc[victim].tv, 0, sizeof(g_wc[victim].tv));
    g_wc[victim].transport  = 0;
    g_wc[victim].vol        = GTA2_MASTER_VOL;
    g_wc[victim].pan        = GTA2_PAN_CENTER;
    _snprintf(g_wc[victim].name, sizeof(g_wc[victim].name), "%s", fn);
    g_wc[victim].data  = *data;
    g_wc[victim].chans = *chans;
    g_wc[victim].len   = *len;
    g_wc[victim].rate  = *rate;
    g_wc[victim].refs  = 1;
    g_wc[victim].used  = ++g_wcClock;
    return victim;
}

static void WavCachePut(int idx)
{
    if (idx >= 0 && idx < WAVCACHE_N && g_wc[idx].refs > 0) --g_wc[idx].refs;
}

/* Живые потоки. Объекты выделяются в куче, поэтому КАЖДЫЙ AIL_open_stream
   возвращает уникальный хендл - как в retail Miles. Со статическим пулом
   хендл переиспользовался, и AIL_close_stream(старый) убивал новый поток. */
HSTREAM AILCALL AIL_open_stream(HDIGDRIVER dig, char const* filename, S32 stream_mem)
{
    int ci;
    short* data = 0;
    int chans = 0;
    U32 len = 0, rate = 0;
    Obj* o;

    g_wcOpenCalls++;
    if (g_strCount >= MAX_STREAMS) return 0;
    if (!filename) return 0;
    ci = WavCacheGet(filename, &data, &chans, &len, &rate);
    if (ci < 0 && ci != -2) return 0;

    o = (Obj*)calloc(1, sizeof(Obj));
    if (!o) { if (ci >= 0) WavCachePut(ci); else if (ci == -2) free(data); return 0; }
    o->magic = OBJ_MAGIC;
    o->owned = (ci == -2) ? data : 0;
    o->v.src.raw16 = data;
    o->v.src.chans = chans;
    o->v.src.len   = len;
    o->v.src.rate  = rate;
    o->v.len       = len;
    o->v.loopStart = 0;
    o->v.loopEnd   = len;
    o->v.volume    = GTA2_MASTER_VOL;
    o->v.pan       = GTA2_PAN_CENTER;
    o->v.loopCount = 0;
    o->v.totalMs   = rate ? (U32)((U64)len * 1000 / rate) : 0;
    o->v.status    = SMP_STOPPED;
    o->v.cacheIdx  = ci;
    g_strLive[g_strCount++] = o;

    if (g_wcOpenCalls <= 3 || (g_wcOpenCalls % 200) == 0)
        L("AIL_open_stream #%lu \"%s\" -> %p (%u frames ch=%d rate=%u)",
          g_wcOpenCalls, filename, (void*)o, len, chans, rate);
    return (HSTREAM)o;
}

void AILCALL AIL_close_stream(HSTREAM s)
{
    int i, j;
    if (!s) return;
    g_wcCloseCalls++;
    for (i = 0; i < g_strCount; ++i) {
        if (g_strLive[i] == (Obj*)s) {
            for (j = i; j + 1 < g_strCount; ++j) g_strLive[j] = g_strLive[j + 1];
            --g_strCount;
            break;
        }
    }
    if (g_wcCloseCalls <= 6 || (g_wcCloseCalls % 200) == 0)
        L("AIL_close_stream(%p) live=%d pos=%.0f status=%d",
          s, g_strCount, ((Obj*)s)->v.pos, (int)((Obj*)s)->v.status);
    /* close НЕ останавливает транспорт - иначе 30 раз в секунду музыка
       начинается с нуля и заикается (см. AIL_start_stream). */
    if (((Obj*)s)->owned) { free(((Obj*)s)->owned); ((Obj*)s)->owned = 0; }
    ((Obj*)s)->magic = 0;
    ((Obj*)s)->v.status = SMP_FREE;
    WavCachePut(((Obj*)s)->v.cacheIdx);
    free((void*)s);
}

void AILCALL AIL_start_stream(HSTREAM s)
{
    Obj* o = (Obj*)s;
    if (!s) return;
    /* ВАЖНО: GTA2 дёргает open->start->close ~30 раз в секунду на одном и
       том же файле. Если каждый start начинает с pos=0, а close убивает
       объект, микшер успевает отрендерить только первый буфер (46 мс) и
       музыка идёт щелчком. Поэтому состояние воспроизведения живёт в
       кэше файла (общий транспорт), а хендл - просто ссылка на него. */
    if (o->v.cacheIdx >= 0) {
        WavCache* c = &g_wc[o->v.cacheIdx];
        if (!c->transport) {
            memset(&c->tv, 0, sizeof(c->tv));
            c->tv.src.raw16 = c->data;
            c->tv.src.chans = c->chans;
            c->tv.src.len   = c->len;
            c->tv.src.rate  = c->rate;
            c->tv.len = c->len;  c->tv.loopStart = 0;  c->tv.loopEnd = c->len;
            c->tv.volume = o->v.volume;  c->tv.pan = o->v.pan;
            c->tv.loopCount = o->v.loopCount;
            c->tv.totalMs = c->rate ? (U32)((U64)c->len * 1000 / c->rate) : 0;
            c->tv.pos = 0;  c->tv.loopsDone = 0;
            c->transport = 1;
            g_wcStartCalls++;
            L("AIL_start_stream(%p) transport BEGIN %s", s, c->name);
        } else {
            c->vol = o->v.volume;  c->pan = o->v.pan;
            c->tv.volume = c->vol; c->tv.pan = c->pan;
        }
        c->tv.status = SMP_PLAYING;
        SetEvent(g_wakeEv);
        return;
    }
    if (o->v.status == SMP_PLAYING) return;
    o->v.pos = 0;
    o->v.loopsDone = 0;
    o->v.status = SMP_PLAYING;
    SetEvent(g_wakeEv);
    g_wcStartCalls++;
}

void AILCALL AIL_set_stream_loop_count(HSTREAM s, S32 count)
{
    if (!s) return;
    ((Obj*)s)->v.loopCount = count;
}

void AILCALL AIL_set_stream_playback_rate(HSTREAM s, S32 rate)
{
    if (!s || rate <= 0) return;
    ((Obj*)s)->v.src.rate = (double)rate;
}

S32 AILCALL AIL_stream_playback_rate(HSTREAM s)
{
    if (!s) return 0;
    return (S32)((Obj*)s)->v.src.rate;
}

void AILCALL AIL_set_stream_ms_position(HSTREAM s, S32 ms)
{
    if (!s) return;
    if (((Obj*)s)->v.cacheIdx >= 0) {
        WavCache* c = &g_wc[((Obj*)s)->v.cacheIdx];
        c->tv.pos = (double)ms * c->rate / 1000.0;
        return;
    }
    ((Obj*)s)->v.pos = (double)ms * ((Obj*)s)->v.src.rate / 1000.0;
}

void AILCALL AIL_stream_ms_position(HSTREAM s, S32* total_ms, S32* current_ms)
{
    if (!s) return;
    if (((Obj*)s)->v.cacheIdx >= 0) {
        WavCache* c = &g_wc[((Obj*)s)->v.cacheIdx];
        if (total_ms)   *total_ms = (S32)(c->rate ? (U32)((U64)c->len * 1000 / c->rate) : 0);
        if (current_ms) *current_ms = (S32)(c->rate ? (U32)(c->tv.pos * 1000.0 / c->rate) : 0);
        return;
    }
    if (total_ms)   *total_ms = (S32)((Obj*)s)->v.totalMs;
    if (current_ms) *current_ms = (S32)(((Obj*)s)->v.pos * 1000.0 / ((Obj*)s)->v.src.rate);
}

S32 AILCALL AIL_stream_status(HSTREAM s)
{
    /* GTA2 трактует 2 как "играет". */
    S32 r;
    if (!s) return 0;
    if (((Obj*)s)->v.cacheIdx >= 0) {
        WavCache* c = &g_wc[((Obj*)s)->v.cacheIdx];
        r = c->transport ? 2 : 0;
        if (g_wcStatCalls < 12 || (g_wcStatCalls % 600) == 0)
            L("AIL_stream_status(%p) -> %d (transport=%d pos=%.0f)", s, r, c->transport, c->tv.pos);
        g_wcStatCalls++;
        return r;
    }
    r = ((Obj*)s)->v.status == SMP_PLAYING ? 2 : 0;
    g_wcStatCalls++;
    return r;
}

void AILCALL AIL_set_stream_volume(HSTREAM s, S32 volume)
{
    if (!s) return;
    if (volume < 0) volume = 0;
    if (volume > 127) volume = 127;
    if (((Obj*)s)->v.volume != volume) {
        L("AIL_set_stream_volume(%p, %d old=%d)", s, volume, ((Obj*)s)->v.volume);
        ((Obj*)s)->v.volume = volume;
    }
    if (((Obj*)s)->v.cacheIdx >= 0) {
        g_wc[((Obj*)s)->v.cacheIdx].vol = volume;
        g_wc[((Obj*)s)->v.cacheIdx].tv.volume = volume;
    }
}

S32 AILCALL AIL_stream_volume(HSTREAM s)
{
    if (!s) return 0;
    return ((Obj*)s)->v.volume;
}

/* ================= 3D ================= */
S32 AILCALL AIL_enumerate_3D_providers(HPROENUM* next, HPROVIDER* dest, C8** name)
{
    L("AIL_enumerate_3D_providers(next=%p)", next);
    if (next && *next == 0) {
        if (dest) *dest = (HPROVIDER)1;
        if (name) *name = (C8*)GTA2_3D_PROVIDER_NAME;
        if (next) *next = 1;
        return 1;
    }
    if (next) *next = 0;
    return 0;
}

M3DRESULT AILCALL AIL_open_3D_provider(HPROVIDER lib)
{
    L("AIL_open_3D_provider(%u)", lib);
    if (!lib) return M3D_INVALID_PARAM;
    g_3dOpen = 1;
    return M3D_NOERR;
}

void AILCALL AIL_close_3D_provider(HPROVIDER lib)
{
    L("AIL_close_3D_provider(%u)", lib);
    g_3dOpen = 0;
}

void AILCALL AIL_3D_provider_attribute(HPROVIDER lib, C8 const* name, void* val)
{
    L("AIL_3D_provider_attribute(%u, \"%s\", %p)", lib, name ? name : "", val);
    /* GTA2 читает РОВНО ОДИН байт и требует 8..16, иначе отключает 3D
       (gta2.exe.c:151168-151182). */
    if (val && name && !strcmp(name, "Maximum supported samples"))
        *(BYTE*)val = (BYTE)MAX_3D;
}

void AILCALL AIL_set_3D_provider_preference(HPROVIDER lib, C8 const* name, void const* val)
{
    L("AIL_set_3D_provider_preference(%u, \"%s\", %p)", lib, name ? name : "", val);
}

H3DSAMPLE AILCALL AIL_allocate_3D_sample_handle(HPROVIDER lib)
{
    int i;
    for (i = 0; i < MAX_3D; ++i) {
        if (g_s3d[i].magic != OBJ_MAGIC) {
            memset(&g_s3d[i], 0, sizeof(Obj));
            g_s3d[i].magic = OBJ_MAGIC;
            g_s3d[i].v.status = SMP_FREE;
            g_s3d[i].v.is3D = 1;
            g_s3d[i].v.volume = GTA2_MASTER_VOL;
            g_s3d[i].v.dFrontMin = 0; g_s3d[i].v.dFrontMax = -1;
            g_s3d[i].v.dBackMin  = 0; g_s3d[i].v.dBackMax  = -1;
            g_s3d[i].v.vol3D = 1.0f;
            ++g_3dHandles;
            L("AIL_allocate_3D_sample_handle -> slot %d", i);
            return (H3DSAMPLE)&g_s3d[i];
        }
    }
    return 0;
}

void AILCALL AIL_release_3D_sample_handle(H3DSAMPLE S)
{
    if (!S) return;
    ((Obj*)S)->magic = 0;
    if (g_3dHandles > 0) --g_3dHandles;
}

S32 AILCALL AIL_set_3D_sample_info(H3DSAMPLE S, AILSOUNDINFO const* info)
{
    if (!S || !info) return -1;
    EnterCriticalSection(&g_lock);
    ((Obj*)S)->v.src.raw8  = (const BYTE*)info->data_ptr;
    ((Obj*)S)->v.src.raw16 = 0;
    ((Obj*)S)->v.src.chans = info->channels ? info->channels : 1;
    ((Obj*)S)->v.src.rate  = info->rate ? (double)info->rate : 22050.0;
    ((Obj*)S)->v.len       = info->data_len;
    ((Obj*)S)->v.loopStart = 0;
    ((Obj*)S)->v.loopEnd   = info->data_len;
    LeaveCriticalSection(&g_lock);
    L("AIL_set_3D_sample_info(%p, fmt=%d rate=%lu len=%lu bits=%d ch=%d)",
      S, info->format, info->rate, info->data_len, info->bits, info->channels);
    return 0;
}

void AILCALL AIL_start_3D_sample(H3DSAMPLE S)
{
    if (!S) return;
    ((Obj*)S)->v.pos = 0;
    ((Obj*)S)->v.loopsDone = 0;
    ((Obj*)S)->v.status = SMP_PLAYING;
    SetEvent(g_wakeEv);
}

void AILCALL AIL_end_3D_sample(H3DSAMPLE S)
{
    if (!S) return;
    ((Obj*)S)->v.status = SMP_STOPPED;
}

U32 AILCALL AIL_3D_sample_status(H3DSAMPLE S)
{
    if (!S) return SMP_FREE;
    return ((Obj*)S)->v.status;
}

void AILCALL AIL_set_3D_sample_volume(H3DSAMPLE S, F32 volume)
{
    if (!S) return;
    if (volume < 0) volume = 0;
    if (volume > 1) volume = 1;
    {
        S32 old = ((Obj*)S)->v.volume;
        ((Obj*)S)->v.volume = (S32)(volume * 127.0f);
        if (old != ((Obj*)S)->v.volume) L("AIL_set_3D_sample_volume(%p, %.2f old=%d)", S, volume, old);
    }
}

void AILCALL AIL_set_3D_sample_playback_rate(H3DSAMPLE S, S32 rate)
{
    if (!S || rate <= 0) return;
    ((Obj*)S)->v.src.rate = (double)rate;
}

void AILCALL AIL_set_3D_sample_loop_count(H3DSAMPLE S, U32 loops)
{
    if (!S) return;
    ((Obj*)S)->v.loopCount = (S32)loops;
}

void AILCALL AIL_set_3D_sample_loop_block(H3DSAMPLE S, S32 start_offset, S32 end_offset)
{
    if (!S) return;
    ((Obj*)S)->v.loopStart = (U32)(start_offset < 0 ? 0 : start_offset);
    ((Obj*)S)->v.loopEnd   = (U32)(end_offset   < 0 ? (S32)((Obj*)S)->v.len : end_offset);
}

/* v5: 4 float. Первый аргумент — H3DSAMPLE. */
void AILCALL AIL_set_3D_sample_float_distances(H3DSAMPLE S, F32 fmin, F32 fmax, F32 bmin, F32 bmax)
{
    if (!S) return;
    ((Obj*)S)->v.dFrontMin = fmin;
    ((Obj*)S)->v.dFrontMax = fmax;
    ((Obj*)S)->v.dBackMin  = bmin;
    ((Obj*)S)->v.dBackMax  = bmax;
    L("AIL_set_3D_sample_float_distances(%p, %f, %f, %f, %f)", S, fmin, fmax, bmin, bmax);
}

void AILCALL AIL_set_3D_position(H3DPOBJECT obj, F32 X, F32 Y, F32 Z)
{
    if (!obj) return;
    ((Obj*)obj)->v.x = X;
    ((Obj*)obj)->v.y = Y;
    ((Obj*)obj)->v.z = Z;
}

BOOL DllMain(HINSTANCE h, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) DisableThreadLibraryCalls(h);
    return TRUE;
}
