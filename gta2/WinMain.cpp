// Основной вход в GTA2 


#include "Global.h"
#include "WinMain.h"
#include <stdio.h>
#include "DirectX.h"

HINSTANCE ghInstance;
HANDLE gHANDLE;

DWORD	gMajor;
DWORD	gMinor;
HWND    gHWND;
char    gPath[255];

bool gSkipFrontend1;


#define NameWindows "GTA2"

// Точка входа Windows-приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 1. Регистрация класса окна
    const char* CLASS_NAME = NameWindows;
	// 

	ghInstance=hInstance;
	gHANDLE =(HANDLE)CoInitialize(0);
	GetVersion(&gMajor, &gMinor);
	
	DWORD pFlags;
	
	InitGraphicsAndInput(hInstance,  &pFlags);
	
	if ((unsigned int)hInstance < 0x601){
			MessageBox(NULL,"ERROR: Incorrect version of DirectX", "ERROR", MB_ICONERROR);
			ReleaseMutex(gHANDLE);
			CloseHandle(gHANDLE);
			return -1;
		}

	GetDebugParam();
	gMapGm.LoadFileResurce();
	gSkipFrontend1=!gSkipFrontend;

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    //wc.hIcon = LoadIconA(hInstance, (LPCSTR)0x65); FIXME нету иконки для приложения
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(0);
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Ошибка регистрации класса окна!", "Ошибка", MB_ICONERROR);
        return 1;
    }

    FindGraphiDevace();
    _getcwd(gPath,256);

    // 2. Создание окна
    HWND hwnd = CreateWindowEx(
        0,                      // Дополнительные стили
        CLASS_NAME,             // Имя класса
        NameWindows,            // Заголовок
        WS_OVERLAPPEDWINDOW,   // Стиль окна

        // Размер и позиция
        CW_USEDEFAULT, CW_USEDEFAULT, 
        800, 600,

        NULL,       // Родительское окно
        NULL,       // Меню
        hInstance,  // Экземпляр приложения
        NULL        // Дополнительные данные
    );

    if (!hwnd) {
        MessageBox(NULL, "Ошибка создания окна!", "Ошибка", MB_ICONERROR);
        return 1;
    }
    gHWND = hwnd;
    // 3. Показать окно
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    //конфигурация видео окна
    initDirectInput(ghInstance);
    ConfigureVideoSystem();
    InitVideoSystem_3DFX();
    LoadConfig();

    // 4. Цикл обработки сообщений
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

