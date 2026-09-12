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
    static void SetCameraBounds(AudioSourceParams* p);
};
#pragma pack(pop)

int Update(AudioSourceParams* p);  // (gm) старый: ProjectPointToScreen -> Update

#endif // __AUDIO_SOURCE_PARAMS_H__