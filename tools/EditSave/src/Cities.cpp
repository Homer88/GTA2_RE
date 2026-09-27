#include "Cities.h"

#include <QCoreApplication>
#include <QRegularExpression>
#include <QStringList>

namespace {

QString tr(const char *text)
{
    return QCoreApplication::translate("Cities", text);
}

} // namespace

namespace Cities {

const QVector<CityDef> &all()
{
    static const QVector<CityDef> v = {
        { 0, QStringLiteral("wil"), tr("Liberty City"),
          QStringLiteral("data\\wil.gmp"), QStringLiteral("data\\wil.sty"),
          QStringLiteral("data\\wil.scr") },
        { 1, QStringLiteral("ste"), tr("Industrial City"),
          QStringLiteral("data\\ste.gmp"), QStringLiteral("data\\ste.sty"),
          QStringLiteral("data\\ste.scr") },
        { 2, QStringLiteral("bil"), tr("Bilboa City"),
          QStringLiteral("data\\bil.gmp"), QStringLiteral("data\\bil.sty"),
          QStringLiteral("data\\bil.scr") },
    };
    return v;
}

const CityDef *byArena(int arena)
{
    const QVector<CityDef> &v = all();
    for (const CityDef &c : v)
        if (c.arena == arena)
            return &c;
    return nullptr;
}

QString baseName(const QString &path)
{
    // Saves store Windows paths, but the editor may be handed a path built
    // with forward slashes, so accept either separator.
    const int i = path.lastIndexOf(QRegularExpression(QStringLiteral("[/\\\\]")));
    return i < 0 ? path : path.mid(i + 1);
}

const CityDef *byFileName(const QString &anyName)
{
    if (anyName.isEmpty())
        return nullptr;
    const QString needle = baseName(anyName).toLower();
    const QVector<CityDef> &v = all();
    for (const CityDef &c : v) {
        if (baseName(c.mapFile).toLower()    == needle) return &c;
        if (baseName(c.styleFile).toLower()  == needle) return &c;
        if (baseName(c.scriptFile).toLower() == needle) return &c;
    }
    return nullptr;
}

} // namespace Cities
