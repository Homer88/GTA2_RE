#pragma once

#include <QWidget>

class SaveFile;
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;

// ---------------------------------------------------------------------------
// Weapons tab.
//
// The save stores 15 one-byte ammo counters at 0xBA and a 16-bit "equipped"
// index at 0xD6. Player::sub_4A5B40 initialises sWeapon slots 0..14 for
// Index < CAR_BOMB (15), so slot order is the recovered WeaponType order, not
// the order the old editors guessed. The old tool's numbering disagreed with
// the binary in several places (it listed Electro Gun where the enum has the
// Uzi, and shifted the rest), which is why names come from FieldDefs rather
// than from that table.
// ---------------------------------------------------------------------------
class WeaponTable : public QWidget
{
    Q_OBJECT
public:
    explicit WeaponTable(QWidget *parent = nullptr);

    void setSave(SaveFile *save);
    void apply();

signals:
    void dirtyChanged(bool dirty);

private:
    void reload();
    void touch();

    SaveFile *m_save = nullptr;
    bool m_updating = false;
    bool m_dirty = false;

    // 0x6E..0x7E - 17 powerup timers, read as bytes by Player::sub_4A5A50.
    QSpinBox *m_pup[17]   = { nullptr };
    QLabel   *m_pupName[17] = { nullptr };
    QSpinBox *m_ammo[15]  = { nullptr };
    QLabel   *m_ammoName[15] = { nullptr };
    QComboBox *m_equipped = nullptr;
    QCheckBox *m_remap = nullptr;
};
