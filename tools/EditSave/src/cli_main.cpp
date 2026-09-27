// ---------------------------------------------------------------------------
// EditSaveCli - console front end over the same parsing code as the GUI.
//
// Its real job is verification: parse a real slot, print what it found, and
// prove the write path is byte-exact. "It compiled" says nothing about whether
// the format handling is right, and a save editor that silently corrupts a file
// is worse than no tool at all.
// ---------------------------------------------------------------------------
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QTranslator>
#include "SaveFile.h"
#include "FieldDefs.h"
#include "ScriptFile.h"
#include "Cities.h"

static QString joinRange(SaveFile &sf, int off, int count, int size)
{
    QStringList l;
    for (int i = 0; i < count; ++i) {
        const int o = off + i * size;
        l << QString::number(size == 1 ? sf.u8(o) : (size == 2 ? sf.u16(o) : sf.u32(o)));
    }
    return l.join(' ');
}

static int selfTest(const QString &dir, int slot, QTextStream &out)
{
    const QString svg = QString("%1/plyslot%2.svg").arg(dir).arg(slot);
    const QString dat = QString("%1/plyslot%3.dat").arg(dir).arg(slot);

    SaveFile sf;
    QString err;
    if (!sf.loadSvg(svg, &err)) { out << "FAIL svg: " << err << "\n"; return 1; }
    const bool haveDat = sf.loadDat(dat, &err);
    if (!haveDat) out << "note: no .dat (" << err << ")\n";

    out << "=== " << QFileInfo(svg).fileName() << " ===\n";
    out << QString("  map    = '%1'\n").arg(sf.nameAt(0x00));
    out << QString("  style  = '%1'\n").arg(sf.nameAt(0x19));
    out << QString("  script = '%1'\n").arg(sf.nameAt(0x32));
    out << QString("  city=%1 (arena)  bonusStage=0x%2  gang=%3\n")
               .arg(sf.u8(0x4B)).arg(sf.u8(0x4C), 2, 16, QChar('0')).arg(sf.u8(0x4D));
    {
        const CityDef *c = Cities::byFileName(sf.nameAt(0x00));
        out << QString("  -> %1\n").arg(c ? c->displayName
                                           : QStringLiteral("unknown map file"));
    }
    out << QString("  money=%1  multiplier=%2  health=%3  lives=%4  wanted=%5  tokens=%6\n")
               .arg(sf.u32(0x64)).arg(sf.u32(0x68)).arg(sf.u16(0x6C))
               .arg(sf.u8(0xD4)).arg(sf.u16(0xE0)).arg(sf.u32(0x744));
    out << "  powerups[17] = " << joinRange(sf, 0x6E, PupSlotCount, 1) << "\n";
    for (int i = 0; i < PupSlotCount; ++i)
        out << QString("      [%1] %2 = %3\n").arg(i, 2).arg(powerupSlotName(i), -24).arg(sf.u8(0x6E + i));
    out << "  gangRespect  = " << joinRange(sf, 0xC9, 10, 1) << "\n";
    out << "  ammo[15]     = " << joinRange(sf, 0xBA, WpnSlotCount, 1) << "\n";
    for (int i = 0; i < WpnSlotCount; ++i)
        out << QString("      [%1] %2 = %3\n").arg(i, 2).arg(weaponSlotName(i), -24).arg(sf.u8(0xBA + i));
    out << QString("  equipped weapon = %1\n")
               .arg(sf.u16(0xD6) == 0xFFFF
                        ? QCoreApplication::translate("WeaponTable", "none")
                        : weaponSlotName(sf.u16(0xD6)));
    out << QString("  trailing blocks = %1 / %2 / %3 B\n")
               .arg(sf.trailing().value(0).size())
               .arg(sf.trailing().value(1).size())
               .arg(sf.trailing().value(2).size());
    out << QString("  mission count@0x12A = %1, non-empty = %2\n")
               .arg(sf.missionCountField()).arg(sf.missionUsedCount());
    out << QString("  manifest fields = %1\n").arg(fieldDefs().size());

    if (haveDat) {
        out << QString("=== %1 ===  player='%2'\n")
                   .arg(QFileInfo(dat).fileName()).arg(sf.datPlayerName());
        for (int i = 0; i < SaveFile::kDatRecCount; ++i)
            out << QString("  rec %1  arena %2  sub %3  flag %4  best %5  last %6\n")
                       .arg(i, 2).arg(i / 4).arg(i % 4)
                       .arg(sf.datFlag(i)).arg(sf.datBest(i)).arg(sf.datLast(i));
    }

    // ---- round trip ------------------------------------------------------
    const QString tmp = QDir(QDir::tempPath())
        .filePath(QString("editsave_rt_%1.svg").arg(slot));
    if (!sf.saveSvg(tmp, &err)) { out << "FAIL write: " << err << "\n"; return 1; }
    QFile a(svg), b(tmp);
    if (!a.open(QIODevice::ReadOnly) || !b.open(QIODevice::ReadOnly)) {
        out << "FAIL: cannot reopen files\n"; return 1;
    }
    const QByteArray ba = a.readAll(), bb = b.readAll();
    QFile::remove(tmp);
    if (ba == bb) {
        out << QString("ROUND TRIP OK (%1 bytes identical)\n").arg(ba.size());
    } else {
        int firstDiff = -1;
        for (int i = 0; i < qMin(ba.size(), bb.size()); ++i)
            if (ba[i] != bb[i]) { firstDiff = i; break; }
        out << QString("FAIL round trip: sizes %1 vs %2, first diff at 0x%3\n")
                   .arg(ba.size()).arg(bb.size()).arg(firstDiff, 0, 16);
        return 1;
    }
    return 0;
}

// Verify that applyCity() reproduces the table the retail game wrote: the .scr
// markers must match the save's 300 rows exactly.
static int checkCity(const QString &dataDir, const QString &dir, int slot, QTextStream &out)
{
    const QString svg = QString("%1/plyslot%2.svg").arg(dir).arg(slot);
    SaveFile sf;
    QString err;
    if (!sf.loadSvg(svg, &err)) { out << "FAIL svg: " << err << "\n"; return 1; }

    const QString scr = QString("%1/%2").arg(dataDir, Cities::baseName(sf.nameAt(0x32)));
    ScriptFile script;
    if (!script.load(scr, &err)) { out << "FAIL scr: " << err << "\n"; return 1; }

    const QVector<QPair<quint16, quint16> > want = script.markers();
    out << QString("=== %1 vs %2 ===\n").arg(Cities::baseName(sf.nameAt(0x32)), svg);
    out << QString("  .scr markers      = %1\n").arg(want.size());
    out << QString("  save count @0x12A = %1\n").arg(sf.missionCountField());
    out << QString("  save non-empty    = %1\n").arg(sf.missionUsedCount());

    int idDiffs = 0, stateDiffs = 0;
    for (int i = 0; i < 300; ++i) {
        const int off = 0x134 + i * 4;
        const quint16 sid = sf.u16(off), sst = sf.u16(off + 2);
        const quint16 wid = i < want.size() ? want.at(i).first  : 0;
        const quint16 wst = i < want.size() ? want.at(i).second : 0;
        if (sid != wid) {
            if (idDiffs < 5)
                out << QString("  row %1: save id %2, scr id %3\n").arg(i).arg(sid).arg(wid);
            ++idDiffs;
        }
        if (sst != wst) {
            ++stateDiffs;
            out << QString("  row %1: state save=%2 scr=%3  (written by the game at runtime)\n")
                       .arg(i).arg(sst).arg(wst);
        }
    }
    if (idDiffs) {
        out << "FAIL: " << idDiffs << " id mismatches - this save is not from that map\n";
        return 1;
    }
    out << QString("CITY MATCH OK - all %1 ids identical to the .scr\n").arg(want.size());
    if (stateDiffs)
        out << QString("note: %1 state value(s) differ; the game overwrites these at runtime\n")
                   .arg(stateDiffs);
    return 0;
}

// Create a save from scratch and re-read it, to prove the generated bytes parse.
static int makeNew(const QString &dataDir, const QString &dir, int slot, int arena, QTextStream &out)
{
    const QString tmpl = QString("%1/plyslot%2.svg").arg(dir).arg(slot);
    SaveFile sf;
    QString err;
    if (!sf.createNew(arena, tmpl, &err)) { out << "FAIL create: " << err << "\n"; return 1; }

    ScriptFile script;
    const CityDef *city = Cities::byArena(arena);
    if (!script.load(QString("%1/%2").arg(dataDir, Cities::baseName(city->scriptFile)), &err)) {
        out << "FAIL scr: " << err << "\n"; return 1;
    }
    if (!sf.applyCity(arena, script, &err)) { out << "FAIL applyCity: " << err << "\n"; return 1; }

    const QString outSvg = QString("%1/plyslot%2_new.svg").arg(dir).arg(slot);
    const QString outDat = QString("%1/plyslot%2_new.dat").arg(dir).arg(slot);
    if (!sf.saveSvg(outSvg, &err)) { out << "FAIL write svg: " << err << "\n"; return 1; }
    if (!sf.saveDat(outDat, &err)) { out << "FAIL write dat: " << err << "\n"; return 1; }

    out << QString("=== created %1 (arena %2 = %3) ===\n")
               .arg(outSvg).arg(arena).arg(city->displayName);
    out << QString("  map='%1' style='%2' script='%3'\n")
               .arg(sf.nameAt(0x00), sf.nameAt(0x19), sf.nameAt(0x32));
    out << QString("  mission count=%1 non-empty=%2\n")
               .arg(sf.missionCountField()).arg(sf.missionUsedCount());
    out << QString("  size=%1 B (block0 %2 + %3 trailing)\n")
               .arg(sf.size()).arg(SaveFile::kBlock0Size).arg(sf.trailingBytes());

    SaveFile re;
    if (!re.loadSvg(outSvg, &err)) { out << "FAIL reread: " << err << "\n"; return 1; }
    const bool same = re.block0() == sf.block0() && re.trailing() == sf.trailing();
    out << QString("  reread: %1\n").arg(same ? "identical" : "MISMATCH");
    if (!same) return 1;
    out << "CREATE OK\n";
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("EditSaveCli");
    QTextStream out(stdout);
    // QTextStream defaults to the locale codec, so on a cp1251 console the
    // Russian names come out as mojibake and a translation bug looks like an
    // encoding bug. Force UTF-8 so redirecting to a file is reproducible.
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#endif

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QStringLiteral("Parse a GTA2 save slot and verify a byte-exact round trip."));
    parser.addHelpOption();
    QCommandLineOption dirOpt(QStringList{QStringLiteral("d"), QStringLiteral("dir")},
        QStringLiteral("Save folder (default C:/work/log/player)."), QStringLiteral("path"));
    QCommandLineOption slotOpt(QStringList{QStringLiteral("s"), QStringLiteral("slot")},
        QStringLiteral("Slot index 0..7."), QStringLiteral("n"));
    QCommandLineOption dataOpt(QStringList{QStringLiteral("D"), QStringLiteral("data")},
        QStringLiteral("Game data folder (default C:/work/GTA2_RE/bin/data)."), QStringLiteral("path"));
    QCommandLineOption checkCityOpt(QStringLiteral("check-city"),
        QStringLiteral("Rebuild the mission table from the .scr and compare it to the save."));
    QCommandLineOption newOpt(QStringList{QStringLiteral("n"), QStringLiteral("new")},
        QStringLiteral("Create a new save for the given arena (0-2)."), QStringLiteral("arena"));
    QCommandLineOption langOpt(QStringList{QStringLiteral("l"), QStringLiteral("lang")},
        QStringLiteral("Load a translation (en/ru) before printing."), QStringLiteral("code"));
    parser.addOption(dirOpt);
    parser.addOption(slotOpt);
    parser.addOption(dataOpt);
    parser.addOption(checkCityOpt);
    parser.addOption(newOpt);
    parser.addOption(langOpt);
    parser.process(app);

    // Installed before any tr() runs, and deliberately the same catalogue the
    // GUI loads, so a context mismatch shows up here rather than on screen.
    // Declared at function scope: a QTranslator destroyed while still
    // installed leaves Qt holding a dangling catalogue, and every lookup after
    // that point silently returns the untranslated source string.
    QTranslator tr;
    if (parser.isSet(langOpt)) {
        const QString code = parser.value(langOpt);
        if (code != QStringLiteral("en")) {
            const QStringList dirs = {
                QCoreApplication::applicationDirPath() + QStringLiteral("/translations"),
                QCoreApplication::applicationDirPath() + QStringLiteral("/../translations"),
                QCoreApplication::applicationDirPath() + QStringLiteral("/../build/translations"),
            };
            for (const QString &d : dirs) {
                if (tr.load(QStringLiteral("editsave_") + code, d)) {
                    app.installTranslator(&tr);
                    out << "loaded translation '" << code << "' from " << d << "\n";
                    break;
                }
            }
        }
    }

    QString dir = QStringLiteral("C:/work/log/player");
    if (parser.isSet(dirOpt))
        dir = QDir::cleanPath(parser.value(dirOpt));
    if (!QDir(dir).exists())
        dir = QDir::currentPath();

    QString data = QStringLiteral("C:/work/GTA2_RE/bin/data");
    if (parser.isSet(dataOpt))
        data = QDir::cleanPath(parser.value(dataOpt));

    int slot = 0;
    if (parser.isSet(slotOpt)) {
        bool ok = false;
        const int s = parser.value(slotOpt).toInt(&ok);
        if (ok && s >= 0 && s < 8) slot = s;
    }

    int rc;
    if (parser.isSet(newOpt)) {
        bool ok = false;
        const int a = parser.value(newOpt).toInt(&ok);
        rc = (ok && a >= 0 && a <= 2) ? makeNew(data, dir, slot, a, out)
                                      : (out << "arena must be 0..2\n", 1);
    } else if (parser.isSet(checkCityOpt)) {
        rc = checkCity(data, dir, slot, out);
    } else {
        rc = selfTest(dir, slot, out);
    }
    out.flush();
    return rc;
}
