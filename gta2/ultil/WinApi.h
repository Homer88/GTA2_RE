/*
Данный файл содержит стандартные функции для работы с текстом и так далее
*/
#ifndef ___WIN_API___H__
#define ___WIN_API___H__
#include <windows.h>
class WinApi{
	public:
		WinApi();
		char* Convertor_wchar_t_ToChar(wchar_t* Text);
		~WinApi();
};



 
#endif  //___WIN_API___H__
