#ifndef __TOOLS_WEAPON_EDITOR_MAINWINDOW_H_
#define __TOOLS_WEAPON_EDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "WeaponInfo.h"

class QListWidget;
class QListWidgetItem;
class QSpinBox;
class QCheckBox;
class QLabel;

// Главное окно редактора оружия GTA2:
//   слева - список типов оружия (28 шт.), справа - параметры выбранного типа.
//   Данные редактируются в памяти (live); сохранение пишет текстовый .gwn файл.
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);

private slots:
	void openFile();
	void saveFile();
	void saveFileAs();
	void loadDefaults();

	void onWeaponSelected(int index);

	void onMaxAmmoChanged(int);
	void onAmmoPickupChanged(int);
	void onReloadSmgChanged(int);
	void onReloadNormalChanged(int);
	void onFireSmgChanged(int);
	void onFireNormalChanged(int);
	void onExplosiveToggled(bool);
	void onCarWeaponToggled(bool);

private:
	void buildUi();
	void reloadWeaponList();
	void loadWeaponToPanel(int index);
	void applyWeaponFromPanel(int index);
	void updateWindowTitle();

	gta2::WeaponInfoFile m_weaponInfo;

	QListWidget*   m_weaponList;
	QLabel*        m_typeName;
	QSpinBox*      m_sbMaxAmmo;
	QSpinBox*      m_sbAmmoPickup;
	QSpinBox*      m_sbReloadSmg;
	QSpinBox*      m_sbReloadNormal;
	QSpinBox*      m_sbFireSmg;
	QSpinBox*      m_sbFireNormal;
	QCheckBox*     m_chkExplosive;
	QCheckBox*     m_chkCarWeapon;
	QLabel*        m_status;

	bool m_updating;
	int  m_currentWeapon;
	QString m_filePath;
};

#endif // !__TOOLS_WEAPON_EDITOR_MAINWINDOW_H_
