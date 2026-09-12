
#ifndef __RANDOM_H_
#define __RANDOM_H_


class Random{
    public:

    // 0x00472C00 byte __thiscall
    unsigned char GetZoneIndex(int arg0);  // (gm) старый: GetRandomIndex -> GetZoneIndex
    // 0x00472E90
    int PauseGame(void);
};

#endif // !__RANDOM_H_