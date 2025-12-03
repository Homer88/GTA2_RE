#ifndef __MenuEntry__H_
#define __MenuEntry__H_

#include <assert.h>

enum MenuActions: unsigned char 
{
	MENUACTION_NONE = 0u,
	MENUACTION_CHANGEPAGE = 1u,
     MENUACTION_SETPLAYERNAME = 2u,
};


struct MenuEntry
{
	MenuActions MenuActions;
	char field1;
	short X;
	short Y;
	wchar_t str[50];
	short field_6A;
	short field_6C;
	unsigned short PlayerSlot;
	short PlayerSlot1;
	int field_72;
	int field_76;
	int field_7A;
	unsigned short  field_7E;
	unsigned short  field_80;

};

static_assert(sizeof(MenuEntry) == 132, "ERROR MENU STRUCT");


#endif // !__MenuEntry__H_
