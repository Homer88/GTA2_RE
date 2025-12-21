#ifndef __MENUPAGE__H_
#define __MENUPAGE__H_

#include "MenuEntry.h"
#include "GUI.h"
#include "MenuItem.h"

class MenuPage {
	
public:
	unsigned short numMenuItems;
	MenuEntry  pMenuEntry[10];
	MenuItem   pMenuItem[10];
	GUI   pGUI[15];
	unsigned short IndexMenuActions;
	unsigned  short SelectActiveElementDefault;
	MenuPage() {};
	~MenuPage() {};
};


#endif // !__MENUPAGE__H_
