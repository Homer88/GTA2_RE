#include "MenuPage.h"

MenuPage::MenuPage() {
	/*for (int i = 0; i <= 10; i++) {
		this->MenuEntryArray[i].Init();
	}
	for (int i = 0; i <= 15; i++) {
		this->MenuEntryArray[i].Init();
	}
	for (int i = 0; i <= 10; i++) {
		this->MenuEntryArray[i].Init();
	}*/
	this->NumberMenuItems[0] = 0;
	this->NumberMenuItems[1] = 0;
	this->IndexMenuActions = 0;
	this->SelectActiveElementDefault = 0;
}
void MenuPage::Init() {
	//this->MenuPage();
}

int  MenuPage::NextActiveItem() {
	unsigned short _IndexMenuActions = this->IndexMenuActions;
	unsigned short _IndexMenuActionsStart = _IndexMenuActions;
	int _NumberMenuItems = this->NumberMenuItems[0] - 1;
	do {
		if (_IndexMenuActions == _NumberMenuItems) {
			this->IndexMenuActions = 0;
		}
		else {
			this->IndexMenuActions++;
		}
		_IndexMenuActions = this->IndexMenuActions;
	} while (!this->MenuItemArray[_IndexMenuActions].IndexMenuActions);
	return _IndexMenuActionsStart != _IndexMenuActions;
	{

	}
}
MenuPage::~MenuPage() {

}