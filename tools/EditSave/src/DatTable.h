#pragma once

#include <QWidget>
class SaveFile;
class QTableWidget;
class QLineEdit;

// ---------------------------------------------------------------------------
// Editor for the 12 per-location records in plyslotN.dat.
//
// Layout proven by PlayerData::WriteFileNamePlayer:
//   18 B header, then 12 x 9 B { u8 flag; u32 best; u32 last; }
//
// flag is genuine player progress, not a map constant:
//   PlayerData::sub_4A8A90 sets one (arena, sub) pair's flag to 1 on completion;
//   PlayerData::sub_4A8B00 sets all 12 flags to 1 - the game's own "unlock
//   everything" routine. A real 100% save carries flag=1 on every row.
//
// best/last are money snapshots, NOT a score.
// Record index maps to location as arena = idx / 4, sub = idx % 4.
// ---------------------------------------------------------------------------
class DatTable : public QWidget
{
    Q_OBJECT
public:
    explicit DatTable(QWidget *parent = nullptr);

    void setSave(SaveFile *save);
    void reload();
    bool apply();
    void setAllFlags(quint8 v);

signals:
    void dirtyChanged(bool dirty);

private:
    void buildUi();

    SaveFile    *m_save = nullptr;
    QTableWidget *m_table = nullptr;
    QLineEdit   *m_nameEdit = nullptr;
    bool         m_dirty = false;
    bool         m_loading = false;
};
