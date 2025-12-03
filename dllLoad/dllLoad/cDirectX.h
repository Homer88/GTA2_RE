#ifndef __DIRECTX__H_
#define __DIRECTX__H_

#include <dinput.h>

BOOL  __stdcall InitDiretX(HINSTANCE phInstance, DWORD* pFlags);
void __stdcall CleanupDirectInput();
HRESULT __stdcall CreateInputDevice(HINSTANCE hinst);
bool __stdcall directInputUtils(void* a, void* b);
#endif // !__DIRECTX__H_

