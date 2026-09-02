#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setApplicationName("GTA2 MenuEditor");
	app.setOrganizationName("GTA2_RE");

	MainWindow w;
	w.show();
	return app.exec();
}