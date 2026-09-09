#ifndef __FONT_H_
#define __FONT_H_

class Font{

    public:

    // 0x004539B0
    int GetCharHeight(void);
    // 0x004539D0 byte __thiscall
    unsigned char GetRemapColour(int param_1,int param_2);
    // 0x004539F0
    int DrawGTATextRawMain(void);
    // 0x004CB0C0
    int GetStringWidth(void);
    // 0x004CC0C0
    int GetNumberLines(void);
    // 0x004CC100
    int DrawGTATextRaw(void);
};

#endif // !__FONT_H_
