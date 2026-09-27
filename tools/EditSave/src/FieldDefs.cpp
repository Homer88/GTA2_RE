#include "FieldDefs.h"

#include <QCoreApplication>

namespace {

FieldDef makeF(const QString &key, const QString &label, int off, int size,
               FieldKind kind, FieldGroup grp,
               quint32 lo, quint32 hi, bool editable, const QString &note)
{
    FieldDef f;
    f.key      = key;
    f.label    = label;
    f.off      = off;
    f.size     = size;
    f.kind     = kind;
    f.group    = grp;
    f.min      = lo;
    f.max      = hi;
    f.editable = editable;
    f.note     = note;
    return f;
}

QVector<FieldDef> build()
{
    QVector<FieldDef> v;

    // ---- identity ---------------------------------------------------------
    v << makeF("map",    "Map file",    0x00, 25, FieldKind::Name, FieldGroup::Identity,
               0, 0, true,  "e.g. data\\wil.gmp - selects the level")
      << makeF("style",  "Style file",  0x19, 25, FieldKind::Name, FieldGroup::Identity,
               0, 0, true,  "e.g. data\\wil.sty")
      << makeF("script", "Script file", 0x32, 25, FieldKind::Name, FieldGroup::Identity,
               0, 0, true,  "e.g. data\\wil.scr - the mission script")
      << makeF("arena",  "Arena",       0x4B, 1, FieldKind::U8, FieldGroup::Identity,
               0, 2, true,  "MapGm::GetPlayerArena - which of the 3 cities")
      << makeF("bonusStage", "Bonus stage", 0x4C, 1, FieldKind::U8, FieldGroup::Identity,
               0, 255, true, "MapGm::GetBonusStage")
      << makeF("gang",   "Gang",        0x4D, 1, FieldKind::U8, FieldGroup::Identity,
               0, 9, true,  "MapGm::GetGang - 0 = none");

    // ---- progress ---------------------------------------------------------
    v << makeF("money",      "Money",      0x64, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "CONFIRMED: survives a save cycle, shows in wallet")
      << makeF("multiplier", "Multiplier", 0x68, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "GetMultiPlayer / SetMultiPlayer")
      << makeF("health",     "Health",     0x6C, 2, FieldKind::U16, FieldGroup::Progress,
               0, 0xFFFF, true, "Ped::GetHealth")
      << makeF("posX",       "Pos X",      0x54, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "Ped::GetXCoordinate")
      << makeF("posY",       "Pos Y",      0x58, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "Ped::GetYCoordinate")
      << makeF("posZ",       "Pos Z",      0x5C, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "Ped::GetPositionZ")
      << makeF("rotation",   "Rotation",   0x60, 2, FieldKind::U16, FieldGroup::Progress,
               0, 0xFFFF, true, "Ped::GetRotation")
      << makeF("lives",      "Lives",      0xD4, 1, FieldKind::U8, FieldGroup::Progress,
               0, 255, true, "SetMonyeLives; the community docs call this Point multiplier")
      << makeF("policeStar", "Wanted",     0xE0, 2, FieldKind::U16, FieldGroup::Progress,
               0, 6, true, "police star level, in-game max is 6")
      << makeF("tokens",     "Tokens",     0x744, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "MapGm::GetSpecialTokens");

    // ---- bonuses ----------------------------------------------------------
    // Player::sub_4A5A50 reads a2+26 (== 0x6E) as 17 single bytes, one per
    // powerup - NOT 17 words. Each byte is a timer: 0 = inactive, 0xFF lasts
    // roughly 45 minutes. Names from gta2/Game/PowerUp/PowerUp.h.
    for (int i = 0; i < PupSlotCount; ++i) {
        v << makeF(QString("powerup.%1").arg(i),
                   powerupSlotName(i), 0x6E + i, 1, FieldKind::U8,
                   FieldGroup::Bonuses, 0, 255, true,
                   i == PupInvulnerability || i == PupElectroFingers || i == PupInvisibility
                       ? "applies an effect on load: sub_4A5A50 cases 6/9/11"
                       : "timer in 1/256 units, 0xFF = about 45 minutes");
    }

    // ---- gangs ------------------------------------------------------------
    for (int i = 0; i < 10; ++i) {
        v << makeF(QString("gangRespect.%1").arg(i),
                   QString("Respect gang %1").arg(i), 0xC9 + i, 1, FieldKind::U8,
                   FieldGroup::Gangs, 0, 255, true,
                   "Gang::GetRespectForPlayer - 100 unlocks that gang");
    }

    // ---- arsenal ----------------------------------------------------------
    // sWeapon[0..14] are WeaponType 0..14 in enum order (see FieldDefs.h), and
    // sub_4A6B20 stores GetDisplayAmmo for each - so these 15 bytes are the
    // per-weapon ammo counters, one byte each. 0 = weapon not carried.
    for (int i = 0; i < WpnSlotCount; ++i) {
        v << makeF(QString("ammo.%1").arg(i),
                   weaponSlotName(i), 0xBA + i, 1, FieldKind::U8,
                   FieldGroup::Arsenal, 0, 255, true,
                   "ammo for this weapon; a non-zero value arms it");
    }
    v << makeF("remap",        "Weapon remap",  0xD3, 1, FieldKind::U8, FieldGroup::Arsenal,
               0, 255, true,
               "Ped::GetRemap - weapon model index; invalid values break the load")
      << makeF("selectWeapon", "Equipped weapon", 0xD6, 2, FieldKind::U16,
               FieldGroup::Arsenal, 0, 0xFFFF, true,
               "weapon slot index, 0xFFFF = none; sub_4A5B40 starts the player at -1");

    // ---- internals we copy verbatim but have not identified ---------------
    for (int i = 0; i < 10; ++i) {
        v << makeF(QString("field644.%1").arg(i),
                   QString("field644[%1]").arg(i), 0x90 + i * 4, 4, FieldKind::U32,
                   FieldGroup::Internals, 0, 0xFFFFFFFFu, true,
                   "copied verbatim by sub_4A6B20 / sub_4A6C80, purpose unknown");
    }
    for (int i = 0; i < 2; ++i) {
        v << makeF(QString("unkB8.%1").arg(i), QString("unkB8[%1]").arg(i),
                   0xB8 + i, 1, FieldKind::U8, FieldGroup::Internals, 0, 255, true,
                   "unknown");
    }
    v << makeF("unkD5",     "unkD5",     0xD5, 1, FieldKind::U8,  FieldGroup::Internals,
               0, 255, true, "unknown")
      << makeF("field678",  "field678",  0xD8, 4, FieldKind::U32, FieldGroup::Internals,
               0, 0xFFFFFFFFu, true, "copied verbatim, purpose unknown")
      << makeF("field67C",  "field67C",  0xDC, 4, FieldKind::U32, FieldGroup::Internals,
               0, 0xFFFFFFFFu, true, "copied verbatim, purpose unknown")
      << makeF("unk742",    "unk742",    0x742, 1, FieldKind::U8, FieldGroup::Internals,
               0, 255, true, "unknown")
      << makeF("unk743",    "unk743",    0x743, 1, FieldKind::U8, FieldGroup::Internals,
               0, 255, true, "unknown");

    // 0xE2..0x127: no known writer touches it, and a city-to-city diff of two
    // real saves showed 0 differing bytes here, so it is inert padding.
    for (int i = 0; i < 70; ++i) {
        v << makeF(QString("unkE2.%1").arg(i), QString("unkE2[%1]").arg(i),
                   0xE2 + i, 1, FieldKind::U8, FieldGroup::Internals, 0, 255, true,
                   "no known writer reads or writes this byte");
    }

    // ---- dangerous: map-derived or proven crashers -----------------------
    v << makeF("missionCount", "Mission count", 0x12A, 2, FieldKind::U16,
               FieldGroup::Dangerous, 0, 0xFFFF, false,
               "MAP-DERIVED: sub_47EE70 rebuilds it from the live script on every save")
      << makeF("mask32", "mask32", 0x12C, 4, FieldKind::U32,
               FieldGroup::Dangerous, 0, 0xFFFFFFFFu, false,
               "bits index arr2_15, a RAM array that is NOT saved - setting bits crashes the load")
      << makeF("mask25", "mask25", 0x130, 4, FieldKind::U32,
               FieldGroup::Dangerous, 0, 0x01FFFFFFu, false,
               "bits index arr_12 (25 ids), also RAM-only - setting bits crashes the load");

    return v;
}

} // namespace

// ---------------------------------------------------------------------------
// Named slot tables. Keys are the recovered enum names from
// gta2/Game/Weapon/Weapon.h and gta2/Game/PowerUp/PowerUp.h; the values are
// tr()'d so a translation file can localise them without touching the order.
// ---------------------------------------------------------------------------
namespace {

struct NamedSlot { const char *key; const char *text; };

const NamedSlot kWeapons[] = {
    { "weapon.pistol",      QT_TRANSLATE_NOOP("FieldDefs", "Pistol") },
    { "weapon.smg",         QT_TRANSLATE_NOOP("FieldDefs", "Uzi SMG") },
    { "weapon.rocket",      QT_TRANSLATE_NOOP("FieldDefs", "Rocket launcher") },
    { "weapon.electorgun",  QT_TRANSLATE_NOOP("FieldDefs", "Electro Gun") },
    { "weapon.molotov",     QT_TRANSLATE_NOOP("FieldDefs", "Molotov cocktail") },
    { "weapon.grenade",     QT_TRANSLATE_NOOP("FieldDefs", "Grenade") },
    { "weapon.shotgun",     QT_TRANSLATE_NOOP("FieldDefs", "Shotgun") },
    { "weapon.shocker",     QT_TRANSLATE_NOOP("FieldDefs", "Shocker") },
    { "weapon.flamegun",    QT_TRANSLATE_NOOP("FieldDefs", "Flamethrower") },
    { "weapon.smggrenade",  QT_TRANSLATE_NOOP("FieldDefs", "Grenade launcher") },
    { "weapon.dualpistol",  QT_TRANSLATE_NOOP("FieldDefs", "Dual pistols") },
    { "weapon.machinegun",  QT_TRANSLATE_NOOP("FieldDefs", "Machine gun") },
    { "weapon.unknown12",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown weapon 12") },
    { "weapon.unknown13",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown weapon 13") },
    { "weapon.unknown14",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown weapon 14") },
};

const NamedSlot kPowerups[] = {
    { "powerup.multiplier",  QT_TRANSLATE_NOOP("FieldDefs", "Point multiplier") },
    { "powerup.life",        QT_TRANSLATE_NOOP("FieldDefs", "Extra life") },
    { "powerup.health",      QT_TRANSLATE_NOOP("FieldDefs", "Health") },
    { "powerup.armor",       QT_TRANSLATE_NOOP("FieldDefs", "Armor") },
    { "powerup.jailcard",    QT_TRANSLATE_NOOP("FieldDefs", "Get out of jail card") },
    { "powerup.copbribe",    QT_TRANSLATE_NOOP("FieldDefs", "COP bribe") },
    { "powerup.invuln",      QT_TRANSLATE_NOOP("FieldDefs", "Invulnerability") },
    { "powerup.doubledmg",   QT_TRANSLATE_NOOP("FieldDefs", "Double damage") },
    { "powerup.fastreload",  QT_TRANSLATE_NOOP("FieldDefs", "Fast reload") },
    { "powerup.electro",     QT_TRANSLATE_NOOP("FieldDefs", "Electro fingers") },
    { "powerup.respect",     QT_TRANSLATE_NOOP("FieldDefs", "Respect") },
    { "powerup.invis",       QT_TRANSLATE_NOOP("FieldDefs", "Invisibility") },
    { "powerup.gang",        QT_TRANSLATE_NOOP("FieldDefs", "Instant gang") },
    { "powerup.unknown13",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown powerup 13") },
    { "powerup.unknown14",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown powerup 14") },
    { "powerup.unknown15",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown powerup 15") },
    { "powerup.unknown16",   QT_TRANSLATE_NOOP("FieldDefs", "Unknown powerup 16") },
};

// The names come from a table, so the lookup cannot be a tr() call at the
// call site - lupdate would not see it, and the runtime translation would be
// looked up under the wrong context. Naming the context explicitly is what
// makes these strings translatable at all.
QString lookup(const NamedSlot *tab, int n, int idx)
{
    if (idx < 0 || idx >= n)
        return QCoreApplication::translate("FieldDefs", "Unknown");
    return QCoreApplication::translate("FieldDefs", tab[idx].text);
}

} // namespace

QString weaponSlotName(int slot) { return lookup(kWeapons, WpnSlotCount, slot); }
QString powerupSlotName(int slot) { return lookup(kPowerups, PupSlotCount, slot); }

// Notes explain what the byte does, so the raw number is not the only clue.
static const char *const kPowerupNotes[PupSlotCount] = {
    QT_TRANSLATE_NOOP("FieldDefs", "point multiplier timer"),
    QT_TRANSLATE_NOOP("FieldDefs", "extra life timer"),
    QT_TRANSLATE_NOOP("FieldDefs", "health pickup timer"),
    QT_TRANSLATE_NOOP("FieldDefs", "armour pickup timer"),
    QT_TRANSLATE_NOOP("FieldDefs", "get outta jail free card"),
    QT_TRANSLATE_NOOP("FieldDefs", "cop bribe"),
    QT_TRANSLATE_NOOP("FieldDefs", "invulnerability"),
    QT_TRANSLATE_NOOP("FieldDefs", "double damage"),
    QT_TRANSLATE_NOOP("FieldDefs", "fast reload"),
    QT_TRANSLATE_NOOP("FieldDefs", "electro fingers"),
    QT_TRANSLATE_NOOP("FieldDefs", "respect / gang points"),
    QT_TRANSLATE_NOOP("FieldDefs", "invisibility"),
    QT_TRANSLATE_NOOP("FieldDefs", "instant gang access"),
    QT_TRANSLATE_NOOP("FieldDefs", "not identified"),
    QT_TRANSLATE_NOOP("FieldDefs", "not identified"),
    QT_TRANSLATE_NOOP("FieldDefs", "not identified"),
    QT_TRANSLATE_NOOP("FieldDefs", "not identified"),
};

QString powerupSlotNote(int slot)
{
    if (slot < 0 || slot >= PupSlotCount)
        return QCoreApplication::translate("FieldDefs", "no such slot");
    return QCoreApplication::translate("FieldDefs", kPowerupNotes[slot]);
}

int weaponSlotForType(int weaponType)
{
    return (weaponType >= 0 && weaponType < WpnSlotCount) ? weaponType : -1;
}

const QVector<FieldDef> &fieldDefs()
{
    static const QVector<FieldDef> defs = build();
    return defs;
}

QString fieldGroupTitle(FieldGroup g)
{
    switch (g) {
    case FieldGroup::Identity:  return QCoreApplication::translate("FieldDefs", "Identity / level");
    case FieldGroup::Progress:  return QCoreApplication::translate("FieldDefs", "Progress");
    case FieldGroup::Bonuses:   return QCoreApplication::translate("FieldDefs", "Bonuses");
    case FieldGroup::Gangs:     return QCoreApplication::translate("FieldDefs", "Gang respect");
    case FieldGroup::Arsenal:   return QCoreApplication::translate("FieldDefs", "Weapons");
    case FieldGroup::Internals: return QCoreApplication::translate("FieldDefs", "Unidentified (copied verbatim)");
    case FieldGroup::Dangerous: return QCoreApplication::translate("FieldDefs", "Map-derived / unsafe");
    }
    return QString();
}
