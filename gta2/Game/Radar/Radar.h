
#ifndef __RADAR_H_
#define __RADAR_H_


class Radar{
    public:
    // IDA 0x401B60 Radar::WorldCoordinateToScreenCoord: (field_0 * (__int64)a3->BaseCar[0].field) >> 14
    // Debug-only formula helper. NOT a full RE Radar object/layout port.
    static int WorldCoordinateToScreenCoord_Formula(int radarField0, int a3BaseCar0Field);

    // 0x004C3680
    int UpdateDeltaTime(void);
};

#endif // !__RADAR_H_