#include <QApplication>
#include <QMainWindow>
#include <QLabel>

// Редактор оружия. ТЗ:
//   - параметры оружия (урон, скорострельность, разброс, боезапас...);
//   - тюнинг под моды.
// Текущее состояние: каркас. Нужен дамп формата.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QMainWindow w;
	w.setWindowTitle(QString::fromUtf8("GTA2 WeaponEditor"));
	QLabel* l = new QLabel(QString::fromUtf8(
		"Редактор оружия - в разработке\n\n"
		"Нужен разбор формата параметров оружия из дампа игры."));
	l->setAlignment(Qt::AlignCenter);
	w.setCentralWidget(l);
	w.resize(700, 420);
	w.show();
	return app.exec();
}