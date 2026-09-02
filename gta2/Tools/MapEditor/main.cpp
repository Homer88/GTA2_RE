#include <QApplication>
#include <QMainWindow>
#include <QLabel>

// Редактор карт. ТЗ:
//   - редактирование карт игры (зоны, спавны, пути, дороги, постройки).
// Текущее состояние: каркас. Нужен дамп формата карт/зоны.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QMainWindow w;
	w.setWindowTitle(QString::fromUtf8("GTA2 MapEditor"));
	QLabel* l = new QLabel(QString::fromUtf8(
		"Редактор карт - в разработке\n\n"
		"Нужен дамп формата карт игры."));
	l->setAlignment(Qt::AlignCenter);
	w.setCentralWidget(l);
	w.resize(700, 420);
	w.show();
	return app.exec();
}