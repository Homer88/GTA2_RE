#ifndef __DMAVIDEO_H__
#define __DMAVIDEO_H__

#define STATIC_ASSERT(cond, msg) \
    typedef char CONCAT(static_assert_, __LINE__)[(cond) ? 1 : -1]
#define CONCAT_(a, b) a ## b
#define CONCAT(a, b) CONCAT_(a, b)

#include <windows.h>
#include <ddraw.h>

struct PtrVideoFunctions;

typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef unsigned char u8;

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
    GUID pGUID;
    IDirectDrawSurface4* SurfacePrimary;
    IDirectDrawSurface4* Surface;
    DDSURFACEDESC2 DDSurfaceDesc7;
    LPDIRECTDRAWCLIPPER Clipper;
    DWORD field_1BC;
    DWORD field_1C0;
    DWORD field_1C4;
    DWORD field_1C8;
    DDCAPS DeviceCaps;
    DDCAPS HelCaps;
    HWND hwnd;
};

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
    DWORD EndBuffer;
};
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

struct VidVersion
{
    DWORD mVersion;
    char mVersionString[255];
};

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
    VidVersion* (CC **pVid_GetVersion)();
    Video* (CC **pVid_Init_SYS)(s32, u16);
    s32 (CC **pVid_CheckMode)(Video*, s32, s32, s32);
    DisplayMode* (CC **pVid_FindMode)(Video*, s32);
    s32 (CC **pVid_FindFirstMode)(Video*, s32);
    s32 (CC **pVid_FindNextMode)(Video*);
    Device* (CC **pVid_FindDevice)(Video*, s32);
    s32 (CC **pVid_SetDevice)(Video*, s32);
    void (CC **pVid_CloseScreen)(Video*);
    s32 (CC **pVid_SetMode)(Video*, HWND, s32);
    void (CC **pVid_FlipBuffers)(Video*);
    void (CC **pVid_ReleaseSurface)(Video*);
    void (CC **pVid_GrabSurface)(Video*);
    void (CC **pVid_ShutDown_SYS)(Video*);
    s32 (CC **pVid_EnableWrites)(Video*);
    s32 (CC **pVid_DisableWrites)(Video*);
    s32 (CC **pVid_GetSurface)(Video*);
    s32 (CC **pVid_FreeSurface)(Video*);
    s32 (CC **pVid_ClearScreen)(Video*, u8, u8, u8, s32, s32, s32, s32);
    s32 (CC **pVid_WindowProc)(Video*, HWND, DWORD, WPARAM, LPARAM);
    s32 (CC **pVid_InitDLL)(HINSTANCE, PtrVideoFunctions*);
    s32 (CC **pVid_SetGamma)(Video*, f32, f32, f32);
    const char* mErrStr;
};

struct VideoFunctions
{
    VidVersion* (CC *pVid_GetVersion)();
    Video* (CC *pVid_Init_SYS)(s32, u16);
    s32 (CC *pVid_CheckMode)(Video*, s32, s32, s32);
    DisplayMode* (CC *pVid_FindMode)(Video*, s32);
    s32 (CC *pVid_FindFirstMode)(Video*, s32);
    s32 (CC *pVid_FindNextMode)(Video*);
    Device* (CC *pVid_FindDevice)(Video*, s32);
    s32 (CC *pVid_SetDevice)(Video*, s32);
    void (CC *pVid_CloseScreen)(Video*);
    s32 (CC *pVid_SetMode)(Video*, HWND, s32);
    void (CC *pVid_FlipBuffers)(Video*);
    void (CC *pVid_ReleaseSurface)(Video*);
    void (CC *pVid_GrabSurface)(Video*);
    void (CC *pVid_ShutDown_SYS)(Video*);
    s32 (CC *pVid_EnableWrites)(Video*);
    s32 (CC *pVid_DisableWrites)(Video*);
    s32 (CC *pVid_GetSurface)(Video*);
    s32 (CC *pVid_FreeSurface)(Video*);
    s32 (CC *pVid_ClearScreen)(Video*, u8, u8, u8, s32, s32, s32, s32);
    s32 (CC *pVid_WindowProc)(Video*, HWND, DWORD, WPARAM, LPARAM);
    s32 (CC *pVid_InitDLL)(HINSTANCE, PtrVideoFunctions*);
    s32 (CC *pVid_SetGamma)(Video*, f32, f32, f32);
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
