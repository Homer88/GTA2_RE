#pragma once



// Прототип функции обработки сообщений
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion);
void FindGraphiDevace();
bool IsVideoPlaying();
void InitInput();
void Deff(byte a);
void DestructorMovie(); //FixMe
void Destructor();//FixMe
int BinkClose(UINT uMSG, HWND hWND);//FixMe
int SetVideoPlayer();
void SetGamma();
void* ConfigureVideoSystem();
char  LoadConfig();

