#ifndef __TOOLS_CHAR_EDITOR_MAINWINDOW_H_
#define __TOOLS_CHAR_EDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "CharInfo.h"

class QListWidget;
class QListWidgetItem;
class QSpinBox;
class QCheckBox;
class QLabel;

// Редактор персонажей GTA2:
//   слева - список профессий/персонажей, справа - параметры выбранного.
//   Данные редактируются в памяти (live); сохранение пишет текстовый .gch.
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);

private slots:
	void openFile();
	void saveFile();
	void saveFileAs();
	void loadDefaults();

	void onCharSelected(int index);

	void onHealthChanged(int);
	void onSpeedChanged(int);
	void onSpriteChanged(int);
	void onRemapChanged(int);
	void onWeaponChanged(int);
	void onPoliceToggled(bool);
	void onCriminalToggled(bool);
	void onAgentToggled(bool);

private:
	void buildUi();
	void reloadCharList();
	void loadCharToPanel(int index);
	void applyCharFromPanel(int index);
	void updateWindowTitle();

	gta2::CharInfoFile m_charInfo;

	QListWidget* m_charList;
	QLabel*      m_charName;
	QSpinBox*    m_sbHealth;
	QSpinBox*    m_sbSpeed;
	QSpinBox*    m_sbSprite;
	QSpinBox*    m_sbRemap;
	QSpinBox*    m_sbWeapon;
	QCheckBox*   m_chkPolice;
	QCheckBox*   m_chkCriminal;
	QCheckBox*   m_chkAgent;
	QLabel*      m_status;

	bool m_updating;
	int  m_currentChar;
	QString m_filePath;
};

#endif // !__TOOLS_CHAR_EDITOR_MAINWINDOW_H_