#ifndef __TOOLS_MENU_EDITOR_MAINWINDOW_H_
#define __TOOLS_MENU_EDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "MenuDataModel.h"
#include "MenuScene.h"

class QListWidget;
class QLineEdit;
class QSpinBox;
class QComboBox;
class QCheckBox;
class QLabel;
class QPushButton;

// Главное окно редактора меню:
//   слева  - список страниц, справа - свойства пункта,
//   в центре - «живой» предпросмотр страницы (640x480, редактирование мышью).
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);

private slots:
	// файл
	void newProject();
	void openProject();
	void saveProject();
	void exportCpp();

	// страницы
	void onPageListChanged();
	void onAddPage();
	void onDeletePage();

	// пункты
	void onAddEntry();
	void onDeleteEntry();

	// свойства пункта (live-обновление)
	void onEntryTextChanged();
	void onHeaderChanged();
	void onEntryPosChanged();
	void onEntryPropChanged(int);
	void onFlagsToggled(bool);

	// сцена
	void onSceneEntrySelected(int index);
	void onSceneEntryMoved(int index, int x, int y);
	void onDoubleClickedEntry(int index);

	// проверка (play)
	void onPlayToggled(bool);
	void onNavigate();
	void onActiveDelta(int delta);

private:
	void buildUi();
	void refreshPages();
	void loadProjectToModel();
	void reloadScene();
	void loadEntryToPanel(int index);
	void applyEntryToModel();
	void updateWindowTitle();
	int  currentEntryIndex() const { return m_currentEntry; }
	int  findPageIndexById(int id) const;
	gta2tools::MenuProjectModel* project() { return &m_project; }

	gta2tools::MenuProjectModel m_project;

	MenuScene*     m_scene;
	MenuSceneView* m_view;

	QListWidget* m_pagesList;
	QLineEdit*   m_editHeader;
	QLineEdit*   m_editText;
	QSpinBox*    m_sbX;
	QSpinBox*    m_sbY;
	QSpinBox*    m_sbSize;
	QComboBox*   m_cbAction;
	QSpinBox*    m_sbTarget;
	QCheckBox*   m_chkDim;
	QCheckBox*   m_chkPlay;
	QLabel*      m_status;

	bool m_updating;      // защита от обратной связи при загрузке значений
	int  m_currentEntry;  // выбранный пункт текущей страницы (-1 = нет)
	QString m_currentPath; // путь последнего сохранения/загрузки
};

#endif // !__TOOLS_MENU_EDITOR_MAINWINDOW_H_