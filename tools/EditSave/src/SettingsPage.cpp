#include "SettingsPage.h"
#include "AppSettings.h"
#include "Translator.h"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScreen>
#include <QSlider>
#include <QSpinBox>
#include <QUrl>
#include <QVBoxLayout>

namespace {

// Screen DPI without QApplication::desktop(), which Qt6 removed.
int primaryDpi()
{
    if (QScreen *s = QGuiApplication::primaryScreen())
        return qRound(s->logicalDotsPerInchX());
    return 96;
}

void applyCurrentScale()
{
    if (QApplication *app = qobject_cast<QApplication *>(QApplication::instance()))
        AppSettings::instance().applyScale(*app);
}

} // namespace

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    setLayout(buildUi());
    reloadFromConfig();
}

QVBoxLayout *SettingsPage::buildUi()
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(10);

    // --- interface scale --------------------------------------------------
    auto *scaleBox = new QGroupBox(tr("Interface"), this);
    auto *scaleLay = new QVBoxLayout(scaleBox);

    auto *scaleRow = new QHBoxLayout;
    auto *scaleLabel = new QLabel(tr("Scale:"), scaleBox);

    m_slider = new QSlider(Qt::Horizontal, scaleBox);
    m_slider->setRange(AppSettings::kMinScale, AppSettings::kMaxScale);
    m_slider->setSingleStep(5);
    m_slider->setPageStep(25);
    m_slider->setTickPosition(QSlider::TicksBelow);
    m_slider->setTickInterval(25);
    m_slider->setMinimumWidth(320);

    m_spin = new QSpinBox(scaleBox);
    m_spin->setRange(AppSettings::kMinScale, AppSettings::kMaxScale);
    m_spin->setSingleStep(5);
    m_spin->setSuffix(QStringLiteral(" %"));
    m_spin->setFixedWidth(88);

    scaleRow->addWidget(scaleLabel);
    scaleRow->addWidget(m_slider, 1);
    scaleRow->addWidget(m_spin);
    scaleLay->addLayout(scaleRow);

    auto *langRow = new QHBoxLayout;
    langRow->addWidget(new QLabel(tr("Language:"), scaleBox));
    m_langBox = new QComboBox(scaleBox);
    // The combo shows each language in its own name, so the list is readable
    // regardless of the currently active one.
    m_langBox->addItem(QStringLiteral("English"), QStringLiteral("en"));
    m_langBox->addItem(QString::fromUtf8("Русский"), QStringLiteral("ru"));
    m_langBox->setToolTip(tr("Takes effect immediately, no restart needed"));
    langRow->addWidget(m_langBox, 1);
    scaleLay->addLayout(langRow);

    m_scaleHint = new QLabel(scaleBox);
    m_scaleHint->setWordWrap(true);
    m_scaleHint->setStyleSheet(QStringLiteral("color: palette(mid);"));
    scaleLay->addWidget(m_scaleHint);

    m_fontInfo = new QLabel(scaleBox);
    m_fontInfo->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_fontInfo->setStyleSheet(QStringLiteral("color: palette(mid);"));
    scaleLay->addWidget(m_fontInfo);

    root->addWidget(scaleBox);

    // --- save folder ------------------------------------------------------
    auto *pathBox = new QGroupBox(tr("Save folder"), this);
    auto *pathLay = new QGridLayout(pathBox);

    m_dirEdit = new QLineEdit(pathBox);
    m_dirEdit->setPlaceholderText(QStringLiteral("C:/work/log/player"));
    m_dirEdit->setToolTip(tr("Folder holding plyslotN.svg / plyslotN.dat"));

    auto *browse = new QPushButton(tr("Browse..."), pathBox);
    auto *useCurrent = new QPushButton(tr("Current folder"), pathBox);
    useCurrent->setToolTip(tr("Use the current working folder"));

    pathLay->addWidget(m_dirEdit,     0, 0, 1, 2);
    pathLay->addWidget(browse,        0, 2);
    pathLay->addWidget(useCurrent,    1, 2);
    pathLay->setColumnStretch(0, 1);
    root->addWidget(pathBox);

    // --- game data folder -------------------------------------------------
    // Needed to rebuild the mission table when the city is switched.
    auto *dataBox = new QGroupBox(tr("Game data"), pathBox->parentWidget());
    auto *dataLay = new QGridLayout(dataBox);

    m_dataEdit = new QLineEdit(dataBox);
    m_dataEdit->setPlaceholderText(QStringLiteral("C:/work/GTA2_RE/bin/data"));
    m_dataEdit->setToolTip(tr("Folder with wil.gmp / wil.sty / wil.scr and the other two cities.\n"
                              "The mission table is rebuilt from the .scr when the city changes."));

    auto *dataBrowse = new QPushButton(tr("Browse..."), dataBox);
    dataLay->addWidget(m_dataEdit,   0, 0);
    dataLay->addWidget(dataBrowse,   0, 1);
    dataLay->setColumnStretch(0, 1);
    root->addWidget(dataBox);

    // --- behaviour --------------------------------------------------------
    auto *behBox = new QGroupBox(tr("Behaviour"), this);
    auto *behLay = new QVBoxLayout(behBox);

    m_autoBackup = new QCheckBox(tr("Make a timestamped backup before writing"), behBox);
    m_confirm   = new QCheckBox(tr("Ask for confirmation when quitting with unsaved edits"), behBox);
    m_hexCols   = new QCheckBox(tr("Show the hex address column in the viewer"), behBox);

    behLay->addWidget(m_autoBackup);
    behLay->addWidget(m_confirm);
    behLay->addWidget(m_hexCols);
    root->addWidget(behBox);

    root->addStretch(1);

    // --- footer -----------------------------------------------------------
    auto *foot = new QHBoxLayout;
    m_configPath = new QLabel(this);
    m_configPath->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_configPath->setStyleSheet(QStringLiteral("color: palette(mid);"));

    auto *openCfg = new QPushButton(tr("Open folder"), this);
    auto *reset   = new QPushButton(tr("Reset all"), this);
    reset->setToolTip(tr("Restore the default values.\n"
                         "Save files are not affected."));

    foot->addWidget(m_configPath, 1);
    foot->addWidget(openCfg);
    foot->addWidget(reset);
    root->addLayout(foot);

    // Slider and spin box are two views of one value, so they are kept in sync
    // manually. m_updating stops the resulting signal storm from recursing.
    connect(m_slider, &QSlider::valueChanged, this, &SettingsPage::onSyncSlider);
    connect(m_spin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &SettingsPage::onSyncSpin);
    connect(m_spin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &SettingsPage::onScalePercentChanged);

    connect(m_autoBackup, &QCheckBox::toggled, this, &SettingsPage::onAutoBackupToggled);
    connect(m_confirm,   &QCheckBox::toggled, this, &SettingsPage::onConfirmOnExitToggled);
    connect(m_hexCols,   &QCheckBox::toggled, this, &SettingsPage::onHexColumnsToggled);
    connect(m_langBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsPage::onLanguageChanged);
    connect(dataBrowse, &QPushButton::clicked, this, &SettingsPage::onBrowseDataDir);

    connect(browse, &QPushButton::clicked, this, &SettingsPage::onBrowseSaveDir);
    connect(useCurrent, &QPushButton::clicked, this, [this] {
        applyPlayerDir(QDir::toNativeSeparators(QDir::currentPath()));
    });
    connect(openCfg, &QPushButton::clicked, this, &SettingsPage::onOpenConfigDir);
    connect(reset,   &QPushButton::clicked, this, &SettingsPage::onResetDefaults);

    // Typing a path by hand should work too, not just the folder picker.
    connect(m_dirEdit, &QLineEdit::editingFinished, this, [this] {
        applyPlayerDir(m_dirEdit->text());
    });
    connect(m_dataEdit, &QLineEdit::editingFinished, this, [this] {
        applyDataDir(m_dataEdit->text());
    });

    return root;
}

void SettingsPage::applyDataDir(const QString &raw)
{
    if (raw.trimmed().isEmpty())
        return;
    const QString clean = QDir::cleanPath(raw);
    m_dataEdit->setText(QDir::toNativeSeparators(clean));
    AppSettings::instance().setDataDir(clean);
    AppSettings::instance().sync();
}

void SettingsPage::onBrowseDataDir()
{
    const QString cur = m_dataEdit->text().trimmed().isEmpty()
                            ? AppSettings::instance().dataDir()
                            : m_dataEdit->text();
    const QString picked = QFileDialog::getExistingDirectory(
        this, tr("Select the game data folder"), QDir::toNativeSeparators(cur));
    if (!picked.isEmpty())
        applyDataDir(picked);
}

void SettingsPage::onLanguageChanged(int index)
{
    if (m_updating)
        return;
    const QString code = m_langBox->itemData(index).toString();
    if (code.isEmpty() || code == AppSettings::instance().language())
        return;
    AppSettings::instance().setLanguage(code);
    AppSettings::instance().sync();
    // main.cpp installs the translator and re-translates every live window.
    Translator::instance().applyLanguage(code);
}

void SettingsPage::applyPlayerDir(const QString &raw)
{
    if (raw.trimmed().isEmpty())
        return;
    const QString clean = QDir::cleanPath(raw);
    m_dirEdit->setText(QDir::toNativeSeparators(clean));
    AppSettings &cfg = AppSettings::instance();
    cfg.setPlayerDir(clean);
    cfg.sync();
    emit playerDirChanged(clean);
}

void SettingsPage::reloadFromConfig()
{
    AppSettings &cfg = AppSettings::instance();
    m_updating = true;
    setScaleControls(cfg.uiScalePercent());
    m_dirEdit->setText(QDir::toNativeSeparators(cfg.playerDir()));
    m_dataEdit->setText(QDir::toNativeSeparators(cfg.dataDir()));
    const int li = m_langBox->findData(cfg.language());
    m_langBox->setCurrentIndex(li >= 0 ? li : 0);
    m_autoBackup->setChecked(cfg.autoBackup());
    m_confirm->setChecked(cfg.confirmOnExit());
    m_hexCols->setChecked(cfg.showHexColumns());
    m_updating = false;
    refreshDerivedLabels();
}

void SettingsPage::setScaleControls(int percent)
{
    m_slider->setValue(percent);
    m_spin->setValue(percent);
}

void SettingsPage::refreshDerivedLabels()
{
    AppSettings &cfg = AppSettings::instance();
    const int pct = cfg.uiScalePercent();

    const QFont scaled = AppSettings::scaledFont(cfg.baseFont(), pct);
    m_fontInfo->setText(tr("Font: %1, %2 pt, screen %3 DPI")
                            .arg(QFontInfo(scaled).family())
                            .arg(scaled.pointSizeF(), 0, 'f', 1)
                            .arg(primaryDpi()));

    switch (pct) {
    case 100:
        m_scaleHint->setText(tr("Normal size."));
        break;
    case AppSettings::kMinScale:
    case AppSettings::kMaxScale:
        m_scaleHint->setText(tr("Extreme value of the range."));
        break;
    default:
        m_scaleHint->setText(pct < 100 ? tr("Smaller interface - more data on screen.")
                                       : tr("Larger interface - easier on high-DPI displays."));
        break;
    }

    m_configPath->setText(tr("Config: %1").arg(cfg.configFilePath()));
}

void SettingsPage::onScalePercentChanged(int percent)
{
    if (m_updating)
        return;
    AppSettings &cfg = AppSettings::instance();
    cfg.setUiScalePercent(percent);
    applyCurrentScale();
    refreshDerivedLabels();
}

void SettingsPage::onSyncSlider(int value)
{
    if (m_updating)
        return;
    m_updating = true;
    m_spin->setValue(value);
    m_updating = false;
    onScalePercentChanged(value);
}

void SettingsPage::onSyncSpin(int value)
{
    if (m_updating)
        return;
    m_updating = true;
    m_slider->setValue(value);
    m_updating = false;
}

void SettingsPage::onAutoBackupToggled(bool on)
{
    AppSettings::instance().setAutoBackup(on);
}

void SettingsPage::onConfirmOnExitToggled(bool on)
{
    AppSettings::instance().setConfirmOnExit(on);
}

void SettingsPage::onHexColumnsToggled(bool on)
{
    AppSettings::instance().setShowHexColumns(on);
    emit showHexColumnsChanged(on);
}

void SettingsPage::onBrowseSaveDir()
{
    const QString cur = m_dirEdit->text().trimmed().isEmpty()
                            ? AppSettings::instance().playerDir()
                            : m_dirEdit->text();
    const QString picked = QFileDialog::getExistingDirectory(
        this, tr("Select the save folder"), QDir::toNativeSeparators(cur));
    if (!picked.isEmpty())
        applyPlayerDir(picked);
}

void SettingsPage::onOpenConfigDir()
{
    const QString file = AppSettings::instance().configFilePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(file).absolutePath()));
}

void SettingsPage::onResetDefaults()
{
    AppSettings &cfg = AppSettings::instance();
    cfg.resetToDefaults();
    applyCurrentScale();
    reloadFromConfig();
    emit playerDirChanged(cfg.playerDir());
    emit showHexColumnsChanged(cfg.showHexColumns());
}
