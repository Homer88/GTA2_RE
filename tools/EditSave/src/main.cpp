#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QIcon>
#include <QMessageBox>
#include "AppSettings.h"
#include "MainWindow.h"
#include "Translator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("GTA2RE");
    QCoreApplication::setApplicationName("EditSave");
    QCoreApplication::setApplicationVersion("1.0.0");

    // ---- appearance ------------------------------------------------------
    // The PNG drives the window decoration and task bar; the .ico is compiled
    // into the PE resource block by resources/EditSave.rc for Explorer/Alt-Tab.
    QIcon icon(QStringLiteral(":/EditSave.png"));
    if (icon.isNull())
        icon = QIcon(QStringLiteral(":/EditSave.ico"));
    if (!icon.isNull())
        app.setWindowIcon(icon);

    // Must happen before any widget is constructed: Qt bakes the application
    // font into widget metrics at construction time, so scaling afterwards
    // leaves already-created widgets on the old size.
    AppSettings::instance().applyScale(app);

    // Translations next, so every tr() below resolves at construction time.
    Translator::instance().applyLanguage(AppSettings::instance().language());

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QStringLiteral("GTA2 save editor for plyslotN.svg / plyslotN.dat"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption dirOpt(QStringList{QStringLiteral("d"), QStringLiteral("dir")},
        QStringLiteral("Player save folder (default from config)."),
        QStringLiteral("path"));
    QCommandLineOption slotOpt(QStringList{QStringLiteral("s"), QStringLiteral("slot")},
        QStringLiteral("Slot index to open, 0..7."), QStringLiteral("n"),
        QStringLiteral("0"));
    parser.addOption(dirOpt);
    parser.addOption(slotOpt);
    parser.process(app);

    // Precedence: command line, then last session, then a folder that exists.
    AppSettings &cfg = AppSettings::instance();

    QString dir = cfg.playerDir();
    if (parser.isSet(dirOpt))
        dir = QDir::cleanPath(parser.value(dirOpt));
    if (!QDir(dir).exists())
        dir = QDir::currentPath();

    int slot = cfg.lastSlot();
    if (parser.isSet(slotOpt)) {
        bool ok = false;
        const int s = parser.value(slotOpt).toInt(&ok);
        if (ok && s >= 0 && s < 8)
            slot = s;
    }

    MainWindow *w = new MainWindow;
    w->setPlayerDir(dir);
    w->openSlot(slot);
    w->show();

    // Qt does not re-run tr() on existing widgets, so switching language means
    // building the window again. The new one is constructed before the old is
    // torn down, which keeps geometry, slot and folder continuous.
    QObject::connect(&Translator::instance(), &Translator::languageChanged,
                     w, [w](const QString &code) {
        const auto r = QMessageBox::question(
            w, QObject::tr("Switch language"),
            QObject::tr("Language set to %1. The window will be rebuilt.\n\n"
                        "Unsaved edits in the current window are lost.").arg(code),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (r != QMessageBox::Yes)
            return;

        const QString dir = w->playerDir();
        const int slot = w->currentSlot();
        auto *fresh = new MainWindow;
        fresh->setPlayerDir(dir);
        fresh->openSlot(slot);
        fresh->show();
        w->deleteLater();
    });

    return app.exec();
}
