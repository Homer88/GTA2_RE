#pragma once

#include <QByteArray>
#include <QString>
#include <QVector>

// ---------------------------------------------------------------------------
// Reader for data\<city>.scr, the mission script of a map.
//
// Proven layout, matched byte-exactly against three retail files (all 82 656 B):
//
//   +0x0000   12 000 B   u16[6000]  offset of each script record, 0 = unused
//   +0x2EE0   65 536 B   Script, the raw record pool
//   +0x12EE0       2 B   u16 size
//   +0x12EE2    5 118 B   remainder, handed to partOfLoadScrip
//
// MissionManager::StartMission(i) is literally `Script + table[i]`, and a
// record starts with { u16 id; u16 type; ...; u16 state @ +8 }.
//
// MissionManager::sub_47EE70 walks all 6000 slots on every save and keeps the
// records whose type is 275 or 276, writing {id, state} into the save block at
// 0x134. That is why the save's mission table is a byte-exact fingerprint of the
// .scr: wil yields 155/155 identical rows, bil 107/107 identical ids.
//
// Rebuilding the table here is therefore not a guess - it reproduces exactly
// what the game writes.
// ---------------------------------------------------------------------------
class ScriptFile
{
public:
    static constexpr int kTableOffset = 0x0000;
    static constexpr int kTableSize   = 12000;   // u16[6000]
    static constexpr int kSlotCount   = 6000;
    static constexpr int kScriptOffset = 0x2EE0;
    static constexpr int kScriptSize  = 65536;
    static constexpr int kSizeOffset  = 0x12EE0;
    static constexpr int kFileSize    = 82656;

    // Types sub_47EE70 keeps.
    static constexpr quint16 kMarkerTypeA = 275;
    static constexpr quint16 kMarkerTypeB = 276;

    ScriptFile();

    bool load(const QString &path, QString *error);
    bool isLoaded() const { return !m_script.isEmpty(); }
    QString path() const   { return m_path; }

    int  fileSize()   const { return m_raw.size(); }
    int  scriptSize() const { return m_script.size(); }
    int  slotCount()  const { return m_table.size(); }
    bool slotUsed(int i) const;

    // Raw record access. Returns false when the slot is unused or truncated.
    bool record(int i, quint16 *id, quint16 *type, quint16 *state) const;

    // The rows sub_47EE70 would store, in table order. Capped at 300 because
    // the save only has room for 300.
    QVector<QPair<quint16, quint16> > markers() const;

    // Every distinct record type present, with its count - for the info panel.
    QVector<QPair<int, int> > typeHistogram() const;

private:
    QByteArray            m_raw;
    QByteArray            m_script;
    QVector<quint16>      m_table;
    QString               m_path;
};
