#include <QApplication>
#include <QMainWindow>
#include <QLabel>

// Редактор характеристик машин. ТЗ:
//   - редактирование параметров машин игры (скорость, ускорение, броня...);
//   - создание/тюнинг машин для модов.
// Текущее состояние: каркас. Нужен дамп формата таблицы машин.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QMainWindow w;
	w.setWindowTitle(QString::fromUtf8("GTA2 CarEditor"));
	QLabel* l = new QLabel(QString::fromUtf8(
		"Редактор машин - в разработке\n\n"
		"Нужен разбор формата характеристик машин из дампа игры.\n"
		"(скорость, ускорение, броня и т.п.)"));
	l->setAlignment(Qt::AlignCenter);
	w.setCentralWidget(l);
	w.resize(700, 420);
	w.show();
	return app.exec();
}