#pragma once

#include <QWidget>
class SaveFile;
class QTableWidget;
class QPlainTextEdit;
class QComboBox;
class QLabel;

// ---------------------------------------------------------------------------
// Two read-only views that exist because of what the reverse engineering found:
//
//  * MissionTableView shows block0 0x134..0x5E3 as 300 x {u16 id, u16 extra}.
//    It is intentionally NOT editable: sub_47EE70 rebuilds this from the live
//    script on every save, and it is byte-identical between saves of different
//    maps only in the sense that it tracks the map - it is not player state.
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
