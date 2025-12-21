#ifndef __MenuEntry__H_
#define __MenuEntry__H_

#include <assert.h>

enum MenuActions: unsigned char 
{
	MENUACTION_NONE = 0u,
	MENUACTION_CHANGEPAGE = 1u,
     MENUACTION_SETPLAYERNAME = 2u,
};

#pragma pack(push, 1) // устанавливает выравнивание по 1 байту (максимально упакованная структура)

struct MenuEntry
{
	unsigned char  pMenuActions;  //0x0
	char field1;			  //0x1
	short X;				  //0x2
	short Y;				//0x4
	wchar_t TextMenuElement[50];		//0x6
	short field_6A;			//6a
	short field_6C;			//6c
	unsigned short PlayerSlot; //6e
	short PlayerSlot1;			// 70
	int field_72;				//72
	int field_76;				//76
	int field_7A;				//80
	unsigned short  field_7E;	//7E
	unsigned short  SelectMenu;   //0x80

};

#pragma pack(pop) // возвращает предыдущие настройки


static_assert(sizeof(MenuEntry) == 130, "ERROR MENU STRUCT");


#endif // !__MenuEntry__H_
