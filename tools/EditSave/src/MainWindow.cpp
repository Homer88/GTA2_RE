#include "MainWindow.h"
#include "AppSettings.h"
#include "FieldEditor.h"
#include "DatTable.h"
#include "HexView.h"
#include "SettingsPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
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
} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_playerDir(defaultPlayerDir())
{
    buildUi();
    openSlot(0);
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
    root->addLayout(top);

    // ---- action bar -------------------------------------------------------
    QHBoxLayout *bar = new QHBoxLayout;
    m_reload  = new QPushButton(tr("Reload from disk"), central);
    m_apply   = new QPushButton(tr("Apply edits"), central);
    m_saveNow = new QPushButton(tr("Write to disk"), central);
    m_backup  = new QPushButton(tr("Backup now"), central);
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
    m_dat     = new DatTable(m_tabs);
    m_mission = new MissionTableView(m_tabs);
    m_hex     = new HexView(m_tabs);
    m_settings = new SettingsPage(m_tabs);
    m_tabs->addTab(m_fields,   tr("Fields"));
    m_tabs->addTab(m_dat,      tr(".dat records"));
    m_tabs->addTab(m_mission,  tr("Mission table (read-only)"));
    m_tabs->addTab(m_hex,      tr("Hex"));
    m_tabs->addTab(m_settings, tr("Settings"));
    root->addWidget(m_tabs, 1);

    m_status = new QLabel(central);
    root->addWidget(m_status);
    statusBar()->showMessage(tr("ready"));

    setCentralWidget(central);

    connect(browse,   &QPushButton::clicked, this, &MainWindow::onBrowseDir);
    connect(m_reload, &QPushButton::clicked, this, &MainWindow::onReload);
    connect(m_apply,  &QPushButton::clicked, this, &MainWindow::onApply);
    connect(m_saveNow,&QPushButton::clicked, this, &MainWindow::onSaveNow);
    connect(m_backup, &QPushButton::clicked, this, &MainWindow::onBackup);
    connect(m_slotBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSlotChanged);
    connect(m_dirEdit, &QLineEdit::editingFinished, this, [this]{
        m_playerDir = m_dirEdit->text().trimmed();
        openSlot(m_slot);
    });

    connect(m_fields,  &FieldEditor::dirtyChanged,      this, &MainWindow::setDirty);
    connect(m_dat,     &DatTable::dirtyChanged,         this, &MainWindow::setDirty);

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
    if (index < 0) return;
    m_slot = index;
    openSlot(index);
}

void MainWindow::openSlot(int slot)
{
    m_save = SaveFile();
    m_slot = slot;
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
    m_dat->setSave(&m_save);
    m_mission->setSave(&m_save);
    m_hex->setSave(&m_save);
    m_dat->setEnabled(gotDat);
    m_fields->setEnabled(gotSvg);
    m_mission->setEnabled(gotSvg);
    m_hex->setEnabled(gotSvg || gotDat);

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
    if (m_dirty) {
        const auto r = QMessageBox::question(this, tr("Quit?"),
            tr("There are unsaved edits. Quit anyway?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (r != QMessageBox::Yes) { ev->ignore(); return; }
    }
    ev->accept();
}
