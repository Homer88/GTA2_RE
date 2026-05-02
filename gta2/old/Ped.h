#ifndef __PED__H__
#define __PED__H__



#include "Car.h"
#include "Player.h"

class Car;
class Player;


class Ped{
    private:

    public:
       // S200 S200_50[50];
        int Counter;
        Ped *sPed1;
        Ped *Driver;
        Ped *sPed;
        Car *pCar;
        Car *ObjectiveTargetCar;
        Car *TargetCarForEnter;
        Player *Player;
        //Ped *NextPed;
        //Ped *sPed2;
        //GameObject *GameObject;
        //Car *CurrentCar;
        //Weapon *SelectedWeapon;
        //Weapon *Weapon_;
        //Weapon *Weapon;
        int field_17C;
        Ped *DriverPed;
        int field_184;
        int field_188;
        int field_18C;
        int field_190;
        int field_194;
        Ped *sPed3;
        int field_19C;
        int field_1A0;
        int field_1A4;
        int field_1A8;
        int PositionX;
        int PositionY;
        int PositionZ;
        int PositionX1;
        int PositionY1;
        int field_1C0;
        int field_1C4;
        int field_1C8;
        int field_1CC;
        int field_1D0;
        int field_1D4;
        int field_1D8;
        int PositionX2;
        Ped *DriverPed1;
        int PositionZ1;
        int field_1E8;
        int field_1EC;
        int field_1F0;
        int field_1F4;
        int field_1F8;
        int field_1FC;
        int ID;
        int field_204;
        __int16 field_208;
        __int16 PoliceStar;
      //  _BYTE gap20C[2];
        __int16 field_20E;
        __int16 field_210;
        __int16 field_212;
        __int16 field_214;
        __int16 Health;
        __int16 field_218;
        __int16 field_21A;
        int field_21C;
        int field_220;
        char field_224;
        char field_225;
        char field_226;
        char field_227;
        char field_228;
        char field_229;
        char field_22A;
        char field_22B;
        int field_22C;
        int field_230;
        char field_234;
        char field_235;
        char field_236;
        char field_237;
        //SearchType SearchType;
        char field_23C;
        char field_23D;
        char field_23E;
        char field_23F;
        //OCUPATION Occupation;
        //Remap Remap;
        char field_245;
        char field_246;
        char field_247;
        int TargetCarDoor;
        char Index;
        char field_24D;
        char field_24E;
        char field_24F;
        int field_250;
        char field_254;
        char field_255;
        char field_256;
        char field_257;
        int State;
        int field_25C;
        char field_260;
        char field_261;
        char field_262;
        char field_263;
        char field_264;
        char field_265;
        char field_266;
        char field_267;
        char field_268;
        char field_269;
        char field_26A;
        char field_26B;
        ///GraphicType GraphicType;
        int field_270;
        int GangCarModel;
        //PedState PedState;
        int field_27C;
        int field_280;
        int field_284;
        int field_288;
        int field_28C;
        int field_290; 
        Ped();
        ~Ped();
};

#endif // !__PED__H__