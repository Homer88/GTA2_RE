
#ifndef __TRANSMISSIONINFO_H_
#define __TRANSMISSIONINFO_H_


class TransmissionInfo{
    public:

    // 0x004B91E0
    int Reset(void);
    // 0x004B91F0
    int AddScore(void);
    // 0x004B9260
    int UpdateBrakes(void);
    // 0x004B94B0 void __thiscall
    void ValidateSpawnPoints(void);  // (gm) старый: UpdateTransmission -> ValidateSpawnPoints
};

#endif // !__TRANSMISSIONINFO_H_