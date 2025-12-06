#ifndef ___DIRECTX_H_
#define ___DIRECTX_H_



BOOL InitGraphicsAndInput(HINSTANCE hInst, DWORD* pFlags);

void CleanupDirectInput();
HRESULT CreateInputDevice(HINSTANCE hinst);

#endif // !___DIRECTX_H_


