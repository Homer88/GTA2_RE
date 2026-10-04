/*
 * mss32_abi.h - ABI-контракт Miles Sound System 5.0r для GTA2.
 *
 * Сигнатуры восстановлены по таблице импортов gta2-resurected.exe
 * (52 функции с декораторами @N) и сверены с retail 5.0r.
 * ВНИМАНИЕ: здесь v5-сигнатуры, а НЕ v6.5c из mss.h.
 *   - volume/pan принимают S32 0..127 (в v6 перешли на F32 0..1)
 *   - AIL_set_3D_sample_float_distances принимает 4 float (в v6 осталось 2)
 */
#ifndef MSS32_ABI_H
#define MSS32_ABI_H

#include <windows.h>
#include <mmsystem.h>

typedef int           S32;
typedef unsigned int  U32;
typedef unsigned __int64 U64;
typedef float         F32;
typedef char          C8;
typedef int           BOOL_;

#define AILCALL  __stdcall

/* ---- хендлы (mss.h) ---- */
typedef struct _DIG_DRIVER  *HDIGDRIVER;
typedef struct _SAMPLE      *HSAMPLE;
typedef struct _STREAM      *HSTREAM;
typedef struct h3DPOBJECT   *H3DPOBJECT;
typedef H3DPOBJECT           H3DSAMPLE;
typedef U32                  HPROVIDER;
typedef U32                  HPROENUM;
typedef S32                  M3DRESULT;
typedef S32                  HTIMER;

typedef struct _AILSOUNDINFO {
    S32           format;        /* +0  WAVE_FORMAT_PCM=1 / IMA_ADPCM=0x11 */
    void const   *data_ptr;      /* +4 */
    U32           data_len;      /* +8 */
    U32           rate;          /* +C */
    S32           bits;          /* +10 */
    S32           channels;      /* +14 */
    U32           samples;       /* +18 */
    U32           block_size;    /* +1C */
    void const   *initial_ptr;   /* +20 */
} AILSOUNDINFO;                 /* 36 байт */

/* ---- статусы сэмпла (mss_6_1a.h; GTA2: пул SFX ждёт ==4, вокал !=2) ---- */
#define SMP_FREE     1u
#define SMP_DONE     2u
#define SMP_PLAYING  4u
#define SMP_STOPPED  8u

/* ---- M3D коды (mss.h:1403) ; GTA2 считает M3D_NOERR успехом ---- */
#define M3D_NOERR                0
#define M3D_NOT_ENABLED          1
#define M3D_ALREADY_STARTED      2
#define M3D_INVALID_PARAM        3
#define M3D_INTERNAL_ERR         4
#define M3D_OUT_OF_MEM           5
#define M3D_ERR_NOT_IMPLEMENTED  6
#define M3D_NOT_FOUND            7
#define M3D_NOT_INIT             8
#define M3D_CLOSE_ERR            9

/* ---- 3D режимы (mss.h:4767) ---- */
#define AIL_3D_2_SPEAKER   0
#define AIL_3D_HEADPHONE   1
#define AIL_3D_SURROUND    2
#define AIL_3D_4_SPEAKER   3
#define AIL_3D_51_SPEAKER  4
#define AIL_3D_71_SPEAKER  5

/* ---- форматы ---- */
#define PCM_FORMAT        1        /* 8-бит unsigned mono (из кода GTA2) */
#define PCM_FMT_PCM       1        /* WAVE_FORMAT_PCM */
#define PCM_FMT_ADPCM     0x0011   /* WAVE_FORMAT_IMA_ADPCM */

/* ---- значения по умолчанию GTA2 ---- */
#define GTA2_MAX_SAMPLES  32       /* пул SFX: игра берёт 1 + 16 = 17 хендлов */
#define GTA2_MASTER_VOL   127
#define GTA2_PAN_CENTER   64

/* Имя 3D-провайдера, которое GTA2 ищет дословно
   (Initialize3DAudioWithDirectSound @ 0x4B72B0, до 256 провайдеров). */
#define GTA2_3D_PROVIDER_NAME "Microsoft DirectSound3D hardware support"

/* ---- 52 прототипа v5, в порядке декораторов @N ---- */
extern "C" {

/* startup / prefs / digital driver */
int      AILCALL AIL_startup(void);
void     AILCALL AIL_shutdown(void);
int      AILCALL AIL_set_preference(U32 number, S32 value);
void     AILCALL AIL_delay(S32 intervals);
void*    AILCALL AIL_mem_alloc_lock(U32 size_or_addr);
void     AILCALL AIL_mem_free_lock(void* p);
int      AILCALL AIL_waveOutOpen(HDIGDRIVER* drvr, LPHWAVEOUT* lphWaveOut,
                                 S32 wDeviceID, LPWAVEFORMAT lpFormat);
                                 /* ВОЗВРАТ: 0 = успех, ненулевое = ошибка.
                                    GTA2 (gta2.exe.c:150886) делает if(ret) return 0. */
void     AILCALL AIL_waveOutClose(HDIGDRIVER drvr);
int      AILCALL AIL_digital_handle_release(HDIGDRIVER drvr);
int      AILCALL AIL_digital_handle_reacquire(HDIGDRIVER drvr);

/* sample (2D) */
HSAMPLE  AILCALL AIL_allocate_sample_handle(HDIGDRIVER dig);
void     AILCALL AIL_release_sample_handle(HSAMPLE S);
void     AILCALL AIL_init_sample(HSAMPLE S);
void     AILCALL AIL_set_sample_address(HSAMPLE S, void const* start, U32 len);
void     AILCALL AIL_set_sample_type(HSAMPLE S, S32 format, U32 flags);
void     AILCALL AIL_start_sample(HSAMPLE S);
void     AILCALL AIL_end_sample(HSAMPLE S);
U32      AILCALL AIL_sample_status(HSAMPLE S);
void     AILCALL AIL_set_sample_playback_rate(HSAMPLE S, S32 playback_rate);
void     AILCALL AIL_set_sample_loop_count(HSAMPLE S, S32 loop_count);
void     AILCALL AIL_set_sample_loop_block(HSAMPLE S, S32 start_offset, S32 end_offset);
/* v5: S32 0..127, НЕ F32 как в v6 */
void     AILCALL AIL_set_sample_volume(HSAMPLE S, S32 volume);
void     AILCALL AIL_set_sample_pan(HSAMPLE S, S32 pan);

/* stream */
HSTREAM  AILCALL AIL_open_stream(HDIGDRIVER dig, char const* filename, S32 stream_mem);
void     AILCALL AIL_close_stream(HSTREAM s);
void     AILCALL AIL_start_stream(HSTREAM s);
void     AILCALL AIL_set_stream_loop_count(HSTREAM s, S32 count);
void     AILCALL AIL_set_stream_playback_rate(HSTREAM s, S32 rate);
S32      AILCALL AIL_stream_playback_rate(HSTREAM s);
void     AILCALL AIL_set_stream_ms_position(HSTREAM s, S32 ms);
void     AILCALL AIL_stream_ms_position(HSTREAM s, S32* total_ms, S32* current_ms);
S32      AILCALL AIL_stream_status(HSTREAM s);
void     AILCALL AIL_set_stream_volume(HSTREAM s, S32 volume);   /* v5: 2 арг, 0..127 */
S32      AILCALL AIL_stream_volume(HSTREAM s);                  /* v5: геттер, 0..127 */

/* 3D provider */
S32      AILCALL AIL_enumerate_3D_providers(HPROENUM* next, HPROVIDER* dest, C8** name);
M3DRESULT AILCALL AIL_open_3D_provider(HPROVIDER lib);
void     AILCALL AIL_close_3D_provider(HPROVIDER lib);
void     AILCALL AIL_3D_provider_attribute(HPROVIDER lib, C8 const* name, void* val);
void     AILCALL AIL_set_3D_provider_preference(HPROVIDER lib, C8 const* name, void const* val);

/* 3D sample */
H3DSAMPLE AILCALL AIL_allocate_3D_sample_handle(HPROVIDER lib);
void      AILCALL AIL_release_3D_sample_handle(H3DSAMPLE S);
void      AILCALL AIL_start_3D_sample(H3DSAMPLE S);
void      AILCALL AIL_end_3D_sample(H3DSAMPLE S);
U32       AILCALL AIL_3D_sample_status(H3DSAMPLE S);
S32       AILCALL AIL_set_3D_sample_info(H3DSAMPLE S, AILSOUNDINFO const* info);
void      AILCALL AIL_set_3D_sample_volume(H3DSAMPLE S, F32 volume);
void      AILCALL AIL_set_3D_sample_playback_rate(H3DSAMPLE S, S32 playback_rate);
void      AILCALL AIL_set_3D_sample_loop_count(H3DSAMPLE S, U32 loops);
void      AILCALL AIL_set_3D_sample_loop_block(H3DSAMPLE S, S32 start_offset, S32 end_offset);
/* v5: 4 float. Первый аргумент — H3DSAMPLE (в mss_v5compat.h ошибочно HSAMPLE). */
void      AILCALL AIL_set_3D_sample_float_distances(H3DSAMPLE S, F32 front_min,
                                                    F32 front_max, F32 back_min, F32 back_max);
void      AILCALL AIL_set_3D_position(H3DPOBJECT obj, F32 X, F32 Y, F32 Z);

/* master volume: v5 — S32 0..127 */
void      AILCALL AIL_set_digital_master_volume(HDIGDRIVER dig, S32 volume);

} /* extern "C" */

#endif /* MSS32_ABI_H */
