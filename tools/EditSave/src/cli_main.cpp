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
#include "SaveFile.h"
#include "FieldDefs.h"

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
    out << QString("  city=%1  level=0x%2  gang=%3\n")
               .arg(sf.u8(0x4B)).arg(sf.u8(0x4C), 2, 16, QChar('0')).arg(sf.u8(0x4D));
    out << QString("  money=%1  multiplier=%2  health=%3  lives=%4  wanted=%5  tokens=%6\n")
               .arg(sf.u32(0x64)).arg(sf.u32(0x68)).arg(sf.u16(0x6C))
               .arg(sf.u8(0xD4)).arg(sf.u16(0xE0)).arg(sf.u32(0x744));
    out << "  powerups[17] = " << joinRange(sf, 0x6E, 17, 2) << "\n";
    out << "  gangRespect  = " << joinRange(sf, 0xC9, 10, 1) << "\n";
    out << "  ammo[15]     = " << joinRange(sf, 0xBA, 15, 1) << "\n";
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

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("EditSaveCli");
    QTextStream out(stdout);

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QStringLiteral("Parse a GTA2 save slot and verify a byte-exact round trip."));
    parser.addHelpOption();
    QCommandLineOption dirOpt(QStringList{QStringLiteral("d"), QStringLiteral("dir")},
        QStringLiteral("Save folder (default C:/work/log/player)."), QStringLiteral("path"));
    QCommandLineOption slotOpt(QStringList{QStringLiteral("s"), QStringLiteral("slot")},
        QStringLiteral("Slot index 0..7."), QStringLiteral("n"));
    parser.addOption(dirOpt);
    parser.addOption(slotOpt);
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
        if (ok && s >= 0 && s < 8) slot = s;
    }

    const int rc = selfTest(dir, slot, out);
    out.flush();
    return rc;
}
