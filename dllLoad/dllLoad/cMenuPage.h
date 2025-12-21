#ifndef __MENU__PAGE__H__
#define __MENU__PAGE__H__

#include <assert.h>

#include "cS136.h"
#include "cS137.h"
#include "cMenuEntry.h"

#pragma pack(push, 1) // устанавливает выравнивание по 1 байту (максимально упакованная структура)
struct MenuPage{

	short numMenuItems; //0x0
	short field1;//0x2
	MenuEntry pMenuEntry[10]; //0x4
	S136    pS136[15];//0x518
	S137    pS137[10];
	unsigned short IndexMenuActions;
	short field_BC8;

};
#pragma pack(pop) // возвращает предыдущие настройки

static_assert(sizeof(MenuPage) == 3018, "ERROR MENU PAGE");




#endif // !__MENU__PAGE__H__

