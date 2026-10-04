#include "gta2_shim.h"

// Module: other, Class: PublicTransport
// Functions: 25
// Source: unified (IDA+Ghidra)

// 0x004af0e0: PublicTransport::sub_4AF0E0
// IDA: PublicTransport::sub_4AF0E0
// Ghidra: FUN_004af0e0
char * gta2::PublicTransport_sub_4AF0E0(undefined4 param_1,int param_2,char param_3,undefined4 param_4, undefined4 param_5,byte param_6)
{
  byte bVar1;
  char *pcVar2;
  void *extraout_ECX;
  void *self;
  void *extraout_ECX_00;
  
  if (param_3 == '\0') {
    param_6 = 0xb;
  }
  else if (param_3 == '\x01') {
    param_6 = 0xc;
  }
  else if (param_3 == '\x02') {
    param_6 = 0xd;
  }
  else {
    gta2::DebugLog(0x3ee,"pubtrans.cpp",0x62);
  }
  pcVar2 = gta2::MapRelatedStruct_sub_464E70(gMapRelatedStruct,param_6);
  self = extraout_ECX;
  do {
    DAT_0066bb48 = 6;
    bVar1 = gta2::CompareStringsUpToLen(self,pcVar2 + 6,param_2);
    if (bVar1 != 0) {
      return pcVar2;
    }
    pcVar2 = gta2::MapRelatedStruct_sub_4651C0(gMapRelatedStruct);
    self = extraout_ECX_00;
  } while (pcVar2 != NULL);
  return NULL;
}


// 0x004af3d0: PublicTransport::AllocateBusSlot
// IDA: PublicTransport::AllocateBusSlot
// Ghidra: ---
Bus * gta2::PublicTransport_AllocateBusSlot(struct PublicTransport *self)
{
  unsigned __int16 index; // dx

  if ( skip_trains )
    return 0;
  index = 0;
  while ( self->BUS[index].Status )
  {
    if ( ++index >= 10u )
      return 0;
  }
  return &self->BUS[index];
}


// 0x004af420: PublicTransport::GetS82
// IDA: PublicTransport::GetS82
// Ghidra: ---
BaseCar * gta2::PublicTransport_GetS82(struct PublicTransport *self)
{
  unsigned __int16 index; // dx

  index = 0;
  while ( self->BaseCar_[index].Status )
  {
    if ( ++index >= 100u )
      return 0;
  }
  return &self->BaseCar_[index];
}


// 0x004af460: PublicTransport::sub_4AF460
// IDA: PublicTransport::sub_4AF460
// Ghidra: ---
char gta2::PublicTransport_sub_4AF460(struct PublicTransport *self, int a2)
{
  int *p_SkipTrains; // eax
  int v3; // edx

  LOBYTE(p_SkipTrains) = skip_trains;
  if ( !skip_trains )
  {
    p_SkipTrains = &self->BaseCar_.SkipTrains;
    self->BaseCar_.SkipTrains = *(_DWORD *)a2;
    self->BaseCar_.field_28 = *(_DWORD *)(a2 + 4);
    self->BaseCar_.field_2C = *(_WORD *)(a2 + 8);
    v3 = 10;
    do
    {
      if ( *(_BYTE *)p_SkipTrains )
        ++self->BaseCar_.field_2E;
      p_SkipTrains = (int *)((char *)p_SkipTrains + 1);
      --v3;
    }
    while ( v3 );
  }
  return (char)p_SkipTrains;
}


// 0x004af500: PublicTransport::sub_4AF500
// IDA: PublicTransport::sub_4AF500
// Ghidra: ---
_BYTE * gta2::PublicTransport_sub_4AF500(struct PublicTransport *self)
{
  int *p_count; // esi
  int v2; // edi
  _BYTE *result; // eax
  _BYTE *v4; // eax
  struct PublicTransport *v5; // ecx
  _BYTE *v6; // eax
  int v7; // edx
  struct PublicTransport *v8; // ecx

  p_count = &self->BaseCar_.count;
  v2 = 100;
  do
  {
    result = (_BYTE *)*(p_count - 4);
    if ( result )
    {
      if ( --result )
      {
        if ( result == (_BYTE *)1 )
        {
          v4 = gta2::PublicTransport_sub_4AF0E0(self, *p_count + 6, 0);
          v5 = (struct PublicTransport *)(*p_count + 6);
          *(p_count - 3) = (int)v4;
          v6 = gta2::PublicTransport_sub_4AF0E0(v5, (int)v5, 1);
          v7 = *p_count + 6;
          *(p_count - 2) = (int)v6;
          result = gta2::PublicTransport_sub_4AF0E0(v8, v7, 2);
          *(p_count - 1) = (int)result;
        }
        else
        {
          result = (_BYTE *)gta2::debug_log(0x3EEu, "pubtrans.cpp", 928);
        }
      }
    }
    p_count += 13;
    --v2;
  }
  while ( v2 );
  return result;
}


// 0x004af570: PublicTransport::IsThisBus
// IDA: PublicTransport::IsThisBus
// Ghidra: ---
bool gta2::PublicTransport_IsThisBus(struct PublicTransport *self, Car *pCar)
{
  struct Car *pCar1; // eax
  bool result; // al

  result = 0;
  if ( !skip_buses )
  {
    pCar1 = self->BusMetrics.Car;
    if ( pCar1 )
    {
      if ( pCar == pCar1 )
        return 1;
    }
  }
  return result;
}


// 0x004af5a0: PublicTransport::sub_4AF5A0
// IDA: PublicTransport::sub_4AF5A0
// Ghidra: ---
Car * gta2::PublicTransport_sub_4AF5A0(struct PublicTransport *self)
{
  struct Car *result; // eax

  if ( skip_buses )
    return 0;
  result = self->BusMetrics.Car;
  if ( !result || self->BusMetrics.field_48 != 13 )
    return 0;
  return result;
}


// 0x004af5c0: PublicTransport::HasReachedBusSkipLimit
// IDA: PublicTransport::HasReachedBusSkipLimit
// Ghidra: ---
bool gta2::PublicTransport_HasReachedBusSkipLimit(struct PublicTransport *self)
{
  return !skip_buses && self->BusMetrics.SkipCount >= 10;
}


// 0x004af5e0: PublicTransport::UpdateBusSkipCounter
// IDA: PublicTransport::UpdateBusSkipCounter
// Ghidra: ---
char gta2::PublicTransport_UpdateBusSkipCounter(struct PublicTransport *self)
{
  char result; // al

  result = skip_buses;
  if ( !skip_buses )
    ++self->BusMetrics.SkipCount;
  return result;
}


// 0x004af5f0: PublicTransport::sub_4AF5F0
// IDA: PublicTransport::sub_4AF5F0
// Ghidra: ---
char gta2::PublicTransport_sub_4AF5F0(struct PublicTransport *self)
{
  char result; // al

  result = skip_buses;
  if ( !skip_buses )
  {
    self->BusMetrics.SkipCount = 0;
    gta2::sub_446120(&self->BusMetrics.Car->Passenger_);
  }
  return result;
}


// 0x004af610: PublicTransport::FindCarField
// IDA: PublicTransport::FindCarField
// Ghidra: ---
void * gta2::PublicTransport_FindCarField(struct PublicTransport *self, Car *pCar)
{
  unsigned __int8 v2; // bl
  unsigned __int8 Index; // [esp+8h] [ebp-4h]

  v2 = 0;
  Index = 0;
  while ( self->BUS[Index].Car != pCar )
  {
    Index = ++v2;
    if ( v2 >= 10u )
      return 0;
  }
  return &self->BUS[Index].field_10;
}


// 0x004af660: PublicTransport::sub_4AF660
// IDA: PublicTransport::sub_4AF660
// Ghidra: ---
BaseCar * gta2::PublicTransport_sub_4AF660(struct PublicTransport *self, void *a2)
{
  struct BaseCar *result; // eax
  int Index; // edx

  result = (struct BaseCar *)self;
  Index = 0;
  while ( (void *)result->count != a2 )
  {
    ++result;
    if ( (unsigned __int16)++Index >= 100u )
      return 0;
  }
  return result;
}


// 0x004af680: PublicTransport::sub_4AF680
// IDA: PublicTransport::sub_4AF680
// Ghidra: ---
_DWORD * gta2::PublicTransport_sub_4AF680(struct PublicTransport *self, Car *pCar)
{
  _DWORD *result; // eax
  unsigned __int8 v4; // cl
  unsigned __int8 v6; // bl
  unsigned __int8 v7; // dl
  unsigned __int8 v8; // [esp+4h] [ebp-4h]
  unsigned __int8 pCara; // [esp+Ch] [ebp+4h]

  if ( skip_trains )
    return 0;
  v4 = 0;
  v8 = 0;
  while ( 1 )
  {
    result = &self->BUS[v8].Car1;
    if ( self->BUS[v8].Car == pCar )
      return result;
    v6 = self->BUS[v8].field_43;
    v7 = 0;
    pCara = 0;
    if ( v6 )
    {
      while ( (struct Car *)result[pCara + 4] != pCar )
      {
        pCara = ++v7;
        if ( v7 >= v6 )
          goto LABEL_8;
      }
      return result;
    }
LABEL_8:
    v8 = ++v4;
    if ( v4 >= 0xAu )
      return 0;
  }
}


// 0x004af700: PublicTransport::sub_4AF700
// IDA: PublicTransport::sub_4AF700
// Ghidra: ---
_BYTE * gta2::PublicTransport_sub_4AF700(struct PublicTransport *self, Car *pCar)
{
  _BYTE *result; // eax
  unsigned __int8 v4; // cl
  unsigned __int8 v6; // bl
  unsigned __int8 v7; // dl
  unsigned __int8 v8; // [esp+4h] [ebp-4h]
  unsigned __int8 pCara; // [esp+Ch] [ebp+4h]

  if ( skip_trains )
    return 0;
  v4 = 0;
  v8 = 0;
  while ( 1 )
  {
    v6 = 0;
    pCara = 0;
    v7 = self->BUS[v8].field_43;
    result = &self->BUS[v8].Car1;
    if ( v7 )
      break;
LABEL_7:
    v8 = ++v4;
    if ( v4 >= 0xAu )
      return 0;
  }
  while ( *(Car **)&result[4 * pCara + 16] != pCar )
  {
    pCara = ++v6;
    if ( v6 >= v7 )
      goto LABEL_7;
  }
  return result;
}


// 0x004af780: PublicTransport::PublicTransport
// IDA: PublicTransport::PublicTransport
// Ghidra: ---
PublicTransport * gta2::PublicTransport_PublicTransport(struct PublicTransport *self)
{
  gta2::Construct(self, 52, 100, S82::S82, S82::S82_Des);
  gta2::Construct(self->BUS, 0x58, 10, S83::S83, S83::S83_des);
  gta2::S83_S83(&self->BusMetrics);
  return self;
}


// 0x004af7f0: PublicTransport::sub_4AF7F0
// IDA: PublicTransport::sub_4AF7F0
// Ghidra: ---
int gta2::PublicTransport_sub_4AF7F0(struct PublicTransport *self)
{
  gta2::S83_S83_des(&self->BusMetrics.Car1);
  gta2::Construct_0(self->BUS, 88, 10, S83::S83_des);
  return gta2::Construct_0(self, 52, 100, S82::S82_Des);
}


// 0x004afe20: PublicTransport::sub_4AFE20
// IDA: PublicTransport::sub_4AFE20
// Ghidra: ---
char gta2::PublicTransport_sub_4AFE20(struct PublicTransport *self)
{
  char result; // al
  struct PublicTransport *pPublicTransport1; // esi
  int *i; // edi
  int v4; // eax
  char v5; // bl
  struct Bus *BusSlot; // esi
  int v7; // ebp
  void *v8; // ecx
  void *v9; // ecx
  int v10; // ebp
  int v11; // ebx
  unsigned __int8 v12; // dl
  struct S202 *v13; // eax
  struct Tango *v14; // eax
  unsigned __int8 v15; // al
  struct S202 *v16; // eax
  struct S202 **v17; // ebx
  CarModel *v18; // eax
  struct Car *v19; // eax
  int v20; // ebx
  unsigned __int8 v21; // cl
  struct S202 *v22; // eax
  struct SpriteS1 *v23; // eax
  struct Tango *v24; // eax
  struct SpriteS1 *v25; // eax
  unsigned __int8 v26; // dl
  struct S202 *v27; // eax
  struct SpriteS1 *v28; // eax
  int v29; // ebp
  unsigned __int8 v30; // al
  struct S202 *v31; // eax
  struct S202 **v32; // ebx
  struct S202 **v33; // eax
  __int16 v34; // dx
  struct Car *v35; // eax
  void *v36; // ecx
  int v37; // ebp
  int v38; // ebx
  struct Tango *v39; // eax
  unsigned __int8 v40; // al
  struct Player *v41; // eax
  unsigned __int8 v42; // al
  struct S202 *v43; // eax
  struct S202 **v44; // ebx
  CarModel *v45; // eax
  struct Car *v46; // eax
  int v47; // ebx
  struct Tango *v48; // eax
  struct SpriteS1 *v49; // eax
  unsigned __int8 v50; // dl
  struct Player *v51; // eax
  struct SpriteS1 *v52; // eax
  struct SpriteS1 *v53; // eax
  unsigned __int8 v54; // dl
  struct S202 *v55; // eax
  struct SpriteS1 *v56; // eax
  int v57; // ebp
  unsigned __int8 v58; // cl
  struct S202 **v59; // eax
  struct S202 *v60; // eax
  void *v61; // ecx
  int v62; // ebp
  int v63; // ebx
  unsigned __int8 v64; // al
  struct S202 *v65; // eax
  struct Tango *v66; // eax
  unsigned __int8 v67; // al
  struct Player *v68; // eax
  struct S202 **v69; // ebx
  CarModel *v70; // eax
  struct Car *v71; // eax
  int v72; // ebx
  unsigned __int8 v73; // cl
  struct S202 *v74; // eax
  struct SpriteS1 *v75; // eax
  struct Tango *v76; // eax
  struct SpriteS1 *v77; // eax
  unsigned __int8 v78; // dl
  struct Player *v79; // eax
  struct SpriteS1 *v80; // eax
  int v81; // ebp
  unsigned __int8 v82; // al
  struct S202 *v83; // eax
  int v84; // ebp
  int v85; // ebx
  struct Tango *v86; // eax
  unsigned __int8 v87; // al
  struct S202 *v88; // eax
  unsigned __int8 v89; // al
  struct S202 *v90; // eax
  struct S202 **v91; // ebx
  CarModel *v92; // eax
  struct Car *v93; // eax
  int v94; // ebx
  struct Tango *v95; // eax
  struct SpriteS1 *v96; // eax
  unsigned __int8 v97; // dl
  struct S202 *v98; // eax
  struct SpriteS1 *v99; // eax
  struct SpriteS1 *v100; // eax
  unsigned __int8 v101; // dl
  struct S202 *v102; // eax
  struct SpriteS1 *v103; // eax
  int v104; // ebp
  unsigned __int8 v105; // cl
  struct S202 **v106; // eax
  struct S202 *v107; // eax
  int v108; // eax
  struct PublicTransport *v109; // ecx
  int v110; // eax
  struct SpriteS1 *v111; // ecx
  struct PublicTransport *v112; // ecx
  struct SpriteS1 *v113; // ecx
  struct PublicTransport *v114; // ecx
  struct PublicTransport *v115; // eax
  struct PublicTransport *v116; // ebp
  struct SpriteS1 *v117; // ecx
  int v118; // ecx
  int v119; // ebp
  int v120; // ebp
  struct Car *Car; // ecx
  struct PublicTransport *pPublicTransport; // [esp-18h] [ebp-13Ch] BYREF
  struct S202 ***p_pPlayer; // [esp-14h] [ebp-138h] BYREF
  struct PublicTransport *v124; // [esp-10h] [ebp-134h] BYREF
  int v125; // [esp-Ch] [ebp-130h] BYREF
  struct SpriteS1 *v126; // [esp-8h] [ebp-12Ch] BYREF
  int v127; // [esp-4h] [ebp-128h]
  int v128; // [esp+7h] [ebp-11Dh]
  struct S202 **v129; // [esp+Ch] [ebp-118h] BYREF
  int v130; // [esp+10h] [ebp-114h] BYREF
  struct S202 **v131; // [esp+14h] [ebp-110h] BYREF
  int v132; // [esp+18h] [ebp-10Ch] BYREF
  struct PublicTransport *v133; // [esp+1Ch] [ebp-108h] BYREF
  int v134; // [esp+20h] [ebp-104h] BYREF
  int v135; // [esp+24h] [ebp-100h]
  int v136; // [esp+28h] [ebp-FCh] BYREF
  int v137; // [esp+2Ch] [ebp-F8h] BYREF
  S202 v138; // [esp+30h] [ebp-F4h] BYREF
  int v139; // [esp+50h] [ebp-D4h] BYREF
  S202 v140; // [esp+54h] [ebp-D0h] BYREF
  int v141; // [esp+74h] [ebp-B0h] BYREF
  S202 pS202; // [esp+78h] [ebp-ACh] BYREF
  int v143; // [esp+98h] [ebp-8Ch] BYREF
  S202 v144; // [esp+9Ch] [ebp-88h] BYREF
  int v145; // [esp+BCh] [ebp-68h] BYREF
  int v146; // [esp+C0h] [ebp-64h] BYREF
  S202 v147; // [esp+C4h] [ebp-60h] BYREF
  int v148; // [esp+E4h] [ebp-40h] BYREF
  S202 v149; // [esp+E8h] [ebp-3Ch] BYREF
  int v150; // [esp+108h] [ebp-1Ch] BYREF
  char v151; // [esp+110h] [ebp-14h] BYREF
  char v152; // [esp+118h] [ebp-Ch] BYREF
  int v153; // [esp+120h] [ebp-4h] BYREF

  result = skip_trains;
  pPublicTransport1 = self;
  pPublicTransport = self;
  if ( !skip_trains )
  {
    for ( i = &self->BaseCar_.count; ; i += 13 )
    {
      v4 = *(i - 4);
      v5 = *((_BYTE *)i + 30);
      if ( v4 )
      {
        if ( v5 && v4 == 2 )
          break;
      }
LABEL_55:
      result = --v137;
      if ( !v137 )
        return result;
    }
    if ( !*i )
      gta2::debug_log(0x8Fu, "pubtrans.cpp", 734);
    if ( !*(i - 3) )
      gta2::debug_log(0x7E5u, "pubtrans.cpp", 738);
    if ( !*(i - 2) )
      gta2::debug_log(0x7E6u, "pubtrans.cpp", 740);
    if ( !*(i - 1) )
      gta2::debug_log(0x7E7u, "pubtrans.cpp", 742);
    BusSlot = gta2::PublicTransport_AllocateBusSlot(pPublicTransport1);
    if ( !BusSlot )
      gta2::debug_log(0x90u, "pubtrans.cpp", 746);
    BusSlot->Status = 2;
    v7 = gta2::MapRelatedStruct_sub_463570(
           gMapRelatedStruct,
           *(unsigned __int8 *)(*(i - 1) + 1),
           *(unsigned __int8 *)(*(i - 1) + 2),
           &v133);
    if ( sub_4AF030(v8, 4, v7) )
    {
      LOBYTE(v128) = 0;
      v132 = v5;
      if ( v5 > 0 )
      {
        v10 = 0;
        do
        {
          v11 = *(i - 1);
          v130 = unk_66BDBC;
          v12 = *(_BYTE *)(v11 + 2);
          v124 = (struct PublicTransport *)&v130;
          p_pPlayer = (S202 ***)&pS202.field_18;
          gta2::S202_sub_40CE30(&v138, v12);
          v131 = (S202 **)gta2::S202_sub_401B20(v13, (struct SpriteS1 *)p_pPlayer, v124);
          v124 = (struct PublicTransport *)&dword_66BE74;
          p_pPlayer = (S202 ***)&v149.field_10;
          v130 = v10 + 1;
          LOWORD(v14) = gta2::bitShiftLeft1(&v138.CarSystemManager, v10 + 1);
          v124 = (struct PublicTransport *)gta2::Radar_AddBlip(v14, (struct SpriteS1 *)p_pPlayer, v124);
          v15 = *(_BYTE *)(v11 + 1);
          p_pPlayer = (S202 ***)&v144.field_C;
          gta2::S202_sub_40CE30((struct S202 *)&v138.field_10, v15);
          v17 = (S202 **)gta2::S202_sub_401B20(v16, (struct SpriteS1 *)p_pPlayer, v124);
          v18 = (CarModel *)gta2::sub_4AF170((_BYTE *)i - 16, v128);
          v19 = gta2::CarSystemManager_sub_426E40(gCarSystemManager, *v17, *v131, unk_66BC4C, v18);
          *((_DWORD *)&BusSlot->field_10 + v10) = v19;
          if ( !v19 )
          {
            v20 = *(i - 1);
            v131 = (S202 **)unk_66BDBC;
            v124 = v133;
            v21 = *(_BYTE *)(v20 + 2);
            p_pPlayer = &v131;
            pPublicTransport = (struct PublicTransport *)&v147.field_1C;
            gta2::S202_sub_40CE30((struct S202 *)&v138.field_18, v21);
            v23 = gta2::S202_sub_401B20(v22, (struct SpriteS1 *)pPublicTransport, (struct PublicTransport *)p_pPlayer);
            p_pPlayer = (S202 ***)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v23);
            pPublicTransport = (struct PublicTransport *)&dword_66BE74;
            LOWORD(v24) = gta2::bitShiftLeft1(&v139, v130);
            v25 = gta2::Radar_AddBlip(v24, (struct SpriteS1 *)&v144.pPlayer, pPublicTransport);
            v26 = *(_BYTE *)(v20 + 1);
            pPublicTransport = (struct PublicTransport *)v25;
            gta2::S202_sub_40CE30((struct S202 *)&v140.S202, v26);
            v28 = gta2::S202_sub_401B20(v27, (struct SpriteS1 *)&v150, pPublicTransport);
            pPublicTransport = (struct PublicTransport *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v28);
            gta2::debug_log(0xBC9u, "pubtrans.cpp", 761);
          }
          ++HIBYTE(v130);
          v10 = HIBYTE(v130);
        }
        while ( HIBYTE(v130) < v135 );
      }
      v29 = *(i - 1);
      v134 = unk_66BDBC;
      v30 = *(_BYTE *)(v29 + 2);
      v127 = (int)&v134;
      v126 = (struct SpriteS1 *)&v147;
      gta2::S202_sub_40CE30((struct S202 *)&v140.field_18, v30);
      v32 = (S202 **)gta2::S202_sub_401B20(v31, v126, (struct PublicTransport *)v127);
      gta2::S202_sub_40CE30((struct S202 *)&v149.field_C, *(_BYTE *)(v29 + 1));
      v34 = unk_66BC4C;
    }
    else if ( sub_4AF030(v9, 2, v7) )
    {
      LOBYTE(v128) = 0;
      v132 = v5;
      if ( v5 > 0 )
      {
        v37 = 0;
        do
        {
          v38 = *(i - 1);
          v131 = (S202 **)unk_66BDBC;
          v124 = (struct PublicTransport *)&dword_66BCD4;
          p_pPlayer = (S202 ***)&v140.pPlayer;
          v130 = v37 + 1;
          LOWORD(v39) = gta2::bitShiftLeft1(&v146, v37 + 1);
          v124 = (struct PublicTransport *)gta2::Radar_AddBlip(v39, (struct SpriteS1 *)p_pPlayer, v124);
          v40 = *(_BYTE *)(v38 + 2);
          p_pPlayer = (S202 ***)&v140.field_1C;
          gta2::S202_sub_40CE30((struct S202 *)&v149.field_18, v40);
          v129 = (S202 **)gta2::Player_sub_401B40(v41, (struct S202 *)p_pPlayer, (int)v124);
          v42 = *(_BYTE *)(v38 + 1);
          v124 = (struct PublicTransport *)&v131;
          p_pPlayer = (S202 ***)&pS202;
          gta2::S202_sub_40CE30((struct S202 *)&v147.S202, v42);
          v44 = (S202 **)gta2::S202_sub_401B20(v43, (struct SpriteS1 *)p_pPlayer, v124);
          v45 = (CarModel *)gta2::sub_4AF170((_BYTE *)i - 16, v128);
          v46 = gta2::CarSystemManager_sub_426E40(gCarSystemManager, *v44, *v129, unk_66BD10, v45);
          *((_DWORD *)&BusSlot->field_10 + v37) = v46;
          if ( !v46 )
          {
            v47 = *(i - 1);
            v129 = (S202 **)unk_66BDBC;
            v124 = v133;
            p_pPlayer = (S202 ***)&dword_66BCD4;
            pPublicTransport = (struct PublicTransport *)&pS202.CarSystemManager;
            LOWORD(v48) = gta2::bitShiftLeft1(&v149.CarSystemManager, v130);
            v49 = gta2::Radar_AddBlip(v48, (struct SpriteS1 *)pPublicTransport, (struct PublicTransport *)p_pPlayer);
            v50 = *(_BYTE *)(v47 + 2);
            p_pPlayer = (S202 ***)v49;
            pPublicTransport = (struct PublicTransport *)&pS202.field_10;
            gta2::S202_sub_40CE30((struct S202 *)&v147.field_C, v50);
            v52 = gta2::Player_sub_401B40(v51, (struct S202 *)pPublicTransport, (int)p_pPlayer);
            v53 = (struct SpriteS1 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v52);
            v54 = *(_BYTE *)(v47 + 1);
            p_pPlayer = (S202 ***)v53;
            pPublicTransport = (struct PublicTransport *)&v129;
            gta2::S202_sub_40CE30((struct S202 *)&v151, v54);
            v56 = gta2::S202_sub_401B20(v55, (struct SpriteS1 *)&v136, pPublicTransport);
            pPublicTransport = (struct PublicTransport *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v56);
            gta2::debug_log(0xBC9u, "pubtrans.cpp", 773);
          }
          ++HIBYTE(v130);
          v37 = HIBYTE(v130);
        }
        while ( HIBYTE(v130) < v135 );
      }
      v57 = *(i - 1);
      v132 = unk_66BDBC;
      gta2::S202_sub_40CE30((struct S202 *)&v144.CarSystemManager, *(_BYTE *)(v57 + 2));
      v58 = *(_BYTE *)(v57 + 1);
      v32 = v59;
      v127 = (int)&v132;
      v126 = (struct SpriteS1 *)&v148;
      gta2::S202_sub_40CE30((struct S202 *)&v144.field_10, v58);
      v33 = (S202 **)gta2::S202_sub_401B20(v60, v126, (struct PublicTransport *)v127);
      v34 = unk_66BD10;
    }
    else if ( sub_4AF030(v36, 3, v7) )
    {
      LOBYTE(v128) = 0;
      v132 = v5;
      if ( v5 > 0 )
      {
        v62 = 0;
        do
        {
          v63 = *(i - 1);
          v129 = (S202 **)unk_66BDBC;
          v64 = *(_BYTE *)(v63 + 2);
          v124 = (struct PublicTransport *)&v129;
          p_pPlayer = (S202 ***)&v137;
          gta2::S202_sub_40CE30((struct S202 *)&v138.S202, v64);
          v129 = (S202 **)gta2::S202_sub_401B20(v65, (struct SpriteS1 *)p_pPlayer, v124);
          v124 = (struct PublicTransport *)&dword_66BE74;
          p_pPlayer = (S202 ***)&v138.field_C;
          v130 = v62 + 1;
          LOWORD(v66) = gta2::bitShiftLeft1(&v138.pPlayer, v62 + 1);
          v124 = (struct PublicTransport *)gta2::Radar_AddBlip(v66, (struct SpriteS1 *)p_pPlayer, v124);
          v67 = *(_BYTE *)(v63 + 1);
          p_pPlayer = (S202 ***)&v138.field_1C;
          gta2::S202_sub_40CE30(&v140, v67);
          v69 = (S202 **)gta2::Player_sub_401B40(v68, (struct S202 *)p_pPlayer, (int)v124);
          v70 = (CarModel *)gta2::sub_4AF170((_BYTE *)i - 16, v128);
          v71 = gta2::CarSystemManager_sub_426E40(gCarSystemManager, *v69, *v129, unk_66BC4C, v70);
          *((_DWORD *)&BusSlot->field_10 + v62) = v71;
          if ( !v71 )
          {
            v72 = *(i - 1);
            v129 = (S202 **)unk_66BDBC;
            v124 = v133;
            v73 = *(_BYTE *)(v72 + 2);
            p_pPlayer = &v129;
            pPublicTransport = (struct PublicTransport *)&v140.CarSystemManager;
            gta2::S202_sub_40CE30((struct S202 *)&v140.field_10, v73);
            v75 = gta2::S202_sub_401B20(v74, (struct SpriteS1 *)pPublicTransport, (struct PublicTransport *)p_pPlayer);
            p_pPlayer = (S202 ***)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v75);
            pPublicTransport = (struct PublicTransport *)&dword_66BE74;
            LOWORD(v76) = gta2::bitShiftLeft1(&v141, v130);
            v77 = gta2::Radar_AddBlip(v76, (struct SpriteS1 *)&v140.field_18, pPublicTransport);
            v78 = *(_BYTE *)(v72 + 1);
            pPublicTransport = (struct PublicTransport *)v77;
            gta2::S202_sub_40CE30((struct S202 *)&pS202.field_C, v78);
            v80 = gta2::Player_sub_401B40(v79, (struct S202 *)&pS202.S202, (int)pPublicTransport);
            pPublicTransport = (struct PublicTransport *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v80);
            gta2::debug_log(0xBC9u, "pubtrans.cpp", 785);
          }
          ++HIBYTE(v130);
          v62 = HIBYTE(v130);
        }
        while ( HIBYTE(v130) < v135 );
      }
      v81 = *(i - 1);
      v132 = unk_66BDBC;
      v82 = *(_BYTE *)(v81 + 2);
      v127 = (int)&v132;
      v126 = (struct SpriteS1 *)&v143;
      gta2::S202_sub_40CE30((struct S202 *)&v144.S202, v82);
      v32 = (S202 **)gta2::S202_sub_401B20(v83, v126, (struct PublicTransport *)v127);
      gta2::S202_sub_40CE30((struct S202 *)&v144.field_C, *(_BYTE *)(v81 + 1));
      v34 = unk_66BE30;
    }
    else
    {
      if ( !sub_4AF030(v61, 1, v7) )
      {
        v108 = *(i - 1);
        v124 = v133;
        v109 = (struct PublicTransport *)*(unsigned __int8 *)(v108 + 1);
        p_pPlayer = (S202 ***)*(unsigned __int8 *)(v108 + 2);
        pPublicTransport = v109;
        gta2::debug_log(0xBC8u, "pubtrans.cpp", 802);
        goto LABEL_46;
      }
      LOBYTE(v128) = 0;
      v132 = v5;
      if ( v5 > 0 )
      {
        v84 = 0;
        do
        {
          v85 = *(i - 1);
          v129 = (S202 **)unk_66BDBC;
          v124 = (struct PublicTransport *)&dword_66BCD4;
          p_pPlayer = (S202 ***)&v144.CarSystemManager;
          v130 = v84 + 1;
          LOWORD(v86) = gta2::bitShiftLeft1(&v144.field_10, v84 + 1);
          v124 = (struct PublicTransport *)gta2::Radar_AddBlip(v86, (struct SpriteS1 *)p_pPlayer, v124);
          v87 = *(_BYTE *)(v85 + 2);
          p_pPlayer = (S202 ***)&v144.field_18;
          gta2::S202_sub_40CE30((struct S202 *)&v145, v87);
          v131 = (S202 **)gta2::S202_sub_401B20(v88, (struct SpriteS1 *)p_pPlayer, v124);
          v89 = *(_BYTE *)(v85 + 1);
          v124 = (struct PublicTransport *)&v129;
          p_pPlayer = (S202 ***)&v147;
          gta2::S202_sub_40CE30((struct S202 *)&v147.CarSystemManager, v89);
          v91 = (S202 **)gta2::S202_sub_401B20(v90, (struct SpriteS1 *)p_pPlayer, v124);
          v92 = (CarModel *)gta2::sub_4AF170((_BYTE *)i - 16, v128);
          v93 = gta2::CarSystemManager_sub_426E40(gCarSystemManager, *v91, *v131, unk_66BD74, v92);
          *((_DWORD *)&BusSlot->field_10 + v84) = v93;
          if ( !v93 )
          {
            v94 = *(i - 1);
            v129 = (S202 **)unk_66BDBC;
            v124 = v133;
            p_pPlayer = (S202 ***)&dword_66BCD4;
            pPublicTransport = (struct PublicTransport *)&v147.field_10;
            LOWORD(v95) = gta2::bitShiftLeft1(&v147.field_18, v130);
            v96 = gta2::Radar_AddBlip(v95, (struct SpriteS1 *)pPublicTransport, (struct PublicTransport *)p_pPlayer);
            v97 = *(_BYTE *)(v94 + 2);
            p_pPlayer = (S202 ***)v96;
            pPublicTransport = (struct PublicTransport *)&v148;
            gta2::S202_sub_40CE30((struct S202 *)&v149.S202, v97);
            v99 = gta2::S202_sub_401B20(v98, (struct SpriteS1 *)pPublicTransport, (struct PublicTransport *)p_pPlayer);
            v100 = (struct SpriteS1 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v99);
            v101 = *(_BYTE *)(v94 + 1);
            p_pPlayer = (S202 ***)v100;
            pPublicTransport = (struct PublicTransport *)&v129;
            gta2::S202_sub_40CE30((struct S202 *)&v149.pPlayer, v101);
            v103 = gta2::S202_sub_401B20(v102, (struct SpriteS1 *)&v149.field_C, pPublicTransport);
            pPublicTransport = (struct PublicTransport *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v103);
            gta2::debug_log(0xBC9u, "pubtrans.cpp", 796);
          }
          ++HIBYTE(v130);
          v84 = HIBYTE(v130);
        }
        while ( HIBYTE(v130) < v135 );
      }
      v104 = *(i - 1);
      v132 = unk_66BDBC;
      gta2::S202_sub_40CE30((struct S202 *)&v151, *(_BYTE *)(v104 + 2));
      v105 = *(_BYTE *)(v104 + 1);
      v32 = v106;
      v127 = (int)&v132;
      v126 = (struct SpriteS1 *)&v152;
      gta2::S202_sub_40CE30((struct S202 *)&v153, v105);
      v33 = (S202 **)gta2::S202_sub_401B20(v107, v126, (struct PublicTransport *)v127);
      v34 = unk_66BD74;
    }
    v35 = gta2::CarSystemManager_sub_426E40(gCarSystemManager, *v33, *v32, v34, (CarModel *)0x3C);
    v5 = HIBYTE(v131);
    BusSlot->Car = v35;
LABEL_46:
    BusSlot->field_43 = v5;
    HIBYTE(v130) = 0;
    if ( v5 > 0 )
    {
      v110 = 0;
      do
      {
        gta2::CarsPrefabs_sub_420F30(gCarsPrefabs, *((Car **)&BusSlot->field_10 + v110));
        ++HIBYTE(v130);
        v110 = HIBYTE(v130);
      }
      while ( HIBYTE(v130) < v5 );
    }
    gta2::Car_CarMakeDriveable2(BusSlot->Car);
    gta2::EngineStruct_MakeDriveable3(BusSlot->Car->EngineStruct_, BusSlot->Car);
    gta2::Car_CarPutDummyDriverIn(BusSlot->Car);
    gta2::Car_CarMakeDriveable1(BusSlot->Car, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
    v127 = 255;
    v126 = v111;
    gta2::bitShiftLeft1(&v126, 3);
    v125 = 16744448;
    v124 = v112;
    gta2::bitShiftLeft1(&v124, 2);
    p_pPlayer = (S202 ***)v113;
    gta2::bitShiftLeft1(&p_pPlayer, 138);
    pPublicTransport = v114;
    gta2::bitShiftLeft1(&pPublicTransport, 94);
    v115 = (struct PublicTransport *)gta2::Object_sub_485370(
                                gObject,
                                (int)pPublicTransport,
                                (int)p_pPlayer,
                                (int)v124,
                                v125,
                                (int)v126,
                                v127);
    v116 = v115;
    LOWORD(v115) = unk_66BD10;
    v127 = (int)v115;
    v126 = v117;
    gta2::bitShiftLeft1(&v126, 2);
    v125 = v118;
    gta2::bitShiftLeft1(&v125, 0);
    gta2::Car_sub_4BED90(BusSlot->Car, v116->BaseCar_.field_4, v125, (int)v126, v127);
    gta2::Car_SetLocksDoor_4(BusSlot->Car);
    HIBYTE(v130) = 0;
    if ( v5 > 0 )
    {
      v119 = 0;
      do
      {
        gta2::Car_CarPutDummyDriverIn(*((Car **)&BusSlot->field_10 + v119));
        gta2::Car_CarMakeDriveable1(
          *((Car **)&BusSlot->field_10 + v119),
          SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
        gta2::Car_CarMakeDriveable4(*((Car **)&BusSlot->field_10 + v119));
        gta2::Car_ENGINE_ON(*((Car **)&BusSlot->field_10 + v119));
        v120 = *((_DWORD *)&BusSlot->field_10 + v119);
        if ( *(_DWORD *)(v120 + 132) == 61 )
          gta2::Car_SetLocksDoor_4((struct Car *)v120);
        ++HIBYTE(v130);
        v119 = HIBYTE(v130);
      }
      while ( HIBYTE(v130) < v5 );
    }
    Car = BusSlot->Car;
    BusSlot->field_44 = 0;
    BusSlot->field_48 = 4;
    BusSlot->field_4C = (int)(i - 4);
    BusSlot->SkipCount = 6;
    BusSlot->field_0 = *((_BYTE *)i + 31);
    gta2::Car_CarMakeDummy(Car);
    gta2::Car_sub_4222F0(BusSlot->Car);
    i[2] = (int)BusSlot;
    pPublicTransport1 = (struct PublicTransport *)v138.field_0;
    i[1] = 2;
    i[3] = 1;
    goto LABEL_55;
  }
  return result;
}


// 0x004b08a0: PublicTransport::sub_4B08A0
// IDA: PublicTransport::sub_4B08A0
// Ghidra: ---
_BYTE * gta2::PublicTransport_sub_4B08A0(struct PublicTransport *self)
{
  unsigned __int8 v1; // bl
  int v2; // ebp
  char *i; // esi
  struct BaseCar *S82; // eax
  char v5; // cl
  char *v6; // ebp
  struct BaseCar *v7; // esi
  char v8; // cl
  char *v9; // eax
  int count; // edi
  int v11; // eax
  int v12; // esi
  int v13; // eax
  unsigned __int8 SMG; // di
  struct MapRelatedStruct *pMapRelatedStruct; // esi
  unsigned __int8 index; // bl
  unsigned __int8 v17; // al
  char v18; // al
  unsigned __int8 v19; // al
  char v20; // al
  int v21; // eax
  struct S202 *v22; // eax
  int *v23; // esi
  int *v24; // edi
  int *v25; // eax
  int v26; // edx
  int v28; // [esp-8h] [ebp-54h]
  int v29; // [esp-8h] [ebp-54h]
  char v30; // [esp-8h] [ebp-54h]
  unsigned __int8 v31; // [esp-8h] [ebp-54h]
  char v32; // [esp-8h] [ebp-54h]
  unsigned __int8 v33; // [esp-8h] [ebp-54h]
  int v34; // [esp-8h] [ebp-54h]
  char *str1; // [esp-4h] [ebp-50h]
  unsigned __int8 v36; // [esp-4h] [ebp-50h]
  unsigned __int8 v37; // [esp-4h] [ebp-50h]
  struct PublicTransport *Car; // [esp+10h] [ebp-3Ch] BYREF
  Weapon v39; // [esp+14h] [ebp-38h] BYREF
  char str[8]; // [esp+44h] [ebp-8h] BYREF

  v39.field_C = (int)self;
  unk_66BB4A = 0;
  dword_66BB4C = 0;
  if ( !skip_trains )
  {
    v1 = 0;
    v2 = 0;
    do
    {
      switch ( v2 )
      {
        case 0:
          strcpy(str, "trak0");
          break;
        case 1:
          str1 = "trak1";
          goto LABEL_9;
        case 2:
          strcpy(str, "trak2");
          break;
        case 3:
          strcpy(str, "trak3");
          break;
        case 4:
          str1 = "trak4";
LABEL_9:
          strcpy(str, str1);
          break;
        default:
          break;
      }
      gS82[0] = 0;
      gS82[1] = 0;
      gS82[2] = 0;
      gS82[3] = 0;
      gS82[4] = 0;
      gCount = 0;
      for ( i = gta2::MapRelatedStruct_sub_464E70(gMapRelatedStruct, 6); i; i = gta2::MapRelatedStruct_sub_4651C0(gMapRelatedStruct) )
      {
        unk_66BB48 = 5;
        if ( gta2::CompareStringsUpToLen(str, i + 6) )
        {
          S82 = gta2::PublicTransport_GetS82(gPublicTransport);
          S82->field = 2;
          S82->Status = 1;
          S82->field_1C = 1;
          v5 = unk_66BB49;
          S82->count = (int)i;
          S82->field_18 = 0;
          S82->field_2F = v1;
          unk_66BB49 = v5 + 1;
          switch ( i[11] )
          {
            case '0':
              gS82[0] = S82;
              break;
            case '1':
              gS82[1] = S82;
              break;
            case '2':
              gS82[2] = S82;
              break;
            case '3':
              gS82[3] = S82;
              break;
            case '4':
              gS82[4] = S82;
              break;
            default:
              break;
          }
          ++gCount;
        }
      }
      if ( gCount )
        gta2::sub_4AF4A0((void *)v39.field_C);
      ++v1;
      ++v2;
    }
    while ( v1 < 5u );
  }
  if ( !skip_buses )
  {
    v6 = gta2::MapRelatedStruct_sub_464E70(gMapRelatedStruct, 7);
    while ( v6 )
    {
      v7 = gta2::PublicTransport_GetS82(gPublicTransport);
      v8 = unk_66BB49 + 1;
      v7->field = 1;
      v7->Status = 1;
      v7->field_1C = 1;
      v7->count = (int)v6;
      v7->field_18 = 0;
      unk_66BB49 = v8;
      v9 = gta2::MapRelatedStruct_sub_4651C0(gMapRelatedStruct);
      count = v7->count;
      v6 = v9;
      gta2::S202_sub_40CE30((struct S202 *)&v39.short, *(_BYTE *)(count + 1));
      v36 = *(_BYTE *)(count + 2);
      *(_DWORD *)&v39.Ammo = *(_DWORD *)&v39.short;
      gta2::S202_sub_40CE30((struct S202 *)&v39.Car, v36);
      Car = (struct PublicTransport *)v39.Car;
      v28 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&Car);
      v11 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v39);
      gta2::MapRelatedStruct_FindMaxZForTile(gMapRelatedStruct, v11, v28, &v39.SMG);
      v12 = v7->count;
      gta2::S202_sub_40CE30((struct S202 *)&v39.NextWeapon, *(_BYTE *)(v12 + 1));
      v37 = *(_BYTE *)(v12 + 2);
      *(_DWORD *)&v39.Ammo = v39.NextWeapon;
      gta2::S202_sub_40CE30((struct S202 *)&v39.TypeWeapon, v37);
      Car = (struct PublicTransport *)v39.TypeWeapon;
      v29 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&Car);
      v13 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v39);
      gta2::MapRelatedStruct_FindMaxZForTile(gMapRelatedStruct, v13, v29, &v39.SMG);
      SMG = v39.SMG;
      pMapRelatedStruct = gMapRelatedStruct;
      index = 0;
      LOBYTE(v39.field_8) = 0;
      do
      {
        switch ( LOBYTE(v39.field_8) )
        {
          case 0:
            v30 = gta2::Weapon_sub_41C1E0((struct Weapon *)&Car);
            v17 = gta2::Weapon_sub_41C1E0(&v39);
            if ( gta2::MapRelatedStruct_sub_433470(pMapRelatedStruct, v17, v30, SMG) )
            {
              gta2::Weapon_UseAmmo((struct Weapon *)&Car, &unk_66BBE8);
              goto LABEL_35;
            }
            break;
          case 1:
            v31 = gta2::Weapon_sub_41C1E0((struct Weapon *)&Car);
            v18 = gta2::Weapon_sub_41C1E0(&v39);
            if ( gta2::MapRelatedStruct_sub_4334A0(pMapRelatedStruct, v18, v31, SMG) )
            {
              gta2::Player_sub_40E530((struct Player *)&v39, &unk_66BBE8);
              goto LABEL_35;
            }
            break;
          case 2:
            v32 = gta2::Weapon_sub_41C1E0((struct Weapon *)&Car);
            v19 = gta2::Weapon_sub_41C1E0(&v39);
            if ( gta2::MapRelatedStruct_sub_4334D0(pMapRelatedStruct, v19, v32, SMG) )
            {
              gta2::Player_sub_40E530((struct Player *)&Car, &unk_66BBE8);
              goto LABEL_35;
            }
            break;
          case 3:
            v33 = gta2::Weapon_sub_41C1E0((struct Weapon *)&Car);
            v20 = gta2::Weapon_sub_41C1E0(&v39);
            if ( gta2::MapRelatedStruct_sub_433500(pMapRelatedStruct, v20, v33, SMG) )
            {
              gta2::Weapon_UseAmmo(&v39, &unk_66BD18);
LABEL_35:
              index = 4;
            }
            break;
          default:
            break;
        }
        LOBYTE(v39.field_8) = ++index;
      }
      while ( index < 4u );
      v34 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&Car);
      v21 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v39);
      gta2::MapRelatedStruct_FindMaxZForTile(pMapRelatedStruct, v21, v34, &v39.SMG);
      gta2::S202_sub_41F980((struct S202 *)&v39.Ped, v39.SMG);
      v23 = (int *)gta2::S202_sub_401B20(v22, (struct SpriteS1 *)&v39.field_20, (struct PublicTransport *)&unk_66BBE8);
      v24 = (int *)gta2::S202_sub_401B20((struct S202 *)&Car, (struct SpriteS1 *)&v39.SoundWeapon, (struct PublicTransport *)&unk_66BD18);
      v25 = (int *)gta2::S202_sub_401B20((struct S202 *)&v39, (struct SpriteS1 *)&v39.field_2C, (struct PublicTransport *)&unk_66BD18);
      LOWORD(v26) = unk_66BD10;
      gta2::Object_SpawnObject(gObject, 129, *v25, *v24, *v23, v26);
    }
  }
  return gta2::PublicTransport_sub_4AF500((struct PublicTransport *)v39.field_C);
}


// 0x004b0cf0: PublicTransport::sub_4B0CF0
// IDA: PublicTransport::sub_4B0CF0
// Ghidra: FUN_004b0cf0
int gta2::PublicTransport_sub_4B0CF0(void *self)
{
  void *pvVar1;
  byte bVar2;
  uint uVar3;
  undefined4 extraout_ECX;
  ushort uVar4;
  undefined4 uVar5;
  int iVar6;
  
  if (!gSkipBuses) {
    uVar4 = 0;
    if (DAT_0066bb49 != 0) {
      do {
        uVar3 = (uint)uVar4;
        iVar6 = uVar3 * 3;
        pvVar1 = (void *)((int)self + uVar3 * 0x34);
        if (*(int *)((int)self + uVar3 * 0x34) == 1) {
          gta2::FUN_0040ce30(&stack0xfffffff0,
                       *(byte *)(*(int *)((int)pvVar1 + 0x10) + 2));
          uVar5 = extraout_ECX;
          gta2::FUN_0040ce30(&stack0xffffffec,
                       *(byte *)(*(int *)((int)pvVar1 + 0x10) + 1));
          bVar2 = gta2::Game_sub_45BC10(gGame,uVar5,iVar6);
          if (bVar2 != 0) {
            return (int)pvVar1;
          }
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < DAT_0066bb49);
    }
  }
  return 0;
}


// 0x004b0d70: PublicTransport::sub_4B0D70
// IDA: PublicTransport::sub_4B0D70
// Ghidra: ---
char gta2::PublicTransport_sub_4B0D70(struct PublicTransport *self, Car *a2)
{
  int v2; // eax
  struct Car *Car; // ecx
  struct SpriteS1 *v5; // eax

  LOBYTE(v2) = skip_buses;
  if ( !skip_buses )
  {
    Car = self->BusMetrics.Car;
    if ( Car )
    {
      if ( a2 == Car )
      {
        v2 = self->BusMetrics.field_48;
        if ( v2 )
        {
          if ( v2 == 14 )
            self->BusMetrics.field_4 = 10;
        }
        else if ( self->BusMetrics.Car1 != 1
               || (v5 = gta2::Car_sub_421D90(Car, (struct SpriteS1 *)&a2), LOWORD(v2) = gta2::Car_sub_403820((struct Car *)v5, byte_66BC54), !v2) )
        {
          self->BusMetrics.field_48 = 12;
          self->BusMetrics.field_4 = 10;
        }
      }
    }
  }
  return v2;
}


// 0x004b0df0: PublicTransport::sub_4B0DF0
// IDA: PublicTransport::sub_4B0DF0
// Ghidra: ---
bool gta2::PublicTransport_sub_4B0DF0(struct PublicTransport *self, Car *pCar, int *a3)
{
  bool result; // al
  unsigned __int8 v5; // bl
  struct Car *Car; // ecx
  unsigned __int8 v7; // [esp+4h] [ebp-4h]

  if ( skip_trains )
    return 0;
  v5 = 0;
  v7 = 0;
  while ( 1 )
  {
    Car = self->BUS[v7].Car;
    if ( Car == pCar )
      break;
LABEL_7:
    v7 = ++v5;
    if ( v5 >= 10u )
      return 0;
  }
  if ( gta2::Car_IsEngineOn(Car) )
  {
    switch ( self->BUS[v7].field_50 )
    {
      case 0:
        *a3 = unk_66BC80;
        result = 0;
        break;
      case 1:
        *a3 = unk_66BB60.field_0;
        result = 0;
        break;
      case 2:
        *a3 = *(_DWORD *)byte_66BC54;
        result = 1;
        break;
      case 3:
        *a3 = unk_66BB60.field_0;
        result = 1;
        break;
      case 4:
        *a3 = unk_66BE54;
        result = 1;
        break;
      case 5:
        *a3 = unk_66BE3C;
        result = 1;
        break;
      default:
        goto LABEL_7;
    }
  }
  else
  {
    *a3 = *(_DWORD *)byte_66BC54;
    return self->BUS[v7].field_50 >= 2u;
  }
  return result;
}


// 0x004b0f20: PublicTransport::sub_4B0F20
// IDA: PublicTransport::sub_4B0F20
// Ghidra: FUN_004b0f20
void gta2::PublicTransport_sub_4B0F20(void *self)
{
  LoadScreen *this_00;
  struct MapRelatedStruct *this_01;
  byte bVar1;
  char cVar2;
  bool bVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  struct SpriteS1 *pSVar9;
  struct Car *pCVar10;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  Matrix3D **this_02;
  Matrix3D *pMVar11;
  ushort uVar12;
  undefined4 unaff_EDI;
  int *piVar13;
  Matrix3D *local_14;
  Matrix3D *local_10;
  int local_c;
  Turrel *local_8 [2];
  struct Ped *pPed;
  
  if (!gSkipBuses) {
    if (((_DAT_0066bb4c == 0) && (DAT_0066bb4a == '\0')) &&
       (bVar1 = gta2::CarSystemManager_sub_420CE0(gCarSystemManager,1), bVar1 != 0)) {
      iVar5 = FUN_004b0cf0(self);
      if (iVar5 != 0) {
        iVar5 = *(int *)(iVar5 + 0x10);
        gta2::FUN_0040ce30(&local_10,*(byte *)(iVar5 + 1));
        local_14 = local_10;
        gta2::FUN_0040ce30(&local_10,*(byte *)(iVar5 + 2));
        piVar13 = &local_c;
        iVar5 = DecoderFloat(&local_10);
        iVar6 = DecoderFloat(&local_14);
        gta2::MapRelatedStruct_FindMaxZForTile(gMapRelatedStruct,iVar6,iVar5,piVar13)
        ;
        this_01 = gMapRelatedStruct;
        uVar12 = 0;
        do {
          switch(uVar12) {
          case 0:
            iVar5 = local_c;
            iVar6 = DecoderFloat(&local_10);
            iVar7 = DecoderFloat(&local_14);
            cVar2 = FUN_00433470(iVar7,iVar6,iVar5);
            if (cVar2 != '\0') {
              this_02 = &local_10;
LAB_004b109b:
              UseAmmo(this_02,(int *)&DAT_0066bd18);
LAB_004b10a5:
              uVar12 = 4;
            }
            break;
          case 1:
            iVar5 = local_c;
            iVar6 = DecoderFloat(&local_10);
            iVar7 = DecoderFloat(&local_14);
            bVar3 = gta2::MapRelatedStruct_sub_4334A0(this_01,(char)iVar7,iVar6,iVar5);
            if (bVar3) {
              gta2::Player_sub_40E530((Point2D *)&local_14,(int *)&DAT_0066bbe8);
              goto LAB_004b10a5;
            }
            break;
          case 2:
            iVar5 = local_c;
            uVar8 = DecoderFloat(&local_10);
            cVar2 = (char)iVar5;
            iVar5 = DecoderFloat(&local_14);
            bVar3 = gta2::MapRelatedStruct_sub_4334D0(this_01,iVar5,uVar8,cVar2,(byte)unaff_EDI);
            if (bVar3) {
              gta2::Player_sub_40E530((Point2D *)&local_10,(int *)&DAT_0066bbe8);
              goto LAB_004b10a5;
            }
            break;
          case 3:
            iVar5 = local_c;
            uVar8 = DecoderFloat(&local_10);
            iVar6 = DecoderFloat(&local_14);
            bVar3 = gta2::MapRelatedStruct_sub_433500(this_01,(char)iVar6,uVar8,iVar5);
            if (bVar3) {
              this_02 = &local_14;
              goto LAB_004b109b;
            }
          }
          uVar12 = uVar12 + 1;
        } while (uVar12 < 4);
        piVar13 = &local_c;
        iVar5 = DecoderFloat(&local_10);
        iVar6 = DecoderFloat(&local_14);
        iVar5 = gta2::MapRelatedStruct_FindMaxZForTile(this_01,iVar6,iVar5,piVar13);
        bVar1 = FUN_004af030(4,iVar5);
        if (bVar1 != 0) {
          local_8[0] = (Turrel *)0xb;
          pSVar9 = gta2::S202_sub_401B20((Point2D *)&local_10,(struct SpriteS1 *)(local_8 + 1),
                              (struct S127 *)&DAT_0066bd18);
          pCVar10 = gta2::CarSystemManager_sub_427D60(gCarSystemManager,local_14,
                               (Matrix3D *)pSVar9->FirstElement,4,
                               (byte *)local_8);
          *(Car **)((int)self + 0x17cc) = pCVar10;
        }
        bVar1 = FUN_004af030(2,iVar5);
        pMVar11 = local_10;
        if (bVar1 != 0) {
          local_8[0] = (Turrel *)0xb;
          pSVar9 = gta2::S202_sub_401B20((Point2D *)&local_14,(struct SpriteS1 *)(local_8 + 1),
                              (struct S127 *)&DAT_0066bd18);
          pCVar10 = gta2::CarSystemManager_sub_427D60(gCarSystemManager,
                               (Matrix3D *)pSVar9->FirstElement,local_10,2,
                               (byte *)local_8);
          *(Car **)((int)self + 0x17cc) = pCVar10;
          pMVar11 = local_10;
        }
        bVar1 = FUN_004af030(3,iVar5);
        if (bVar1 != 0) {
          local_8[0] = (Turrel *)0xb;
          pCVar10 = gta2::CarSystemManager_sub_427D60(gCarSystemManager,local_14,pMVar11,3,
                               (byte *)local_8);
          *(Car **)((int)self + 0x17cc) = pCVar10;
        }
        bVar1 = FUN_004af030(1,iVar5);
        if (bVar1 != 0) {
          local_8[0] = (Turrel *)0xb;
          pCVar10 = gta2::CarSystemManager_sub_427D60(gCarSystemManager,local_14,pMVar11,1,
                               (byte *)local_8);
          *(Car **)((int)self + 0x17cc) = pCVar10;
        }
        if (*(Car **)((int)self + 0x17cc) != NULL) {
          gta2::Car_CarMakeDriveable2(*(Car **)((int)self + 0x17cc));
          gta2::EngineStruct_MakeDriveable3((struct Car *)(*(Car **)((int)self + 0x17cc))->
                                     EngineStruct,*(Car **)((int)self + 0x17cc))
          ;
          gta2::Car_CarPutDummyDriverIn(*(Car **)((int)self + 0x17cc));
          gta2::Car_CarMakeDriveable1(*(Car **)((int)self + 0x17cc),4);
          gta2::Car_CarMakeDummy(*(Car **)((int)self + 0x17cc));
          gta2::Car_ENGINE_ON(*(Car **)((int)self + 0x17cc));
          DAT_0066bb4a = '\x01';
          *(undefined4 *)((int)self + 0x1808) = 0;
          *(undefined1 *)((int)self + 0x1816) = 0;
          gta2::Car_sub_424630(*(Car **)((int)self + 0x17cc),1);
        }
      }
      _DAT_0066bb4c = 200;
    }
    else {
      _DAT_0066bb4c = _DAT_0066bb4c + -1;
      if (_DAT_0066bb4c < 0) {
        _DAT_0066bb4c = 0;
      }
    }
    pCVar10 = *(Car **)((int)self + 0x17cc);
    if (pCVar10 != NULL) {
      this_00 = (LoadScreen *)((int)self + 0x17c0);
      if (*(char *)((int)self + 0x17c0) == '\0') {
        bVar1 = gta2::Car_IsDriverPlayer(pCVar10);
        if (bVar1 == 0) {
          pPed = pCVar10->Driver;
          if (((pPed != NULL) && (iVar5 = gta2::Ped_GetCurrentOccupation(pPed), iVar5 != 4))
             && (iVar5 = gta2::Ped_GetCurrentOccupation(pPed), iVar5 != 5)) {
            this_00->field0_0x0 = 1;
          }
        }
        else {
          this_00->field0_0x0 = 1;
          gta2::PlayerStats_sub_4B8BD0((SaveSlotAnimatedValue *)&pCVar10->Driver->isPlayer->Money,
                     pCVar10);
        }
      }
      else {
        bVar1 = gta2::Car_IsDriverPlayer(pCVar10);
        if (((bVar1 == 0) && (pCVar10->Driver != NULL)) &&
           (iVar5 = gta2::Ped_GetCurrentOccupation(pCVar10->Driver), iVar5 == 0xc)) {
          this_00->field0_0x0 = 0;
          *(undefined1 *)((int)self + 0x17c2) = 0;
          gta2::Ped_SetCurrentOccupation(pCVar10->Driver,5);
          gta2::Ped_SetSearchType(*(Ped **)(*(int *)((int)self + 0x17cc) + 0x54),3);
        }
        if ((*(char *)((int)self + 0x17c2) == '\0') &&
           (*(char *)((int)self + 0x1818) == '\0')) {
          pSVar9 = gta2::S202_sub_401B20((Point2D *)&DAT_0066bb60,(struct SpriteS1 *)(local_8 + 1)
                              ,(struct S127 *)&DAT_0066bb5c);
          pCVar10 = gta2::Car_sub_421D90(*(Car **)((int)self + 0x17cc),
                                     (struct Car *)local_8);
          bVar3 = gta2::Car_sub_403800(pCVar10,(int *)pSVar9);
          if (CONCAT31(extraout_var,bVar3) != 0) {
            *(undefined1 *)((int)self + 0x17c2) = 1;
            FUN_00445e40();
          }
        }
      }
      pCVar10 = *(Car **)((int)self + 0x17cc);
      sVar4 = gta2::Car_sub_4A9AD0(pCVar10);
      if (sVar4 < 0xc9) {
        bVar3 = gta2::Car_GetMask(pCVar10);
        if ((!bVar3) && (pCVar10->Damage != 32000)) {
          switch(*(undefined4 *)((int)self + 0x1808)) {
          case 5:
            *(short *)((int)self + 0x17c4) = *(short *)((int)self + 0x17c4) + -1
            ;
            FUN_0041f8a0(pCVar10);
            if (*(short *)((int)self + 0x17c4) == 0) {
              *(undefined2 *)((int)self + 0x17c4) = 100;
              *(undefined4 *)((int)self + 0x1808) = 0xd;
            }
            break;
          case 9:
            gta2::Car_sub_41F8F0(pCVar10);
            *(short *)((int)self + 0x17c4) = *(short *)((int)self + 0x17c4) + -1
            ;
            if (*(short *)((int)self + 0x17c4) == 0) {
              *(undefined4 *)((int)self + 0x1808) = 0xe;
              *(undefined2 *)((int)self + 0x17c4) = 10;
            }
            break;
          case 0xc:
            *(short *)((int)self + 0x17c4) = *(short *)((int)self + 0x17c4) + -1
            ;
            gta2::Car_sub_4222F0(pCVar10);
            if (*(short *)((int)self + 0x17c4) == 0) {
              *(undefined4 *)((int)self + 0x1808) = 5;
              *(undefined2 *)((int)self + 0x17c4) = 10;
            }
            break;
          case 0xd:
            if (*(char *)((int)self + 0x17c2) == '\0') {
              gta2::Car_sub_4AFB30(this_00);
            }
            if (this_00->field0_0x0 == 0) {
              *(short *)((int)self + 0x17c4) =
                   *(short *)((int)self + 0x17c4) + -1;
              if (*(short *)((int)self + 0x17c4) == 0) {
                *(undefined4 *)((int)self + 0x1808) = 9;
                *(undefined2 *)((int)self + 0x17c4) = 10;
              }
            }
            else {
              piVar13 = (int *)&DAT_0066bc54;
              pCVar10 = gta2::Car_sub_421D90(*(Car **)((int)self + 0x17cc),
                                         (struct Car *)(local_8 + 1));
              bVar3 = gta2::Car_sub_403800(pCVar10,piVar13);
              if (CONCAT31(extraout_var_00,bVar3) != 0) {
                *(undefined4 *)((int)self + 0x1808) = 9;
                *(undefined2 *)((int)self + 0x17c4) = 10;
              }
            }
            break;
          case 0xe:
            gta2::Car_sub_4222D0(pCVar10);
            *(short *)((int)self + 0x17c4) = *(short *)((int)self + 0x17c4) + -1
            ;
            if (*(short *)((int)self + 0x17c4) == 0) {
              *(undefined4 *)((int)self + 0x1808) = 0;
            }
          }
          gta2::S56_sub_447480(gCheckpoint2,
                     *(SpriteS1 **)(*(int *)((int)self + 0x17cc) + 0x50));
          return;
        }
        _DAT_0066bb4c = 0;
      }
      else {
        gta2::Car_isMask4(pCVar10);
        _DAT_0066bb4c = 100;
      }
      *(undefined4 *)((int)self + 0x17cc) = 0;
      DAT_0066bb4a = '\0';
    }
  }
  return;
}


// 0x004b1560: PublicTransport::sub_4B1560
// IDA: PublicTransport::sub_4B1560
// Ghidra: ---
char gta2::PublicTransport_sub_4B1560(struct PublicTransport *self)
{
  struct PublicTransport *pS81; // esi
  unsigned __int16 v2; // ax
  int v3; // edx
  struct Car *Car; // eax
  int v5; // esi
  struct Car *pCar; // edi
  struct Car *v7; // eax
  struct Car *v8; // eax
  int v9; // ebx
  int v10; // ebp
  int v11; // edi
  int v12; // ebp
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // ebp
  int v18; // ebx
  _DWORD *v19; // edi
  void *v20; // ecx
  int v21; // eax
  int v22; // ebp
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // ecx
  int v30; // eax
  int v31; // edi
  _DWORD *v32; // eax
  int v33; // edx
  char v35; // [esp+7h] [ebp-15h]
  int v36; // [esp+8h] [ebp-14h]
  int v37; // [esp+Ch] [ebp-10h]
  char v39[4]; // [esp+14h] [ebp-8h] BYREF
  char v40[4]; // [esp+18h] [ebp-4h] BYREF

  pS81 = self;
  v35 = 0;
  gta2::PublicTransport_sub_4B0F20(self);
  LOBYTE(v2) = skip_trains;
  if ( !skip_trains )
  {
    v2 = 0;
    v37 = 0;
    while ( 1 )
    {
      v3 = v2;
      Car = pS81->BUS[v2].Car;
      v5 = (int)&pS81->BUS[v3];
      if ( !Car )
        goto LABEL_98;
      gta2::sub_4AF2B0(v5);
      pCar = *(Car **)(v5 + 12);
      if ( gta2::Car_IsDriverPlayer(pCar) )
      {
        if ( pCar->Driver )
        {
          *(_BYTE *)v5 = 1;
          v7 = gta2::Ped_sub_436200(pCar->Driver, (struct Car *)v39);
          if ( gta2::Car_sub_403800(v7, (int)byte_66BC54) )
          {
            if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 84) + 348) + 139) )
              gta2::sub_4AF9A0((void *)v5);
          }
          else
          {
            v8 = gta2::Ped_sub_436200(*(Ped **)(*(_DWORD *)(v5 + 12) + 84), (struct Car *)v40);
            if ( gta2::sub_4037E0(v8) && *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 84) + 348) + 140) )
              gta2::sub_4AFA10((_DWORD *)v5);
          }
        }
        else
        {
          gta2::Car_CarMakeDriveable1(pCar, SEARCHTYPE_LINE_OF_SIGHT);
          *(_BYTE *)v5 = 0;
        }
      }
      switch ( *(_DWORD *)(v5 + 80) )
      {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
          v35 = 1;
          break;
        case 2:
          v35 = 0;
          break;
        default:
          break;
      }
      switch ( *(_DWORD *)(v5 + 72) )
      {
        case 0:
          v36 = *(_DWORD *)(v5 + 76);
          if ( *(_BYTE *)v5 )
          {
            if ( v35 )
              goto LABEL_33;
          }
          else
          {
            if ( !*(_DWORD *)(*(_DWORD *)(v5 + 76) + 24) )
              goto LABEL_33;
            gta2::sub_4AFA80(v5);
          }
          *(_DWORD *)(v5 + 72) = 1;
LABEL_33:
          if ( !*(_BYTE *)v5 )
          {
            v16 = *(_DWORD *)(v5 + 12);
            v17 = *(_DWORD *)(v16 + 80);
            v18 = *(_DWORD *)(v36 + 4);
            if ( (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v17 + 20)) == *(_BYTE *)(v18 + 1)
              && (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v17 + 24)) == *(_BYTE *)(v18 + 2) )
            {
              if ( v16 )
              {
                v19 = *(_DWORD **)(v16 + 84);
                if ( v19 )
                {
                  if ( *(_BYTE *)(v5 + 67) )
                    gta2::sub_4AF860(v19, v36);
                }
              }
              *(_DWORD *)(v5 + 72) = 2;
              gta2::sub_4AFA10((_DWORD *)v5);
            }
            else if ( *(_DWORD *)(v5 + 80) != 2 && v35 )
            {
              gta2::sub_4AF9A0((void *)v5);
            }
          }
LABEL_98:
          v2 = ++v37;
          if ( (unsigned __int16)v37 >= 0xAu )
            return v2;
          pS81 = self;
          break;
        case 1:
          if ( *(_BYTE *)v5 )
          {
            if ( v35 )
              *(_DWORD *)(v5 + 72) = 0;
          }
          else if ( !*(_DWORD *)(*(_DWORD *)(v5 + 76) + 24) )
          {
            gta2::sub_4AF290((_DWORD *)v5);
            *(_DWORD *)(v5 + 72) = 0;
            gta2::sub_4AF9A0(v20);
          }
          goto LABEL_98;
        case 2:
          v21 = *(_DWORD *)(v5 + 76);
          *(_DWORD *)(v21 + 24) = v5;
          v22 = *(_DWORD *)(v21 + 12);
          v23 = *(_DWORD *)(*(_DWORD *)(v5 + 12) + 80);
          if ( (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v23 + 20)) == *(_BYTE *)(v22 + 1)
            && (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v23 + 24)) == *(_BYTE *)(v22 + 2) )
          {
            *(_DWORD *)(v5 + 72) = 4;
          }
          else if ( *(_BYTE *)v5 == 1 && !v35 )
          {
            *(_DWORD *)(v5 + 72) = 3;
          }
          goto LABEL_98;
        case 3:
          if ( *(_BYTE *)v5 == 1 && v35 )
            *(_DWORD *)(v5 + 72) = 2;
          goto LABEL_98;
        case 4:
          if ( *(_BYTE *)v5 )
          {
            if ( v35 )
            {
              *(_DWORD *)(v5 + 72) = 10;
            }
            else
            {
              *(_DWORD *)(v5 + 72) = 5;
              gta2::sub_4AFAF0((Car **)v5);
              *(_WORD *)(v5 + 4) = 10;
            }
          }
          else
          {
            gta2::sub_4AFA80(v5);
            *(_DWORD *)(v5 + 72) = 5;
            *(_WORD *)(v5 + 4) = 10;
            gta2::sub_4AFAF0((Car **)v5);
          }
          goto LABEL_98;
        case 5:
          --*(_WORD *)(v5 + 4);
          gta2::sub_4AFAF0((Car **)v5);
          if ( *(_BYTE *)v5 == 1 && v35 )
          {
            *(_DWORD *)(v5 + 72) = 10;
          }
          else if ( !*(_WORD *)(v5 + 4) )
          {
            v24 = *(_DWORD *)(v5 + 76);
            *(_DWORD *)(v5 + 72) = 6;
            *(_WORD *)(v5 + 4) = 10;
            *(_DWORD *)(v24 + 24) = v5;
            *(_DWORD *)(v24 + 28) = 4;
          }
          goto LABEL_98;
        case 6:
          if ( *(_BYTE *)v5 == 1 )
          {
            if ( v35 )
            {
              *(_DWORD *)(v5 + 72) = 10;
            }
            else if ( !--*(_WORD *)(v5 + 4) )
            {
              v25 = *(_DWORD *)(v5 + 76);
              *(_WORD *)(v5 + 4) = 50;
              *(_DWORD *)(v5 + 72) = 7;
              *(_DWORD *)(v25 + 28) = 2;
            }
          }
          else if ( !--*(_WORD *)(v5 + 4) )
          {
            v26 = *(_DWORD *)(v5 + 76);
            *(_WORD *)(v5 + 4) = 50;
            *(_DWORD *)(v5 + 72) = 7;
            *(_DWORD *)(v26 + 28) = 2;
          }
          goto LABEL_98;
        case 7:
          if ( *(_BYTE *)v5 == 1 )
          {
            if ( v35 )
            {
              *(_DWORD *)(v5 + 72) = 10;
            }
            else
            {
              gta2::Car_sub_4AFB30((struct Car *)v5);
              if ( !--*(_WORD *)(v5 + 4) )
              {
                v27 = *(_DWORD *)(v5 + 76);
                *(_DWORD *)(v5 + 72) = 8;
                *(_WORD *)(v5 + 4) = 50;
                *(_DWORD *)(v27 + 28) = 2;
              }
            }
          }
          else
          {
            gta2::Car_sub_4AFB30((struct Car *)v5);
            if ( !--*(_WORD *)(v5 + 4) )
            {
              v28 = *(_DWORD *)(v5 + 76);
              *(_DWORD *)(v5 + 72) = 8;
              *(_WORD *)(v5 + 4) = 50;
              *(_DWORD *)(v28 + 28) = 2;
            }
          }
          goto LABEL_98;
        case 8:
          if ( *(_BYTE *)v5 == 1 )
          {
            if ( v35 )
            {
              *(_DWORD *)(v5 + 72) = 10;
            }
            else if ( !--*(_WORD *)(v5 + 4) )
            {
              v29 = *(_DWORD *)(v5 + 76);
              *(_DWORD *)(v5 + 72) = 9;
              *(_WORD *)(v5 + 4) = 10;
              *(_DWORD *)(v29 + 28) = 3;
            }
          }
          else if ( !--*(_WORD *)(v5 + 4) )
          {
            v30 = *(_DWORD *)(v5 + 12);
            v31 = *(_DWORD *)(v5 + 76);
            if ( v30 )
            {
              v32 = *(_DWORD **)(v30 + 84);
              if ( v32 )
              {
                if ( *(_BYTE *)(v5 + 67) )
                  gta2::sub_4AF880(v32, *(_DWORD *)(v5 + 76));
              }
            }
            *(_DWORD *)(v5 + 72) = 9;
            *(_WORD *)(v5 + 4) = 10;
            *(_DWORD *)(v31 + 28) = 3;
          }
          goto LABEL_98;
        case 9:
          gta2::sub_4AFAB0((Car **)v5);
          if ( *(_BYTE *)v5 == 1 )
            goto LABEL_94;
          if ( !--*(_WORD *)(v5 + 4) )
          {
            v33 = *(_DWORD *)(v5 + 76);
            *(_DWORD *)(v5 + 72) = 10;
            *(_DWORD *)(v33 + 28) = 1;
          }
          goto LABEL_98;
        case 0xA:
          gta2::sub_4AFAB0((Car **)v5);
          v9 = *(_DWORD *)(v5 + 76);
          if ( *(_BYTE *)v5 )
          {
            if ( !v35 )
            {
              v10 = *(_DWORD *)(v9 + 12);
              v11 = *(_DWORD *)(*(_DWORD *)(v5 + 12) + 80);
              if ( (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v11 + 20)) == *(_BYTE *)(v10 + 1)
                && (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v11 + 24)) == *(_BYTE *)(v10 + 2) )
              {
                *(_DWORD *)(v5 + 72) = 4;
                goto LABEL_98;
              }
              *(_DWORD *)(v5 + 72) = 11;
            }
          }
          else
          {
            gta2::sub_4AF290((_DWORD *)v5);
          }
          v12 = *(_DWORD *)(v9 + 8);
          v13 = *(_DWORD *)(*(_DWORD *)(v5 + 12) + 80);
          if ( (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v13 + 20)) == *(_BYTE *)(v12 + 1)
            && (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)(v13 + 24)) == *(_BYTE *)(v12 + 2) )
          {
            *(_DWORD *)(v5 + 72) = 0;
            gta2::sub_4AF9A0((void *)v5);
            v14 = *(_DWORD *)(v5 + 76);
            *(_DWORD *)(v14 + 24) = 0;
            v15 = *(_DWORD *)(v14 + 32);
            *(_DWORD *)(v5 + 76) = v15;
            *(_DWORD *)(v15 + 28) = 1;
          }
          goto LABEL_98;
        case 0xB:
LABEL_94:
          if ( v35 )
            *(_DWORD *)(v5 + 72) = 10;
          goto LABEL_98;
        default:
          goto LABEL_98;
      }
    }
  }
  return v2;
}


// 0x004b1b40: PublicTransport::sub_4B1B40
// IDA: PublicTransport::sub_4B1B40
// Ghidra: ---
int gta2::PublicTransport_sub_4B1B40(struct PublicTransport *self, Car *pCar)
{
  if ( skip_trains )
    return 0;
  if ( gta2::Car_IsTrainOrTrainCarriage(pCar) )
    return gta2::PublicTransport_sub_4AF680(self, pCar)[3];
  return 0;
}


// 0x004b1b80: PublicTransport::sub_4B1B80
// IDA: PublicTransport::sub_4B1B80
// Ghidra: ---
bool gta2::PublicTransport_sub_4B1B80(struct PublicTransport *self, Car *pCar, Car *a3)
{
  _DWORD *v4; // edi
  bool result; // al

  result = 0;
  if ( gta2::Car_IsTrainOrTrainCarriage(pCar) && gta2::Car_IsTrainOrTrainCarriage(a3) )
  {
    v4 = gta2::PublicTransport_sub_4AF680(self, pCar);
    if ( *((_BYTE *)v4 + 87) != *((_BYTE *)gta2::PublicTransport_sub_4AF680(self, a3) + 87) )
      return 1;
  }
  return result;
}



