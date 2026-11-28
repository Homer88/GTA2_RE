#include "Radar.h"
#include "../../Engine/MapRelatedStruct/MapRelatedStruct.h"
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

int Radar::WorldCoordinateToScreenCoord_Formula(int radarField0, int a3BaseCar0Field) {
    // IDA 0x401B60: S202::SetToNewVal(a2, (this->field_0 * (__int64)a3->BaseCar[0].field) >> 14)
    // Guarded/debug formula helper only; no verified RE Radar object layout.
    return (int)(((std::int64_t)radarField0 * (std::int64_t)a3BaseCar0Field) >> 14);
}

void Radar::WorldCoordinateToScreenCoord_ToS202(struct S202* out, int radarField0, int a3BaseCar0Field) {
    // IDA 0x401B60 shape: S202::SetToNewVal(a2, result). Not full Radar object/layout port.
    if (!out) return;
    int v = WorldCoordinateToScreenCoord_Formula(radarField0, a3BaseCar0Field);
    out->SetToNewVal((void*)(uintptr_t)(std::uint32_t)v);
}

S202* Radar::WorldCoordinateToScreenCoord(S202* out, void* a3) {
    // IDA 0x401B60: thiscall(ecx=this, out, a3), retn 8.
    // result = (this->field_0 * (__int64)a3->BaseCar[0].field) >> 14; S202::SetToNewVal(out, result); return out.
    // Guarded RE port: only reads a3[0] as int; caller must ensure a3 layout matches IDA expectation.
    if (!out) return out;
    int a3Field = 0;
    bool ok = false;
#ifdef _WIN32
    __try {
        if (a3) { a3Field = *(int*)a3; ok = true; }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        ok = false;
    }
#else
    if (a3) { a3Field = *(int*)a3; ok = true; }
#endif
    if (!ok) {
        out->SetToNewVal((void*)0);
        return out;
    }
    int v = WorldCoordinateToScreenCoord_Formula(this->field_0, a3Field);
    out->SetToNewVal((void*)(uintptr_t)(std::uint32_t)v);
    return out;
}

    // 0x004C3680


// 0x004C3680 IDA/BN Radar::UpdateDeltaTime: DeltaTime += timeGetTime() - Time. RE field-name impl.
int Radar::UpdateDeltaTime(void){
        this->DeltaTime += (int)timeGetTime() - this->Time;
        return 0;
    }
