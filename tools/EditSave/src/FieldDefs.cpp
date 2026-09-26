#include "FieldDefs.h"

#include <QObject>

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
      << makeF("city",   "City",        0x4B, 1, FieldKind::U8, FieldGroup::Identity,
               0, 2, true,  "0..2 - which city the player is in")
      << makeF("level",  "Level",       0x4C, 1, FieldKind::U8, FieldGroup::Identity,
               0, 255, true,"packed city<<4 | sublevel; 0xFF = no level")
      << makeF("gang",   "Gang",        0x4D, 1, FieldKind::U8, FieldGroup::Identity,
               0, 9, true,  "0..9 - current gang (0 = none)");

    // ---- progress ---------------------------------------------------------
    v << makeF("money",      "Money",      0x64, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "CONFIRMED: survives a save cycle, shows in wallet")
      << makeF("multiplier", "Multiplier", 0x68, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "GetMultiPlayer / SetMultiPlayer")
      << makeF("health",     "Health",     0x6C, 2, FieldKind::U16, FieldGroup::Progress,
               0, 0xFFFF, true, "Ped::GetHealth")
      << makeF("lives",      "Lives",      0xD4, 1, FieldKind::U8, FieldGroup::Progress,
               0, 255, true, "SetMonyeLives")
      << makeF("policeStar", "Wanted",     0xE0, 2, FieldKind::U16, FieldGroup::Progress,
               0, 6, true, "police star level, in-game max is 6")
      << makeF("tokens",     "Tokens",     0x744, 4, FieldKind::U32, FieldGroup::Progress,
               0, 0xFFFFFFFFu, true, "MapGm::GetSpecialTokens");

    // ---- bonuses ----------------------------------------------------------
    for (int i = 0; i < 17; ++i) {
        v << makeF(QString("powerup.%1").arg(i),
                   QString("Bonus %1").arg(i), 0x6E + i * 2, 2, FieldKind::U16,
                   FieldGroup::Bonuses, 0, 0xFFFF, true,
                   "loaded by sub_4A5A50; 6/9 = special fx, 11 = invisibility");
    }

    // ---- gangs ------------------------------------------------------------
    for (int i = 0; i < 10; ++i) {
        v << makeF(QString("gangRespect.%1").arg(i),
                   QString("Respect gang %1").arg(i), 0xC9 + i, 1, FieldKind::U8,
                   FieldGroup::Gangs, 0, 255, true,
                   "Gang::GetRespectForPlayer - 100 unlocks that gang");
    }

    // ---- arsenal ----------------------------------------------------------
    for (int i = 0; i < 15; ++i) {
        v << makeF(QString("ammo.%1").arg(i),
                   QString("Ammo %1").arg(i), 0xBA + i, 1, FieldKind::U8,
                   FieldGroup::Arsenal, 0, 255, true, "ammo for weapon slot i");
    }
    v << makeF("remap",        "Weapon remap",  0xD3, 1, FieldKind::U8, FieldGroup::Arsenal,
               0, 255, true, "index into the remap table - invalid values break the load")
      << makeF("selectWeapon", "Selected weap", 0xD6, 2, FieldKind::U16, FieldGroup::Arsenal,
               0, 0xFFFF, true, "0xFFFF = none, otherwise an arsenal index");

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

const QVector<FieldDef> &fieldDefs()
{
    static const QVector<FieldDef> defs = build();
    return defs;
}

QString fieldGroupTitle(FieldGroup g)
{
    switch (g) {
    case FieldGroup::Identity:  return QObject::tr("Identity / level");
    case FieldGroup::Progress:  return QObject::tr("Progress");
    case FieldGroup::Bonuses:   return QObject::tr("Bonuses");
    case FieldGroup::Gangs:     return QObject::tr("Gang respect");
    case FieldGroup::Arsenal:   return QObject::tr("Weapons");
    case FieldGroup::Internals: return QObject::tr("Unidentified (copied verbatim)");
    case FieldGroup::Dangerous: return QObject::tr("Map-derived / unsafe");
    }
    return QString();
}
