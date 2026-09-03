#ifndef __TOOLS_CAR_EDITOR_MAINWINDOW_H_
#define __TOOLS_CAR_EDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "CarInfo.h"
#include "StyFormat.h"
#include "GciFormat.h"

class QListWidget;
class QListWidgetItem;
class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;
class QTableWidget;
class QLabel;
class QPushButton;

// Главное окно редактора машин GTA2:
//   слева - список машин (модель: имя), справа - свойства выбранной машины
//   (графика из секции CARI файла .sty + физика из файла .gci).
// Данные редактируются в памяти (live); сохранение пишет CARI обратно в .sty,
// а физику - в текстовый .gci.
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);

private slots:
	// файл
	void openSty();
	void saveSty();
	void openGci();
	void saveGci();

	// список машин
	void onCarSelected(int index);
	void onAddCar();
	void onDeleteCar();

	// графика (CARI)
	void onGfxFieldChanged(int);
	void onFlagToggled(bool);
	void onRemapCountChanged(int);
	void onRemapCellChanged(int row, int col);
	void onDoorCountChanged(int);
	void onDoorCellChanged(int row, int col);

	// физика (GCI)
	void onPhysIntChanged(int);
	void onPhysDoubleChanged(double);

private:
	void buildUi();
	void reloadCarList();
	void loadCarToPanel(int index);
	void applyCarFromPanel(int index);
	void updateWindowTitle();
	int  currentCarIndex() const { return m_currentCar; }
	int  carIndexAtUi() const;   // индекс машины по данным в панели (для применения)
	gta2::CarInfo* currentCar(); // указатель на CarInfo выбранной машины (или NULL)
	gta2::GciCar*  currentGci(); // указатель на GciCar по model выбранной машины (или NULL)

	// Пометка списка на обновление без потери текущей позиции.
	void markListStale() { m_listStale = true; }

	gta2::StyFile      m_sty;
	gta2::CarInfoList  m_cars;
	gta2::GciFile      m_gci;

	QListWidget* m_carList;
	QSpinBox*    m_sbModel;
	QSpinBox*    m_sbSprite;
	QSpinBox*    m_sbW;
	QSpinBox*    m_sbH;
	QSpinBox*    m_sbPassengers;
	QSpinBox*    m_sbWreck;
	QSpinBox*    m_sbRating;
	QSpinBox*    m_sbFwOff;
	QSpinBox*    m_sbRwOff;
	QSpinBox*    m_sbFwinOff;
	QSpinBox*    m_sbRwinOff;
	QCheckBox*   m_chkFlag[16];
	QSpinBox*    m_sbRemapCount;
	QTableWidget* m_tblRemap;
	QSpinBox*    m_sbDoorCount;
	QTableWidget* m_tblDoor;

	QSpinBox*    m_sbTurbo;
	QSpinBox*    m_sbValue;
	QLabel*      m_physName;
	QDoubleSpinBox* m_dbPhys[17];

	QLabel* m_status;
	bool m_updating;      // защита от обратной связи при загрузке значений
	int  m_currentCar;    // выбранная машина в списке (-1 = нет)
	bool m_listStale;     // список нужно перестроить, но сохранив позицию
	QString m_styPath;    // путь последнего .sty
	QString m_gciPath;    // путь последнего .gci
};

#endif // !__TOOLS_CAR_EDITOR_MAINWINDOW_H_
