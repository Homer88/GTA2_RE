#ifndef  ___MenuEntry__H_
#define  ___MenuEntry__H_
#include <assert.h>

class MenuEntry {

public:
	int eMenuActions;
	// кординаты 
	short X;
	short Y;
	wchar_t TextMenuElement[50];
	short StringLength;
	unsigned short PlayerSlot;
	unsigned short PlayerSlot1;
	char FLAG[7];
	short index;
	unsigned short SelectMenu;


};
#endif // ! ___MenuEntry__H_

