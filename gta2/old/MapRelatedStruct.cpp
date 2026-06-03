#include "MapRelatedStruct.h"

MapRelatedStruct::MapRelatedStruct() {
    // Calls sub_464A40 internally:
    // S16_01::S16_01(&this->S16_01);
    // Initialises all fields to 0/-1.
}

MapRelatedStruct::~MapRelatedStruct() {
    // Calls sub_464B30 internally:
    // Frees Buffer_ZONE, pCount, field_330, field_334,
    // Buffer_MOBJ, Buffer_LGHT, Buffer_ANIM, and Map
    // (including Map's internal field_40008/field_4000C buffers).
}
