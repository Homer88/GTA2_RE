#include <math.h>
#include "dmavideo.h"

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#define BYTEn(x, n)   (*((BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)

static HINSTANCE gHinstance;
static PtrVideoFunctions* gVideoFuncs_100FFF8;

static VideoFunctions gRealFuncs;

typedef HRESULT (WINAPI *TDirectDrawEnumerateEx)(LPVOID, LPVOID, DWORD);

#define FLAG_HARDWARE_RENDERING 0x40
#define FLAG_TRIPPLE_BUFFERING 0x10

BOOL WINAPI DirectDrawEnumerateCallBack(
    GUID FAR *lpGUID,
    LPSTR    lpDriverDescription,
    LPSTR    lpDriverName,
    LPVOID   lpContext
)
{
    Video* pVideoDriver = reinterpret_cast<Video*>(lpContext);
    pVideoDriver->NumEnums++;

    const s32 driverDescStrLen = strlen(lpDriverDescription);
    const s32 driverNameStrLen = strlen(lpDriverName);

    const u32 requiredSize = driverDescStrLen + 1 + driverNameStrLen + 1 + sizeof(Device);
    Device* pDevice = reinterpret_cast<Device*>(malloc(requiredSize));
    memset(pDevice, 0, requiredSize);

    pDevice->DriverName = reinterpret_cast<char*>(&pDevice->EndBuffer);
    pDevice->DriverDesc = reinterpret_cast<char*>(&pDevice->EndBuffer) + driverNameStrLen + 1;

    memcpy(pDevice->DriverName, lpDriverName, driverNameStrLen + 1);
    memcpy(pDevice->DriverDesc, lpDriverDescription, driverDescStrLen + 1);

    Device* pHead = pVideoDriver->DeviceInfoLast;
    if (pHead)
    {
        pHead->NextDevice = pDevice;
    }
    else
    {
        pVideoDriver->pDeviceInfoHead = pDevice;
    }
    pVideoDriver->DeviceInfoLast = pDevice;

    if (lpGUID)
    {
        pDevice->pDeviceGuid = &pDevice->Guid;
        pDevice->Guid = *lpGUID;
        pDevice->Id = pVideoDriver->NumGuids++;
    }
    else
    {
        pDevice->Id = 1;
    }

    return TRUE;
}

BOOL WINAPI DirectDrawEnumerateExCallBack(
    GUID FAR *lpGUID,
    LPSTR    lpDriverDescription,
    LPSTR    lpDriverName,
    LPVOID   lpContext,
    HMONITOR hm
)
{
    return DirectDrawEnumerateCallBack(lpGUID, lpDriverDescription, lpDriverName, lpContext);
}

Device*  __stdcall InitDisplayMode(DisplayMode* pDisplayMode, DDSURFACEDESC2* ddsurface, Video* pVideoDriver);

void (__stdcall *pInitDisplayMode)(void) = 0;

Device*  __stdcall InitDisplayMode(DisplayMode* pDisplayMode, DDSURFACEDESC2* ddsurface, Video* pVideoDriver)
{
    pDisplayMode->Width = ddsurface->dwWidth;
    pDisplayMode->Height = ddsurface->dwHeight;
    pDisplayMode->RGBbitCount = ddsurface->ddpfPixelFormat.dwRGBBitCount;
    pDisplayMode->Pitch = ddsurface->lPitch;
    pDisplayMode->NextDisplayMode = 0;

    int bitNum = 0;
    int bIs32 = 0;
    DWORD result = ddsurface->ddpfPixelFormat.dwRBitMask;

    if (result & 1)
    {
        bIs32 = bitNum == 32;
    }
    else
    {
        for (;;)
        {
            bIs32 = bitNum == 32;
            if (bitNum >= 32)
            {
                break;
            }

            result = result >> 1;
            ++bitNum;

            if (result & 1)
            {
                bIs32 = bitNum == 32;
            }
        }
    }

    if (bIs32)
    {
        pDisplayMode->field_18 = 0;
        pDisplayMode->field_1C = 0;
        pDisplayMode->field_28 = 0;
        pDisplayMode->field_2C = 0;
        pDisplayMode->field_20 = 0;
        pDisplayMode->field_24 = 0;
    }
    else
    {
        abort();
    }
    return 0;
}

HRESULT WINAPI EnumDisplayModesCallBack_1001340(
    LPDDSURFACEDESC2 lpDDSurfaceDesc,
    LPVOID           lpContext
)
{
    Video* pVideoDriver = reinterpret_cast<Video*>(lpContext);
    if (pVideoDriver->Flags & FLAG_HARDWARE_RENDERING)
    {
    }

    pVideoDriver->NumDisplayModes++;
    DisplayMode* pDisplayMode = new DisplayMode();
    memset(pDisplayMode, 0, sizeof(DisplayMode));

    if (pVideoDriver->DisplayModeArray)
    {
        pVideoDriver->DisplayModeArray->NextDisplayMode = pDisplayMode;
    }
    else
    {
        pVideoDriver->pHead = pDisplayMode;
    }

    pVideoDriver->DisplayModeArray = pDisplayMode;

    pDisplayMode->DisplayModeIdx  = pVideoDriver->DisplayModeCount_2_q;
    ++pVideoDriver->DisplayModeCount_2_q;
    pDisplayMode->field_3C = 1;
    pDisplayMode->DeviceId = pVideoDriver->ActiveDeviceId;
    InitDisplayMode(pDisplayMode, lpDDSurfaceDesc, 0);

    return DDENUMRET_OK;
}

static void FreeDDrawInstances(Video* pVideoDriver)
{
    if (pVideoDriver->IDDraw4)
    {
        pVideoDriver->IDDraw4->Release();
        pVideoDriver->IDDraw4 = 0;
    }

    if (pVideoDriver->DirectDraw7)
    {
        pVideoDriver->DirectDraw7->Release();
        pVideoDriver->DirectDraw7 = 0;
    }
}

Video* CC Vid_Init_SYS(s32 param1, u16 param2_flags)
{
    HMODULE hDirectDraw = LoadLibraryA("ddraw.dll");
    if (hDirectDraw)
    {
        FreeLibrary(hDirectDraw);
        Video* pVideoDriver = new Video();
        memset(pVideoDriver, 0, sizeof(Video));
        pVideoDriver->SelfDllHandle = gHinstance;
        pVideoDriver->initDLL = gVideoFuncs_100FFF8;
        pVideoDriver->field_0 = 1;
        pVideoDriver->field_78 = param1;
        pVideoDriver->DisplayModeCount_2_q = 1;
        pVideoDriver->NumGuids = 2;
        pVideoDriver->Flags = param2_flags & FLAG_HARDWARE_RENDERING | 0x200;

        TDirectDrawEnumerateEx pDirectDrawEnumerateEx = 0;

        if (param2_flags & 4)
        {
            pDirectDrawEnumerateEx = reinterpret_cast<TDirectDrawEnumerateEx>(GetProcAddress(hDirectDraw, "DirectDrawEnumerateEx"));
        }
        if (pDirectDrawEnumerateEx)
        {
            pVideoDriver->LastError = pDirectDrawEnumerateEx(DirectDrawEnumerateExCallBack, pVideoDriver, 7);
        }
        else
        {
            pVideoDriver->LastError = DirectDrawEnumerateA(DirectDrawEnumerateCallBack, pVideoDriver);
        }

        if (pVideoDriver->LastError)
        {
            delete pVideoDriver;
            pVideoDriver = 0;
        }

        if (param2_flags & 8 || (pVideoDriver && !pVideoDriver->pDeviceInfoHead))
        {
            return pVideoDriver;
        }
        else
        {
            Device* pDeviceInfo = pVideoDriver->pDeviceInfoHead;
            Device* pNextDevice = pVideoDriver->pDeviceInfoHead;

            for (;;)
            {
                pVideoDriver->ActiveDeviceId = pDeviceInfo->Id;

                FreeDDrawInstances(pVideoDriver);

                pVideoDriver->LastError = DirectDrawCreate(pDeviceInfo->pDeviceGuid, (LPDIRECTDRAW *)&pVideoDriver->DirectDraw7, 0);
                if (pVideoDriver->LastError)
                {
                    break;
                }

                pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(
                    IID_IDirectDraw4, (LPVOID *)&pVideoDriver->IDDraw4);

                if (pVideoDriver->LastError)
                {
                    pVideoDriver->DirectDraw7->Release();
                    pVideoDriver->DirectDraw7 = 0;
                    return 0;
                }

                memset(&pVideoDriver->DeviceCaps, 0, sizeof(DDCAPS));
                pVideoDriver->DeviceCaps.dwSize = sizeof(DDCAPS);

                memset(&pVideoDriver->HelCaps, 0, sizeof(DDCAPS));
                pVideoDriver->HelCaps.dwSize = sizeof(DDCAPS);

                pVideoDriver->LastError = pVideoDriver->IDDraw4->GetCaps(
                    &pVideoDriver->DeviceCaps, &pVideoDriver->HelCaps);

                if (pVideoDriver->DeviceCaps.dwCaps2 & 0x80000)
                {
                    pNextDevice->Flags |= 1;
                }

                pNextDevice->dwVidMemTotal = pVideoDriver->DeviceCaps.dwVidMemTotal;
                if (pVideoDriver->LastError)
                {
                    FreeDDrawInstances(pVideoDriver);
                    break;
                }

                pVideoDriver->LastError = pVideoDriver->IDDraw4->EnumDisplayModes(
                    0,
                    0,
                    pVideoDriver,
                    EnumDisplayModesCallBack_1001340);

                pVideoDriver->ActiveDeviceId = 0;

                FreeDDrawInstances(pVideoDriver);

                pNextDevice = pNextDevice->NextDevice;
                pDeviceInfo = pNextDevice;

                if (!pNextDevice)
                {
                    return pVideoDriver;
                }
            }
        }

    }
    return 0;
}

s32 CC Vid_CheckMode(Video* pVideoDriver, s32 width, s32 height, s32 rgbBitCount)
{
    if (!pVideoDriver)
    {
        return 0;
    }

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
            {
                return 0;
            }
        }
        return result;
    }
    return 0;
}

DisplayMode* CC Vid_FindMode(Video* pVideoDriver, s32 modeId)
{
    if (!pVideoDriver || modeId == -2 && pVideoDriver->ActiveDeviceId > 1)
    {
        return 0;
    }

    DisplayMode* result = pVideoDriver->pHead;
    if (!result)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->FoundWidth = 0;
        pVideoDriver->FoundHeight = 0;
        return 0;
    }

    const DWORD deviceId = pVideoDriver->ActiveDeviceId;
    while (result->DeviceId != deviceId && deviceId || result->DisplayModeIdx != modeId)
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
    {
        return 0;
    }

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

    while (pMode->DeviceId != deviceId && deviceId || pMode->RGBbitCount != rgbBitCountFilter)
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
    {
        return 0;
    }

    DisplayMode* pMode = pVideoDriver->pCurrentEnum;
    if (!pMode)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->pCurrentEnum = 0;
        return 0;
    }

    const DWORD deviceId = pVideoDriver->ActiveDeviceId;
    while (pMode->DeviceId != deviceId && deviceId
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

static DWORD gCoopResult_dword_100FFE4;

void CC Vid_CloseScreen(Video* pVideo)
{
    if (pVideo)
    {
        if (pVideo->FullScreen)
        {
            if (pVideo->DirectDraw7)
            {
                if (pVideo->SurfacePrimary)
                {
                    pVideo->DirectDraw7->RestoreDisplayMode();
                    gCoopResult_dword_100FFE4 = pVideo->DirectDraw7->SetCooperativeLevel(pVideo->hwnd, DDSCL_NORMAL);
                    pVideo->SurfacePrimary->Release();
                    if (pVideo->FullScreen == -2)
                    {
                        pVideo->Surface->Release();
                    }
                    pVideo->SurfacePrimary = 0;
                    pVideo->Surface = 0;
                    pVideo->FullScreen = 0;
                }
            }
        }
    }
}

s32 CC Vid_SetDevice(Video* pVideoDriver, s32 deviceId)
{
    const DWORD currentDeviceId = pVideoDriver->ActiveDeviceId;
    if (currentDeviceId != deviceId)
    {
        if (currentDeviceId)
        {
            if (pVideoDriver)
            {
                if (pVideoDriver->FullScreen)
                {
                    IDirectDraw7* pDDraw = pVideoDriver->DirectDraw7;
                    if (pDDraw)
                    {
                        if (pVideoDriver->SurfacePrimary)
                        {
                            pDDraw->RestoreDisplayMode();
                            gCoopResult_dword_100FFE4 = pVideoDriver->DirectDraw7->SetCooperativeLevel(
                                pVideoDriver->hwnd, DDSCL_NORMAL);
                            pVideoDriver->SurfacePrimary->Release();
                            if (pVideoDriver->FullScreen == -2)
                            {
                                pVideoDriver->Surface->Release();
                            }
                            pVideoDriver->SurfacePrimary = 0;
                            pVideoDriver->Surface = 0;
                            pVideoDriver->FullScreen = 0;
                        }
                    }
                }
            }

            FreeDDrawInstances(pVideoDriver);

            pVideoDriver->ActiveDeviceId = 0;
        }
        if (deviceId)
        {
            Device* pDevice = pVideoDriver->pDeviceInfoHead;
            if (pVideoDriver && pDevice != 0)
            {
                while (pDevice->Id != deviceId)
                {
                    pDevice = pDevice->NextDevice;
                    if (!pDevice)
                    {
                        break;
                    }
                }
            }
            else
            {
                pDevice = 0;
            }

            FreeDDrawInstances(pVideoDriver);

            pVideoDriver->LastError = DirectDrawCreate(pDevice->pDeviceGuid,
                (LPDIRECTDRAW *)&pVideoDriver->DirectDraw7, 0);
            if (pVideoDriver->LastError)
            {
                return 1;
            }

            pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(
                IID_IDirectDraw4, (LPVOID*)&pVideoDriver->IDDraw4);

            if (pVideoDriver->LastError)
            {
                pVideoDriver->DirectDraw7->Release();
                pVideoDriver->DirectDraw7 = 0;
                return 1;
            }
            pVideoDriver->ActiveDeviceId = deviceId;
        }
    }
    return 0;
}

static s32 SetDisplayModeFromSurface(Video* pVideoDriver,  DisplayMode* pDisplayMode_1, DWORD modeId)
{
    DDSCAPS2 caps = {};
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    if (pVideoDriver->SurfacePrimary->GetAttachedSurface(&caps, &pVideoDriver->Surface))
    {
        return 1;
    }

    DDSURFACEDESC2 ddsurface = {};
    ddsurface.dwSize = sizeof(LPDDSURFACEDESC2);
    pVideoDriver->Surface->GetSurfaceDesc(&ddsurface);

    DisplayMode pDisplayMode = {};
    InitDisplayMode(&pDisplayMode, &ddsurface, pVideoDriver);

    pVideoDriver->field_38 = pDisplayMode_1->RGBbitCount;
    pVideoDriver->FullScreen = modeId;
    pVideoDriver->RectRight = pDisplayMode_1->Width;
    pVideoDriver->field_58 = pDisplayMode.field_18;

    pVideoDriver->RectBottom  = pDisplayMode_1-> Height;
    pVideoDriver->field_5C = pDisplayMode.field_1C;

    pVideoDriver->Red = pDisplayMode.field_24;
    pVideoDriver->Green = pDisplayMode.field_20;
    pVideoDriver->Blue = pDisplayMode.field_28;

    pVideoDriver->field_70 = pDisplayMode.field_30;
    pVideoDriver->field_6C = pDisplayMode.field_2C;
    pVideoDriver->field_74 = pDisplayMode.field_34;
    return 0;
}

s32 CC Vid_SetMode(Video* pVideoDriver, HWND hWnd, s32 modeId)
{
    if (!pVideoDriver)
    {
        return 1;
    }

    const int bNotFullScreen = modeId != -2;
    UpdateWindow(hWnd);
    pVideoDriver->hwnd = hWnd;

    if (pVideoDriver->FullScreen)
    {
        if (pVideoDriver->DirectDraw7)
        {
            if (pVideoDriver->SurfacePrimary)
            {
                pVideoDriver->DirectDraw7->RestoreDisplayMode();
                gCoopResult_dword_100FFE4 = pVideoDriver->DirectDraw7->SetCooperativeLevel(pVideoDriver->hwnd, DDSCL_NORMAL);
                pVideoDriver->SurfacePrimary->Release();
                if (pVideoDriver->FullScreen == -2)
                {
                    pVideoDriver->Surface->Release();
                }
                pVideoDriver->SurfacePrimary = 0;
                pVideoDriver->Surface = 0;
                pVideoDriver->FullScreen = 0;
            }
        }
    }

    const DWORD activeDeviceId = pVideoDriver->ActiveDeviceId;
    pVideoDriver->ActiveModeQ  = bNotFullScreen;
    if (bNotFullScreen != 1)
    {
        if (!activeDeviceId)
        {
            Device* pDevice = pVideoDriver->pDeviceInfoHead;
            if (pDevice)
            {
                while (pDevice->Id != 1)
                {
                    pDevice = pDevice->NextDevice;
                    if (!pDevice)
                    {
                        pDevice = 0;
                        break;
                    }
                }
            }

            FreeDDrawInstances(pVideoDriver);

            pVideoDriver->LastError = DirectDrawCreate(pDevice->pDeviceGuid, (LPDIRECTDRAW *)&pVideoDriver->DirectDraw7, 0);
            if (pVideoDriver->LastError)
            {
                return 1;
            }

            pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(IID_IDirectDraw4, (LPVOID*)&pVideoDriver->IDDraw4);
            if (pVideoDriver->LastError)
            {
                pVideoDriver->DirectDraw7->Release();
                pVideoDriver->DirectDraw7 = 0;
                return 1;
            }
            pVideoDriver->ActiveDeviceId = 1;
        }

        if (pVideoDriver->DirectDraw7->SetCooperativeLevel(hWnd, DDSCL_NORMAL))
        {
            return 1;
        }

        memset(&pVideoDriver->DDSurfaceDesc7, 0, sizeof(pVideoDriver->DDSurfaceDesc7));
        pVideoDriver->DDSurfaceDesc7.dwSize = sizeof(DDSURFACEDESC2);
        pVideoDriver->DDSurfaceDesc7.dwFlags = 1;
        pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps = 512;

        if (pVideoDriver->IDDraw4->CreateSurface(&pVideoDriver->DDSurfaceDesc7, &pVideoDriver->SurfacePrimary, 0))
        {
            return 1;
        }

        if (pVideoDriver->IDDraw4->CreateClipper(0, &pVideoDriver->Clipper, 0))
        {
            return 1;
        }

        if (pVideoDriver->Clipper->SetHWnd(0, hWnd))
        {
            return 1;
        }

        if (pVideoDriver->SurfacePrimary->SetClipper(pVideoDriver->Clipper))
        {
            return 1;
        }

        RECT Rect = {};
        GetClientRect(hWnd, &Rect);
        const LONG rectTop = Rect.top;
        memset(&pVideoDriver->DDSurfaceDesc7, 0, sizeof(DDSURFACEDESC2));
        const LONG rectBottom_1 = Rect.bottom;
        pVideoDriver->DDSurfaceDesc7.dwWidth = Rect.right - Rect.left;
        pVideoDriver->DDSurfaceDesc7.dwSize = sizeof(DDSURFACEDESC2);
        pVideoDriver->DDSurfaceDesc7.dwFlags = 7;
        pVideoDriver->DDSurfaceDesc7.dwHeight = rectBottom_1 - rectTop;

        if (pVideoDriver->Flags & 0x80)
        {
            pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps = 0x4000;
            pVideoDriver->Flags |= 0x20000000;
        }
        else
        {
            pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps = 2048;
            pVideoDriver->Flags &= 0xDFFFFFFF;
        }

        if (pVideoDriver->Flags & FLAG_HARDWARE_RENDERING)
        {
            pVideoDriver->Flags |= 0x20000000;

            DWORD byte1Flags = pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps;
            BYTE1(byte1Flags) = BYTE1(byte1Flags) & 0xF7 | 0x60;

            pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps = byte1Flags;
        }

        if (!pVideoDriver->IDDraw4->CreateSurface(&pVideoDriver->DDSurfaceDesc7, &pVideoDriver->Surface, 0))
        {
            DDSURFACEDESC2 ddsurface = {};
            ddsurface.dwSize = sizeof(DDSURFACEDESC2);
            pVideoDriver->Surface->GetSurfaceDesc(&ddsurface);

            DisplayMode displayMode = {};
            displayMode.DisplayModeIdx = -2;
            displayMode.field_3C = 1;

            InitDisplayMode(&displayMode, &ddsurface, pVideoDriver);

            pVideoDriver->FullScreen = modeId;
            pVideoDriver->RectRight = Rect.right - Rect.left;
            pVideoDriver->RectBottom = Rect.bottom - Rect.top;
            pVideoDriver->field_58 = displayMode.field_18;
            pVideoDriver->field_5C = displayMode.field_1C;
            pVideoDriver->Green = displayMode.field_20;
            pVideoDriver->Red = displayMode.field_24;
            pVideoDriver->Blue = displayMode.field_28;
            pVideoDriver->field_6C = displayMode.field_2C;
            pVideoDriver->field_70 = displayMode.field_30;
            pVideoDriver->field_74 = displayMode.field_34;
            pVideoDriver->field_38 = displayMode.RGBbitCount;
            return 0;
        }
        return 1;
    }

    if (activeDeviceId)
    {
        if (pVideoDriver->FullScreen)
        {
            if (pVideoDriver->DirectDraw7)
            {
                if (pVideoDriver->SurfacePrimary)
                {
                    pVideoDriver->DirectDraw7->RestoreDisplayMode();
                    gCoopResult_dword_100FFE4 = pVideoDriver->DirectDraw7->SetCooperativeLevel(pVideoDriver->hwnd, DDSCL_NORMAL);
                    pVideoDriver->SurfacePrimary->Release();
                    if (pVideoDriver->FullScreen == -2)
                    {
                        pVideoDriver->Surface->Release();
                    }
                    pVideoDriver->SurfacePrimary = 0;
                    pVideoDriver->Surface = 0;
                    pVideoDriver->FullScreen = 0;
                }
            }
        }

        FreeDDrawInstances(pVideoDriver);

        pVideoDriver->ActiveDeviceId = 0;
    }
    if (modeId == -2 && pVideoDriver->ActiveDeviceId > 1)
    {
        return 1;
    }

    DisplayMode* pDisplayMode_1 = pVideoDriver->pHead;
    if (!pDisplayMode_1)
    {
        pVideoDriver->FoundRGBbitCount = 0;
        pVideoDriver->FoundWidth  = 0;
        pVideoDriver->FoundHeight = 0;
        return 1;
    }

    while (pDisplayMode_1->DeviceId  != pVideoDriver->ActiveDeviceId && pVideoDriver->ActiveDeviceId
        || pDisplayMode_1->DisplayModeIdx != modeId)
    {
        pDisplayMode_1 = pDisplayMode_1->NextDisplayMode;
        if (!pDisplayMode_1)
        {
            pVideoDriver->FoundRGBbitCount = 0;
            pVideoDriver->FoundWidth = 0;
            pVideoDriver->FoundHeight = 0;
            return 1;
        }
    }

    pVideoDriver->FoundRGBbitCount = pDisplayMode_1->RGBbitCount;
    pVideoDriver->FoundWidth = pDisplayMode_1->Width;
    pVideoDriver->FoundHeight = pDisplayMode_1->Height;

    const DWORD deviceId = pDisplayMode_1->DeviceId;
    if (pVideoDriver->ActiveDeviceId != deviceId)
    {
        if (pVideoDriver->ActiveDeviceId)
        {
            if (pVideoDriver->FullScreen)
            {
                if (pVideoDriver->DirectDraw7)
                {
                    if (pVideoDriver->SurfacePrimary)
                    {
                        pVideoDriver->DirectDraw7->RestoreDisplayMode();
                        gCoopResult_dword_100FFE4 = pVideoDriver->DirectDraw7->SetCooperativeLevel(pVideoDriver->hwnd, DDSCL_NORMAL);
                        pVideoDriver->SurfacePrimary->Release();
                        if (pVideoDriver->FullScreen == -2)
                        {
                            pVideoDriver->Surface->Release();
                        }
                        pVideoDriver->SurfacePrimary = 0;
                        pVideoDriver->Surface = 0;
                        pVideoDriver->FullScreen = 0;
                    }
                }
            }

            FreeDDrawInstances(pVideoDriver);

            pVideoDriver->ActiveDeviceId = 0;
        }
        if (deviceId)
        {
            Device* pDevice_1 = pVideoDriver->pDeviceInfoHead;
            if (pDevice_1)
            {
                while (pDevice_1->Id != deviceId)
                {
                    pDevice_1 = pDevice_1->NextDevice;
                    if (!pDevice_1)
                    {
                        break;
                    }
                }
            }

            FreeDDrawInstances(pVideoDriver);

            pVideoDriver->LastError = DirectDrawCreate(pDevice_1->pDeviceGuid,
                (LPDIRECTDRAW *)&pVideoDriver->DirectDraw7, 0);

            if (pVideoDriver->LastError)
            {
                return 1;
            }

            pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(IID_IDirectDraw4, (LPVOID *)&pVideoDriver->IDDraw4);

            if (pVideoDriver->LastError)
            {
                pVideoDriver->DirectDraw7->Release();
                pVideoDriver->DirectDraw7 = 0;
                return 1;
            }

            pVideoDriver->ActiveDeviceId = deviceId;
        }
    }

    if (pVideoDriver->DirectDraw7->SetCooperativeLevel(hWnd, DDSCL_ALLOWMODEX | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))
    {
        return 1;
    }

    pVideoDriver->Flags |= 0xA0000000;
    memset(&pVideoDriver->DDSurfaceDesc7, 0, sizeof(DDSURFACEDESC2));
    pVideoDriver->DDSurfaceDesc7.dwSize = 124;
    pVideoDriver->DDSurfaceDesc7.dwFlags = 33;
    pVideoDriver->DDSurfaceDesc7.dwBackBufferCount = 2;
    pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps = 16920;

    if (pVideoDriver->Flags & FLAG_HARDWARE_RENDERING)
    {
        pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps = 25112;
    }

    if (pVideoDriver->Flags & FLAG_TRIPPLE_BUFFERING)
    {
        if (!pVideoDriver->IDDraw4->CreateSurface(&pVideoDriver->DDSurfaceDesc7, &pVideoDriver->SurfacePrimary, 0))
        {
            return SetDisplayModeFromSurface(pVideoDriver, pDisplayMode_1, modeId);
        }
    }

    pVideoDriver->DDSurfaceDesc7.dwBackBufferCount = 1;

    DWORD flags = pVideoDriver->Flags & 0x3FFFFFFF;
    flags |= 0x40000000u;
    pVideoDriver->Flags = flags;

    if (pVideoDriver->Flags & 0x30)
    {
        if (!pVideoDriver->IDDraw4->CreateSurface(&pVideoDriver->DDSurfaceDesc7, &pVideoDriver->SurfacePrimary, 0))
        {
            return SetDisplayModeFromSurface(pVideoDriver, pDisplayMode_1, modeId);
        }
    }

    pVideoDriver->Flags &= 0x9FFFFFFF;
    if (pVideoDriver->Flags & 0x80)
    {
        return 1;
    }

    pVideoDriver->DDSurfaceDesc7.ddsCaps.dwCaps &= 0xFFFFBFFF;
    if (pVideoDriver->IDDraw4->CreateSurface(&pVideoDriver->DDSurfaceDesc7, &pVideoDriver->SurfacePrimary, 0))
    {
        return 1;
    }

    return SetDisplayModeFromSurface(pVideoDriver, pDisplayMode_1, modeId);
}

void CC Vid_GrabSurface(Video* pVideoDriver)
{
    if (pVideoDriver && !(pVideoDriver->Flags & 1))
    {
        if (pVideoDriver->SurfacePrimary->IsLost() == DDERR_SURFACELOST)
        {
            pVideoDriver->SurfacePrimary->Restore();
        }
        memset(&pVideoDriver->DDSurfaceDesc7, 0, sizeof(pVideoDriver->DDSurfaceDesc7));
        pVideoDriver->DDSurfaceDesc7.dwSize = sizeof(DDSURFACEDESC2);
        if (!pVideoDriver->Surface->Lock(0, &pVideoDriver->DDSurfaceDesc7, 1, 0))
        {
            pVideoDriver->Flags |= 1;
        }
    }
}

void CC Vid_ReleaseSurface(Video* pVideoDriver)
{
    if (pVideoDriver && pVideoDriver->Flags & 1)
    {
        pVideoDriver->Surface->Unlock(0);
        if (pVideoDriver->SurfacePrimary->IsLost() == DDERR_SURFACELOST)
        {
            pVideoDriver->SurfacePrimary->Restore();
        }
        pVideoDriver->Flags &= 0xFE;
    }
}

static int SurfaceRestored(Video* pVideo, IDirectDrawSurface4* pSurface)
{
    if (pSurface->IsLost() == DDERR_SURFACELOST)
    {
        pVideo->Flags |= 0x10000000u;
        if (pSurface->Restore())
        {
            return 1;
        }
    }
    else
    {
        pVideo->Flags &= 0xEFFFFFFF;
    }
    return 0;
}

void CC Vid_FlipBuffers(Video* pVideo)
{
    if (pVideo && pVideo->SurfacePrimary && pVideo->Surface)
    {
        if (SurfaceRestored(pVideo, pVideo->SurfacePrimary))
        {
            return;
        }

        if (SurfaceRestored(pVideo, pVideo->Surface))
        {
            return;
        }

        if (pVideo->ActiveModeQ == 1)
        {
            if (pVideo->Flags & 2)
            {
                pVideo->SurfacePrimary->Flip(0, DDFLIP_NOVSYNC | DDFLIP_WAIT);
            }
            else
            {
                pVideo->SurfacePrimary->Flip(0, DDFLIP_WAIT);
            }
        }
        else
        {
            RECT r = {};
            r.top = 0;
            r.left = 0;
            r.bottom = pVideo->RectBottom;
            r.right = pVideo->RectRight;

            RECT r2 = {};
            GetClientRect(pVideo->hwnd, &r2);

            ClientToScreen(pVideo->hwnd, (LPPOINT)&r2.left);
            ClientToScreen(pVideo->hwnd, (LPPOINT)&r2.right);

            pVideo->SurfacePrimary->Blt(
                &r2,
                pVideo->Surface,
                &r,
                DDBLT_WAIT,
                0);
        }
    }
}

void CC Vid_ShutDown_SYS(Video* pVideoDriver)
{
    if (pVideoDriver)
    {
        if (pVideoDriver->FullScreen)
        {
            if (pVideoDriver->DirectDraw7)
            {
                if (pVideoDriver->SurfacePrimary)
                {
                    pVideoDriver->DirectDraw7->RestoreDisplayMode();
                    gCoopResult_dword_100FFE4 = pVideoDriver->DirectDraw7->SetCooperativeLevel(pVideoDriver->hwnd, DDSCL_NORMAL);
                    pVideoDriver->SurfacePrimary->Release();
                    if (pVideoDriver->FullScreen == -2)
                    {
                        pVideoDriver->Surface->Release();
                    }
                    pVideoDriver->SurfacePrimary = 0;
                    pVideoDriver->Surface = 0;
                    pVideoDriver->FullScreen = 0;
                }
            }
        }

        FreeDDrawInstances(pVideoDriver);

        DisplayMode* pCurrent = pVideoDriver->pHead;
        if (pCurrent)
        {
            do
            {
                DisplayMode* tmp = pCurrent->NextDisplayMode;
                free(pCurrent);
                pCurrent = tmp;
            } while (pCurrent);
        }

        Device* pCurrent2 = pVideoDriver->pDeviceInfoHead;
        if (pCurrent2)
        {
            do
            {
                Device* tmp = pCurrent2->NextDevice;
                free(pCurrent2);
                pCurrent2 = tmp;
            } while (pCurrent2);
        }
        free(pVideoDriver);
    }
}

s32 CC Vid_EnableWrites(Video* pVideoDriver)
{
    if (pVideoDriver && (pVideoDriver->Flags & 1) && !(pVideoDriver->Flags & 2))
    {
        pVideoDriver->Flags |= 2;
        if (pVideoDriver->Flags & 1)
        {
            pVideoDriver->pSurfacePixels  = pVideoDriver->DDSurfaceDesc7.lpSurface;
            pVideoDriver->SurfacePixelsPitch  = pVideoDriver->DDSurfaceDesc7.lPitch;
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
    {
        return 1;
    }

    if (!(pVideoDriver->Flags & 1))
    {
        if (pVideoDriver->SurfacePrimary->IsLost() == DDERR_SURFACELOST)
        {
            pVideoDriver->SurfacePrimary->Restore();
        }

        memset(&pVideoDriver->DDSurfaceDesc7, 0, sizeof(DDSURFACEDESC2));
        pVideoDriver->DDSurfaceDesc7.dwSize = sizeof(DDSURFACEDESC2);

        if (!pVideoDriver->Surface->Lock(0, &pVideoDriver->DDSurfaceDesc7, 1, 0))
        {
            pVideoDriver->Flags |= 1;
        }
    }

    if (pVideoDriver && (pVideoDriver->Flags & 1) && !(pVideoDriver->Flags & 2))
    {
        pVideoDriver->Flags |= 2;
        if (pVideoDriver->Flags & 1)
        {
            pVideoDriver->SurfacePixelsPitch = pVideoDriver->DDSurfaceDesc7.lPitch;
            pVideoDriver->pSurfacePixels = pVideoDriver->DDSurfaceDesc7.lpSurface;
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
    {
        pVideoDriver->Surface->Unlock(0);
        if (pVideoDriver->SurfacePrimary->IsLost() == DDERR_SURFACELOST)
        {
            pVideoDriver->SurfacePrimary->Restore();
        }
        pVideoDriver->Flags &= 0xFE;
    }
    return ret;
}

s32 CC Vid_ClearScreen(Video* pVideoDriver, u8 aR, u8 aG, u8 aB, s32 aLeft, s32 aTop, s32 aRight, s32 aBottom)
{
    RECT dstRect = {};
    dstRect.left = aLeft;
    dstRect.top = aTop;
    dstRect.right = aRight;
    dstRect.bottom = aBottom;

    DDBLTFX bltFx = {};
    bltFx.dwSize = 0x64;
    bltFx.dwFillColor = 0;

    HRESULT result = S_FALSE;
    do
    {
        result = pVideoDriver->Surface->Blt(&dstRect, 0, 0, 1024, &bltFx);
        if (!result)
        {
            break;
        }
        if (result == DDERR_SURFACELOST)
        {
            result = pVideoDriver->Surface->Restore();
            LONG bottom = pVideoDriver->RectBottom;
            pVideoDriver->Flags |= 0x10000000u;
            LONG right = pVideoDriver->RectRight;
            dstRect.left = 0;
            dstRect.top = 0;
            dstRect.right = right;
            dstRect.bottom = bottom;
            if (result)
            {
                break;
            }
        }
    } while (result == DDERR_WASSTILLDRAWING);

    return result;
}

static void ApplyGamma(WORD* gammaArray, float gamma)
{
    float rAcc = 0.0f;
    float rNormalized = 1.0f / gamma;
    int i;
    for (i=0; i<256; i++)
    {
        *gammaArray = static_cast<WORD>(pow(rAcc, rNormalized) * 65535.0f);
        ++gammaArray;
        rAcc = rAcc - -0.0039215689f;
    }
}

s32 CC Vid_SetGamma(Video* pVideoDriver, f32 gR, f32 gG, f32 gB)
{
    IDirectDrawSurface4* pPrimarySurface = pVideoDriver->SurfacePrimary;
    if (!pPrimarySurface)
    {
        return 1;
    }

    IDirectDrawGammaControl* pIDirectDrawGammaControl = 0;
    pVideoDriver->LastError = pPrimarySurface->QueryInterface(IID_IDirectDrawGammaControl, (LPVOID*)&pIDirectDrawGammaControl);

    if (gCoopResult_dword_100FFE4)
    {
        return 1;
    }

    DDGAMMARAMP gammaRamp = {};
    pVideoDriver->LastError = pIDirectDrawGammaControl->GetGammaRamp(0, &gammaRamp);

    if (gCoopResult_dword_100FFE4)
    {
        return 1;
    }

    ApplyGamma(gammaRamp.red, gR);
    ApplyGamma(gammaRamp.green, gG);
    ApplyGamma(gammaRamp.blue, gB);

    pVideoDriver->LastError = pIDirectDrawGammaControl->SetGammaRamp(0, &gammaRamp);
    if (gCoopResult_dword_100FFE4)
    {
        return 1;
    }

    pIDirectDrawGammaControl->Release();

    return 0;
}

s32 CC Vid_WindowProc(Video* pVideoDriver, HWND hwnd, DWORD uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

s32 CC Vid_InitDLL(HINSTANCE hInstance, PtrVideoFunctions* a2)
{
    gHinstance = hInstance;
    gVideoFuncs_100FFF8 = a2;

    return 0;
}

static VidVersion gVersionInfo =
{
    0x3FE7AE14,
    "Reimplementation of DMA Video (Direct Draw implementation). Version 1.8.1"
};

VidVersion* CC Vid_GetVersion()
{
    return &gVersionInfo;
}
