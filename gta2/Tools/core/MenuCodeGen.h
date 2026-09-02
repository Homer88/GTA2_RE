#ifndef __GTA2TOOLS_MENU_CODE_GEN_H_
#define __GTA2TOOLS_MENU_CODE_GEN_H_

#include <string>
#include "MenuDataModel.h"

namespace gta2tools {

// Генератор C++ по проекту меню: выдаёт функции в стиле реконструкции игры
// (MenuPage/MenuEntry), с текстом в виде широких строк-эскейпов (не зависит от
// кодировки исходников). Результат затем встраивается в класс меню игры.
std::string GenerateMenuCode(const MenuProjectModel& project);

} // namespace gta2tools

#endif // !__GTA2TOOLS_MENU_CODE_GEN_H_