/*
Иструменты для работы ПО.
*/
#ifndef ___WIN_API___H__
#define ___WIN_API___H__
#include <windows.h>
class WinApi{
	public:
		WinApi();
		char* Convertor_wchar_t_ToChar(wchar_t* Text);
		wchar_t* CopyWideString(wchar_t* dest, wchar_t* source);
		
		void GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion);
		~WinApi();
};



 
#endif  //___WIN_API___H__
