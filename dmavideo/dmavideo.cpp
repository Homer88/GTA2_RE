#include <math.h>
#include "dmavideo.h"
///#include "logger.hpp"

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#define BYTEn(x, n)   (*((BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)

static HINSTANCE gHinstance;
static PtrVideoFunctions* gVideoFuncs_100FFF8;

static VideoFunctions gRealFuncs;

using TDirectDrawEnumerateEx = decltype(&DirectDrawEnumerateExA);

#define FLAG_HARDWARE_RENDERING 0x40
#define FLAG_TRIPPLE_BUFFERING 0x10

BOOL WINAPI DirectDrawEnumerateCallBack(
    _In_ GUID FAR *lpGUID,
    _In_ LPSTR    lpDriverDescription,
    _In_ LPSTR    lpDriverName,
    _In_ LPVOID   lpContext
)
{
    //TRACE_ENTRYEXIT;

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
    _In_ GUID FAR *lpGUID,
    _In_ LPSTR    lpDriverDescription,
    _In_ LPSTR    lpDriverName,
    _In_ LPVOID   lpContext,
    _In_ HMONITOR hm
)
{
    // Pass to other call back
    //TRACE_ENTRYEXIT;
    return DirectDrawEnumerateCallBack(lpGUID, lpDriverDescription, lpDriverName, lpContext);
}

Device*  __stdcall InitDisplayMode(DisplayMode* pDisplayMode, DDSURFACEDESC2* ddsurface, Video* pVideoDriver);

decltype(&InitDisplayMode) pInitDisplayMode = nullptr;

// TODO: This function is wrong as some stuff isn't set correctly in pDisplayMode, still seems to work however!
Device*  __stdcall InitDisplayMode(DisplayMode* pDisplayMode, DDSURFACEDESC2* ddsurface, Video* pVideoDriver)
{
  ///  TRACE_ENTRYEXIT;

    //return pInit_DisplayMode_1001010(pDisplayMode, ddsurface, pVideoDriver);
    

    pDisplayMode->Width = ddsurface->dwWidth;
    pDisplayMode->Height = ddsurface->dwHeight;
    pDisplayMode->RGBbitCount = ddsurface->ddpfPixelFormat.dwRGBBitCount;
    pDisplayMode->Pitch = ddsurface->lPitch;
    pDisplayMode->NextDisplayMode = 0;

    int bitNum = 0;
    bool bIs32 = false;
    auto result = ddsurface->ddpfPixelFormat.dwRBitMask;
    
    // Count number of bits
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
        // TODO
        abort();
    }
    return nullptr;
}

HRESULT WINAPI EnumDisplayModesCallBack_1001340(
    _In_ LPDDSURFACEDESC2 lpDDSurfaceDesc,
    _In_ LPVOID           lpContext
)
{
   /// TRACE_ENTRYEXIT;

    Video* pVideoDriver = reinterpret_cast<Video*>(lpContext);
    if (pVideoDriver->Flags & FLAG_HARDWARE_RENDERING)
    {
        // TODO: Debug/test code skipped
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
        //--gDD4Refs_dword_100FFF4;
        pVideoDriver->IDDraw4->Release();
        pVideoDriver->IDDraw4 = 0;
    }

    if (pVideoDriver->DirectDraw7)
    {
        //--gDD7Refs_dword_100FFF0;
        pVideoDriver->DirectDraw7->Release();
        pVideoDriver->DirectDraw7 = 0;
    }
}

Video* CC Vid_Init_SYS(s32 param1, u16 param2_flags)
{
   /// TRACE_ENTRYEXIT;

    //Video* ret = gRealFuncs.pVid_Init_SYS(param1, param2_flags);
    //return ret;

    HMODULE hDirectDraw = ::LoadLibraryA("ddraw.dll");
    if (hDirectDraw)
    {
        ::FreeLibrary(hDirectDraw);
        Video* pVideoDriver = new Video();
        memset(pVideoDriver, 0, sizeof(Video));
        pVideoDriver->SelfDllHandle = gHinstance;
        pVideoDriver->initDLL = gVideoFuncs_100FFF8;
        pVideoDriver->field_0 = 1;
        pVideoDriver->field_78 = param1;
        pVideoDriver->DisplayModeCount_2_q = 1;
        pVideoDriver->NumGuids = 2;
        pVideoDriver->Flags = param2_flags & FLAG_HARDWARE_RENDERING | 0x200;
        
        TDirectDrawEnumerateEx pDirectDrawEnumerateEx = nullptr;
        
        if (param2_flags & 4)
        {
            // Yes - using a freed HMODULE is correct here! Mainly because this dll linked to ddraw so its not actually unloaded
            pDirectDrawEnumerateEx = reinterpret_cast<TDirectDrawEnumerateEx>(::GetProcAddress(hDirectDraw, "DirectDrawEnumerateEx"));
        }
        if (pDirectDrawEnumerateEx)
        {
            pVideoDriver->LastError = pDirectDrawEnumerateEx(DirectDrawEnumerateExCallBack, pVideoDriver, 7); // TODO: Constant
        }
        else
        {
            pVideoDriver->LastError = DirectDrawEnumerateA(DirectDrawEnumerateCallBack, pVideoDriver);
        }

        if (pVideoDriver->LastError)
        {
            delete pVideoDriver;
            pVideoDriver = nullptr;
        }

      
        if (param2_flags & 8 || (pVideoDriver && !pVideoDriver->pDeviceInfoHead))
        {
            // TODO: Might be wrong conditional
            return pVideoDriver;
        }
        else
        {
            auto pDeviceInfo = pVideoDriver->pDeviceInfoHead;
            auto pNextDevice = pVideoDriver->pDeviceInfoHead;

            for (;;)
            {
                pVideoDriver->ActiveDeviceId = pDeviceInfo->Id;

                FreeDDrawInstances(pVideoDriver);

                // Create DDraw7 Instance
                pVideoDriver->LastError = DirectDrawCreate(pDeviceInfo->pDeviceGuid, (LPDIRECTDRAW *)&pVideoDriver->DirectDraw7, 0);
                //++gDD7Refs_dword_100FFF0;
                if (pVideoDriver->LastError)
                {
                    break;
                }

                // Query DDraw4 instance from 7
                pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(
                    IID_IDirectDraw4, (LPVOID *)&pVideoDriver->IDDraw4);
                //++gDD4Refs_dword_100FFF4;

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
                    // TODO: Check correct
                    return pVideoDriver;
                }
            }
        }

    }
    return nullptr;
}

s32 CC Vid_CheckMode(Video* pVideoDriver, s32 width, s32 height, s32 rgbBitCount)
{
    ///TRACE_ENTRYEXIT;

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
    //TRACE_ENTRYEXIT;


    Device* result = pVideoDriver->pDeviceInfoHead;
    if (pVideoDriver && result)
    {
        while (result->Id != deviceId)
        {
            result = result->NextDevice;
            if (!result)
            {
                return nullptr;
            }
        }
        return result;
    }
    return nullptr;

}

DisplayMode* CC Vid_FindMode(Video* pVideoDriver, s32 modeId)
{
    ///TRACE_ENTRYEXIT;

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
    ///TRACE_ENTRYEXIT;

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
    //TRACE_ENTRYEXIT;

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

static DWORD gCoopResult_dword_100FFE4; // TODO: Not required to be global?

void CC Vid_CloseScreen(Video* pVideo)
{
    //TRACE_ENTRYEXIT;

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
    ///TRACE_ENTRYEXIT;

    const DWORD currentDeviceId = pVideoDriver->ActiveDeviceId;
    if (currentDeviceId != deviceId)
    {
        if (currentDeviceId)
        {
            if (pVideoDriver)
            {
                if (pVideoDriver->FullScreen)
                {
                    auto pDDraw = pVideoDriver->DirectDraw7;
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
            auto pDevice = pVideoDriver->pDeviceInfoHead;
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
            //++gDD7Refs_dword_100FFF0;
            if (pVideoDriver->LastError)
            {
                return 1;
            }

            pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(
                IID_IDirectDraw4, (LPVOID*)&pVideoDriver->IDDraw4);
            //++gDD4Refs_dword_100FFF4;

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
    ///TRACE_ENTRYEXIT;

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

    pVideoDriver->Red = pDisplayMode.field_24;// RED
    pVideoDriver-> Green = pDisplayMode.field_20;
    pVideoDriver->Blue = pDisplayMode.field_28;

    pVideoDriver->field_70 = pDisplayMode.field_30;
    pVideoDriver->field_6C = pDisplayMode.field_2C;
    pVideoDriver->field_74 = pDisplayMode.field_34;
    return 0;
}

s32 CC Vid_SetMode(Video* pVideoDriver, HWND hWnd, s32 modeId)
{
   // TRACE_ENTRYEXIT;

    //return gRealFuncs.pVid_SetMode(pVideoDriver, hWnd, modeId);

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
            auto pDevice = pVideoDriver->pDeviceInfoHead;
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
            //++gDD7Refs_dword_100FFF0;
            if (pVideoDriver->LastError)
            {
                return 1;
            }

            pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(IID_IDirectDraw4, (LPVOID*)&pVideoDriver->IDDraw4);
            //++gDD4Refs_dword_100FFF4;
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
        const auto rectTop = Rect.top;
        memset(&pVideoDriver->DDSurfaceDesc7, 0, sizeof(DDSURFACEDESC2));
        const auto rectBottom_1 = Rect.bottom;
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
            // TODO: Refactor with SetDisplayModeFromSurface
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

    auto pDisplayMode_1 = pVideoDriver->pHead ;
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


    const auto deviceId = pDisplayMode_1->DeviceId;
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
            auto pDevice_1 = pVideoDriver->pDeviceInfoHead;
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

            //++gDD7Refs_dword_100FFF0;
            if (pVideoDriver->LastError)
            {
                return 1;
            }

            pVideoDriver->LastError = pVideoDriver->DirectDraw7->QueryInterface(IID_IDirectDraw4, (LPVOID *)&pVideoDriver->IDDraw4);
            //++gDD4Refs_dword_100FFF4;

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

    /*
    // HACK: Typecast to get to older SetDisplayMode, else stack will be smashed
    IDirectDraw* pOld = (IDirectDraw*)pVideoDriver->DirectDraw7;
    if (pOld->SetDisplayMode(
        pDisplayMode_1->Width, 
        pDisplayMode_1->Height, 
        pDisplayMode_1->RGBbitCount))
    {
        return 1;
    }
    */

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

    auto flags = pVideoDriver->Flags & 0x3FFFFFFF;
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
    ///TRACE_ENTRYEXIT;

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
    //TRACE_ENTRYEXIT;

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

static bool SurfaceRestored(Video* pVideo, IDirectDrawSurface4* pSurface)
{
    if (pSurface->IsLost() == DDERR_SURFACELOST)
    {
        pVideo->Flags |= 0x10000000u;
        if (pSurface->Restore())
        {
            return true;
        }
    }
    else
    {
        pVideo->Flags &= 0xEFFFFFFF;
    }
    return false;
}

void CC Vid_FlipBuffers(Video* pVideo)
{
    //TRACE_ENTRYEXIT;

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
                pVideo->SurfacePrimary->Flip(nullptr, DDFLIP_NOVSYNC | DDFLIP_WAIT);
            }
            else
            {
                pVideo->SurfacePrimary->Flip(nullptr, DDFLIP_WAIT);
            }
        }
        else
        {
            RECT r = {};
            r.top = 0;
            r.left = 0;
            r.bottom = pVideo->RectBottom;
            r.right = pVideo->RectRight;

            // Can't use GetWindowRect as it includes the window borders
            RECT r2 = {};
            GetClientRect(pVideo->hwnd, &r2);
            
            ClientToScreen(pVideo->hwnd, (LPPOINT)&r2.left);
            ClientToScreen(pVideo->hwnd, (LPPOINT)&r2.right);

            pVideo->SurfacePrimary->Blt(
                &r2,
                pVideo->Surface, // Source
                &r,                        // Source rect size
                DDBLT_WAIT,
                0); 
            
        }
    }
}

void CC Vid_ShutDown_SYS(Video* pVideoDriver)
{
    //TRACE_ENTRYEXIT;
    
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
                    if (pVideoDriver->FullScreen == -2) // -2 == windowed mode ?
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

        // Free display modes
        auto pCurrent = pVideoDriver->pHead;
        if (pCurrent)
        {
            do
            {
                auto tmp = pCurrent->NextDisplayMode;
                free(pCurrent);
                pCurrent = tmp;
            } while (pCurrent);
        }
        
        // Free devices
        auto pCurrent2 = pVideoDriver->pDeviceInfoHead;
        if (pCurrent2)
        {
            do
            {
                auto tmp = pCurrent2->NextDevice;
                free(pCurrent2);
                pCurrent2 = tmp;
            } while (pCurrent2);
        }
        free(pVideoDriver);
    }
    //return gRealFuncs.pVid_ShutDown_SYS(pVideoDriver);
}

s32 CC Vid_EnableWrites(Video* pVideoDriver)
{
   /// TRACE_ENTRYEXIT;


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
    ///TRACE_ENTRYEXIT;
    
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
    //TRACE_ENTRYEXIT;

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
    //TRACE_ENTRYEXIT;

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
   // TRACE_ENTRYEXIT;

    auto v8 = pVideoDriver->field_5C;
    auto v9 = 8 - pVideoDriver->Red;

    RECT dstRect = {};
    dstRect.left = aLeft;
    dstRect.top = aTop;
    dstRect.right = aRight;
    dstRect.bottom = aBottom;

    // TODO: This is like what happens in TextureAllocate/Init2 in D3DDll

    /*
    v16.field_0 = 0;
    v16.field_1 = 1;
    v16.field_2 = 3;
    v16.field_3 = 7;
    v16.field_4 = 15;
    v16.field_5 = 31;
    v16.field_6 = 63;
    v16.field_7 = 127;
    LOBYTE(v16.field_8) = -1;
    v10 = *(&v16.field_0 + v8);
    */
    auto v11 = pVideoDriver->field_6C;
    auto v12 = pVideoDriver->field_58;

    DDBLTFX bltFx = {};
    bltFx.dwSize = 0x64;
    bltFx.dwFillColor = 0;

    /*
    bltFx.dwFillColor =
        ((((unsigned int)aG >> v9) & *(&v16.field_0 + pVideoDriver->Red)) << pVideoDriver->Green) 
      | ((((unsigned int)aB >> (8 - v11)) & *(&v16.field_0 + v11)) << pVideoDriver->Blue) 
      | ((((unsigned int)aR >> (8 - v8)) & v10) << v12);
      */

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
            auto bottom = pVideoDriver->RectBottom;
            pVideoDriver->Flags |= 0x10000000u;
            auto right = pVideoDriver->RectRight;
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
    for (int i=0; i<256; i++)
    {
        *gammaArray = static_cast<WORD>(pow(rAcc, rNormalized) * 65535.0f);
        ++gammaArray;
        rAcc = rAcc - -0.0039215689f;
    }
}

s32 CC Vid_SetGamma(Video* pVideoDriver, f32 gR, f32 gG, f32 gB)
{
   /// TRACE_ENTRYEXIT;

    auto pPrimarySurface = pVideoDriver->SurfacePrimary;
    if (!pPrimarySurface)
    {
        return 1;
    }

    IDirectDrawGammaControl* pIDirectDrawGammaControl = nullptr;
    pVideoDriver->LastError = pPrimarySurface->QueryInterface(IID_IDirectDrawGammaControl, (LPVOID*)&pIDirectDrawGammaControl);

    if (gCoopResult_dword_100FFE4) // Original bug, should be checking pVideoDriver->LastError  ?
    {
        return 1;
    }

    DDGAMMARAMP gammaRamp = {};
    pVideoDriver->LastError = pIDirectDrawGammaControl->GetGammaRamp(0, &gammaRamp);

    if (gCoopResult_dword_100FFE4) // TODO: Ditto?
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
    // Nothing to do
    return 0;
}


s32 CC Vid_InitDLL(HINSTANCE hInstance, PtrVideoFunctions* a2)
{
    ///TRACE_ENTRYEXIT;

    //HMODULE hReal = LoadLibrary(L"C:\\Program Files (x86)\\Rockstar Games\\GTA2\\_Dmavideo.dll");

   // DWORD addr = (DWORD)hReal + 0x1010;
    //pInit_DisplayMode_1001010 = (decltype(&Init_DisplayMode_1001010))addr;


    //PopulateVideoFunctions(hReal, gRealFuncs);

    gHinstance = hInstance;
    gVideoFuncs_100FFF8 = a2;

    return 0;
    //return gRealFuncs.pVid_InitDLL(hInstance, a2);
}

static VidVersion gVersionInfo =
{
    0x3FE7AE14, // TODO: Reverse
    "Reimplementation of DMA Video (Direct Draw implementation). Version 1.8.1"
};

VidVersion* CC Vid_GetVersion()
{
   /// TRACE_ENTRYEXIT;
    return &gVersionInfo;
}
