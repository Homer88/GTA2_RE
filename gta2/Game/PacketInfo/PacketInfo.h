#ifndef __PACKETINFO_H_
#define __PACKETINFO_H_

class PacketInfo{

    public:

    // 0x004C2780
    int LoadTextures(void);
    // 0x004C27F0
    int LoadPalettedTextures(void);
    // 0x004C2F30
    int Setup(void);
};

#endif // !__PACKETINFO_H_
