#include "SettingsPage.h"
#include "AppSettings.h"

#include <QApplication>
#include <QCheckBox>
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

QWidget *SettingsPage::buildUi()
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(10);

    // --- interface scale --------------------------------------------------
    auto *scaleBox = new QGroupBox(tr("Интерфейс"), this);
    auto *scaleLay = new QVBoxLayout(scaleBox);

    auto *scaleRow = new QHBoxLayout;
    auto *scaleLabel = new QLabel(tr("Масштаб:"), scaleBox);

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
    auto *pathBox = new QGroupBox(tr("Папка сохранений"), this);
    auto *pathLay = new QGridLayout(pathBox);

    m_dirEdit = new QLineEdit(pathBox);
    m_dirEdit->setPlaceholderText(QStringLiteral("C:/work/log/player"));
    m_dirEdit->setToolTip(tr("Папка с файлами plyslotN.svg / plyslotN.dat"));

    auto *browse = new QPushButton(tr("Обзор..."), pathBox);
    auto *useCurrent = new QPushButton(tr("Текущая папка"), pathBox);
    useCurrent->setToolTip(tr("Подставить рабочую папку приложения"));

    pathLay->addWidget(m_dirEdit,     0, 0, 1, 2);
    pathLay->addWidget(browse,        0, 2);
    pathLay->addWidget(useCurrent,    1, 2);
    pathLay->setColumnStretch(0, 1);
    root->addWidget(pathBox);

    // --- behaviour --------------------------------------------------------
    auto *behBox = new QGroupBox(tr("Поведение"), this);
    auto *behLay = new QVBoxLayout(behBox);

    m_autoBackup = new QCheckBox(tr("Автоматически делать резервную копию перед записью"), behBox);
    m_confirm   = new QCheckBox(tr("Спрашивать подтверждение при выходе с несохранёнными правками"), behBox);
    m_hexCols   = new QCheckBox(tr("Показывать колонку с hex-адресами в просмотре"), behBox);

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

    auto *openCfg = new QPushButton(tr("Открыть папку"), this);
    auto *reset   = new QPushButton(tr("Сбросить всё"), this);
    reset->setToolTip(tr("Вернуть значения по умолчанию.\n"
                         "Файлы сохранений при этом не затрагиваются."));

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

    return this;
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
    m_fontInfo->setText(tr("Шрифт: %1, %2 pt, экран %3 DPI")
                            .arg(QFontInfo(scaled).family())
                            .arg(scaled.pointSizeF(), 0, 'f', 1)
                            .arg(primaryDpi()));

    switch (pct) {
    case 100:
        m_scaleHint->setText(tr("Обычный размер."));
        break;
    case AppSettings::kMinScale:
    case AppSettings::kMaxScale:
        m_scaleHint->setText(tr("Крайнее значение диапазона."));
        break;
    default:
        m_scaleHint->setText(pct < 100 ? tr("Уменьшенный интерфейс — больше данных на экране.")
                                       : tr("Увеличенный интерфейс — удобнее на высоких DPI."));
        break;
    }

    m_configPath->setText(tr("Конфигурация: %1").arg(cfg.configFilePath()));
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
        this, tr("Выберите папку сохранений"), QDir::toNativeSeparators(cur));
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
