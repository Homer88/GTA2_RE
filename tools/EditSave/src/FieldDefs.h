#pragma once

#include <QString>
#include <QVector>
#include <QMetaType>

// ---------------------------------------------------------------------------
// Field manifest for block0 of plyslotN.svg.
//
// Every offset here was read off the retail writer/loader in
// dump/IDA/gta2.exe.c, not guessed:
//
//   Player::sub_4A6B20  (writer)   v4+0x00 posX  -> 0x54
//                                    v4+0x04 posY  -> 0x58
//                                    v4+0x08 posZ  -> 0x5C
//                                    v4+0x0C rot   -> 0x60
//                                    v4+0x10 money -> 0x64  (GetMoneyPlayer)
//                                    v4+0x14 mp    -> 0x68
//                                    v4+0x18 hp    -> 0x6C
//                                    v4+0x3C f644  -> 0x90 .. 0xB7
//                                    v4+0x66 ammo  -> 0xBA .. 0xC8
//                                    v4+0x75 resp  -> 0xC9 .. 0xD2
//                                    v4+0x7F lives -> 0xD4
//                                    v4+0x82 selwp -> 0xD6
//                                    v4+0x84 f678  -> 0xD8
//                                    v4+0x88 f67C  -> 0xDC
//                                    v4+0x8C stars -> 0xE0
//
//   Player::sub_4A6C80  (loader)   reads the same set back.
//   Player::sub_4A5A50  (loader)   powerups from a2+26 == 0x6E, 17 single bytes
//                                    (0x6E..0x7E), NOT 17 words.
//
// 0x12A mission count, 0x12C/0x130 masks and 0x134..0x5E3 the mission table
// come from MissionManager::SaveFile / sub_47EE70.
// ---------------------------------------------------------------------------

enum class FieldKind { U8, U16, U32, Name };

enum class FieldGroup {
    Identity,     // map/style/script, city, level, gang
    Progress,     // money, lives, health, tokens, wanted
    Bonuses,      // powerups
    Gangs,        // gang respect
    Arsenal,      // ammo, weapons
    Internals,    // verbatim copies we have not identified yet
    Dangerous     // proven crashers / map-derived: read-only by default
};

struct FieldDef {
    QString   key;        // stable id, e.g. "gangRespect.3"
    QString   label;      // UI label
    int       off;        // byte offset in block0
    int       size;       // 1, 2, 4, or 25 for Name
    FieldKind kind;
    FieldGroup group;
    quint32   min;
    quint32   max;
    bool      editable;
    QString   note;

    // Names are stored as fixed 25-byte NUL-padded fields, so the byte width
    // differs from the semantic type; keep both in one place.
    int width() const { return kind == FieldKind::Name ? 25 : size; }
};

// The full manifest, in display order. Call once at startup.
const QVector<FieldDef> &fieldDefs();
QString                  fieldGroupTitle(FieldGroup g);

// ---------------------------------------------------------------------------
// Named tables.
//
// Player::sub_4A5B40 builds the player's weapon array like this:
//
//   Index = PISTOL;                       // 0
//   do { *sWeapon++ = Turrel::sub_4CD770(gArsenal, Index++, ped, ...); }
//   while (Index < CAR_BOMB);             // CAR_BOMB == 15
//
// so sWeapon[0..14] are WeaponType 0..14 in order, and the 15 ammo bytes at
// 0xBA..0xC8 are those same slots. That is why the 15 slots line up with the
// head of the WeaponType enum, and why 15 is the count - not 29.
//
// Names come from gta2/Game/Weapon/Weapon.h and gta2/Game/PowerUp/PowerUp.h,
// which are the project's own recovered enums.
enum WeaponSlot {
    WpnPistol = 0, WpnSmg, WpnRocket, WpnElectroGun, WpnMolotov,
    WpnGrenade, WpnShotgun, WpnShocker, WpnFlameGun, WpnSmgGrenade,
    WpnDualPistol, WpnMachineGun, WpnUnknown12, WpnUnknown13, WpnUnknown14,
    WpnSlotCount
};

enum PowerupSlot {
    PupMultiplier = 0, PupLife, PupHealth, PupArmor,
    PupGetOuttaJailFreeCard, PupCopBribe, PupInvulnerability,
    PupDoubleDamage, PupFastReload, PupElectroFingers, PupRespect,
    PupInvisibility, PupInstantGang, PupUnknown13, PupUnknown14,
    PupUnknown15, PupUnknown16,
    PupSlotCount
};

// Translated display names; empty-safe for out-of-range indices.
QString weaponSlotName(int slot);
QString powerupSlotName(int slot);
// What the powerup byte actually does, for tooltips.
QString powerupSlotNote(int slot);

// -1 when the index has no entry in the enum.
int weaponSlotForType(int weaponType);
