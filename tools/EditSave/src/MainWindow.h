#pragma once

#include <QMainWindow>
#include "SaveFile.h"

class FieldEditor;
class DatTable;
class MissionTableView;
class HexView;
class SettingsPage;
class WeaponTable;
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

    // Read back by main.cpp so a language switch can rebuild the window
    // without losing which folder and slot were open.
    QString playerDir() const { return m_playerDir; }
    int     currentSlot() const { return m_slot; }

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
    void onNewSave();
    void onCityChanged(int index);
    void updateStatus();

private:
    void buildUi();
    bool writeBack(bool withBackup);
    void setDirty(bool dirty);
    void closeEvent(QCloseEvent *ev) override;

    // Writes map/style/script names, the arena byte and the whole 300-row
    // mission table for the given city. Returns false and fills `error` if
    // the .scr is missing or does not match the city.
    bool syncCity(int arena, QString *error);
    // Best existing .svg to use as the trailing-blocks template: same city
    // first, then any save at all. Empty when the folder has no saves.
    QString findTemplate(int arena) const;

    SaveFile  m_save;
    QString   m_playerDir;
    int       m_slot = 0;
    bool      m_dirty = false;
    bool      m_updatingSlot = false;

    QLineEdit *m_dirEdit   = nullptr;
    QComboBox *m_slotBox   = nullptr;
    QComboBox *m_cityBox   = nullptr;
    QPushButton *m_newSave = nullptr;
    QPushButton *m_reload  = nullptr;
    QPushButton *m_apply   = nullptr;
    QPushButton *m_saveNow = nullptr;
    QPushButton *m_backup  = nullptr;
    QLabel      *m_status  = nullptr;
    QTabWidget  *m_tabs    = nullptr;
    bool         m_updatingCity = false;

    FieldEditor      *m_fields  = nullptr;
    DatTable         *m_dat     = nullptr;
    WeaponTable      *m_weapons = nullptr;
    MissionTableView *m_mission = nullptr;
    HexView          *m_hex     = nullptr;
    SettingsPage     *m_settings = nullptr;
};
