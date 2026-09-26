#include <QApplication>
#include "MainWindow.h"

// Редактор текстов игры (.gxt):
//   - открытие/сохранение e/f/g/i/s.gxt и bob_*.gxt (формат GBL?/TKEY/TDAT);
//   - таблица «Ключ | Текст» с фильтром;
//   - справочный файл-оригинал для перевода на новые языки;
//   - чистый save() без правок бинарно идентичен оригиналу.
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow w;
	w.resize(1024, 680);
	w.show();
	// Возможность открыть файл из командной строки.
	if (argc > 1)
		w.openGxtAt(QString::fromLocal8Bit(argv[1]));
	return app.exec();
}