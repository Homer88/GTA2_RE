#ifndef ___BINKW_32_H_
#define ___BINKW_32_H_




//прототипы
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
BOOL __stdcall DllEntryPoint(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);
int __stdcall BinkCheckCursor(HWND hWnd, LONG a2, LONG a3, int a4, int a5);
int __stdcall BinkRestoreCursor(int restoreCount);
void* __stdcall radmalloc(size_t size);
void __stdcall radfree(void* aligned_ptr);




#endif
