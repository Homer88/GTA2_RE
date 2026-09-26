#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include "MainWindow.h"
#include "SaveFile.h"
#include "FieldDefs.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("GTA2RE");
    QCoreApplication::setApplicationName("EditSave");
    QCoreApplication::setApplicationVersion("1.0.0");

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QStringLiteral("GTA2 save editor for plyslotN.svg / plyslotN.dat"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption dirOpt(QStringList{QStringLiteral("d"), QStringLiteral("dir")},
        QStringLiteral("Player save folder (default C:/work/log/player)."),
        QStringLiteral("path"));
    QCommandLineOption slotOpt(QStringList{QStringLiteral("s"), QStringLiteral("slot")},
        QStringLiteral("Slot index to open, 0..7."), QStringLiteral("n"),
        QStringLiteral("0"));
    parser.process(app);

    QString dir = QStringLiteral("C:/work/log/player");
    if (parser.isSet(dirOpt))
        dir = QDir::cleanPath(parser.value(dirOpt));
    if (!QDir(dir).exists())
        dir = QDir::currentPath();

    int slot = 0;
    if (parser.isSet(slotOpt)) {
        bool ok = false;
        const int s = parser.value(slotOpt).toInt(&ok);
        if (ok && s >= 0 && s < 8)
            slot = s;
    }

    MainWindow w;
    w.setPlayerDir(dir);
    w.openSlot(slot);
    w.show();
    return app.exec();
}
