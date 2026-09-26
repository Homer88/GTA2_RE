#include <QApplication>
#include "MainWindow.h"

// Редактор карт GTA2: редактор зон (.gmp, секция ZONE).
//   - список зон (спавны/территории/пути),
//   - правка параметров (тип, x, y, w, h, имя),
//   - отрисовка зон поверх карты,
//   - сохранение обратно в .gmp без потери прочих секций.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();
	if (argc > 1)
		QMetaObject::invokeMethod(&w, "openFile", Qt::QueuedConnection);
	return app.exec();
}
