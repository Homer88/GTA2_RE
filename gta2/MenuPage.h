#ifndef __MENUPAGE__H_
#define __MENUPAGE__H_

#include "MenuEntry.h"
#include "S136.h"
#include "S137.h"

class MenuPage {
	
public:
	unsigned short numMenuItems;
	MenuEntry  pMenuEntry[10];
	S137   pS137[10];
	S136   pS136[15];
	unsigned short IndexMenuActions;
	MenuPage() {};
	~MenuPage() {};
};


#endif // !__MENUPAGE__H_
