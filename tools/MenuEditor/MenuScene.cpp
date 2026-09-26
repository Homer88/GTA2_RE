#include "MenuScene.h"

#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPen>
#include <QBrush>
#include <QVariant>
#include <QFont>
#include <QFontMetricsF>
#include <QPainter>

// Экран меню игры.
static const qreal kScreenW = 640.0;
static const qreal kScreenH = 480.0;

// Пункт меню, который можно перетаскивать мышью (режим редактирования).
class MovableTextItem : public QGraphicsSimpleTextItem {
public:
	MovableTextItem(MenuScene* scene, int index)
		: QGraphicsSimpleTextItem(), m_scene(scene), m_index(index), m_play(false)
	{
		setData(0, index);
		setFlag(QGraphicsItem::ItemIsSelectable, true);
		setFlag(QGraphicsItem::ItemIsMovable, true);
	}

	void setPlay(bool on)
	{
		m_play = on;
		setFlag(QGraphicsItem::ItemIsMovable, !on);
	}

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant& value)
	{
		if (change == ItemPositionChange) {
			QPointF p = value.toPointF();
			if (p.x() < 0.0) p.setX(0.0);
			if (p.y() < 0.0) p.setY(0.0);
			if (p.x() > kScreenW) p.setX(kScreenW);
			if (p.y() > kScreenH) p.setY(kScreenH);
			return p;
		}
		if (change == ItemPositionHasChanged && !m_play)
			m_scene->entryMoved(m_index, (int)pos().x(), (int)pos().y());
		return QGraphicsSimpleTextItem::itemChange(change, value);
	}

private:
	MenuScene* m_scene;
	int m_index;
	bool m_play;
};

MenuScene::MenuScene(QObject* parent)
	: QGraphicsScene(parent), m_project(NULL), m_pageIndex(0), m_play(false), m_active(0), m_header(NULL)
{
	setSceneRect(0.0, 0.0, kScreenW, kScreenH);
}

void MenuScene::setProject(gta2tools::MenuProjectModel* project)
{
	m_project = project;
	if (!m_project || m_project->pages.empty()) {
		m_pageIndex = 0;
		clear();
		return;
	}
	if (m_pageIndex >= (int)m_project->pages.size())
		m_pageIndex = 0;
	m_active = 0;
	rebuild();
}

gta2tools::MenuPageModel* MenuScene::currentPage()
{
	if (!m_project || m_pageIndex < 0 || m_pageIndex >= (int)m_project->pages.size())
		return NULL;
	return &m_project->pages[m_pageIndex];
}

void MenuScene::showPage(int index)
{
	if (!m_project || index < 0 || index >= (int)m_project->pages.size())
		return;
	m_pageIndex = index;
	m_active = 0;
	rebuild();
}

void MenuScene::rebuild()
{
	clear();
	m_header = NULL;
	m_items.clear();

	// Фон экрана меню.
	QGraphicsRectItem* bg = addRect(0.0, 0.0, kScreenW, kScreenH,
	                                QPen(QColor(120, 120, 120)), QBrush(QColor(16, 16, 20)));
	bg->setZValue(-10.0);

	gta2tools::MenuPageModel* page = currentPage();
	if (!page)
		return;

	// Заголовок страницы (по центру сверху).
	if (!page->header.empty()) {
		m_header = addSimpleText(QString::fromStdWString(page->header));
		QFont hf = m_header->font();
		hf.setPointSize(16);
		hf.setBold(true);
		m_header->setFont(hf);
		m_header->setBrush(QBrush(QColor(255, 215, 0)));
		QFontMetricsF fm(hf);
		m_header->setPos((kScreenW - fm.horizontalAdvance(m_header->text())) / 2.0, 8.0);
	}

	// Пункты меню.
	for (size_t i = 0; i < page->entries.size(); i++) {
		gta2tools::MenuEntryModel& e = page->entries[i];
		QString text = QString::fromStdWString(e.text);
		QFont f = font();
		f.setPointSize(e.fontSize > 0 ? e.fontSize : 14);

		MovableTextItem* item = new MovableTextItem(this, (int)i);
		item->setText(text);
		item->setFont(f);
		item->setPos(e.x, e.y);
		item->setZValue((qreal)i + 1.0);

		QColor col = (e.flags & 2) ? QColor(120, 120, 120) : QColor(255, 255, 255);
		if (m_play && (int)i == m_active)
			col = QColor(255, 215, 0); // активный пункт в режиме проверки
		item->setBrush(QBrush(col));

		item->setPlay(m_play);
		item->setSelected(false);
		addItem(item);
		m_items.push_back(item);
	}
}

void MenuScene::updateEntryVisual(int index)
{
	gta2tools::MenuPageModel* page = currentPage();
	if (!page || index < 0 || index >= (int)m_items.size() ||
	    index >= (int)page->entries.size())
		return;

	gta2tools::MenuEntryModel& e = page->entries[index];
	MovableTextItem* item = static_cast<MovableTextItem*>(m_items[index]);
	item->setText(QString::fromStdWString(e.text));
	QFont f = font();
	f.setPointSize(e.fontSize > 0 ? e.fontSize : 14);
	item->setFont(f);
	item->setPos(e.x, e.y);
	QColor col = (e.flags & 2) ? QColor(120, 120, 120) : QColor(255, 255, 255);
	if (m_play && index == m_active)
		col = QColor(255, 215, 0);
	item->setBrush(QBrush(col));
}

void MenuScene::setPlayMode(bool on)
{
	m_play = on;
	if (on) {
		m_active = 0;
		// снимаем выделение с пунктов, чтобы не путало навигацию
		for (size_t i = 0; i < m_items.size(); i++)
			m_items[i]->setSelected(false);
	}
	rebuild();
}

void MenuScene::setActiveIndex(int index)
{
	gta2tools::MenuPageModel* page = currentPage();
	int count = page ? (int)page->entries.size() : 0;
	if (count == 0)
		return;
	m_active = ((index % count) + count) % count;
	rebuild();
}

void MenuScene::onSelectionChanged()
{
	QList<QGraphicsItem*> sel = selectedItems();
	for (int i = 0; i < sel.size(); i++) {
		bool ok = false;
		int idx = sel[i]->data(0).toInt(&ok);
		if (ok && idx >= 0 && idx < (int)m_items.size()) {
			emit entrySelected(idx);
			return;
		}
	}
}

// ---------------------------------------------------------------------------
// MenuSceneView: навигация и фит страницы по окну.
// ---------------------------------------------------------------------------

MenuSceneView::MenuSceneView(MenuScene* scene, QWidget* parent)
	: QGraphicsView(scene, parent), m_scene(scene)
{
	setRenderHint(QPainter::Antialiasing, true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFocusPolicy(Qt::StrongFocus);
}

void MenuSceneView::keyPressEvent(QKeyEvent* e)
{
	switch (e->key()) {
	case Qt::Key_Up:
		emit activeDelta(-1);
		return;
	case Qt::Key_Down:
		emit activeDelta(1);
		return;
	case Qt::Key_Return:
	case Qt::Key_Enter:
		emit navigate();
		return;
	default:
		break;
	}
	QGraphicsView::keyPressEvent(e);
}

void MenuSceneView::mouseDoubleClickEvent(QMouseEvent* e)
{
	QGraphicsItem* item = itemAt(e->pos());
	if (item) {
		bool ok = false;
		int idx = item->data(0).toInt(&ok);
		if (ok)
			emit doubleClickedEntry(idx);
	}
	QGraphicsView::mouseDoubleClickEvent(e);
}

void MenuSceneView::resizeEvent(QResizeEvent* e)
{
	fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(e);
}