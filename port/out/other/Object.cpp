#include "gta2_shim.h"

// Module: other, Class: Object
// Functions: 22
// Source: unified (IDA+Ghidra)

// 0x00482960: Object::sub_482960
// IDA: Object::sub_482960
// Ghidra: FUN_00482960
void gta2::Object_sub_482960(int param_1,undefined1 param_2)
{
  *(undefined1 *)(param_1 + 0x18) = param_2;
  return;
}


// 0x00482970: Object::GetS63
// IDA: Object::GetS63
// Ghidra: ---
EventHandler * gta2::Object_GetS63(Object *self)
{
  return self->S63;
}


// 0x00483d90: Object::sub_483D90
// IDA: Object::sub_483D90
// Ghidra: ---
void gta2::Object_sub_483D90(Object *self, int a2)
{
  unsigned __int16 v2; // bp
  EventHandler *S63; // eax
  void *v4; // ebx
  EventHandler *pS63; // edi
  _DWORD *v6; // eax
  int v7; // esi
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  unsigned __int16 v10; // [esp+10h] [ebp-Ch]
  int v11; // [esp+14h] [ebp-8h] BYREF
  int v12; // [esp+18h] [ebp-4h] BYREF

  v2 = 0;
  S63 = gta2::Object_GetS63((Object *)gCollisionBox);
  v4 = (void *)a2;
  pS63 = S63;
  *(_DWORD *)&v10 = 0;
  do
  {
    if ( pS63->S63_1_ )
    {
      if ( gta2::S63_sub_421060(pS63) )
      {
        gta2::S63_sub_4340D0(pS63, &a2);
        v7 = v2;
        *((_DWORD *)v4 + v2) = *v6;
        gta2::S63_sub_4340E0(pS63, &v11);
        *((_DWORD *)v4 + v2 + 20) = *v8;
        gta2::S63_sub_4340F0(pS63, &v12);
        *((_DWORD *)v4 + v2 + 40) = *v9;
        *((_WORD *)v4 + v2++ + 120) = pS63->S63_1_;
        *((_BYTE *)v4 + v7 + 280) = gta2::S63_sub_4340A0(pS63);
        if ( v2 >= 0x14u )
          break;
      }
    }
    ++pS63;
    ++*(_DWORD *)&v10;
  }
  while ( v10 < 0xEF1u );
}


// 0x00484af0: Object::Object
// IDA: Object::Object
// Ghidra: ---
Object * gta2::Object_Object(Object *self)
{
  CollisionBox *_pS61; // eax
  CollisionBox *pS61; // eax
  SpriteS1 *_pS64; // eax
  TriggerVolume *pS64; // eax
  S66 *_pS66; // eax
  S66 *pS66; // eax
  SpriteS1 *v8; // eax
  EventHandler *v9; // ecx
  SpriteS3 *v10; // ecx
  SpriteS1 *v11; // ecx
  CarSystemManager *v12; // eax
  EventHandler *v13; // ecx
  SpriteS3 *v14; // ecx
  SpriteS1 *v15; // ecx
  int v17; // [esp-Ch] [ebp-28h] BYREF
  SpriteS3 *v18; // [esp-8h] [ebp-24h] BYREF
  EventHandler *v19; // [esp-4h] [ebp-20h] BYREF
  int v20; // [esp+0h] [ebp-1Ch]
  int v21; // [esp+Ch] [ebp-10h]

  gta2::Arsenal_Reset((Arsenal *)&self->S63[0].field_14);
  memset(&self->S63[0].S63_1, 1u, 48u);
  *(_WORD *)&self->S63[1].field_1C = 257;
  self->S63[1].field_20 = 0;
  self->S63[0].pEventHandler = 0;
  self->S63[0].S65 = 0;
  unk_665770 = 0;
  unk_665764 = 0;
  unk_66576C = 0;
  unk_665778 = 0;
  self->S63[1].S202 = 0;
  LOBYTE(self->S63[0].Car) = 0;
  unk_665761 = 0;
  unk_665774 = 0;
  unk_665760 = 0;
  unk_665768 = 0;
  if ( !gCollisionBox )
  {
    _pS61 = (CollisionBox *)gta2::operator_new(0x29178u);
    v17 = 0;
    pS61 = _pS61 ? gta2::S61_S61(_pS61) : 0;
    v17 = -1;
    gCollisionBox = pS61;
    if ( !pS61 )
      gta2::debug_log(0x20u, "object.cpp", 4239);
  }
  _pS64 = (SpriteS1 *)gta2::operator_new(0x226Cu);
  v17 = (int)_pS64;
  v20 = 1;
  if ( _pS64 )
    pS64 = gta2::S64_S64((TriggerVolume *)_pS64);
  else
    pS64 = 0;
  v20 = -1;
  gTriggerVolume = pS64;
  if ( !pS64 )
    gta2::debug_log(0x20u, "object.cpp", 4243);
  _pS66 = (S66 *)gta2::operator_new(0x5A40u);
  v20 = (int)_pS66;
  v21 = 2;
  if ( _pS66 )
    pS66 = gta2::S66_S66(_pS66);
  else
    pS66 = 0;
  v21 = -1;
  unk_665780 = pS66;
  if ( !pS66 )
    gta2::debug_log(0x20u, "object.cpp", 4245);
  v8 = gta2::SpriteS1_sub_421000(gSpriteS1);
  v19 = v9;
  self->S63[1].S202 = (S202 *)v8;
  v21 = (int)&v19;
  gta2::bitShiftLeft1(&v19, 0);
  v18 = v10;
  v21 = (int)&v18;
  gta2::bitShiftLeft1(&v18, 0);
  v17 = (int)v11;
  v21 = (int)&v17;
  gta2::bitShiftLeft1(&v17, 0);
  gta2::SpriteS1_sub_420600((SpriteS1 *)self->S63[1].S202, v17, (int)v18, (int)v19);
  LOWORD(v12) = (_WORD)word_6657F8;
  gta2::SpriteS1_SetRotation((SpriteS1 *)self->S63[1].S202, v12);
  v19 = v13;
  v21 = (int)&v19;
  gta2::bitShiftLeft1(&v19, 0);
  v18 = v14;
  v21 = (int)&v18;
  gta2::bitShiftLeft1(&v18, 0);
  v17 = (int)v15;
  v21 = (int)&v17;
  gta2::bitShiftLeft1(&v17, 0);
  gta2::SpriteS1_sub_4BCB90((SpriteS1 *)self->S63[1].S202, (SpriteS1 *)v17, v18, v19);
  self->field_0 = 0;
  self->S63[0].SpriteS1 = 0;
  self->S63[0].NextElement = 0;
  self->field_4 = 0;
  return self;
}


// 0x00484cf0: Object::ExitInGameMenu
// IDA: Object::ExitInGameMenu
// Ghidra: ---
SpriteS1 * gta2::Object_ExitInGameMenu(Object *self)
{
  SpriteS1 *result; // eax

  result = (SpriteS1 *)self->S63[1].S202;
  if ( result )
  {
    result = gta2::SpriteS1_SpriteS1_Des(gSpriteS1, result);
    self->S63[1].S202 = 0;
  }
  if ( gCollisionBox )
  {
    result = (SpriteS1 *)gta2::S61_S61_Des(gCollisionBox, 1);
    gCollisionBox = 0;
  }
  if ( gTriggerVolume )
  {
    result = (SpriteS1 *)gta2::S64_S64_des(gTriggerVolume, 1);
    gTriggerVolume = 0;
  }
  if ( unk_665780 )
  {
    result = (SpriteS1 *)gta2::S66_S66_des(unk_665780, 1);
    unk_665780 = 0;
  }
  self->field_0 = 0;
  self->S63[0].SpriteS1 = 0;
  self->S63[0].NextElement = 0;
  self->field_4 = 0;
  return result;
}


// 0x00484e00: Object::sub_484E00
// IDA: Object::sub_484E00
// Ghidra: ---
EventHandler * gta2::Object_sub_484E00(Object *self, S900 *a2)
{
  int v3; // eax
  int v5; // edi
  EventHandler *v6; // eax
  EventHandler *pS63; // esi
  __int16 v8; // bx
  byte Car; // al
  int v10; // eax
  int v11; // eax
  struct S65 *pS65; // eax
  S101 *pS101; // eax
  S67 *pS67; // eax
  int v15; // edx
  S67 *pS67_1; // eax
  int v17; // ecx
  struct S65 *pS68_1; // eax
  int v19; // ecx
  struct S63_1 *S63_1; // eax
  EventHandler *v21; // edi
  int *v22; // ebx
  SpriteS1 *v23; // eax
  int v24; // [esp-8h] [ebp-18h] BYREF
  EventHandler *pS63_1; // [esp-4h] [ebp-14h]
  int v26; // [esp+18h] [ebp+8h]
  int v27; // [esp+1Ch] [ebp+Ch]
  int v28; // [esp+20h] [ebp+10h]
  __int16 v29; // [esp+24h] [ebp+14h]
  SpriteS1 v30; // [esp+28h] [ebp+18h] BYREF

  if ( a2 == (S900 *)266 )
  {
    v3 = self->S63[1].field_20;
    if ( !*((_BYTE *)&self->S63[0].S63_1 + v3) )
    {
      self->S63[1].field_20 = v3 + 1;
      return 0;
    }
  }
  v5 = gta2::PathNode_sub_488170(gPathNode, (int)a2);
  if ( *(_DWORD *)(v5 + 92) == 2 )
  {
    v6 = self->S63[0].pEventHandler;
    if ( v6 == (EventHandler *)360 )
      return 0;
    self->S63[0].pEventHandler = (EventHandler *)((char *)&v6->NextElement + 1);
  }
  if ( *(_BYTE *)(v5 + 97) )
  {
    pS63 = gta2::S61_sub_4829A0(gCollisionBox);
    pS63->field_20 = 1;
  }
  else
  {
    pS63 = gta2::S61_sub_4829C0(gCollisionBox);
    pS63->field_20 = 2;
  }
  v8 = v29;
  gta2::S63_sub_483990(pS63, (int)a2, v26, v27, v28, v29);
  Car = (byte)self->S63[0].Car;
  if ( Car )
  {
    gta2::S63_sub_482790(pS63, Car);
    LOBYTE(self->S63[0].Car) = 0;
  }
  if ( LOBYTE(v30.FirstElement)
    && (gta2::SpriteS1_sub_4BDFE0(pS63->SpriteS1_, 0)
     || *(_DWORD *)(v5 + 64) == 3 && gta2::S56_sub_447740(gCheckpoint2, pS63->SpriteS1_, 0)) )
  {
    v10 = pS63->field_20;
    pS63_1 = pS63;
    if ( v10 == 1 )
    {
      gta2::S61_sub_484D60(gCollisionBox, (SpriteS1 *)pS63_1);
      return 0;
    }
    gta2::S61_sub_484DB0(gCollisionBox, pS63_1);
    return 0;
  }
  if ( *(_DWORD *)(v5 + 92) == 3 )
  {
    ++self->S63[0].S65;
    gta2::Turrel_sub_4BED60((Arsenal *)&self->S63[0].field_14, pS63->SpriteS1_);
  }
  switch ( *(_DWORD *)(v5 + 52) )
  {
    case 0:
    case 1:
    case 6:
    case 0xA:
    case 0xC:
      v11 = 0;
      pS63->Car = 0;
      goto LABEL_30;
    case 2:
    case 8:
      pS65 = gta2::S64_sub_483FA0(gTriggerVolume);
      pS63->S65_ = pS65;
      HIBYTE(pS65->field_6) = 0;
      pS63->S65_->field_4 = *(char *)(v5 + 101);
      LOBYTE(pS63->S65_->field_6) = 0;
      break;
    case 3:
    case 7:
      pS67 = gta2::S66_NextElement(unk_665780);
      v15 = pS63->field_14;
      pS63->Car = (Car *)pS67;
      pS67->field_20 = v15;
      *(_DWORD *)pS63->Car->CarDoor_[0].AnimationFrame = pS63->pEventHandler->Car;
      *(_DWORD *)&pS63->Car->CarDoor_[0].field_C = *(_DWORD *)(v5 + 20);
      LOWORD(pS63->Car->Passenger_) = v8;
      *(_WORD *)&pS63->Car->CarDoor_[1].field_C = SBYTE1(pS63->pEventHandler[2].S65);
      pS63->Car->CarDoor_[0].doorState = dword_665894;
      *(_DWORD *)pS63->Car->CarDoor_[1].AnimationFrame = dword_665894;
      break;
    case 4:
    case 9:
      pS67_1 = gta2::S66_NextElement(unk_665780);
      v17 = pS63->field_14;
      pS63->Car = (Car *)pS67_1;
      pS67_1->field_20 = v17;
      *(_DWORD *)pS63->Car->CarDoor_[0].AnimationFrame = pS63->pEventHandler->Car;
      *(_DWORD *)&pS63->Car->CarDoor_[0].field_C = *(_DWORD *)(v5 + 20);
      pS63->Car->CarDoor_[0].doorState = dword_665894;
      *(_DWORD *)pS63->Car->CarDoor_[1].AnimationFrame = dword_665894;
      LOWORD(pS63->Car->Passenger_) = v8;
      *(_WORD *)&pS63->Car->CarDoor_[1].field_C = SBYTE1(pS63->pEventHandler[2].S65);
      pS68_1 = gta2::S64_sub_483FA0(gTriggerVolume);
      pS63->S65_ = pS68_1;
      HIBYTE(pS68_1->field_6) = 0;
      pS63->S65_->field_4 = *(char *)(v5 + 101);
      LOBYTE(pS63->S65_->field_6) = 0;
      break;
    case 5:
      pS101 = gta2::S102_sub_48A6C0(gS102);
      pS63->S65_ = (S65 *)pS101;
      if ( !pS101 )
        return 0;
      pS63->field_1C = 1;
      break;
    case 0xB:
      pS63_1 = 0;
      v24 = 0;
      gta2::bitShiftLeft1(&v24, 0);
      v11 = gta2::S115_sub_469010(gS115, v26, v27, v28, 0, v24, (unsigned __int8)pS63_1);
LABEL_30:
      pS63->S65_ = (S65 *)v11;
      break;
    default:
      break;
  }
  ++unk_66578C;
  pS63->S63_1_ = (S63_1 *)a2;
  if ( gta2::S63_sub_421060(pS63) )
    gta2::S63_sub_483D50(pS63);
  S63_1 = pS63->S63_1_;
  if ( S63_1 == (S63_1 *)281 )
  {
    LOWORD(v19) = word_6657F8[0];
    v21 = gta2::Object_SpawnObject(self, 284, dword_665894, dword_665894, dword_665894, v19);
    v22 = (int *)gta2::Radar_AddBlip((Tango *)&unk_6657FC, &v30, (PublicTransport *)&dword_6659B4);
    v23 = gta2::Radar_AddBlip((Tango *)&unk_6657FC, (SpriteS1 *)&a2, (PublicTransport *)&unk_6657C4);
    gta2::SpriteS1_sub_4B9D50(pS63->SpriteS1_, (int)v21->SpriteS1_, v23->FirstElement, *v22, word_6657F8[0]);
    return pS63;
  }
  else
  {
    if ( S63_1 == (S63_1 *)266 )
    {
      gta2::S63_sub_447E90(pS63, self->S63[1].field_20);
      ++self->S63[1].field_20;
    }
    return pS63;
  }
}


// 0x00485180: Object::sub_485180
// IDA: Object::sub_485180
// Ghidra: ---
void gta2::Object_sub_485180(
        Object *self,
        S900 *a2,
        int a3,
        int a4,
        int a5,
        __int16 a6,
        int a7,
        Ped *a8,
        int a9,
        int a10,
        int a11)
{
  EventHandler *v11; // eax
  EventHandler *v12; // esi
  int v13; // edi
  S67 *Element; // eax
  struct Car *Car; // edi
  int v16; // eax

  v11 = gta2::Object_sub_484E00(self, a2);
  v12 = v11;
  if ( v11 )
  {
    gta2::S63_sub_482630(v11);
    v13 = gta2::PathNode_sub_488170((PathNode *)gCarSystemManager2.field_24, (int)a2);
    if ( v12->Car || (Element = gta2::S66_NextElement(unk_665780), (v12->Car = (Car *)Element) != 0) )
    {
      *(_DWORD *)v12->Car->CarDoor_[0].AnimationFrame = a8;
      v12->Car->CarDoor_[0].doorState = a10;
      v12->Car->CarDoor_[0].PedInDoor = a8;
      *(_DWORD *)v12->Car->CarDoor_[1].AnimationFrame = unk_665948.FirstElement;
      *(_DWORD *)&v12->Car->CarDoor_[0].field_C = a9;
      LOWORD(v12->Car->Passenger_) = a6;
      *(_WORD *)&v12->Car->CarDoor_[1].field_C = *(char *)(v13 + 101);
      Car = v12->Car;
      LOWORD(v16) = gta2::Car_sub_403820((Car *)&Car->CarDoor_[0].doorState, &dword_665894);
      if ( v16 )
        *(_WORD *)&Car->CarDoor_[1].rezerv_2 = 1;
    }
    else
    {
      gta2::S63_sub_4827B0(v12);
    }
  }
}


// 0x00485260: Object::sub_485260
// IDA: Object::sub_485260
// Ghidra: ---
int gta2::Object_sub_485260(void *self, int *a2)
{
  if ( *(_DWORD *)(a2[2] + 52) != 11 )
    gta2::S56_sub_447BD0(gCheckpoint3, (SpriteS1 *)a2[1]);
  return (int)gta2::S61_sub_484DB0(gCollisionBox, (EventHandler *)a2);
}


// 0x00485290: Object::sub_485290
// IDA: Object::sub_485290
// Ghidra: ---
int * gta2::Object_sub_485290(
        Object *self,
        S900 *a2,
        int a3,
        int a4,
        int a5,
        int a6,
        SpriteS1 *a7,
        SpriteS3 *a8,
        EventHandler *a9)
{
  EventHandler *v9; // esi

  v9 = gta2::Object_sub_484E00(self, a2);
  if ( v9 )
  {
    gta2::sub_482A40(v9->SpriteS1_, a7, a8, a9);
    gta2::S63_sub_482630(v9);
  }
  return (int *)v9;
}


// 0x004852e0: Object::SpawnObject
// IDA: Object::SpawnObject
// Ghidra: ---
EventHandler * gta2::Object_SpawnObject(Object *self, int a1, int x, int y, int z, int rot)
{
  EventHandler *v6; // eax
  EventHandler *pS63; // esi

  v6 = gta2::Object_sub_484E00(self, (S900 *)a1);
  pS63 = v6;
  if ( v6 )
    gta2::S63_sub_482630(v6);
  return pS63;
}


// 0x00485320: Object::sub_485320
// IDA: Object::sub_485320
// Ghidra: ---
int * gta2::Object_sub_485320(Object *self, S900 *a2, char a3, int a4, int a5, int a6)
{
  EventHandler *pS63; // esi

  pS63 = gta2::Object_sub_484E00(self, a2);
  if ( pS63 )
  {
    gta2::S63_sub_482C00(pS63, a3);
    if ( a2 == (S900 *)279 )
      gta2::S63_sub_4827B0(pS63);
  }
  return (int *)pS63;
}


// 0x00485370: Object::sub_485370
// IDA: Object::sub_485370
// Ghidra: FUN_00485370
EventHandler * gta2::Object_sub_485370(Object *param_1,undefined4 param_2,undefined4 param_3, undefined4 param_4,undefined4 param_5,undefined4 param_6, undefined4 param_7)
{
  undefined4 in_EAX;
  EventHandler *pEVar1;
  
  pEVar1 = gta2::Object_SpawnObject(param_1,0xa5,param_2,param_3,param_4,
                               CONCAT22((short)((uint)in_EAX >> 0x10),
                                        _DAT_006657f8______S38),'\0');
  if (pEVar1 != NULL) {
    FUN_00482d60(param_5,param_6,param_7);
  }
  return pEVar1;
}


// 0x004853c0: Object::sub_4853C0
// IDA: Object::sub_4853C0
// Ghidra: FUN_004853c0
EventHandler * gta2::Object_sub_4853C0(Object *param_1,int param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7, undefined4 param_8)
{
  undefined4 in_EAX;
  EventHandler *pEVar1;
  
  pEVar1 = gta2::Object_SpawnObject(param_1,param_2,param_3,param_4,param_5,
                               CONCAT22((short)((uint)in_EAX >> 0x10),
                                        _DAT_006657f8______S38),'\0');
  if (pEVar1 != NULL) {
    FUN_00482d60(param_6,param_7,param_8);
  }
  return pEVar1;
}


// 0x00485480: Object::sub_485480
// IDA: Object::sub_485480
// Ghidra: FUN_00485480
CollisionBox * gta2::Object_sub_485480(Object *param_1,int param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6)
{
  CollisionBox *self;
  
  self = (CollisionBox *)
         gta2::Object_SpawnObject(param_1,param_2,param_3,param_4,param_5,param_6,
                             '\x01');
  if (self != NULL) {
    gta2::S63_sub_482630(self);
  }
  return self;
}


// 0x00485500: Object::sub_485500
// IDA: Object::sub_485500
// Ghidra: FUN_00485500
void gta2::Object_sub_485500(Object *param_1,int param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined2 param_6,undefined4 param_7, Ped *param_8,undefined4 param_9,int param_10)
{
  gta2::Object_sub_485180(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             param_9,param_10,'\x01');
  return;
}


// 0x00485540: Object::sub_485540
// IDA: Object::sub_485540
// Ghidra: ---
int gta2::Object_sub_485540(Object *self, int a2, int a3, int a4, int a5, int a6, int a7)
{
  EventHandler *v7; // eax
  int v8; // esi
  struct S65 *S65; // eax
  _DWORD *v10; // ecx
  int v11; // edi
  S67 *Element; // eax
  int v13; // ecx

  v7 = gta2::Object_SpawnObject(self, 113, a2, a3, a4, a5);
  v8 = (int)v7;
  if ( !v7 )
    return 0;
  S65 = v7->S65_;
  *(_BYTE *)(v8 + 28) = 1;
  if ( !S65 )
    *(_DWORD *)(v8 + 12) = gta2::S102_sub_48A6C0(gS102);
  v10 = *(_DWORD **)(v8 + 12);
  if ( !v10 )
    return 0;
  v11 = a6;
  gta2::sub_482A90(v10, a6);
  gta2::sub_48A590(*(void **)(v8 + 12), v8);
  *(_DWORD *)(*(_DWORD *)(v8 + 12) + 44) = a7;
  switch ( v11 )
  {
    case 18:
    case 19:
    case 20:
    case 22:
    case 23:
    case 24:
    case 25:
    case 32:
    case 33:
      *(_WORD *)(*(_DWORD *)(v8 + 12) + 26) = 100;
      gta2::bitShiftLeft1(&a5, 0);
      *(_DWORD *)(*(_DWORD *)(v8 + 12) + 36) = a5;
      break;
    default:
      *(_WORD *)(*(_DWORD *)(v8 + 12) + 26) = 9999;
      break;
  }
  if ( !*(_DWORD *)(v8 + 16) )
  {
    Element = gta2::S66_NextElement(unk_665780);
    v13 = *(_DWORD *)(v8 + 20);
    *(_DWORD *)(v8 + 16) = Element;
    Element->field_20 = v13;
    *(_DWORD *)(*(_DWORD *)(v8 + 16) + 12) = dword_665894;
    *(_DWORD *)(*(_DWORD *)(v8 + 16) + 16) = dword_665894;
  }
  return v8;
}


// 0x00485640: Object::sub_485640
// IDA: Object::sub_485640
// Ghidra: ---
int gta2::Object_sub_485640(Object *self, char *a2)
{
  char *v2; // ebp
  char *v3; // ebx
  char *v4; // esi
  int v5; // eax
  int v6; // eax
  EventHandler *v7; // eax
  int result; // eax
  int v9; // [esp+10h] [ebp-8h]

  v2 = a2 + 280;
  v3 = a2 + 240;
  v4 = a2 + 80;
  v9 = 20;
  do
  {
    LOWORD(v5) = gta2::Car_sub_403820((Car *)(v4 - 80), &dword_665894);
    if ( v5 )
    {
      LOWORD(v6) = gta2::Car_sub_403820((Car *)v4, &dword_665894);
      if ( v6 )
      {
        LOWORD(v6) = word_6657F8[0];
        v7 = gta2::Object_SpawnObject(
               self,
               *(unsigned __int16 *)v3,
               *((_DWORD *)v4 - 20),
               *(_DWORD *)v4,
               *((_DWORD *)v4 + 20),
               v6);
        gta2::S63_sub_45E0A0(v7, *v2);
      }
    }
    v3 += 2;
    v4 += 4;
    ++v2;
    --v9;
  }
  while ( v9 );
  result = 0;
  memset(a2, 0, 0x12Cu);
  return result;
}


// 0x00485d9d: Object::sub_485E40
// IDA: Object::sub_485E40
// Ghidra: ---
  return gta2::Object_sub_485E40(self);
}


// 0x00485e40: Object::sub_485E40
// IDA: Object::sub_485E40
// Ghidra: ---
int gta2::Object_sub_485E40(Object *self)
{
  int result; // eax
  SpriteS1 *v3; // esi
  EventHandler *pS63; // edi
  char v5; // al
  int v6; // eax
  int v7; // ecx
  int v8; // [esp+4h] [ebp-4h]

  result = (int)&self->S63[0].S65[-11];
  if ( result >= 0 )
  {
    v8 = result + 1;
    do
    {
      v3 = (SpriteS1 *)gta2::sub_4BEE30(&self->S63[0].field_14);
      pS63 = (EventHandler *)gta2::SpriteS1_sub_40FEC0(v3);
      if ( pS63->S63_1_ == (S63_1 *)10 )
      {
        if ( gta2::Game_sub_45C420(gGame, v3, dword_665894) )
        {
          v5 = gta2::S63_sub_420FF0(pS63);
          v6 = gta2::S68_sub_420F10(gScriptThread, v5);
          LOWORD(v7) = word_6657F8[0];
          gta2::Object_sub_485540(
            self,
            v3->S3_arr5031[0].PositionX,
            v3->S3_arr5031[0].PositionY,
            v3->S3_arr5031[0].PositionZ,
            v7,
            18,
            v6);
        }
      }
      gta2::S63_sub_483C40(pS63);
      result = --v8;
    }
    while ( v8 );
  }
  return result;
}


// 0x00485ed0: Object::sub_485ED0
// IDA: Object::sub_485ED0
// Ghidra: ---
char gta2::Object_sub_485ED0(Object *self)
{
  int v1; // eax
  int v3; // ecx
  int v4; // ecx
  EventHandler *v5; // eax
  Object *v6; // ecx
  int v7; // ecx
  int v8; // ecx
  EventHandler *v9; // eax
  int v10; // edx
  Object *v11; // ecx
  int v12; // ecx
  int v13; // ecx
  EventHandler *v14; // eax
  int v15; // eax
  Object *v16; // ecx
  int v17; // ecx
  int v18; // ecx
  SpriteS1 *v19; // eax
  char result; // al
  int v21; // [esp-10h] [ebp-14h] BYREF
  int v22; // [esp-Ch] [ebp-10h] BYREF
  Object *v23; // [esp-8h] [ebp-Ch] BYREF
  Object *v24; // [esp-4h] [ebp-8h]

  LOWORD(v1) = unk_665A7C.Index;
  v24 = (Object *)v1;
  v23 = self;
  gta2::bitShiftLeft1(&v23, 0);
  v22 = v3;
  gta2::bitShiftLeft1(&v22, 0);
  v21 = v4;
  gta2::bitShiftLeft1(&v21, 0);
  v5 = gta2::Object_SpawnObject(self, 166, v21, v22, (int)v23, (int)v24);
  LOBYTE(v24) = 45;
  self->field_0 = v5;
  gta2::S63_sub_447E90(v5, (char)v24);
  LOWORD(v6) = unk_665910;
  v24 = v6;
  v23 = v6;
  gta2::bitShiftLeft1(&v23, 0);
  v22 = v7;
  gta2::bitShiftLeft1(&v22, 0);
  v21 = v8;
  gta2::bitShiftLeft1(&v21, 0);
  v9 = gta2::Object_SpawnObject(self, 166, v21, v22, (int)v23, (int)v24);
  LOBYTE(v24) = 48;
  self->field_4 = v9;
  gta2::S63_sub_447E90(v9, (char)v24);
  LOWORD(v10) = unk_6659B8;
  v24 = (Object *)v10;
  v23 = v11;
  gta2::bitShiftLeft1(&v23, 0);
  v22 = v12;
  gta2::bitShiftLeft1(&v22, 0);
  v21 = v13;
  gta2::bitShiftLeft1(&v21, 0);
  v14 = gta2::Object_SpawnObject(self, 166, v21, v22, (int)v23, (int)v24);
  LOBYTE(v24) = 46;
  self->S63[0].NextElement = v14;
  gta2::S63_sub_447E90(v14, (char)v24);
  LOWORD(v15) = unk_66589C;
  v24 = (Object *)v15;
  v23 = v16;
  gta2::bitShiftLeft1(&v23, 0);
  v22 = v17;
  gta2::bitShiftLeft1(&v22, 0);
  v21 = v18;
  gta2::bitShiftLeft1(&v21, 0);
  v19 = (SpriteS1 *)gta2::Object_SpawnObject(self, 166, v21, v22, (int)v23, (int)v24);
  LOBYTE(v24) = 47;
  self->S63[0].SpriteS1 = v19;
  gta2::S63_sub_447E90((EventHandler *)v19, (char)v24);
  return result;
}


// 0x00487f50: Object::sub_487F50
// IDA: Object::sub_487F50
// Ghidra: ---
char gta2::Object_sub_487F50(Object *self)
{
  CollisionBox *pS61; // ebx
  EventHandler *pS63; // esi
  EventHandler *v3; // edi
  EventHandler *NextElement; // ebp
  EventHandler *pS63_1; // eax
  EventHandler *FirstElement; // eax

  LOBYTE(FirstElement) = gta2::Object_sub_485E40(self);
  pS61 = gCollisionBox;
  pS63 = gCollisionBox->pS63;
  v3 = 0;
  gCollisionBox->field_29174 = 0;
  if ( pS63 )
  {
    do
    {
      ++pS61->field_29174;
      NextElement = pS63->NextElement;
      LOBYTE(FirstElement) = gta2::S63_sub_487E80(pS63);
      if ( (_BYTE)FirstElement )
      {
        gta2::S63_sub_484910(pS63);
        if ( !v3 )
          goto LABEL_6;
        if ( v3->NextElement != pS63 )
        {
          v3 = 0;
LABEL_6:
          pS63_1 = pS61->pS63;
          if ( pS63_1 == pS63 )
          {
            FirstElement = pS61->FirstElement;
            pS61->pS63 = pS63->NextElement;
            pS63->NextElement = FirstElement;
            pS61->FirstElement = pS63;
          }
          else
          {
            v3 = pS61->pS63;
            if ( pS63_1->NextElement != pS63 )
            {
              do
                v3 = v3->NextElement;
              while ( v3->NextElement != pS63 );
            }
            v3->NextElement = pS63->NextElement;
            FirstElement = pS61->FirstElement;
            pS63->NextElement = pS61->FirstElement;
            pS61->FirstElement = pS63;
          }
          goto LABEL_13;
        }
        v3->NextElement = pS63->NextElement;
        FirstElement = pS61->FirstElement;
        pS63->NextElement = pS61->FirstElement;
        pS61->FirstElement = pS63;
      }
      else
      {
        v3 = pS63;
      }
LABEL_13:
      pS63 = NextElement;
    }
    while ( NextElement );
  }
  return (char)FirstElement;
}


// 0x004c0ad0: Object::SpawnObject
// IDA: Object::SpawnObject
// Ghidra: ---
  return gta2::Object_SpawnObject(gObject, 218, (int)v267, (int)v268, v269, v270);
}



