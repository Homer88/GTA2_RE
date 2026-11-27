#include "Radar.h"
#include <cstdint>

int Radar::WorldCoordinateToScreenCoord_Formula(int radarField0, int a3BaseCar0Field) {
    // IDA 0x401B60: S202::SetToNewVal(a2, (this->field_0 * (__int64)a3->BaseCar[0].field) >> 14)
    // Guarded/debug formula helper only; no verified RE Radar object layout.
    return (int)(((std::int64_t)radarField0 * (std::int64_t)a3BaseCar0Field) >> 14);
}

    // 0x004C3680


int Radar::UpdateDeltaTime(void){
        return 0;
    }
