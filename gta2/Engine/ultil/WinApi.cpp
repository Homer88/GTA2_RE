#include "WinApi.h"
#include <stdlib.h>

WinApi gWinApi;

#define MaxTextElement 80

char gTextArrayChar[MaxTextElement];



WinApi::WinApi(){
}

char * WinApi::Convertor_wchar_t_ToChar(wchar_t *Text){
	wchar_t * _Text=Text;
	for (int index=0; _Text; ++index){
		if (index>=79){
			break;
		};
		gTextArrayChar[index]= *_Text<128u ? *(BYTE*)_Text: '#';
		++_Text;
	};
	return gTextArrayChar;
	
}

void  WinApi::GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion){
	
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

WinApi::~WinApi(){};