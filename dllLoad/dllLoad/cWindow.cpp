#include <Windows.h>
#include "cWindow.h"

HWND hwnd;

#pragma comment(lib, "version.lib")

void GetVersionLaunch(DWORD* pMajorVersion, DWORD* pMinorVersion) {


    hwnd = FindWindow(NULL, "GTA2");
    if (hwnd == NULL) {
        MessageBox(NULL, "Version!", "GTA2", MB_OK);
    }
    MessageBox(NULL, "Version!","GTA2",  MB_OK);
    // Проверка входных указателей
    if (pMajorVersion == NULL || pMinorVersion == NULL) {
        return;
    }

    // Инициализация выходных значений
    *pMajorVersion = 0;
    *pMinorVersion = 0;

    // Получение размера информации о версии
    DWORD dummyHandle = 0;
    DWORD versionInfoSize = GetFileVersionInfoSizeA("GTA2.EXE", &dummyHandle);

    if (versionInfoSize == 0) {
        return;
    }

    // Выделение памяти (C++98 style)
    BYTE* pVersionInfo = (BYTE*)malloc(versionInfoSize);
    if (pVersionInfo == NULL) {
        return;
    }

    // Получение информации о версии
    if (!GetFileVersionInfoA("GTA2.EXE", 0, versionInfoSize, pVersionInfo)) {
        free(pVersionInfo);
        return;
    }

    // Получение указателя на структуру версии
    VS_FIXEDFILEINFO* pFileInfo = NULL;
    UINT fileInfoLen = 0;

    if (!VerQueryValueA(pVersionInfo, "\\", (LPVOID*)&pFileInfo, &fileInfoLen) ||
        pFileInfo == NULL ||
        fileInfoLen < sizeof(VS_FIXEDFILEINFO))
    {
        free(pVersionInfo);
        return;
    }

    // Извлечение версий с помощью макросов Windows
    *pMajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
    *pMinorVersion = LOWORD(pFileInfo->dwFileVersionMS);

    // Освобождение памяти
    free(pVersionInfo);
}

