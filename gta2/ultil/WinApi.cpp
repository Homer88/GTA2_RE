#include "WinApi.h"
#include "../global.h"

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
		gTextArrayChar[index]= *_Text<128u ? *(_BYTE*)_Text: '#';
		++_Text;
	};
	return gTextArrayChar;
	
}
