#ifndef __TOOLS_MENU_JSON_H_
#define __TOOLS_MENU_JSON_H_

#include <QJsonObject>
#include <QJsonDocument>
#include "MenuDataModel.h"

// Сохранение/загрузка проекта меню в/из JSON.
// Формат: { "name", "startPage", "pages": [ { "id","name","header",
//           "entries": [ {"text","x","y","fontSize","action","target","flags"} ] } ] }

bool MenuProjectToJson(const gta2tools::MenuProjectModel& project, QJsonObject& out);
bool MenuProjectFromJson(const QJsonObject& in, gta2tools::MenuProjectModel& project);

// Удобные обёртки для файла.
QJsonDocument MenuProjectToDoc(const gta2tools::MenuProjectModel& project);
bool MenuProjectFromDoc(const QJsonDocument& doc, gta2tools::MenuProjectModel& project);

#endif // !__TOOLS_MENU_JSON_H_