#ifndef __GTA2TOOLS_MENU_DATA_MODEL_H_
#define __GTA2TOOLS_MENU_DATA_MODEL_H_

#include <string>
#include <vector>

// Модель данных меню GTA2 для редактора меню.
// Поля соответствуют реконструированным классам игры (MenuPage/MenuEntry):
// страница = до 10 элементов (MenuPage::MenuEntryArray[10]), у каждого элемента
// координаты X/Y (пиксели экрана 640x480), текст (wchar_t, до 50 символов —
// MenuEntry::TextMenuElementArray), размер шрифта и действие.

namespace gta2tools {

// Действие пункта меню (MenuEntry::MenuAction упрощённо: 0/1/2).
enum MenuEntryAction {
	ActionNone  = 0, // просто надпись, ничего не делает
	ActionPage,      // переход на другую страницу (target = id страницы)
	ActionGame       // игровое действие (target = номер действия игры)
};

struct MenuEntryModel {
	std::wstring text;   // текст надписи
	int x = 0;           // координата X (пиксели, экран 640x480)
	int y = 0;           // координата Y
	int fontSize = 0;    // размер шрифта в пунктах; 0 = размер по умолчанию
	int action = ActionNone; // что делает пункт
	int target = 0;          // при action: id страницы или номер действия
	int flags = 0;           // битовая маска флагов (0x2 = пункт неактивен/затемнён)
};

struct MenuPageModel {
	std::wstring name;   // имя страницы (для редактора)
	std::wstring header; // заголовок страницы
	int id = 0;          // номер страницы (MenuPage::CurentMenuPage)
	std::vector<MenuEntryModel> entries; // пункты (не более 10)
};

struct MenuProjectModel {
	std::wstring name;               // название проекта/мода
	int startPage = 0;               // страница, показываемая первой
	std::vector<MenuPageModel> pages; // все страницы меню
};

} // namespace gta2tools

#endif // !__GTA2TOOLS_MENU_DATA_MODEL_H_