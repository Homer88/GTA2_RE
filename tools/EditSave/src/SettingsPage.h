#pragma once

#include <QWidget>

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QSpinBox;

// ---------------------------------------------------------------------------
// Settings tab.
//
// The scale control writes straight through to the live application font, so
// the window rescales while you drag it - no restart, and the immediate visual
// feedback is the whole point of exposing it as a slider. Everything else is
// ordinary persisted state.
//
// Changes are committed as they happen rather than behind an OK/Cancel pair.
// That is deliberate: the only destructive action in this app is a save-file
// write, and none of these settings can trigger one, so a Cancel button would
// imply a safety that does not exist.
// ---------------------------------------------------------------------------
class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);

signals:
    void playerDirChanged(const QString &dir);
    void showHexColumnsChanged(bool on);

private slots:
    void onScalePercentChanged(int percent);
    void onSyncSlider(int value);
    void onSyncSpin(int value);
    void onAutoBackupToggled(bool on);
    void onConfirmOnExitToggled(bool on);
    void onHexColumnsToggled(bool on);
    void onBrowseSaveDir();
    void onResetDefaults();
    void onOpenConfigDir();

private:
    QWidget *buildUi();
    void reloadFromConfig();
    void setScaleControls(int percent);
    void refreshDerivedLabels();
    void applyPlayerDir(const QString &raw);

    QSlider   *m_slider    = nullptr;
    QSpinBox  *m_spin      = nullptr;
    QLabel    *m_scaleHint = nullptr;
    QLineEdit *m_dirEdit   = nullptr;
    QCheckBox *m_autoBackup = nullptr;
    QCheckBox *m_confirm   = nullptr;
    QCheckBox *m_hexCols   = nullptr;
    QLabel    *m_configPath = nullptr;
    QLabel    *m_fontInfo  = nullptr;

    bool m_updating = false; // guards the spin<->slider signal loop
};
