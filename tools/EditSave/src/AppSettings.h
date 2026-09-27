#pragma once

#include <QByteArray>
#include <QFont>
#include <QSettings>
#include <QString>
#include <QStringList>

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

    // --- game data --------------------------------------------------------
    // Folder holding wil/ste/bil .gmp/.sty/.scr. Needed to rebuild the mission
    // table and to name a save's map; the game itself stores the same relative
    // "data\wil.gmp" style names in the .svg.
    QString dataDir() const { return m_dataDir; }
    void setDataDir(const QString &dir) { m_dataDir = dir; }

    // --- language ---------------------------------------------------------
    // "en" or "ru". The C++ source is English; "ru" loads a QTranslator.
    QString language() const { return m_language; }
    void setLanguage(const QString &code) { m_language = code; }
    static QStringList availableLanguages();

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

    // constexpr, not static const: these are passed to QWidget::setRange()
    // and qBound(), which take them by const reference, and only constexpr
    // members are implicitly inline in C++17.
    static constexpr int kMinScale = 70;
    static constexpr int kMaxScale = 300;

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
    QString  m_dataDir       = QStringLiteral("C:/work/GTA2_RE/bin/data");
    QString  m_language      = QStringLiteral("en");
    bool     m_autoBackup    = true;
    bool     m_confirmOnExit = true;
    bool     m_showHexColumns = true;
};
