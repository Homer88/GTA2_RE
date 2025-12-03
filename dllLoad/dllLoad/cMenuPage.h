#ifndef __MENU__PAGE__H__
#define __MENU__PAGE__H__

#include <assert.h>

#include "cS136.h"
#include "cS137.h"
#include "cMenuEntry.h"


struct MenuPage{

	short field;
	short field1;
	MenuEntry strMenuEntry[10];
	S136    pS136[15];
	S137    pS137[10];
	unsigned short IndexMenuActins;
	short field_BC8;

};

///static_assert(sizeof(MenuPage) == 3018, "ERROR MENU PAGE");




#endif // !__MENU__PAGE__H__

