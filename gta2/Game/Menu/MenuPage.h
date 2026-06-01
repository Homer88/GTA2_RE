#ifndef __MENU_PAGE_H_
#define __MENU_PAGE_H_

#include "MenuEntry.h"
#include "GUI.h"
#include "MenuItemConfig.h"
// Структура MenuPage (страница меню)
// Размер: предположительно 0x200 байт


class MenuPage {
public:
    int NumberMenuItems[2];// +0x00 - количество элементов  на странице 
    unsigned short CurentMenuPage;
    unsigned short NextMenuPage;
    MenuEntry MenuEntryArray[10];        // +0x04 - элементы меню (10 * 0x50 = 0x320)
    GUI GUIArray[15];            // +0x324 - графические элементы (15 * 4 = 0x3C)
    MenuItem MenuItemArray[10];  // +0x360 - пункты меню (10 * 4 = 0x28)
    int IndexMenuActions;
    int SelectActiveElementDefault;
    MenuPage();
    ~MenuPage();
    void Init();
    int  NextActiveItem();

};
#endif // !__MENU_PAGE_H_
