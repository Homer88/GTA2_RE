#include "SaveFile.h"

#include <QFile>
#include <QObject>
#include <QFileInfo>
#include <QDir>

namespace {
inline quint16 rd16(const QByteArray &b, int off)
{
    return static_cast<quint16>(static_cast<quint8>(b[off]))
         | static_cast<quint16>(static_cast<quint8>(b[off + 1])) << 8;
}
inline quint32 rd32(const QByteArray &b, int off)
{
    return static_cast<quint32>(static_cast<quint8>(b[off]))
         | static_cast<quint32>(static_cast<quint8>(b[off + 1])) << 8
         | static_cast<quint32>(static_cast<quint8>(b[off + 2])) << 16
         | static_cast<quint32>(static_cast<quint8>(b[off + 3])) << 24;
}
inline void wr16(QByteArray &b, int off, quint16 v)
{
    b[off]     = static_cast<char>(v & 0xFF);
    b[off + 1] = static_cast<char>((v >> 8) & 0xFF);
}
inline void wr32(QByteArray &b, int off, quint32 v)
{
    b[off]     = static_cast<char>(v & 0xFF);
    b[off + 1] = static_cast<char>((v >> 8) & 0xFF);
    b[off + 2] = static_cast<char>((v >> 16) & 0xFF);
    b[off + 3] = static_cast<char>((v >> 24) & 0xFF);
}
} // namespace

SaveFile::SaveFile() = default;

int SaveFile::trailingBytes() const
{
    int n = 0;
    for (const QByteArray &b : m_trailing)
        n += b.size();
    return n;
}

// ---------------------------------------------------------------------------
// .svg
// ---------------------------------------------------------------------------
bool SaveFile::loadSvg(const QString &path, QString *error)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        if (error) *error = QObject::tr("cannot open %1: %2").arg(path, f.errorString());
        return false;
    }
    const QByteArray all = f.readAll();
    f.close();

    if (all.size() < kBlock0Size) {
        if (error) *error = QObject::tr("%1 is %2 B, block0 alone needs %3 B")
                                .arg(QFileInfo(path).fileName()).arg(all.size()).arg(kBlock0Size);
        return false;
    }

    m_block0 = all.left(kBlock0Size);
    m_trailing.clear();

    // [u32 len][data] x3. Guard against a truncated or nonsense length so a
    // damaged file cannot make us allocate wildly.
    int pos = kBlock0Size;
    for (int i = 0; i < kTrailingNum; ++i) {
        if (pos + 4 > all.size()) {
            if (error) *error = QObject::tr("%1 ends inside trailing block %2")
                                    .arg(QFileInfo(path).fileName()).arg(i + 1);
            m_trailing.clear();
            return false;
        }
        const quint32 len = rd32(all, pos);
        pos += 4;
        if (len > static_cast<quint32>(all.size() - pos)) {
            if (error) *error = QObject::tr("%1: trailing block %2 claims %3 B but only %4 B left")
                                    .arg(QFileInfo(path).fileName()).arg(i + 1)
                                    .arg(len).arg(all.size() - pos);
            m_trailing.clear();
            return false;
        }
        m_trailing.append(all.mid(pos, static_cast<int>(len)));
        pos += static_cast<int>(len);
    }

    m_svgPath = path;
    return true;
}

bool SaveFile::saveSvg(const QString &path, QString *error) const
{
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (error) *error = QObject::tr("cannot write %1: %2").arg(path, f.errorString());
        return false;
    }
    if (f.write(m_block0) != kBlock0Size) {
        if (error) *error = QObject::tr("short write on block0");
        return false;
    }
    for (const QByteArray &b : m_trailing) {
        char lenbuf[4];
        const quint32 blen = static_cast<quint32>(b.size());
        for (int i = 0; i < 4; ++i) lenbuf[i] = char((blen >> (8 * i)) & 0xFF);
        if (f.write(lenbuf, 4) != 4) { if (error) *error = QObject::tr("short write on length"); return false; }
        if (!b.isEmpty() && f.write(b) != b.size()) {
            if (error) *error = QObject::tr("short write on trailing block");
            return false;
        }
    }
    f.close();
    return true;
}

// ---------------------------------------------------------------------------
// .dat
// ---------------------------------------------------------------------------
bool SaveFile::loadDat(const QString &path, QString *error)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        if (error) *error = QObject::tr("cannot open %1: %2").arg(path, f.errorString());
        return false;
    }
    const QByteArray all = f.readAll();
    f.close();

    if (all.size() != kDatSize) {
        if (error) *error = QObject::tr("%1 is %2 B, expected %3 B")
                                .arg(QFileInfo(path).fileName()).arg(all.size()).arg(kDatSize);
        return false;
    }
    m_dat    = all;
    m_datPath = path;
    return true;
}

bool SaveFile::saveDat(const QString &path, QString *error) const
{
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (error) *error = QObject::tr("cannot write %1: %2").arg(path, f.errorString());
        return false;
    }
    const bool ok = (f.write(m_dat) == m_dat.size());
    f.close();
    if (!ok && error) *error = QObject::tr("short write on %1").arg(path);
    return ok;
}

// ---------------------------------------------------------------------------
// block0 accessors
// ---------------------------------------------------------------------------
quint8  SaveFile::u8 (int off) const { return static_cast<quint8>(m_block0[off]); }
quint16 SaveFile::u16(int off) const { return rd16(m_block0, off); }
quint32 SaveFile::u32(int off) const { return rd32(m_block0, off); }

void SaveFile::setU8 (int off, quint8  v) { m_block0[off] = static_cast<char>(v); }
void SaveFile::setU16(int off, quint16 v) { wr16(m_block0, off, v); }
void SaveFile::setU32(int off, quint32 v) { wr32(m_block0, off, v); }

QString SaveFile::nameAt(int off) const
{
    QByteArray s = m_block0.mid(off, 25);
    const int z = s.indexOf('\0');
    if (z >= 0) s.truncate(z);
    return QString::fromLatin1(s);
}

void SaveFile::setNameAt(int off, const QString &s)
{
    QByteArray raw = s.toLatin1();
    if (raw.size() > 24) raw.truncate(24);          // keep room for the NUL
    raw.append(QByteArray(25 - raw.size(), '\0'));  // NUL-pad the rest
    m_block0.replace(off, 25, raw);
}

quint8 SaveFile::rawAt(int off) const
{
    if (off < 0 || off >= kBlock0Size)
        return static_cast<quint8>(m_trailing.at(0).at(off - kBlock0Size));
    return static_cast<quint8>(m_block0[off]);
}

// ---------------------------------------------------------------------------
// .dat accessors
// ---------------------------------------------------------------------------
static inline int recOff(int rec) { return SaveFile::kDatHeader + rec * SaveFile::kDatRecSize; }

int      SaveFile::datFlag(int rec) const { return static_cast<quint8>(m_dat[recOff(rec)]); }
quint32  SaveFile::datBest(int rec) const { return rd32(m_dat, recOff(rec) + 1); }
quint32  SaveFile::datLast(int rec) const { return rd32(m_dat, recOff(rec) + 5); }

void SaveFile::setDatFlag(int rec, quint8 v)  { m_dat[recOff(rec)] = static_cast<char>(v); }
void SaveFile::setDatBest(int rec, quint32 v)  { wr32(m_dat, recOff(rec) + 1, v); }
void SaveFile::setDatLast(int rec, quint32 v)  { wr32(m_dat, recOff(rec) + 5, v); }

QString SaveFile::datPlayerName() const
{
    // Fixed 12-byte UTF-16LE field; decode explicitly rather than relying on
    // QString::fromUtf16 so the byte order is visible and endian-independent.
    QString s;
    for (int i = 0; i < 6; ++i) {
        const ushort c = static_cast<ushort>(static_cast<quint8>(m_dat[i * 2]))
                       | static_cast<ushort>(static_cast<quint8>(m_dat[i * 2 + 1])) << 8;
        if (c == 0)
            break;
        s.append(QChar(c));
    }
    return s;
}

void SaveFile::setDatPlayerName(const QString &s)
{
    // 5 characters plus a terminator have to fit in 12 bytes.
    for (int i = 0; i < 6; ++i) {
        const ushort c = (i < s.size()) ? s.at(i).unicode() : 0;
        m_dat[i * 2]     = static_cast<char>(c & 0xFF);
        m_dat[i * 2 + 1] = static_cast<char>((c >> 8) & 0xFF);
    }
}

// ---------------------------------------------------------------------------
// mission table
// ---------------------------------------------------------------------------
QVector<SaveFile::MissionRow> SaveFile::missions() const
{
    QVector<MissionRow> rows;
    rows.reserve(300);
    for (int i = 0; i < 300; ++i) {
        const int off = 0x134 + i * 4;   // interleaved: {u16 id, u16 extra}
        MissionRow r;
        r.index = i;
        r.off   = off;
        r.id    = rd16(m_block0, off);
        r.extra = rd16(m_block0, off + 2);
        r.used  = (r.id != 0);
        rows.append(r);
    }
    return rows;
}

int SaveFile::missionCountField() const { return rd16(m_block0, 0x12A); }

int SaveFile::missionUsedCount() const
{
    int n = 0;
    for (int i = 0; i < 300; ++i)
        if (rd16(m_block0, 0x134 + i * 4) != 0) ++n;
    return n;
}
