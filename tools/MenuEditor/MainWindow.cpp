#include "MainWindow.h"

#include <QListWidget>
#include <QFile>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QSplitter>
#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>

#include "MenuJson.h"
#include "MenuCodeGen.h"

namespace {
// Пример проекта при первом запуске: главное меню + параметры + сеть.
void FillSampleProject(gta2tools::MenuProjectModel& p)
{
	using namespace gta2tools;
	p.name = L"Пример меню";

	MenuPageModel main;
	main.id = 0; main.name = L"Главное меню"; main.header = L"GTA2";
	MenuEntryModel e1; e1.text = L"НОВАЯ ИГРА";   e1.x = 220; e1.y = 120; e1.action = ActionPage; e1.target = 1;
	MenuEntryModel e2; e2.text = L"ПАРАМЕТРЫ";    e2.x = 220; e2.y = 160; e2.action = ActionPage; e2.target = 2;
	MenuEntryModel e3; e3.text = L"СЕТЕВАЯ ИГРА"; e3.x = 220; e3.y = 200; e3.action = ActionPage; e3.target = 3;
	MenuEntryModel e4; e4.text = L"ВЫХОД";        e4.x = 220; e4.y = 240; e4.action = ActionNone;
	main.entries.push_back(e1); main.entries.push_back(e2);
	main.entries.push_back(e3); main.entries.push_back(e4);

	MenuPageModel opt;
	opt.id = 2; opt.name = L"Параметры"; opt.header = L"ПАРАМЕТРЫ";
	MenuEntryModel o1; o1.text = L"ЗВУК";      o1.x = 220; o1.y = 120;
	MenuEntryModel o2; o2.text = L"УПРАВЛЕНИЕ"; o2.x = 220; o2.y = 160;
	MenuEntryModel o3; o3.text = L"ЭКРАН";     o3.x = 220; o3.y = 200;
	MenuEntryModel o4; o4.text = L"НАЗАД";     o4.x = 220; o4.y = 240; o4.action = ActionPage; o4.target = 0;
	opt.entries.push_back(o1); opt.entries.push_back(o2);
	opt.entries.push_back(o3); opt.entries.push_back(o4);

	MenuPageModel net;
	net.id = 3; net.name = L"Сеть"; net.header = L"СЕТЕВАЯ ИГРА";
	MenuEntryModel n1; n1.text = L"ИГРА ПО СЕТИ";     n1.x = 220; n1.y = 120;
	MenuEntryModel n2; n2.text = L"СОЗДАТЬ ИГРУ";     n2.x = 220; n2.y = 160;
	MenuEntryModel n3; n3.text = L"ПОДКЛЮЧИТЬСЯ";     n3.x = 220; n3.y = 200;
	MenuEntryModel n4; n4.text = L"НАЗАД";            n4.x = 220; n4.y = 240; n4.action = ActionPage; n4.target = 0;
	net.entries.push_back(n1); net.entries.push_back(n2);
	net.entries.push_back(n3); net.entries.push_back(n4);

	p.startPage = 0;
	p.pages.push_back(main);
	p.pages.push_back(opt);
	p.pages.push_back(net);
}
} // namespace

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), m_scene(NULL), m_view(NULL),
	  m_pagesList(NULL), m_editHeader(NULL), m_editText(NULL),
	  m_sbX(NULL), m_sbY(NULL), m_sbSize(NULL), m_cbAction(NULL),
	  m_sbTarget(NULL), m_chkDim(NULL), m_chkPlay(NULL), m_status(NULL),
	  m_updating(false), m_currentEntry(-1)
{
	buildUi();
	FillSampleProject(m_project);
	refreshPages();
	reloadScene();
	updateWindowTitle();
}

void MainWindow::buildUi()
{
	setWindowTitle("GTA2 MenuEditor");
	resize(1100, 640);

	QToolBar* tb = addToolBar(tr("Файл"));
	tb->addAction(tr("Новый"), this, SLOT(newProject()));
	tb->addAction(tr("Открыть"), this, SLOT(openProject()));
	tb->addAction(tr("Сохранить"), this, SLOT(saveProject()));
	tb->addSeparator();
	tb->addAction(tr("Экспорт C++"), this, SLOT(exportCpp()));
	tb->addSeparator();
	m_chkPlay = new QCheckBox(tr("Проверка меню (игра)"), this);
	tb->addWidget(m_chkPlay);
	connect(m_chkPlay, SIGNAL(toggled(bool)), this, SLOT(onPlayToggled(bool)));

	m_scene = new MenuScene(this);
	m_view  = new MenuSceneView(m_scene, this);
	connect(m_scene, SIGNAL(selectionChanged()), m_scene, SLOT(onSelectionChanged()));
	connect(m_scene, SIGNAL(entrySelected(int)), this, SLOT(onSceneEntrySelected(int)));
	connect(m_scene, SIGNAL(entryMoved(int,int,int)), this, SLOT(onSceneEntryMoved(int,int,int)));
	connect(m_view, SIGNAL(navigate()), this, SLOT(onNavigate()));
	connect(m_view, SIGNAL(activeDelta(int)), this, SLOT(onActiveDelta(int)));
	connect(m_view, SIGNAL(doubleClickedEntry(int)), this, SLOT(onDoubleClickedEntry(int)));

	// --- Слева: список страниц.
	m_pagesList = new QListWidget(this);
	connect(m_pagesList, SIGNAL(currentRowChanged(int)), this, SLOT(onPageListChanged()));

	QPushButton* btnAddPage = new QPushButton(tr("+ страница"), this);
	connect(btnAddPage, SIGNAL(clicked()), this, SLOT(onAddPage()));
	QPushButton* btnDelPage = new QPushButton(tr("- страница"), this);
	connect(btnDelPage, SIGNAL(clicked()), this, SLOT(onDeletePage()));

	QWidget* left = new QWidget(this);
	QVBoxLayout* ll = new QVBoxLayout(left);
	ll->addWidget(new QLabel(tr("Страницы"), left));
	ll->addWidget(m_pagesList, 1);
	QHBoxLayout* hl = new QHBoxLayout();
	hl->addWidget(btnAddPage);
	hl->addWidget(btnDelPage);
	ll->addLayout(hl);

	// --- Справа: свойства.
	m_editText  = new QLineEdit(this);
	m_sbX       = new QSpinBox(this);
	m_sbY       = new QSpinBox(this);
	m_sbSize    = new QSpinBox(this);
	m_cbAction  = new QComboBox(this);
	m_sbTarget  = new QSpinBox(this);
	m_chkDim    = new QCheckBox(tr("пункт неактивен"), this);
	connect(m_editText, SIGNAL(textChanged(QString)), this, SLOT(onEntryTextChanged()));
	connect(m_sbX, SIGNAL(valueChanged(int)), this, SLOT(onEntryPosChanged()));
	connect(m_sbY, SIGNAL(valueChanged(int)), this, SLOT(onEntryPosChanged()));
	connect(m_sbSize, SIGNAL(valueChanged(int)), this, SLOT(onEntryPropChanged(int)));
	connect(m_cbAction, SIGNAL(currentIndexChanged(int)), this, SLOT(onEntryPropChanged(int)));
	connect(m_sbTarget, SIGNAL(valueChanged(int)), this, SLOT(onEntryPropChanged(int)));
	connect(m_chkDim, SIGNAL(toggled(bool)), this, SLOT(onFlagsToggled(bool)));

	m_editHeader = new QLineEdit(this);
	connect(m_editHeader, SIGNAL(textChanged(QString)), this, SLOT(onHeaderChanged()));

	m_sbX->setRange(0, 640);    m_sbY->setRange(0, 480);
	m_sbSize->setRange(0, 72);  m_sbTarget->setRange(0, 999);
	m_sbX->setSuffix(" px");    m_sbY->setSuffix(" px");
	m_sbSize->setSuffix(" pt");

	m_cbAction->addItem(tr("ничего"), gta2tools::ActionNone);
	m_cbAction->addItem(tr("переход на страницу"), gta2tools::ActionPage);
	m_cbAction->addItem(tr("игровое действие"), gta2tools::ActionGame);

	QPushButton* btnAddEntry = new QPushButton(tr("+ пункт"), this);
	connect(btnAddEntry, SIGNAL(clicked()), this, SLOT(onAddEntry()));
	QPushButton* btnDelEntry = new QPushButton(tr("- пункт"), this);
	connect(btnDelEntry, SIGNAL(clicked()), this, SLOT(onDeleteEntry()));

	QGroupBox* right = new QGroupBox(tr("Пункт меню"), this);
	QFormLayout* fl = new QFormLayout(right);
	fl->addRow(tr("Текст"), m_editText);
	fl->addRow(tr("X"), m_sbX);
	fl->addRow(tr("Y"), m_sbY);
	fl->addRow(tr("Размер шрифта (0 = авто)"), m_sbSize);
	fl->addRow(tr("Действие"), m_cbAction);
	fl->addRow(tr("Переход/действие №"), m_sbTarget);
	fl->addRow(tr(""), m_chkDim);
	fl->addRow(tr("Заголовок страницы"), m_editHeader);
	QHBoxLayout* eh = new QHBoxLayout();
	eh->addWidget(btnAddEntry);
	eh->addWidget(btnDelEntry);
	fl->addRow(eh);

	QSplitter* split = new QSplitter(this);
	split->addWidget(left);
	split->addWidget(m_view);
	split->addWidget(right);
	split->setStretchFactor(0, 0);
	split->setStretchFactor(1, 1);
	split->setStretchFactor(2, 0);
	setCentralWidget(split);

	m_status = new QLabel(tr("Готово"), this);
	statusBar()->addWidget(m_status);
}

// ---------------------------------------------------------------------------
// Файл: проект/экспорт.
// ---------------------------------------------------------------------------

void MainWindow::newProject()
{
	m_project = gta2tools::MenuProjectModel();
	m_project.name = L"Новый проект";
	m_currentPath.clear();
	m_currentEntry = -1;
	refreshPages();
	reloadScene();
	updateWindowTitle();
	statusBar()->showMessage(tr("Создан новый проект"), 3000);
}

void MainWindow::openProject()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Открыть проект меню"),
	                                            m_currentPath, tr("Меню GTA2 (*.menu *.json)"));
	if (path.isEmpty())
		return;
	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл."));
		return;
	}
	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
	if (err.error != QJsonParseError::NoError || !MenuProjectFromDoc(doc, m_project)) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Файл повреждён: %1").arg(err.errorString()));
		return;
	}
	m_currentPath = path;
	m_currentEntry = -1;
	refreshPages();
	reloadScene();
	updateWindowTitle();
	statusBar()->showMessage(tr("Открыт: %1").arg(path), 3000);
}

void MainWindow::saveProject()
{
	QString path = m_currentPath;
	if (path.isEmpty())
		path = QFileDialog::getSaveFileName(this, tr("Сохранить проект меню"),
		                                    tr("menu.menu"), tr("Меню GTA2 (*.menu *.json)"));
	if (path.isEmpty())
		return;
	QFile f(path);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось записать файл."));
		return;
	}
	f.write(MenuProjectToDoc(m_project).toJson(QJsonDocument::Indented));
	m_currentPath = path;
	statusBar()->showMessage(tr("Сохранено: %1").arg(path), 3000);
}

void MainWindow::exportCpp()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Экспорт C++"),
	                                            tr("MenuGenerated.cpp"), tr("C++ (*.cpp)"));

	if (path.isEmpty())
		return;
	QFile f(path);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось записать файл."));
		return;
	}
	f.write(QString::fromStdString(gta2tools::GenerateMenuCode(m_project)).toUtf8());
	statusBar()->showMessage(tr("C++ сохранён: %1").arg(path), 3000);
}

// ---------------------------------------------------------------------------
// Страницы.
// ---------------------------------------------------------------------------

void MainWindow::refreshPages()
{
	m_updating = true;
	m_pagesList->clear();
	for (size_t i = 0; i < m_project.pages.size(); i++) {
		const gta2tools::MenuPageModel& pg = m_project.pages[i];
		m_pagesList->addItem(QString("%1: %2")
		                     .arg(pg.id)
		                     .arg(QString::fromStdWString(pg.name)));
	}
	if (!m_project.pages.empty())
		m_pagesList->setCurrentRow(0);
	m_updating = false;
}

void MainWindow::onPageListChanged()
{
	if (m_updating)
		return;
	m_currentEntry = -1;
	loadEntryToPanel(-1);
	m_scene->showPage(m_pagesList->currentRow());
}

void MainWindow::onAddPage()
{
	gta2tools::MenuPageModel pg;
	pg.id = (int)m_project.pages.size();
	pg.name = L"Новая страница";
	pg.header = L"ЗАГОЛОВОК";
	gta2tools::MenuEntryModel back;
	back.text = L"НАЗАД";
	back.x = 20; back.y = 440;
	back.action = gta2tools::ActionPage;
	back.target = 0;
	pg.entries.push_back(back);
	m_project.pages.push_back(pg);
	refreshPages();
	m_pagesList->setCurrentRow(m_pagesList->count() - 1);
	reloadScene();
}

void MainWindow::onDeletePage()
{
	int row = m_pagesList->currentRow();
	if (row < 0 || row >= (int)m_project.pages.size())
		return;
	m_project.pages.erase(m_project.pages.begin() + row);
	m_currentEntry = -1;
	refreshPages();
	loadEntryToPanel(-1);
	reloadScene();
}

// ---------------------------------------------------------------------------
// Пункты.
// ---------------------------------------------------------------------------

void MainWindow::onAddEntry()
{
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page)
		return;
	if ((int)page->entries.size() >= 10) {
		QMessageBox::information(this, tr("Пункты"), tr("На странице не более 10 пунктов."));
		return;
	}
	gta2tools::MenuEntryModel e;
	e.x = 20;
	e.y = 80 + (int)page->entries.size() * 40;
	e.text = L"НОВЫЙ ПУНКТ";
	page->entries.push_back(e);
	int idx = (int)page->entries.size() - 1;
	m_scene->rebuild();
	loadEntryToPanel(idx);
}

void MainWindow::onDeleteEntry()
{
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page || m_currentEntry < 0 || m_currentEntry >= (int)page->entries.size())
		return;
	page->entries.erase(page->entries.begin() + m_currentEntry);
	m_currentEntry = -1;
	m_scene->rebuild();
	loadEntryToPanel(-1);
}

// ---------------------------------------------------------------------------
// Свойства пункта (живое обновление).
// ---------------------------------------------------------------------------

void MainWindow::loadEntryToPanel(int index)
{
	m_currentEntry = index;
	m_updating = true;

	gta2tools::MenuPageModel* page = m_scene->currentPage();
	bool valid = page && index >= 0 && index < (int)page->entries.size();
	gta2tools::MenuEntryModel* e = valid ? &page->entries[index] : NULL;

	m_editText->setText(e ? QString::fromStdWString(e->text) : QString());
	m_sbX->setValue(e ? e->x : 0);
	m_sbY->setValue(e ? e->y : 0);
	m_sbSize->setValue(e ? e->fontSize : 0);
	m_cbAction->setCurrentIndex(e ? e->action : 0);
	m_sbTarget->setValue(e ? e->target : 0);
	m_chkDim->setChecked(e ? (e->flags & 2) != 0 : false);
	m_editHeader->setText(page ? QString::fromStdWString(page->header) : QString());

	m_updating = false;
	statusBar()->showMessage(valid
	                         ? tr("Пункт %1: x=%2, y=%3")
	                           .arg(index).arg(e->x).arg(e->y)
	                         : tr("Пункт не выбран"), 3000);
}

void MainWindow::applyEntryToModel()
{
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page || m_currentEntry < 0 || m_currentEntry >= (int)page->entries.size())
		return;
	gta2tools::MenuEntryModel& e = page->entries[m_currentEntry];
	e.text = m_editText->text().toStdWString();
	e.x = m_sbX->value();
	e.y = m_sbY->value();
	e.fontSize = m_sbSize->value();
	e.action = m_cbAction->currentData().toInt();
	e.target = m_sbTarget->value();
	e.flags = (e.flags & ~2) | (m_chkDim->isChecked() ? 2 : 0);
}

void MainWindow::onEntryTextChanged()
{
	if (m_updating)
		return;
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page || m_currentEntry < 0)
		return;
	page->entries[m_currentEntry].text = m_editText->text().toStdWString();
	m_scene->updateEntryVisual(m_currentEntry);
}

void MainWindow::onHeaderChanged()
{
	if (m_updating)
		return;
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page)
		return;
	page->header = m_editHeader->text().toStdWString();
	m_scene->rebuild();
}

void MainWindow::onEntryPosChanged()
{
	if (m_updating)
		return;
	applyEntryToModel();
	m_scene->updateEntryVisual(m_currentEntry);
}

void MainWindow::onEntryPropChanged(int)
{
	if (m_updating)
		return;
	applyEntryToModel();
	m_scene->updateEntryVisual(m_currentEntry);
}

void MainWindow::onFlagsToggled(bool)
{
	if (m_updating)
		return;
	applyEntryToModel();
	m_scene->updateEntryVisual(m_currentEntry);
}

// ---------------------------------------------------------------------------
// Сцена.
// ---------------------------------------------------------------------------

void MainWindow::onSceneEntrySelected(int index)
{
	if (m_chkPlay->isChecked())
		return; // в режиме проверки выделение не влияет на редактор
	loadEntryToPanel(index);
}

void MainWindow::onSceneEntryMoved(int index, int x, int y)
{
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page || index < 0 || index >= (int)page->entries.size())
		return;
	page->entries[index].x = x;
	page->entries[index].y = y;
	// Показываем новые координаты в панели, не прерывая перетаскивание.
	if (index == m_currentEntry && !m_updating) {
		m_updating = true;
		m_sbX->setValue(x);
		m_sbY->setValue(y);
		m_updating = false;
	}
	statusBar()->showMessage(tr("Пункт %1: x=%2, y=%3").arg(index).arg(x).arg(y), 3000);
}

void MainWindow::onDoubleClickedEntry(int index)
{
	if (m_chkPlay->isChecked())
		return;
	loadEntryToPanel(index);
	m_editText->setFocus();
	m_editText->selectAll();
}

// ---------------------------------------------------------------------------
// Проверка меню (навигация как в игре).
// ---------------------------------------------------------------------------

void MainWindow::reloadScene()
{
	m_scene->setProject(&m_project);
	m_scene->setPlayMode(m_chkPlay->isChecked());
	loadEntryToPanel(-1);
	updateWindowTitle();
}

void MainWindow::onPlayToggled(bool on)
{
	m_scene->setPlayMode(on);
	if (on)
		m_view->setFocus();
	else
		loadEntryToPanel(m_scene->activeIndex());
	statusBar()->showMessage(on ? tr("Проверка: вверх/вниз - выбор, Enter - переход")
	                            : tr("Редактирование"), 3000);
}

void MainWindow::onActiveDelta(int delta)
{
	if (!m_chkPlay->isChecked())
		return;
	m_scene->setActiveIndex(m_scene->activeIndex() + delta);
}

void MainWindow::onNavigate()
{
	if (!m_chkPlay->isChecked() || !m_scene->playMode())
		return;
	gta2tools::MenuPageModel* page = m_scene->currentPage();
	if (!page)
		return;
	int idx = m_scene->activeIndex();
	if (idx < 0 || idx >= (int)page->entries.size())
		return;
	const gta2tools::MenuEntryModel& e = page->entries[idx];
	if (e.action == gta2tools::ActionPage) {
		int pi = findPageIndexById(e.target);
		if (pi < 0) {
			statusBar()->showMessage(tr("Страница %1 не найдена").arg(e.target), 3000);
			return;
		}
		m_pagesList->setCurrentRow(pi); // открывает страницу и активный пункт
		m_scene->setActiveIndex(0);
	} else {
		statusBar()->showMessage(tr("Пункт «%1» (действие %2) ")
		                         .arg(QString::fromStdWString(e.text), QString::number(e.action)), 3000);
	}
}

int MainWindow::findPageIndexById(int id) const
{
	for (size_t i = 0; i < m_project.pages.size(); i++)
		if (m_project.pages[i].id == id)
			return (int)i;
	return -1;
}

void MainWindow::updateWindowTitle()
{
	setWindowTitle(QString("GTA2 MenuEditor - %1").arg(QString::fromStdWString(m_project.name)));
}