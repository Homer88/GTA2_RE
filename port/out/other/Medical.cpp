#include "gta2_shim.h"

// Module: other, Class: Medical
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x00472fb0: Medical::sub_472FB0
// IDA: Medical::sub_472FB0
// Ghidra: FUN_00472fb0
void gta2::Medical_sub_472FB0(void *self,Ped *param_1)
{
  gta2::Passenger_sub_445F10((Passenger *)((int)self + 0x10),param_1);
  *(char *)((int)self + 0x14) = *(char *)((int)self + 0x14) + '\x01';
  return;
}


// 0x00473140: Medical::sub_473140
// IDA: Medical::sub_473140
// Ghidra: ---
int gta2::Medical_sub_473140(struct Medical *self)
{
  int result; // eax

  gta2::Passenger_Passenger(&self->Passenger_);
  result = 0;
  self->field = 0;
  self->field_1 = 0;
  self->field_2 = 0;
  LOBYTE(self->Passenger_.PassengerPrev) = 0;
  HIWORD(self->Passenger_.PassengerPrev) = 0;
  self->field_14 = 0;
  LOBYTE(self->field_18) = 0;
  self->S110_ = 0;
  self->Ped_ = 0;
  self->field_C = 0;
  BYTE1(self->field_18) = 0;
  return result;
}


// 0x00473170: Medical::sub_473170
// IDA: Medical::sub_473170
// Ghidra: ---
char gta2::Medical_sub_473170(struct Medical *self)
{
  S169 *v2; // ebx
  struct Ped *Ped; // eax
  struct Ped *v5; // esi
  struct Ped *pPed; // edi
  struct Ped *v7; // [esp+Ch] [ebp-4h] BYREF

  v2 = gta2::Medical_sub_404C40(self);
  if ( !v2 || gCharacter->field_5 >= 0x1Eu )
    return 0;
  Ped = gta2::Character_CreatePed(gCharacter);
  v5 = Ped;
  if ( !Ped )
    return 0;
  gta2::Ped_SetSearchType(Ped, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(v5, UNKNOWN_OCUPATION_23);
  gta2::Ped_sub_433BB0(v5, 2);
  gta2::Ped_PutPedInCarRelated(v5, self->S110_->Car);
  gta2::Ped_PedSetObjective(v5, 14, 0);
  gta2::S202_sub_40CE30((S202 *)&v7, self->field);
  v5->Weapon2 = (int)v7;
  gta2::S202_sub_40CE30((S202 *)&v7, self->field_1);
  v5->Gang_ = v7;
  gta2::S202_sub_40CE30((S202 *)&v7, self->field_2);
  v5->DriverPed = (int)v7;
  v5->field_228 = 1;
  v5->field_224 = 0;
  gta2::Ped_SetRemap(v5, 16);
  v5->Invulnerability = GRAPHIC_DUMMY;
  v5->field_194 = unk_6640B4.field_0;
  pPed = gta2::Character_CreatePed(gCharacter);
  if ( !pPed )
    return 0;
  gta2::Ped_sub_433320(pPed, self->S110_->Car);
  gta2::Ped_SetSearchType(pPed, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(pPed, UNKNOWN_OCUPATION_23);
  gta2::Ped_sub_433BB0(pPed, 2);
  gta2::Ped_PedSetObjective(pPed, 0, 9999);
  gta2::Ped_SetRemap(pPed, 16);
  pPed->Invulnerability = GRAPHIC_DUMMY;
  pPed->field_228 = 1;
  pPed->field_224 = 0;
  gta2::S169_sub_404400(v2, v5);
  gta2::S169_SetListSize(v2, 1);
  gta2::S169_AddPedtoList(v2, pPed, 0);
  LOBYTE(v2->Ped1[0]) = 0;
  self->S110_->Ped_ = v5;
  self->S110_->field_28 = 6;
  gta2::Car_CarMakeDriveable1(self->S110_->Car, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Car_CarMakeDriveable4(self->S110_->Car);
  gta2::Car_CarMakeDummy(self->S110_->Car);
  gta2::Car_sub_4222D0(self->S110_->Car);
  self->S110_->NPC = v2;
  return 1;
}


// 0x00473320: Medical::sub_473320
// IDA: Medical::sub_473320
// Ghidra: ---
void gta2::Medical_sub_473320(struct Medical *self)
{
  void *pCar; // edi
  struct Ped *v3; // ecx
  struct S110 *S110; // eax
  struct Car *CurrentCar; // edx
  S169 *NPC; // eax
  bool v7; // al
  struct Car *Car; // ecx

  pCar = self->S110_;
  if ( *((_DWORD *)pCar + 9) == 2 )
  {
    v3 = (Ped *)*((_DWORD *)pCar + 1);
    if ( !v3 || gta2::Ped_GetDeadPed(v3) )
    {
      *((_DWORD *)pCar + 10) = 5;
      self->S110_->field_2C = 0;
      unk_663DE0 = 0;
      return;
    }
    if ( *(_DWORD *)pCar )
    {
      if ( gta2::Car_GetFullDamage(*(Car **)pCar) )
      {
        *(_DWORD *)pCar = 0;
        self->S110_->field_24 = 0;
      }
    }
    else
    {
      *((_DWORD *)pCar + 9) = 0;
    }
  }
  unk_663DE0 = self->S110_->Ped_;
  if ( unk_663DE0 )
  {
    if ( LOBYTE(self->field_18) )
    {
      S110 = self->S110_;
      if ( S110->field_24 )
      {
        CurrentCar = unk_663DE0->field_10B;
        if ( CurrentCar )
        {
          if ( unk_663DE0 == CurrentCar->Driver )
          {
            NPC = S110->NPC;
            if ( NPC )
            {
              v7 = gta2::S169_sub_404840(NPC);
              Car = self->S110_->Car;
              if ( v7 )
              {
                gta2::Car_sub_4222D0(Car);
                self->S110_->field_28 = 5;
                self->S110_->field_2C = 0;
                unk_663DE0 = 0;
              }
              else
              {
                gta2::Car_sub_4222F0(Car);
              }
            }
          }
        }
      }
      else
      {
        S110->field_28 = 5;
        self->S110_->field_2C = 0;
      }
    }
  }
  else
  {
    self->S110_->field_24 = 2;
  }
}


// 0x00473410: Medical::sub_473410
// IDA: Medical::sub_473410
// Ghidra: ---
int gta2::Medical_sub_473410(struct Medical *self)
{
  int result; // eax
  struct Ped *pPed; // ebp
  struct Ped *Ped; // edi
  bool v5; // zf
  struct Ped *v6; // edi
  struct S110 *v7; // eax
  struct Car *Car; // edi
  void *v9; // ecx
  Passenger *v10; // eax
  struct Ped *v11; // edi
  struct S110 *S110; // ecx
  struct EngineStruct *EngineStruct; // eax
  char Index; // al
  struct Car *CurrentCar; // eax
  char v16; // al
  char v17; // al
  struct Ped *v18; // edi
  struct S110 *v19; // ecx
  struct S110 *v20; // edi
  struct Ped *v21; // ecx
  struct Ped *Passenger; // edi
  char v23; // al
  struct Ped **v24; // eax
  S169 *NPC; // eax
  Passenger *v26; // eax
  struct Ped *v27; // edi
  struct S110 *v28; // eax
  S169 *v29; // eax
  struct S110 *v30; // eax
  S169 *v31; // eax
  bool v32; // [esp+11h] [ebp-2Fh]
  bool v33; // [esp+12h] [ebp-2Eh]
  bool v34; // [esp+13h] [ebp-2Dh]
  struct Ped *a2; // [esp+14h] [ebp-2Ch]
  unsigned __int8 v36; // [esp+18h] [ebp-28h]
  S202 v37; // [esp+1Ch] [ebp-24h] BYREF
  int Z; // [esp+3Ch] [ebp-4h] BYREF

  result = (int)self->S110_;
  v32 = 0;
  v34 = 0;
  v36 = 0;
  pPed = *(Ped **)(result + 4);
  unk_663DE0 = pPed;
  Ped = self->Ped_;
  a2 = Ped;
  v33 = self->S110_->field_24 == 0;
  if ( pPed )
  {
    while ( 2 )
    {
      if ( Ped )
      {
        if ( !gta2::Ped_Get_433B40(Ped) )
        {
          if ( gta2::Ped_GetPedState(pPed) != 9 )
            gta2::Ped_PedSetObjective(pPed, 0, 9999);
          v5 = Ped == self->Ped_;
          goto LABEL_12;
        }
        if ( pPed->GameObject2 )
        {
          if ( !sub_435430(Ped) )
          {
LABEL_15:
            pPed = unk_663DE0;
            goto LABEL_16;
          }
          gta2::Ambulance_AddPedToAmbulance(gAmbulance, a2);
          v6 = unk_663DE0;
          if ( gta2::Ped_GetPedState(unk_663DE0) != 9 )
            gta2::Ped_PedSetObjective(v6, 0, 9999);
          v5 = a2 == self->Ped_;
LABEL_12:
          if ( v5 )
            self->Ped_ = 0;
          else
            self->field_C = 0;
          goto LABEL_15;
        }
      }
LABEL_16:
      switch ( gta2::Ped_GetState(pPed) )
      {
        case 0:
          if ( gta2::Ped_sub_472FD0(pPed) )
          {
            v10 = sub_446100(&self->Passenger_);
            v11 = (Ped *)v10;
            if ( v10 )
            {
              v5 = !sub_435430(v10);
              CurrentCar = unk_663DE0->field_10B;
              if ( v5 )
              {
                if ( CurrentCar && (unk_663DE0->PositionX1 & 0x8000000) == 0 )
                {
                  gta2::Ped_PedSetObjective(unk_663DE0, 36, 9999);
                  gta2::Ped_SetCurrentCar(unk_663DE0, self->S110_->Car);
                  gta2::Ped_SetSearchType(unk_663DE0, SEARCHTYPE_AREA_PLAYER_ONLY);
                  v32 = 1;
                  self->Ped_ = v11;
                  goto LABEL_96;
                }
                gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
                gta2::Ped_PedSetObjective(unk_663DE0, 16, 9999);
                gta2::Ped_SetDriverPed(unk_663DE0, v11);
                v32 = 1;
LABEL_54:
                self->Ped_ = v11;
                goto LABEL_96;
              }
              if ( CurrentCar )
              {
                gta2::Ped_PedSetObjective(unk_663DE0, 0, 9999);
                gta2::Ped_UpdatePedState(unk_663DE0, 10);
                gta2::Ped_sub_4332B0(unk_663DE0, 10);
                v32 = 1;
                v16 = LOBYTE(self->Passenger_.PassengerPrev) - 1;
                self->Ped_ = v11;
                LOBYTE(self->Passenger_.PassengerPrev) = v16;
              }
              else
              {
                if ( !v33 && (unk_663DE0->PositionX1 & 0x8000000) == 0 )
                {
                  gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
                  gta2::Ped_PedSetObjective(unk_663DE0, 35, 9999);
                  gta2::Ped_SetCurrentCar(unk_663DE0, self->S110_->Car);
                  gta2::Ped_SetTargetCarDoor(unk_663DE0, 0);
                  gta2::Ped_SetAnimationState_0(unk_663DE0, 0);
                }
                v32 = 1;
                v17 = LOBYTE(self->Passenger_.PassengerPrev) - 1;
                self->Ped_ = v11;
                LOBYTE(self->Passenger_.PassengerPrev) = v17;
              }
            }
            else if ( unk_663DE0->field_10B )
            {
              gta2::Ped_PedSetObjective(unk_663DE0, 0, 9999);
              gta2::Ped_UpdatePedState(unk_663DE0, 10);
              gta2::Ped_sub_4332B0(unk_663DE0, 10);
              S110 = self->S110_;
              if ( !S110->Car )
                goto LABEL_54;
              EngineStruct = S110->Car->EngineStruct_;
              if ( EngineStruct )
              {
                Index = EngineStruct->JuncIdx;
                if ( Index > 0 )
                {
                  gta2::JuncIds_ClearJunctionId(gJuncIds, Index);
                  self->S110_->Car->EngineStruct_->JuncIdx = -1;
                }
              }
              if ( self->S110_->Car->Model_ )
              {
                gta2::S121_ReleaseModel(gS121, self->S110_->Car->Model_);
                self->S110_->Car->Model_ = 0;
              }
              if ( gta2::S169_sub_404840(self->S110_->NPC) )
              {
                gta2::Car_sub_4222D0(self->S110_->Car);
LABEL_38:
                v32 = 0;
                self->Ped_ = 0;
                goto LABEL_96;
              }
              gta2::Car_sub_4222F0(self->S110_->Car);
              self->Ped_ = 0;
            }
            else
            {
              if ( v33 || (unk_663DE0->PositionX1 & 0x8000000) != 0 )
                goto LABEL_38;
              gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
              gta2::Ped_PedSetObjective(unk_663DE0, 35, 9999);
              gta2::Ped_SetCurrentCar(unk_663DE0, self->S110_->Car);
              gta2::Ped_SetTargetCarDoor(unk_663DE0, 0);
              gta2::Ped_SetAnimationState_0(unk_663DE0, 0);
              self->Ped_ = 0;
            }
          }
          else if ( gta2::Ped_GetCurrentAction(pPed) == 9 )
          {
            v18 = (Ped *)sub_446100(&self->Passenger_);
            if ( v18 )
            {
              gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
              gta2::Ped_PedSetObjective(unk_663DE0, 16, 9999);
              gta2::Ped_SetDriverPed(unk_663DE0, v18);
              v19 = self->S110_;
              --LOBYTE(self->Passenger_.PassengerPrev);
              v19->NPC->field_30 = 1;
            }
            self->field_C = (int)v18;
          }
          goto LABEL_96;
        case 14:
          v32 = 1;
          v7 = self->S110_;
          if ( !pPed->field_10B )
          {
            v7->field_28 = 6;
            goto LABEL_25;
          }
          Car = v7->Car;
          v32 = v7->Car->field_76 <= 1000;
          if ( gta2::Ped_GetDamageState(pPed) == 1 )
          {
            gta2::Car_sub_4222F0(Car);
            self->S110_->field_28 = 6;
LABEL_25:
            gta2::Ped_PedSetObjective(unk_663DE0, 0, 9999);
            goto LABEL_96;
          }
          gta2::S202_sub_40CE30(&v37, self->field_1);
          gta2::S202_sub_40CE30((S202 *)&v37.S202, self->field);
          gta2::Ped_GetYCoordinate(pPed, &v37.field_C);
          gta2::Ped_GetXCoordinate(pPed, (int)&v37.field_10);
          v37.CarSystemManager = (CarSystemManager *)gta2::sub_42A6B0(v9, &v37.pPlayer)->Car;
          if ( !gta2::sub_4037E0(&v37.CarSystemManager) )
            goto LABEL_96;
          if ( !(unsigned __int16)sub_445BB0(&self->Passenger_) )
          {
            v32 = 0;
            goto LABEL_96;
          }
          if ( (unsigned __int16)gta2::Ped_Get_sub_403B30(unk_663DE0) > 0x32u )
          {
            gta2::Car_sub_4222F0(self->S110_->Car);
            self->S110_->field_28 = 6;
            goto LABEL_25;
          }
LABEL_96:
          result = (int)self->S110_->NPC;
          if ( result )
          {
            pPed = *(Ped **)(result + 4 * v36 + 4);
            unk_663DE0 = pPed;
            Ped = (Ped *)self->field_C;
            a2 = Ped;
          }
          else
          {
            Ped = a2;
            pPed = 0;
            unk_663DE0 = 0;
          }
          ++v36;
          if ( pPed )
            continue;
          if ( !v32 )
            goto LABEL_101;
          return result;
        case 16:
          Passenger = gta2::Ped_GetDriver(pPed);
          if ( gta2::Ped_Get_450CB0(pPed) )
          {
            v23 = BYTE1(self->field_18) + 1;
            BYTE1(self->field_18) = v23;
            if ( v23 == 50 )
            {
              if ( Passenger->field_228 == 1 )
                v34 = gta2::Ped_GetCurrentOccupation(Passenger) == UNKNOWN_OCUPATION_23;
              gta2::Ped_SetAnimationState(Passenger, 0, 9999);
              if ( v34 )
              {
                gta2::Ped_sub_403B40(Passenger, 1);
              }
              else
              {
                gta2::Ped_SetAnimationState(Passenger, 0, 9999);
                Passenger->field_214 = PEDSTATE_MOVE_TURN;
                Passenger->ObjectiveTimer = 0;
                gta2::Ped_PedSetObjective(Passenger, 1, 9999);
                Passenger->Weapon2 = *(_DWORD *)gta2::Ped_GetXCoordinate(Passenger, (int)&v37.field_18);
                gta2::Ped_GetYCoordinate(Passenger, (int *)&v37.field_1C);
                Passenger->Gang_ = *v24;
                Passenger->DriverPed = *(_DWORD *)gta2::Ped_GetPositionZ(Passenger, (int)&Z);
                gta2::Ped_SetSearchType(Passenger, SEARCHTYPE_AREA);
                gta2::Ped_SetCurrentOccupation(Passenger, DUMMY);
                Passenger->field_228 = 3;
              }
              gta2::Ped_SetHealth(Passenger, 100);
              gta2::Ped_sub_403960(Passenger);
              if ( Passenger == self->Ped_ )
                self->Ped_ = 0;
              else
                self->field_C = 0;
              gta2::Ped_PedSetObjective(unk_663DE0, 0, 9999);
              BYTE1(self->field_18) = 0;
            }
          }
          v32 = 1;
          NPC = self->S110_->NPC;
          if ( NPC )
            BYTE1(NPC->Ped1[0]) = 0;
          goto LABEL_96;
        case 28:
          if ( gta2::Ped_Get_450CB0(pPed) )
          {
            pPed->field_214 = PEDSTATE_MOVE_TURN;
            unk_663DE0->ObjectiveTimer = 0;
            gta2::Ped_PedSetObjective(unk_663DE0, 0, 9999);
            gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
            v20 = self->S110_;
            v21 = v20->Ped_;
            if ( unk_663DE0 != v21 && gta2::Ped_GetDeadPed(v21) )
            {
              gta2::S169_sub_404120(v20->NPC, 0);
              self->S110_->Ped_ = self->S110_->NPC->Ped_;
              gta2::Ped_PedSetObjective(self->S110_->Ped_, 0, 9999);
              gta2::Ped_SetAnimationState(self->S110_->Ped_, 0, 9999);
            }
            self->S110_->field_28 = 6;
          }
          goto LABEL_96;
        case 35:
          if ( gta2::Ped_sub_472FD0(pPed) )
          {
            if ( pPed->field_10B )
            {
              gta2::Ped_PedSetObjective(pPed, 0, 9999);
              gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
              gta2::Ped_UpdatePedState(unk_663DE0, 10);
              gta2::Ped_sub_4332B0(unk_663DE0, 10);
              goto LABEL_95;
            }
            v26 = sub_446100(&self->Passenger_);
            v27 = (Ped *)v26;
            if ( v26 )
            {
              if ( sub_435430(v26) )
              {
                gta2::Ambulance_AddPedToAmbulance(gAmbulance, a2);
                v30 = self->S110_;
                if ( v30->field_24 != 1 )
                {
LABEL_87:
                  gta2::Ped_PedSetObjective(unk_663DE0, 0, 9999);
                  gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
                  goto LABEL_95;
                }
                v31 = v30->NPC;
                if ( v31 )
                  BYTE1(v31->Ped1[0]) = 1;
              }
              else
              {
                gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
                gta2::Ped_PedSetObjective(unk_663DE0, 16, 9999);
                gta2::Ped_SetDriverPed(unk_663DE0, v27);
                --LOBYTE(self->Passenger_.PassengerPrev);
                if ( gta2::Ped_sub_472FD0(unk_663DE0) )
                  self->Ped_ = v27;
                else
                  self->field_C = (int)v27;
              }
            }
            else
            {
              v28 = self->S110_;
              if ( v28->field_24 != 1 )
                goto LABEL_87;
              v29 = v28->NPC;
              if ( v29 )
                BYTE1(v29->Ped1[0]) = 1;
            }
LABEL_95:
            v32 = 1;
          }
          else
          {
            gta2::Ped_PedSetObjective(pPed, 0, 9999);
            gta2::Ped_SetAnimationState(unk_663DE0, 0, 9999);
          }
          goto LABEL_96;
        case 36:
          if ( gta2::Ped_Get_450CB0(pPed) )
          {
            gta2::Ped_SetAnimationState(pPed, 0, 9999);
            gta2::Ped_PedSetObjective(unk_663DE0, 16, 9999);
            gta2::Ped_SetDriverPed(unk_663DE0, self->Ped_);
          }
          goto LABEL_95;
        default:
          goto LABEL_96;
      }
    }
  }
LABEL_101:
  LOBYTE(self->field_18) = 1;
  return result;
}


// 0x00473ce0: Medical::sub_473CE0
// IDA: Medical::sub_473CE0
// Ghidra: ---
void * gta2::Medical_sub_473CE0(struct Medical *self)
{
  Passenger *p_Passenger; // edi
  void *result; // eax
  struct Ped *v4; // eax
  struct S110 *v5; // eax
  struct Car *Car; // ecx
  struct Car *S110; // eax
  struct S110 *v8; // esi

  p_Passenger = &self->Passenger_;
  gta2::S195_sub_446060(&self->Passenger_);
  result = self->S110_;
  switch ( *((_DWORD *)result + 10) )
  {
    case 3:
      if ( *((_BYTE *)result + 44) )
      {
        if ( gta2::Medical_sub_473170(self) )
        {
          unk_663DE0 = self->S110_->Ped_;
          S110 = (Car *)self->S110_;
          LOBYTE(self->field_18) = 0;
          if ( !S110->Car )
            return (void *)gta2::Medical_sub_473410(self);
          gta2::Car_sub_422D20((Car *)S110->Car);
          return (void *)gta2::Medical_sub_473410(self);
        }
        else
        {
          Car = self->S110_->Car;
          if ( Car )
            gta2::Car_isMask4(Car);
          gta2::S110_sub_4C5480_2(self->S110_);
          return (void *)gta2::Medical_sub_473140(self);
        }
      }
      else
      {
        ++*((_WORD *)result + 14);
        v8 = self->S110_;
        if ( v8->field_1C > 500 )
          v8->field_28 = 5;
      }
      break;
    case 5:
      while ( !gta2::Passenger_Passenger_des(p_Passenger) )
      {
        v4 = (Ped *)sub_446100(p_Passenger);
        gta2::Ambulance_AddPedToAmbulance(gAmbulance, v4);
      }
      v5 = self->S110_;
      if ( !v5->field_2C )
        return (void *)gta2::Medical_sub_473410(self);
      v5->field_28 = 0;
      gta2::S110_sub_4C5480_2(self->S110_);
      return (void *)gta2::Medical_sub_473140(self);
    case 6:
      gta2::Medical_sub_473320(self);
      return (void *)gta2::Medical_sub_473410(self);
    default:
      gta2::debug_log(0x3EEu, "medical.cpp", 1087);
      return (void *)gta2::Medical_sub_473410(self);
  }
  return result;
}



