
#ifndef __MAUDIO_H_
#define __MAUDIO_H_


class MAudio{
    public:

    // 0x00410580
    int DMAudioAddPositionalSound(void);
    // 0x00410590
    int RemovePositionalSound(void);
    // 0x00410730
    int PopAudioObject(void);
    // 0x004B2180
    int CalculateDistanceVolume(void);
};

#endif // !__MAUDIO_H_