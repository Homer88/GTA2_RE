#ifndef __TOOLS_TEXT_EDITOR_MAINWINDOW_H_
#define __TOOLS_TEXT_EDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "GxtFormat.h"

class GxtModel;
class QTableView;
class QLineEdit;
class QLabel;
class QPushButton;

// Главное окно редактора текстов игры (.gxt).
// Таблица строк: Ключ | Текст | Оригинал (необязательный справочный файл).
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);
	// Открыть .gxt по пути (слот для вызова из командной строки).
	void openGxtAt(const QString& path);

private slots:
	void openGxt();
	void openReference();
	void saveGxt();
	void addRow();
	void deleteRow();
	void onFilterChanged(const QString& f);
	void onDirty();

private:
	void updateStats();
	void updateWindowTitle();

	gta2::GxtFile m_gxt;      // редактируемая таблица
	gta2::GxtFile m_ref;      // справочный файл (перевод-исходник)
	GxtModel* m_model;
	QTableView* m_table;
	QLineEdit* m_filter;
	QLabel* m_stats;
	QAction* m_btnRef;
	QString m_path;           // путь текущего файла
	QString m_refPath;        // путь справочного файла
};

#endif // !__TOOLS_TEXT_EDITOR_MAINWINDOW_H_