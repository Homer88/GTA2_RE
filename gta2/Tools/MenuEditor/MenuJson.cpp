#include "MenuJson.h"

#include <QStringList>
#include <QJsonArray>

bool MenuProjectToJson(const gta2tools::MenuProjectModel& project, QJsonObject& out)
{
	QJsonArray pages;
	for (size_t i = 0; i < project.pages.size(); i++) {
		const gta2tools::MenuPageModel& pg = project.pages[i];
		QJsonArray entries;
		for (size_t k = 0; k < pg.entries.size(); k++) {
			const gta2tools::MenuEntryModel& e = pg.entries[k];
			QJsonObject jo;
			jo["text"]     = QString::fromStdWString(e.text);
			jo["x"]        = e.x;
			jo["y"]        = e.y;
			jo["fontSize"] = e.fontSize;
			jo["action"]   = e.action;
			jo["target"]   = e.target;
			jo["flags"]    = e.flags;
			entries.append(jo);
		}
		QJsonObject jp;
		jp["id"]      = pg.id;
		jp["name"]    = QString::fromStdWString(pg.name);
		jp["header"]  = QString::fromStdWString(pg.header);
		jp["entries"] = entries;
		pages.append(jp);
	}
	out["name"]      = QString::fromStdWString(project.name);
	out["startPage"] = project.startPage;
	out["pages"]     = pages;
	return true;
}

bool MenuProjectFromJson(const QJsonObject& in, gta2tools::MenuProjectModel& project)
{
	project = gta2tools::MenuProjectModel();
	project.name      = in["name"].toString().toStdWString();
	project.startPage = in["startPage"].toInt();

	const QJsonArray pages = in["pages"].toArray();
	for (int i = 0; i < pages.size(); i++) {
		const QJsonObject jp   = pages[i].toObject();
		gta2tools::MenuPageModel pg;
		pg.id     = jp["id"].toInt();
		pg.name   = jp["name"].toString().toStdWString();
		pg.header = jp["header"].toString().toStdWString();

		const QJsonArray entries = jp["entries"].toArray();
		for (int k = 0; k < entries.size() && k < 10; k++) {
			const QJsonObject jo = entries[k].toObject();
			gta2tools::MenuEntryModel e;
			e.text     = jo["text"].toString().toStdWString();
			e.x        = jo["x"].toInt();
			e.y        = jo["y"].toInt();
			e.fontSize = jo["fontSize"].toInt();
			e.action   = jo["action"].toInt();
			e.target   = jo["target"].toInt();
			e.flags    = jo["flags"].toInt();
			pg.entries.push_back(e);
		}
		project.pages.push_back(pg);
	}
	return !project.pages.empty();
}

QJsonDocument MenuProjectToDoc(const gta2tools::MenuProjectModel& project)
{
	QJsonObject o;
	MenuProjectToJson(project, o);
	return QJsonDocument(o);
}

bool MenuProjectFromDoc(const QJsonDocument& doc, gta2tools::MenuProjectModel& project)
{
	if (!doc.isObject())
		return false;
	return MenuProjectFromJson(doc.object(), project);
}