#pragma once

#include <QString>
#include <QVector>

// ---------------------------------------------------------------------------
// The three playable cities and the map/style/script triple each one loads.
//
// The retail game does not hardcode this table: MapGm reads the names from the
// registry keys "mapname", "stylename" and "scriptname", which the 2D frontend
// writes when the player picks a level (Registry::sub_407930 scans data\*.mmp
// for the multiplayer maps). So the mapping below is the editor's own table,
// matching what the three single-player cities are called on disk.
//
// The editor therefore offers the city as a choice and fills the three name
// fields plus the mission table, rather than trying to infer a city from an
// arena byte.
// ---------------------------------------------------------------------------
struct CityDef {
    int         arena;         // value stored at block0 + 0x4B
    QString     key;           // "wil" / "ste" / "bil"
    QString     displayName;   // translated
    QString     mapFile;       // e.g. "data\\wil.gmp"
    QString     styleFile;     // e.g. "data\\wil.sty"
    QString     scriptFile;    // e.g. "data\\wil.scr"
};

namespace Cities {

// Number of playable cities; arena values run 0..kCityCount-1.
constexpr int kCityCount = 3;

// Display order matches the arena values 0,1,2.
const QVector<CityDef> &all();

// nullptr when the arena byte is out of range.
const CityDef *byArena(int arena);

// Match on any of the three name fields, e.g. "wil.gmp" or "data\\wil.scr".
// Case-insensitive, and tolerant of a missing "data\\" prefix.
const CityDef *byFileName(const QString &anyName);

// Last path component, e.g. "data\\wil.scr" -> "wil.scr".
QString baseName(const QString &path);

} // namespace Cities
