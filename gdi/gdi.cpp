// GDI software back-end for GTA2, for running over RDP where no DirectDraw
// adapter exists.
//
// Renders into a top-down 32bpp DIB section, presents with GDI BitBlt/StretchBlt.
// GDI works over RDP; DirectDraw does not.
//
// Export signatures are copied VERBATIM from d3ddll\d3ddll.h. With __stdcall
// the callee pops its own arguments, so a wrong arity or type corrupts the
// caller's stack. Do not "simplify" any prototype here.
//
// GTA2 does its own polygon sorting (it rejects polys with z <= 0), so this
// rasteriser is painter's-algorithm: no z-buffer.

#include <windows.h>
#include <tlhelp32.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------------------------------------------ types
typedef unsigned short u16;
typedef signed   int     s32;
typedef unsigned int     u32;
typedef float            f32;
typedef unsigned char    u8;

#define CC __stdcall

// older MSVC has no STATIC_ASSERT
#ifndef STATIC_ASSERT
#define STATIC_ASSERT(expr, msg) typedef char sa_##__LINE__[(expr) ? 1 : -1]
#endif

// ------------------------------------------------------------------ structs
// from d3ddll.h
struct Texture;
struct Cache;

struct Texture
{
    unsigned short ID;
    unsigned short field_2;
    unsigned short PalIsTrans;
    unsigned short PalSize;
    void*  pLockedPixels;
    BYTE   field_C;
    BYTE   field_D;
    unsigned short Width;
    unsigned short Height;
    u8     PalIsValid;
    u8     Flags;
    BYTE*  pOriginalPixelData;
    WORD*  pPaltData;
    struct Cache* NextCache;
};

struct Vert
{
    float x, y, z, w;
    DWORD diff;
    DWORD spec;
    float u, v;
};

struct Verts
{
    Vert mVerts[4];
};

struct Light
{
    DWORD field_0;
    float X, Y, Z;
    DWORD Colour;
};

// from d3ddll.cpp:95  (sizeof 0x2C)
struct Cache
{
    BYTE   field_0;
    BYTE   Flags;
    BYTE   field_2;
    BYTE   field_3;
    WORD   field_4;
    WORD   CacheIdx;
    DWORD  UsedFrameNum;
    float  field_C;
    DWORD  field_10;
    DWORD  field_14;
    struct Texture* pTexture;
    struct Cache* pNextCache;
    struct Cache* pCache;
    void*  TextureId;
    DWORD  field_28;
};
STATIC_ASSERT(sizeof(Cache) == 0x2C, "Wrong size Cache");

// from d3ddll.cpp:69 -- the game reads AND writes these.
struct Globals
{
    DWORD mNumPolysDrawn;
    DWORD mNumTextureSwaps;
    DWORD mNumBatchFlushes;
    DWORD mSceneTime;

    DWORD gCacheSizes[12];
    DWORD gCacheSizes1[12];
    DWORD gCacheHitRates[12];
    DWORD gCacheUnknown[12];
    Cache* CacheArray[12];
};
static Globals gGlobals;

/* счётчики вызовов - показывают, какой путь рисует, а какой молчит */
static DWORD g_nDrawQuad = 0, g_nDrawTri = 0, g_nDrawTile = 0;
static DWORD g_nFlatRect = 0, g_nPlot = 0, g_nBlitImage = 0, g_nQuadClipped = 0;
static DWORD g_nRasterTri = 0, g_nRasterRejectZ = 0, g_nRasterDegenerate = 0;
static DWORD g_nPlotPx = 0;
static DWORD g_nAddLight = 0, g_nSetAmbient = 0, g_nResetLights = 0, g_nSetCamera = 0;

// from d3ddll.h:86, packed
#pragma pack(push)
#pragma pack(1)
struct Image
{
    BYTE  field_0;
    BYTE  field_1;
    BYTE  field_2;
    BYTE  field_3;
    DWORD field_4;
    DWORD field_8;
    WORD  Width;
    WORD  Height;
    BYTE  field_10;
    BYTE  field_11;
    DWORD field_12;
};
#pragma pack(pop)

struct Video;   // opaque, defined in dmavideo.h; we only pass it through

// ------------------------------------------------------------------ logging
static FILE* g_log = 0;
static void L(const char* fmt, ...)
{
    if (!g_log) {
        g_log = fopen("C:\\games\\GTA2 _old\\log\\gdi.log", "ab");
        if (!g_log) return;
    }
    va_list ap; va_start(ap, fmt);
    vfprintf(g_log, fmt, ap);
    va_end(ap);
    fputc('\n', g_log);
    fflush(g_log);
}

// ------------------------------------------------------------------ back buffer
static const int SCREEN_W = 640;
static const int SCREEN_H = 480;

static HWND     g_hwnd  = 0;
static HDC      g_memDC = 0;
static HDC      g_winDC = 0;
static HBITMAP  g_bmp   = 0;
static HGDIOBJ  g_oldBmp = 0;
static DWORD*   g_bits  = 0;
static int      g_w = SCREEN_W, g_h = SCREEN_H;
static int      g_bFrames = 0;
static DWORD    g_lastCol = 0;
static int      gScreenTableSize = 0;
static int      g_setWindowCalls = 0;
static int      g_bImages = 0;
static int      g_bScenes = 0;
static int      g_lastBlitRet = 0;
static int      g_bufFromTable = 0;
static LRESULT CALLBACK g_origProc = 0;
static LRESULT CALLBACK SubProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
    if (m == WM_ERASEBKGND) return 1;          // stop the flicker
    if (m == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        if (dc && g_bits && g_memDC) {
            RECT rc; GetClientRect(h, &rc);
            SetStretchBltMode(dc, COLORONCOLOR);
            StretchBlt(dc, 0, 0, rc.right, rc.bottom,
                       g_memDC, 0, 0, g_w, g_h, SRCCOPY);
        }
        EndPaint(h, &ps);
        return 0;
    }
    /* Cursor must stay visible in the window: the game (DirectDraw-era) keeps
       hiding it. Forcing the arrow here beats any SetCursor(NULL) it does. */
    if (m == WM_SETCURSOR) {
        SetCursor(LoadCursorA(NULL, (LPCSTR)IDC_ARROW));
        return TRUE;
    }
    return CallWindowProcA((WNDPROC)g_origProc, h, m, w, l);
}
static LRESULT CALLBACK g_origProc2_unused = 0;
static int g_madeWindowed = 0;
static HWND FindGameWindow();
static long g_bestArea = 0;
static void MakeWindowed(HWND h)
{
    if (g_madeWindowed) return;
    if (!h) { h = FindGameWindow(); L("MakeWindowed: hwnd was null, FindGameWindow -> %p", h); }
    if (!h) return;
    int ww = (g_w >= 640) ? g_w : 1024;
    int hh = (g_h >= 480) ? g_h : 768;
    g_madeWindowed = 1;
    LONG style = GetWindowLongA(h, GWL_STYLE);
    SetWindowLongA(h, GWL_STYLE, WS_OVERLAPPEDWINDOW);
    SetWindowPos(h, HWND_TOP, 632, 280, ww, hh, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    ShowWindow(h, SW_SHOWNORMAL);
    SetForegroundWindow(h);
    g_origProc = (LRESULT)SetWindowLongA(h, GWLP_WNDPROC, (LONG)SubProc);
    L("windowed mode applied %dx%d, subclassed wndproc (orig=%p style %08lX->%08lX)",
      ww, hh, (void*)g_origProc, (unsigned long)style, (unsigned long)WS_OVERLAPPEDWINDOW);
}
static int      g_rectRight  = SCREEN_W - 1;
static int      g_rectBottom = SCREEN_H - 1;

// image table (see gbh_LoadImage / gbh_BlitImage below)
struct ImageTableEntry
{
    DWORD* pSurface;   // 0x00RRGGBB pixels, top-down, W*H
    int    Loaded;
    int    W;
    int    H;
};
static ImageTableEntry* gImageTable      = 0;
static int              gImageTableCount = 0;
static int      g_dirty = 0;

// ------------------------------------------------------------------ palette / texture storage
struct PalData
{
    DWORD* mPOriginalData;  // expanded 0x00RRGGBB
    WORD*  mPData;          // raw 16-bit entries as delivered by the game
    DWORD  mbLoaded;
};
static PalData gPals[4096];
static DWORD   gCurrentColour = 0;

// GTA2 palettes are 15-bit BGR; be tolerant of 8-bit tables too.
/* Палитра приходит от игры массивом DWORD'ов, но адресуется с ШАГОМ 64 DWORD'а
   (256 байт) - это видно в эталонном драйвере d3ddll.cpp:2873 "pData += 64".
   Раньше здесь читалось mPData[i] подряд с шагом 2 байта, то есть совсем не
   та память - палитра получалась нулевой и весь текст (он рисуется глифами
   через палитру) был чёрным.
   Retail также правит палитру НА МЕСТЕ: элемент 0 обнуляется, а нулевые
   элементы заменяются на 0x10000. Это часть контракта, игра это читает. */
static void ExpandPaletteStrided(PalData* p, DWORD* pOriginal)
{
    if (!p || !p->mPData || !pOriginal) return;

    DWORD* src = pOriginal;
    for (int i = 0; i < 256; ++i) {
        DWORD c = *src;
        int r, g, b;
        /* GTA2 style palettes store each entry as a DWORD in BGRA byte order
           (see GTA2 Style Format 5.1 / retail ConvertPixel). Reading it as
           0x00RRGGBB swapped red and blue (red selections appeared blue).
           ВАЖНО: без эвристики "5 бит на канал". У всех тёмных записей каналы
           <=31 (это и есть чёрные полоски), и побитовая реинтерпретация давала
           из чёрного синий и прочий мусор. Всегда 8-бит BGRA, как в retail. */
        b = (int)(c & 0xFF);
        g = (int)((c >> 8) & 0xFF);
        r = (int)((c >> 16) & 0xFF);
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        /* RasterTri ждёт 5 бит на канал в раскладке 0xBBGGRRR */
        WORD w = (WORD)(((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3));
        p->mPData[i] = w;
        /* и сразу кладём 32-битный цвет в кэш */
        /* mPOriginalData is a read-only identity key (game buffer a2). */
        src += 64;
    }
    {
        /* Диагностика: та самая палитра, что реально юзает текущая текстура -
           печатаем её ПОЛНОСТЬЮ (сырые DWORD, шаг 64) и заодно десятичный
           сэмпл ключевых индексов, чтобы понять формат WHITE/жёлтого. */
        static DWORD s_palDbg[6] = {0};
        int slot = -1;
        for (int i = 0; i < 6; ++i) {
            if (s_palDbg[i] == (DWORD)pOriginal) { slot = i; break; }
            if (s_palDbg[i] == 0) { s_palDbg[i] = (DWORD)pOriginal; slot = i; break; }
        }
        if (slot >= 0 && slot < 3) {
            char buf[3200];
            int pos = sprintf(buf, "PALFULL%d @ %08lX:", slot, (unsigned long)(DWORD)pOriginal);
            for (int i = 0; i < 256; ++i)
                pos += sprintf(buf + pos, " %02X=%08lX", i, (unsigned long)pOriginal[i * 64]);
            L("%s", buf);
        }
    }
}

// The per-vertex diffuse is a shade multiplier. GTA2 may hand us 5-bit or
// 8-bit components, so normalise to 0..255.
static void DiffuseScale(DWORD diff, int* pr, int* pg, int* pb)
{
    /* diff это D3DCOLOR 0x00RRGGBB (память little-endian: B,G,R,A). Брать
       r=diff&0xFF значило rентятся синим каналом - золотой текст (diff золотой)
       превращался в зелёный/бирюзовый из-за перестановки R и B. */
    int r = (int)((diff >> 16) & 0xFF);
    int g = (int)((diff >> 8) & 0xFF);
    int b = (int)(diff & 0xFF);
    /* diff == 0 - это не "чёрный свет", а "освещение не задано": gbh_ResetLights
       и gbh_BeginLevel у нас заглушки, поэтому игра присылает нулевой light.
       Раньше это схлопывалось в ShadeMul в чистый чёрный и ВЕСЬ текст (он рисуется
       квадами с нулевым diff) был не виден. Нулевой свет = полная яркость. */
    if (r == 0 && g == 0 && b == 0) { *pr = 255; *pg = 255; *pb = 255; return; }
    /* Никакой эвристики "<=31 -> 5-бит": диффуз/свет приходит как 8-бит
       D3DCOLOR 0x00RRGGBB (см. retail ConvertPixel и палитры BGRA). */
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    *pr = r; *pg = g; *pb = b;
}

static inline DWORD ShadeMul(DWORD clr, int sr, int sg, int sb)
{
    int r = (int)(((clr >> 16) & 0xFF) * sr) >> 8;
    int g = (int)(((clr >>  8) & 0xFF) * sg) >> 8;
    int b = (int)(((clr      & 0xFF) * sb) >> 8);
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    return 0xFF000000u | ((DWORD)r << 16) | ((DWORD)g << 8) | (DWORD)b;
}

// ------------------------------------------------------------------ DIB
static int CreateBackBuffer(int w, int h)
{
    if (g_bits) return 1;

    BITMAPINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = w;
    bi.bmiHeader.biHeight      = -h;          // top-down
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    g_memDC = CreateCompatibleDC(NULL);
    if (!g_memDC) { L("CreateCompatibleDC failed %lu", GetLastError()); return 0; }

    g_bmp = CreateDIBSection(g_memDC, &bi, DIB_RGB_COLORS,
                             (void**)&g_bits, NULL, 0);
    if (!g_bmp || !g_bits) {
        L("CreateDIBSection failed %lu", GetLastError());
        if (g_memDC) { DeleteDC(g_memDC); g_memDC = 0; }
        return 0;
    }
    g_oldBmp = SelectObject(g_memDC, g_bmp);
    g_w = w; g_h = h;
    L("back buffer %dx%dx32 bits=%p", w, h, (void*)g_bits);
    return 1;
}

static void DestroyBackBuffer()
{
    if (g_winDC && g_hwnd) { ReleaseDC(g_hwnd, g_winDC); g_winDC = 0; }
    if (g_memDC) {
        if (g_oldBmp) SelectObject(g_memDC, g_oldBmp);
        if (g_bmp) DeleteObject(g_bmp);
        DeleteDC(g_memDC);
    }
    g_memDC = 0; g_bmp = 0; g_oldBmp = 0; g_bits = 0;
    L("back buffer destroyed");
}

static void ClearBuffer(DWORD colour)
{
    if (!g_bits) return;
    DWORD* p = g_bits;
    DWORD  n = (DWORD)(g_w * g_h);
    for (DWORD i = 0; i < n; ++i) p[i] = colour;
}

// The game never hands us an HWND on the exported path, so find our own
// top-level visible window instead of guessing.
static BOOL CALLBACK FindWinProc(HWND h, LPARAM p)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    if (!IsWindowVisible(h)) return TRUE;

    // Our own hook opens a "GTA2 Struct Inspector" / console window in the same
    // process. Picking the first visible window grabbed THAT one instead of the
    // game window, so the render went to the log window while the game played
    // in a different window. Skip the tooling windows...
    char t[160] = {0};
    GetWindowTextA(h, t, sizeof(t));
    if (strstr(t, "Inspector") || strstr(t, ".exe") || !t[0]) return TRUE;

    // ...and take the largest remaining one: that is the real game window.
    RECT r;
    if (!GetWindowRect(h, &r)) return TRUE;
    long area = (long)(r.right - r.left) * (long)(r.bottom - r.top);
    if (area <= 0) return TRUE;
    if (area > g_bestArea) { g_bestArea = area; g_hwnd = h; }
    return TRUE;
}

static HWND FindGameWindow()
{
    g_hwnd = 0;
    g_bestArea = 0;
    EnumWindows(FindWinProc, 0);
    return g_hwnd;
}

// The game paints over this window in its own WM_PAINT. We subclass the
// window and blit from inside WM_PAINT (see SubProc) so the presentation is
// synchronised with the game's own repaints - blitting from a separate thread
// fought with WM_ERASEBKGND and produced heavy flicker.
static int BlitToWindow()
{
    if (!g_bits) return 0;
    if (!g_hwnd || !IsWindow(g_hwnd)) {
        if (!FindGameWindow()) return 0;
    }
    if (!g_winDC) g_winDC = GetDC(g_hwnd);
    if (!g_winDC) return 0;

    static int s_chk = 0;
    if (s_chk++ < 2) {
        char cls[64] = {0}, txt[128] = {0};
        GetClassNameA(g_hwnd, cls, 64);
        GetWindowTextA(g_hwnd, txt, 128);
        RECT wr; GetWindowRect(g_hwnd, &wr);
        L("  [blit target] hwnd=%p class='%s' title='%s' vis=%d iconic=%d rect=%ld,%ld,%ld,%ld",
          g_hwnd, cls, txt, IsWindowVisible(g_hwnd), IsIconic(g_hwnd),
          wr.left, wr.top, wr.right, wr.bottom);
        // list every top-level window we own, so we can spot a mismatch
        HWND w = GetTopWindow(0);
        while (w) {
            DWORD pid = 0;
            GetWindowThreadProcessId(w, &pid);
            if (pid == GetCurrentProcessId()) {
                char t2[128] = {0}; GetWindowTextA(w, t2, 128);
                RECT r2; GetWindowRect(w, &r2);
                L("  [own window] hwnd=%p class='%s' title='%s' vis=%d rect=%ld,%ld,%ld,%ld",
                  w, cls, t2, IsWindowVisible(w), r2.left, r2.top, r2.right, r2.bottom);
            }
            w = GetWindow(w, GW_HWNDNEXT);
        }
    }

    RECT rc;
    GetClientRect(g_hwnd, &rc);
    int cw = rc.right - rc.left;
    int ch = rc.bottom - rc.top;
    if (cw <= 0 || ch <= 0) return 0;

    if (!g_origProc) {
        MakeWindowed(g_hwnd);
    }

    SetStretchBltMode(g_winDC, COLORONCOLOR);
    int ok = StretchBlt(g_winDC, 0, 0, cw, ch,
                        g_memDC, 0, 0, g_w, g_h, SRCCOPY) ? 1 : 0;
    if (ok) { GdiFlush(); RedrawWindow(g_hwnd, 0, 0, RDW_UPDATENOW | RDW_INVALIDATE); }
    /* Belt-and-braces vs the game calling ShowCursor(FALSE): re-show every frame. */
    if (ok) while (ShowCursor(TRUE) < 1) {}
    return ok;
}

// ------------------------------------------------------------------ rasteriser
static void PlotPixel(int x, int y, DWORD clr)
{
    if (x < 0 || y < 0 || x >= g_w || y >= g_h) return;
    g_bits[(DWORD)y * g_w + x] = clr;
    ++g_nPlotPx;
}

static void FillRect(int x, int y, int w, int h, DWORD clr)
{
    if (!g_bits) return;
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > g_w) w = g_w - x;
    if (y + h > g_h) h = g_h - y;
    if (w <= 0 || h <= 0) return;
    for (int j = 0; j < h; ++j) {
        DWORD* row = g_bits + (DWORD)(y + j) * g_w + x;
        for (int i = 0; i < w; ++i) row[i] = clr;
    }
}

// Affine-mapped textured triangle with per-vertex diffuse.
static void RasterTri(const Vert* v0, const Vert* v1, const Vert* v2,
                      Texture* tex, int baseColour)
{
    if (!g_bits) return;

    ++g_nRasterTri;
    /* Ближний отсев. Раньше здесь стояло "если ЛЮБАЯ вершина z<=0 - отбросить
       треугольник", из-за чего терялись большие квады (земля, фон, небо): у
       большого квада одна вершина почти всегда уходит за near plane, и весь
       квад пропадал - это и давало "видна только левая половина кадра".
       Теперь отбрасываем только когда ЗА КАМЕРОЙ все вершины. */
    if (v0->z <= 0.0f && v1->z <= 0.0f && v2->z <= 0.0f) { ++g_nRasterRejectZ; return; }

    float minX = v0->x, maxX = v0->x;
    float minY = v0->y, maxY = v0->y;
    if (v1->x < minX) minX = v1->x; if (v1->x > maxX) maxX = v1->x;
    if (v2->x < minX) minX = v2->x; if (v2->x > maxX) maxX = v2->x;
    if (v1->y < minY) minY = v1->y; if (v1->y > maxY) maxY = v1->y;
    if (v2->y < minY) minY = v2->y; if (v2->y > maxY) maxY = v2->y;

    int x0 = (int)floorf(minX), x1 = (int)ceilf(maxX);
    int y0 = (int)floorf(minY), y1 = (int)ceilf(maxY);
    if (x0 < 0) x0 = 0; if (y0 < 0) y0 = 0;
    if (x1 > g_w) x1 = g_w; if (y1 > g_h) y1 = g_h;
    if (x0 >= x1 || y0 >= y1) return;

    float ax = v0->x, ay = v0->y;
    float bx = v1->x, by = v1->y;
    float cx = v2->x, cy = v2->y;

    float area = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    if (fabsf(area) < 1e-6f) { ++g_nRasterDegenerate; return; }
    float inv = 1.0f / area;

    BYTE*    pix = tex ? tex->pOriginalPixelData : 0;
    int      tw  = tex ? (int)tex->Width  : 0;
    int      th  = tex ? (int)tex->Height : 0;
    WORD*    pal = 0;
    if (tex) {
        /* Ключ - исходный буфер палитры, который задала игра (mPOriginalData);
           mPData теперь наш сконвертированный массив. */
        for (int i = 0; i < 4096; ++i)
            if (gPals[i].mbLoaded && gPals[i].mPOriginalData == (DWORD*)tex->pPaltData) {
                pal = gPals[i].mPData; break;
            }
    }

    /* Перспективная коррекция текстуры. Retail gbh_DrawQuad перед отрисовкой
       делает w = z (d3ddll.cpp:1165), т.е. D3D интерполирует u/z, v/z, 1/z
       линейно по экрану и делит: u = (sum b*u/z) / (sum b/z). Без этого большие
       квады мира (здания, земля) и наклонённые спрайты ломались аффинным изломом
       (текстура "перекручена", спрайты выглядят повёрнутыми на 90/180°), тогда
       как мелкие квады (машины, HUD) остаются почти орто и выглядят верно.
       Для HUD z масштабировано ортогонально (z=const) - деление вырождается в
       аффинное, ничего не меняя. */
    float invZ[3], uToW[3], vToW[3];
    for (int k = 0; k < 3; ++k) {
        const Vert* vv = k == 0 ? v0 : (k == 1 ? v1 : v2);
        if (vv->z > 1e-4f) {
            invZ[k] = 1.0f / vv->z;
            uToW[k] = vv->u * invZ[k];
            vToW[k] = vv->v * invZ[k];
        } else {
            /* вершина за ближней плоскостью - аффинный вклад, как если бы
               z ~ 1 (перспектива по остальным вершинам уже учтена) */
            invZ[k] = 1.0f;
            uToW[k] = vv->u;
            vToW[k] = vv->v;
        }
    }


    for (int y = y0; y < y1; ++y) {
        float py = (float)y + 0.5f;
        for (int x = x0; x < x1; ++x) {
            float px = (float)x + 0.5f;

            // barycentric
            float w0 = ((bx - px) * (cy - py) - (by - py) * (cx - px)) * inv;
            float w1 = ((cx - px) * (ay - py) - (cy - py) * (ax - px)) * inv;
            float w2 = 1.0f - w0 - w1;
            if (w0 < 0.0f || w1 < 0.0f || w2 < 0.0f) continue;

            // interpolate shade
            int dr, dg, db;
            {
                int r = (int)(((v0->diff >> 16) * w0 + (v1->diff >> 16) * w1 + (v2->diff >> 16) * w2));
                int g = (int)(((v0->diff >> 8) * w0 + (v1->diff >> 8) * w1 + (v2->diff >> 8) * w2));
                int b = (int)(((v0->diff & 0xFF) * w0 + (v1->diff & 0xFF) * w1 + (v2->diff & 0xFF) * w2));
                DWORD interp = ((DWORD)r & 0xFF) | ((DWORD)((g & 0xFF) << 8)) | ((DWORD)((b & 0xFF) << 16));
                DiffuseScale(interp, &dr, &dg, &db);
            }

            DWORD clr;
            if (pix && tw > 0 && th > 0) {
                float wInv = w0 * invZ[0] + w1 * invZ[1] + w2 * invZ[2];
                if (wInv < 1e-6f) continue;
                float u = (w0 * uToW[0] + w1 * uToW[1] + w2 * uToW[2]) / wInv;
                float v = (w0 * vToW[0] + w1 * vToW[1] + w2 * vToW[2]) / wInv;
                /* UVs come in texel units (0..width/height), cf. retail
                   gbh_DrawQuadClipped: u = textureW - eps. */
                int tx = (int)u;
                int ty = (int)v;
                if (tx < 0) tx = 0; if (ty < 0) ty = 0;
                if (tx >= tw) tx = tw - 1;
                if (ty >= th) ty = th - 1;
                /* Style sprite/tile pages are 256 pixels wide (see GTA2 Style
                   Format 5.1 / retail D3dTextureUnknown: sourcePixelIndex +=
                   palSize - textureW with palSize = 256). */
                BYTE idx = pix[ty * 256 + tx];
                if (pal) {
                    /* Индекс палитры 0 = прозрачный (retail D3dTextureUnknown
                       не ставит alpha-маску, а pal[0] принудительно 0; редактор
                       карты: colorId 0 -> alpha 0). Без этого спрайты/проёмы
                       заливались чёрным прямоугольником. */
                    if (idx == 0) continue;
                    /* Диагностика текста/спрайтов: шрифтовые текстуры маленькие
                       (полоски ~9-64 px). Для ПЕРВЫХ пикселей печатаем, какой
                       индекс палитры реально выбирается и что из него выходит,
                       чтобы понять, почему "белый" рендерится голубым. */
                    if (tw < 64 && th < 240) {
                        static DWORD s_txDbg = 0;
                        static DWORD s_txSkip = 0;
                        /* пропускаем серошкальные шрифты (первые 80 серых строк),
                           остальное - цветные палитры (золотой текст и т.п.) */
                        if (s_txDbg < 400) {
                            DWORD raw = ((DWORD*)tex->pPaltData)[idx * 64];
                            int rb = (int)(raw & 0xFF);
                            int gg = (int)((raw >> 8) & 0xFF);
                            int rr = (int)((raw >> 16) & 0xFF);
                            ++s_txSkip;
                            if ((rb != gg || gg != rr) || s_txSkip < 80) {
                                ++s_txDbg;
                                WORD pw = pal[idx];
                                L("TxD tx=%2d ty=%2d idx=%02X palw=%04X raw=%08lX "
                                  "asBGR=(%02lX,%02lX,%02lX) rgb_in=%02lX%02lX%02lX",
                                  tx, ty, (int)idx, (unsigned)pw, (unsigned long)raw,
                                  (unsigned long)rb, (unsigned long)gg, (unsigned long)rr,
                                  (unsigned long)dr, (unsigned long)dg, (unsigned long)db);
                            }
                        }
                    }
                    clr = ShadeMul(0xFF000000u |
                                   (DWORD)((pal[idx] & 0x1F) << 3) << 16 |
                                   (DWORD)(((pal[idx] >> 5) & 0x1F) << 3) << 8 |
                                   (DWORD)((pal[idx] >> 10) & 0x1F) << 3,
                                   dr, dg, db);
                } else {
                    clr = ShadeMul(g_lastCol, dr, dg, db);
                }
            } else {
                clr = ShadeMul((DWORD)(baseColour ? (u32)baseColour : g_lastCol) | 0xFF000000u,
                               dr, dg, db);
            }
            PlotPixel(x, y, clr);
        }
    }
    ++gGlobals.mNumPolysDrawn;
}

// ==================================================================
//  Exports. Signatures are verbatim from d3ddll.h.
// ==================================================================

u32 CC gbh_InitDLL(Video* pVideoDriver)
{
    L("gbh_InitDLL(%p)", (void*)pVideoDriver);
    if (!CreateBackBuffer(SCREEN_W, SCREEN_H)) return 0;
    ClearBuffer(0xFF203040u);
    FindGameWindow();
    L("    hwnd=%p", g_hwnd);
    return 1;
}

s32 CC gbh_Init(int a1)
{
    L("gbh_Init(%d)", a1);
    return 1;
}

void CC gbh_CloseDLL()
{
    L("gbh_CloseDLL");
    DestroyBackBuffer();
}

void CC gbh_CloseScreen(Video* pVideo)
{
    L("gbh_CloseScreen(%p)", (void*)pVideo);
    DestroyBackBuffer();
}

void CC gbh_BeginLevel()      { L("gbh_BeginLevel"); }

int  CC gbh_BeginScene()
{
    if (g_bScenes < 3) L("gbh_BeginScene");
    ++g_bScenes;
    // fresh frame: the game never calls gbh_BlitBuffer, so clear here
    if (g_bits) memset(g_bits, 0, (size_t)g_w * g_h * 4);
    g_bImages = 0;
    return 1;
}

void CC gbh_EndLevel()        { L("gbh_EndLevel"); }

/* Дамп back buffer в 24-битный BMP: это ground truth того, что реально
   рисует драйвер, независимо от видимости окна. */
static void DumpBackBufferBMP(const char* path)
{
    if (!g_bits || !path) return;
    const int W = g_w, H = g_h;
    const DWORD rowBytes = (DWORD)((W * 3 + 3) & ~3);
    const DWORD imgBytes = rowBytes * (DWORD)H;
    const DWORD hdrBytes = 14 + 40;
    BYTE* f = (BYTE*)malloc(hdrBytes + imgBytes);
    if (!f) return;
    memset(f, 0, hdrBytes);
    f[0] = 'B'; f[1] = 'M';
    *(DWORD*)(f + 2)  = hdrBytes + imgBytes;
    *(DWORD*)(f + 10) = hdrBytes;
    *(DWORD*)(f + 14) = 40;
    *(DWORD*)(f + 18) = (DWORD)W;
    *(DWORD*)(f + 22) = (DWORD)H;      /* положительная высота = bottom-up */
    *(WORD *)(f + 26) = 1;
    *(WORD *)(f + 28) = 24;
    BYTE* px = f + hdrBytes;
    for (int y = 0; y < H; ++y) {
        const DWORD* src = g_bits + (DWORD)(H - 1 - y) * g_w;
        BYTE* dst = px + (DWORD)y * rowBytes;
        for (int x = 0; x < W; ++x) {
            DWORD c = src[x];
            dst[x * 3 + 0] = (BYTE)(c & 0xFF);
            dst[x * 3 + 1] = (BYTE)((c >> 8) & 0xFF);
            dst[x * 3 + 2] = (BYTE)((c >> 16) & 0xFF);
        }
    }
    HANDLE hf = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if (hf != INVALID_HANDLE_VALUE) {
        DWORD wr = 0;
        WriteFile(hf, f, hdrBytes + imgBytes, &wr, 0);
        CloseHandle(hf);
        L("  back buffer dumped to %s (%d bytes)", path, (int)(hdrBytes + imgBytes));
    }
    free(f);
}

static void LogCoverage(const char* tag);

double CC gbh_EndScene()
{
    if (g_bScenes < 3) L("gbh_EndScene");
    // prove whether anything actually landed in the back buffer
    if (g_bits && (g_bScenes < 6 || (g_bScenes % 100) == 0)) {
        DWORD n = (DWORD)((size_t)g_w * g_h);
        DWORD nz = 0; DWORD sample = 0;
        for (DWORD i = 0; i < n; i += 7) {   // sparse sample, cheap
            if (g_bits[i] & 0x00FFFFFF) { ++nz; if (!sample) sample = g_bits[i]; }
        }
        L("  [frame %d] buf=%dx%d nonzero~%lu/%lu first=%08lX blitres=%d plotpx=%lu",
          g_bScenes, g_w, g_h, nz, (n + 6) / 7, sample, g_lastBlitRet, g_nPlotPx);
    }
    /* Пространственная карта покрытия - главный инструмент по "видна только
       левая половина": показывает, КАКАЯ часть кадра заполнена. */
    if (g_bScenes == 30 || g_bScenes == 150 || g_bScenes == 400)
        LogCoverage(g_bScenes == 30 ? "f30" : (g_bScenes == 150 ? "f150" : "f400"));
    if (g_bScenes == 60 || g_bScenes == 200)
        DumpBackBufferBMP(g_bScenes == 60
            ? "C:\\Users\\Home\\AppData\\Local\\Temp\\opencode\\gta2_f060.bmp"
            : "C:\\Users\\Home\\AppData\\Local\\Temp\\opencode\\gta2_f200.bmp");
    if (g_bScenes == 330)
        DumpBackBufferBMP("C:\\Users\\Home\\AppData\\Local\\Temp\\opencode\\gta2_live.bmp");
    int ok = BlitToWindow();
    if (g_bScenes < 6) L("  [frame %d] BlitToWindow=%d", g_bScenes, ok);
    return 0.0;
}

// 16x16 карта покрытия: сколько ненулевых пикселей в каждой ячейке.
// Показывает ПРОСТРАНСТВЕННО, какая часть кадра вообще рисуется - этого
// не видно ни по счётчикам вызовов, ни по 'nonzero~'.
static void LogCoverage(const char* tag)
{
    if (!g_bits) return;
    const int G = 16;
    static const char* ramp = " .:-=+*#%@";
    char row[G + 1];
    DWORD worst = 0, best = 0;
    for (int gy = 0; gy < G; ++gy) {
        for (int gx = 0; gx < G; ++gx) {
            DWORD cnt = 0;
            int x0 = gx * g_w / G, x1 = (gx + 1) * g_w / G;
            int y0 = gy * g_h / G, y1 = (gy + 1) * g_h / G;
            for (int y = y0; y < y1; ++y) {
                const DWORD* p = g_bits + (DWORD)y * g_w;
                for (int x = x0; x < x1; ++x) if (p[x] & 0x00FFFFFFu) ++cnt;
            }
            DWORD total = (DWORD)(x1 - x0) * (DWORD)(y1 - y0);
            DWORD pc = total ? cnt * 100 / total : 0;
            if (pc > 100) pc = 100;
            row[gx] = ramp[pc * (DWORD)(strlen(ramp) - 1) / 100];
            if (cnt < worst || worst == 0xFFFFFFFFu) {}
            if (gx == 0) { worst = pc; best = pc; }
            else { if (pc < worst) worst = pc; if (pc > best) best = pc; }
        }
        row[G] = 0;
        L("cov %s |%s|", tag, row);
    }
    L("cov %s min=%lu%% max=%lu%% | quad=%lu tri=%lu tile=%lu flat=%lu plot=%lu blitimg=%lu qclip=%lu | tri=%lu rejZ=%lu degen=%lu",
      tag, worst, best, g_nDrawQuad, g_nDrawTri, g_nDrawTile, g_nFlatRect,
      g_nPlot, g_nBlitImage, g_nQuadClipped, g_nRasterTri, g_nRasterRejectZ,
      g_nRasterDegenerate);
}

int  CC gbh_BlitBuffer(int a1, int a2, int a3, int a4, int a5, int a6)
{
    ++g_bFrames;
    if (g_bFrames <= 3 || (g_bFrames % 30) == 0)
        L("gbh_BlitBuffer(%d,%d,%d,%d,%d,%d) frame=%d polys=%lu",
          a1, a2, a3, a4, a5, a6, g_bFrames, (unsigned long)gGlobals.mNumPolysDrawn);
    return BlitToWindow();
}

u32* CC gbh_GetGlobals()
{
    return (u32*)&gGlobals;
}

// ---- drawing ----
void CC gbh_DrawQuad(int quadFlags, Texture* pTexture, Vert* pVerts, int baseColour)
{
    if (!pVerts) return;
    ++g_nDrawQuad;
    if (quadFlags & 0x10000) quadFlags |= 0x20000;
    g_lastCol = (DWORD)baseColour;
    /* Первые кадры: смотрим, ГДЕ и КАКИМ цветом реально рисуются квады.
       Текст рисуется квадами, поэтому по этим координатам видно, куда он
       должен попасть и почему его не видно. */
    if (g_bScenes <= 2)
        L("  quad#%lu fl=%08X tex=%p col=%08X diff=%08lX spec=%08lX | "
          "v0=(%.1f,%.1f,%.1f u=%.2f v=%.2f) v1=(%.1f,%.1f) v2=(%.1f,%.1f) v3=(%.1f,%.1f)",
          g_nDrawQuad, (unsigned)quadFlags, (void*)pTexture, (DWORD)baseColour,
          (unsigned long)pVerts[0].diff, (unsigned long)pVerts[0].spec,
          pVerts[0].x, pVerts[0].y, pVerts[0].z, pVerts[0].u, pVerts[0].v,
          pVerts[1].x, pVerts[1].y, pVerts[2].x, pVerts[2].y,
          pVerts[3].x, pVerts[3].y);
    /* Перспективная коррекция текстуры: retail делает w=z и D3D делит на 1/w.
       Игра шлёт z в пикселях/мире - надо увидеть ЗАКОН изменения z по квадам
       земли/стен, чтобы понять, где падает 1/z. Ловим только большие квады с
       ЦЕНТРОМ в зоне обзора и ПЕРЕПАДОМ z между углами (это мир, не HUD). */
    {
        float sx = pVerts[0].x, xmi = sx, xma = sx;
        float sy = pVerts[0].y, ymi = sy, yma = sy;
        for (int i = 1; i < 4; ++i) {
            float px = pVerts[i].x, py = pVerts[i].y;
            if (px < xmi) xmi = px; if (px > xma) xma = px;
            if (py < ymi) ymi = py; if (py > yma) yma = py;
        }
        static DWORD s_quad3dDbg = 0;
        float zmax = pVerts[0].z, zmin = zmax;
        for (int i = 1; i < 4; ++i) {
            if (pVerts[i].z > zmax) zmax = pVerts[i].z;
            if (pVerts[i].z < zmin) zmin = pVerts[i].z;
        }
        if (s_quad3dDbg < 24 &&
            (xma - xmi) > 60.0f && (yma - ymi) > 40.0f &&
            (xmi + xma) * 0.5f > 60.0f && (xmi + xma) * 0.5f < 580.0f &&
            (ymi + yma) * 0.5f > 70.0f && (ymi + yma) * 0.5f < 420.0f &&
            (zmax - zmin) > 0.003f) {
            ++s_quad3dDbg;
            L("GRQ%d fl=%08X tex=%p tw=%d th=%d base=%08X | "
              "v0=(%7.1f,%7.1f z=%7.3f w=%7.3f u=%6.2f v=%6.2f) "
              "v1=(%7.1f,%7.1f z=%7.3f w=%7.3f u=%6.2f v=%6.2f) "
              "v2=(%7.1f,%7.1f z=%7.3f w=%7.3f u=%6.2f v=%6.2f) "
              "v3=(%7.1f,%7.1f z=%7.3f w=%7.3f u=%6.2f v=%6.2f)",
              s_quad3dDbg, (unsigned)quadFlags, (void*)pTexture,
              pTexture ? (int)pTexture->Width : 0,
              pTexture ? (int)pTexture->Height : 0,
              (DWORD)baseColour,
              pVerts[0].x, pVerts[0].y, pVerts[0].z, pVerts[0].w,
              pVerts[0].u, pVerts[0].v,
              pVerts[1].x, pVerts[1].y, pVerts[1].z, pVerts[1].w,
              pVerts[1].u, pVerts[1].v,
              pVerts[2].x, pVerts[2].y, pVerts[2].z, pVerts[2].w,
              pVerts[2].u, pVerts[2].v,
              pVerts[3].x, pVerts[3].y, pVerts[3].z, pVerts[3].w,
              pVerts[3].u, pVerts[3].v);
        }
    }
    /* Буква "G" в "GET READY" не видна. Ловим все глиф-квады нижней полосы
       (y=430..480) при старте уровня: x0/u/v покажут, какие буквы рисуются
       и где начинается строка. */
    {
        static DWORD s_glyphDbg = 0;
        if (s_glyphDbg < 80 && pTexture && pTexture->Width < 160) {
            float ym0 = pVerts[0].y, ym1 = ym0;
            if (pVerts[1].y < ym0) ym0 = pVerts[1].y; if (pVerts[1].y > ym1) ym1 = pVerts[1].y;
            if (pVerts[2].y < ym0) ym0 = pVerts[2].y; if (pVerts[2].y > ym1) ym1 = pVerts[2].y;
            if (pVerts[3].y < ym0) ym0 = pVerts[3].y; if (pVerts[3].y > ym1) ym1 = pVerts[3].y;
            float xm0 = pVerts[0].x, xm1 = xm0;
            if (pVerts[1].x < xm0) xm0 = pVerts[1].x; if (pVerts[1].x > xm1) xm1 = pVerts[1].x;
            if (pVerts[2].x < xm0) xm0 = pVerts[2].x; if (pVerts[2].x > xm1) xm1 = pVerts[2].x;
            if (pVerts[3].x < xm0) xm0 = pVerts[3].x; if (pVerts[3].x > xm1) xm1 = pVerts[3].x;
            if (ym0 > 425.0f && ym1 < 485.0f && xm0 > 0.0f && xm0 < 520.0f) {
                ++s_glyphDbg;
                L("GLY%d fl=%08X tw=%d th=%d base=%08X x0=%6.1f x1=%6.1f "
                  "u0=%6.2f u1=%6.2f v0=%6.2f | v0=(%7.1f,%7.1f) v1=(%7.1f,%7.1f)",
                  s_glyphDbg, (unsigned)quadFlags, (int)pTexture->Width,
                  (int)pTexture->Height, (DWORD)baseColour,
                  xm0, xm1, pVerts[0].u, pVerts[2].u, pVerts[0].v,
                  pVerts[0].x, pVerts[0].y, pVerts[1].x, pVerts[1].y);
                /* дамп пикселей первых глифов (10x14): пусто ли в 'G' */
                if (s_glyphDbg <= 8 && pTexture->Width <= 13 && pTexture->Height <= 16) {
                    BYTE* pg = pTexture->pOriginalPixelData;
                    int w = (int)pTexture->Width, h = (int)pTexture->Height;
                    for (int yy = 0; yy < h && yy < 14; ++yy)
                        L("  GLYpx y=%02d: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
                          yy,
                          pg[yy*256+0], pg[yy*256+1], pg[yy*256+2], pg[yy*256+3],
                          pg[yy*256+4], pg[yy*256+5], pg[yy*256+6], pg[yy*256+7],
                          pg[yy*256+8], pg[yy*256+9]);
                }
            }
        }
    }
    RasterTri(&pVerts[0], &pVerts[1], &pVerts[2], pTexture, baseColour);
    RasterTri(&pVerts[0], &pVerts[2], &pVerts[3], pTexture, baseColour);
}

void CC gbh_DrawTriangle(int triFlags, Texture* pTexture, Vert* pVerts, int diffuseColour)
{
    if (!pVerts) return;
    ++g_nDrawTri;
    g_lastCol = (DWORD)diffuseColour;
    RasterTri(&pVerts[0], &pVerts[1], &pVerts[2], pTexture, diffuseColour);
}

s32 CC gbh_DrawTilePart(unsigned int flags, Texture* pTexture, Vert* pData, int diffuseColour)
{
    if (!pData) return 0;
    ++g_nDrawTile;
    g_lastCol = (DWORD)diffuseColour;

    /* Поворот/отражение тайла - обязанность ДРАЙВЕРА (retail gbh_DrawTilePart,
       d3ddll.cpp:1236-1343). Игра шлёт единичные UV 0.5..63.5 и биты поворота
       во flags: 0x20=90, 0x40=180, 0x60=270, 0x8=vertical flip, 0x10=horizontal.
       Без этого все тайлы рисовались без поворота: земля выглядела "повёрнутой
       на 90", между соседними плитками был скачок рисунка. */
    {
        static DWORD s_tlDbg = 0;
        if (s_tlDbg < 24) {
            ++s_tlDbg;
            L("TL%d fl=%08X tex=%p base=%08X | v0=(%.1f,%.1f z=%.3f u=%.1f v=%.1f) "
              "v1=(%.1f,%.1f u=%.1f v=%.1f) v2=(%.1f,%.1f u=%.1f v=%.1f) v3=(%.1f,%.1f u=%.1f v=%.1f)",
              s_tlDbg, (unsigned)flags, (void*)pTexture, (DWORD)diffuseColour,
              pData[0].x, pData[0].y, pData[0].z, pData[0].u, pData[0].v,
              pData[1].x, pData[1].y, pData[1].u, pData[1].v,
              pData[2].x, pData[2].y, pData[2].u, pData[2].v,
              pData[3].x, pData[3].y, pData[3].u, pData[3].v);
        }
    }

    unsigned oldFlags = flags;
    if (!(flags & 0x4000)) {
        pData[0].u = 0.5f;   pData[0].v = 0.5f;
        pData[1].u = 63.499901f; pData[1].v = 0.5f;
        pData[2].u = 63.499901f; pData[2].v = 63.499901f;
        pData[3].u = 0.5f;   pData[3].v = 63.499901f;
    }

    struct UV { float u; float v; };
    UV uvs[4];
    for (int i = 0; i < 4; ++i) { uvs[i].u = pData[i].u; uvs[i].v = pData[i].v; }

    bool updated = false;
    switch (flags & 0x60) {
    case 0x20:
        pData[0].u = uvs[3].u; pData[0].v = uvs[3].v;
        pData[1].u = uvs[0].u; pData[1].v = uvs[0].v;
        pData[2].u = uvs[1].u; pData[2].v = uvs[1].v;
        pData[3].u = uvs[2].u; pData[3].v = uvs[2].v;
        updated = true;
        break;
    case 0x40:
        oldFlags = flags ^ 0x18;
        break;
    case 0x60:
        pData[0].u = uvs[1].u; pData[0].v = uvs[1].v;
        pData[1].u = uvs[2].u; pData[1].v = uvs[2].v;
        pData[2].u = uvs[3].u; pData[2].v = uvs[3].v;
        pData[3].u = uvs[0].u; pData[3].v = uvs[0].v;
        updated = true;
        break;
    }
    if (updated) {
        for (int i = 0; i < 4; ++i) { uvs[i].u = pData[i].u; uvs[i].v = pData[i].v; }
    }

    if (oldFlags & 8) {
        pData[0].u = uvs[1].u; pData[0].v = uvs[1].v;
        pData[1].u = uvs[0].u; pData[1].v = uvs[0].v;
        pData[2].u = uvs[3].u; pData[2].v = uvs[3].v;
        pData[3].u = uvs[2].u; pData[3].v = uvs[2].v;
        if (oldFlags & 0x10) {
            for (int i = 0; i < 4; ++i) { uvs[i].u = pData[i].u; uvs[i].v = pData[i].v; }
        }
    }
    if (oldFlags & 0x10) {
        pData[0].u = uvs[3].u; pData[0].v = uvs[3].v;
        pData[1].u = uvs[2].u; pData[1].v = uvs[2].v;
        pData[2].u = uvs[1].u; pData[2].v = uvs[1].v;
        pData[3].u = uvs[0].u; pData[3].v = uvs[0].v;
    }

    RasterTri(&pData[0], &pData[1], &pData[2], pTexture, diffuseColour);
    RasterTri(&pData[0], &pData[2], &pData[3], pTexture, diffuseColour);
    return 0;
}

void CC gbh_DrawQuadClipped(int a1, int a2, int a3, int a4, int a5)
{
    ++g_nQuadClipped;
    if (g_nQuadClipped <= 8)
        L("gbh_DrawQuadClipped(%d,%d,%d,%d,%d)", a1, a2, a3, a4, a5);
}

/* a1 = Vert* (4 вершины), a2 = цвет. Заполняет НЕТЕКСТУРИРОВАННЫЙ квад.
   Раньше здесь стоял FillRect(32,32) - то есть всегда рисовался квадрат
   32x32 в левом верхнем углу, независимо от геометрии. */
int CC gbh_DrawFlatRect(Vert* pVerts, int colour)
{
    if (!pVerts) return 0;
    ++g_nFlatRect;
    g_lastCol = (DWORD)colour;
    /* RasterTri сам разбирает текстуру: если pTexture == 0, он красит
       сплошным baseColour, используя интерполяцию diffuse по вершинам. */
    RasterTri(&pVerts[0], &pVerts[1], &pVerts[2], 0, colour);
    RasterTri(&pVerts[0], &pVerts[2], &pVerts[3], 0, colour);
    if (g_nFlatRect <= 6)
        L("gbh_DrawFlatRect verts=(%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f) col=%08X",
          pVerts[0].x, pVerts[0].y, pVerts[0].z,
          pVerts[2].x, pVerts[2].y, pVerts[2].z, (DWORD)colour);
    return 1;
}

void CC gbh_Plot(int a1, int a2, int a3, int a4)
{
    ++g_nPlot;
    g_lastCol = (DWORD)a1;
    PlotPixel(a2, a3, (DWORD)a1 | 0xFF000000u);
}

int CC gbh_PrintBitmap(int a1, int a2)
{
    L("gbh_PrintBitmap(%d,%d)", a1, a2);
    return 0;
}

// imageIndex, srcLeft, srcTop, srcRight, srcBottom, dstX, dstY
// Mirrors d3ddll.cpp:378 semantics (returns negative on failure), but blits
// from our own 32bpp image table into the GDI back buffer.
char CC gbh_BlitImage(int imageIndex, int srcLeft, int srcTop,
                      int srcRight, int srcBottom, int dstX, int dstY)
{
    static int s_nBlit = 0;
    ++g_nBlitImage;
    ImageTableEntry* pe = (imageIndex >= 0 && imageIndex < gImageTableCount)
                              ? &gImageTable[imageIndex] : 0;
    ++s_nBlit;
    if (g_bImages < 4 || (s_nBlit % 20) == 0 || s_nBlit < 12)
        L("gbh_BlitImage(img=%d src=%d,%d,%d,%d dst=%d,%d) n=%d imgW=%d imgH=%d load=%d",
          imageIndex, srcLeft, srcTop, srcRight, srcBottom, dstX, dstY,
          s_nBlit, pe ? pe->W : -1, pe ? pe->H : -1, pe ? pe->Loaded : -1);

    if (!g_bits) return -4;
    if (imageIndex < 0 || imageIndex >= gImageTableCount) return -1;

    ImageTableEntry& e = gImageTable[imageIndex];
    if (!e.Loaded || !e.pSurface) return -1;

    if (srcLeft < 0 || srcTop < 0 || srcRight < 0 || srcBottom < 0 ||
        srcLeft > e.W || srcTop > e.H || srcRight > e.W || srcBottom > e.H) {
        static DWORD s_rej = 0;
        if (s_rej < 8) { ++s_rej; L("  !! blit REJECT img=%d src=%d,%d,%d,%d > img %dx%d", imageIndex,
          srcLeft, srcTop, srcRight, srcBottom, e.W, e.H); }
        return -2;
    }

    if (dstX < 0 || dstY < 0) return -3;
    if ((dstX - srcLeft + srcRight) > g_w) return -3;
    if ((dstY - srcTop + srcBottom) > g_h) return -3;

    const int copyW = srcRight - srcLeft;
    const int copyH = srcBottom - srcTop;
    if (copyW <= 0 || copyH <= 0) return -2;

    ++g_bImages;
    for (int y = 0; y < copyH; ++y) {
        DWORD* dst = g_bits + (size_t)(dstY + y) * g_w + dstX;
        const DWORD* src = e.pSurface + (size_t)(srcTop + y) * e.W + srcLeft;
        memcpy(dst, src, (size_t)copyW * 4);
    }
    g_dirty = 1;
    g_lastBlitRet = 0;
    return 0;
}

// ---- colour ----
unsigned int CC gbh_ConvertColour(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
    DWORD c = 0xFF000000u | ((DWORD)a1 << 16) | ((DWORD)a2 << 8) | (DWORD)a3;
    g_lastCol = c;
    return c;
}

unsigned int CC gbh_Convert16BitGraphic(int a1, unsigned int a2, WORD* a3, signed int a4)
{
    static DWORD s_dbg = 0;
    if (s_dbg < 4) { ++s_dbg; L("gbh_Convert16BitGraphic(%d,%08lX,%p,%d)", a1, (unsigned long)a2, a3, a4); }
    return 0;
}

unsigned int CC gbh_RegisterPalette(int paltId, DWORD* a2)
{
    if (paltId < 0 || paltId >= 4096) return 0;
    PalData* p = &gPals[paltId];
    if (!p->mPData) p->mPData = (WORD*)malloc(256 * sizeof(WORD));
    if (!p->mPData) return 0;

    /* Retail-driver правит палитру НА МЕСТЕ: q[0]=0 и нули -> 0x10000 на
       256 записях с шагом 64. Но игра передаёт указатели, отстоящие друг от
       друга на 4 байта, и такого буфера у неё нет - запись на 64 КБ уходила
       за пределы чужой памяти и роняла игру (rep movs, d3ddll+0x4B0E).
       Оставляем только безопасную правку нулевой записи, чтение - как в retail. */
    if (a2) a2[0] = 0;

    p->mPOriginalData = a2;      /* как в retail: исходный буфер игры */
    p->mbLoaded = 1;
    ExpandPaletteStrided(p, a2);
    return (unsigned int)a2;
}

void CC gbh_FreePalette(int a1)
{
    L("gbh_FreePalette(%d)", a1);
    if (a1 >= 0 && a1 < 4096) gPals[a1].mbLoaded = 0;
}

char CC gbh_AssignPalette(Texture* pTexture, int palId)
{
    L("gbh_AssignPalette(%p,%d)", pTexture, palId);
    if (!pTexture) return 0;
    if (palId >= 0 && palId < 4096) {
        pTexture->pPaltData = (WORD*)gPals[palId].mPOriginalData;
        pTexture->PalIsValid = 1;
    }
    return 1;
}

// ---- textures ----
Texture* CC gbh_RegisterTexture(__int16 width, __int16 height, BYTE* pData, int a4, char a5)
{
    int w = width, h = height;
    L("gbh_RegisterTexture(%d,%d,%p,%d,%d)", w, h, pData, a4, (int)a5);
    if (w <= 0 || h <= 0) return 0;

    Texture* t = (Texture*)calloc(1, sizeof(Texture));
    if (!t) return 0;
    t->Width  = (unsigned short)w;
    t->Height = (unsigned short)h;
    t->Flags  = 0x40;
    if (pData) {
        /* Sprite/tile pixels live in the game's 256-wide style pages; keep the
           pointer (like retail) instead of copying w*h bytes. */
        t->pOriginalPixelData = pData;
        t->field_C = 0;
    }
    if (a4 >= 0 && a4 < 4096) {
        t->pPaltData = (WORD*)gPals[a4].mPOriginalData;
        t->PalIsValid = 1;
    }
    return t;
}

Texture* CC gbh_LockTexture(Texture* pTexture)
{
    L("gbh_LockTexture(%p)", pTexture);
    if (pTexture) pTexture->pLockedPixels = pTexture->pOriginalPixelData;
    return pTexture;
}

Texture* CC gbh_UnlockTexture(Texture* pTexture)
{
    L("gbh_UnlockTexture(%p)", pTexture);
    if (pTexture) pTexture->pLockedPixels = 0;
    return pTexture;
}

void CC gbh_FreeTexture(Texture* pTexture)
{
    L("gbh_FreeTexture(%p)", pTexture);
    if (!pTexture) return;
    if (pTexture->field_C == 1 && pTexture->pOriginalPixelData) free(pTexture->pOriginalPixelData);
    free(pTexture);
}

// ---- lights / camera / window ----
void CC gbh_ResetLights()
{
    static DWORD s_dbg = 0;
    ++g_nResetLights;
    if (s_dbg < 2) { ++s_dbg; L("gbh_ResetLights (n=%lu)", g_nResetLights); }
}

static float g_ambient = 1.0f;
void CC gbh_SetAmbient(float a)
{
    static DWORD s_dbg = 0;
    ++g_nSetAmbient;
    g_ambient = a;
    if (s_dbg < 2) { ++s_dbg; L("gbh_SetAmbient(%f) (n=%lu)", (double)a, g_nSetAmbient); }
}

/* Освещение GTA2 считается игрой на CPU прямо в Vert.diff каждого полигона;
   драйверные света нужны только самому D3D (дистанция/fog на GPU), в нашем
   софт-растеризаторе они не использованы. Поэтому здесь только счётчики. */
int CC gbh_AddLight(Light* pLight)
{
    static DWORD s_dbg = 0;
    ++g_nAddLight;
    if (s_dbg < 2) {
        ++s_dbg;
        L("gbh_AddLight(%p,%08lX) (n=%lu)", pLight,
          pLight ? (unsigned long)pLight->Colour : 0u, g_nAddLight);
    }
    return 0;
}

int CC gbh_SetCamera(float a1, float a2, float a3, float a4)
{
    static DWORD s_dbg = 0;
    ++g_nSetCamera;
    if (s_dbg < 2) { ++s_dbg; L("gbh_SetCamera(%f,%f,%f,%f) (n=%lu)",
      (double)a1, (double)a2, (double)a3, (double)a4, g_nSetCamera); }
    return 1;
}

int CC gbh_SetColourDepth()
{
    L("gbh_SetColourDepth() -> 32");
    return 32;
}

float CC gbh_SetWindow(float left, float top, float right, float bottom)
{
    // The game asks for the real output size here (e.g. 0,0,1919,1079). The
    // back buffer has to match, otherwise every gbh_BlitImage bounds check
    // fails and the screen stays black.
    int nw = (int)(right - left) + 1;
    int nh = (int)(bottom - top) + 1;
    if (g_setWindowCalls++ < 3 || (nw != g_w || nh != g_h))
        L("gbh_SetWindow(%f,%f,%f,%f) -> resize %dx%d (was %dx%d)",
          (double)left, (double)top, (double)right, (double)bottom,
          nw, nh, g_w, g_h);

    if (nw > 0 && nh > 0 && (nw != g_w || nh != g_h) && !g_bufFromTable) {
        if (nw > 4096) nw = 4096;
        if (nh > 4096) nh = 4096;
        // release the old DC/DIB first: re-creating over a live DIB section
        // leaves a dangling g_memDC and faults on the next scene.
        DestroyBackBuffer();
        if (CreateBackBuffer(nw, nh)) {
            g_w = nw; g_h = nh;
            g_rectRight = nw - 1;
            g_rectBottom = nh - 1;
        }
        MakeWindowed(g_hwnd);
    } else if (g_bufFromTable) {
        L("gbh_SetWindow(%dx%d) ignored: buffer locked to scanline pitch %dx%d",
          nw, nh, g_w, g_h);
    }
    return 1.0f;
}

// ---- images (the game's actual draw path is gbh_BlitImage, not gbh_DrawQuad) ----
signed int CC gbh_InitImageTable(int tableSize)
{
    L("gbh_InitImageTable(%d)", tableSize);
    if (tableSize <= 0 || tableSize > 4096) return -1;
    for (int i = 0; i < gImageTableCount; ++i) {
        if (gImageTable[i].pSurface) { free(gImageTable[i].pSurface); }
    }
    free(gImageTable);
    gImageTable = (ImageTableEntry*)calloc(tableSize, sizeof(ImageTableEntry));
    if (!gImageTable) return -1;
    gImageTableCount = tableSize;
    L("    image table allocated: %d entries", tableSize);
    return 0;
}

// Original (d3ddll.cpp:2719) decodes RGB555 words that live inside the
// Image struct itself: pSrc = (BYTE*)&pToLoad->field_12 + field_0.
// The source is stored bottom-up, hence the descending y loop.
signed int CC gbh_LoadImage(Image* pToLoad)
{
    if (!gImageTable || gImageTableCount <= 0) return -1;

    DWORD freeImageIndex = 0;
    if (gImageTableCount > 0) {
        ImageTableEntry* pFreeImage = gImageTable;
        do {
            if (!pFreeImage->Loaded) break;
            ++freeImageIndex;
            ++pFreeImage;
        } while (freeImageIndex < gImageTableCount);
    }
    if (freeImageIndex >= (DWORD)gImageTableCount) return -1;

    // original validation: field_1 must be 0, field_2 == 2, field_10 == 16
    if (!pToLoad || pToLoad->field_1 || pToLoad->field_2 != 2 || pToLoad->field_10 != 16)
        return -2;

    int w = (int)pToLoad->Width;
    int h = (int)pToLoad->Height;
    L("gbh_LoadImage slot=%u W=%d H=%d (f1=%d f2=%d f10=%d off=%d)",
      (unsigned)freeImageIndex, w, h, (int)pToLoad->field_1,
      (int)pToLoad->field_2, (int)pToLoad->field_10, (int)pToLoad->field_0);
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) return -2;

    DWORD* surf = (DWORD*)malloc((size_t)w * h * 4);
    if (!surf) return -3;

    BYTE* pSrc = (BYTE*)&pToLoad->field_12;
    pSrc += pToLoad->field_0;

    int sourcePixelIndex = 0;
    for (int y = h - 1; y >= 0; --y) {          // bottom-up source -> top-down dest
        DWORD* dstRow = surf + (size_t)y * w;
        for (int x = 0; x < w; ++x) {
            WORD pixelValue = ((WORD*)pSrc)[sourcePixelIndex];
            WORD r = (pixelValue & 0x7C00) >> 10;
            WORD g = (pixelValue & 0x03E0) >> 5;
            WORD b = (pixelValue & 0x001F);
            r = (BYTE)((r << 3) | (r >> 2));    // 5 -> 8 bit
            g = (BYTE)((g << 3) | (g >> 2));
            b = (BYTE)((b << 3) | (b >> 2));
            dstRow[x] = 0xFF000000u | ((DWORD)r << 16) | ((DWORD)g << 8) | b;
            sourcePixelIndex++;
        }
    }

    gImageTable[freeImageIndex].pSurface = surf;
    gImageTable[freeImageIndex].Loaded   = 1;
    gImageTable[freeImageIndex].W        = w;
    gImageTable[freeImageIndex].H        = h;
    return (signed int)freeImageIndex;
}

int CC gbh_FreeImageTable()
{
    L("gbh_FreeImageTable");
    for (int i = 0; i < gImageTableCount; ++i) {
        if (gImageTable[i].pSurface) free(gImageTable[i].pSurface);
        gImageTable[i].pSurface = 0;
        gImageTable[i].Loaded   = 0;
    }
    return 0;
}

int CC gbh_GetUsedCache(int cacheIdx)
{
    return 0;
}

// ---- non-gbh helpers ----
void CC ConvertColourBank(s32 unknown)   { L("ConvertColourBank(%d)", unknown); }
int  CC DrawLine(int a1,int a2,int a3,int a4,int a5) { L("DrawLine"); return 0; }
void CC SetShadeTableA(int a1,int a2,int a3,int a4,int a5) { L("SetShadeTableA"); }

int* CC MakeScreenTable(int value, int elementSize, unsigned int size)
{
    // The game writes pixels DIRECTLY through this table, one scanline at a
    // time: elementSize is the pitch in bytes. elementSize 7680 == 1920*4, so
    // the game renders into a 1920-wide surface. Our back buffer must match,
    // otherwise rows wrap and you get half a picture and no text.
    static int sTable[4096];
    gScreenTableSize = size;

    int nw = elementSize / 4;
    int nh = (int)size;
    // MakeScreenTable is also used for small scratch tables (e.g. 56x28), so
    // only trust it when the pitch really looks like a display pitch.
    if (elementSize >= 640 * 4 && nw <= 4096 && nh >= 480 && nh <= 4096 &&
        (nw != g_w || nh != g_h)) {
        L("MakeScreenTable: match buffer to pitch %d x rows %d (was %dx%d)", nw, nh, g_w, g_h);
        DestroyBackBuffer();
        if (CreateBackBuffer(nw, nh)) {
            g_w = nw; g_h = nh;
            g_rectRight = nw - 1;
            g_rectBottom = nh - 1;
            g_bufFromTable = 1;
            MakeWindowed(g_hwnd);
        }
    }

    if (size == 0 || size > 4096) return sTable;
    for (unsigned int i = 0; i < size; ++i)
        sTable[i] = value + (int)i * elementSize;
    return sTable;
}

// ------------------------------------------------------------------ crash tracer
static PVOID g_veh = 0;

static void DumpContext(CONTEXT* c)
{
    L("    EAX=%08lX ECX=%08lX EDX=%08lX EBX=%08lX",
      (unsigned long)c->Eax, (unsigned long)c->Ecx,
      (unsigned long)c->Edx, (unsigned long)c->Ebx);
    L("    ESP=%08lX EBP=%08lX ESI=%08lX EDI=%08lX",
      (unsigned long)c->Esp, (unsigned long)c->Ebp,
      (unsigned long)c->Esi, (unsigned long)c->Edi);
    L("    last call return addrs:");
    DWORD* sp = (DWORD*)c->Esp;
    for (int i = 0; i < 16; ++i) {
        DWORD v = sp[i];
        if (v >= 0x00400000 && v < 0x00700000)
            L("      [esp+%02d] = %08lX   <-- in game exe", i * 4, (unsigned long)v);
    }
}

static LONG CALLBACK VehHandler(EXCEPTION_POINTERS* ep)
{
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
        EXCEPTION_RECORD* r = ep->ExceptionRecord;
        DWORD pid = GetCurrentProcessId();
        L("=== ACCESS_VIOLATION ===");
        L("    EIP       = %08lX", (unsigned long)r->ExceptionAddress);
        L("    operation = %s", r->NumberParameters > 0
            ? (r->ExceptionInformation[0] ? "WRITE" : "READ") : "?");
        if (r->NumberParameters > 1)
            L("    fault addr= %08lX", (unsigned long)r->ExceptionInformation[1]);
        DumpContext(ep->ContextRecord);

        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        if (snap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 me;
            me.dwSize = sizeof(me);
            if (Module32First(snap, &me)) {
                do {
                    DWORD base = (DWORD)me.modBaseAddr;
                    if ((DWORD)r->ExceptionAddress >= base &&
                        (DWORD)r->ExceptionAddress < base + me.modBaseSize)
                        L(">>> FAULT IN %s base=%08lX offset=%08lX",
                          me.szModule, (unsigned long)base,
                          (unsigned long)((DWORD)r->ExceptionAddress - base));
                } while (Module32Next(snap, &me));
            }
            CloseHandle(snap);
        }
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID v)
{
    if (reason == DLL_PROCESS_ATTACH) {
        L("=== gdi back-end attached ===");
        g_veh = 0;   // crash logging lives in the hook's CrashFilter, not here
    }
    return TRUE;
}
