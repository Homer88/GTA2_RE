#include "WeaponTable.h"
#include "SaveFile.h"
#include "FieldDefs.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>

namespace {
constexpr int kPupOff = 0x6E;   // sub_4A5A50: a2 + 26, 17 single bytes
constexpr int kAmmoOff = 0xBA;
constexpr int kEquippedOff = 0xD6;
constexpr int kRemapOff = 0xD3;
constexpr int kPupMax = 9999;
} // namespace

WeaponTable::WeaponTable(QWidget *parent)
    : QWidget(parent)
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(10, 10, 10, 10);
    root->setSpacing(8);

    auto *hint = new QLabel(
        tr("Ammo counters and powerup timers live in the .svg. A timer of 0 means the "
           "effect is not running; a non-zero value counts down while it lasts. Values "
           "written here are passed to the game as-is."), this);
    hint->setWordWrap(true);
    hint->setStyleSheet(QStringLiteral("color: palette(mid);"));
    root->addWidget(hint);

    auto *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    auto *body = new QWidget(scroll);
    auto *cols = new QHBoxLayout(body);
    cols->setContentsMargins(0, 0, 0, 0);

    // ---- weapons ---------------------------------------------------------
    auto *wBox = new QGroupBox(tr("Weapons"), body);
    auto *wLay = new QGridLayout(wBox);
    wLay->addWidget(new QLabel(tr("Slot"), wBox), 0, 0);
    wLay->addWidget(new QLabel(tr("Name"), wBox), 0, 1);
    wLay->addWidget(new QLabel(tr("Ammo"), wBox), 0, 2);
    for (int i = 0; i < WpnSlotCount; ++i) {
        m_ammoName[i] = new QLabel(weaponSlotName(i), wBox);
        m_ammo[i] = new QSpinBox(wBox);
        m_ammo[i]->setRange(0, 255);
        m_ammo[i]->setGroupSeparatorShown(false);
        wLay->addWidget(m_ammoName[i], i + 1, 0);
        wLay->addWidget(m_ammo[i],     i + 1, 1);
        wLay->addWidget(new QLabel(QStringLiteral("0x%1").arg(kAmmoOff + i, 2, 16, QChar('0')), wBox),
                        i + 1, 2);
    }
    wLay->setColumnStretch(1, 1);

    auto *eqRow = new QHBoxLayout;
    eqRow->addWidget(new QLabel(tr("Equipped:"), wBox));
    m_equipped = new QComboBox(wBox);
    m_equipped->addItem(tr("none"), 0xFFFF);
    for (int i = 0; i < WpnSlotCount; ++i)
        m_equipped->addItem(QStringLiteral("%1. %2").arg(i).arg(weaponSlotName(i)), i);
    eqRow->addWidget(m_equipped, 1);
    m_remap = new QCheckBox(tr("weapon remap (0x%1)").arg(kRemapOff), wBox);
    m_remap->setToolTip(tr("game-side remap flag; leave as the game wrote it"));
    eqRow->addWidget(m_remap);
    wLay->addLayout(eqRow, WpnSlotCount + 1, 0, 1, 3);
    cols->addWidget(wBox, 1);

    // ---- powerups --------------------------------------------------------
    auto *pBox = new QGroupBox(tr("Powerups"), body);
    auto *pLay = new QGridLayout(pBox);
    pLay->addWidget(new QLabel(tr("Slot"), pBox), 0, 0);
    pLay->addWidget(new QLabel(tr("Name"), pBox), 0, 1);
    pLay->addWidget(new QLabel(tr("Timer"), pBox), 0, 2);
    for (int i = 0; i < PupSlotCount; ++i) {
        m_pupName[i] = new QLabel(powerupSlotName(i), pBox);
        m_pup[i] = new QSpinBox(pBox);
        m_pup[i]->setRange(0, kPupMax);
        m_pup[i]->setGroupSeparatorShown(false);
        m_pup[i]->setToolTip(tr("%1 - %2").arg(0x6E + i).arg(powerupSlotNote(i)));
        pLay->addWidget(m_pupName[i], i + 1, 0);
        pLay->addWidget(m_pup[i],     i + 1, 1);
        pLay->addWidget(new QLabel(QStringLiteral("0x%1").arg(kPupOff + i, 2, 16, QChar('0')), pBox),
                        i + 1, 2);
    }
    pLay->setColumnStretch(1, 1);
    cols->addWidget(pBox, 1);

    scroll->setWidget(body);
    root->addWidget(scroll, 1);

    auto *btnRow = new QHBoxLayout;
    auto *clearPup = new QPushButton(tr("All powerups = 0"), this);
    clearPup->setToolTip(tr("Clears every powerup timer"));
    auto *maxAmmo = new QPushButton(tr("Refill all ammo"), this);
    maxAmmo->setToolTip(tr("Sets every ammo counter to 255"));
    btnRow->addWidget(clearPup);
    btnRow->addWidget(maxAmmo);
    btnRow->addStretch(1);
    root->addLayout(btnRow);

    // Every control raises dirty once; apply() pushes values into the save.
    for (int i = 0; i < WpnSlotCount; ++i)
        connect(m_ammo[i], QOverload<int>::of(&QSpinBox::valueChanged),
                this, [this]{ touch(); });
    for (int i = 0; i < PupSlotCount; ++i)
        connect(m_pup[i], QOverload<int>::of(&QSpinBox::valueChanged),
                this, [this]{ touch(); });
    connect(m_equipped, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this]{ touch(); });
    connect(m_remap, &QCheckBox::toggled, this, [this]{ touch(); });

    connect(clearPup, &QPushButton::clicked, this, [this] {
        m_updating = true;
        for (int i = 0; i < PupSlotCount; ++i) m_pup[i]->setValue(0);
        m_updating = false;
        touch();
    });
    connect(maxAmmo, &QPushButton::clicked, this, [this] {
        m_updating = true;
        for (int i = 0; i < WpnSlotCount; ++i) m_ammo[i]->setValue(255);
        m_updating = false;
        touch();
    });
}

void WeaponTable::touch()
{
    if (m_updating)
        return;
    if (!m_dirty) {
        m_dirty = true;
        emit dirtyChanged(true);
    }
}

void WeaponTable::setSave(SaveFile *save)
{
    m_save = save;
    reload();
}

void WeaponTable::reload()
{
    m_updating = true;
    const bool have = m_save && m_save->hasSvg();
    setEnabled(have);
    for (int i = 0; i < WpnSlotCount; ++i)
        m_ammo[i]->setValue(have ? m_save->u8(kAmmoOff + i) : 0);
    for (int i = 0; i < PupSlotCount; ++i)
        m_pup[i]->setValue(have ? m_save->u8(kPupOff + i) : 0);
    if (have) {
        const int eq = m_save->u16(kEquippedOff);
        const int idx = m_equipped->findData(eq);
        m_equipped->setCurrentIndex(idx >= 0 ? idx : 0);
        m_remap->setChecked(m_save->u8(kRemapOff) != 0);
    } else {
        m_equipped->setCurrentIndex(0);
        m_remap->setChecked(false);
    }
    m_updating = false;
    if (m_dirty) {
        m_dirty = false;
        emit dirtyChanged(false);
    }
}

void WeaponTable::apply()
{
    if (!m_save || !m_save->hasSvg())
        return;
    for (int i = 0; i < WpnSlotCount; ++i)
        m_save->setU8(kAmmoOff + i, quint8(m_ammo[i]->value()));
    for (int i = 0; i < PupSlotCount; ++i)
        m_save->setU8(kPupOff + i, quint8(m_pup[i]->value()));
    m_save->setU16(kEquippedOff, quint16(m_equipped->currentData().toInt()));
    m_save->setU8(kRemapOff, m_remap->isChecked() ? 1 : 0);
    if (m_dirty) {
        m_dirty = false;
        emit dirtyChanged(false);
    }
}
