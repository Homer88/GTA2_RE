#ifndef  ___MenuEntry__H_
#define  ___MenuEntry__H_
#include <assert.h>

class MenuEntry {

public:
	int eMenuActions;
	// кординаты 
	short X;
	short Y;
	wchar_t str[50];
	unsigned short PlayerSlot;


};
#endif // ! ___MenuEntry__H_

