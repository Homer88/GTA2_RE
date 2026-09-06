#include "MainWindow.h"

#include <QApplication>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QSplitter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileInfo>
#include <QFile>
#include <QIODevice>

#include <cstdio>

// ---------------------------------------------------------------------------
// Конструктор
// ---------------------------------------------------------------------------
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_updating(false)
	, m_currentWeapon(-1)
{
	buildUi();
	setWindowTitle(tr("GTA2 WeaponEditor"));
	m_weaponInfo.LoadDefaults();
	reloadWeaponList();
}

// ---------------------------------------------------------------------------
// Построение интерфейса
// ---------------------------------------------------------------------------
void MainWindow::buildUi()
{
	QToolBar* tb = addToolBar(tr("File"));
	tb->addAction(tr("Open..."), this, &MainWindow::openFile);
	tb->addAction(tr("Save"),   this, &MainWindow::saveFile);
	tb->addAction(tr("Save As..."), this, &MainWindow::saveFileAs);
	tb->addSeparator();
	tb->addAction(tr("Load Defaults"), this, &MainWindow::loadDefaults);

	QSplitter* split = new QSplitter(this);

	// --- Левая панель: список оружия ---
	QWidget* left = new QWidget(split);
	QVBoxLayout* lv = new QVBoxLayout(left);
	m_weaponList = new QListWidget(left);
	lv->addWidget(m_weaponList);
	connect(m_weaponList, SIGNAL(currentRowChanged(int)), this, SLOT(onWeaponSelected(int)));

	// --- Правая панель: параметры ---
	QWidget* right = new QWidget(split);
	QGridLayout* g = new QGridLayout(right);

	// Имя типа
	g->addWidget(new QLabel(tr("Weapon Type:"), right), 0, 0);
	m_typeName = new QLabel(tr("-"), right);
	QFont f = m_typeName->font();
	f.setBold(true);
	m_typeName->setFont(f);
	g->addWidget(m_typeName, 0, 1, 1, 3);

	// max_ammo
	g->addWidget(new QLabel(tr("Max Ammo (display):"), right), 1, 0);
	m_sbMaxAmmo = new QSpinBox(right);
	m_sbMaxAmmo->setRange(0, 999);
	g->addWidget(m_sbMaxAmmo, 1, 1);
	connect(m_sbMaxAmmo, SIGNAL(valueChanged(int)), this, SLOT(onMaxAmmoChanged(int)));

	// ammo_per_pickup
	g->addWidget(new QLabel(tr("Ammo Per Pickup:"), right), 2, 0);
	m_sbAmmoPickup = new QSpinBox(right);
	m_sbAmmoPickup->setRange(0, 999);
	g->addWidget(m_sbAmmoPickup, 2, 1);
	connect(m_sbAmmoPickup, SIGNAL(valueChanged(int)), this, SLOT(onAmmoPickupChanged(int)));

	// Разделитель
	QGroupBox* reloadBox = new QGroupBox(tr("Reload (frames)"), right);
	QGridLayout* rl = new QGridLayout(reloadBox);
	rl->addWidget(new QLabel(tr("SMG mode:"), reloadBox), 0, 0);
	m_sbReloadSmg = new QSpinBox(reloadBox);
	m_sbReloadSmg->setRange(0, 255);
	rl->addWidget(m_sbReloadSmg, 0, 1);
	connect(m_sbReloadSmg, SIGNAL(valueChanged(int)), this, SLOT(onReloadSmgChanged(int)));

	rl->addWidget(new QLabel(tr("Normal:"), reloadBox), 1, 0);
	m_sbReloadNormal = new QSpinBox(reloadBox);
	m_sbReloadNormal->setRange(0, 255);
	rl->addWidget(m_sbReloadNormal, 1, 1);
	connect(m_sbReloadNormal, SIGNAL(valueChanged(int)), this, SLOT(onReloadNormalChanged(int)));
	g->addWidget(reloadBox, 3, 0, 1, 4);

	// Fire rate
	QGroupBox* fireBox = new QGroupBox(tr("Fire Rate (frames)"), right);
	QGridLayout* fl = new QGridLayout(fireBox);
	fl->addWidget(new QLabel(tr("SMG mode:"), fireBox), 0, 0);
	m_sbFireSmg = new QSpinBox(fireBox);
	m_sbFireSmg->setRange(0, 255);
	fl->addWidget(m_sbFireSmg, 0, 1);
	connect(m_sbFireSmg, SIGNAL(valueChanged(int)), this, SLOT(onFireSmgChanged(int)));

	fl->addWidget(new QLabel(tr("Normal:"), fireBox), 1, 0);
	m_sbFireNormal = new QSpinBox(fireBox);
	m_sbFireNormal->setRange(0, 255);
	fl->addWidget(m_sbFireNormal, 1, 1);
	connect(m_sbFireNormal, SIGNAL(valueChanged(int)), this, SLOT(onFireNormalChanged(int)));
	g->addWidget(fireBox, 4, 0, 1, 4);

	// Флаги
	QGroupBox* flagBox = new QGroupBox(tr("Flags"), right);
	QGridLayout* fg = new QGridLayout(flagBox);
	m_chkExplosive = new QCheckBox(tr("Explosive"), flagBox);
	fg->addWidget(m_chkExplosive, 0, 0);
	connect(m_chkExplosive, &QCheckBox::toggled, this, &MainWindow::onExplosiveToggled);

	m_chkCarWeapon = new QCheckBox(tr("Car Weapon"), flagBox);
	fg->addWidget(m_chkCarWeapon, 0, 1);
	connect(m_chkCarWeapon, &QCheckBox::toggled, this, &MainWindow::onCarWeaponToggled);
	g->addWidget(flagBox, 5, 0, 1, 4);

	// Пояснение
	QLabel* hint = new QLabel(tr(
		"max_ammo / ammo_per_pickup: display value (raw = value * 10)\n"
		"reload / fire: game frames"), right);
	hint->setStyleSheet("color: gray;");
	g->addWidget(hint, 6, 0, 1, 4);

	g->setRowStretch(7, 1);

	split->addWidget(left);
	split->addWidget(right);
	split->setStretchFactor(0, 1);
	split->setStretchFactor(1, 2);
	setCentralWidget(split);

	// Строка состояния
	m_status = new QLabel(tr("Loaded default weapon parameters."), this);
	statusBar()->addWidget(m_status);

	resize(700, 480);
}

// ---------------------------------------------------------------------------
// Файл: открыть .gwn
// ---------------------------------------------------------------------------
void MainWindow::openFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Weapon Info"), QString(),
	                                            tr("GTA2 Weapon Info (*.gwn *.txt)"));
	if (path.isEmpty()) return;

	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot open file:\n%1").arg(path));
		return;
	}
	QByteArray bytes = f.readAll();
	f.close();

	gta2::WeaponInfoFile info;
	if (!info.ParseText(std::string(bytes.constData(), (size_t)bytes.size()))) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot parse weapon info file:\n%1").arg(path));
		return;
	}

	m_weaponInfo = info;
	m_filePath = path;
	reloadWeaponList();
	updateWindowTitle();
	m_status->setText(tr("Loaded %1 weapon types from %2")
	                  .arg((int)m_weaponInfo.Weapons().size())
	                  .arg(QFileInfo(path).fileName()));
}

// ---------------------------------------------------------------------------
// Файл: сохранить
// ---------------------------------------------------------------------------
void MainWindow::saveFile()
{
	if (m_filePath.isEmpty()) {
		saveFileAs();
		return;
	}

	applyWeaponFromPanel(m_currentWeapon);
	std::string text = m_weaponInfo.SaveText();

	QFile f(m_filePath);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot write file:\n%1").arg(m_filePath));
		return;
	}
	f.write(text.data(), (qint64)text.size());
	f.close();

	m_weaponInfo.SetDirty();
	m_status->setText(tr("Saved %1 bytes to %2").arg(text.size()).arg(QFileInfo(m_filePath).fileName()));
	updateWindowTitle();
}

void MainWindow::saveFileAs()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save Weapon Info"), QString(),
	                                            tr("GTA2 Weapon Info (*.gwn)"));
	if (path.isEmpty()) return;
	if (!path.endsWith(QLatin1String(".gwn"), Qt::CaseInsensitive))
		path += QLatin1String(".gwn");
	m_filePath = path;
	saveFile();
}

// ---------------------------------------------------------------------------
// Загрузить значения по умолчанию
// ---------------------------------------------------------------------------
void MainWindow::loadDefaults()
{
	m_weaponInfo.LoadDefaults();
	m_filePath.clear();
	reloadWeaponList();
	updateWindowTitle();
	m_status->setText(tr("Loaded default weapon parameters (28 types)."));
}

// ---------------------------------------------------------------------------
// Список оружия
// ---------------------------------------------------------------------------
void MainWindow::reloadWeaponList()
{
	m_updating = true;
	m_weaponList->clear();
	const std::vector<gta2::WeaponParams>& weapons = m_weaponInfo.Weapons();
	for (size_t i = 0; i < weapons.size(); i++) {
		const gta2::WeaponParams& w = weapons[i];
		QString item = QString("%1  %2").arg(i, 2).arg(QString::fromUtf8(w.name.c_str()));
		m_weaponList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::onWeaponSelected(int index)
{
	if (m_updating) return;
	if (m_currentWeapon >= 0 && m_currentWeapon != index)
		applyWeaponFromPanel(m_currentWeapon);
	m_currentWeapon = index;
	if (index >= 0) loadWeaponToPanel(index);
	m_status->setText(index >= 0 ? tr("Editing weapon type %1").arg(index) : tr("No weapon selected"));
}

// ---------------------------------------------------------------------------
// Загрузка данных выбранного оружия в панель
// ---------------------------------------------------------------------------
void MainWindow::loadWeaponToPanel(int index)
{
	if (index < 0 || index >= (int)m_weaponInfo.Weapons().size()) return;
	const gta2::WeaponParams& w = m_weaponInfo.Weapons()[index];

	m_updating = true;
	m_typeName->setText(QString::fromUtf8(w.name.c_str()));
	m_sbMaxAmmo->setValue(w.max_ammo);
	m_sbAmmoPickup->setValue(w.ammo_per_pickup);
	m_sbReloadSmg->setValue(w.reload_time_smg);
	m_sbReloadNormal->setValue(w.reload_time_normal);
	m_sbFireSmg->setValue(w.fire_smg);
	m_sbFireNormal->setValue(w.fire_normal);
	m_chkExplosive->setChecked(w.is_explosive != 0);
	m_chkCarWeapon->setChecked(w.is_car_weapon != 0);
	m_updating = false;
}

// ---------------------------------------------------------------------------
// Применение панели к данным
// ---------------------------------------------------------------------------
void MainWindow::applyWeaponFromPanel(int index)
{
	if (index < 0 || index >= (int)m_weaponInfo.Weapons().size()) return;
	gta2::WeaponParams& w = m_weaponInfo.Weapons()[index];

	w.max_ammo = m_sbMaxAmmo->value();
	w.ammo_per_pickup = m_sbAmmoPickup->value();
	w.reload_time_smg = m_sbReloadSmg->value();
	w.reload_time_normal = m_sbReloadNormal->value();
	w.fire_smg = m_sbFireSmg->value();
	w.fire_normal = m_sbFireNormal->value();
	w.is_explosive = m_chkExplosive->isChecked() ? 1 : 0;
	w.is_car_weapon = m_chkCarWeapon->isChecked() ? 1 : 0;
}

// ---------------------------------------------------------------------------
// Обработчики изменений
// ---------------------------------------------------------------------------
void MainWindow::onMaxAmmoChanged(int)       { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onAmmoPickupChanged(int)    { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onReloadSmgChanged(int)     { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onReloadNormalChanged(int)  { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onFireSmgChanged(int)       { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onFireNormalChanged(int)    { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onExplosiveToggled(bool)    { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }
void MainWindow::onCarWeaponToggled(bool)    { if (!m_updating && m_currentWeapon >= 0) applyWeaponFromPanel(m_currentWeapon); }

// ---------------------------------------------------------------------------
// Вспомогательное
// ---------------------------------------------------------------------------
void MainWindow::updateWindowTitle()
{
	QString t = tr("GTA2 WeaponEditor");
	if (!m_filePath.isEmpty()) t += QString(" - %1").arg(QFileInfo(m_filePath).fileName());
	setWindowTitle(t);
}
