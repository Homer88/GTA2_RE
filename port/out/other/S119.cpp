#include "gta2_shim.h"

// Module: other, Class: S119
// Functions: 7
// Source: unified (IDA+Ghidra)

// 0x00476ac0: S119::sub_476AC0
// IDA: S119::sub_476AC0
// Ghidra: FUN_00476ac0
bool gta2::S119_sub_476AC0(int param_1)
{
  return *(int *)(param_1 + 0xc) == 3;
}


// 0x00476ad0: S119::sub_476AD0
// IDA: S119::sub_476AD0
// Ghidra: ---
void gta2::S119_sub_476AD0(struct S119 *self)
{
  self->field_3F = 1;
}


// 0x00489650: S119::sub_489650
// IDA: S119::sub_489650
// Ghidra: FUN_00489650
void gta2::S119_sub_489650(void *self)
{
  *(undefined4 *)((int)self + 0x10) = 0;
  *(undefined4 *)((int)self + 0xc) = 0;
  gta2::S103_sub_41E1E0((LinkedList *)((int)self + 0x28));
  gta2::S103_sub_41E1E0((LinkedList *)((int)self + 0x18));
  gta2::S103_sub_41E1E0((LinkedList *)((int)self + 0x20));
  gta2::S103_sub_41E1E0((LinkedList *)((int)self + 0x30));
  return;
}


// 0x00489680: S119::sub_489680
// IDA: S119::sub_489680
// Ghidra: ---
char gta2::S119_sub_489680(struct S119 *self)
{
  struct Car *Car; // eax
  struct Car *pCar_2; // ecx
  struct Car *v4; // edi
  struct Player *v5; // eax
  struct Car *v6; // ebx
  struct Ped *v7; // edi
  int *v8; // eax
  __int16 *v9; // eax
  struct Ped *v10; // edi
  struct Player *XCoordinate; // eax
  struct Player *v12; // eax
  int v13; // eax
  struct Player *v14; // eax
  struct Player *v15; // eax
  int v16; // eax
  int *v17; // eax
  __int16 *v18; // eax
  struct Car *v19; // eax
  int ID; // eax
  struct Car *pCar_1; // ecx
  struct Ped *v22; // edi
  struct Car *v23; // eax
  char v24; // cl
  struct Car *v25; // ecx
  int Driver; // ecx
  struct Car *v27; // edi
  struct Player *Player; // eax
  struct Car *pCar; // ebp
  void *v30; // eax
  void *v31; // eax
  _DWORD *v32; // eax
  struct GameEntity *v33; // eax
  struct S103 **v34; // eax
  struct Tango *v35; // eax
  struct S103 **v36; // eax
  void *v38; // [esp-Ch] [ebp-74h]
  struct Car *v39; // [esp-4h] [ebp-6Ch]
  __int16 v40; // [esp+Ch] [ebp-5Ch] BYREF
  __int16 v41; // [esp+Eh] [ebp-5Ah] BYREF
  int v42; // [esp+10h] [ebp-58h] BYREF
  int v43; // [esp+18h] [ebp-50h] BYREF
  int a2; // [esp+1Ch] [ebp-4Ch] BYREF
  int X; // [esp+20h] [ebp-48h] BYREF
  int v46; // [esp+24h] [ebp-44h] BYREF
  int Y; // [esp+28h] [ebp-40h] BYREF
  int v48; // [esp+2Ch] [ebp-3Ch] BYREF
  int v49; // [esp+30h] [ebp-38h] BYREF
  int v50; // [esp+34h] [ebp-34h] BYREF
  Weapon v51; // [esp+38h] [ebp-30h] BYREF

  if ( self->field_C == 1 )
  {
    Car = self->Car;
    if ( !self->Car->CarSprite )
      goto LABEL_21;
    Driver = (int)Car->Driver;
    if ( Driver && Driver != self->field_14 )
      self->field_14 = Driver;
    LOBYTE(Car) = gta2::sub_4BB4D0(
                    &Car->CarSprite->FirstElement,
                    &self->S103_1,
                    (struct SpriteS1 *)&self->S103_2,
                    (unsigned __int8 *)&v42,
                    (unsigned __int8 *)&v40);
    if ( (_BYTE)Car == 2 )
    {
      LOBYTE(Car) = v42;
      if ( (_BYTE)v42 )
      {
        if ( (_BYTE)v42 != 2 || (_BYTE)v40 != 3 )
          return (char)Car;
      }
      else if ( (_BYTE)v40 != 1 )
      {
        return (char)Car;
      }
    }
    else
    {
      if ( (unsigned __int8)Car <= 2u )
        return (char)Car;
      if ( (unsigned __int8)Car >= 4u )
      {
LABEL_49:
        self->field_C = 2;
        return (char)Car;
      }
    }
    gta2::Car_sub_44A3E0(self->Car);
    gta2::Car_sub_4218A0(self->Car);
    v27 = self->Car;
    if ( gta2::Car_IsDriverPlayer(self->Car) )
    {
      Player = gta2::Car_GetPlayer(v27);
      gta2::Player_sub_4A69A0(Player);
    }
    gta2::Car_SetLocksDoor(self->Car);
    gta2::sub_4895D0(self->Car->Player_);
    pCar = self->Car;
    gta2::Car_GetY(self->Car, &v48);
    v38 = v30;
    gta2::Car_GetX(pCar, &v49);
    gta2::Weapon_sub_432860((struct Weapon *)&v50, v31, v38);
    v32 = gta2::S103_sub_40F5C0(
            (struct S103 *)(&pCar->CarSprite->S3_arr5031[0].SpriteS3->S39_Arr48[0].field_C + 2 * (unsigned __int8)v42),
            &v51.Car,
            &pCar->CarSprite->S3_arr5031[0].SpriteS3->S39_Arr48[0].field_C + 2 * (unsigned __int8)v40);
    v33 = (struct GameEntity *)sub_4202E0(v32, &v51.field_C, &unk_669C5C);
    v34 = (S103 **)gta2::S1_sub_40F600(v33, &v51.SMG, (int)&v50);
    self->S103_ = *v34;
    self->Player_ = (int)v34[1];
    if ( gta2::Player_IsCurrentPlayer((struct Player *)&self->S103_, (struct Player *)&unk_669BE0)
      && gta2::Player_IsCurrentPlayer((struct Player *)&self->Player_, (struct Player *)&unk_669BE0) )
    {
      self->field_3D = 1;
      self->field_C = 2;
      LOBYTE(Car) = (unsigned __int8)gta2::Player_sub_4A0930(pCar->Player_, (struct Tango *)&self->S103_);
      self->field_C = 2;
      return (char)Car;
    }
    v35 = (struct Tango *)sub_420390(&self->S103_, &v51.Ped);
    v36 = (S103 **)gta2::Tango_sub_41E1A0(v35, &v51.TypeWeapon, &unk_669C9C);
    self->S103_ = *v36;
    self->Player_ = (int)v36[1];
    LOBYTE(Car) = (unsigned __int8)gta2::Player_sub_4A0930(pCar->Player_, (struct Tango *)&self->S103_);
    goto LABEL_49;
  }
  if ( self->field_C != 2 )
  {
    Car = (struct Car *)(self->field_C - 3);
    if ( self->field_C == 3 )
    {
      pCar_2 = self->Car;
      if ( self->Car->CarSprite )
      {
        gta2::Car_sub_476230(pCar_2);
        gta2::Car_sub_4895E0(self->Car);
        gta2::sub_476A30((void *)self->field_10);
        gta2::sub_4895F0((void *)self->field_10);
        gta2::Car_SetLocksDoor_4(self->Car);
        gta2::Car_sub_426F60(self->Car, v39);
        gta2::sub_446120(&self->Car->Passenger_);
        v4 = self->Car;
        if ( gta2::Car_IsDriverPlayer(self->Car) )
        {
          v5 = gta2::Car_GetPlayer(v4);
          gta2::sub_4A4E50(v5);
        }
        if ( !self->field_3F )
        {
          v6 = self->Car;
          v7 = gta2::Car_GetDriver(self->Car);
          if ( v7 )
          {
            gta2::Car_GetZ(v6, &v43);
            gta2::Ped_sub_43AD50(v7, (struct Ped *)self->S103_3, *(_DWORD *)&self->field_34, *v8);
            gta2::Car_sub_4235D0(self->Car);
            v9 = sub_489560(&v40, self->field_38);
            gta2::Ped_SetRotation(v7, *v9);
            self->Car->Driver = 0;
            LOBYTE(v7->GameObject2->field_5C) = 20;
          }
          else
          {
            v10 = (struct Ped *)self->field_14;
            if ( v10 )
            {
              XCoordinate = (struct Player *)gta2::Ped_GetXCoordinate(v10, (int)&a2);
              if ( gta2::Player_sub_40CE70(XCoordinate, &self->S103_1) )
              {
                v12 = (struct Player *)gta2::Ped_GetXCoordinate(v10, (int)&X);
                LOBYTE(v13) = gta2::Player_CheckCondition(v12, (int *)&self->S103_2);
                if ( v13 )
                {
                  gta2::Ped_GetYCoordinate(v10, &v46);
                  if ( gta2::Player_sub_40CE70(v14, &self->field_1C) )
                  {
                    gta2::Ped_GetYCoordinate(v10, &Y);
                    LOBYTE(v16) = gta2::Player_CheckCondition(v15, &self->field_24);
                    if ( v16 )
                    {
                      gta2::Car_GetZ(v6, &v48);
                      gta2::Ped_sub_43AD50(v10, (struct Ped *)self->S103_3, *(_DWORD *)&self->field_34, *v17);
                      v18 = sub_489560(&v41, self->field_38);
                      gta2::Ped_SetRotation((struct Ped *)self->field_14, *v18);
                    }
                  }
                }
              }
            }
          }
        }
        gta2::Car_isMask3(self->Car);
      }
      v19 = self->Car;
      self->pCar = self->Car;
      ID = v19->ID;
      self->Car = 0;
      self->ID = ID;
      LOBYTE(Car) = gta2::S119_sub_489650(self);
    }
    return (char)Car;
  }
  pCar_1 = self->Car;
  if ( !self->Car->Player_ )
    gta2::Car_CarMakeDriveable4(pCar_1);
  Car = (struct Car *)((char *)&self->Car1->Car + 1);
  self->Car1 = Car;
  if ( (unsigned int)Car >= 0x12C )
  {
LABEL_21:
    self->field_C = 3;
    return (char)Car;
  }
  v22 = self->Car->Driver;
  if ( v22 && !gta2::Car_IsDriverPlayer(self->Car) )
    gta2::Ped_PedSetObjective(v22, 27, 9999);
  if ( gta2::sub_4BB4D0(
         &self->Car->CarSprite->FirstElement,
         &self->S103_1,
         (struct SpriteS1 *)&self->S103_2,
         (unsigned __int8 *)&v42,
         (unsigned __int8 *)&v40) == 4
    || self->field_3D )
  {
    v23 = self->Car;
    v24 = self->field_3C - 1;
    self->field_3D = 1;
    self->field_3C = v24;
    gta2::sub_4895D0(v23->Player_);
    LOBYTE(Car) = self->field_3C;
    if ( !(_BYTE)Car )
    {
      v25 = self->Car;
      self->field_C = 3;
      LOBYTE(Car) = gta2::sub_4895D0(v25->Player_);
    }
  }
  else
  {
    gta2::sub_4895D0(self->Car->Player_);
    LOBYTE(Car) = (unsigned __int8)gta2::Player_sub_4A0930(self->Car->Player_, (struct Tango *)&self->S103_);
  }
  return (char)Car;
}


// 0x00489ac0: S119::S119
// IDA: S119::S119
// Ghidra: ---
S119 * gta2::S119_S119(struct S119 *self)
{
  self->Car = 0;
  self->field_10 = 0;
  self->field_14 = 0;
  self->field_C = 0;
  gta2::S103_sub_41E1E0((struct S103 *)&self->S103_);
  gta2::S103_sub_41E1E0((struct S103 *)&self->S103_1);
  gta2::S103_sub_41E1E0((struct S103 *)&self->S103_2);
  self->field_38 = 0;
  gta2::S103_sub_41E1E0((struct S103 *)&self->S103_3);
  self->field_3C = 30;
  self->field_3D = 0;
  self->field_3E = 0;
  self->field_3F = 0;
  self->field_40 = 0;
  self->pCar = 0;
  self->ID = 0;
  return self;
}


// 0x00489bc0: S119::sub_489BC0
// IDA: S119::sub_489BC0
// Ghidra: ---
char gta2::S119_sub_489BC0(struct S119 *self, _DWORD ***a2, void *a3)
{
  char v4; // al
  struct Tango *Tango; // eax
  int v6; // edi
  struct SpriteS1 *v7; // eax
  unsigned __int8 v8; // di
  struct Player *v9; // eax
  struct SpriteS1 *v10; // eax
  struct S202 *v11; // ecx
  struct Player *v12; // eax
  unsigned __int8 v13; // bl
  void *v14; // eax
  struct S202 *v15; // eax
  struct SpriteS1 *v16; // eax
  struct S202 *v17; // eax
  struct SpriteS1 *v18; // eax
  struct SpriteS1 *v19; // eax
  struct S202 *v20; // eax
  struct Player *v21; // eax
  struct SpriteS1 *v22; // eax
  unsigned __int8 v23; // di
  struct Player *v24; // eax
  struct SpriteS1 *v25; // eax
  unsigned __int8 v26; // bl
  struct Player *v27; // eax
  struct SpriteS1 *v28; // eax
  struct S202 *v29; // eax
  struct SpriteS1 *v30; // eax
  struct S202 *v31; // ecx
  struct S202 *v32; // eax
  struct SpriteS1 *v33; // eax
  struct S202 *v34; // eax
  struct SpriteS1 *v35; // eax
  struct S202 *v36; // eax
  struct S202 *v37; // eax
  struct SpriteS1 *v38; // eax
  struct SpriteS1 *v39; // eax
  unsigned __int8 v40; // di
  unsigned __int8 v41; // bl
  void *v42; // eax
  struct Player *v43; // eax
  struct SpriteS1 *v44; // eax
  struct S202 *v45; // eax
  struct SpriteS1 *v46; // eax
  struct SpriteS1 *v47; // edx
  struct S202 *v48; // ecx
  struct S202 *v49; // eax
  struct SpriteS1 *v50; // eax
  struct S202 *v51; // eax
  struct SpriteS1 *v52; // eax
  struct SpriteS1 *v53; // eax
  struct Player *v54; // eax
  struct S202 *v55; // ecx
  bool v56; // al
  unsigned __int8 v57; // di
  struct Player *v58; // eax
  struct S202 *v59; // ecx
  struct Player *v60; // eax
  struct Player *v61; // eax
  struct SpriteS1 *v62; // eax
  struct S202 *v63; // eax
  struct S202 *v64; // eax
  struct SpriteS1 *v65; // eax
  struct SpriteS1 *v66; // eax
  struct S202 *v67; // eax
  struct SpriteS1 *v68; // eax
  struct S202 *v69; // eax
  struct SpriteS1 *v71; // [esp-14h] [ebp-158h]
  struct Tango **p_Tango; // [esp-10h] [ebp-154h]
  struct SpriteS1 *v73; // [esp-Ch] [ebp-150h]
  struct SpriteS1 *v74; // [esp-Ch] [ebp-150h]
  struct SpriteS1 *v75; // [esp-Ch] [ebp-150h]
  struct S202 *v76; // [esp-Ch] [ebp-150h]
  void *v77; // [esp-8h] [ebp-14Ch]
  int v78; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v79; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v80; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v81; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v82; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v83; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v84; // [esp-4h] [ebp-148h]
  void *v85; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v86; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v87; // [esp-4h] [ebp-148h]
  struct SpriteS1 *v88; // [esp-4h] [ebp-148h]
  S900 v89; // [esp+10h] [ebp-134h] BYREF
  S202 v90; // [esp+114h] [ebp-30h] BYREF
  int v91; // [esp+134h] [ebp-10h] BYREF
  char v92; // [esp+138h] [ebp-Ch] BYREF
  char v93; // [esp+13Ch] [ebp-8h] BYREF
  char v94; // [esp+140h] [ebp-4h] BYREF

  v4 = self->field_3E;
  self->Car = (struct Car *)a2;
  self->Car1 = 0;
  self->field_10 = (int)a3;
  self->field_C = 1;
  self->field_14 = 0;
  self->field_3C = 30;
  self->field_3D = 0;
  if ( v4 == -1 )
    self->field_3E = 1;
  else
    self->field_3E = v4 + 1;
  self->field_40 = gta2::Car_sub_447ED0(a2);
  gta2::sub_44C730(a3, &v89.gap3[12], &v89.gap3[8], &v89.gap3[16], &self->field_38);
  Tango = *(Tango **)&unk_669C5C.Index;
  if ( !self->field_40 )
    Tango = stru_669B70.Tango;
  v6 = self->field_38;
  *(_DWORD *)&v89.Index = Tango;
  *(_DWORD *)&v89.gap3[1] = Tango;
  switch ( v6 )
  {
    case 1:
      if ( gta2::sub_489600((_DWORD *)self->field_10) )
      {
        v7 = gta2::S202_sub_401B20((struct S202 *)&stru_669B70.Tango, (struct SpriteS1 *)&v89.gap3[153], (struct PublicTransport *)&v89);
        v8 = v89.gap3[8];
        v78 = (int)v7;
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[233], v89.gap3[8]);
        v10 = gta2::Player_sub_401B40(v9, (struct S202 *)&v89.gap3[25], v78);
        v11 = (struct S202 *)&v89.gap3[33];
      }
      else
      {
        v8 = v89.gap3[8];
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[41], v89.gap3[8]);
        v10 = gta2::Player_sub_401B40(v12, (struct S202 *)&v89.gap3[169], (int)&v89);
        v11 = (struct S202 *)&v93;
      }
      v13 = v89.gap3[12];
      v79 = v10;
      gta2::S202_sub_40CE30(v11, v89.gap3[12]);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_1, v14, v79);
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[57], v8);
      v16 = gta2::S202_sub_401B20(v15, (struct SpriteS1 *)&v89.gap3[177], (struct PublicTransport *)&stru_669B70.Tango);
      v80 = gta2::S202_sub_401B20((struct S202 *)v16, (struct SpriteS1 *)&v89.gap3[49], (struct PublicTransport *)&v89);
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[65], v13);
      v18 = gta2::S202_sub_401B20(v17, (struct SpriteS1 *)&v89.gap3[241], (struct PublicTransport *)&stru_669B70.Tango);
      v19 = gta2::S202_sub_401B20((struct S202 *)v18, (struct SpriteS1 *)&v89, (struct PublicTransport *)&v89.gap3[1]);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_2, v19, v80);
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[185], v8);
      v81 = gta2::S202_sub_401B20(v20, (struct SpriteS1 *)&v89.gap3[1], (struct PublicTransport *)&unk_669CA0);
      gta2::S202_sub_40CE30((struct S202 *)&v90.field_10, v13);
      v22 = gta2::Player_sub_401B40(v21, (struct S202 *)&v89.gap3[73], (int)&unk_669DB4);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_3, v22, v81);
      break;
    case 2:
      v23 = v89.gap3[8];
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[193], v89.gap3[8]);
      v25 = gta2::Player_sub_401B40(v24, (struct S202 *)&v89.gap3[81], (int)&v89);
      v26 = v89.gap3[12];
      v82 = v25;
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[249], v89.gap3[12]);
      v28 = gta2::Player_sub_401B40(v27, (struct S202 *)&v89.gap3[89], (int)&v89.gap3[1]);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_1, v28, v82);
      if ( gta2::sub_489600((_DWORD *)self->field_10) )
      {
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[105], v23);
        v30 = gta2::S202_sub_401B20(v29, (struct SpriteS1 *)&v89.gap3[201], (struct PublicTransport *)&unk_669C5C);
        v83 = gta2::S202_sub_401B20((struct S202 *)v30, (struct SpriteS1 *)&v89.gap3[97], (struct PublicTransport *)&v89);
        v73 = (struct SpriteS1 *)&v91;
        v31 = (struct S202 *)&v89.gap3[113];
      }
      else
      {
        gta2::S202_sub_40CE30(&v90, v23);
        v33 = gta2::S202_sub_401B20(v32, (struct SpriteS1 *)&v89.gap3[121], (struct PublicTransport *)&stru_669B70.Tango);
        v83 = gta2::S202_sub_401B20((struct S202 *)v33, (struct SpriteS1 *)&v89.gap3[209], (struct PublicTransport *)&v89);
        v73 = (struct SpriteS1 *)&v89.gap3[129];
        v31 = (struct S202 *)&v89.gap3[217];
      }
      gta2::S202_sub_40CE30(v31, v26);
      v35 = gta2::S202_sub_401B20(v34, v73, (struct PublicTransport *)&stru_669B70.Tango);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_2, v35, v83);
      gta2::S202_sub_40CE30((struct S202 *)&v90.field_18, v23);
      v84 = gta2::S202_sub_401B20(v36, (struct SpriteS1 *)&v89.gap3[137], (struct PublicTransport *)&unk_669CA0);
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[17], v26);
      v38 = gta2::S202_sub_401B20(v37, (struct SpriteS1 *)&v89.gap3[225], (struct PublicTransport *)&stru_669B70.Tango);
      v39 = gta2::S202_sub_401B20((struct S202 *)v38, (struct SpriteS1 *)&v89.gap3[145], &unk_669DB4);
      goto LABEL_25;
    case 3:
      v40 = v89.gap3[8];
      gta2::S202_sub_40CE30((struct S202 *)&v90.CarSystemManager, v89.gap3[8]);
      v41 = v89.gap3[12];
      v85 = v42;
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[21], v89.gap3[12]);
      v44 = gta2::Player_sub_401B40(v43, (struct S202 *)&v89.gap3[161], (int)&v89);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_1, v44, v85);
      if ( gta2::sub_489600((_DWORD *)self->field_10) )
      {
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[45], v40);
        v46 = gta2::S202_sub_401B20(v45, (struct SpriteS1 *)&v89.gap3[37], (struct PublicTransport *)&stru_669B70.Tango);
        v86 = gta2::S202_sub_401B20((struct S202 *)v46, (struct SpriteS1 *)&v89.gap3[29], (struct PublicTransport *)&v89.gap3[1]);
        v74 = (struct SpriteS1 *)&v89.gap3[53];
        p_Tango = (Tango **)&unk_669C5C;
        v47 = (struct SpriteS1 *)&v89.gap3[61];
        v48 = (struct S202 *)&v89.gap3[69];
      }
      else
      {
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[93], v40);
        v50 = gta2::S202_sub_401B20(v49, (struct SpriteS1 *)&v89.gap3[85], (struct PublicTransport *)&stru_669B70.Tango);
        v86 = gta2::S202_sub_401B20((struct S202 *)v50, (struct SpriteS1 *)&v89.gap3[77], (struct PublicTransport *)&v89.gap3[1]);
        v74 = (struct SpriteS1 *)&v89.gap3[101];
        p_Tango = &stru_669B70.Tango;
        v47 = (struct SpriteS1 *)&v89.gap3[109];
        v48 = (struct S202 *)&v89.gap3[117];
      }
      v71 = v47;
      gta2::S202_sub_40CE30(v48, v41);
      v52 = gta2::S202_sub_401B20(v51, v71, (struct PublicTransport *)p_Tango);
      v53 = gta2::S202_sub_401B20((struct S202 *)v52, v74, (struct PublicTransport *)&v89);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_2, v53, v86);
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[133], v40);
      v84 = gta2::Player_sub_401B40(v54, (struct S202 *)&v89.gap3[125], (int)&unk_669DB4);
      v75 = (struct SpriteS1 *)&v89.gap3[141];
      v55 = (struct S202 *)&v89.gap3[149];
      goto LABEL_23;
    case 4:
      v56 = gta2::sub_489600((_DWORD *)self->field_10);
      v57 = v89.gap3[8];
      if ( v56 )
      {
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[165], v89.gap3[8]);
        v87 = gta2::Player_sub_401B40(v58, (struct S202 *)&v89.gap3[157], (int)&v89.gap3[1]);
        v77 = gta2::S202_sub_401B20((struct S202 *)&stru_669B70.Tango, (struct SpriteS1 *)&v89.gap3[173], (struct PublicTransport *)&v89);
        v76 = (struct S202 *)&v89.gap3[181];
        v59 = (struct S202 *)&v89.gap3[189];
      }
      else
      {
        gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[205], v89.gap3[8]);
        v87 = gta2::Player_sub_401B40(v60, (struct S202 *)&v89.gap3[197], (int)&v89.gap3[1]);
        v77 = &v89;
        v76 = (struct S202 *)&v89.gap3[213];
        v59 = (struct S202 *)&v89.gap3[221];
      }
      v41 = v89.gap3[12];
      gta2::S202_sub_40CE30(v59, v89.gap3[12]);
      v62 = gta2::Player_sub_401B40(v61, v76, (int)v77);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_1, v62, v87);
      gta2::S202_sub_40CE30((struct S202 *)&v89.gap3[237], v57);
      v88 = gta2::S202_sub_401B20(v63, (struct SpriteS1 *)&v89.gap3[229], (struct PublicTransport *)&stru_669B70.Tango);
      gta2::S202_sub_40CE30((struct S202 *)&v90.S202, v41);
      v65 = gta2::S202_sub_401B20(v64, (struct SpriteS1 *)&v89.field_100, (struct PublicTransport *)&stru_669B70.Tango);
      v66 = gta2::S202_sub_401B20((struct S202 *)v65, (struct SpriteS1 *)&v89.gap3[245], (struct PublicTransport *)&v89);
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_2, v66, v88);
      gta2::S202_sub_40CE30((struct S202 *)&v90.field_1C, v57);
      v68 = gta2::S202_sub_401B20(v67, (struct SpriteS1 *)&v90.pPlayer, (struct PublicTransport *)&stru_669B70.Tango);
      v84 = gta2::S202_sub_401B20((struct S202 *)v68, (struct SpriteS1 *)&v90.field_C, &unk_669DB4);
      v75 = (struct SpriteS1 *)&v92;
      v55 = (struct S202 *)&v94;
LABEL_23:
      gta2::S202_sub_40CE30(v55, v41);
      v39 = gta2::S202_sub_401B20(v69, v75, (struct PublicTransport *)&unk_669CA0);
LABEL_25:
      gta2::Weapon_sub_432860((struct Weapon *)&self->S103_3, v39, v84);
      break;
    default:
      break;
  }
  gta2::sub_489B10((int)self);
  return self->field_3E;
}


// 0x00493540: S119::IsCarEqual
// IDA: S119::IsCarEqual
// Ghidra: ---
bool gta2::S119_IsCarEqual(struct S119 *self, Car *a2)
{
  return a2 == self->Car;
}



