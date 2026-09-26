#pragma once

#include <QByteArray>
#include <QFont>
#include <QSettings>
#include <QString>

class QApplication;
class QWidget;

// ---------------------------------------------------------------------------
// Persisted user preferences.
//
// Scaling note: the obvious implementation ("take the current font, multiply
// its point size, apply") compounds on every change - 100% -> 150% -> 225% ->
// 337% - because each pass reads back the result of the previous one. So the
// *base* font is captured once on first run and stored in the config, and every
// apply recomputes from that immutable reference. Applying the same percentage
// twice is then guaranteed to be a no-op.
//
// Config file: <AppConfigLocation>/EditSave.ini, i.e. %APPDATA%\GTA2RE\EditSave
// on Windows. Setting EDITSAVE_CONFIG to a file path overrides that, which makes
// the whole app portable (ship bin/ + one ini, no registry).
// ---------------------------------------------------------------------------
class AppSettings
{
public:
    static AppSettings &instance();

    // --- UI scale ---------------------------------------------------------
    int  uiScalePercent() const { return m_uiScale; }
    void setUiScalePercent(int percent);

    // Recompute the application font from the stored base font. Safe to call
    // repeatedly; live-updates open windows.
    void applyScale(QApplication &app);

    // A copy of the reference font, for the settings page to preview against.
    QFont baseFont() const;
    static QFont scaledFont(const QFont &base, int percent);

    // --- window state -----------------------------------------------------
    QByteArray windowGeometry() const { return m_geometry; }
    void setWindowGeometry(const QByteArray &g) { m_geometry = g; }
    QByteArray windowState() const { return m_state; }
    void setWindowState(const QByteArray &s) { m_state = s; }

    // --- session ----------------------------------------------------------
    QString playerDir() const { return m_playerDir; }
    void setPlayerDir(const QString &dir) { m_playerDir = dir; }
    int  lastSlot() const { return m_lastSlot; }
    void setLastSlot(int slot) { m_lastSlot = slot; }

    // --- behaviour --------------------------------------------------------
    bool autoBackup() const { return m_autoBackup; }
    void setAutoBackup(bool on) { m_autoBackup = on; }
    bool confirmOnExit() const { return m_confirmOnExit; }
    void setConfirmOnExit(bool on) { m_confirmOnExit = on; }
    bool showHexColumns() const { return m_showHexColumns; }
    void setShowHexColumns(bool on) { m_showHexColumns = on; }

    // --- maintenance ------------------------------------------------------
    void sync();
    void resetToDefaults();
    QString configFilePath() const;

    static const int kMinScale = 70;
    static const int kMaxScale = 300;

private:
    AppSettings();

    void load();
    void writeAll();

    mutable QSettings m_settings;
    QFont             m_baseFont;
    bool              m_haveBaseFont = false;

    int      m_uiScale       = 100;
    QByteArray m_geometry;
    QByteArray m_state;
    QString  m_playerDir;
    int      m_lastSlot      = 0;
    bool     m_autoBackup    = true;
    bool     m_confirmOnExit = true;
    bool     m_showHexColumns = true;
};
