#ifndef __MENU__PAGE__H__
#define __MENU__PAGE__H__

#include <assert.h>

#include "cS136.h"
#include "cS137.h"
#include "cMenuEntry.h"

#pragma pack(push, 1) // ������������� ������������ �� 1 ����� (����������� ����������� ���������)
struct MenuPage{

	short numMenuItems; //0x0
	short field1;//0x2
	MenuEntry pMenuEntry[10]; //0x4
	S136    pS136[15];//0x518
	S137    pS137[10];
	// ДОКАЗАНО по retail: UpdateIndexToActive @0x452A50 и NextActiveItem
	// @0x452AA0 (это и есть up/down) читают и пишут [this+0xBC6], границей
	// служит [this+0] (numMenuItems-1), а невидимые пункты пропускаются по
	// pS137[idx].Y==0. Значит это ИНДЕКС ВЫДЕЛЕННОГО ПУНКТА.
	// В пересборке gta2\Game\MenuPage поле названо IndexMenuActions.
	unsigned short CurrentActiveElement;
	// Дефолтный индекс: при LoadTextMenu равен CurrentActiveElement, при
	// up/down в рантайме НЕ меняется (наблюдение из menu.txt).
	short SelectActiveElementDefault;

};
#pragma pack(pop) // ���������� ���������� ���������

static_assert(sizeof(MenuPage) == 3018, "ERROR MENU PAGE");




#endif // !__MENU__PAGE__H__

