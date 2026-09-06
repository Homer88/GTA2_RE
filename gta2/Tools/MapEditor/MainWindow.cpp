#include "MainWindow.h"

#include <QApplication>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QToolBar>
#include <QSplitter>
#include <QTabWidget>
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
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QCheckBox>
#include <QIcon>
#include <QPixmap>
#include <QListView>
#include <QProgressBar>
#include <QPlainTextEdit>
#include <QImage>
#include <QPixmap>
#include <cmath>

#include <vector>

// ---------------------------------------------------------------------------
// ZoneCanvas — отрисовка зон/объектов/узлов поверх сетки карты 256x256.
// ---------------------------------------------------------------------------
ZoneCanvas::ZoneCanvas(QWidget* parent)
	: QWidget(parent)
	, m_zones(nullptr)
	, m_objects(nullptr)
	, m_lights(nullptr)
	, m_junctions(nullptr)
	, m_tileMap(nullptr)
	, m_cityMap(nullptr)
	, m_hSeg(nullptr)
	, m_vSeg(nullptr)
	, m_numJunctions(0)
	, m_layer(-1)
	, m_dragX(-1)
	, m_dragY(-1)
	, m_dragging(false)
	, m_mode(DrawZones)
	, m_pickJunction(-1)
	, m_pickSegment(-1)
	, m_pickSegmentVert(false)
{
	setMinimumSize(300, 300);
}

// ---------------------------------------------------------------------------
// Преобразование пиксель холста -> координаты тайла (та же геометрия, что в
// paintEvent: поле 256x256 с масштабом side/256, отцентровано).
// ---------------------------------------------------------------------------
void ZoneCanvas::tileFromPixel(const QPointF& p, int& x, int& y) const
{
	const int grid = 256;
	int side = qMin(width(), height());
	QRectF field(0, 0, grid, grid);
	field.moveCenter(QPointF(width() / 2.0, height() / 2.0));
	double scale = side / (double)grid;
	double gx = (p.x() - field.left()) / scale;
	double gy = (p.y() - field.top()) / scale;
	x = (int)gx;
	y = (int)gy;
	if (x < 0) x = 0; else if (x > 255) x = 255;
	if (y < 0) y = 0; else if (y > 255) y = 255;
}

void ZoneCanvas::paintAt(const QPoint& pos, bool set)
{
	if (m_layer < 0) return;   // рисование только на конкретном слое
	int x, y;
	tileFromPixel(QPointF(pos), x, y);
	if (x < 0 || y < 0 || !m_cityMap || (int)m_cityMap->size() < 8 * 256 * 256) return;
	if (m_dragging && x == m_dragX && y == m_dragY) return;
	m_dragX = x; m_dragY = y;
	emit tilePainted(m_layer, x, y, set);
}

void ZoneCanvas::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton) {
		if (m_mode == DrawObjects && e->button() == Qt::LeftButton) {
			// Размещение объекта: клик по карте -> центр тайла в pix-координатах.
			int x, y;
			tileFromPixel(QPointF(e->pos()), x, y);
			emit objectPlaced(x * 128 + 64, y * 128 + 64);
		} else if (m_mode == DrawRoad && e->button() == Qt::LeftButton &&
		           m_junctions && m_hSeg && m_vSeg) {
			pickRoadAt(e->pos());
		} else {
			m_dragging = true;
			paintAt(e->pos(), e->button() == Qt::LeftButton);
		}
	}
	QWidget::mousePressEvent(e);
}

// Поиск ближайшего узла/сегмента возле клика (режим Road). Приоритет узлу.
void ZoneCanvas::pickRoadAt(const QPoint& pos)
{
	int tx, ty;
	tileFromPixel(QPointF(pos), tx, ty);
	if (tx < 0 || ty < 0 || tx > 255 || ty > 255) return;
	// Сначала junction: точка попадает в увеличенную рамку узла.
	int bestJ = -1;
	double bestJd = 1e9;
	int n = m_numJunctions < (int)m_junctions->size() ? m_numJunctions : (int)m_junctions->size();
	if (m_mode == DrawRoad) {
		for (int i = 0; i < n; i++) {
			const gta2::Junction& j = (*m_junctions)[i];
			double cx = (j.min_x + j.max_x) / 2.0;
			double cy = (j.min_y + j.max_y) / 2.0;
			double d = (tx - cx) * (tx - cx) + (ty - cy) * (ty - cy);
			if (d < bestJd) { bestJd = d; bestJ = i; }
		}
	}
	// Если нет близкого узла — искать сегмент.
	const double PICK = 3.0;
	if (bestJ < 0 || bestJd > PICK * PICK) {
		// Ближайшая точка к отрезку сегмента (евклидово расстояние до линии).
		double bestS = 1e9; int bestI = -1; bool bestV = false;
		const std::vector<gta2::Segment>* lists[2] = { m_hSeg, m_vSeg };
		for (int v = 0; v < 2; v++) {
			for (size_t i = 0; i < lists[v]->size(); i++) {
				const gta2::Segment& s = (*lists[v])[i];
				double x1 = s.min_x + 0.5, y1 = s.min_y + 0.5;
				double x2 = s.max_x + 0.5, y2 = s.max_y + 0.5;
				double dx = x2 - x1, dy = y2 - y1;
				double len2 = dx * dx + dy * dy;
				double t = len2 > 0 ? ((tx - x1) * dx + (ty - y1) * dy) / len2 : 0;
				if (t < 0) t = 0; else if (t > 1) t = 1;
				double px = x1 + t * dx, py = y1 + t * dy;
				double d = (tx - px) * (tx - px) + (ty - py) * (ty - py);
				if (d < bestS) { bestS = d; bestI = (int)i; bestV = (v == 1); }
			}
		}
		if (bestS < PICK * PICK) {
			emit segmentPicked(bestI, bestV);
			return;
		}
		emit junctionPicked(-1);
		return;
	}
	emit junctionPicked(bestJ);
}

void ZoneCanvas::mouseMoveEvent(QMouseEvent* e)
{
	if (m_dragging && (e->buttons() & (Qt::LeftButton | Qt::RightButton)))
		paintAt(e->pos(), e->buttons() & Qt::LeftButton);
	QWidget::mouseMoveEvent(e);
}

void ZoneCanvas::mouseReleaseEvent(QMouseEvent* e)
{
	m_dragging = false;
	QWidget::mouseReleaseEvent(e);
}

void ZoneCanvas::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	p.fillRect(rect(), QColor(90, 92, 80));

	const int grid = 256;
	int side = qMin(width(), height());
	QRectF field(0, 0, grid, grid);
	field.moveCenter(QPointF(width() / 2.0, height() / 2.0));
	double scale = side / (double)grid;
	QTransform tr;
	tr.translate(field.left(), field.top());
	tr.scale(scale, scale);
	p.setTransform(tr);

	QPen gridPen(QColor(150, 150, 130, 120));
	gridPen.setWidthF(0.05);
	p.setPen(gridPen);
	for (int i = 0; i <= grid; i += 16) {
		p.drawLine(i, 0, i, grid);
		p.drawLine(0, i, grid, i);
	}

	// ===== Базовый слой: карта 256x256 блоков =====
	//   "Top" (m_layer == -1) — верхний вид из TileMap;
	//   конкретный слой — из полной карты (m_city: z*65536 + y*256 + x).
	if (m_tileMap && (int)m_tileMap->size() >= grid * grid) {
		for (int y = 0; y < grid; y++) {
			for (int x = 0; x < grid; x++) {
				const gta2::BlockInfo& b = (m_layer >= 0 && m_cityMap && (int)m_cityMap->size() > m_layer * grid * grid + y * grid + x
					? (*m_cityMap)[(size_t)m_layer * grid * grid + (size_t)y * grid + x]
					: (*m_tileMap)[(size_t)y * grid + x]);
				if (!b.left && !b.right && !b.top && !b.bottom && !b.lid && !b.arrows)
					continue; // пустой блок — пропускаем
				p.setPen(Qt::NoPen);
				p.setBrush(tileColor(b));
				p.drawRect(QRectF(x, y, 1, 1));
			}
		}
	}

	if (m_mode == DrawZones && m_zones) {
		QPen zPen(QColor(255, 0, 0));
		zPen.setWidthF(0.2);
		for (size_t i = 0; i < m_zones->size(); i++) {
			const gta2::ZoneInfo& z = (*m_zones)[i];
			p.setPen(zPen);
			p.setBrush(QColor(255, 0, 0, 40));
			p.drawRect(QRectF(z.x, z.y, z.w, z.h + 1));
			p.drawText(QRectF(z.x + 1, z.y + 1, z.w, z.h),
			           Qt::AlignLeft | Qt::AlignTop,
			           QString::fromUtf8(z.name.c_str()));
		}
	}
	else if (m_mode == DrawObjects && m_objects) {
		QPen oPen(QColor(0, 0, 255));
		oPen.setWidthF(0.3);
		for (size_t i = 0; i < m_objects->size(); i++) {
			const gta2::MapObject& o = (*m_objects)[i];
			p.setPen(oPen);
			p.setBrush(QColor(0, 0, 255, 80));
			// Объекты в пикселях (128x128 зар-область в тайлах 256x256).
			double px = o.x / 128.0;   // 1 тайл = 128 пикселей GTA2
			double py = o.y / 128.0;
			p.drawRect(QRectF(px - 2, py - 2, 4, 4));
		}
	}
	else if (m_mode == DrawLights && m_lights) {
		QPen lPen(QColor(255, 255, 0));
		lPen.setWidthF(0.2);
		for (size_t i = 0; i < m_lights->size(); i++) {
			const gta2::MapLight& l = (*m_lights)[i];
			double px = l.x / 128.0;
			double py = l.y / 128.0;
			p.setPen(lPen);
			p.setBrush(QColor(l.r, l.g, l.b, 60));
			p.drawEllipse(QPointF(px, py), l.radius / 128.0, l.radius / 128.0);
			p.drawPoint(QPointF(px, py));
		}
	}
	// ===== Сеть дорог (RGEN): сегменты и узлы =====
	if ((m_mode == DrawRoad || m_mode == DrawObjects) && m_junctions) {
		// Сегменты: H (горизонтальные) и V (вертикальные).
		QPen segPen(QColor(160, 90, 200));
		segPen.setWidthF(0.15);
		if (m_hSeg) {
			for (size_t i = 0; i < m_hSeg->size(); i++) {
				const gta2::Segment& s = (*m_hSeg)[i];
				p.setPen(segPen);
				p.drawLine(s.min_x + 0.5, s.min_y + 0.5, s.max_x + 0.5, s.max_y + 0.5);
			}
		}
		if (m_vSeg) {
			QPen segPenV(QColor(90, 160, 220));
			segPenV.setWidthF(0.15);
			for (size_t i = 0; i < m_vSeg->size(); i++) {
				const gta2::Segment& s = (*m_vSeg)[i];
				p.setPen(segPenV);
				p.drawLine(s.min_x + 0.5, s.min_y + 0.5, s.max_x + 0.5, s.max_y + 0.5);
			}
		}
	}

	if (m_mode == DrawRoad && m_junctions) {
		QPen jPen(QColor(0, 255, 0));
		jPen.setWidthF(0.25);
		for (int i = 0; i < m_numJunctions && i < (int)m_junctions->size(); i++) {
			const gta2::Junction& j = (*m_junctions)[i];
			p.setPen(jPen);
			p.setBrush(QColor(0, 255, 0, 80));
			p.drawRect(QRectF(j.min_x - 1.5, j.min_y - 1.5, 3, 3));
		}
		// Подсветка выбранного узла.
		if (m_pickJunction >= 0 && m_pickJunction < (int)m_junctions->size()) {
			const gta2::Junction& j = (*m_junctions)[m_pickJunction];
			QPen hp(QColor(255, 128, 0));
			hp.setWidthF(0.05);
			p.setPen(hp);
			p.setBrush(QColor(255, 128, 0, 150));
			p.drawRect(QRectF(j.min_x - 2.5, j.min_y - 2.5, 5, 5));
		}
		// Подсветка выбранного сегмента.
		if (m_pickSegment >= 0) {
			const gta2::Segment* s = m_pickSegmentVert
				? (m_vSeg && m_pickSegment < (int)m_vSeg->size() ? &(*m_vSeg)[m_pickSegment] : NULL)
				: (m_hSeg && m_pickSegment < (int)m_hSeg->size() ? &(*m_hSeg)[m_pickSegment] : NULL);
			if (s) {
				QPen hp(QColor(255, 128, 0));
				hp.setWidthF(0.4);
				p.setPen(hp);
				p.drawLine(s->min_x + 0.5, s->min_y + 0.5, s->max_x + 0.5, s->max_y + 0.5);
			}
		}
	}
}

// ---------------------------------------------------------------------------
// Главное окно
// ---------------------------------------------------------------------------
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_canvas(nullptr)
	, m_updating(false)
	, m_currentZone(-1)
	, m_currentObject(-1)
	, m_currentLight(-1)
	, m_tileIdx(0)
	, m_styLoaded(false)
	, m_currentScript(-1)
{
	buildUi();
	setWindowTitle(tr("GTA2 MapEditor"));
	m_status->setText(tr("No map loaded."));
}

// ---------------------------------------------------------------------------
// Интерфейс
// ---------------------------------------------------------------------------
void MainWindow::buildUi()
{
	QToolBar* tb = addToolBar(tr("File"));
	tb->addAction(tr("Open..."), this, &MainWindow::openFile);
	tb->addAction(tr("Save"),   this, &MainWindow::saveFile);
	tb->addAction(tr("Save As..."), this, &MainWindow::saveFileAs);

	QSplitter* split = new QSplitter(this);

	m_tabs = new QTabWidget(split);

	// ============ ВКЛАДКА ZONES ============
	{
		QWidget* w = new QWidget(m_tabs);
		QHBoxLayout* h = new QHBoxLayout(w);

		QWidget* left = new QWidget(w);
		QVBoxLayout* lv = new QVBoxLayout(left);
		m_zoneList = new QListWidget(left);
		lv->addWidget(m_zoneList, 1);
		connect(m_zoneList, SIGNAL(currentRowChanged(int)), this, SLOT(onZoneSelected(int)));
		QHBoxLayout* btns = new QHBoxLayout();
		QPushButton* bAdd = new QPushButton(tr("Add"), left);
		QPushButton* bDel = new QPushButton(tr("Delete"), left);
		connect(bAdd, &QPushButton::clicked, this, &MainWindow::onAddZone);
		connect(bDel, &QPushButton::clicked, this, &MainWindow::onDeleteZone);
		btns->addWidget(bAdd);
		btns->addWidget(bDel);
		lv->addLayout(btns);

		QWidget* right = new QWidget(w);
		QVBoxLayout* rv = new QVBoxLayout(right);
		QGridLayout* g = new QGridLayout();
		m_zoneIndex = new QLabel(tr("-"), right);
		QFont f = m_zoneIndex->font(); f.setBold(true); m_zoneIndex->setFont(f);
		g->addWidget(m_zoneIndex, 0, 0, 1, 2);

		g->addWidget(new QLabel(tr("Type:"), right), 1, 0);
		m_sbType = new QSpinBox(right); m_sbType->setRange(0, 255);
		g->addWidget(m_sbType, 1, 1);
		connect(m_sbType, SIGNAL(valueChanged(int)), this, SLOT(onTypeChanged(int)));

		g->addWidget(new QLabel(tr("X:"), right), 2, 0);
		m_sbX = new QSpinBox(right); m_sbX->setRange(0, 255);
		g->addWidget(m_sbX, 2, 1);
		connect(m_sbX, SIGNAL(valueChanged(int)), this, SLOT(onXChanged(int)));

		g->addWidget(new QLabel(tr("Y:"), right), 3, 0);
		m_sbY = new QSpinBox(right); m_sbY->setRange(0, 255);
		g->addWidget(m_sbY, 3, 1);
		connect(m_sbY, SIGNAL(valueChanged(int)), this, SLOT(onYChanged(int)));

		g->addWidget(new QLabel(tr("Width (w):"), right), 4, 0);
		m_sbW = new QSpinBox(right); m_sbW->setRange(0, 255);
		g->addWidget(m_sbW, 4, 1);
		connect(m_sbW, SIGNAL(valueChanged(int)), this, SLOT(onWChanged(int)));

		g->addWidget(new QLabel(tr("Height (h):"), right), 5, 0);
		m_sbH = new QSpinBox(right); m_sbH->setRange(0, 255);
		g->addWidget(m_sbH, 5, 1);
		connect(m_sbH, SIGNAL(valueChanged(int)), this, SLOT(onHChanged(int)));

		g->addWidget(new QLabel(tr("Name:"), right), 6, 0);
		m_edName = new QLineEdit(right);
		g->addWidget(m_edName, 6, 1);
		connect(m_edName, &QLineEdit::textChanged, this, &MainWindow::onNameChanged);

		g->setColumnStretch(1, 1);
		rv->addLayout(g);
		rv->addStretch(1);

		h->addWidget(left, 1);
		h->addWidget(right, 1);
		m_tabs->addTab(w, tr("Zones"));
	}

	// ============ ВКЛАДКА OBJECTS ============
	{
		QWidget* w = new QWidget(m_tabs);
		QHBoxLayout* h = new QHBoxLayout(w);

		QWidget* left = new QWidget(w);
		QVBoxLayout* lv = new QVBoxLayout(left);
		m_objList = new QListWidget(left);
		lv->addWidget(m_objList, 1);
		connect(m_objList, SIGNAL(currentRowChanged(int)), this, SLOT(onObjectSelected(int)));
		QHBoxLayout* btns = new QHBoxLayout();
		QPushButton* bAdd = new QPushButton(tr("Add"), left);
		QPushButton* bDel = new QPushButton(tr("Delete"), left);
		connect(bAdd, &QPushButton::clicked, this, &MainWindow::onAddObject);
		connect(bDel, &QPushButton::clicked, this, &MainWindow::onDeleteObject);
		btns->addWidget(bAdd);
		btns->addWidget(bDel);
		lv->addLayout(btns);

		QWidget* right = new QWidget(w);
		QVBoxLayout* rv = new QVBoxLayout(right);
		QGridLayout* g = new QGridLayout();
		m_objIndex = new QLabel(tr("-"), right);
		QFont f = m_objIndex->font(); f.setBold(true); m_objIndex->setFont(f);
		g->addWidget(m_objIndex, 0, 0, 1, 2);

		g->addWidget(new QLabel(tr("X (px):"), right), 1, 0);
		m_sbObjX = new QSpinBox(right); m_sbObjX->setRange(0, 65535);
		g->addWidget(m_sbObjX, 1, 1);
		connect(m_sbObjX, SIGNAL(valueChanged(int)), this, SLOT(onObjXChanged(int)));

		g->addWidget(new QLabel(tr("Y (px):"), right), 2, 0);
		m_sbObjY = new QSpinBox(right); m_sbObjY->setRange(0, 65535);
		g->addWidget(m_sbObjY, 2, 1);
		connect(m_sbObjY, SIGNAL(valueChanged(int)), this, SLOT(onObjYChanged(int)));

		g->addWidget(new QLabel(tr("Rotation:"), right), 3, 0);
		m_sbObjRot = new QSpinBox(right); m_sbObjRot->setRange(0, 255);
		g->addWidget(m_sbObjRot, 3, 1);
		connect(m_sbObjRot, SIGNAL(valueChanged(int)), this, SLOT(onObjRotChanged(int)));

		g->addWidget(new QLabel(tr("Type:"), right), 4, 0);
		m_sbObjType = new QSpinBox(right); m_sbObjType->setRange(0, 255);
		g->addWidget(m_sbObjType, 4, 1);
		connect(m_sbObjType, SIGNAL(valueChanged(int)), this, SLOT(onObjTypeChanged(int)));

		g->setColumnStretch(1, 1);
		rv->addLayout(g);
		m_objSpriteInfo = new QLabel(right);
		m_objSpriteInfo->setAlignment(Qt::AlignCenter);
		rv->addWidget(m_objSpriteInfo);
		m_objSprite = new QLabel(right);
		m_objSprite->setAlignment(Qt::AlignCenter);
		m_objSprite->setMinimumSize(80, 80);
		rv->addWidget(m_objSprite);
		rv->addStretch(1);

		h->addWidget(left, 1);
		h->addWidget(right, 1);
		m_tabs->addTab(w, tr("Objects"));
	}

	// ============ ВКЛАДКА LIGHTS ============
	{
		QWidget* w = new QWidget(m_tabs);
		QHBoxLayout* h = new QHBoxLayout(w);

		QWidget* left = new QWidget(w);
		QVBoxLayout* lv = new QVBoxLayout(left);
		m_lightList = new QListWidget(left);
		lv->addWidget(m_lightList, 1);
		connect(m_lightList, SIGNAL(currentRowChanged(int)), this, SLOT(onLightSelected(int)));

		QWidget* right = new QWidget(w);
		QVBoxLayout* rv = new QVBoxLayout(right);
		QGridLayout* g = new QGridLayout();
		m_lightIndex = new QLabel(tr("-"), right);
		QFont f = m_lightIndex->font(); f.setBold(true); m_lightIndex->setFont(f);
		g->addWidget(m_lightIndex, 0, 0, 1, 2);

		g->addWidget(new QLabel(tr("R:"), right), 1, 0);
		m_sbLightR = new QSpinBox(right); m_sbLightR->setRange(0, 255);
		g->addWidget(m_sbLightR, 1, 1);
		connect(m_sbLightR, SIGNAL(valueChanged(int)), this, SLOT(onLightChanged(int)));

		g->addWidget(new QLabel(tr("G:"), right), 2, 0);
		m_sbLightG = new QSpinBox(right); m_sbLightG->setRange(0, 255);
		g->addWidget(m_sbLightG, 2, 1);
		connect(m_sbLightG, SIGNAL(valueChanged(int)), this, SLOT(onLightChanged(int)));

		g->addWidget(new QLabel(tr("B:"), right), 3, 0);
		m_sbLightB = new QSpinBox(right); m_sbLightB->setRange(0, 255);
		g->addWidget(m_sbLightB, 3, 1);
		connect(m_sbLightB, SIGNAL(valueChanged(int)), this, SLOT(onLightChanged(int)));

		g->addWidget(new QLabel(tr("X:"), right), 4, 0);
		m_sbLightX = new QSpinBox(right); m_sbLightX->setRange(0, 65535);
		g->addWidget(m_sbLightX, 4, 1);
		connect(m_sbLightX, SIGNAL(valueChanged(int)), this, SLOT(onLightChanged(int)));

		g->addWidget(new QLabel(tr("Y:"), right), 5, 0);
		m_sbLightY = new QSpinBox(right); m_sbLightY->setRange(0, 65535);
		g->addWidget(m_sbLightY, 5, 1);
		connect(m_sbLightY, SIGNAL(valueChanged(int)), this, SLOT(onLightChanged(int)));

		g->addWidget(new QLabel(tr("Radius:"), right), 6, 0);
		m_sbLightRadius = new QSpinBox(right); m_sbLightRadius->setRange(0, 65535);
		g->addWidget(m_sbLightRadius, 6, 1);
		connect(m_sbLightRadius, SIGNAL(valueChanged(int)), this, SLOT(onLightChanged(int)));

		g->setColumnStretch(1, 1);
		rv->addLayout(g);
		rv->addStretch(1);

		h->addWidget(left, 1);
		h->addWidget(right, 1);
		m_tabs->addTab(w, tr("Lights"));
	}

	// ============ ВКЛАДКА ROAD ============
	{
		QWidget* w = new QWidget(m_tabs);
		QSplitter* rs = new QSplitter(Qt::Horizontal, w);
		QHBoxLayout* rl = new QHBoxLayout(w);

		// --- Левая часть: список узлов (junctions) ---
		QWidget* lj = new QWidget(rs);
		QVBoxLayout* ljv = new QVBoxLayout(lj);
		m_junctionList = new QListWidget(lj);
		ljv->addWidget(new QLabel(tr("Junctions:"), lj));
		ljv->addWidget(m_junctionList, 1);
		connect(m_junctionList, SIGNAL(currentRowChanged(int)), this, SLOT(onJunctionSelected(int)));

		// --- Правая часть: детали узла (редактируемые) ---
		QWidget* rj = new QWidget(rs);
		QVBoxLayout* rjv = new QVBoxLayout(rj);
		m_junctionIndex = new QLabel(tr("-"), rj);
		QFont fj = m_junctionIndex->font(); fj.setBold(true); m_junctionIndex->setFont(fj);
		rjv->addWidget(m_junctionIndex);
		QGridLayout* jg = new QGridLayout();
		auto addJField = [&](int row, int col, const QString& label, QSpinBox*& spin, int maxv) {
			spin = new QSpinBox(rj);
			spin->setRange(0, maxv);
			jg->addWidget(new QLabel(label, rj), row, col);
			jg->addWidget(spin, row, col + 1);
			connect(spin, SIGNAL(valueChanged(int)), this, SLOT(onJunctionFieldChanged(int)));
		};
		addJField(0, 0, tr("Type:"),           m_sbJType,  255);
		addJField(1, 0, tr("Search type:"),    m_sbJSearch, 255);
		addJField(2, 0, tr("Min X:"),          m_sbJMinX,   255);
		addJField(3, 0, tr("Min Y:"),          m_sbJMinY,   255);
		addJField(4, 0, tr("Max X:"),          m_sbJMaxX,   255);
		addJField(5, 0, tr("Max Y:"),          m_sbJMaxY,   255);
		addJField(6, 0, tr("Link N:"),         m_sbJLinkN,  545);
		addJField(7, 0, tr("Link S:"),         m_sbJLinkS,  545);
		addJField(8, 0, tr("Link W:"),         m_sbJLinkW,  545);
		addJField(9, 0, tr("Link E:"),         m_sbJLinkE,  545);
		jg->setColumnStretch(1, 1);
		jg->setColumnStretch(3, 1);
		rjv->addLayout(jg);
		rjv->addStretch(1);
		rs->addWidget(lj);
		rs->addWidget(rj);
		rs->setStretchFactor(0, 1);
		rs->setStretchFactor(1, 2);

		// --- Верхний блок: сегменты (H/V) ---
		QWidget* segBox = new QWidget(w);
		QSplitter* ss = new QSplitter(Qt::Horizontal, segBox);
		QHBoxLayout* sv = new QHBoxLayout(segBox);
		QWidget* ls = new QWidget(ss);
		QVBoxLayout* lsv = new QVBoxLayout(ls);
		m_cbSegmentType = new QComboBox(ls);
		m_cbSegmentType->addItem(tr("Horizontal (H)"));
		m_cbSegmentType->addItem(tr("Vertical (V)"));
		m_segmentList = new QListWidget(ls);
		lsv->addWidget(m_cbSegmentType);
		lsv->addWidget(new QLabel(tr("Segments:"), ls));
		lsv->addWidget(m_segmentList, 1);
		QWidget* rs2 = new QWidget(ss);
		QVBoxLayout* rsv = new QVBoxLayout(rs2);
		m_segmentIndex = new QLabel(tr("-"), rs2);
		QFont fs = m_segmentIndex->font(); fs.setBold(true); m_segmentIndex->setFont(fs);
		rsv->addWidget(m_segmentIndex);
		m_segmentDetail = new QLabel(rs2);
		m_segmentDetail->setTextInteractionFlags(Qt::TextSelectableByMouse);
		m_segmentDetail->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		rsv->addWidget(m_segmentDetail, 1);

		ss->addWidget(ls);
		ss->addWidget(rs2);
		ss->setStretchFactor(0, 1);
		ss->setStretchFactor(1, 2);
		sv->addWidget(ss);

		connect(m_cbSegmentType, SIGNAL(currentIndexChanged(int)), this, SLOT(onSegmentTypeChanged(int)));
		connect(m_segmentList, SIGNAL(currentRowChanged(int)), this, SLOT(onSegmentSelected(int)));

		rl->addWidget(rs, 3);
		rl->addWidget(segBox, 2);
		m_tabs->addTab(w, tr("Road"));
	}

	// ============ ВКЛАДКА STYLE (палитра тайлов) ============
	{
		QWidget* w = new QWidget(m_tabs);
		QHBoxLayout* h = new QHBoxLayout(w);

		QWidget* left = new QWidget(w);
		QVBoxLayout* lv = new QVBoxLayout(left);
		QPushButton* bSty = new QPushButton(tr("Open .sty..."), left);
		connect(bSty, &QPushButton::clicked, this, &MainWindow::onOpenStyle);
		lv->addWidget(bSty);

		m_tileList = new QListWidget(left);
		m_tileList->setViewMode(QListView::IconMode);
		m_tileList->setIconSize(QSize(64, 64));
		m_tileList->setResizeMode(QListView::Adjust);
		m_tileList->setGridSize(QSize(72, 72));
		m_tileList->setMovement(QListView::Static);
		m_tileList->setUniformItemSizes(true);
		m_tileList->setSelectionMode(QAbstractItemView::SingleSelection);
		connect(m_tileList, SIGNAL(currentRowChanged(int)), this, SLOT(onTileSelected(int)));
		lv->addWidget(m_tileList, 1);

		QWidget* right = new QWidget(w);
		QVBoxLayout* rv = new QVBoxLayout(right);
		m_tileInfo = new QLabel(tr("No style loaded."), right);
		m_tileInfo->setWordWrap(true);
		rv->addWidget(m_tileInfo);
		rv->addStretch(1);

		h->addWidget(left, 2);
		h->addWidget(right, 1);
		m_tabs->addTab(w, tr("Tiles"));
	}

	// ============ ВКЛАДКА SCRIPTS (миссийные .scr) ============
	{
		QWidget* w = new QWidget(m_tabs);
		QSplitter* ss = new QSplitter(Qt::Horizontal, w);
		QHBoxLayout* hl = new QHBoxLayout(w);

		QWidget* left = new QWidget(ss);
		QVBoxLayout* lv = new QVBoxLayout(left);
		QHBoxLayout* btns = new QHBoxLayout();
		QPushButton* bOpen = new QPushButton(tr("Open .scr..."), left);
		QPushButton* bSave = new QPushButton(tr("Save"), left);
		connect(bOpen, &QPushButton::clicked, this, &MainWindow::onOpenScript);
		connect(bSave, &QPushButton::clicked, this, &MainWindow::onSaveScript);
		btns->addWidget(bOpen);
		btns->addWidget(bSave);
		lv->addLayout(btns);
		m_scriptList = new QListWidget(left);
		connect(m_scriptList, SIGNAL(currentRowChanged(int)), this, SLOT(onScriptSelected(int)));
		lv->addWidget(m_scriptList, 1);

		QWidget* right = new QWidget(ss);
		QVBoxLayout* rv = new QVBoxLayout(right);
		m_scriptIndex = new QLabel(tr("-"), right);
		QFont fsi = m_scriptIndex->font(); fsi.setBold(true); m_scriptIndex->setFont(fsi);
		rv->addWidget(m_scriptIndex);
		m_scriptInfo = new QLabel(tr("No script loaded."), right);
		m_scriptInfo->setWordWrap(true);
		m_scriptInfo->setTextInteractionFlags(Qt::TextSelectableByMouse);
		rv->addWidget(m_scriptInfo);
		QSplitter* vs = new QSplitter(Qt::Vertical, right);
		m_scriptDecoded = new QPlainTextEdit(vs);
		m_scriptDecoded->setReadOnly(true);
		m_scriptDecoded->setFont(QFont(QStringLiteral("Courier New"), 9));
		m_scriptHex = new QPlainTextEdit(vs);
		m_scriptHex->setReadOnly(true);
		m_scriptHex->setFont(QFont(QStringLiteral("Courier New"), 9));
		vs->addWidget(m_scriptDecoded);
		vs->addWidget(m_scriptHex);
		vs->setStretchFactor(0, 1);
		vs->setStretchFactor(1, 2);
		rv->addWidget(vs, 1);

		ss->addWidget(left);
		ss->addWidget(right);
		ss->setStretchFactor(0, 1);
		ss->setStretchFactor(1, 2);
		hl->addWidget(ss);
		m_tabs->addTab(w, tr("Scripts"));
	}

	// Канвас (общий для всех вкладок) + выбор уровня карты.
	QWidget* canvasPane = new QWidget(split);
	QVBoxLayout* canvasLay = new QVBoxLayout(canvasPane);
	QHBoxLayout* layerBar = new QHBoxLayout();
	layerBar->addWidget(new QLabel(tr("Layer:"), canvasPane));
	m_layerSel = new QComboBox(canvasPane);
	m_layerSel->addItem(tr("Top"));
	layerBar->addWidget(m_layerSel);
	layerBar->addSpacing(12);
	layerBar->addWidget(new QLabel(tr("Brush ground:"), canvasPane));
	m_cbGround = new QComboBox(canvasPane);
	m_cbGround->addItems(QStringList() << tr("Air") << tr("Road") << tr("Pavement") << tr("Field"));
	layerBar->addWidget(m_cbGround);
	m_chkLid = new QCheckBox(tr("+ Lid"), canvasPane);
	layerBar->addWidget(m_chkLid);
	m_chkSides = new QCheckBox(tr("+ Sides"), canvasPane);
	layerBar->addWidget(m_chkSides);
	m_chkFlat = new QCheckBox(tr("Flat"), canvasPane);
	layerBar->addWidget(m_chkFlat);
	m_chkWall = new QCheckBox(tr("Wall"), canvasPane);
	layerBar->addWidget(m_chkWall);
	layerBar->addStretch(1);

	// Полоса занятости памяти сжатой карты (лимиты для переноса на PSX/PS2).
	QHBoxLayout* memBar = new QHBoxLayout();
	memBar->addWidget(new QLabel(tr("Mem:"), canvasPane));
	m_memCmap = new QProgressBar(canvasPane);
	m_memCmap->setRange(0, 65536);
	m_memCmap->setFormat(tr("CMAP col %v/%m"));
	m_memDmap = new QProgressBar(canvasPane);
	m_memDmap->setRange(0, 131072);
	m_memDmap->setFormat(tr("DMAP col %v/%m"));
	memBar->addWidget(m_memCmap, 2);
	memBar->addWidget(m_memDmap, 2);
	memBar->addStretch(0);

	m_canvas = new ZoneCanvas(canvasPane);
	m_canvas->SetZones(&m_gmp.Zones());
	m_canvas->SetObjects(&m_gmp.Objects());
	m_canvas->SetLights(&m_gmp.Lights());
	m_canvas->SetJunctions(&m_gmp.Junctions(), m_gmp.NumJunctions());
	m_canvas->SetSegments(&m_gmp.HSegments(), &m_gmp.VSegments());
	m_canvas->SetTileMap(&m_gmp.TileMap());
	m_canvas->SetCityMap(&m_gmp.City());
	m_canvas->SetLayer(-1);

	canvasLay->addLayout(layerBar);
	canvasLay->addLayout(memBar);
	canvasLay->addWidget(m_canvas, 1);

	connect(m_layerSel, SIGNAL(currentIndexChanged(int)), this, SLOT(onLayerChanged(int)));
	connect(m_canvas, &ZoneCanvas::tilePainted, this, &MainWindow::onTilePainted);
	connect(m_canvas, &ZoneCanvas::objectPlaced, this, &MainWindow::onObjectPlaced);
	connect(m_canvas, &ZoneCanvas::junctionPicked, this, &MainWindow::onJunctionPicked);
	connect(m_canvas, &ZoneCanvas::segmentPicked, this, &MainWindow::onSegmentPicked);

	split->addWidget(m_tabs);
	split->addWidget(canvasPane);
	split->setStretchFactor(0, 1);
	split->setStretchFactor(1, 2);
	setCentralWidget(split);

	connect(m_tabs, &QTabWidget::currentChanged, [this](int) {
		switch (m_tabs->currentIndex()) {
			case 0:  m_canvas->SetMode(ZoneCanvas::DrawZones); break;
			case 1:  m_canvas->SetMode(ZoneCanvas::DrawObjects); break;
			case 2:  m_canvas->SetMode(ZoneCanvas::DrawLights); break;
			case 3:  m_canvas->SetMode(ZoneCanvas::DrawRoad); break;
			default: break;
		}
	});

	m_status = new QLabel(this);
	statusBar()->addWidget(m_status);

	resize(1000, 600);
}

// ---------------------------------------------------------------------------
// Файл: открыть .gmp
// ---------------------------------------------------------------------------
void MainWindow::openFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open GTA2 Map"), QString(),
	                                            tr("GTA2 Map (*.gmp *.gca);;All files (*)"));
	if (path.isEmpty()) return;

	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot open file:\n%1").arg(path));
		return;
	}
	QByteArray bytes = f.readAll();
	f.close();

	gta2::GmpFile gf;
	const unsigned char* data = reinterpret_cast<const unsigned char*>(bytes.constData());
	if (!gf.Parse(data, (size_t)bytes.size())) {
		QMessageBox::warning(this, tr("Error"),
			tr("Cannot parse map file:\n%1\n%2").arg(path).arg(QString::fromUtf8(gf.Error().c_str())));
		return;
	}

	m_gmp = gf;
	m_filePath = path;
	m_currentZone = -1;
	m_currentObject = -1;
	m_currentLight = -1;
	m_canvas->SetZones(&m_gmp.Zones());
	m_canvas->SetObjects(&m_gmp.Objects());
	m_canvas->SetLights(&m_gmp.Lights());
	m_canvas->SetJunctions(&m_gmp.Junctions(), m_gmp.NumJunctions());
	m_canvas->SetSegments(&m_gmp.HSegments(), &m_gmp.VSegments());
	m_canvas->SetTileMap(&m_gmp.TileMap());
	m_canvas->SetCityMap(&m_gmp.City());
	m_canvas->SetLayer(-1);

	// Уровни карты: 0.7, если есть полная карта города.
	m_updating = true;
	m_layerSel->blockSignals(true);
	m_layerSel->clear();
	m_layerSel->addItem(tr("Top"));
	int layers = (int)(m_gmp.City().size() / (256 * 256));
	if (layers > 8) layers = 8;
	for (int i = 0; i < layers; i++)
		m_layerSel->addItem(tr("Layer %1").arg(i));
	m_layerSel->blockSignals(false);
	m_updating = false;

	reloadZoneList();
	reloadObjectList();
	reloadLightList();
	reloadJunctionList();
	reloadSegmentList();
	refreshMemoryBar();
	updateWindowTitle();
	m_status->setText(tr("Loaded %1 zones, %2 objects, %3 lights, %4 junctions, %5/%6 H/V segments%7 from %8")
		.arg((int)m_gmp.Zones().size())
		.arg((int)m_gmp.Objects().size())
		.arg((int)m_gmp.Lights().size())
		.arg((int)m_gmp.Junctions().size())
		.arg((int)m_gmp.HSegments().size())
		.arg((int)m_gmp.VSegments().size())
		.arg(m_gmp.HasTileMap() ? tr(", %1 tiles").arg((int)m_gmp.TileMap().size()) : QString())
		.arg(QFileInfo(path).fileName()));
}

// ---------------------------------------------------------------------------
// Файл: сохранить
// ---------------------------------------------------------------------------
void MainWindow::saveFile()
{
	if (m_filePath.isEmpty()) { saveFileAs(); return; }

	applyZoneFromPanel(m_currentZone);
	applyObjectFromPanel(m_currentObject);
	applyJunctionFromPanel(m_currentJunction);
	std::vector<unsigned char> blob = m_gmp.Save();

	QFile f(m_filePath);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot write file:\n%1").arg(m_filePath));
		return;
	}
	f.write(reinterpret_cast<const char*>(blob.data()), (qint64)blob.size());
	f.close();

	m_status->setText(tr("Saved %1 bytes to %2")
		.arg((int)blob.size())
		.arg(QFileInfo(m_filePath).fileName()));
	updateWindowTitle();
}

void MainWindow::saveFileAs()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save GTA2 Map"), QString(),
	                                            tr("GTA2 Map (*.gmp)"));
	if (path.isEmpty()) return;
	if (!path.endsWith(QLatin1String(".gmp"), Qt::CaseInsensitive))
		path += QLatin1String(".gmp");
	m_filePath = path;
	saveFile();
}

// ---------------------------------------------------------------------------
// ZONES
// ---------------------------------------------------------------------------
void MainWindow::reloadZoneList()
{
	m_updating = true;
	m_zoneList->clear();
	const std::vector<gta2::ZoneInfo>& zones = m_gmp.Zones();
	for (size_t i = 0; i < zones.size(); i++) {
		const gta2::ZoneInfo& z = zones[i];
		QString item = QString("%1  [%2] %3  (%4x%5)")
			.arg(i, 4).arg((int)z.zone_type)
			.arg(QString::fromUtf8(z.name.c_str()))
			.arg((int)z.w).arg((int)z.h);
		m_zoneList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::onZoneSelected(int index)
{
	if (m_updating) return;
	if (m_currentZone >= 0 && m_currentZone != index)
		applyZoneFromPanel(m_currentZone);
	m_currentZone = index;
	if (index >= 0) loadZoneToPanel(index);
}

void MainWindow::loadZoneToPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Zones().size()) return;
	const gta2::ZoneInfo& z = m_gmp.Zones()[index];
	m_updating = true;
	m_zoneIndex->setText(tr("Zone %1").arg(index));
	m_sbType->setValue(z.zone_type);
	m_sbX->setValue(z.x);
	m_sbY->setValue(z.y);
	m_sbW->setValue(z.w);
	m_sbH->setValue(z.h);
	m_edName->setText(QString::fromUtf8(z.name.c_str()));
	m_updating = false;
}

void MainWindow::applyZoneFromPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Zones().size()) return;
	gta2::ZoneInfo& z = m_gmp.Zones()[index];
	z.zone_type = (unsigned char)m_sbType->value();
	z.x = (unsigned char)m_sbX->value();
	z.y = (unsigned char)m_sbY->value();
	z.w = (unsigned char)m_sbW->value();
	z.h = (unsigned char)m_sbH->value();
	z.name = m_edName->text().toUtf8().constData();
	refreshCanvas();
}

void MainWindow::onAddZone()
{
	gta2::ZoneInfo z;
	z.zone_type = 0;
	z.x = z.y = 0;
	z.w = 10;
	z.h = 10;
	z.name = "new_zone";
	m_gmp.Zones().push_back(z);
	reloadZoneList();
	m_zoneList->setCurrentRow((int)m_gmp.Zones().size() - 1);
	refreshCanvas();
}

void MainWindow::onDeleteZone()
{
	if (m_currentZone < 0 || m_currentZone >= (int)m_gmp.Zones().size()) return;
	m_gmp.Zones().erase(m_gmp.Zones().begin() + m_currentZone);
	m_currentZone = -1;
	reloadZoneList();
	refreshCanvas();
}

void MainWindow::onTypeChanged(int) { if (!m_updating && m_currentZone >= 0) applyZoneFromPanel(m_currentZone); }
void MainWindow::onXChanged(int)    { if (!m_updating && m_currentZone >= 0) applyZoneFromPanel(m_currentZone); }
void MainWindow::onYChanged(int)    { if (!m_updating && m_currentZone >= 0) applyZoneFromPanel(m_currentZone); }
void MainWindow::onWChanged(int)    { if (!m_updating && m_currentZone >= 0) applyZoneFromPanel(m_currentZone); }
void MainWindow::onHChanged(int)    { if (!m_updating && m_currentZone >= 0) applyZoneFromPanel(m_currentZone); }
void MainWindow::onNameChanged(const QString&) { if (!m_updating && m_currentZone >= 0) applyZoneFromPanel(m_currentZone); }

// ---------------------------------------------------------------------------
// OBJECTS
// ---------------------------------------------------------------------------
void MainWindow::reloadObjectList()
{
	m_updating = true;
	m_objList->clear();
	const std::vector<gta2::MapObject>& objs = m_gmp.Objects();
	for (size_t i = 0; i < objs.size(); i++) {
		const gta2::MapObject& o = objs[i];
		QString item = QString("%1  type=%2 rot=%3  (%4,%5)")
			.arg(i, 4).arg((int)o.type).arg((int)o.rotation)
			.arg((int)o.x).arg((int)o.y);
		m_objList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::onObjectSelected(int index)
{
	if (m_updating) return;
	if (m_currentObject >= 0 && m_currentObject != index)
		applyObjectFromPanel(m_currentObject);
	m_currentObject = index;
	if (index >= 0) loadObjectToPanel(index);
}

void MainWindow::loadObjectToPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Objects().size()) return;
	const gta2::MapObject& o = m_gmp.Objects()[index];
	m_updating = true;
	m_objIndex->setText(tr("Object %1").arg(index));
	m_sbObjX->setValue(o.x);
	m_sbObjY->setValue(o.y);
	m_sbObjRot->setValue(o.rotation);
	m_sbObjType->setValue(o.type);
	m_updating = false;
	renderObjectSprite((int)o.type);
}

// Превью спрайта объекта: спрайт = MapObjectSpriteIndex(type) (SPRG/SPRX/PPAL).
void MainWindow::renderObjectSprite(int type)
{
	m_objSprite->setPixmap(QPixmap());
	m_objSpriteInfo->setText(QString());
	if (!m_styLoaded) {
		m_objSpriteInfo->setText(tr("Нет .sty — откройте его на вкладке Tiles"));
		return;
	}
	int idx = m_sty.MapObjectSpriteIndex(type);
	if (idx < 0) {
		m_objSpriteInfo->setText(tr("Не найден спрайт для type=%1 (OBJI/SPRB?)").arg(type));
		return;
	}
	int w = 0, h = 0;
	std::vector<unsigned char> rgba;
	if (!m_sty.RenderSprite(idx, rgba, w, h)) {
		m_objSpriteInfo->setText(tr("Нет спрайта idx=%1").arg(idx));
		return;
	}
	QImage img(&rgba[0], w, h, w * 4, QImage::Format_RGBA8888);
	img = img.copy(); // отсоединить от буфера
	double sc = 200.0 / (w > h ? w : h);
	if (sc > 4) sc = 4;
	if (w && h) {
		m_objSprite->setPixmap(QPixmap::fromImage(img.scaled((int)(w * sc), (int)(h * sc),
		                         Qt::KeepAspectRatio, Qt::SmoothTransformation)));
	}
	m_objSpriteInfo->setText(tr("sprite=%1  %2x%3").arg(idx).arg(w).arg(h));
}

void MainWindow::applyObjectFromPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Objects().size()) return;
	gta2::MapObject& o = m_gmp.Objects()[index];
	o.x = (uint16_t)m_sbObjX->value();
	o.y = (uint16_t)m_sbObjY->value();
	o.rotation = (uint8_t)m_sbObjRot->value();
	o.type = (uint8_t)m_sbObjType->value();
	refreshCanvas();
}

void MainWindow::onAddObject()
{
	gta2::MapObject o;
	o.x = o.y = 0; o.rotation = 0; o.type = 0;
	m_gmp.Objects().push_back(o);
	reloadObjectList();
	m_objList->setCurrentRow((int)m_gmp.Objects().size() - 1);
	refreshCanvas();
}

void MainWindow::onDeleteObject()
{
	if (m_currentObject < 0 || m_currentObject >= (int)m_gmp.Objects().size()) return;
	m_gmp.Objects().erase(m_gmp.Objects().begin() + m_currentObject);
	m_currentObject = -1;
	reloadObjectList();
	refreshCanvas();
}

void MainWindow::onObjXChanged(int)   { if (!m_updating && m_currentObject >= 0) applyObjectFromPanel(m_currentObject); }
void MainWindow::onObjYChanged(int)   { if (!m_updating && m_currentObject >= 0) applyObjectFromPanel(m_currentObject); }
void MainWindow::onObjRotChanged(int) { if (!m_updating && m_currentObject >= 0) applyObjectFromPanel(m_currentObject); }
void MainWindow::onObjTypeChanged(int v)
{
	if (!m_updating && m_currentObject >= 0) {
		applyObjectFromPanel(m_currentObject);
		renderObjectSprite(v);
	}
}

// Размещение объекта MOBJ кликом по карте в режиме Objects.
void MainWindow::onObjectPlaced(int px, int py)
{
	gta2::MapObject o;
	o.x = (uint16_t)(px & 0xFFFF);
	o.y = (uint16_t)(py & 0xFFFF);
	o.rotation = 0;
	o.type = 1;   // по умолчанию первый тип (правка — через панель Objects)
	m_gmp.Objects().push_back(o);
	reloadObjectList();
	m_objList->setCurrentRow((int)m_gmp.Objects().size() - 1);
	refreshCanvas();
	m_status->setText(tr("Added object %1 at (%2,%3) type=%4 — Type/rot/X/Y правится на вкладке Objects")
		.arg((int)m_gmp.Objects().size() - 1).arg(px).arg(py).arg((int)o.type));
}

// ---------------------------------------------------------------------------
// LIGHTS
// ---------------------------------------------------------------------------
void MainWindow::reloadLightList()
{
	m_updating = true;
	m_lightList->clear();
	const std::vector<gta2::MapLight>& lights = m_gmp.Lights();
	for (size_t i = 0; i < lights.size(); i++) {
		const gta2::MapLight& l = lights[i];
		QString item = QString("%1  rgb(%2,%3,%4) r=%5  (%6,%7)")
			.arg(i, 4).arg((int)l.r).arg((int)l.g).arg((int)l.b)
			.arg((int)l.radius).arg((int)l.x).arg((int)l.y);
		m_lightList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::onLightSelected(int index)
{
	if (m_updating) return;
	m_currentLight = index;
	if (index >= 0) loadLightToPanel(index);
}

void MainWindow::loadLightToPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Lights().size()) return;
	const gta2::MapLight& l = m_gmp.Lights()[index];
	m_updating = true;
	m_lightIndex->setText(tr("Light %1").arg(index));
	m_sbLightR->setValue(l.r);
	m_sbLightG->setValue(l.g);
	m_sbLightB->setValue(l.b);
	m_sbLightX->setValue(l.x);
	m_sbLightY->setValue(l.y);
	m_sbLightRadius->setValue(l.radius);
	m_updating = false;
}

void MainWindow::onLightChanged(int)
{
	if (m_updating || m_currentLight < 0 || m_currentLight >= (int)m_gmp.Lights().size()) return;
	gta2::MapLight& l = m_gmp.Lights()[m_currentLight];
	l.r = (uint8_t)m_sbLightR->value();
	l.g = (uint8_t)m_sbLightG->value();
	l.b = (uint8_t)m_sbLightB->value();
	l.x = (uint16_t)m_sbLightX->value();
	l.y = (uint16_t)m_sbLightY->value();
	l.radius = (uint16_t)m_sbLightRadius->value();
	refreshCanvas();
}

// ---------------------------------------------------------------------------
// ROAD (RGEN) — junctions и сегменты
// ---------------------------------------------------------------------------
void MainWindow::reloadJunctionList()
{
	m_updating = true;
	m_junctionList->clear();
	const std::vector<gta2::Junction>& js = m_gmp.Junctions();
	int n = (int)js.size();
	if (m_gmp.NumJunctions() < n) n = m_gmp.NumJunctions();
	for (int i = 0; i < n; i++) {
		const gta2::Junction& j = js[i];
		QString item = QString("%1  [t=%2 s=%3]  (%4,%5)-(%6,%7)")
			.arg(i, 4).arg((int)j.junc_type).arg((int)j.search_type)
			.arg((int)j.min_x).arg((int)j.min_y).arg((int)j.max_x).arg((int)j.max_y);
		m_junctionList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::loadJunctionToPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Junctions().size()) return;
	const gta2::Junction& j = m_gmp.Junctions()[index];
	m_updating = true;
	m_junctionIndex->setText(tr("Junction %1").arg(index));
	m_sbJType->setValue(j.junc_type);
	m_sbJSearch->setValue(j.search_type);
	m_sbJMinX->setValue(j.min_x);
	m_sbJMinY->setValue(j.min_y);
	m_sbJMaxX->setValue(j.max_x);
	m_sbJMaxY->setValue(j.max_y);
	m_sbJLinkN->setValue(j.northIndex());
	m_sbJLinkS->setValue(j.southIndex());
	m_sbJLinkW->setValue(j.westIndex());
	m_sbJLinkE->setValue(j.eastIndex());
	m_updating = false;
}

void MainWindow::applyJunctionFromPanel(int index)
{
	if (index < 0 || index >= (int)m_gmp.Junctions().size()) return;
	gta2::Junction& j = m_gmp.Junctions()[index];
	j.junc_type   = (uint8_t)m_sbJType->value();
	j.search_type = (uint8_t)m_sbJSearch->value();
	j.min_x = (uint8_t)m_sbJMinX->value();
	j.min_y = (uint8_t)m_sbJMinY->value();
	j.max_x = (uint8_t)m_sbJMaxX->value();
	j.max_y = (uint8_t)m_sbJMaxY->value();
	// Связи: сохраняем низкие 9 бит (индекс узла), старшие биты — длина дороги.
	j.north = (uint16_t)((j.north & 0xFE00) | ((uint16_t)m_sbJLinkN->value() & 0x1FF));
	j.south = (uint16_t)((j.south & 0xFE00) | ((uint16_t)m_sbJLinkS->value() & 0x1FF));
	j.west  = (uint16_t)((j.west  & 0xFE00) | ((uint16_t)m_sbJLinkW->value() & 0x1FF));
	j.east  = (uint16_t)((j.east  & 0xFE00) | ((uint16_t)m_sbJLinkE->value() & 0x1FF));
	refreshCanvas();
}

void MainWindow::reloadSegmentList()
{
	m_updating = true;
	m_segmentList->clear();
	bool vert = m_cbSegmentType->currentIndex() == 1;
	const std::vector<gta2::Segment>* segs = vert ? &m_gmp.VSegments() : &m_gmp.HSegments();
	const char* label = vert ? "V" : "H";
	for (size_t i = 0; i < segs->size(); i++) {
		const gta2::Segment& s = (*segs)[i];
		QString item = QString("%1 [%2]  J%3->J%4  (%5,%6)-(%7,%8)")
			.arg((int)i, 4).arg(label)
			.arg((int)s.junction1).arg((int)s.junction2)
			.arg((int)s.min_x).arg((int)s.min_y).arg((int)s.max_x).arg((int)s.max_y);
		m_segmentList->addItem(item);
	}
	m_updating = false;
}

void MainWindow::loadSegmentToPanel(int index)
{
	if (index < 0 || index >= (int)(m_cbSegmentType->currentIndex() == 1
	                                     ? m_gmp.VSegments().size()
	                                     : m_gmp.HSegments().size())) return;
	bool vert = m_cbSegmentType->currentIndex() == 1;
	const gta2::Segment& s = vert ? m_gmp.VSegments()[index] : m_gmp.HSegments()[index];
	m_updating = true;
	m_segmentIndex->setText(tr("%1-Segment %2").arg(vert ? "V" : "H").arg(index));
	QString d = tr(
		"junctions:      %1 -> %2\n"
		"bounding rect:  (%3, %4) - (%5, %6)\n")
		.arg((int)s.junction1).arg((int)s.junction2)
		.arg((int)s.min_x).arg((int)s.min_y).arg((int)s.max_x).arg((int)s.max_y);
	m_segmentDetail->setText(d);
	m_updating = false;
}

void MainWindow::onJunctionSelected(int index)
{
	if (m_updating) return;
	if (m_currentJunction >= 0 && m_currentJunction != index)
		applyJunctionFromPanel(m_currentJunction);
	m_currentJunction = index;
	if (index >= 0) loadJunctionToPanel(index);
}

void MainWindow::onJunctionFieldChanged(int)
{
	if (m_updating) return;
	if (m_currentJunction >= 0)
		applyJunctionFromPanel(m_currentJunction);
}

void MainWindow::onSegmentTypeChanged(int)
{
	if (m_updating) return;
	m_currentSegment = -1;
	reloadSegmentList();
}

void MainWindow::onSegmentSelected(int index)
{
	if (m_updating) return;
	m_currentSegment = index;
	if (index >= 0) loadSegmentToPanel(index);
}

void MainWindow::onSegmentListChanged()
{
	if (m_updating) return;
	m_currentSegment = -1;
	reloadSegmentList();
}

// Выделен узел кликом на канвасе.
void MainWindow::onJunctionPicked(int index)
{
	m_canvas->SetPick(index, -1, false);
	if (index < 0 || index >= (int)m_gmp.Junctions().size()) return;
	if (m_currentJunction >= 0 && m_currentJunction != index)
		applyJunctionFromPanel(m_currentJunction);
	m_currentJunction = index;
	m_updating = true;
	m_junctionList->setCurrentRow(index);
	m_updating = false;
	loadJunctionToPanel(index);
	// Показать вкладку Road, если нет.
	if (m_tabs->currentIndex() != 3) m_tabs->setCurrentIndex(3);
	m_status->setText(tr("Junction %1 selected (t=%2)").arg(index).arg((int)m_gmp.Junctions()[index].junc_type));
}

// Выделен сегмент кликом на канвасе.
void MainWindow::onSegmentPicked(int index, bool vert)
{
	if (index < 0) { m_canvas->SetPick(-1, -1, false); return; }
	m_canvas->SetPick(-1, index, vert);
	m_updating = true;
	if (m_cbSegmentType->currentIndex() != (vert ? 1 : 0))
		m_cbSegmentType->setCurrentIndex(vert ? 1 : 0);
	reloadSegmentList();
	m_updating = false;
	if (index < (int)(vert ? m_gmp.VSegments().size() : m_gmp.HSegments().size())) {
		m_currentSegment = index;
		m_segmentList->setCurrentRow(index);
		loadSegmentToPanel(index);
	}
	m_status->setText(tr("%1-Segment %2 selected (%3,%4)-(%5,%6)")
		.arg(vert ? "V" : "H").arg(index)
		.arg((int)(vert ? m_gmp.VSegments()[index].min_x : m_gmp.HSegments()[index].min_x))
		.arg((int)(vert ? m_gmp.VSegments()[index].min_y : m_gmp.HSegments()[index].min_y))
		.arg((int)(vert ? m_gmp.VSegments()[index].max_x : m_gmp.HSegments()[index].max_x))
		.arg((int)(vert ? m_gmp.VSegments()[index].max_y : m_gmp.HSegments()[index].max_y)));
}

void MainWindow::onLayerChanged(int index)
{
	if (m_updating) return;
	// index 0 = "Top" (верхний вид), 1..8 = слой 0..7.
	m_canvas->SetLayer(index - 1);
	m_status->setText(index == 0
		? tr("Top view. Рисование выключено — выберите слой 0..7.")
		: tr("Layer %1: ЛКМ — красить, ПКМ — стереть").arg(index - 1));
}

void MainWindow::onTilePainted(int z, int x, int y, bool set)
{
	gta2::BlockInfo b;
	if (set) {
		b.slope = (uint8_t)m_cbGround->currentIndex();   // bits 0-1: земля
		// Выбранный тайл кладём на lid и/или боковые грани.
		unsigned t = (unsigned)(m_styLoaded ? (m_tileIdx & 0x03FF) : 0);
		unsigned rot = (unsigned)(m_tileIdx >> 10) & 3;   // биты 14-15: поворот
		bool flat = m_chkFlat->isChecked();
		bool wall = m_chkWall->isChecked();
		unsigned g = t | (flat ? 0x1000 : 0) | (rot << 14);
		if (m_chkLid->isChecked()) b.lid = (uint16_t)g;
		if (m_chkSides->isChecked()) {
			// Боковые грани: wall/бал-стена/фейс/флип/поворот по мануалу.
			unsigned side = t | (wall ? 0x0400 : 0) | (flat ? 0x1000 : 0) | (rot << 14);
			b.left = b.right = b.top = b.bottom = (uint16_t)side;
		}
	}
	m_gmp.SetBlock(z, x, y, b);
	refreshMemoryBar();
	refreshCanvas();
}

// ---------------------------------------------------------------------------
// Полоса занятости памяти: заполненность области column сжатой карты.
// ---------------------------------------------------------------------------
void MainWindow::refreshMemoryBar()
{
	gta2::GmpFile::CompressionStats s = m_gmp.ComputeCompressionStats();
	if (!s.hasCity) {
		m_memCmap->setValue(0);
		m_memCmap->setFormat(tr("CMAP — нет полной карты"));
		m_memDmap->setValue(0);
		m_memDmap->setFormat(tr("DMAP — нет полной карты"));
		return;
	}
	// Движок GTA2 использует зарезервированные слова в начале области column;
	// для индикации берём жёсткий предел: CMAP 0xFFFF, DMAP 0x7FFFFFFF.
	const size_t CMAP_LIMIT = 0xFFFF;
	const size_t DMAP_LIMIT = 0x7FFFFFFF;
	double cf = s.cmapColWords / (double)CMAP_LIMIT;
	double df = s.dmapColWords / (double)DMAP_LIMIT;
	if (cf > 1.0) cf = 1.0;
	if (df > 1.0) df = 1.0;
	m_memCmap->setRange(0, 100);
	m_memDmap->setRange(0, 100);
	m_memCmap->setValue((int)(cf * 100));
	m_memDmap->setValue((int)(df * 100));
	QColor cc = s.cmapFits ? QColor(70, 170, 90) : QColor(220, 60, 60);
	QColor dc = s.dmapFits ? QColor(70, 170, 90) : QColor(220, 60, 60);
	m_memCmap->setStyleSheet(QString("QProgressBar::chunk { background: %1; }").arg(cc.name()));
	m_memDmap->setStyleSheet(QString("QProgressBar::chunk { background: %1; }").arg(dc.name()));
	m_memCmap->setFormat(tr("CMAP %1/%2 words, %3 blk").arg((long long)s.cmapColWords)
		.arg((long long)CMAP_LIMIT).arg((long long)s.cmapBlocks));
	m_memDmap->setFormat(tr("DMAP %1/%2 words, %3 blk").arg((long long)s.dmapColWords)
		.arg((long long)DMAP_LIMIT).arg((long long)s.dmapBlocks));
}

// ---------------------------------------------------------------------------
// STYLE (палитра тайлов из .sty)
// ---------------------------------------------------------------------------
void MainWindow::onOpenStyle()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open GTA2 Style"), QString(),
	                                            tr("GTA2 Style (*.sty);;All files (*)"));
	if (path.isEmpty()) return;
	loadStyleFile(path);
}

void MainWindow::loadStyleFile(const QString& path)
{
	QFile f(path);
	if (!f.open(QIODevice::ReadOnly)) {
		m_tileInfo->setText(tr("Cannot open:\n%1").arg(path));
		return;
	}
	QByteArray bytes = f.readAll();
	f.close();

	gta2::StyFile sty;
	const unsigned char* data = reinterpret_cast<const unsigned char*>(bytes.constData());
	if (!sty.Parse(data, (size_t)bytes.size())) {
		m_tileInfo->setText(tr("Cannot parse style file:\n%1").arg(path));
		return;
	}

	m_sty = sty;
	m_styPath = path;
	m_styLoaded = true;
	m_tileIdx = 0;
	reloadTileList();
	if (m_currentObject >= 0) loadObjectToPanel(m_currentObject);
	m_tileInfo->setText(tr("Style: %1\nTiles: %2\nВыберите тайл — кистью он наносится на lid/борта в течение слоя.")
		.arg(QFileInfo(path).fileName())
		.arg((int)m_sty.NumTiles()));
}

void MainWindow::reloadTileList()
{
	if (!m_styLoaded || !m_tileList) return;
	m_tileList->blockSignals(true);
	m_tileList->clear();
	int n = m_sty.NumTiles();
	if (n > 1024) n = 1024;
	std::vector<unsigned char> rgba;
	for (int i = 0; i < n; i++) {
		QListWidgetItem* item = new QListWidgetItem;
		item->setData(Qt::UserRole, i);
		item->setSizeHint(QSize(64, 64));
		item->setToolTip(QString("Tile %1").arg(i));
		if (m_sty.RenderTile(i, rgba)) {
			QImage img((const unsigned char*)rgba.data(), 64, 64, 64 * 4, QImage::Format_RGBA8888);
			item->setIcon(QPixmap::fromImage(img.copy()));
		}
		m_tileList->addItem(item);
	}
	m_tileList->blockSignals(false);
	if (m_tileList->count() > 0)
		m_tileList->setCurrentRow(0);
}

void MainWindow::onTileSelected(int index)
{
	if (!m_styLoaded || index < 0 || index >= m_tileList->count()) {
		m_tileIdx = 0;
		return;
	}
	QListWidgetItem* it = m_tileList->item(index);
	m_tileIdx = it->data(Qt::UserRole).toInt();
	int tid = m_tileIdx & 0x03FF;
	unsigned rot = (unsigned)(m_tileIdx >> 10) & 3;
	QString f = m_chkFlat->isChecked() ? tr("flat") : tr("solid");
	QString w = m_chkWall->isChecked() ? tr("wall") : tr("no-collide");
	QString sides = m_chkSides->isChecked() ? tr("+sides") : tr("lid-only");
	m_status->setText(tr("Tile %1  (rot=%2, %3, %4, %5) — ЛКМ красить, ПКМ стереть")
		.arg(tid).arg(rot).arg(sides).arg(f).arg(w));
}

// ---------------------------------------------------------------------------
// SCRIPTS (.scr) — миссийные скрипты регионов bil/ste/wil.
// Контейнер: u16 (константа региона) + u16 (номер) + u32 len +
//            3072 B objective + len B скрипт-данных (см. ScrFormat.h).
// ---------------------------------------------------------------------------
void MainWindow::onOpenScript()
{
	QStringList paths = QFileDialog::getOpenFileNames(this, tr("Open GTA2 Scripts"), QString(),
	                                                  tr("GTA2 Script (*.scr);;All files (*)"));
	if (paths.isEmpty()) return;

	for (const QString& path : paths) {
		QFile f(path);
		if (!f.open(QIODevice::ReadOnly)) continue;
		QByteArray bytes = f.readAll();
		f.close();

		gta2::ScrFormat s;
		const unsigned char* data = reinterpret_cast<const unsigned char*>(bytes.constData());
		if (!s.Parse(data, (size_t)bytes.size())) continue;
		m_scripts.push_back(s);
		m_scriptPaths.push_back(path);
	}
	reloadScriptList();
	m_status->setText(tr("Loaded %1 script(s)").arg((int)m_scripts.size()));
}

void MainWindow::onSaveScript()
{
	if (m_currentScript < 0 || m_currentScript >= (int)m_scripts.size()) return;
	const QString& path = m_scriptPaths[m_currentScript];
	std::vector<unsigned char> blob = m_scripts[m_currentScript].Save();

	QFile f(path);
	if (!f.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("Cannot write file:\n%1").arg(path));
		return;
	}
	f.write(reinterpret_cast<const char*>(blob.data()), (qint64)blob.size());
	f.close();
	m_status->setText(tr("Saved %1 bytes to %2").arg((int)blob.size()).arg(QFileInfo(path).fileName()));
}

void MainWindow::reloadScriptList()
{
	m_updating = true;
	m_scriptList->blockSignals(true);
	m_scriptList->clear();
	for (size_t i = 0; i < m_scripts.size(); i++) {
		const gta2::ScrFormat& s = m_scripts[i];
		QString item = QFileInfo(m_scriptPaths[i]).fileName();
		if (s.IsMission())
			item += tr("  [mission w0=%1 w1=%2, %3 B]")
				.arg(s.Word0()).arg(s.Word1()).arg((int)s.DataSize());
		else
			item += tr("  [raw %1 B]").arg((int)s.Raw().size());
		m_scriptList->addItem(item);
	}
	m_scriptList->blockSignals(false);
	m_updating = false;
	if (m_scriptList->count() > 0)
		m_scriptList->setCurrentRow(0);
	else
		m_currentScript = -1;
}

void MainWindow::onScriptSelected(int index)
{
	if (m_updating) return;
	m_currentScript = index;
	if (index >= 0) loadScriptToPanel(index);
}

void MainWindow::loadScriptToPanel(int index)
{
	if (index < 0 || index >= (int)m_scripts.size()) return;
	const gta2::ScrFormat& s = m_scripts[index];
	const QString& path = m_scriptPaths[index];

	m_scriptIndex->setText(tr("Script %1 — %2").arg(index).arg(QFileInfo(path).fileName()));
	if (s.IsMission()) {
		m_scriptInfo->setText(tr(
			"Mission layout (ScrFormat):\n"
			"  word0 (регион): %1   word1 (номер): %2\n"
			"  objective: %3 B   script data: %4 B\n"
			"Полный hex-дамп: 8 байт заголовка + 3072 B objective + скрипт-данные.")
			.arg(s.Word0()).arg(s.Word1())
			.arg((int)s.Objective().size()).arg((int)s.DataSize()));
		std::vector<unsigned char> blob = s.Save();
		m_scriptDecoded->setPlainText(decodeScriptLines(s));
		m_scriptHex->setPlainText(hexDump(blob));
	} else {
		m_scriptInfo->setText(tr("Не миссийная раскладка (вероятно city-заглушка/frontend). "
			"Показываются исходные байты (%1 B).").arg((int)s.Raw().size()));
		m_scriptDecoded->setPlainText(QString());
		m_scriptHex->setPlainText(hexDump(s.Raw()));
	}
}

QString MainWindow::decodeScriptLines(const gta2::ScrFormat& s) const
{
	QString out;
	out.reserve((int)(s.DataSize() * 2) + 512);
	const std::vector<gta2::ScriptLine> lines = s.Lines();
	out += tr("// data: %1 B, записей по 12 байт: %2\n")
		.arg((int)s.DataSize()).arg((int)lines.size());
	int num = 0;
	for (size_t i = 0; i < lines.size(); i++) {
		const gta2::ScriptLine& l = lines[i];
		const char* name = gta2::ScriptOpcodeName(l.type);
		QString n = name && name[0] ? tr("  %1").arg(QString::fromLatin1(name))
		                            : tr("  (op 0x%1)").arg(l.type, 2, 16, QLatin1Char('0')).toUpper();
		out += tr("%1: %2 %3 %4")
			.arg(num++, 5)
			.arg(l.uid, 4, 16, QLatin1Char('0')).toUpper()
			.arg(l.type, 4, 16, QLatin1Char('0')).toUpper()
			.arg(QString("%1 %2 %3 %4 %5")
				.arg(l.p1, 4, 16, QLatin1Char('0')).toUpper()
				.arg(l.p2, 4, 16, QLatin1Char('0')).toUpper()
				.arg(l.p3, 4, 16, QLatin1Char('0')).toUpper()
				.arg(l.p4, 4, 16, QLatin1Char('0')).toUpper()
				.arg(QString::fromLatin1("   @%1").arg(l.offset, 4, 16, QLatin1Char('0')).toUpper())) + n + "\n";
	}
	return out;
}

QString MainWindow::hexDump(const std::vector<unsigned char>& data) const
{
	QString out;
	out.reserve((int)(data.size() * 4));
	const size_t perLine = 16;
	for (size_t off = 0; off < data.size(); off += perLine) {
		out += QString("%1  ").arg((unsigned)off, 6, 16, QLatin1Char('0'));
		QString hexPart, asciiPart;
		for (size_t i = 0; i < perLine; i++) {
			if (off + i < data.size()) {
				hexPart += QString("%1 ").arg(data[off + i], 2, 16, QLatin1Char('0'));
				char c = (char)data[off + i];
				asciiPart += (c >= 32 && c < 127) ? QChar(c) : QLatin1Char('.');
			} else {
				hexPart += "   ";
			}
		}
		out += hexPart + " |" + asciiPart + "|\n";
	}
	return out;
}

// ---------------------------------------------------------------------------
// Вспомогательное
// ---------------------------------------------------------------------------

// Цвет блока по типу уклона/земли + признаку стен/крышки.
// slope_type (из мануала): bits 0-1 ground type (0=air,1=road,2=pavement,3=field...)
QColor ZoneCanvas::tileColor(const gta2::BlockInfo& b) const
{
	unsigned gnd = b.slope & 0x03;
	QColor c;
	switch (gnd) {
		case 0: c = QColor(120, 120, 112); break; // air/undefined — серый
		case 1: c = QColor(64, 74, 90); break;    // road — тёмно-синий/асфальт
		case 2: c = QColor(120, 116, 100); break; // pavement — серо-бежевый
		case 3: c = QColor(84, 108, 84); break;   // field — зелёный
		default: c = QColor(120, 120, 112); break;
	}
	// Крышка (lid) поднимает блок — светлее.
	if (b.lid) c = c.lighter(110);
	// Наличие боковых стен — тёмнее контуры.
	if (b.left || b.right || b.top || b.bottom) c = c.darker(115);
	return c;
}

void MainWindow::refreshCanvas()
{
	if (m_canvas) m_canvas->update();
}

void MainWindow::updateWindowTitle()
{
	QString t = tr("GTA2 MapEditor");
	if (!m_filePath.isEmpty()) t += QString(" - %1").arg(QFileInfo(m_filePath).fileName());
	setWindowTitle(t);
}
