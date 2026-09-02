#ifndef __TOOLS_MENU_SCENE_H_
#define __TOOLS_MENU_SCENE_H_

#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "MenuDataModel.h"

class QGraphicsSimpleTextItem;

// Сцена «живого» отображения страницы меню (экран игры 640x480).
// Пункты меню рисуются списком; в режиме редактирования их можно двигать мышью,
// в режиме проверки (play) работает навигация игры (вверх/вниз/Enter).
class MenuScene : public QGraphicsScene {
	Q_OBJECT
public:
	MenuScene(QObject* parent = NULL);

	// Проект принадлежит окну (MainWindow), сцена только читает/обновляет его.
	void setProject(gta2tools::MenuProjectModel* project);
	void showPage(int index);
	int pageIndex() const { return m_pageIndex; }
	gta2tools::MenuPageModel* currentPage();

	// Полная перерисовка страницы из модели.
	void rebuild();
	// Обновить внешний вид одного пункта по индексу (текст/размер/флаг).
	void updateEntryVisual(int index);

	void setPlayMode(bool on);
	bool playMode() const { return m_play; }
	void setActiveIndex(int index);
	int activeIndex() const { return m_active; }

public slots:
	void onSelectionChanged();

signals:
	void entrySelected(int index);            // выбран пункт
	void entryMoved(int index, int x, int y); // пункт перетащен мышь

private:
	gta2tools::MenuProjectModel* m_project;
	int m_pageIndex;
	bool m_play;
	int m_active;
	std::vector<QGraphicsSimpleTextItem*> m_items; // пункты меню (по порядку модели)
	QGraphicsSimpleTextItem* m_header;             // заголовок страницы
};

// Вид сцены: навигация клавишами (игра), двойной клик - редактирование пункта.
class MenuSceneView : public QGraphicsView {
	Q_OBJECT
public:
	MenuSceneView(MenuScene* scene, QWidget* parent = NULL);

protected:
	void keyPressEvent(QKeyEvent* e);
	void mouseDoubleClickEvent(QMouseEvent* e);
	void resizeEvent(QResizeEvent* e);

signals:
	void navigate();             // Enter: выполнить действие пункта (проверка)
	void activeDelta(int delta); // вверх/вниз (проверка)
	void doubleClickedEntry(int index);

private:
	MenuScene* m_scene;
};

#endif // !__TOOLS_MENU_SCENE_H_