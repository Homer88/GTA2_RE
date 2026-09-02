#include <QApplication>
#include <QMainWindow>
#include <QLabel>

// Редактор персонажей. ТЗ:
//   - параметры персонажей/пешеходов игры;
//   - редактор персонажей с внешним видом/поведением.
// Текущее состояние: каркас. Нужен дамп формата.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QMainWindow w;
	w.setWindowTitle(QString::fromUtf8("GTA2 CharacterEditor"));
	QLabel* l = new QLabel(QString::fromUtf8(
		"Редактор персонажей - в разработке\n\n"
		"Нужен разбор формата параметров персонажей из дампа игры."));
	l->setAlignment(Qt::AlignCenter);
	w.setCentralWidget(l);
	w.resize(700, 420);
	w.show();
	return app.exec();
}