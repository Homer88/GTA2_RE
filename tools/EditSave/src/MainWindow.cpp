#include "MainWindow.h"
#include "AppSettings.h"
#include "Cities.h"
#include "FieldEditor.h"
#include "DatTable.h"
#include "HexView.h"
#include "SettingsPage.h"
#include "ScriptFile.h"
#include "WeaponTable.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QStatusBar>
#include <QCloseEvent>
#include <QIcon>

namespace {
// Artwork lives in the qrc, so the exe carries it - no loose file to lose.
QIcon appIcon()
{
    QIcon i(QStringLiteral(":/EditSave.png"));
    if (i.isNull())
        i = QIcon(QStringLiteral(":/EditSave.ico"));
    return i;
}

QString defaultPlayerDir()
{
    // The dir the game actually uses; fall back to the repo layout if missing.
    const QStringList candidates = {
        QStringLiteral("C:/work/log/player"),
        QDir::currentPath() + QStringLiteral("/player")
    };
    for (const QString &c : candidates)
        if (QDir(c).exists())
            return c;
    return candidates.first();
}

QString defaultDataDir()
{
    // The .scr/.gmp/.sty files the mission table and map names are derived
    // from. Checked rather than hardcoded so a fresh checkout works.
    const QStringList candidates = {
        QStringLiteral("C:/work/GTA2_RE/bin/data"),
        QDir::currentPath() + QStringLiteral("/../../bin/data")
    };
    for (const QString &c : candidates)
        if (QDir(c).exists())
            return QDir::cleanPath(c);
    return candidates.first();
}
} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_playerDir(defaultPlayerDir())
{
    buildUi();
    // Reopen the slot from last session. openSlot drives the combo box, whose
    // change signal would call back into openSlot, hence the guard.
    m_updatingSlot = true;
    m_slotBox->setCurrentIndex(AppSettings::instance().lastSlot());
    m_updatingSlot = false;
    openSlot(m_slotBox->currentIndex());
}

void MainWindow::buildUi()
{
    setWindowTitle(tr("GTA2 Save Editor"));
    setWindowIcon(appIcon());
    // restoreGeometry honours a monitor arrangement that has since changed.
    const QByteArray geo = AppSettings::instance().windowGeometry();
    if (geo.isEmpty())
        resize(1000, 720);
    else
        restoreGeometry(geo);
    if (!AppSettings::instance().windowState().isEmpty())
        restoreState(AppSettings::instance().windowState());

    QWidget *central = new QWidget(this);
    QVBoxLayout *root = new QVBoxLayout(central);

    // ---- top bar: directory + slot ---------------------------------------
    QHBoxLayout *top = new QHBoxLayout;
    top->addWidget(new QLabel(tr("Save dir:"), central));
    m_dirEdit = new QLineEdit(m_playerDir, central);
    top->addWidget(m_dirEdit, 1);
    QPushButton *browse = new QPushButton(tr("..."), central);
    browse->setFixedWidth(32);
    top->addWidget(browse);

    top->addSpacing(12);
    top->addWidget(new QLabel(tr("Slot:"), central));
    m_slotBox = new QComboBox(central);
    for (int i = 0; i < 8; ++i)
        m_slotBox->addItem(tr("plyslot%1").arg(i), i);
    top->addWidget(m_slotBox);

    top->addSpacing(12);
    top->addWidget(new QLabel(tr("City:"), central));
    m_cityBox = new QComboBox(central);
    // User-facing numbering is 1-based; the save stores 0/1/2.
    for (int a = 0; a < Cities::kCityCount; ++a) {
        const CityDef *c = Cities::byArena(a);
        m_cityBox->addItem(tr("%1. %2").arg(a + 1).arg(c->displayName), a);
    }
    m_cityBox->setToolTip(tr("Switching city rewrites the map, style and script names, "
                             "the arena byte and the whole mission table from the game's "
                             "own .scr file."));
    top->addWidget(m_cityBox);
    root->addLayout(top);

    // ---- action bar -------------------------------------------------------
    QHBoxLayout *bar = new QHBoxLayout;
    m_newSave = new QPushButton(tr("New save..."), central);
    m_newSave->setToolTip(tr("Build a fresh .svg + .dat pair in the current slot"));
    m_reload  = new QPushButton(tr("Reload from disk"), central);
    m_apply   = new QPushButton(tr("Apply edits"), central);
    m_saveNow = new QPushButton(tr("Write to disk"), central);
    m_backup  = new QPushButton(tr("Backup now"), central);
    bar->addWidget(m_newSave);
    bar->addWidget(m_reload);
    bar->addWidget(m_apply);
    bar->addWidget(m_saveNow);
    bar->addWidget(m_backup);
    bar->addStretch(1);
    root->addLayout(bar);

    m_apply->setEnabled(false);
    m_saveNow->setEnabled(false);

    // ---- tabs -------------------------------------------------------------
    m_tabs = new QTabWidget(central);
    m_fields  = new FieldEditor(m_tabs);
    m_weapons = new WeaponTable(m_tabs);
    m_dat     = new DatTable(m_tabs);
    m_mission = new MissionTableView(m_tabs);
    m_hex     = new HexView(m_tabs);
    m_settings = new SettingsPage(m_tabs);
    m_tabs->addTab(m_fields,   tr("Fields"));
    m_tabs->addTab(m_weapons,  tr("Weapons"));
    m_tabs->addTab(m_dat,      tr(".dat records"));
    m_tabs->addTab(m_mission,  tr("Map fingerprint"));
    m_tabs->addTab(m_hex,      tr("Hex"));
    m_tabs->addTab(m_settings, tr("Settings"));
    root->addWidget(m_tabs, 1);

    m_status = new QLabel(central);
    root->addWidget(m_status);
    statusBar()->showMessage(tr("ready"));

    setCentralWidget(central);

    connect(browse,   &QPushButton::clicked, this, &MainWindow::onBrowseDir);
    connect(m_newSave,&QPushButton::clicked, this, &MainWindow::onNewSave);
    connect(m_reload, &QPushButton::clicked, this, &MainWindow::onReload);
    connect(m_apply,  &QPushButton::clicked, this, &MainWindow::onApply);
    connect(m_saveNow,&QPushButton::clicked, this, &MainWindow::onSaveNow);
    connect(m_backup, &QPushButton::clicked, this, &MainWindow::onBackup);
    connect(m_cityBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onCityChanged);
    connect(m_slotBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSlotChanged);
    connect(m_dirEdit, &QLineEdit::editingFinished, this, [this]{
        m_playerDir = m_dirEdit->text().trimmed();
        openSlot(m_slot);
    });

    connect(m_fields,  &FieldEditor::dirtyChanged,      this, &MainWindow::setDirty);
    connect(m_dat,     &DatTable::dirtyChanged,         this, &MainWindow::setDirty);
    connect(m_weapons, &WeaponTable::dirtyChanged,      this, &MainWindow::setDirty);

    // --- settings tab ------------------------------------------------------
    // The toolbar and the settings page both edit the save folder; route both
    // through setPlayerDir so they cannot disagree.
    connect(m_settings, &SettingsPage::playerDirChanged, this, [this](const QString &d) {
        if (QDir::cleanPath(d) == QDir::cleanPath(m_playerDir))
            return;
        if (m_dirty) {
            const auto r = QMessageBox::question(
                this, tr("Discard edits?"),
                tr("There are unsaved edits. Switch folder and lose them?"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if (r != QMessageBox::Yes)
                return;
        }
        setPlayerDir(d);
    });
    connect(this, &MainWindow::playerDirSynced, m_dirEdit, &QLineEdit::setText);

    // A field edit does not raise dirtyChanged on its own (we only apply on
    // demand), so poll the editor when the user switches tabs or hits Apply.
    connect(m_apply, &QPushButton::clicked, this, [this]{
        if (m_fields->apply()) {
            m_weapons->apply();
            m_hex->reload();
            setDirty(false);
            statusBar()->showMessage(tr("field values applied to the in-memory save - "
                                        "press \"Write to disk\" to persist"), 5000);
        }
    });
}

void MainWindow::setPlayerDir(const QString &dir)
{
    m_playerDir = dir;
    emit playerDirSynced(dir);
    AppSettings::instance().setPlayerDir(dir);
    openSlot(m_slot);
}

void MainWindow::setDirty(bool dirty)
{
    m_dirty = dirty;
    m_apply->setEnabled(dirty);
    updateStatus();
}

void MainWindow::onSlotChanged(int index)
{
    if (m_updatingSlot)
        return;
    if (index < 0 || index > 7)
        return;
    m_slot = index;
    openSlot(index);
}

void MainWindow::openSlot(int slot)
{
    if (slot < 0 || slot > 7)
        return;
    m_save = SaveFile();
    m_slot = slot;

    // Keep the combo in step without re-entering onSlotChanged.
    if (m_slotBox && m_slotBox->currentIndex() != slot) {
        const bool prev = m_updatingSlot;
        m_updatingSlot = true;
        m_slotBox->setCurrentIndex(slot);
        m_updatingSlot = prev;
    }
    const QString svg = QString("%1/plyslot%2.svg").arg(m_playerDir).arg(slot);
    const QString dat = QString("%1/plyslot%3.dat").arg(m_playerDir).arg(slot);

    QString err;
    const bool gotSvg = m_save.loadSvg(svg, &err);
    if (!gotSvg)
        statusBar()->showMessage(err, 8000);
    const bool gotDat = m_save.loadDat(dat, &err);
    if (!gotSvg && !gotDat) {
        QMessageBox::warning(this, tr("Slot %1").arg(slot),
                             tr("Neither file could be read.\n\n%1\n\n"
                                "Check the save directory above.").arg(err));
    }

    m_fields->setSave(&m_save);
    m_weapons->setSave(&m_save);
    m_dat->setSave(&m_save);
    m_mission->setSave(&m_save);
    m_hex->setSave(&m_save);
    m_dat->setEnabled(gotDat);
    m_fields->setEnabled(gotSvg);
    m_weapons->setEnabled(gotSvg);
    m_mission->setEnabled(gotSvg);
    m_hex->setEnabled(gotSvg || gotDat);

    // Reflect the loaded save's city, not the last one the user picked.
    if (m_cityBox) {
        m_updatingCity = true;
        m_cityBox->setCurrentIndex(gotSvg
            ? qBound(0, int(m_save.u8(0x4B)), Cities::kCityCount - 1) : 0);
        m_updatingCity = false;
        m_cityBox->setEnabled(gotSvg);
    }

    m_dirty = false;
    m_apply->setEnabled(false);
    m_saveNow->setEnabled(gotSvg || gotDat);

    // Remember where we were so the next launch reopens the same save.
    AppSettings &cfg = AppSettings::instance();
    cfg.setLastSlot(slot);
    if (m_dirEdit)
        cfg.setPlayerDir(m_playerDir);
    cfg.sync();

    updateStatus();
}

void MainWindow::updateStatus()
{
    QStringList parts;
    if (m_save.hasSvg()) {
        parts << tr("map=%1  city=%2  money=%3")
                     .arg(m_save.nameAt(0x00))
                     .arg(m_save.u8(0x4B))
                     .arg(m_save.u32(0x64));
    } else {
        parts << tr("no .svg");
    }
    if (m_save.hasDat())
        parts << tr(".dat '%1' loaded").arg(m_save.datPlayerName());
    else
        parts << tr("no .dat");
    if (m_dirty)
        parts << tr("** unsaved edits **");
    m_status->setText(parts.join(tr("   |   ")));
}

void MainWindow::onBrowseDir()
{
    const QString d = QFileDialog::getExistingDirectory(this, tr("Select the player save folder"),
                                                        m_playerDir);
    if (!d.isEmpty())
        setPlayerDir(d);
}

void MainWindow::onReload()
{
    if (m_dirty) {
        const auto r = QMessageBox::question(this, tr("Discard edits?"),
            tr("There are unsaved edits. Reload from disk and lose them?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (r != QMessageBox::Yes)
            return;
    }
    openSlot(m_slot);
}

void MainWindow::onApply()
{
    m_fields->apply();
    m_weapons->apply();
    m_dat->apply();
    m_hex->reload();
    setDirty(false);
    statusBar()->showMessage(tr("applied to the in-memory save"), 4000);
}

void MainWindow::onBackup()
{
    const QString dir = m_playerDir + QStringLiteral("/../exp");
    if (!QDir().mkpath(dir)) {
        QMessageBox::warning(this, tr("Backup failed"),
                             tr("Cannot create %1").arg(QDir(dir).absolutePath()));
        return;
    }
    const QString stamp = QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss");
    int n = 0;
    for (const QString &ext : { QStringLiteral("svg"), QStringLiteral("dat") }) {
        const QString src = QString("%1/plyslot%2.%3").arg(m_playerDir).arg(m_slot).arg(ext);
        if (!QFile::exists(src)) continue;
        const QString dst = QString("%1/plyslot%2_%3.%4").arg(dir).arg(m_slot).arg(stamp).arg(ext);
        if (QFile::copy(src, dst)) ++n;
    }
    statusBar()->showMessage(tr("backed up %1 file(s) to %2").arg(n).arg(QDir(dir).absolutePath()), 6000);
}

// ---------------------------------------------------------------------------
// city switching
// ---------------------------------------------------------------------------
bool MainWindow::syncCity(int arena, QString *error)
{
    if (!m_save.hasSvg()) {
        if (error) *error = tr("No .svg is loaded.");
        return false;
    }
    const CityDef *city = Cities::byArena(arena);
    if (!city) {
        if (error) *error = tr("Arena %1 is out of range.").arg(arena);
        return false;
    }

    ScriptFile script;
    const QString path = QString("%1/%2").arg(AppSettings::instance().dataDir(),
                                                 city->scriptFile);
    if (!script.load(path, error))
        return false;

    if (!m_save.applyCity(arena, script, error))
        return false;

    // Push the new values into every view so the user sees the result.
    m_fields->setSave(&m_save);
    m_weapons->setSave(&m_save);
    m_mission->setSave(&m_save);
    m_hex->setSave(&m_save);
    updateStatus();
    return true;
}

void MainWindow::onCityChanged(int index)
{
    if (m_updatingCity || index < 0)
        return;
    const int arena = m_cityBox->itemData(index).toInt();
    if (!m_save.hasSvg()) {
        statusBar()->showMessage(tr("Load a save before switching city"), 5000);
        return;
    }
    if (m_save.u8(0x4B) == arena) {
        updateStatus();
        return;
    }
    if (m_dirty) {
        const auto r = QMessageBox::question(this, tr("Discard edits?"),
            tr("There are unsaved edits. Switch city and lose them?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (r != QMessageBox::Yes) {
            m_updatingCity = true;
            m_cityBox->setCurrentIndex(m_save.u8(0x4B));
            m_updatingCity = false;
            return;
        }
    }

    QString err;
    if (!syncCity(arena, &err)) {
        QMessageBox::warning(this, tr("City switch failed"), err);
        m_updatingCity = true;
        m_cityBox->setCurrentIndex(m_save.u8(0x4B));
        m_updatingCity = false;
        return;
    }

    // The mission table is derived, so the change is applied immediately and
    // only needs "Write to disk" to persist.
    setDirty(true);
    const CityDef *c = Cities::byArena(arena);
    statusBar()->showMessage(
        tr("Switched to %1: names rewritten and %2 mission rows rebuilt from %3. "
           "Press \"Write to disk\" to save.")
            .arg(c->displayName).arg(m_save.missionUsedCount())
            .arg(Cities::baseName(c->scriptFile)), 10000);
}

// ---------------------------------------------------------------------------
// new save
// ---------------------------------------------------------------------------
QString MainWindow::findTemplate(int arena) const
{
    const CityDef *city = Cities::byArena(arena);
    if (!city)
        return QString();
    QString fallback;
    for (int s = 0; s < 8; ++s) {
        const QString p = QString("%1/plyslot%2.svg").arg(m_playerDir).arg(s);
        if (!QFile::exists(p))
            continue;
        if (fallback.isEmpty())
            fallback = p;
        SaveFile probe;
        QString err;
        if (probe.loadSvg(p, &err) && Cities::byFileName(probe.nameAt(0x00)) == city)
            return p;
    }
    return fallback;
}

void MainWindow::onNewSave()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("New save"));
    auto *form = new QFormLayout(&dlg);

    auto *slotBox = new QComboBox(&dlg);
    for (int i = 0; i < 8; ++i)
        slotBox->addItem(tr("plyslot%1").arg(i), i);
    slotBox->setCurrentIndex(m_slot);
    form->addRow(tr("Slot:"), slotBox);

    auto *cityBox = new QComboBox(&dlg);
    for (int a = 0; a < Cities::kCityCount; ++a) {
        const CityDef *c = Cities::byArena(a);
        cityBox->addItem(tr("%1. %2").arg(a + 1).arg(c->displayName), a);
    }
    cityBox->setCurrentIndex(m_cityBox->currentIndex());
    form->addRow(tr("City:"), cityBox);

    auto *tmplEdit = new QLineEdit(&dlg);
    auto *tmplRow = new QWidget(&dlg);
    auto *tmplLay = new QHBoxLayout(tmplRow);
    tmplLay->setContentsMargins(0, 0, 0, 0);
    auto *tmplBrowse = new QPushButton(tr("..."), tmplRow);
    tmplBrowse->setFixedWidth(32);
    tmplLay->addWidget(tmplEdit, 1);
    tmplLay->addWidget(tmplBrowse);
    form->addRow(tr("Template:"), tmplRow);
    form->addRow(QString(), new QLabel(
        tr("The three trailing map-constant blocks are copied from an existing save. "
           "Pick any save from the selected city; block0 is built from scratch."),
        &dlg));

    auto *info = new QLabel(&dlg);
    info->setWordWrap(true);
    info->setStyleSheet(QStringLiteral("color: palette(mid);"));
    form->addRow(info);

    const int arena = cityBox->currentData().toInt();
    tmplEdit->setText(findTemplate(arena));
    const CityDef *c0 = Cities::byArena(arena);
    info->setText(tr("Will write %1/plyslot%2.svg and .dat for %3.")
                      .arg(m_playerDir).arg(slotBox->currentData().toInt())
                      .arg(c0->displayName));

    connect(tmplBrowse, &QPushButton::clicked, &dlg, [&]{
        const QString p = QFileDialog::getOpenFileName(
            &dlg, tr("Pick a template save"), m_playerDir,
            tr("GTA2 saves (*.svg)"));
        if (!p.isEmpty())
            tmplEdit->setText(p);
    });
    // Keep the suggested template in step with the city.
    connect(cityBox, QOverload<int>::of(&QComboBox::currentIndexChanged), &dlg, [&](int){
        tmplEdit->setText(findTemplate(cityBox->currentData().toInt()));
    });
    connect(slotBox, QOverload<int>::of(&QComboBox::currentIndexChanged), &dlg, [&]{
        const CityDef *c = Cities::byArena(cityBox->currentData().toInt());
        info->setText(tr("Will write %1/plyslot%2.svg and .dat for %3.")
                          .arg(m_playerDir).arg(slotBox->currentData().toInt())
                          .arg(c->displayName));
    });

    auto *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
    bb->button(QDialogButtonBox::Ok)->setText(tr("Create"));
    connect(bb, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(bb, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    form->addRow(bb);

    if (dlg.exec() != QDialog::Accepted)
        return;

    const int slot  = slotBox->currentData().toInt();
    const int arenaSel = cityBox->currentData().toInt();
    const CityDef *city = Cities::byArena(arenaSel);
    if (!city) {
        QMessageBox::warning(this, tr("New save failed"), tr("Unknown city."));
        return;
    }

    // Refuse to clobber an occupied slot without a backup and a confirmation.
    const QString svgPath = QString("%1/plyslot%2.svg").arg(m_playerDir).arg(slot);
    const QString datPath = QString("%1/plyslot%3.dat").arg(m_playerDir).arg(slot);
    const bool occupied = QFile::exists(svgPath) || QFile::exists(datPath);
    if (occupied) {
        const auto r = QMessageBox::question(
            this, tr("Overwrite slot %1?").arg(slot),
            tr("Slot %1 already contains a save. A timestamped backup is made first, "
               "then the slot is replaced. Continue?").arg(slot),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (r != QMessageBox::Yes)
            return;
    }
    if (occupied) {
        m_slot = slot;
        onBackup();
    }

    SaveFile fresh;
    QString err;
    if (!fresh.createNew(arenaSel, tmplEdit->text().trimmed(), &err)) {
        QMessageBox::warning(this, tr("New save failed"), err);
        return;
    }
    ScriptFile script;
    if (!script.load(QString("%1/%2").arg(AppSettings::instance().dataDir(),
                                           city->scriptFile), &err)) {
        QMessageBox::warning(this, tr("New save failed"), err);
        return;
    }
    if (!fresh.applyCity(arenaSel, script, &err)) {
        QMessageBox::warning(this, tr("New save failed"), err);
        return;
    }
    if (!fresh.saveSvg(svgPath, &err) || !fresh.saveDat(datPath, &err)) {
        QMessageBox::warning(this, tr("New save failed"), err);
        return;
    }

    openSlot(slot);
    statusBar()->showMessage(
        tr("Created %1: %2, %3 mission rows, fresh .dat with no locations unlocked.")
            .arg(svgPath, city->displayName).arg(fresh.missionUsedCount()), 10000);
}

void MainWindow::onSaveNow()
{
    if (!writeBack(true))
        QMessageBox::critical(this, tr("Write failed"),
                              tr("Could not write the save. See the status bar for details."));
}

bool MainWindow::writeBack(bool withBackup)
{
    // Pull any pending widget values into the save first.
    m_fields->apply();
    m_weapons->apply();
    m_dat->apply();

    if (withBackup && AppSettings::instance().autoBackup())
        onBackup();

    const QString svg = m_save.svgPath().isEmpty()
        ? QString("%1/plyslot%2.svg").arg(m_playerDir).arg(m_slot) : m_save.svgPath();
    const QString dat = m_save.datPath().isEmpty()
        ? QString("%1/plyslot%3.dat").arg(m_playerDir).arg(m_slot) : m_save.datPath();

    QString err;
    if (m_save.hasSvg() && !m_save.saveSvg(svg, &err)) {
        statusBar()->showMessage(err, 10000);
        return false;
    }
    if (m_save.hasDat() && !m_save.saveDat(dat, &err)) {
        statusBar()->showMessage(err, 10000);
        return false;
    }
    m_hex->reload();
    setDirty(false);
    statusBar()->showMessage(tr("written: %1").arg(svg), 6000);
    return true;
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    if (m_dirty && AppSettings::instance().confirmOnExit()) {
        const auto r = QMessageBox::question(this, tr("Quit?"),
            tr("There are unsaved edits. Quit anyway?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (r != QMessageBox::Yes) { ev->ignore(); return; }
    }
    AppSettings &cfg = AppSettings::instance();
    cfg.setWindowGeometry(saveGeometry());
    cfg.setWindowState(saveState());
    cfg.sync();
    ev->accept();
}
