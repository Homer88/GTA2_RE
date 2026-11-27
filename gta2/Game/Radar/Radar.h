
#ifndef __RADAR_H_
#define __RADAR_H_

#include <cstdint>

struct S202;

class Radar{
    public:
    // BN/IDA Radar layout (size 0xC): field_0, Time, DeltaTime.
    int field_0 = 0;
    int Time = 0;
    int DeltaTime = 0;

    // IDA 0x401B60 Radar::WorldCoordinateToScreenCoord: (field_0 * (__int64)a3->BaseCar[0].field) >> 14
    // Debug-only formula helper. NOT a full RE Radar object/layout port.
    static int WorldCoordinateToScreenCoord_Formula(int radarField0, int a3BaseCar0Field);
    // IDA 0x401B60 shape helper: writes computed value into S202-like out. Guarded/debug-only; no verified RE Radar object layout.
    static void WorldCoordinateToScreenCoord_ToS202(struct S202* out, int radarField0, int a3BaseCar0Field);
    // IDA 0x401B60 thiscall shape: result=(this->field_0 * (__int64)*(int*)a3) >> 14; S202::SetToNewVal(out,result); return out.
    // Guarded RE port: reads *(int*)a3 under SEH; no full caller/object-context proof.
    S202* WorldCoordinateToScreenCoord(S202* out, void* a3);

    // 0x004C3680
    int UpdateDeltaTime(void);
};

#endif // !__RADAR_H_