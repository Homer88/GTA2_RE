#ifndef __AUDIO_SOURCE_PARAMS_H__
#define __AUDIO_SOURCE_PARAMS_H__

#pragma pack(push, 1)
struct AudioSourceParams {
    int field;         // 0x00
    int y;             // 0x04
    int z;             // 0x08
    int type;          // 0x0C - direction/behavior type
    int field_10;      // 0x10 - flags

    static int  sub_41F9D0(AudioSourceParams* p);
    static void sub_4BA5E0(AudioSourceParams* p);
};
#pragma pack(pop)

int sub_463760(AudioSourceParams* p);

#endif // __AUDIO_SOURCE_PARAMS_H__
