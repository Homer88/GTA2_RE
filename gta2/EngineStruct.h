#pragma once

#include "Global.h"

class EngineStruct{
    public:
        EngineStruct *ElementNext;
        int field_4;
        char field_8;
        char field_9;
        char field_A;
        char field_B;
        EngineStruct *FirstElement;
        CarSystemManager *CarSystemManager;
        void *field_14;
        void *field_18;
        int field_1C;
        int field_20;
        int field_24;
        char field_28;
        char field_29;
        char field_2A;
        char field_2B;
        char field_2C;
        char field_2D;
        char field_2E;
        char field_2F;
        char field_30;
        char field_31;
        char field_32;
        char field_33;
        int field_34;
        int field_38;
        int field_3C;
        int field_40;
        int field_44;
        int field_48;
        int field_4C;
        int field_50;
        short field_54;
        short field_56;
        short field_58;
        short field_5A;
        int field_5C;
        int field_60;
        int field_64;
        int field_68;
        EngineStruct *NextElement;
        int field_70;
        int field_74;
        EngineStruct();
        ~EngineStruct();


};

#endif