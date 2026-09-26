#pragma once

#include <QMainWindow>
#include "SaveFile.h"

class FieldEditor;
class DatTable;
class MissionTableView;
class HexView;
class SettingsPage;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QCloseEvent;

// ---------------------------------------------------------------------------
// Top level window: pick a slot, edit, write back.
//
// Every write goes through a timestamped backup first, because a save is the
// only irreplaceable artefact here and a bad edit bricks the game load.
// ---------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setPlayerDir(const QString &dir);
    void openSlot(int slot);

signals:
    // Emitted after the folder is accepted, so the toolbar field and the
    // settings page can both be updated from one place.
    void playerDirSynced(const QString &dir);

private slots:
    void onSlotChanged(int index);
    void onBrowseDir();
    void onReload();
    void onApply();
    void onSaveNow();
    void onBackup();
    void updateStatus();

private:
    void buildUi();
    bool writeBack(bool withBackup);
    void setDirty(bool dirty);
    void closeEvent(QCloseEvent *ev) override;

    SaveFile  m_save;
    QString   m_playerDir;
    int       m_slot = 0;
    bool      m_dirty = false;

    QLineEdit *m_dirEdit   = nullptr;
    QComboBox *m_slotBox   = nullptr;
    QPushButton *m_reload  = nullptr;
    QPushButton *m_apply   = nullptr;
    QPushButton *m_saveNow = nullptr;
    QPushButton *m_backup  = nullptr;
    QLabel      *m_status  = nullptr;
    QTabWidget  *m_tabs    = nullptr;

    FieldEditor      *m_fields  = nullptr;
    DatTable         *m_dat     = nullptr;
    MissionTableView *m_mission = nullptr;
    HexView          *m_hex     = nullptr;
    SettingsPage     *m_settings = nullptr;
};
