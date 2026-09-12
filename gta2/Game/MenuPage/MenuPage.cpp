#include "MenuPage.h"


    // 0x00452A50

MenuPage::MenuPage() {
    this->NumberMenuItems[0] = 0;
    this->NumberMenuItems[1] = 0;
    this->IndexMenuActions = 0;
    this->SelectActiveElementDefault = 0;
}

MenuPage::~MenuPage() {
}

void MenuPage::Init() {

}
int MenuPage::UpdateIndexToActive(void){
        return 0;
    }


    // 0x00452AA0


int MenuPage::NextActiveItem(void){
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
    return 0;
}
