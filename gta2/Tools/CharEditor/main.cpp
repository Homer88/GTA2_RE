#include <QApplication>
#include "MainWindow.h"

// Редактор персонажей GTA2: параметры профессий/пешеходов.
//   - список профессий (occupation из struct Ped);
//   - параметры: здоровье, скорость, спрайт, ремап, стартовое оружие, флаги;
//   - сохранение в текстовом формате .gch.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();
	return app.exec();
}