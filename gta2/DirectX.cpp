#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include "DirectX.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"ddraw.lib")

// Функция инициализации графического движка и ввода
BOOL InitGraphicsAndInput(HINSTANCE hInst, DWORD* pFlags)
{
    OSVERSIONINFO osInfo;
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

    // Загрузка библиотеки DirectDraw
    ddrawLib = LoadLibrary(TEXT("DDRAW.DLL"));
    if (!ddrawLib)
    {
        OutputDebugString(TEXT("Failed to load DDRAW.DLL"));
        return FALSE;
    }

    // Получение адреса функции DirectDrawCreate
    FARPROC procAddr = GetProcAddress(ddrawLib, TEXT("DirectDrawCreate"));
    if (!procAddr)
    {
        OutputDebugString(TEXT("Failed to find DirectDrawCreate in DDRAW.DLL"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // Создаем объект DirectDraw
    hr = ((HRESULT(WINAPI*)(GUID*, LPDIRECTDRAW*, IUnknown*))procAddr)(NULL, &lpDDraw, NULL);
    if (FAILED(hr))
    {
        OutputDebugString(TEXT("Failed to create DirectDraw object"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // Проверяем успешность инициализации
    if (lpDDraw->QueryInterface(IID_IDirectDraw2, (LPVOID*)&lpDDraw) != S_OK)
    {
        OutputDebugString(TEXT("Failed to initialize DirectDraw2 interface"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // Загружаем библиотеку DirectInput
    dinputLib = LoadLibrary(TEXT("DINPUT.DLL"));
    if (!dinputLib)
    {
        OutputDebugString(TEXT("Failed to load DINPUT.DLL"));
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // Получаем адрес функции DirectInputCreateA
    procAddr = GetProcAddress(dinputLib, TEXT("DirectInputCreateA"));
    if (!procAddr)
    {
        OutputDebugString(TEXT("Failed to find DirectInputCreateA in DINPUT.DLL"));
        FreeLibrary(dinputLib);
        FreeLibrary(ddrawLib);
        return FALSE;
    }

    // Успешная загрузка всех компонентов
    *pFlags |= 1 << 1 | 1 << 2 | 1 << 3; // Установлены флаги для DirectDraw и DirectInput
    return TRUE;
}
