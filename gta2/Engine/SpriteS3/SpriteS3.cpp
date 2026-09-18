#include "SpriteS3.h"
#include <cstddef>
#include "../Memory/Memory.h"
SpriteS3* gSpriteS3;

    // 0x004BC8F0
SpriteS3::SpriteS3() {

    this->field_3C0 = 0;
    this->Res = 0;
    this->AdressArray = NULL;

    this->Res = NewMemory(0x40000, &this->AdressArray);

    unsigned int  addr = this->Res;

    for (int g = 0; g < 8; ++g) {
        int base = g * 4;
        this->ArrayMissionData[base + 0].field_0 = addr;
        this->ArrayMissionData[base + 1].field_0 = addr + 0x40;
        this->ArrayMissionData[base + 2].field_0 = addr + 0x80;
        this->ArrayMissionData[base + 3].field_0 = addr + 0xC0;
        addr += 0x4000;
    }

    for (int g = 0; g < 4; ++g) {
        int base = 32 + g * 4;
        this->ArrayMissionData[base + 0].field_0 = addr;
        this->ArrayMissionData[base + 1].field_0 = addr + 0x40;
        this->ArrayMissionData[base + 2].field_0 = addr + 0x80;
        this->ArrayMissionData[base + 3].field_0 = addr + 0xC0;
        addr += 0x8000;
    }

    for (int i = 0; i < 48; ++i) {
        this->ArrayMissionData[i].field_10 = (unsigned short )i;
    }


}

int SpriteS3::SpriteS3Init(void){
        return 0;
    }


    // 0x004C2EF0


int SpriteS3::SpriteS3Get(void){
        return 0;
    }
