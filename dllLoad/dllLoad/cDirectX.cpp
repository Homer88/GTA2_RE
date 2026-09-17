#include <Windows.h>
#include <iostream>
#include <ddraw.h>
#include <direct.h>
#include <dinput.h>

#include "cDirectX.h"
#include "cHookTrace.h"

LPDIRECTINPUT8 gDirectInput8 = (LPDIRECTINPUT8) 0x005E8FA4;

#pragma warning(disable : 4996)

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"ddraw.lib")
#pragma comment(lib, "dinput8.lib")


BOOL  __stdcall InitGraphicsAndInput(HINSTANCE phInstance, DWORD* pFlags) {
    OSVERSIONINFO osInfo;
    TraceCall("InitGraphicsAndInput @0x004031C0", TRACE_CALLER_ADDR);
    HMODULE ddrawLib, dinputLib;
    LPVOID lpDDSurfaceDesc = NULL;
    LPDIRECTDRAW lpDDraw = NULL;
    HRESULT hr;

    ZeroMemory(&osInfo, sizeof(OSVERSIONINFO));
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osInfo))
    {
        *pFlags = 0;
        return FALSE;
    }

    if (osInfo.dwMajorVersion != 2 && osInfo.dwMinorVersion != 4)
    {
        *pFlags |= 1 << 0; // Windows NT/XP/Vista+
        return TRUE;
    }

    // �������� ���������� DirectDraw
    ddrawLib = LoadLibrary(TEXT("DDRAW.DLL"));
    if (!ddrawLib)
    {
        OutputDebugString(TEXT("Failed to load DDRAW.DLL"));
        return FALSE;
    }

    // ��������� ������ ������� DirectDrawCreate
    FARPROC procAddr = GetProcAddress(ddrawLib, ("DirectDrawCreate"));
    if (!procAddr)
    {
        OutputDebugString(TEXT("Failed to find DirectDrawCreate in DDRAW.DLL"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // ������� ������ DirectDraw
    hr = ((HRESULT(WINAPI*)(GUID*, LPDIRECTDRAW*, IUnknown*))procAddr)(NULL, &lpDDraw, NULL);
    if (FAILED(hr))
    {
        OutputDebugString(TEXT("Failed to create DirectDraw object"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // ��������� ���������� �������������
    if (lpDDraw->QueryInterface(IID_IDirectDraw2, (LPVOID*)&lpDDraw) != S_OK)
    {
        OutputDebugString(TEXT("Failed to initialize DirectDraw2 interface"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // ��������� ���������� DirectInput
    dinputLib = LoadLibrary(TEXT("DINPUT.DLL"));
    if (!dinputLib)
    {
        OutputDebugString(TEXT("Failed to load DINPUT.DLL"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // �������� ����� ������� DirectInputCreateA
    procAddr = GetProcAddress(dinputLib, "DirectInputCreateA");
    if (!procAddr)
    {
        OutputDebugString(TEXT("Failed to find DirectInputCreateA in DINPUT.DLL"));
        FreeLibrary(dinputLib);
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // �������� �������� ���� �����������
    *pFlags |= 1 << 1 | 1 << 2 | 1 << 3; // ����������� ����� ��� DirectDraw � DirectInput
    return TRUE;
}


void __stdcall CleanupDirectInput() {
   
   
   // �� �������� ������ 
   /* if (gDirectInput8) {
        // �������� Release() � �������� ��������� ������� � ���������
        gDirectInput8->Release();
        gDirectInput8 = NULL; // ������ �� ���������� �������������
    }*/


}

///bool byte_5E8F54 = (bool*)0x5E8F54;
bool __stdcall directInputUtils(void* a, void* b) {

    /// ���������� ������ �������

   /// byte_5E8F54 = 0;
   /// if (DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&gDirectInput8, NULL) < 0)
    return true;
}

HRESULT __stdcall CreateInputDevice(HINSTANCE hinst)
{
    HRESULT result; // eax
  
    result = DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&gDirectInput8, NULL);
    if (result < 0)
        return NULL;
       
    return result;
}
