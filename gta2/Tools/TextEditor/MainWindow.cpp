#include "MainWindow.h"
#include "GxtModel.h"

#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QFileInfo>

#include <fstream>

namespace {

// Чтение/запись файла целиком.
bool ReadAll(const QString& path, std::vector<unsigned char>& out)
{
	std::ifstream f(path.toLocal8Bit().constData(), std::ios::binary);
	if (!f.is_open()) return false;
	f.seekg(0, std::ios::end);
	long sz = (long)f.tellg();
	if (sz <= 0) return false;
	f.seekg(0, std::ios::beg);
	out.resize((size_t)sz);
	f.read((char*)&out[0], sz);
	return true;
}

bool WriteAll(const QString& path, const std::vector<unsigned char>& data)
{
	std::ofstream f(path.toLocal8Bit().constData(), std::ios::binary | std::ios::trunc);
	if (!f.is_open()) return false;
	f.write((const char*)&data[0], (std::streamsize)data.size());
	return f.good();
}

} // namespace

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), m_model(NULL), m_table(NULL), m_filter(NULL),
	  m_stats(NULL), m_btnRef(NULL)
{
	setWindowTitle("GTA2 TextEditor");
	resize(1000, 640);

	QToolBar* tb = addToolBar(tr("Файл"));
	tb->addAction(tr("Открыть .gxt"), this, SLOT(openGxt()));
	tb->addAction(tr("Сохранить"), this, SLOT(saveGxt()));
	tb->addSeparator();
	m_btnRef = tb->addAction(tr("Оригинал (справка)…"), this, SLOT(openReference()));
	m_btnRef->setCheckable(true);
	tb->addSeparator();
	tb->addAction(tr("+ строка"), this, SLOT(addRow()));
	tb->addAction(tr("- строка"), this, SLOT(deleteRow()));

	m_filter = new QLineEdit(this);
	m_filter->setPlaceholderText(tr("Фильтр по ключу/тексту"));
	connect(m_filter, SIGNAL(textChanged(QString)), this, SLOT(onFilterChanged(QString)));

	m_model = new GxtModel(this);
	m_model->setFile(&m_gxt);
	connect(m_model, SIGNAL(edited()), this, SLOT(onDirty()));

	m_table = new QTableView(this);
	m_table->setModel(m_model);
	m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_table->setSelectionMode(QAbstractItemView::SingleSelection);
	m_table->horizontalHeader()->setStretchLastSection(true);
	m_table->setWordWrap(false);

	m_stats = new QLabel(tr("Файл не открыт"), this);

	QWidget* cw = new QWidget(this);
	QVBoxLayout* vl = new QVBoxLayout(cw);
	vl->addWidget(m_filter);
	vl->addWidget(m_table, 1);
	setCentralWidget(cw);
	statusBar()->addWidget(m_stats);
}

void MainWindow::onDirty()
{
	updateStats();
	updateWindowTitle();
}

void MainWindow::openGxt()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Открыть тексты игры"),
	                                            "bin\\data", tr("Тексты GTA2 (*.gxt)"));
	if (path.isEmpty()) return;
	openGxtAt(path);
}

void MainWindow::openGxtAt(const QString& path)
{
	std::vector<unsigned char> raw;
	if (!ReadAll(path, raw)) { QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось прочитать файл.")); return; }
	if (!m_gxt.Load(&raw[0], raw.size())) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Не похоже на .gxt (GBL?/TKEY/TDAT)."));
		return;
	}
	m_path = path;
	m_model->setFile(&m_gxt);
	m_model->setReference(m_ref.IsOk() ? &m_ref : NULL);
	onDirty();
	statusBar()->showMessage(tr("Открыт: %1").arg(path), 3000);
}

void MainWindow::openReference()
{
	if (m_btnRef->isChecked()) {
		m_refPath = QFileDialog::getOpenFileName(this, tr("Справочный .gxt"),
		                                         m_refPath, tr("Тексты GTA2 (*.gxt)"));
		if (m_refPath.isEmpty()) { m_btnRef->setChecked(false); return; }
		std::vector<unsigned char> raw;
		if (!ReadAll(m_refPath, raw) || !m_ref.Load(&raw[0], raw.size())) {
			QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть справочный файл."));
			m_btnRef->setChecked(false);
			return;
		}
		m_model->setReference(&m_ref);
		statusBar()->showMessage(tr("Справка: %1").arg(m_refPath), 3000);
	} else {
		m_model->setReference(NULL);
		m_ref = gta2::GxtFile();
		statusBar()->showMessage(tr("Справка выключена"), 3000);
	}
	updateStats();
}

void MainWindow::saveGxt()
{
	if (!m_gxt.IsOk()) { QMessageBox::information(this, tr("Сохранить"), tr("Файл не открыт.")); return; }
	QString path = m_path;
	if (path.isEmpty())
		path = QFileDialog::getSaveFileName(this, tr("Сохранить .gxt"),
		                                    tr("тексты.gxt"), tr("Тексты GTA2 (*.gxt)"));
	if (path.isEmpty()) return;
	if (!m_gxt.IsDirty()) {
		statusBar()->showMessage(tr("Изменений нет — файл не перезаписан"), 3000);
		return;
	}
	std::vector<unsigned char> data = m_gxt.Save();
	if (!WriteAll(path, data)) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось записать файл."));
		return;
	}
	m_path = path;
	m_gxt.ClearDirty();
	onDirty();
	statusBar()->showMessage(tr("Сохранено: %1 (%2 строк)").arg(path).arg(m_gxt.Size()), 3000);
}

void MainWindow::addRow()
{
	if (!m_gxt.IsOk()) { QMessageBox::information(this, tr("Строка"), tr("Сначала откройте .gxt.")); return; }
	bool ok = false;
	QString key = QInputDialog::getText(this, tr("Новая строка"), tr("Ключ (до 8 символов):"),
	                                    QLineEdit::Normal, QString(), &ok);
	if (!ok) return;
	key = key.trimmed();
	if (key.isEmpty() || key.size() > 8) { QMessageBox::warning(this, tr("Ошибка"), tr("Ключ: 1..8 символов.")); return; }
	if (!m_gxt.Add(key.toStdString(), std::wstring())) {
		QMessageBox::warning(this, tr("Ошибка"), tr("Ключ уже существует."));
		return;
	}
	m_model->refresh();
	int last = m_model->rowCount() - 1;
	if (last >= 0) {
		QModelIndex idx = m_model->index(last, 1);
		m_table->setCurrentIndex(idx);
		m_table->edit(idx);
	}
	onDirty();
}

void MainWindow::deleteRow()
{
	if (!m_gxt.IsOk()) return;
	QModelIndex cur = m_table->currentIndex();
	if (!cur.isValid()) return;
	int src = m_model->sourceIndex(cur.row());
	if (src < 0) return;
	if (QMessageBox::question(this, tr("Удалить"), tr("Удалить строку «%1»?")
	                              .arg(QString::fromStdString(m_gxt.Strings()[src].key)))
	    != QMessageBox::Yes) return;
	if (!m_gxt.Remove((size_t)src)) return;
	m_model->refresh();
	onDirty();
}

void MainWindow::onFilterChanged(const QString& f)
{
	m_model->setFilter(f);
}

void MainWindow::updateStats()
{
	if (!m_gxt.IsOk()) {
		m_stats->setText(tr("Файл не открыт"));
		return;
	}
	QString lang = QString(QChar::fromLatin1(m_gxt.Language()));
	int empty = 0;
	for (size_t i = 0; i < m_gxt.Size(); i++)
		if (m_gxt.Strings()[i].text.empty()) empty++;
	m_stats->setText(tr("Язык %1 | строк %2 | пустых %3 | показано %4%5")
	                 .arg(lang).arg(m_gxt.Size()).arg(empty).arg(m_model->rowCount())
	                 .arg(m_gxt.IsDirty() ? tr(" | НЕ СОХРАНЕНО") : QString()));
}

void MainWindow::updateWindowTitle()
{
	QString name = m_path.isEmpty() ? tr("новый") : QFileInfo(m_path).fileName();
	setWindowTitle(QString("GTA2 TextEditor - %1%2")
	               .arg(name).arg(m_gxt.IsDirty() ? " *" : ""));
}