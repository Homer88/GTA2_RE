#pragma once

#include <QWidget>
class SaveFile;
class QTableWidget;
class QPlainTextEdit;
class QComboBox;
class QLabel;
class QSpinBox;
// ---------------------------------------------------------------------------
// Two views that exist because of what the reverse engineering found:
//
//  * MissionTableView shows block0 0x134..0x5E3 as 300 x {u16 id, u16 extra}.
//    It is a MAP FINGERPRINT and must stay read-only. MissionManager::SaveFile
//    calls sub_47EE70 first, which rebuilds the whole table from the live
//    Script buffer, and StartMission returns a pointer into that raw buffer
//    rather than a live object. The id column is byte-for-byte the set of
//    type-275/276 records in data\<city>.scr (verified: wil 155/155 identical,
//    bil 107/107 ids identical), and the second u16 is the static +8 of those
//    records. Player progress is NOT stored here - see the .dat tab.
//
//  * HexView shows the whole file so anything not in the manifest can still be
//    inspected, including the three trailing map-constant blocks.
// ---------------------------------------------------------------------------
class MissionTableView : public QWidget
{
    Q_OBJECT
public:
    explicit MissionTableView(QWidget *parent = nullptr);
    void setSave(SaveFile *save);
    void reload();

private:
    void buildUi();

    SaveFile     *m_save = nullptr;
    QTableWidget *m_table = nullptr;
    QLabel       *m_summary = nullptr;
};

class HexView : public QWidget
{
    Q_OBJECT
public:
    enum class Target { Block0, SvgFile, Dat };
    explicit HexView(QWidget *parent = nullptr);
    void setSave(SaveFile *save);
    void setTarget(Target t);
    void reload();

private:
    void buildUi();
    SaveFile      *m_save = nullptr;
    QPlainTextEdit *m_text = nullptr;
    QComboBox     *m_target = nullptr;
};
