#ifndef __DMAVIDEO_H__
#define __DMAVIDEO_H__

#include <windows.h>
#include <ddraw.h>

struct PtrVideoFunctions;

struct Video
{
    DWORD field_0;
    DWORD Flags;
    DWORD FoundWidth;
    DWORD FoundHeight;
    DWORD FoundRGBbitCount;
    DWORD DisplayModeCount_2_q;
    DWORD NumGuids;
    DWORD NumDisplayModes;
    DWORD NumEnums;
    struct DisplayMode* pHead;
    struct DisplayMode* DisplayModeArray;
    struct Device* pDeviceInfoHead;
    struct Device* DeviceInfoLast;
    DWORD ActiveDeviceId;
    DWORD field_38;
    struct DisplayMode* pCurrentEnum;
    DWORD FullScreen;
    DWORD field_44;
    DWORD RectRight;
    DWORD RectBottom;
    LPVOID pSurfacePixels;
    DWORD SurfacePixelsPitch;
    DWORD field_58;
    DWORD field_5C;
    DWORD Green;
    DWORD Red;
    DWORD Blue;
    DWORD field_6C;
    DWORD field_70;
    DWORD field_74;
    DWORD field_78;
    HINSTANCE SelfDllHandle;
    DWORD ActiveModeQ;
    PtrVideoFunctions* initDLL;
    DWORD LastError;
    IDirectDraw7* DirectDraw7;
    char buffer[144];
    IDirectDraw4* IDDraw4;
    GUID pGUID; // TODO: Check
    IDirectDrawSurface4* SurfacePrimary;
    IDirectDrawSurface4* Surface;
    DDSURFACEDESC2 DDSurfaceDesc7;
    LPDIRECTDRAWCLIPPER Clipper;
    DWORD field_1BC;
    DWORD field_1C0;
    DWORD field_1C4;
    DDCAPS DeviceCaps;
    DDCAPS HelCaps;
    HWND hwnd;
};

static_assert(sizeof(DDCAPS) == 0x17C, "Wrong sized DDCAPS");
static_assert(sizeof(DDSURFACEDESC2) == 0x7C, "Wrong sized DDSURFACEDESC2");
static_assert(sizeof(Video) == 0x4C4, "Wrong sized SVideo");

struct Device
{
    DWORD Id;
    DWORD Flags;
    char* DriverName;
    char* DriverDesc;
    Device* NextDevice;
    GUID* pDeviceGuid;
    GUID Guid;
    DWORD dwVidMemTotal;
    DWORD EndBuffer; // TODO: Actually a word and SDevice is 0x2E ?
};
static_assert(sizeof(Device) == 0x30, "Wrong sized SDevice");

struct DisplayMode
{
    DWORD DisplayModeIdx;
    DWORD DeviceId;
    DWORD Width;
    DWORD Height;
    DWORD Pitch;
    DWORD RGBbitCount;
    DWORD field_18;
    DWORD field_1C;
    DWORD field_20;
    DWORD field_24;
    DWORD field_28;
    DWORD field_2C;
    DWORD field_30;
    DWORD field_34;
    struct DisplayMode* NextDisplayMode;
    DWORD field_3C;
};
static_assert(sizeof(DisplayMode) == 0x40, "Wrong sized SDisplayMode");

struct VidVersion
{
    DWORD mVersion;
    char mVersionString[255];
};

using u16 = unsigned short int;
using s32 = signed int;
using u32 = unsigned int;
using f32 = float;
using u8 = unsigned char;

#define CC __stdcall

Video* CC Vid_Init_SYS(s32 param1, u16 param2_flags);
s32 CC Vid_CheckMode(Video* pVideoDriver, s32 width, s32 height, s32 rgbBitCount);
Device* CC Vid_FindDevice(Video* pVideoDriver, s32 deviceId);
DisplayMode* CC Vid_FindMode(Video* pVideoDriver, s32 modeId);
s32 CC Vid_FindFirstMode(Video* pVideoDriver, s32 rgbBitCountFilter);
s32 CC Vid_FindNextMode(Video* pVideoDriver);
void CC Vid_CloseScreen(Video* pVideo);
s32 CC Vid_SetDevice(Video* pVideoDriver, s32 deviceId);
s32 CC Vid_SetMode(Video* pVideoDriver, HWND hWnd, s32 modeId);
void CC Vid_GrabSurface(Video* pVideoDriver);
void CC Vid_ReleaseSurface(Video* pVideoDriver);
void CC Vid_FlipBuffers(Video* pVideo);
void CC Vid_ShutDown_SYS(Video* pVideoDriver);
s32 CC Vid_EnableWrites(Video* pVideoDriver);
s32 CC Vid_DisableWrites(Video* pVideoDriver);
s32 CC Vid_GetSurface(Video* pVideoDriver);
s32 CC Vid_FreeSurface(Video* pVideoDriver);
s32 CC Vid_ClearScreen(Video* pVideoDriver, u8 aR, u8 aG, u8 aB, s32 aLeft, s32 aTop, s32 aRight, s32 aBottom);
s32 CC Vid_SetGamma(Video* pVideoDriver, f32 a2, f32 a3, f32 a4);
s32 CC Vid_WindowProc(Video* pVideoDriver, HWND hwnd, DWORD uMsg, WPARAM wParam, LPARAM lParam);
s32 CC Vid_InitDLL(HINSTANCE hInstance, PtrVideoFunctions* a2);
VidVersion* CC Vid_GetVersion();

struct PtrVideoFunctions
{
    decltype(&Vid_GetVersion)* pVid_GetVersion;
    decltype(&Vid_Init_SYS)* pVid_Init_SYS;
    decltype(&Vid_CheckMode)* pVid_CheckMode;
    decltype(&Vid_FindMode)* pVid_FindMode;
    decltype(&Vid_FindFirstMode)* pVid_FindFirstMode;
    decltype(&Vid_FindNextMode)* pVid_FindNextMode;
    decltype(&Vid_FindDevice)* pVid_FindDevice;
    decltype(&Vid_SetDevice)* pVid_SetDevice;
    decltype(&Vid_CloseScreen)* pVid_CloseScreen;
    decltype(&Vid_SetMode)* pVid_SetMode;
    decltype(&Vid_FlipBuffers)* pVid_FlipBuffers;
    decltype(&Vid_ReleaseSurface)* pVid_ReleaseSurface;
    decltype(&Vid_GrabSurface)* pVid_GrabSurface;
    decltype(&Vid_ShutDown_SYS)* pVid_ShutDown_SYS;
    decltype(&Vid_EnableWrites)* pVid_EnableWrites;
    decltype(&Vid_DisableWrites)* pVid_DisableWrites;
    decltype(&Vid_GetSurface)* pVid_GetSurface;
    decltype(&Vid_FreeSurface)* pVid_FreeSurface;
    decltype(&Vid_ClearScreen)* pVid_ClearScreen;
    decltype(&Vid_WindowProc)* pVid_WindowProc;
    decltype(&Vid_InitDLL)* pVid_InitDLL;
    decltype(&Vid_SetGamma)* pVid_SetGamma;
    const char* mErrStr; // NOT USED - just used to check struct is never reassigned
};

struct VideoFunctions
{
    decltype(&Vid_GetVersion) pVid_GetVersion;
    decltype(&Vid_Init_SYS) pVid_Init_SYS;
    decltype(&Vid_CheckMode) pVid_CheckMode;
    decltype(&Vid_FindMode) pVid_FindMode;
    decltype(&Vid_FindFirstMode) pVid_FindFirstMode;
    decltype(&Vid_FindNextMode) pVid_FindNextMode;
    decltype(&Vid_FindDevice) pVid_FindDevice;
    decltype(&Vid_SetDevice) pVid_SetDevice;
    decltype(&Vid_CloseScreen) pVid_CloseScreen;
    decltype(&Vid_SetMode) pVid_SetMode;
    decltype(&Vid_FlipBuffers) pVid_FlipBuffers;
    decltype(&Vid_ReleaseSurface) pVid_ReleaseSurface;
    decltype(&Vid_GrabSurface) pVid_GrabSurface;
    decltype(&Vid_ShutDown_SYS) pVid_ShutDown_SYS;
    decltype(&Vid_EnableWrites) pVid_EnableWrites;
    decltype(&Vid_DisableWrites) pVid_DisableWrites;
    decltype(&Vid_GetSurface) pVid_GetSurface;
    decltype(&Vid_FreeSurface) pVid_FreeSurface;
    decltype(&Vid_ClearScreen) pVid_ClearScreen;
    decltype(&Vid_WindowProc) pVid_WindowProc;
    decltype(&Vid_InitDLL) pVid_InitDLL;
    decltype(&Vid_SetGamma) pVid_SetGamma;
};

template<class T>
inline void GetFunc(HINSTANCE hInstance, T& result, const char* name)
{
    result = reinterpret_cast<T>(GetProcAddress(hInstance, name));
}

template<class T>
inline void PopulateSVideoFunctions(HINSTANCE hDmaVideoDll, T& funcs)
{
    GetFunc(hDmaVideoDll, funcs.pVid_GetVersion, "Vid_GetVersion");
    GetFunc(hDmaVideoDll, funcs.pVid_Init_SYS, "Vid_Init_SYS");
    GetFunc(hDmaVideoDll, funcs.pVid_CheckMode, "Vid_CheckMode");
    GetFunc(hDmaVideoDll, funcs.pVid_FindMode, "Vid_FindMode");
    GetFunc(hDmaVideoDll, funcs.pVid_FindFirstMode, "Vid_FindFirstMode");
    GetFunc(hDmaVideoDll, funcs.pVid_FindNextMode, "Vid_FindNextMode");
    GetFunc(hDmaVideoDll, funcs.pVid_FindDevice, "Vid_FindDevice");
    GetFunc(hDmaVideoDll, funcs.pVid_SetDevice, "Vid_SetDevice");
    GetFunc(hDmaVideoDll, funcs.pVid_CloseScreen, "Vid_CloseScreen");
    GetFunc(hDmaVideoDll, funcs.pVid_SetMode, "Vid_SetMode");
    GetFunc(hDmaVideoDll, funcs.pVid_FlipBuffers, "Vid_FlipBuffers");
    GetFunc(hDmaVideoDll, funcs.pVid_ReleaseSurface, "Vid_ReleaseSurface");
    GetFunc(hDmaVideoDll, funcs.pVid_GrabSurface, "Vid_GrabSurface");
    GetFunc(hDmaVideoDll, funcs.pVid_ShutDown_SYS, "Vid_ShutDown_SYS");
    GetFunc(hDmaVideoDll, funcs.pVid_EnableWrites, "Vid_EnableWrites");
    GetFunc(hDmaVideoDll, funcs.pVid_DisableWrites, "Vid_DisableWrites");
    GetFunc(hDmaVideoDll, funcs.pVid_GetSurface, "Vid_GetSurface");
    GetFunc(hDmaVideoDll, funcs.pVid_FreeSurface, "Vid_FreeSurface");
    GetFunc(hDmaVideoDll, funcs.pVid_ClearScreen, "Vid_ClearScreen");
    GetFunc(hDmaVideoDll, funcs.pVid_WindowProc, "Vid_WindowProc");
    GetFunc(hDmaVideoDll, funcs.pVid_InitDLL, "Vid_InitDLL");
    GetFunc(hDmaVideoDll, funcs.pVid_SetGamma, "Vid_SetGamma");
}


#endif // !__DMAVIDEO_H__

