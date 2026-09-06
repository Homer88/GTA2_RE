#ifndef __TOOLS_MAP_EDITOR_MAINWINDOW_H_
#define __TOOLS_MAP_EDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "GmpFile.h"
#include "StyFormat.h"
#include "ScrFormat.h"
#include "ScriptOpcodeTable.h"

class QListWidget;
class QListWidgetItem;
class QLineEdit;
class QSpinBox;
class QLabel;
class QTabWidget;
class QComboBox;
class QPlainTextEdit;
class ZoneCanvas;

// Главное окно редактора карт GTA2 (полный .gmp).
//   Вкладки: Zones (области), Objects (объекты), Lights (света),
//            Road (дорожная сеть) + общий канвас отрисовки.
//   Данные редактируются в памяти; сохранение пишет обратно в .gmp
//   без потери остальных секций (обеспечивает core::GmpFile).
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);

private slots:
	void openFile();
	void saveFile();
	void saveFileAs();

	// --- Zones ---
	void onZoneSelected(int index);
	void onAddZone();
	void onDeleteZone();
	void onTypeChanged(int);
	void onXChanged(int);
	void onYChanged(int);
	void onWChanged(int);
	void onHChanged(int);
	void onNameChanged(const QString&);

	// --- Objects ---
	void onObjectSelected(int index);
	void onAddObject();
	void onDeleteObject();
	void onObjXChanged(int);
	void onObjYChanged(int);
	void onObjRotChanged(int);
	void onObjTypeChanged(int);

	// --- Lights ---
	void onLightSelected(int index);
	void onLightChanged(int);

	// --- Road (RGEN) ---
	void onJunctionSelected(int index);
	void onSegmentListChanged();
	void onSegmentSelected(int index);
	void onSegmentTypeChanged(int);
	void onJunctionFieldChanged(int);
	void onJunctionPicked(int index);
	void onSegmentPicked(int index, bool vert);

	// --- Map layers ---
	void onLayerChanged(int index);
	void onTilePainted(int z, int x, int y, bool set);
	void onObjectPlaced(int px, int py);

	// --- Style (палитра тайлов) ---
	void onOpenStyle();
	void onTileSelected(int index);

	// --- Scripts (миссийные .scr) ---
	void onOpenScript();
	void onSaveScript();
	void onScriptSelected(int index);

private:
	void buildUi();
	void updateWindowTitle();
	void refreshCanvas();

	// Style: загрузка .sty и построение палитры тайлов.
	void loadStyleFile(const QString& path);
	void reloadTileList();

// Scripts
void reloadScriptList();
void loadScriptToPanel(int index);
QString decodeScriptLines(const gta2::ScrFormat& s) const;
	// Представление байтов в hex-виде (16 байт на строку) для просмотра .scr.
	QString hexDump(const std::vector<unsigned char>& data) const;

	// Zones
	void reloadZoneList();
	void loadZoneToPanel(int index);
	void applyZoneFromPanel(int index);

	// Objects
	void reloadObjectList();
	void loadObjectToPanel(int index);
	// Превью спрайта объекта по его type (SPRG/SPRX/PPAL из .sty).
	void renderObjectSprite(int type);
	void applyObjectFromPanel(int index);

	// Lights
	void reloadLightList();
	void loadLightToPanel(int index);

	// Road (RGEN)
	void reloadJunctionList();
	void reloadSegmentList();
	void loadJunctionToPanel(int index);
	void applyJunctionFromPanel(int index);
	void loadSegmentToPanel(int index);

	gta2::GmpFile m_gmp;

	// --- Zones ---
	QListWidget* m_zoneList;
	QLabel*    m_zoneIndex;
	QSpinBox*  m_sbType;
	QSpinBox*  m_sbX;
	QSpinBox*  m_sbY;
	QSpinBox*  m_sbW;
	QSpinBox*  m_sbH;
	QLineEdit* m_edName;
	int  m_currentZone;

	// --- Objects ---
	QListWidget* m_objList;
	QLabel*    m_objIndex;
	QSpinBox*  m_sbObjX;
	QSpinBox*  m_sbObjY;
	QSpinBox*  m_sbObjRot;
	QSpinBox*  m_sbObjType;
	QLabel*    m_objSprite;    // превью спрайта объекта (SPRG из .sty)
	QLabel*    m_objSpriteInfo;
	int  m_currentObject;

	// --- Lights ---
	QListWidget* m_lightList;
	QLabel*    m_lightIndex;
	QSpinBox*  m_sbLightR;
	QSpinBox*  m_sbLightG;
	QSpinBox*  m_sbLightB;
	QSpinBox*  m_sbLightX;
	QSpinBox*  m_sbLightY;
	QSpinBox*  m_sbLightRadius;
	int  m_currentLight;

	// --- Road ---
	QListWidget* m_junctionList;
	QListWidget* m_segmentList;
	QComboBox*   m_cbSegmentType;   // H / V
	QLabel*    m_junctionIndex;
	QLabel*    m_segmentIndex;
	QLabel*    m_segmentDetail;
	// Поля узла (редактируются).
	QSpinBox* m_sbJType;
	QSpinBox* m_sbJSearch;
	QSpinBox* m_sbJMinX;
	QSpinBox* m_sbJMinY;
	QSpinBox* m_sbJMaxX;
	QSpinBox* m_sbJMaxY;
	QSpinBox* m_sbJLinkN;
	QSpinBox* m_sbJLinkS;
	QSpinBox* m_sbJLinkW;
	QSpinBox* m_sbJLinkE;
	int  m_currentJunction;
	int  m_currentSegment;

	QTabWidget* m_tabs;
	ZoneCanvas* m_canvas;
	QLabel*     m_status;
	QComboBox*  m_layerSel;   // выбор уровня карты: "Top" или 0..7
	QComboBox*  m_cbGround;   // кисть: тип земли (air/road/pavement/field)
	class QCheckBox* m_chkLid;
	class QCheckBox* m_chkSides;   // красить боковые грани тайлом
	class QCheckBox* m_chkFlat;    // бит 12 (flat) у lid
	class QCheckBox* m_chkWall;    // бит 10 (wall) у боковых граней

	// --- Style (палитра тайлов) ---
	QListWidget* m_tileList;
	QLabel*    m_tileInfo;
	int        m_tileIdx;      // выбранный тайл (графику), 0 = пусто
	gta2::StyFile m_sty;
	QString    m_styPath;
	bool       m_styLoaded;

	// --- Память сжатой карты (CMAP/DMAP) ---
	class QProgressBar* m_memCmap;
	class QProgressBar* m_memDmap;

	// Пересчёт и показ полосы занятости памяти сжатой карты.
	void refreshMemoryBar();

	// --- Scripts (.scr) ---
	QListWidget* m_scriptList;
QLabel*    m_scriptIndex;
QLabel*    m_scriptInfo;
QPlainTextEdit* m_scriptDecoded;
QPlainTextEdit* m_scriptHex;
	std::vector<gta2::ScrFormat> m_scripts;   // разобранные скрипты
	std::vector<QString> m_scriptPaths;       // пути исходных файлов
	int m_currentScript;

	bool m_updating;
	QString m_filePath;
};

// Канвас отрисовки: режимы отображения зон / объектов / узлов дорог.
class ZoneCanvas : public QWidget {
	Q_OBJECT
public:
	enum DrawMode { DrawZones, DrawObjects, DrawLights, DrawRoad };

	explicit ZoneCanvas(QWidget* parent = NULL);

	void SetZones(const std::vector<gta2::ZoneInfo>* zones) { m_zones = zones; update(); }
	void SetMode(DrawMode m) { m_mode = m; update(); }
	void SetObjects(const std::vector<gta2::MapObject>* o) { m_objects = o; update(); }
	void SetLights(const std::vector<gta2::MapLight>* l) { m_lights = l; update(); }
	void SetJunctions(const std::vector<gta2::Junction>* j, int num) { m_junctions = j; m_numJunctions = num; update(); }
	void SetSegments(const std::vector<gta2::Segment>* h, const std::vector<gta2::Segment>* v) { m_hSeg = h; m_vSeg = v; update(); }
	// Несжатая карта (UMAP): 256x256 блоков (block_info). Рисуется базовым слоем.
	void SetTileMap(const std::vector<gta2::BlockInfo>* t) { m_tileMap = t; update(); }
	// Полная 8-слойная карта города (z*65536 + y*256 + x).
	void SetCityMap(const std::vector<gta2::BlockInfo>* c) { m_cityMap = c; update(); }
	// Текущий отображаемый слой: -1 = "верхний" вид (TileMap), 0..7 = конкретный z.
	void SetLayer(int z) { m_layer = z; update(); }
	// Выделение (режим Road): подсветить узел/сегмент (-1 = сбросить).
	void SetPick(int junction, int seg, bool segVert) {
		m_pickJunction = junction; m_pickSegment = seg; m_pickSegmentVert = segVert; update();
	}

signals:
	// Клик/протаскивание по карте: (x,y) тайла, set=true — кисть, set=false — стереть.
	// Излучается только при выбранном конкретном слое (m_layer >= 0).
	void tilePainted(int z, int x, int y, bool set);
	// Клик в режиме Objects: разместить объект в pix-координатах тайла.
	void objectPlaced(int px, int py);
	// Клик в режиме Road/DrawObjects: выделен junction (-1 если нет).
	void junctionPicked(int index);
	// Клик в режиме Road: выделен сегмент (index в активном H/V списке, -1 если нет);
	// vert=true если это вертикальный список.
	void segmentPicked(int index, bool vert);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	// Пиксель холста -> координаты тайла (255 при вне поля).
	void tileFromPixel(const QPointF& p, int& x, int& y) const;
	void paintAt(const QPoint& pos, bool set);
	// Выделение ближайшего узла/сегмента (режим Road).
	void pickRoadAt(const QPoint& pos);
	// Цвет блока (тайла) по типу уклона/земли.
	QColor tileColor(const gta2::BlockInfo& b) const;

	const std::vector<gta2::ZoneInfo>* m_zones;
	const std::vector<gta2::MapObject>* m_objects;
	const std::vector<gta2::MapLight>* m_lights;
	const std::vector<gta2::Junction>* m_junctions;
	const std::vector<gta2::BlockInfo>* m_tileMap;
	const std::vector<gta2::BlockInfo>* m_cityMap;
	const std::vector<gta2::Segment>* m_hSeg;
	const std::vector<gta2::Segment>* m_vSeg;
	int m_numJunctions;
	int m_layer;
	int m_dragX, m_dragY;
	bool m_dragging;
	DrawMode m_mode;
	// Выделение (режим Road): номер узла/сегмента или -1.
	int m_pickJunction;
	int m_pickSegment;
	bool m_pickSegmentVert;
};

#endif // !__TOOLS_MAP_EDITOR_MAINWINDOW_H_
