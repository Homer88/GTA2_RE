#include <Windows.h>
#include "cText.h"



bool GetLanguageJapan(Text* pText) {

	MessageBox(0, "Попали в cText", 0, 0);
	return pText->Language == 'j';
}