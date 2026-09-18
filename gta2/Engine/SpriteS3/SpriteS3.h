
#ifndef __SPRITES3_H_
#define __SPRITES3_H_
#include "../../Game/MissionData/MissionData.h"

class SpriteS3{
    public:
        MissionData ArrayMissionData[48];
        unsigned int  field_3C0;
        unsigned int Res;              // базовый указатель выделенной памяти
        void* AdressArray;         // адрес, куда NewMemory пишет результат
        SpriteS3();
    // 0x004BC8F0
    int SpriteS3Init(void);
    // 0x004C2EF0
    int SpriteS3Get(void);
};

extern SpriteS3* gSpriteS3;
#endif // !__SPRITES3_H_