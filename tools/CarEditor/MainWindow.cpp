#include "MainWindow.h"

#include <QApplication>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QTabWidget>
#include <QSplitter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QFile>
#include <QIODevice>
#include <QStatusBar>
#include <QFileInfo>

#include <cstdio>

namespace {

// Доступ к полю физики по индексу (порядок совпадает со структурой CarPhysics).
// Используется, чтобы не писать 17 отдельных слотов для QDoubleSpinBox.
double PhysGet(const gta2::CarPhysics& p, int idx)
{
	switch (idx) {
	case 0: return p.mass;
	case 1: return p.front_drive_bias;
	case 2: return p.front_mass_bias;
	case 3: return p.brake_friction;
	case 4: return p.turn_in;
	case 5: return p.turn_ratio;
	case 6: return p.rear_end_stability;
	case 7: return p.handbrake_slide_value;
	case 8: return p.thrust;
	case 9: return p.max_speed;
	case 10: return p.anti_strength;
	case 11: return p.skid_threshhold;
	case 12: return p.gear1_multiplier;
	case 13: return p.gear2_multiplier;
	case 14: return p.gear3_multiplier;
	case 15: return p.gear2_speed;
	case 16: return p.gear3_speed;
	}
	return 0.0;
}

void PhysSet(gta2::CarPhysics& p, int idx, double v)
{
	switch (idx) {
	case 0: p.mass = v; break;
	case 1: p.front_drive_bias = v; break;
	case 2: p.front_mass_bias = v; break;
	case 3: p.brake_friction = v; break;
	case 4: p.turn_in = v; break;
	case 5: p.turn_ratio = v; break;
	case 6: p.rear_end_stability = v; break;
	case 7: p.handbrake_slide_value = v; break;
	case 8: p.thrust = v; break;
	case 9: p.max_speed = v; break;
	case 10: p.anti_strength = v; break;
	case 11: p.skid_threshhold = v; break;
	case 12: p.gear1_multiplier = v; break;
	case 13: p.gear2_multiplier = v; break;
	case 14: p.gear3_multiplier = v; break;
	case 15: p.gear2_speed = v; break;
	case 16: p.gear3_speed = v; break;
	}
}

const char* const kPhysNames[17] = {
	"mass", "front drive bias", "front mass bias", "brake friction",
	"turn in", "turn ratio", "rear end stability", "handbrake slide value",
	"thrust", "max_speed", "anti strength", "skid threshhold",
	"gear1 multiplier", "gear2 multiplier", "gear3 multiplier",
	"gear2 speed", "gear3 speed"
};

const char* const kFlagNames[16] = {
	"bit 0", "bit 1", "bit 2", "bit 3", "bit 4", "bit 5", "bit 6", "bit 7",
	"bit 8", "bit 9", "bit 10", "bit 11", "bit 12", "bit 13", "bit 14", "bit 15"
};

} // namespace

// ---------------------------------------------------------------------------
// Конструктор
// ---------------------------------------------------------------------------
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_updating(false)
	, m_currentCar(-1)
	, m_listStale(false)
{
	buildUi();
	setWindowTitle(tr("GTA2 CarEditor"));
}

// ---------------------------------------------------------------------------
// Построение интерфейса
// ---------------------------------------------------------------------------
void MainWindow::buildUi()
{
	QToolBar* tb = addToolBar(tr("File"));
	tb->addAction(tr("Open STY..."), this, &MainWindow::openSty);
	tb->addAction(tr("Save STY"),   this, &MainWindow::saveSty);
	tb->addSeparator();
	tb->addAction(tr("Open GCI..."),  this, &MainWindow::openGci);
	tb->addAction(tr("Save GCI"),     this, &MainWindow::saveGci);

	QSplitter* split = new QSplitter(this);

	// --- Левая панель: список машин ---
	QWidget* left = new QWidget(split);
	QVBoxLayout* lv = new QVBoxLayout(left);
	m_carList = new QListWidget(left);
	lv->addWidget(m_carList);

	QHBoxLayout* lb = new QHBoxLayout();
	QPushButton* bAdd = new QPushButton(tr("+"), left);
	QPushButton* bDel = new QPushButton(tr("-"), left);
	lb->addWidget(bAdd);
	lb->addWidget(bDel);
	lb->addStretch();
	lv->addLayout(lb);
	connect(m_carList, SIGNAL(currentRowChanged(int)), this, SLOT(onCarSelected(int)));
	connect(bAdd, &QPushButton::clicked, this, &MainWindow::onAddCar);
	connect(bDel, &QPushButton::clicked, this, &MainWindow::onDeleteCar);

	// --- Правая панель: свойства ---
	QTabWidget* tabs = new QTabWidget(split);

	// Вкладка графика (CARI)
	QWidget* gfx = new QWidget(tabs);
	QGridLayout* g = new QGridLayout(gfx);

	auto addSpin = [&](int row, int col, const char* label, QSpinBox*& out,
	                    int min, int max) {
		g->addWidget(new QLabel(tr(label), gfx), row, col);
		out = new QSpinBox(gfx);
		out->setRange(min, max);
		g->addWidget(out, row, col + 1);
		connect(out, SIGNAL(valueChanged(int)), this, SLOT(onGfxFieldChanged(int)));
	};
	auto addSignedSpin = [&](int row, int col, const char* label, QSpinBox*& out,
	                          int min, int max) {
		g->addWidget(new QLabel(tr(label), gfx), row, col);
		out = new QSpinBox(gfx);
		out->setRange(min, max);
		out->setSingleStep(1);
		g->addWidget(out, row, col + 1);
		connect(out, SIGNAL(valueChanged(int)), this, SLOT(onGfxFieldChanged(int)));
	};

	addSpin(0, 0, "model",  m_sbModel, 0, 255);
	addSpin(0, 2, "sprite", m_sbSprite, 0, 255);
	addSpin(1, 0, "w",      m_sbW, 0, 255);
	addSpin(1, 2, "h",      m_sbH, 0, 255);
	addSpin(2, 0, "passengers", m_sbPassengers, 0, 255);
	addSpin(2, 2, "wreck",     m_sbWreck, 0, 255);
	addSpin(3, 0, "rating",    m_sbRating, 0, 255);

	addSignedSpin(4, 0, "front wheel",   m_sbFwOff, -128, 127);
	addSignedSpin(4, 2, "rear wheel",    m_sbRwOff, -128, 127);
	addSignedSpin(5, 0, "front window",  m_sbFwinOff, -128, 127);
	addSignedSpin(5, 2, "rear window",   m_sbRwinOff, -128, 127);

	// Флаги (16 бит)
	QGroupBox* flagsBox = new QGroupBox(tr("Flags (bits 0-7 = info_flags, 8-15 = info_flags_2)"), gfx);
	QGridLayout* fl = new QGridLayout(flagsBox);
	for (int i = 0; i < 16; i++) {
		m_chkFlag[i] = new QCheckBox(tr(kFlagNames[i]), flagsBox);
		fl->addWidget(m_chkFlag[i], i / 4, i % 4);
		connect(m_chkFlag[i], &QCheckBox::toggled, this, &MainWindow::onFlagToggled);
	}
	g->addWidget(flagsBox, 6, 0, 1, 4);

	// Перекраски
	QHBoxLayout* remapHead = new QHBoxLayout();
	remapHead->addWidget(new QLabel(tr("remaps count:"), gfx));
	m_sbRemapCount = new QSpinBox(gfx);
	m_sbRemapCount->setRange(0, 255);
	remapHead->addWidget(m_sbRemapCount);
	remapHead->addStretch();
	g->addLayout(remapHead, 7, 0, 1, 4);
	m_tblRemap = new QTableWidget(0, 1, gfx);
	m_tblRemap->setHorizontalHeaderLabels(QStringList() << tr("remap value"));
	m_tblRemap->horizontalHeader()->setStretchLastSection(true);
	m_tblRemap->setMaximumHeight(110);
	g->addWidget(m_tblRemap, 8, 0, 1, 4);
	connect(m_sbRemapCount, SIGNAL(valueChanged(int)), this, SLOT(onRemapCountChanged(int)));
	connect(m_tblRemap, &QTableWidget::cellChanged, this, &MainWindow::onRemapCellChanged);

	// Двери
	QHBoxLayout* doorHead = new QHBoxLayout();
	doorHead->addWidget(new QLabel(tr("doors count:"), gfx));
	m_sbDoorCount = new QSpinBox(gfx);
	m_sbDoorCount->setRange(0, 255);
	doorHead->addWidget(m_sbDoorCount);
	doorHead->addStretch();
	g->addLayout(doorHead, 9, 0, 1, 4);
	m_tblDoor = new QTableWidget(0, 2, gfx);
	m_tblDoor->setHorizontalHeaderLabels(QStringList() << tr("rx") << tr("ry"));
	m_tblDoor->horizontalHeader()->setStretchLastSection(true);
	m_tblDoor->setMaximumHeight(110);
	g->addWidget(m_tblDoor, 10, 0, 1, 4);
	connect(m_sbDoorCount, SIGNAL(valueChanged(int)), this, SLOT(onDoorCountChanged(int)));
	connect(m_tblDoor, &QTableWidget::cellChanged, this, &MainWindow::onDoorCellChanged);

	g->setRowStretch(11, 1);
	tabs->addTab(gfx, tr("Graphics (CARI)"));

	// Вкладка физика (GCI)
	QWidget* phy = new QWidget(tabs);
	QGridLayout* p = new QGridLayout(phy);
	p->addWidget(new QLabel(tr("name:"), phy), 0, 0);
	m_physName = new QLabel(tr("-"), phy);
	p->addWidget(m_physName, 0, 1);
	p->addWidget(new QLabel(tr("turbo:"), phy), 0, 2);
	m_sbTurbo = new QSpinBox(phy);
	m_sbTurbo->setRange(0, 1);
	p->addWidget(m_sbTurbo, 0, 3);
	p->addWidget(new QLabel(tr("value:"), phy), 0, 4);
	m_sbValue = new QSpinBox(phy);
	m_sbValue->setRange(0, 100000);
	p->addWidget(m_sbValue, 0, 5);
	connect(m_sbTurbo, SIGNAL(valueChanged(int)), this, SLOT(onPhysIntChanged(int)));
	connect(m_sbValue, SIGNAL(valueChanged(int)), this, SLOT(onPhysIntChanged(int)));

	QGroupBox* physBox = new QGroupBox(tr("Physics"), phy);
	QGridLayout* pl = new QGridLayout(physBox);
	for (int i = 0; i < 17; i++) {
		pl->addWidget(new QLabel(tr(kPhysNames[i]), physBox), i, 0);
		m_dbPhys[i] = new QDoubleSpinBox(physBox);
		m_dbPhys[i]->setRange(-1000000.0, 1000000.0);
		m_dbPhys[i]->setDecimals(6);
		pl->addWidget(m_dbPhys[i], i, 1);
		connect(m_dbPhys[i], SIGNAL(valueChanged(double)), this, SLOT(onPhysDoubleChanged(double)));
	}
	p->addWidget(physBox, 1, 0, 1, 6);
	p->setRowStretch(2, 1);
	tabs->addTab(phy, tr("Physics (GCI)"));

	split->addWidget(left);
	split->addWidget(tabs);
	split->setStretchFactor(0, 1);
	split->setStretchFactor(1, 3);
	setCentralWidget(split);

	// Строка состояния
	m_status = new QLabel(tr("Open a .sty file to start."), this);
	statusBar()->addWidget(m_status);

	resize(900, 620);
}

// ---------------------------------------------------------------------------
// Файл: открыть .sty (графика + CARI)
// ---------------------------------------------------------------------------
void MainWindow::openSty()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open STY"), QString(),
	                                            tr("GTA2 style (*.sty)"));
	if (path.isEmpty()) return;

	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot open file:\n%1").arg(path));
		return;
	}
	QByteArray bytes = f.readAll();
	f.close();

	gta2::StyFile sty;
	if (!sty.Parse((const unsigned char*)bytes.constData(), (size_t)bytes.size())) {
		QMessageBox::warning(this, tr("Error"), tr("Not a valid GTA2 .sty file:\n%1").arg(path));
		return;
	}

	const gta2::StySection* cari = sty.FindSection("CARI");
	if (!cari) {
		QMessageBox::warning(this, tr("Error"), tr("File has no CARI section:\n%1").arg(path));
		return;
	}

	gta2::CarInfoList cars;
	if (!cars.Parse(cari->data.data(), cari->data.size())) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot parse CARI section:\n%1").arg(path));
		return;
	}

	m_sty  = sty;
	m_cars = cars;
	m_styPath = path;
	m_currentCar = -1;
	reloadCarList();
	updateWindowTitle();
	m_status->setText(tr("Loaded %1 cars from %2")
	                  .arg(m_cars.Cars().size()).arg(QFileInfo(path).fileName()));
}

// ---------------------------------------------------------------------------
// Файл: сохранить .sty (пишет CARI обратно в секцию)
// ---------------------------------------------------------------------------
void MainWindow::saveSty()
{
	if (m_styPath.isEmpty()) {
		m_styPath = QFileDialog::getSaveFileName(this, tr("Save STY"), QString(),
		                                         tr("GTA2 style (*.sty)"));
		if (m_styPath.isEmpty()) return;
		if (!m_styPath.endsWith(QLatin1String(".sty"), Qt::CaseInsensitive))
			m_styPath += QLatin1String(".sty");
	}

	applyCarFromPanel(m_currentCar);

	std::vector<unsigned char> cariData = m_cars.Save();
	std::vector<unsigned char> cariVec(cariData.begin(), cariData.end());
	m_sty.SetSection("CARI", cariVec);
	std::vector<unsigned char> out = m_sty.Save();

	QFile f(m_styPath);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot write file:\n%1").arg(m_styPath));
		return;
	}
	f.write((const char*)out.data(), (qint64)out.size());
	f.close();

	m_status->setText(tr("Saved STY (%1 bytes)").arg(out.size()));
	updateWindowTitle();
}

// ---------------------------------------------------------------------------
// Файл: открыть .gci (физика)
// ---------------------------------------------------------------------------
void MainWindow::openGci()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open GCI"), QString(),
	                                            tr("GTA2 car info (*.gci)"));
	if (path.isEmpty()) return;

	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot open file:\n%1").arg(path));
		return;
	}
	QByteArray bytes = f.readAll();
	f.close();

	gta2::GciFile gci;
	if (!gci.ParseText(std::string(bytes.constData(), (size_t)bytes.size()))) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot parse GCI file:\n%1").arg(path));
		return;
	}

	m_gci = gci;
	m_gciPath = path;
	m_status->setText(tr("Loaded %1 physics records from %2")
	                  .arg(m_gci.Cars().size()).arg(QFileInfo(path).fileName()));
	// Обновляем имя/физику текущей машины
	if (m_currentCar >= 0) loadCarToPanel(m_currentCar);
	reloadCarList();
}

// ---------------------------------------------------------------------------
// Файл: сохранить .gci (физика)
// ---------------------------------------------------------------------------
void MainWindow::saveGci()
{
	if (m_gciPath.isEmpty()) {
		m_gciPath = QFileDialog::getSaveFileName(this, tr("Save GCI"), QString(),
		                                         tr("GTA2 car info (*.gci)"));
		if (m_gciPath.isEmpty()) return;
		if (!m_gciPath.endsWith(QLatin1String(".gci"), Qt::CaseInsensitive))
			m_gciPath += QLatin1String(".gci");
	}

	applyCarFromPanel(m_currentCar);
	m_gci.SetDirty();
	std::string text = m_gci.SaveText();

	QFile f(m_gciPath);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot write file:\n%1").arg(m_gciPath));
		return;
	}
	f.write(text.data(), (qint64)text.size());
	f.close();

	m_status->setText(tr("Saved GCI (%1 bytes)").arg(text.size()));
}

// ---------------------------------------------------------------------------
// Список машин
// ---------------------------------------------------------------------------
void MainWindow::reloadCarList()
{
	int sel = -1;
	if (m_listStale && m_currentCar >= 0) sel = m_currentCar;
	m_listStale = false;

	m_updating = true;
	m_carList->clear();
	std::vector<gta2::CarInfo>& cars = m_cars.Cars();
	for (size_t i = 0; i < cars.size(); i++) {
		const gta2::CarInfo& c = cars[i];
		QString name;
		const gta2::GciCar* gc = m_gci.FindByModel(c.model);
		if (gc) name = QString::fromUtf8(gc->name.c_str());
		QString item = QString("%1").arg(c.model, 2, 10, QChar('0'));
		if (!name.isEmpty()) item += QString("  %1").arg(name);
		QListWidgetItem* li = new QListWidgetItem(item, m_carList);
		li->setData(Qt::UserRole, (int)i);
	}
	if (sel >= 0 && sel < m_carList->count()) m_carList->setCurrentRow(sel);
	m_updating = false;
}

void MainWindow::onCarSelected(int index)
{
	if (m_updating) return;
	// Применяем изменения предыдущей машины, затем показываем новую.
	if (m_currentCar >= 0 && m_currentCar != index) applyCarFromPanel(m_currentCar);
	m_currentCar = index;
	if (index >= 0) loadCarToPanel(index);
	m_status->setText(index >= 0 ? tr("Editing car %1").arg(index) : tr("No car selected"));
}

void MainWindow::onAddCar()
{
	gta2::CarInfo c;
	c.model = (unsigned char)m_cars.Cars().size(); // следующий номер модели по умолчанию
	m_cars.Cars().push_back(c);
	markListStale();
	int idx = (int)m_cars.Cars().size() - 1;
	reloadCarList();
	if (idx >= 0 && idx < m_carList->count()) {
		m_currentCar = idx;
		m_carList->setCurrentRow(idx);
		loadCarToPanel(idx);
	}
}

void MainWindow::onDeleteCar()
{
	if (m_currentCar < 0 || m_currentCar >= (int)m_cars.Cars().size()) return;
	applyCarFromPanel(m_currentCar);
	m_cars.Cars().erase(m_cars.Cars().begin() + m_currentCar);
	m_currentCar = -1;
	markListStale();
	reloadCarList();
	if (m_carList->count() > 0) {
		m_currentCar = 0;
		m_carList->setCurrentRow(0);
		loadCarToPanel(0);
	}
}

// ---------------------------------------------------------------------------
// Загрузка данных выбранной машины в панель
// ---------------------------------------------------------------------------
void MainWindow::loadCarToPanel(int index)
{
	if (index < 0 || index >= (int)m_cars.Cars().size()) return;
	gta2::CarInfo& c = m_cars.Cars()[index];
	gta2::GciCar* gc = m_gci.FindByModel(c.model);

	m_updating = true;
	m_sbModel->setValue(c.model);
	m_sbSprite->setValue(c.sprite);
	m_sbW->setValue(c.w);
	m_sbH->setValue(c.h);
	m_sbPassengers->setValue(c.passengers);
	m_sbWreck->setValue(c.wreck);
	m_sbRating->setValue(c.rating);
	m_sbFwOff->setValue(c.front_wheel_offset);
	m_sbRwOff->setValue(c.rear_wheel_offset);
	m_sbFwinOff->setValue(c.front_window_offset);
	m_sbRwinOff->setValue(c.rear_window_offset);
	for (int i = 0; i < 16; i++) {
		unsigned char f = (i < 8) ? c.info_flags : c.info_flags_2;
		m_chkFlag[i]->setChecked((f & (1 << (i & 7))) != 0);
	}

	// Перекраски
	m_sbRemapCount->blockSignals(true);
	m_sbRemapCount->setValue((int)c.remap.size());
	m_sbRemapCount->blockSignals(false);
	m_tblRemap->blockSignals(true);
	m_tblRemap->setRowCount((int)c.remap.size());
	for (int r = 0; r < (int)c.remap.size(); r++) {
		QTableWidgetItem* it = new QTableWidgetItem(QString::number(c.remap[r]));
		m_tblRemap->setItem(r, 0, it);
	}
	m_tblRemap->blockSignals(false);

	// Двери
	m_sbDoorCount->blockSignals(true);
	m_sbDoorCount->setValue((int)c.door.size());
	m_sbDoorCount->blockSignals(false);
	m_tblDoor->blockSignals(true);
	m_tblDoor->setRowCount((int)c.door.size());
	for (int r = 0; r < (int)c.door.size(); r++) {
		QTableWidgetItem* itx = new QTableWidgetItem(QString::number(c.door[r].rx));
		QTableWidgetItem* ity = new QTableWidgetItem(QString::number(c.door[r].ry));
		m_tblDoor->setItem(r, 0, itx);
		m_tblDoor->setItem(r, 1, ity);
	}
	m_tblDoor->blockSignals(false);

	// Физика (GCI)
	if (gc) {
		m_physName->setText(QString::fromUtf8(gc->name.c_str()));
		m_sbTurbo->setValue(gc->turbo);
		m_sbValue->setValue(gc->value);
		for (int i = 0; i < 17; i++)
			m_dbPhys[i]->setValue(PhysGet(gc->physics, i));
	} else {
		m_physName->setText(tr("-"));
		m_sbTurbo->setValue(0);
		m_sbValue->setValue(0);
		for (int i = 0; i < 17; i++)
			m_dbPhys[i]->setValue(0.0);
	}
	m_updating = false;
}

// Индекс машины по модели из панели (для применения после смены model).
int MainWindow::carIndexAtUi() const
{
	return m_currentCar;
}

// Указатель на физику по модели текущей машины.
gta2::GciCar* MainWindow::currentGci()
{
	if (m_currentCar < 0 || m_currentCar >= (int)m_cars.Cars().size()) return NULL;
	int model = m_cars.Cars()[m_currentCar].model;
	return m_gci.FindByModel(model);
}

// ---------------------------------------------------------------------------
// Применение панели к данным выбранной машины
// ---------------------------------------------------------------------------
void MainWindow::applyCarFromPanel(int index)
{
	if (index < 0 || index >= (int)m_cars.Cars().size()) return;
	gta2::CarInfo& c = m_cars.Cars()[index];

	c.model = (unsigned char)m_sbModel->value();
	c.sprite = (unsigned char)m_sbSprite->value();
	c.w = (unsigned char)m_sbW->value();
	c.h = (unsigned char)m_sbH->value();
	c.passengers = (unsigned char)m_sbPassengers->value();
	c.wreck = (unsigned char)m_sbWreck->value();
	c.rating = (unsigned char)m_sbRating->value();
	c.front_wheel_offset = (signed char)m_sbFwOff->value();
	c.rear_wheel_offset = (signed char)m_sbRwOff->value();
	c.front_window_offset = (signed char)m_sbFwinOff->value();
	c.rear_window_offset = (signed char)m_sbRwinOff->value();
	c.info_flags = 0; c.info_flags_2 = 0;
	for (int i = 0; i < 16; i++) {
		unsigned char& f = (i < 8) ? c.info_flags : c.info_flags_2;
		if (m_chkFlag[i]->isChecked()) f |= (unsigned char)(1 << (i & 7));
	}
	c.remap.clear();
	for (int r = 0; r < m_tblRemap->rowCount(); r++) {
		QTableWidgetItem* it = m_tblRemap->item(r, 0);
		int v = it ? it->text().toInt() : 0;
		c.remap.push_back((unsigned char)(v & 0xFF));
	}
	c.num_doors = (unsigned char)m_tblDoor->rowCount();
	c.door.clear();
	for (int r = 0; r < m_tblDoor->rowCount(); r++) {
		gta2::CarDoor d;
		QTableWidgetItem* ix = m_tblDoor->item(r, 0);
		QTableWidgetItem* iy = m_tblDoor->item(r, 1);
		d.rx = (signed char)(ix ? ix->text().toInt() : 0);
		d.ry = (signed char)(iy ? iy->text().toInt() : 0);
		c.door.push_back(d);
	}

	// Физика
	gta2::GciCar* gc = m_gci.FindByModel(c.model);
	if (gc) {
		gc->turbo = m_sbTurbo->value();
		gc->value = m_sbValue->value();
		for (int i = 0; i < 17; i++)
			PhysSet(gc->physics, i, m_dbPhys[i]->value());
	}
}

// ---------------------------------------------------------------------------
// Обработчики изменений (live-обновление в данных)
// ---------------------------------------------------------------------------
void MainWindow::onGfxFieldChanged(int)
{
	if (m_updating || m_currentCar < 0) return;
	applyCarFromPanel(m_currentCar);
	if (m_sbModel->value() != (int)m_cars.Cars()[m_currentCar].model) {
		// Модель изменилась — перестроим список (имя/физика могут отличаться).
		markListStale();
		reloadCarList();
	}
}

void MainWindow::onFlagToggled(bool)
{
	if (m_updating || m_currentCar < 0) return;
	applyCarFromPanel(m_currentCar);
}

void MainWindow::onRemapCountChanged(int)
{
	if (m_updating) return;
	m_tblRemap->blockSignals(true);
	int old = m_tblRemap->rowCount();
	m_tblRemap->setRowCount(m_sbRemapCount->value());
	for (int r = old; r < m_tblRemap->rowCount(); r++)
		m_tblRemap->setItem(r, 0, new QTableWidgetItem("0"));
	m_tblRemap->blockSignals(false);
	if (m_currentCar >= 0) applyCarFromPanel(m_currentCar);
}

void MainWindow::onRemapCellChanged(int, int)
{
	if (m_updating || m_currentCar < 0) return;
	applyCarFromPanel(m_currentCar);
}

void MainWindow::onDoorCountChanged(int)
{
	if (m_updating) return;
	m_tblDoor->blockSignals(true);
	int old = m_tblDoor->rowCount();
	m_tblDoor->setRowCount(m_sbDoorCount->value());
	for (int r = old; r < m_tblDoor->rowCount(); r++) {
		m_tblDoor->setItem(r, 0, new QTableWidgetItem("0"));
		m_tblDoor->setItem(r, 1, new QTableWidgetItem("0"));
	}
	m_tblDoor->blockSignals(false);
	if (m_currentCar >= 0) applyCarFromPanel(m_currentCar);
}

void MainWindow::onDoorCellChanged(int, int)
{
	if (m_updating || m_currentCar < 0) return;
	applyCarFromPanel(m_currentCar);
}

void MainWindow::onPhysIntChanged(int)
{
	if (m_updating || m_currentCar < 0) return;
	applyCarFromPanel(m_currentCar);
}

void MainWindow::onPhysDoubleChanged(double)
{
	if (m_updating || m_currentCar < 0) return;
	applyCarFromPanel(m_currentCar);
}

// ---------------------------------------------------------------------------
// Вспомогательное
// ---------------------------------------------------------------------------
void MainWindow::updateWindowTitle()
{
	QString t = tr("GTA2 CarEditor");
	if (!m_styPath.isEmpty()) t += QString(" - %1").arg(QFileInfo(m_styPath).fileName());
	setWindowTitle(t);
}

// ---------------------------------------------------------------------------
// CarInfo текущей машины (вспомогательный; обычно не используется напрямую)
// ---------------------------------------------------------------------------
gta2::CarInfo* MainWindow::currentCar()
{
	if (m_currentCar < 0 || m_currentCar >= (int)m_cars.Cars().size()) return NULL;
	return &m_cars.Cars()[m_currentCar];
}
