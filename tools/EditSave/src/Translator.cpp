#include "Translator.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QStringList>
#include <QTranslator>

namespace {
// Owned by value so a failed load leaves the previous catalogue in place;
// destroyed before the next one is installed (see the header note).
QTranslator *g_translator = nullptr;

QStringList candidatePaths()
{
    const QString exeDir = QCoreApplication::applicationDirPath();
    QStringList paths;
    paths << exeDir + QStringLiteral("/translations")
          << exeDir + QStringLiteral("/../translations")
          << exeDir + QStringLiteral("/../build/translations");
    // QLibraryInfo::path() is deprecated in Qt6 and removed in Qt7, so prefer
    // the location Qt itself reports for the loaded QtCore.
    const QString qtTr = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    if (!qtTr.isEmpty())
        paths << qtTr;
    return paths;
}
} // namespace

Translator &Translator::instance()
{
    static Translator t;
    return t;
}

QString Translator::searchPath()
{
    const QStringList paths = candidatePaths();
    for (const QString &p : paths) {
        if (QFileInfo::exists(p))
            return p;
    }
    return paths.value(0);
}

void Translator::applyLanguage(const QString &code)
{
    if (code.isEmpty() || code == m_code)
        return;

    QCoreApplication *app = QCoreApplication::instance();
    if (!app)
        return;

    // Uninstall before replacing: Qt keeps a raw pointer to the old
    // catalogue, and deleting it only after install() is undefined.
    if (g_translator) {
        app->removeTranslator(g_translator);
        delete g_translator;
        g_translator = nullptr;
    }

    QString applied = QStringLiteral("en");
    if (code != QStringLiteral("en")) {
        auto *t = new QTranslator;
        bool loaded = false;
        for (const QString &dir : candidatePaths()) {
            if (t->load(QStringLiteral("editsave_") + code, dir)) {
                loaded = true;
                break;
            }
        }
        if (loaded && app->installTranslator(t)) {
            g_translator = t;
            applied = code;
        } else {
            delete t;   // fall back to the English source strings
        }
    }

    m_code = applied;
    emit languageChanged(applied);
}
