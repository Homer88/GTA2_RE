#include "ScriptFile.h"

#include <QFile>
#include <QFileInfo>

namespace {

inline quint16 rd16(const QByteArray &b, int off)
{
    return static_cast<quint16>(static_cast<quint8>(b.at(off)))
         | static_cast<quint16>(static_cast<quint8>(b.at(off + 1))) << 8;
}

} // namespace

ScriptFile::ScriptFile() = default;

bool ScriptFile::load(const QString &path, QString *error)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        if (error) *error = QObject::tr("Cannot open %1: %2").arg(path, f.errorString());
        m_raw.clear(); m_script.clear(); m_table.clear(); m_path.clear();
        return false;
    }
    const QByteArray all = f.readAll();
    f.close();

    if (all.size() != kFileSize) {
        if (error) *error = QObject::tr(
            "%1 is %2 bytes, expected %3. A city mission script is a fixed-size "
            "file; this does not look like one.")
            .arg(QFileInfo(path).fileName()).arg(all.size()).arg(kFileSize);
        m_raw.clear(); m_script.clear(); m_table.clear(); m_path.clear();
        return false;
    }

    m_raw    = all;
    m_script = all.mid(kScriptOffset, kScriptSize);
    m_table.resize(kSlotCount);
    for (int i = 0; i < kSlotCount; ++i)
        m_table[i] = rd16(m_raw, kTableOffset + i * 2);
    m_path = path;
    return true;
}

bool ScriptFile::slotUsed(int i) const
{
    if (i < 0 || i >= m_table.size())
        return false;
    const int off = m_table.at(i);
    return off != 0 && off + 12 <= m_script.size();
}

bool ScriptFile::record(int i, quint16 *id, quint16 *type, quint16 *state) const
{
    if (!slotUsed(i))
        return false;
    const int off = m_table.at(i);
    if (id)    *id    = rd16(m_script, off);
    if (type)  *type  = rd16(m_script, off + 2);
    if (state) *state = rd16(m_script, off + 8);
    return true;
}

QVector<QPair<quint16, quint16> > ScriptFile::markers() const
{
    QVector<QPair<quint16, quint16> > out;
    if (m_script.isEmpty())
        return out;
    for (int i = 0; i < kSlotCount; ++i) {
        const int off = m_table.at(i);
        if (off == 0 || off + 12 > m_script.size())
            continue;
        const quint16 type = rd16(m_script, off + 2);
        if (type != kMarkerTypeA && type != kMarkerTypeB)
            continue;
        if (out.size() >= 300)   // the save has exactly 300 rows
            break;
        out.append(qMakePair(rd16(m_script, off), rd16(m_script, off + 8)));
    }
    return out;
}

QVector<QPair<int, int> > ScriptFile::typeHistogram() const
{
    QVector<QPair<int, int> > hist;
    if (m_script.isEmpty())
        return hist;
    QVector<int> tally(4096, 0);
    for (int i = 0; i < kSlotCount; ++i) {
        const int off = m_table.at(i);
        if (off == 0 || off + 12 > m_script.size())
            continue;
        ++tally[rd16(m_script, off + 2)];
    }
    for (int t = 0; t < tally.size(); ++t)
        if (tally.at(t))
            hist.append(qMakePair(t, tally.at(t)));
    return hist;
}
