#include <math.h>
#include "dmaglide.h"
#include "../3dfx/3dfx.h"

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

struct ResolutionEntry {
    int width;
    int height;
    int bpp;
    GrScreenResolution_t res;
};

static const ResolutionEntry gResolutionTable[] = {
    { 320,  200, 16, GR_RESOLUTION_320x200  },
    { 320,  240, 16, GR_RESOLUTION_320x240  },
    { 400,  256, 16, GR_RESOLUTION_400x256  },
    { 512,  384, 16, GR_RESOLUTION_512x384  },
    { 640,  200, 16, GR_RESOLUTION_640x200  },
    { 640,  350, 16, GR_RESOLUTION_640x350  },
    { 640,  400, 16, GR_RESOLUTION_640x400  },
    { 640,  480, 16, GR_RESOLUTION_640x480  },
    { 800,  600, 16, GR_RESOLUTION_800x600  },
    { 960,  720, 16, GR_RESOLUTION_960x720  },
    { 856,  480, 16, GR_RESOLUTION_856x480  },
    { 512,  256, 16, GR_RESOLUTION_512x256  },
    { 1024, 768, 16, GR_RESOLUTION_1024x768 },
    { 1280,1024, 16, GR_RESOLUTION_1280x1024},
    { 1600,1200, 16, GR_RESOLUTION_1600x1200},
    { 400,  300, 16, GR_RESOLUTION_400x300  },
};

static const int gNumResolutions = sizeof(gResolutionTable) / sizeof(gResolutionTable[0]);

static HINSTANCE gHinstance;
static PtrVideoFunctions* gVideoFuncs;

static int gGlideRefCount = 0;
static int gGlideWindowOpen = 0;
static int gCurrentWidth = 0;
static int gCurrentHeight = 0;
static int gCurrentBpp = 16;
static GrScreenResolution_t gCurrentResolution = GR_RESOLUTION_NONE;
static int gSurfaceLocked = 0;
static GrLfbInfo_t gLfbInfo;

static const ResolutionEntry* FindResolution(int width, int height, int bpp)
{
    for (int i = 0; i < gNumResolutions; i++)
    {
        if (gResolutionTable[i].width == width &&
            gResolutionTable[i].height == height &&
            gResolutionTable[i].bpp == bpp)
        {
            return &gResolutionTable[i];
        }
    }
    return 0;
}

static int GrResolutionWidth(GrScreenResolution_t res)
{
    for (int i = 0; i < gNumResolutions; i++)
    {
        if (gResolutionTable[i].res == res)
            return gResolutionTable[i].width;
    }
    return 0;
}

static int GrResolutionHeight(GrScreenResolution_t res)
{
    for (int i = 0; i < gNumResolutions; i++)
    {
        if (gResolutionTable[i].res == res)
            return gResolutionTable[i].height;
    }
    return 0;
}

static GrScreenRefresh_t FindRefresh(int refreshHz)
{
    if (refreshHz >= 120) return GR_REFRESH_120Hz;
    if (refreshHz >= 100) return GR_REFRESH_100Hz;
    if (refreshHz >= 90)  return GR_REFRESH_90Hz;
    if (refreshHz >= 85)  return GR_REFRESH_85Hz;
    if (refreshHz >= 80)  return GR_REFRESH_80Hz;
    if (refreshHz >= 75)  return GR_REFRESH_75Hz;
    if (refreshHz >= 72)  return GR_REFRESH_72Hz;
    if (refreshHz >= 70)  return GR_REFRESH_70Hz;
    return GR_REFRESH_60Hz;
}

static void CloseGlideScreen(Video* pVideo)
{
    if (gGlideWindowOpen)
    {
        grSstWinClose(0);
        gGlideWindowOpen = 0;
    }
    gCurrentResolution = GR_RESOLUTION_NONE;
    gCurrentWidth = 0;
    gCurrentHeight = 0;

    if (pVideo)
    {
        if (pVideo->FullScreen)
        {
            pVideo->SurfacePrimary = 0;
            pVideo->Surface = 0;
            pVideo->FullScreen = 0;
        }
    }
}

static void FillDisplayMode32(DisplayMode* pDisplayMode)
{
    pDisplayMode->field_18 = 0;
    pDisplayMode->field_1C = 0;
    pDisplayMode->field_20 = 0;
    pDisplayMode->field_24 = 0;
    pDisplayMode->field_28 = 0;
    pDisplayMode->field_2C = 0;
    pDisplayMode->field_30 = 0;
    pDisplayMode->field_34 = 0;
}

Video* CC Vid_Init_SYS(s32 param1, u16 param2_flags)
{
    if (gGlideRefCount == 0)
    {
        grGlideInit();
    }
    gGlideRefCount++;

    Video* pVideoDriver = new Video();
    memset(pVideoDriver, 0, sizeof(Video));

    pVideoDriver->SelfDllHandle = gHinstance;
    pVideoDriver->initDLL = gVideoFuncs;
    pVideoDriver->field_0 = 1;
    pVideoDriver->field_78 = param1;
    pVideoDriver->Flags = param2_flags & 0x40 | 0x200;
    pVideoDriver->NumGuids = 1;
    pVideoDriver->DisplayModeCount_2_q = 1;
    pVideoDriver->NumDisplayModes = 0;

    Device* pDevice = reinterpret_cast<Device*>(malloc(sizeof(Device)));
    memset(pDevice, 0, sizeof(Device));
    pDevice->Id = 1;
    pDevice->Flags = 1;
    pDevice->DriverName = const_cast<char*>("Glide 3.x");
    pDevice->DriverDesc = const_cast<char*>("3dfx Glide 3.x Video Driver");
    pDevice->NextDevice = 0;
    pDevice->pDeviceGuid = 0;
    pDevice->dwVidMemTotal = 16 * 1024 * 1024;

    pVideoDriver->pDeviceInfoHead = pDevice;
    pVideoDriver->DeviceInfoLast = pDevice;
    pVideoDriver->ActiveDeviceId = 1;

    DisplayMode* pPrev = 0;
    for (int i = 0; i < gNumResolutions; i++)
    {
        DisplayMode* pMode = new DisplayMode();
        memset(pMode, 0, sizeof(DisplayMode));
        pMode->DisplayModeIdx = pVideoDriver->DisplayModeCount_2_q;
        pVideoDriver->DisplayModeCount_2_q++;
        pMode->DeviceId = 1;
        pMode->Width = gResolutionTable[i].width;
        pMode->Height = gResolutionTable[i].height;
        pMode->RGBbitCount = 16;
        pMode->Pitch = gResolutionTable[i].width * 2;
        pMode->field_3C = 1;
        FillDisplayMode32(pMode);

        if (pPrev)
            pPrev->NextDisplayMode = pMode;
        else
            pVideoDriver->pHead = pMode;

        pPrev = pMode;
        pVideoDriver->NumDisplayModes++;
    }
    pVideoDriver->DisplayModeArray = pPrev;

    return pVideoDriver;
}

s32 CC Vid_CheckMode(Video* pVideoDriver, s32 width, s32 height, s32 rgbBitCount)
{
    if (!pVideoDriver)
        return 0;

    DisplayMode* pDisplayMode = pVideoDriver->pHead;
    if (!pDisplayMode)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->FoundWidth = 0;
        pVideoDriver->FoundHeight = 0;
        return 0;
    }

    const DWORD deviceId = pVideoDriver->ActiveDeviceId;
    while (pDisplayMode->DeviceId != deviceId && deviceId
        || pDisplayMode->Width != width
        || pDisplayMode->Height != height
        || pDisplayMode->RGBbitCount != rgbBitCount)
    {
        pDisplayMode = pDisplayMode->NextDisplayMode;
        if (!pDisplayMode)
        {
            pVideoDriver->FoundRGBbitCount = 0;
            pVideoDriver->FoundWidth = 0;
            pVideoDriver->FoundHeight = 0;
            return 0;
        }
    }
    pVideoDriver->FoundRGBbitCount = pDisplayMode->RGBbitCount;
    pVideoDriver->FoundWidth = pDisplayMode->Width;
    pVideoDriver->FoundHeight = pDisplayMode->Height;
    return pDisplayMode->DisplayModeIdx;
}

Device* CC Vid_FindDevice(Video* pVideoDriver, s32 deviceId)
{
    Device* result = pVideoDriver->pDeviceInfoHead;
    if (pVideoDriver && result)
    {
        while (result->Id != deviceId)
        {
            result = result->NextDevice;
            if (!result)
                return 0;
        }
        return result;
    }
    return 0;
}

DisplayMode* CC Vid_FindMode(Video* pVideoDriver, s32 modeId)
{
    if (!pVideoDriver || (modeId == -2 && pVideoDriver->ActiveDeviceId > 1))
        return 0;

    DisplayMode* result = pVideoDriver->pHead;
    if (!result)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->FoundWidth = 0;
        pVideoDriver->FoundHeight = 0;
        return 0;
    }

    const DWORD deviceId = pVideoDriver->ActiveDeviceId;
    while ((result->DeviceId != deviceId && deviceId) || result->DisplayModeIdx != modeId)
    {
        result = result->NextDisplayMode;
        if (!result)
        {
            pVideoDriver->FoundRGBbitCount = 0;
            pVideoDriver->FoundWidth = 0;
            pVideoDriver->FoundHeight = 0;
            return 0;
        }
    }
    pVideoDriver->FoundRGBbitCount = result->RGBbitCount;
    pVideoDriver->FoundWidth = result->Width;
    pVideoDriver->FoundHeight = result->Height;
    return result;
}

s32 CC Vid_FindFirstMode(Video* pVideoDriver, s32 rgbBitCountFilter)
{
    if (!pVideoDriver)
        return 0;

    DisplayMode* pMode = pVideoDriver->pHead;
    pVideoDriver->FoundRGBbitCount = rgbBitCountFilter;
    if (!pMode)
    {
        pVideoDriver->FoundWidth = 0;
        pVideoDriver->FoundHeight = 0;
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->pCurrentEnum = 0;
        return 0;
    }
    const DWORD deviceId = pVideoDriver->ActiveDeviceId;
    while ((pMode->DeviceId != deviceId && deviceId) || pMode->RGBbitCount != rgbBitCountFilter)
    {
        pMode = pMode->NextDisplayMode;
        if (!pMode)
        {
            pVideoDriver->FoundWidth = 0;
            pVideoDriver->FoundHeight = 0;
            pVideoDriver->FoundRGBbitCount = 0;
            pVideoDriver->pCurrentEnum = 0;
            return 0;
        }
    }
    pVideoDriver->pCurrentEnum = pMode->NextDisplayMode;
    pVideoDriver->FoundWidth = pMode->Width;
    pVideoDriver->FoundHeight = pMode->Height;
    return pMode->DisplayModeIdx;
}

s32 CC Vid_FindNextMode(Video* pVideoDriver)
{
    if (!pVideoDriver)
        return 0;

    DisplayMode* pMode = pVideoDriver->pCurrentEnum;
    if (!pMode)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->pCurrentEnum = 0;
        return 0;
    }

    const DWORD deviceId = pVideoDriver->ActiveDeviceId;
    while ((pMode->DeviceId != deviceId && deviceId)
        || pMode->RGBbitCount != pVideoDriver->FoundRGBbitCount)
    {
        pMode = pMode->NextDisplayMode;
        if (!pMode)
        {
            pVideoDriver->FoundRGBbitCount = 0;
            pVideoDriver->pCurrentEnum = 0;
            return 0;
        }
    }
    pVideoDriver->pCurrentEnum = pMode->NextDisplayMode;
    pVideoDriver->FoundWidth = pMode->Width;
    pVideoDriver->FoundHeight = pMode->Height;
    return pMode->DisplayModeIdx;
}

void CC Vid_CloseScreen(Video* pVideo)
{
    if (pVideo)
    {
        if (pVideo->FullScreen)
        {
            CloseGlideScreen(pVideo);
        }
    }
}

s32 CC Vid_SetDevice(Video* pVideoDriver, s32 deviceId)
{
    (void)pVideoDriver;
    (void)deviceId;
    return 0;
}

s32 CC Vid_SetMode(Video* pVideoDriver, HWND hWnd, s32 modeId)
{
    if (!pVideoDriver)
        return 1;

    UpdateWindow(hWnd);

    if (pVideoDriver->FullScreen)
        CloseGlideScreen(pVideoDriver);

    const int bWindowed = (modeId == -2);
    const DWORD activeDeviceId = pVideoDriver->ActiveDeviceId;
    pVideoDriver->ActiveModeQ = bWindowed ? 1 : 0;

    if (bWindowed)
    {
        if (!pVideoDriver->FullScreen)
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            pVideoDriver->FullScreen = modeId;
            pVideoDriver->RectRight = rect.right - rect.left;
            pVideoDriver->RectBottom = rect.bottom - rect.top;
            pVideoDriver->field_38 = 16;
            pVideoDriver->field_58 = 0;
            pVideoDriver->field_5C = 0;
            pVideoDriver->Green = 0;
            pVideoDriver->Red = 0;
            pVideoDriver->Blue = 0;
            pVideoDriver->field_6C = 0;
            pVideoDriver->field_70 = 0;
            pVideoDriver->field_74 = 0;
        }
        return 0;
    }

    DisplayMode* pDisplayMode = pVideoDriver->pHead;
    if (!pDisplayMode)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->FoundWidth = 0;
        pVideoDriver->FoundHeight = 0;
        return 1;
    }

    while ((pDisplayMode->DeviceId != activeDeviceId && activeDeviceId)
        || pDisplayMode->DisplayModeIdx != modeId)
    {
        pDisplayMode = pDisplayMode->NextDisplayMode;
        if (!pDisplayMode)
        {
            pVideoDriver->FoundRGBbitCount = 0;
            pVideoDriver->FoundWidth = 0;
            pVideoDriver->FoundHeight = 0;
            return 1;
        }
    }

    pVideoDriver->FoundRGBbitCount = pDisplayMode->RGBbitCount;
    pVideoDriver->FoundWidth = pDisplayMode->Width;
    pVideoDriver->FoundHeight = pDisplayMode->Height;

    int width = pDisplayMode->Width;
    int height = pDisplayMode->Height;
    int bpp = pDisplayMode->RGBbitCount;

    const ResolutionEntry* entry = FindResolution(width, height, bpp);
    if (!entry)
        return 1;

    GrScreenResolution_t res = entry->res;
    GrScreenRefresh_t refresh = GR_REFRESH_60Hz;

    CloseGlideScreen(pVideoDriver);

    FxBool ok = grSstWinOpen(
        reinterpret_cast<FxU>(hWnd),
        res,
        refresh,
        GR_COLORFORMAT_ABGR,
        GR_ORIGIN_UPPER_LEFT,
        2,
        1);

    if (!ok)
        return 1;

    gCurrentResolution = res;
    gCurrentWidth = width;
    gCurrentHeight = height;
    gCurrentBpp = bpp;
    gGlideWindowOpen = 1;

    pVideoDriver->FullScreen = modeId;
    pVideoDriver->RectRight = width;
    pVideoDriver->RectBottom = height;
    pVideoDriver->field_38 = bpp;
    pVideoDriver->field_58 = 0;
    pVideoDriver->field_5C = 0;
    pVideoDriver->Green = 0;
    pVideoDriver->Red = 0;
    pVideoDriver->Blue = 0;
    pVideoDriver->field_6C = 0;
    pVideoDriver->field_70 = 0;
    pVideoDriver->field_74 = 0;

    return 0;
}

void CC Vid_GrabSurface(Video* pVideoDriver)
{
    if (!pVideoDriver || (pVideoDriver->Flags & 1))
        return;

    if (!gGlideWindowOpen)
        return;

    memset(&gLfbInfo, 0, sizeof(gLfbInfo));
    gLfbInfo.size = sizeof(gLfbInfo);

    FxBool locked = grLfbLock(
        GR_LFB_WRITE_ONLY,
        GR_BUFFER_BACKBUFFER,
        GR_LFBWRITEMODE_565,
        GR_ORIGIN_UPPER_LEFT,
        FXFALSE,
        &gLfbInfo);

    if (locked)
    {
        gSurfaceLocked = 1;
        pVideoDriver->Flags |= 1;
    }
}

void CC Vid_ReleaseSurface(Video* pVideoDriver)
{
    if (!pVideoDriver || !(pVideoDriver->Flags & 1))
        return;

    if (gSurfaceLocked)
    {
        grLfbUnlock(GR_LFB_WRITE_ONLY, GR_BUFFER_BACKBUFFER);
        gSurfaceLocked = 0;
    }
    pVideoDriver->Flags &= 0xFE;
}

void CC Vid_FlipBuffers(Video* pVideo)
{
    if (!pVideo || !gGlideWindowOpen)
        return;

    if (pVideo->ActiveModeQ == 1)
    {
        grBufferSwap(1);
    }
    else
    {
        grBufferSwap(1);
    }
}

void CC Vid_ShutDown_SYS(Video* pVideoDriver)
{
    if (!pVideoDriver)
        return;

    CloseGlideScreen(pVideoDriver);

    if (gGlideRefCount > 0)
    {
        gGlideRefCount--;
        if (gGlideRefCount == 0)
            grGlideShutdown();
    }

    DisplayMode* pCurrent = pVideoDriver->pHead;
    while (pCurrent)
    {
        DisplayMode* tmp = pCurrent->NextDisplayMode;
        free(pCurrent);
        pCurrent = tmp;
    }

    Device* pCurrent2 = pVideoDriver->pDeviceInfoHead;
    while (pCurrent2)
    {
        Device* tmp = pCurrent2->NextDevice;
        free(pCurrent2);
        pCurrent2 = tmp;
    }

    free(pVideoDriver);
}

s32 CC Vid_EnableWrites(Video* pVideoDriver)
{
    if (pVideoDriver && (pVideoDriver->Flags & 1) && !(pVideoDriver->Flags & 2))
    {
        pVideoDriver->Flags |= 2;
        if (pVideoDriver->Flags & 1 && gSurfaceLocked)
        {
            pVideoDriver->pSurfacePixels = gLfbInfo.lfbPtr;
            pVideoDriver->SurfacePixelsPitch = static_cast<DWORD>(gLfbInfo.strideInBytes);
        }
        else
        {
            pVideoDriver->pSurfacePixels = 0;
            pVideoDriver->SurfacePixelsPitch = 0;
        }
        return 0;
    }
    return 1;
}

s32 CC Vid_DisableWrites(Video* pVideoDriver)
{
    if (pVideoDriver && (pVideoDriver->Flags & 1) && pVideoDriver->Flags & 2)
    {
        pVideoDriver->pSurfacePixels = 0;
        pVideoDriver->Flags &= 0xFD;
        return 0;
    }
    return 1;
}

s32 CC Vid_GetSurface(Video* pVideoDriver)
{
    if (!pVideoDriver)
        return 1;

    if (!(pVideoDriver->Flags & 1))
        Vid_GrabSurface(pVideoDriver);

    if (pVideoDriver && (pVideoDriver->Flags & 1) && !(pVideoDriver->Flags & 2))
    {
        pVideoDriver->Flags |= 2;
        if (pVideoDriver->Flags & 1 && gSurfaceLocked)
        {
            pVideoDriver->SurfacePixelsPitch = static_cast<DWORD>(gLfbInfo.strideInBytes);
            pVideoDriver->pSurfacePixels = gLfbInfo.lfbPtr;
        }
        else
        {
            pVideoDriver->pSurfacePixels = 0;
            pVideoDriver->SurfacePixelsPitch = 0;
        }
        return 0;
    }
    return 1;
}

s32 CC Vid_FreeSurface(Video* pVideoDriver)
{
    s32 ret = 0;
    if (pVideoDriver && (pVideoDriver->Flags & 1) && pVideoDriver->Flags & 2)
    {
        pVideoDriver->pSurfacePixels = 0;
        pVideoDriver->Flags &= 0xFD;
        ret = 0;
    }
    else
    {
        ret = 1;
    }

    if (pVideoDriver && pVideoDriver->Flags & 1)
        Vid_ReleaseSurface(pVideoDriver);

    return ret;
}

static void FillRectViaLfb(int left, int top, int right, int bottom, int width, int height, int pitch, void* pixels, unsigned short color)
{
    int fillW = right - left;
    int fillH = bottom - top;
    if (fillW <= 0 || fillH <= 0)
        return;

    if (left < 0) left = 0;
    if (top < 0) top = 0;
    if (right > width) right = width;
    if (bottom > height) bottom = height;

    for (int y = top; y < bottom; y++)
    {
        unsigned short* row = reinterpret_cast<unsigned short*>(
            reinterpret_cast<unsigned char*>(pixels) + y * pitch);
        for (int x = left; x < right; x++)
            row[x] = color;
    }
}

s32 CC Vid_ClearScreen(Video* pVideoDriver, u8 aR, u8 aG, u8 aB, s32 aLeft, s32 aTop, s32 aRight, s32 aBottom)
{
    if (!gGlideWindowOpen)
        return 0;

    if (aLeft <= 0 && aTop <= 0 && aRight >= gCurrentWidth && aBottom >= gCurrentHeight)
    {
        grBufferClear(0, 0, GR_ZDEPTHVALUE_NEAREST);
        return 0;
    }

    GrLfbInfo_t info;
    memset(&info, 0, sizeof(info));
    info.size = sizeof(info);

    FxBool locked = grLfbLock(
        GR_LFB_WRITE_ONLY,
        GR_BUFFER_BACKBUFFER,
        GR_LFBWRITEMODE_565,
        GR_ORIGIN_UPPER_LEFT,
        FXFALSE,
        &info);

    if (locked)
    {
        unsigned short color = static_cast<unsigned short>(
            ((aR >> 3) << 11) | ((aG >> 2) << 5) | (aB >> 3));

        FillRectViaLfb(aLeft, aTop, aRight, aBottom,
            gCurrentWidth, gCurrentHeight,
            static_cast<int>(info.strideInBytes),
            info.lfbPtr, color);

        grLfbUnlock(GR_LFB_WRITE_ONLY, GR_BUFFER_BACKBUFFER);
    }

    return 0;
}

s32 CC Vid_SetGamma(Video* pVideoDriver, f32 gR, f32 gG, f32 gB)
{
    (void)pVideoDriver;
    (void)gR;
    (void)gG;
    (void)gB;
    return 0;
}

s32 CC Vid_WindowProc(Video* pVideoDriver, HWND hwnd, DWORD uMsg, WPARAM wParam, LPARAM lParam)
{
    (void)pVideoDriver;
    (void)hwnd;
    (void)uMsg;
    (void)wParam;
    (void)lParam;
    return 0;
}

s32 CC Vid_InitDLL(HINSTANCE hInstance, PtrVideoFunctions* a2)
{
    gHinstance = hInstance;
    gVideoFuncs = a2;
    return 0;
}

static VidVersion gVersionInfo =
{
    0x3FE7AE14,
    "Reimplementation of DMA Video (Glide 3.x implementation). Version 1.0.0"
};

VidVersion* CC Vid_GetVersion()
{
    return &gVersionInfo;
}
