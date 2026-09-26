#include "AppSettings.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFontInfo>
#include <QProcessEnvironment>
#include <QStandardPaths>

namespace {
constexpr auto kKeyScale      = "ui/scalePercent";
constexpr auto kKeyBaseFont   = "ui/baseFont";
constexpr auto kKeyGeometry   = "window/geometry";
constexpr auto kKeyState      = "window/state";
constexpr auto kKeyPlayerDir  = "session/playerDir";
constexpr auto kKeyLastSlot   = "session/lastSlot";
constexpr auto kKeyAutoBackup = "behaviour/autoBackup";
constexpr auto kKeyConfirm    = "behaviour/confirmOnExit";
constexpr auto kKeyHexColumns = "behaviour/showHexColumns";
} // namespace

// ---------------------------------------------------------------------------
// QSettings picks a NativeFormat ini (registry-backed) on Windows unless the
// path already carries a recognised suffix. Always passing an explicit .ini
// path is what makes the file portable and readable, so force IniFormat.
// ---------------------------------------------------------------------------
static QSettings makeSettings()
{
    const QString override =
        QProcessEnvironment::systemEnvironment().value(QStringLiteral("EDITSAVE_CONFIG"));
    if (!override.isEmpty()) {
        const QFileInfo fi(override);
        if (!fi.absoluteDir().exists())
            QDir().mkpath(fi.absolutePath());
        return QSettings(fi.absoluteFilePath(), QSettings::IniFormat);
    }
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(dir);
    return QSettings(dir + QStringLiteral("/EditSave.ini"), QSettings::IniFormat);
}

AppSettings::AppSettings()
    : m_settings(makeSettings())
{
    load();
}

AppSettings &AppSettings::instance()
{
    static AppSettings s;
    return s;
}

void AppSettings::load()
{
    m_settings.beginGroup(QStringLiteral(""));
    m_uiScale = qBound(kMinScale,
                       m_settings.value(QLatin1String(kKeyScale), 100).toInt(), kMaxScale);

    const QString spec = m_settings.value(QLatin1String(kKeyBaseFont)).toString();
    if (!spec.isEmpty()) {
        QFont f;
        if (f.fromString(spec)) {
            m_baseFont = f;
            m_haveBaseFont = true;
        }
    }
    m_geometry   = m_settings.value(QLatin1String(kKeyGeometry)).toByteArray();
    m_state      = m_settings.value(QLatin1String(kKeyState)).toByteArray();
    m_playerDir  = m_settings.value(QLatin1String(kKeyPlayerDir),
                                    QStringLiteral("C:/work/log/player")).toString();
    m_lastSlot   = qBound(0, m_settings.value(QLatin1String(kKeyLastSlot), 0).toInt(), 7);
    m_autoBackup    = m_settings.value(QLatin1String(kKeyAutoBackup), true).toBool();
    m_confirmOnExit = m_settings.value(QLatin1String(kKeyConfirm), true).toBool();
    m_showHexColumns = m_settings.value(QLatin1String(kKeyHexColumns), true).toBool();
    m_settings.endGroup();
}

void AppSettings::writeAll()
{
    m_settings.beginGroup(QStringLiteral(""));
    m_settings.setValue(QLatin1String(kKeyScale), m_uiScale);
    m_settings.setValue(QLatin1String(kKeyGeometry), m_geometry);
    m_settings.setValue(QLatin1String(kKeyState), m_state);
    m_settings.setValue(QLatin1String(kKeyPlayerDir), m_playerDir);
    m_settings.setValue(QLatin1String(kKeyLastSlot), m_lastSlot);
    m_settings.setValue(QLatin1String(kKeyAutoBackup), m_autoBackup);
    m_settings.setValue(QLatin1String(kKeyConfirm), m_confirmOnExit);
    m_settings.setValue(QLatin1String(kKeyHexColumns), m_showHexColumns);
    m_settings.endGroup();
    m_settings.sync();
}

QString AppSettings::configFilePath() const
{
    return m_settings.fileName();
}

QFont AppSettings::baseFont() const
{
    return m_haveBaseFont ? m_baseFont : QApplication::font();
}

QFont AppSettings::scaledFont(const QFont &base, int percent)
{
    QFont f = base;
    // Point size, not pixel size: pixel size would ignore the user's DPI and
    // render the same physical glyph count at the wrong size on a 4K screen.
    const double basePt = base.pointSizeF() > 0.0 ? base.pointSizeF() : base.pointSize();
    f.setPointSizeF(qMax(1.0, basePt * percent / 100.0));
    // QFont merges by point size only when the family matches; be explicit so
    // Qt cannot hand back a cached font from the old size.
    f.setFamilies(base.families());
    return f;
}

void AppSettings::setUiScalePercent(int percent)
{
    const int p = qBound(kMinScale, percent, kMaxScale);
    if (p == m_uiScale)
        return;
    m_uiScale = p;
    writeAll();
}

void AppSettings::applyScale(QApplication &app)
{
    // First run: latch whatever Qt/the platform gave us as the reference.
    if (!m_haveBaseFont) {
        m_baseFont = app.font();
        m_haveBaseFont = true;
        m_settings.beginGroup(QStringLiteral(""));
        m_settings.setValue(QLatin1String(kKeyBaseFont), m_baseFont.toString());
        m_settings.endGroup();
    }
    app.setFont(scaledFont(m_baseFont, m_uiScale));
}

void AppSettings::sync()
{
    writeAll();
}

void AppSettings::resetToDefaults()
{
    m_uiScale = 100;
    m_geometry.clear();
    m_state.clear();
    m_lastSlot = 0;
    m_autoBackup = true;
    m_confirmOnExit = true;
    m_showHexColumns = true;
    m_playerDir = QStringLiteral("C:/work/log/player");
    writeAll();
}
