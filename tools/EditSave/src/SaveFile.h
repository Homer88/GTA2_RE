#pragma once

#include <QByteArray>
#include <QString>
#include <QVector>

// ---------------------------------------------------------------------------
// Raw container for one GTA2 player slot.
//
// Layout, as proven against the retail code in dump/IDA/gta2.exe.c:
//
//   plyslotN.svg  = block0 (1864 B) + three length-prefixed trailing blocks
//                   [u32 len1][data1][u32 len2][data2][u32 len3][data3]
//                   block0 is built by MissionManager::sub_475CA0 and written by
//                   MissionManager::SaveFile; the trailing blocks come from
//                   MapRelatedStruct::sub_4642A0 and are byte-identical between
//                   saves, i.e. map constants, not player state.
//
//   plyslotN.dat  = 18 B header + 12 records of 9 B { u8 flag; u32 best; u32 last }
//                   from PlayerData::WriteFileNamePlayer (a3 = 126). Record index
//                   encodes location: arena = idx / 4, sub = idx % 4.
//                   best/last are money snapshots, not a score.
//
// Everything is little-endian (x86 target), so we assemble integers by hand
// instead of relying on QDataStream's stream-level endianness switch.
// ---------------------------------------------------------------------------
class SaveFile
{
public:
    static constexpr int kBlock0Size   = 1864;
    static constexpr int kTrailingNum  = 3;
    static constexpr int kDatHeader    = 18;
    static constexpr int kDatRecSize   = 9;
    static constexpr int kDatRecCount  = 12;
    static constexpr int kDatSize      = kDatHeader + kDatRecCount * kDatRecSize; // 126

    SaveFile();

    // ---- whole-file IO ---------------------------------------------------
    // .svg and .dat are independent: a slot may legitimately have only one of
    // them, so each is loaded and stored on its own.
    bool loadSvg(const QString &path, QString *error);
    bool loadDat(const QString &path, QString *error);
    bool saveSvg(const QString &path, QString *error) const;
    bool saveDat(const QString &path, QString *error) const;

    bool hasSvg() const { return !m_block0.isEmpty(); }
    bool hasDat() const { return !m_dat.isEmpty(); }

    const QString &svgPath() const { return m_svgPath; }
    const QString &datPath() const { return m_datPath; }

    int  svgFileSize()  const { return kBlock0Size + trailingBytes(); }
    int  trailingBytes() const;

    // ---- block0 scalar accessors ----------------------------------------
    quint8  u8 (int off) const;
    quint16 u16(int off) const;
    quint32 u32(int off) const;

    void setU8 (int off, quint8  v);
    void setU16(int off, quint16 v);
    void setU32(int off, quint32 v);

    // Fixed 25-byte NUL-padded name fields at 0x00 / 0x19 / 0x32.
    QString nameAt(int off) const;
    void    setNameAt(int off, const QString &s);

    // ---- .dat record accessors ------------------------------------------
    int  datFlag(int rec) const;
    quint32 datBest(int rec) const;
    quint32 datLast(int rec) const;
    void    setDatFlag(int rec, quint8 v);
    void    setDatBest(int rec, quint32 v);
    void    setDatLast(int rec, quint32 v);
    QString datPlayerName() const;
    void    setDatPlayerName(const QString &s);

    // ---- mission table (map-derived, 300 x {u16 id, u16 extra}) ---------
    struct MissionRow {
        int     index = 0;
        int     off   = 0;
        quint16 id    = 0;
        quint16 extra = 0;
        bool    used  = false;
    };
    QVector<MissionRow> missions() const;
    int missionCountField() const;                 // u16 at 0x12A
    int missionUsedCount() const;

    const QByteArray &block0() const { return m_block0; }
    const QVector<QByteArray> &trailing() const { return m_trailing; }

    // ---- raw hex access for the hex viewer -------------------------------
    int size() const { return kBlock0Size + trailingBytes(); }
    quint8 rawAt(int off) const;

private:
    QByteArray            m_block0;                  // exactly kBlock0Size bytes
    QVector<QByteArray>   m_trailing;                // data payloads, no length prefix
    QByteArray            m_dat;                     // exactly kDatSize bytes
    QString               m_svgPath;
    QString               m_datPath;
};
