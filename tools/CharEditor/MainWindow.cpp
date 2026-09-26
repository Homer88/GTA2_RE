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
	, m_currentChar(-1)
{
	buildUi();
	setWindowTitle(tr("GTA2 CharEditor"));
	m_charInfo.LoadDefaults();
	reloadCharList();
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

	// --- Левая панель: список персонажей ---
	QWidget* left = new QWidget(split);
	QVBoxLayout* lv = new QVBoxLayout(left);
	m_charList = new QListWidget(left);
	lv->addWidget(m_charList);
	connect(m_charList, SIGNAL(currentRowChanged(int)), this, SLOT(onCharSelected(int)));

	// --- Правая панель: параметры ---
	QWidget* right = new QWidget(split);
	QGridLayout* g = new QGridLayout(right);

	// Имя
	g->addWidget(new QLabel(tr("Character:"), right), 0, 0);
	m_charName = new QLabel(tr("-"), right);
	QFont f = m_charName->font();
	f.setBold(true);
	m_charName->setFont(f);
	g->addWidget(m_charName, 0, 1, 1, 3);

	// health
	g->addWidget(new QLabel(tr("Health:"), right), 1, 0);
	m_sbHealth = new QSpinBox(right);
	m_sbHealth->setRange(0, 9999);
	g->addWidget(m_sbHealth, 1, 1);
	connect(m_sbHealth, SIGNAL(valueChanged(int)), this, SLOT(onHealthChanged(int)));

	// speed
	g->addWidget(new QLabel(tr("Speed:"), right), 2, 0);
	m_sbSpeed = new QSpinBox(right);
	m_sbSpeed->setRange(0, 999);
	g->addWidget(m_sbSpeed, 2, 1);
	connect(m_sbSpeed, SIGNAL(valueChanged(int)), this, SLOT(onSpeedChanged(int)));

	// sprite
	g->addWidget(new QLabel(tr("Sprite:"), right), 3, 0);
	m_sbSprite = new QSpinBox(right);
	m_sbSprite->setRange(0, 999);
	g->addWidget(m_sbSprite, 3, 1);
	connect(m_sbSprite, SIGNAL(valueChanged(int)), this, SLOT(onSpriteChanged(int)));

	// remap
	g->addWidget(new QLabel(tr("Remap:"), right), 4, 0);
	m_sbRemap = new QSpinBox(right);
	m_sbRemap->setRange(0, 255);
	g->addWidget(m_sbRemap, 4, 1);
	connect(m_sbRemap, SIGNAL(valueChanged(int)), this, SLOT(onRemapChanged(int)));

	// weapon
	g->addWidget(new QLabel(tr("Weapon:"), right), 5, 0);
	m_sbWeapon = new QSpinBox(right);
	m_sbWeapon->setRange(0, 28);
	g->addWidget(m_sbWeapon, 5, 1);
	connect(m_sbWeapon, SIGNAL(valueChanged(int)), this, SLOT(onWeaponChanged(int)));

	// Флаги
	QGroupBox* flagBox = new QGroupBox(tr("Flags"), right);
	QGridLayout* fg = new QGridLayout(flagBox);
	m_chkPolice = new QCheckBox(tr("Police"), flagBox);
	fg->addWidget(m_chkPolice, 0, 0);
	connect(m_chkPolice, &QCheckBox::toggled, this, &MainWindow::onPoliceToggled);

	m_chkCriminal = new QCheckBox(tr("Criminal"), flagBox);
	fg->addWidget(m_chkCriminal, 0, 1);
	connect(m_chkCriminal, &QCheckBox::toggled, this, &MainWindow::onCriminalToggled);

	m_chkAgent = new QCheckBox(tr("Agent"), flagBox);
	fg->addWidget(m_chkAgent, 0, 2);
	connect(m_chkAgent, &QCheckBox::toggled, this, &MainWindow::onAgentToggled);
	g->addWidget(flagBox, 6, 0, 1, 4);

	// Пояснение
	QLabel* hint = new QLabel(tr(
		"occupation -> \n"
		"  0 - гражданский, 3 - default, 4 - водитель,\n"
		"  8/9 - агент, 15 - MUGGER, 16 - угонщик, 22 - ELVIS,\n"
		"  24..31 - полиция"), right);
	hint->setStyleSheet("color: gray;");
	g->addWidget(hint, 7, 0, 1, 4);

	g->setRowStretch(8, 1);

	split->addWidget(left);
	split->addWidget(right);
	split->setStretchFactor(0, 1);
	split->setStretchFactor(1, 2);
	setCentralWidget(split);

	// Строка состояния
	m_status = new QLabel(tr("Loaded default character parameters."), this);
	statusBar()->addWidget(m_status);

	resize(700, 480);
}

// ---------------------------------------------------------------------------
// Файл: открыть .gch
// ---------------------------------------------------------------------------
void MainWindow::openFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Character Info"), QString(),
	                                            tr("GTA2 Character Info (*.gch *.txt)"));
	if (path.isEmpty()) return;

	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot open file:\n%1").arg(path));
		return;
	}
	QByteArray bytes = f.readAll();
	f.close();

	gta2::CharInfoFile info;
	if (!info.ParseText(std::string(bytes.constData(), (size_t)bytes.size()))) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot parse character info file:\n%1").arg(path));
		return;
	}

	m_charInfo = info;
	m_filePath = path;
	reloadCharList();
	updateWindowTitle();
	m_status->setText(tr("Loaded %1 characters from %2")
	                  .arg((int)m_charInfo.Chars().size())
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

	applyCharFromPanel(m_currentChar);
	std::string text = m_charInfo.SaveText();

	QFile f(m_filePath);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot write file:\n%1").arg(m_filePath));
		return;
	}
	f.write(text.data(), (qint64)text.size());
	f.close();

	m_charInfo.SetDirty();
	m_status->setText(tr("Saved %1 bytes to %2").arg(text.size()).arg(QFileInfo(m_filePath).fileName()));
	updateWindowTitle();
}

void MainWindow::saveFileAs()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save Character Info"), QString(),
	                                            tr("GTA2 Character Info (*.gch)"));
	if (path.isEmpty()) return;
	if (!path.endsWith(QLatin1String(".gch"), Qt::CaseInsensitive))
		path += QLatin1String(".gch");
	m_filePath = path;
	saveFile();
}

// ---------------------------------------------------------------------------
// Загрузить значения по умолчанию
// ---------------------------------------------------------------------------
void MainWindow::loadDefaults()
{
	m_charInfo.LoadDefaults();
	m_filePath.clear();
	reloadCharList();
	updateWindowTitle();
	m_status->setText(tr("Loaded default character parameters."));
}

// ---------------------------------------------------------------------------
// Список персонажей
// ---------------------------------------------------------------------------
void MainWindow::reloadCharList()
{
	m_updating = true;
	m_charList->clear();
	const std::vector<gta2::CharParams>& chars = m_charInfo.Chars();
	for (size_t i = 0; i < chars.size(); i++) {
		const gta2::CharParams& c = chars[i];
		QString item = QString("%1  %2").arg(i, 2).arg(QString::fromUtf8(c.name.c_str()));
		m_charList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::onCharSelected(int index)
{
	if (m_updating) return;
	if (m_currentChar >= 0 && m_currentChar != index)
		applyCharFromPanel(m_currentChar);
	m_currentChar = index;
	if (index >= 0) loadCharToPanel(index);
	m_status->setText(index >= 0 ? tr("Editing character index %1").arg(index) : tr("No character selected"));
}

// ---------------------------------------------------------------------------
// Загрузка данных выбранного персонажа в панель
// ---------------------------------------------------------------------------
void MainWindow::loadCharToPanel(int index)
{
	if (index < 0 || index >= (int)m_charInfo.Chars().size()) return;
	const gta2::CharParams& c = m_charInfo.Chars()[index];

	m_updating = true;
	m_charName->setText(QString("%1  (occupation %2)")
	                   .arg(QString::fromUtf8(c.name.c_str())).arg(c.occupation));
	m_sbHealth->setValue(c.health);
	m_sbSpeed->setValue(c.speed);
	m_sbSprite->setValue(c.sprite);
	m_sbRemap->setValue(c.remap);
	m_sbWeapon->setValue(c.weapon);
	m_chkPolice->setChecked(c.is_police != 0);
	m_chkCriminal->setChecked(c.is_criminal != 0);
	m_chkAgent->setChecked(c.is_agent != 0);
	m_updating = false;
}

// ---------------------------------------------------------------------------
// Применение панели к данным
// ---------------------------------------------------------------------------
void MainWindow::applyCharFromPanel(int index)
{
	if (index < 0 || index >= (int)m_charInfo.Chars().size()) return;
	gta2::CharParams& c = m_charInfo.Chars()[index];

	c.health = m_sbHealth->value();
	c.speed = m_sbSpeed->value();
	c.sprite = m_sbSprite->value();
	c.remap = m_sbRemap->value();
	c.weapon = m_sbWeapon->value();
	c.is_police = m_chkPolice->isChecked() ? 1 : 0;
	c.is_criminal = m_chkCriminal->isChecked() ? 1 : 0;
	c.is_agent = m_chkAgent->isChecked() ? 1 : 0;
}

// ---------------------------------------------------------------------------
// Обработчики изменений
// ---------------------------------------------------------------------------
void MainWindow::onHealthChanged(int)   { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onSpeedChanged(int)    { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onSpriteChanged(int)   { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onRemapChanged(int)    { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onWeaponChanged(int)   { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onPoliceToggled(bool)  { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onCriminalToggled(bool){ if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }
void MainWindow::onAgentToggled(bool)   { if (!m_updating && m_currentChar >= 0) applyCharFromPanel(m_currentChar); }

// ---------------------------------------------------------------------------
// Вспомогательное
// ---------------------------------------------------------------------------
void MainWindow::updateWindowTitle()
{
	QString t = tr("GTA2 CharEditor");
	if (!m_filePath.isEmpty()) t += QString(" - %1").arg(QFileInfo(m_filePath).fileName());
	setWindowTitle(t);
}