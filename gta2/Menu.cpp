#include "Global.h"
#include "Menu.h"


Menu gMenu;



void Menu::SetFrontendKeysEnabled(byte param) {
	this->FrontendKeysEnabled = param;
}