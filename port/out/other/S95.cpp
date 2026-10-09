#include "gta2_shim.h"

// Module: other, Class: S95
// Functions: 12
// Source: unified (IDA+Ghidra)

// 0x0049c680: S95::sub_49C680
// IDA: S95::sub_49C680
// Ghidra: FUN_0049c680
bool gta2::S95_sub_49C680(int param_1,undefined4 param_2)
{
  byte bVar1;
  byte bVar2;
  char cVar3;
  
  bVar1 = *(byte *)(param_1 + 0x25);
  if ((1 < bVar1) && (bVar1 < 0xfe)) {
    bVar2 = *(byte *)(param_1 + 0x26);
    if ((1 < bVar2) && (bVar2 < 0xfe)) {
      cVar3 = FUN_004656d0(bVar1,bVar2,*(undefined1 *)(param_1 + 0x27),param_2,
                           &DAT_0066a7e0,1);
      return cVar3 == '\0';
    }
  }
  return false;
}


// 0x0049c6e0: S95::InitBuffer
// IDA: S95::InitBuffer
// Ghidra: ---
int gta2::S95_InitBuffer(struct S95 *self)
{
  int result; // eax

  result = 0;
  memset(self->Buffer_0x2310, 0, sizeof(self->Buffer_0x2310));
  return result;
}


// 0x0049c700: S95::sub_49C700
// IDA: S95::sub_49C700
// Ghidra: ---
int gta2::S95_sub_49C700(struct S95 *self)
{
  int result; // eax

  result = 0;
  memset(self->Buffer_0x2310, 0, sizeof(self->Buffer_0x2310));
  self->field_38 = 0;
  self->field_34 = 1;
  self->field_36 = 0;
  self->field_3A = 0;
  self->field_2FD0 = 1;
  self->field_2FD1 = 0;
  return result;
}


// 0x0049c740: S95::sub_49C740
// IDA: S95::sub_49C740
// Ghidra: ---
void gta2::S95_sub_49C740(struct S95 *self, Passenger *pPassenger)
{
  if ( pPassenger == self->Passenger1 )
  {
    self->field_2FD0 = 1;
    self->field_2FD1 = 0;
  }
}


// 0x0049c760: S95::sub_49C760
// IDA: S95::sub_49C760
// Ghidra: ---
char gta2::S95_sub_49C760(struct S95 *self)
{
  unsigned __int8 v1; // bl
  unsigned __int8 v2; // al
  unsigned __int8 v3; // dl
  unsigned __int16 v4; // ax
  char *v5; // ecx
  __int64 v6; // rax
  char result; // al

  v1 = self->field_23;
  if ( v1 <= 0x20u )
  {
    v2 = self->field_24;
    if ( v2 <= 0x20u )
    {
      v3 = self->field_22;
      if ( v3 <= 8u )
      {
        v4 = v1 + 34 * v2;
        self->field_1C = v4;
        v5 = &self->Buffer_0x2310[8 * v4];
        if ( !v5[1] )
          return 1;
        if ( *v5 != 1 && v5[2] != v3 )
        {
          v6 = (unsigned __int8)v5[2] - v3;
          if ( (int)((HIDWORD(v6) ^ v6) - HIDWORD(v6)) >= 1 )
          {
            *v5 = 1;
            return 1;
          }
        }
        return 0;
      }
    }
  }
  if ( self->field_10 != self->field_13 )
    return 0;
  switch ( dword_66A7D4 )
  {
    case 1:
      if ( self->field_24 )
        return 0;
      return 2;
    case 2:
      if ( self->field_24 <= 0x20u )
        return 0;
      goto LABEL_15;
    case 3:
      if ( v1 <= 0x20u )
        return 0;
      return 2;
    case 4:
      if ( v1 )
        return 0;
LABEL_15:
      result = 2;
      break;
    default:
      return 0;
  }
  return result;
}


// 0x0049c820: S95::sub_49C820
// IDA: S95::sub_49C820
// Ghidra: ---
char gta2::S95_sub_49C820(struct S95 *self)
{
  char v1; // dl
  unsigned __int8 v2; // bl
  unsigned __int16 v3; // ax
  bool v4; // zf
  char *v5; // eax
  __int16 v6; // di
  __int16 v7; // si
  int v8; // esi
  char v9; // bl
  char v10; // al
  __int16 v12; // [esp+0h] [ebp-4h]

  v1 = self->field_22;
  if ( unk_66A7E0 )
    v1 += unk_66A7E0;
  v2 = self->field_23;
  v12 = (v1 != self->field_13) + 1;
  v3 = v2 + 34 * (unsigned __int8)self->field_24;
  self->field_1C = v3;
  v4 = self->Buffer_0x2310[8 * v3] == 1;
  v5 = &self->Buffer_0x2310[8 * v3];
  if ( v4 && v1 == v5[2] )
  {
    *v5 = 0;
  }
  else
  {
    if ( self->field_4 )
    {
      v7 = *(_WORD *)&self->field_16;
    }
    else
    {
      v6 = (unsigned __int8)self->field_20 - (unsigned __int8)self->field_11;
      v7 = v12
         * (v6 * v6
          + ((unsigned __int8)self->field_21 - (unsigned __int8)self->field_12)
          * ((unsigned __int8)self->field_21 - (unsigned __int8)self->field_12));
    }
    *(_BYTE *)self->field_8 = v2;
    *(_BYTE *)(self->field_8 + 1) = self->field_24;
    *(_BYTE *)(self->field_8 + 2) = self->field_20;
    *(_BYTE *)(self->field_8 + 3) = self->field_21;
    *(_BYTE *)(self->field_8 + 4) = v1;
    *(_WORD *)(self->field_8 + 6) = v7;
    v8 = self->field_8 + 8;
    ++self->field_C;
    self->field_8 = v8;
    v9 = self->field_1B;
    if ( *v5 == 1 )
    {
      v5[3] = v9;
      v5[4] = v1;
    }
    else
    {
      v5[1] = v9;
      v5[2] = v1;
    }
    *((_WORD *)v5 + 3) = self->field_1E + 1;
    v10 = self->field_24;
    if ( v10 )
    {
      if ( v10 == 31 )
      {
        unk_66A7D8 = self->field_23;
        unk_66A7D9 = self->field_24;
        unk_66A7DA = self->field_20;
        unk_66A7DB = self->field_21;
        unk_66A7DC = self->field_22;
      }
    }
    else
    {
      unk_66A7C4 = self->field_23;
      unk_66A7C5 = self->field_24;
      unk_66A7C6 = self->field_20;
      unk_66A7C7 = self->field_21;
      unk_66A7C8 = self->field_22;
    }
    LOBYTE(v5) = self->field_23;
    if ( (_BYTE)v5 )
    {
      if ( (_BYTE)v5 == 31 )
      {
        unk_66A7BC = 31;
        unk_66A7BD = self->field_24;
        unk_66A7BE = self->field_20;
        LOBYTE(v5) = self->field_21;
        unk_66A7BF = (_BYTE)v5;
        unk_66A7C0 = self->field_22;
      }
    }
    else
    {
      unk_66A7CC = 0;
      unk_66A7CD = self->field_24;
      unk_66A7CE = self->field_20;
      unk_66A7CF = self->field_21;
      LOBYTE(v5) = self->field_22;
      unk_66A7D0 = (_BYTE)v5;
    }
  }
  return (char)v5;
}


// 0x0049cb40: S95::sub_49CB40
// IDA: S95::sub_49CB40
// Ghidra: VertexBuffer::FUN_0049cb40
bool gta2::S95_sub_49CB40(VertexBuffer *self,Ped *param_1)
{
  return (Ped *)((self->Passenger2).Passenger)->Passenger_ == param_1;
}


// 0x0049cb60: S95::sub_49CB60
// IDA: S95::sub_49CB60
// Ghidra: FUN_0049cb60
bool gta2::S95_sub_49CB60(int param_1,byte param_2,byte param_3)
{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  
  DAT_0066a7e0 = 0;
  bVar2 = *(byte *)(param_1 + 0x26);
  bVar1 = *(byte *)(param_1 + 0x25);
  cVar4 = param_3 - bVar2;
  if (param_2 == bVar1) {
    if (param_3 == bVar2) {
      return true;
    }
    if (cVar4 != -1) {
      uVar3 = FUN_0049c680(2);
      return (bool)uVar3;
    }
    uVar3 = FUN_0049c680(1);
    return (bool)uVar3;
  }
  if (param_3 == bVar2) {
    if ((byte)(param_2 - bVar1) != -1) {
      uVar3 = FUN_0049c680(3);
      return (bool)uVar3;
    }
    uVar3 = FUN_0049c680(4);
    return (bool)uVar3;
  }
  bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,(uint)bVar1,(uint)bVar2,
                     (uint)*(byte *)(param_1 + 0x27));
  if (bVar2 != 0) {
    return false;
  }
  uVar5 = (uint)*(byte *)(param_1 + 0x26);
  uVar7 = (uint)*(byte *)(param_1 + 0x25);
  if ((byte)(param_2 - bVar1) == '\x01') {
    if (cVar4 == '\x01') {
      bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,uVar7,uVar5 + 1,
                         (uint)*(byte *)(param_1 + 0x27));
      if (bVar2 != 0) {
        return false;
      }
      bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,*(byte *)(param_1 + 0x25) + 1,
                         (uint)*(byte *)(param_1 + 0x26),
                         (uint)*(byte *)(param_1 + 0x27));
      if (bVar2 != 0) {
        return false;
      }
      cVar4 = FUN_0049c680(2);
      if (cVar4 == '\0') {
        return false;
      }
      cVar4 = FUN_0049c680(3);
      if (cVar4 == '\0') {
        return false;
      }
      cVar4 = FUN_004656d0(*(byte *)(param_1 + 0x25) + 1,
                           *(undefined1 *)(param_1 + 0x26),
                           *(undefined1 *)(param_1 + 0x27),2,&DAT_0066a7e0,1);
      if (cVar4 != '\0') {
        return false;
      }
      uVar8 = 3;
      iVar6 = *(byte *)(param_1 + 0x26) + 1;
      goto LAB_0049ce9a;
    }
    bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,uVar7,uVar5 - 1,
                       (uint)*(byte *)(param_1 + 0x27));
    if (bVar2 != 0) {
      return false;
    }
    bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,*(byte *)(param_1 + 0x25) + 1,
                       (uint)*(byte *)(param_1 + 0x26),
                       (uint)*(byte *)(param_1 + 0x27));
    if (bVar2 != 0) {
      return false;
    }
    cVar4 = FUN_0049c680(1);
    if (cVar4 == '\0') {
      return false;
    }
    cVar4 = FUN_0049c680(3);
    if (cVar4 == '\0') {
      return false;
    }
    cVar4 = FUN_004656d0(*(byte *)(param_1 + 0x25) + 1,
                         *(undefined1 *)(param_1 + 0x26),
                         *(undefined1 *)(param_1 + 0x27),1,&DAT_0066a7e0,1);
    if (cVar4 != '\0') {
      return false;
    }
    uVar8 = 3;
  }
  else {
    if (cVar4 == '\x01') {
      bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,uVar7,uVar5 + 1,
                         (uint)*(byte *)(param_1 + 0x27));
      if ((((bVar2 == 0) &&
           (bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,*(byte *)(param_1 + 0x25) - 1,
                               (uint)*(byte *)(param_1 + 0x26),
                               (uint)*(byte *)(param_1 + 0x27)), bVar2 == 0)) &&
          (cVar4 = FUN_0049c680(2), cVar4 != '\0')) &&
         ((cVar4 = FUN_0049c680(4), cVar4 != '\0' &&
          (cVar4 = FUN_004656d0(*(byte *)(param_1 + 0x25) - 1,
                                *(undefined1 *)(param_1 + 0x26),
                                *(undefined1 *)(param_1 + 0x27),2,&DAT_0066a7e0,
                                1), cVar4 == '\0')))) {
        cVar4 = FUN_004656d0(*(undefined1 *)(param_1 + 0x25),
                             *(byte *)(param_1 + 0x26) + 1,
                             *(undefined1 *)(param_1 + 0x27),4,&DAT_0066a7e0,1);
        return cVar4 == '\0';
      }
      return false;
    }
    bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,uVar7,uVar5 - 1,
                       (uint)*(byte *)(param_1 + 0x27));
    if (bVar2 != 0) {
      return false;
    }
    bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,*(byte *)(param_1 + 0x25) - 1,
                       (uint)*(byte *)(param_1 + 0x26),
                       (uint)*(byte *)(param_1 + 0x27));
    if (bVar2 != 0) {
      return false;
    }
    cVar4 = FUN_0049c680(1);
    if (cVar4 == '\0') {
      return false;
    }
    cVar4 = FUN_0049c680(4);
    if (cVar4 == '\0') {
      return false;
    }
    cVar4 = FUN_004656d0(*(byte *)(param_1 + 0x25) - 1,
                         *(undefined1 *)(param_1 + 0x26),
                         *(undefined1 *)(param_1 + 0x27),1,&DAT_0066a7e0,1);
    if (cVar4 != '\0') {
      return false;
    }
    uVar8 = 4;
  }
  iVar6 = *(byte *)(param_1 + 0x26) - 1;
LAB_0049ce9a:
  cVar4 = FUN_004656d0(*(undefined1 *)(param_1 + 0x25),iVar6,
                       *(undefined1 *)(param_1 + 0x27),uVar8,&DAT_0066a7e0,1);
  return cVar4 == '\0';
}


// 0x0049cf10: S95::sub_49CF10
// IDA: S95::sub_49CF10
// Ghidra: ---
char gta2::S95_sub_49CF10(struct S95 *self)
{
  char v2; // al
  unsigned __int16 v4; // dx

  v2 = gta2::S95_sub_49C760(self);
  if ( v2 == 1 )
  {
    if ( gta2::S95_sub_49CB60(self, self->field_20, self->field_21) )
    {
      gta2::S95_sub_49C820(self);
      return 0;
    }
    v4 = self->field_1C;
    if ( self->Buffer_0x2310[8 * v4] != 1 || self->Buffer_0x2310[8 * v4 + 3] )
      return 0;
    self->Buffer_0x2310[8 * v4] = 0;
    return 0;
  }
  else
  {
    if ( v2 != 2 )
      return 0;
    self->field_18 = 0;
    self->field_19 = 1;
    self->field_1A = 1;
    return 1;
  }
}


// 0x0049cf70: S95::sub_49CF70
// IDA: S95::sub_49CF70
// Ghidra: ---
char gta2::S95_sub_49CF70(
        struct S95 *self,
        Passenger *arg0,
        int a3,
        unsigned __int8 a4,
        unsigned __int8 a5,
        unsigned __int8 a2,
        S202 *a7)
{
  Passenger *v7; // eax
  char v9; // dl
  char v10; // al
  unsigned __int8 v11; // bl
  char v12; // cl
  char S202; // dl
  struct CarSystemManager *CarSystemManager; // eax
  int *v15; // eax
  int *v16; // edi
  SpriteS1 **v17; // eax
  SpriteS1 **v18; // ebp
  int **v19; // eax
  Weapon *v20; // eax
  char v21; // dl
  char v22; // al
  int v24; // edx
  unsigned __int16 v25; // cx
  int *v26; // eax
  int v27; // ecx
  unsigned __int16 v28; // cx
  _BYTE *v29; // edx
  char v30; // al
  char v31; // al
  char v32; // cl
  bool v33; // zf
  __int16 v34; // ax
  char v35; // dl
  char v36; // bl
  char v37; // cl
  __int16 S202_low; // dx
  char *v39; // ecx
  __int64 v40; // rax
  unsigned __int8 v41; // dl
  char v42; // al
  char v43; // al
  char v44; // al
  int v45; // edi
  __int16 v46; // ax
  int v47; // edi
  unsigned __int8 v48; // cl
  _BYTE *v49; // eax
  _BYTE *v50; // eax
  S202 v51; // [esp+2Ch] [ebp+1Ch] BYREF

  v7 = arg0;
  self->field_2E = 100;
  self->Passenger1 = v7;
  unk_66A7C4 = 0;
  unk_66A7C5 = 0;
  unk_66A7C6 = 0;
  unk_66A7C7 = 0;
  unk_66A7C8 = 0;
  unk_66A7D8 = 0;
  unk_66A7D9 = 0;
  unk_66A7DA = 0;
  unk_66A7DB = 0;
  unk_66A7DC = 0;
  unk_66A7BC = 0;
  unk_66A7BD = 0;
  unk_66A7BE = 0;
  unk_66A7BF = 0;
  unk_66A7C0 = 0;
  unk_66A7CC = 0;
  unk_66A7CD = 0;
  unk_66A7CE = 0;
  unk_66A7CF = 0;
  unk_66A7D0 = 0;
  if ( self->field_2FD0 )
  {
    v9 = a2;
    v10 = (char)a7;
    v11 = a4;
    self->field_F = a5;
    v12 = v51.field_0;
    self->field_10 = v9;
    S202 = (char)v51.S202;
    self->field_11 = v10;
    CarSystemManager = v51.CarSystemManager;
    self->field_E = v11;
    self->field_12 = v12;
    self->field_13 = S202;
    self->field_2FD1 = 0;
    dword_66A7D4 = CarSystemManager;
    self->field_4 = 0;
    gta2::S95_InitBuffer(self);
    if ( !gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v11, a5, a2) )
    {
      gta2::S202_sub_40CE30((S202 *)&a7, a2);
      v16 = v15;
      gta2::S202_sub_40CE30(&v51, a5);
      v18 = v17;
      gta2::S202_sub_40CE30((S202 *)&v51.S202, v11);
      v20 = (Weapon *)gta2::MapRelatedStruct_sub_469570(gMapRelatedStruct, &arg0, *v19, *v18, *v16);
      self->field_10 = gta2::Weapon_sub_41C1E0(v20);
    }
    v21 = a5;
    unk_66A7E0 = 0;
    self->field_22 = a2;
    self->field_C = 0;
    self->field_8 = (int)&self->field_2350;
    self->field_20 = v11;
    self->field_21 = v21;
    self->field_23 = 16;
    self->field_24 = 16;
    self->field_1B = 66;
    gta2::S95_sub_49C820(self);
    self->field_8 = (int)&self->field_2350;
    self->field_1C = 560;
    *(_WORD *)&self->Buffer_0x2310[4486] = 0;
    self->field_2FD0 = 0;
    self->field_1E = 0;
    self->field_18 = 1;
  }
  v22 = self->field_2FD1 + 1;
  self->field_2FD1 = v22;
  if ( (unsigned __int8)v22 > 0xC8u )
  {
    self->field_2FD0 = 1;
    self->field_38 = 0;
    return 1;
  }
  if ( !self->field_C )
  {
LABEL_30:
    self->field_14 = 0;
    v35 = self->field_25;
    v36 = self->field_26;
    v37 = self->field_27;
    LOBYTE(v51.S202) = unk_66A7B4;
    LOBYTE(a7) = v35;
    LOBYTE(v51.field_0) = unk_66A7B5;
    self->field_8 = (int)&self->field_2350;
    a5 = v37;
    BYTE2(self->field_2350) = v35;
    *(_BYTE *)(self->field_8 + 3) = v36;
    S202_low = LOBYTE(v51.S202);
    *(_BYTE *)(self->field_8 + 4) = v37;
    self->field_C = 1;
    v39 = &self->Buffer_0x2310[8 * (__int16)(S202_low + 34 * LOBYTE(v51.field_0))];
    while ( 2 )
    {
      if ( *v39 == 1 )
      {
        v40 = a5 - (unsigned __int8)v39[4];
        if ( (int)((HIDWORD(v40) ^ v40) - HIDWORD(v40)) >= 1 )
        {
          self->field_1B = v39[1];
          v41 = v39[2];
          v39[1] = v39[3];
          v42 = v39[4];
          *v39 = 0;
          v39[2] = v42;
        }
        else
        {
          self->field_1B = v39[3];
          v41 = v39[4];
          *v39 = 0;
        }
      }
      else
      {
        self->field_1B = v39[1];
        v41 = v39[2];
        v39[1] = 0;
      }
      switch ( self->field_1B )
      {
        case 1:
          v39 += 272;
          ++v36;
          goto LABEL_49;
        case 2:
          v39 -= 8;
          v43 = (_BYTE)a7 - 1;
          goto LABEL_48;
        case 3:
          v39 -= 272;
          --v36;
          goto LABEL_49;
        case 4:
          v39 += 8;
          goto LABEL_47;
        case 5:
          ++v36;
          v39 += 264;
          v43 = (_BYTE)a7 - 1;
          goto LABEL_48;
        case 6:
          --v36;
          v39 -= 280;
          v43 = (_BYTE)a7 - 1;
          goto LABEL_48;
        case 7:
          --v36;
          v39 -= 264;
          goto LABEL_47;
        case 8:
          ++v36;
          v39 += 280;
LABEL_47:
          v43 = (_BYTE)a7 + 1;
LABEL_48:
          LOBYTE(a7) = v43;
LABEL_49:
          v44 = (char)a7;
          v45 = self->field_8 + 8;
          a5 = v41;
          self->field_8 = v45;
          *(_BYTE *)(v45 + 2) = v44;
          *(_BYTE *)(self->field_8 + 3) = v36;
          *(_BYTE *)(self->field_8 + 4) = v41;
          ++self->field_C;
          continue;
        case 0x42:
          v46 = self->field_C;
          if ( (unsigned __int16)v46 > 1u )
            self->field_8 -= 8;
          if ( (unsigned __int16)v46 > 0x64u )
            self->field_C = 100;
          v47 = a3;
          v48 = 0;
          v33 = self->field_C == 0;
          LOBYTE(a7) = 0;
          if ( !v33 )
          {
            do
            {
              v49 = (_BYTE *)(v47 + 2 * (unsigned __int8)a7 + (unsigned __int8)a7);
              *v49 = *(_BYTE *)(self->field_8 + 2);
              v49[1] = *(_BYTE *)(self->field_8 + 3);
              v49[2] = *(_BYTE *)(self->field_8 + 4);
              ++v48;
              self->field_8 -= 8;
              LOBYTE(a7) = v48;
            }
            while ( v48 < (unsigned int)self->field_C );
          }
          v50 = (_BYTE *)(v47 + 2 * (unsigned __int8)a7 + (unsigned __int8)a7);
          *v50 = 0;
          v50[1] = 0;
          v50[2] = 0;
          *(_BYTE *)v51.field_C = self->field_C;
          self->field_2FD0 = 1;
          self->field_38 = 0;
          self->field_2FD1 = 0;
          return 1;
        default:
          goto LABEL_57;
      }
    }
  }
  while ( 1 )
  {
    v24 = 0;
    v25 = self->field_C;
    self->field_38 = 1;
    self->field_8 = (int)&self->field_2350;
    v26 = &self->field_2350;
    if ( v25 - 1 > 0 )
    {
      do
      {
        v27 = self->field_8 + 8;
        self->field_8 = v27;
        if ( *(_WORD *)(v27 + 6) < *((_WORD *)v26 + 3) )
          v26 = (int *)v27;
        ++v24;
      }
      while ( (unsigned __int16)v24 < (unsigned __int16)self->field_C - 1 );
    }
    unk_66A7B4 = *(_BYTE *)v26;
    unk_66A7B5 = *((_BYTE *)v26 + 1);
    unk_66A7B6 = *((_BYTE *)v26 + 2);
    unk_66A7B7 = *((_BYTE *)v26 + 3);
    unk_66A7B8 = *((_BYTE *)v26 + 4);
    unk_66A7BA = *((_WORD *)v26 + 3);
    v28 = unk_66A7B4 + 34 * unk_66A7B5;
    v29 = (_BYTE *)self->field_8;
    self->field_1C = v28;
    self->field_1E = *(_WORD *)&self->Buffer_0x2310[8 * v28 + 6];
    *(_BYTE *)v26 = *v29;
    *((_BYTE *)v26 + 1) = *(_BYTE *)(self->field_8 + 1);
    *((_BYTE *)v26 + 2) = *(_BYTE *)(self->field_8 + 2);
    *((_BYTE *)v26 + 3) = *(_BYTE *)(self->field_8 + 3);
    *((_BYTE *)v26 + 4) = *(_BYTE *)(self->field_8 + 4);
    *((_WORD *)v26 + 3) = *(_WORD *)(self->field_8 + 6);
    --self->field_C;
    LOBYTE(v29) = unk_66A7B6;
    self->field_25 = unk_66A7B6;
    self->field_26 = unk_66A7B7;
    v30 = self->field_11;
    self->field_27 = unk_66A7B8;
    if ( (_BYTE)v29 == v30 && self->field_26 == self->field_12 && self->field_27 == self->field_13 )
    {
      self->field_18 = 0;
      self->field_19 = 1;
      self->field_1A = 1;
      goto LABEL_30;
    }
    self->field_20 = unk_66A7B6;
    self->field_21 = unk_66A7B7 - 1;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4;
    self->field_24 = unk_66A7B5 - 1;
    self->field_1B = 1;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6 + 1;
    self->field_21 = unk_66A7B7 - 1;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4 + 1;
    self->field_24 = unk_66A7B5 - 1;
    self->field_1B = 5;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6 + 1;
    self->field_21 = unk_66A7B7;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4 + 1;
    self->field_24 = unk_66A7B5;
    self->field_1B = 2;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6 + 1;
    self->field_21 = unk_66A7B7 + 1;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4 + 1;
    v31 = unk_66A7B5 + 1;
    self->field_1B = 6;
    self->field_24 = v31;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6;
    self->field_21 = unk_66A7B7 + 1;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4;
    self->field_24 = unk_66A7B5 + 1;
    self->field_1B = 3;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6 - 1;
    self->field_21 = unk_66A7B7 + 1;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4 - 1;
    v32 = unk_66A7B5 + 1;
    self->field_1B = 7;
    self->field_24 = v32;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6 - 1;
    self->field_21 = unk_66A7B7;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4 - 1;
    self->field_24 = unk_66A7B5;
    self->field_1B = 4;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    self->field_20 = unk_66A7B6 - 1;
    self->field_21 = unk_66A7B7 - 1;
    self->field_22 = unk_66A7B8;
    self->field_23 = unk_66A7B4 - 1;
    self->field_24 = unk_66A7B5 - 1;
    self->field_1B = 8;
    if ( gta2::S95_sub_49CF10(self) )
      goto LABEL_30;
    if ( !self->field_C )
      break;
    v33 = self->field_2E == 0;
    self->field_14 = 1;
    if ( v33 )
      return 0;
LABEL_27:
    v34 = self->field_2E;
    if ( v34 )
      self->field_2E = v34 - 1;
    if ( !self->field_18 )
      goto LABEL_30;
  }
  self->field_18 = 0;
  self->field_19 = 1;
  gta2::sub_49C9D0(self);
  if ( unk_66A7B6 )
    goto LABEL_27;
LABEL_57:
  gta2::S95_sub_49C740(self, self->Passenger1);
  return 1;
}


// 0x0049d7a0: S95::sub_49D7A0
// IDA: S95::sub_49D7A0
// Ghidra: ---
char gta2::S95_sub_49D7A0(struct S95 *self, char a2, _BYTE *a3, _BYTE *a4, unsigned __int8 *a5, char a6)
{
  char v8; // al
  unsigned __int8 v9; // cl
  int v10; // edx
  int v11; // ecx
  int *v12; // eax
  int *v13; // edi
  SpriteS1 **v14; // eax
  SpriteS1 **v15; // ebp
  int **v16; // eax
  Weapon *v17; // eax
  char v18; // dl
  char v19; // al
  __int16 v20; // cx
  bool v21; // zf
  unsigned __int8 v22; // dl
  int v23; // ecx
  int *v24; // eax
  int v25; // ebp
  unsigned __int16 v26; // cx
  unsigned __int16 v27; // cx
  _BYTE *v28; // edx
  char v29; // al
  PublicTransport *v30; // eax
  PublicTransport *v31; // eax
  S202 *v32; // eax
  PublicTransport *v33; // eax
  PublicTransport *v34; // eax
  char v35; // dl
  char v36; // cl
  char v37; // cl
  int v38; // [esp-Ch] [ebp-50h]
  char v39; // [esp+Fh] [ebp-35h]
  S202 v40; // [esp+10h] [ebp-34h] BYREF
  char v41; // [esp+30h] [ebp-14h] BYREF
  char v42; // [esp+34h] [ebp-10h] BYREF
  int v43; // [esp+38h] [ebp-Ch] BYREF
  int v44; // [esp+3Ch] [ebp-8h] BYREF
  int v45; // [esp+40h] [ebp-4h] BYREF

  v39 = 0;
  if ( self->field_38 && !a6 )
    return 0;
  if ( *a5 > 6u || !*a5 )
    return 0;
  v8 = gta2::Weapon_sub_41C1E0(&unk_66A8DC);
  self->field_27 = v8;
  self->field_26 = v8;
  self->field_25 = v8;
  self->field_28 = *a3 - 16;
  self->field_29 = *a4 - 16;
  gta2::S95_InitBuffer(self);
  self->field_E = *a3;
  self->field_F = *a4;
  v9 = *a5;
  self->field_10 = *a5;
  v10 = v9;
  v11 = (unsigned __int8)self->field_E;
  v38 = (unsigned __int8)self->field_F;
  self->field_4 = 1;
  if ( !gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v11, v38, v10) )
  {
    gta2::S202_sub_40CE30((S202 *)&v40.CarSystemManager, self->field_10);
    v13 = v12;
    gta2::S202_sub_40CE30((S202 *)&v40.S202, self->field_F);
    v15 = v14;
    gta2::S202_sub_40CE30(&v40, self->field_E);
    v17 = (Weapon *)gta2::MapRelatedStruct_sub_469570(gMapRelatedStruct, &v40.field_C, *v16, *v15, *v13);
    self->field_10 = gta2::Weapon_sub_41C1E0(v17);
  }
  *(_WORD *)&self->field_16 = 0;
  self->field_11 = 0;
  self->field_12 = 0;
  self->field_13 = 0;
  unk_66A7E0 = 0;
  v18 = self->field_E;
  v19 = self->field_F;
  self->field_22 = self->field_10;
  self->field_C = 0;
  self->field_8 = (int)&self->field_2350;
  self->field_24 = 16;
  self->field_23 = 16;
  self->field_20 = v18;
  self->field_21 = v19;
  self->field_1B = 66;
  gta2::S95_sub_49C820(self);
  v20 = *(_WORD *)&self->field_16;
  self->field_8 = (int)&self->field_2350;
  self->field_1C = 560;
  *(_WORD *)&self->Buffer_0x2310[4486] = v20;
  v21 = self->field_C == 0;
  self->field_1E = 0;
  self->field_18 = 1;
  if ( !v21 )
  {
    while ( 1 )
    {
      if ( !self->field_C )
        return 0;
      v22 = 0;
      v23 = (unsigned __int16)self->field_C - 1;
      v24 = &self->field_2350;
      self->field_8 = (int)&self->field_2350;
      if ( v23 > 0 )
      {
        do
        {
          v25 = self->field_8 + 8;
          self->field_8 = v25;
          if ( *(_WORD *)(v25 + 6) < *((_WORD *)v24 + 3) )
            v24 = (int *)v25;
          ++v22;
          v26 = self->field_C;
          LOBYTE(v40.field_0) = v22;
        }
        while ( v22 < v26 - 1 );
      }
      unk_66A7B4 = *(_BYTE *)v24;
      unk_66A7B5 = *((_BYTE *)v24 + 1);
      unk_66A7B6 = *((_BYTE *)v24 + 2);
      unk_66A7B7 = *((_BYTE *)v24 + 3);
      unk_66A7B8 = *((_BYTE *)v24 + 4);
      unk_66A7BA = *((_WORD *)v24 + 3);
      v27 = unk_66A7B4 + 34 * unk_66A7B5;
      v28 = (_BYTE *)self->field_8;
      self->field_1C = v27;
      self->field_1E = *(_WORD *)&self->Buffer_0x2310[8 * v27 + 6];
      *(_BYTE *)v24 = *v28;
      *((_BYTE *)v24 + 1) = *(_BYTE *)(self->field_8 + 1);
      *((_BYTE *)v24 + 2) = *(_BYTE *)(self->field_8 + 2);
      *((_BYTE *)v24 + 3) = *(_BYTE *)(self->field_8 + 3);
      *((_BYTE *)v24 + 4) = *(_BYTE *)(self->field_8 + 4);
      *((_WORD *)v24 + 3) = *(_WORD *)(self->field_8 + 6);
      --self->field_C;
      self->field_25 = unk_66A7B6;
      self->field_26 = unk_66A7B7;
      LOBYTE(v27) = unk_66A7B8;
      self->field_27 = unk_66A7B8;
      v29 = gta2::MapRelatedStruct_sub_420420(
              gMapRelatedStruct,
              (unsigned __int8)self->field_25,
              (unsigned __int8)self->field_26,
              (unsigned __int8)v27 - 1);
      if ( a2 == 5 )
        break;
      if ( v29 == a2 )
      {
        if ( a2 != 1 )
          goto LABEL_16;
        if ( (*(_BYTE *)(gta2::MapRelatedStruct_sub_4653C0(
                           gMapRelatedStruct,
                           (unsigned __int8)self->field_25,
                           (unsigned __int8)self->field_26,
                           (unsigned __int8)self->field_27 - 1)
                       + 10) & 0xF) != 0 )
        {
          v37 = self->field_25;
          self->field_18 = 0;
          *a3 = v37;
          *a4 = self->field_26;
          *a5 = self->field_27;
          return 1;
        }
      }
LABEL_17:
      self->field_20 = unk_66A7B6;
      self->field_21 = unk_66A7B7 - 1;
      self->field_22 = unk_66A7B8;
      self->field_23 = unk_66A7B4;
      self->field_24 = unk_66A7B5 - 1;
      self->field_1B = 1;
      if ( gta2::S95_sub_49CF10(self) )
        return 0;
      self->field_20 = unk_66A7B6 + 1;
      self->field_21 = unk_66A7B7;
      self->field_22 = unk_66A7B8;
      self->field_23 = unk_66A7B4 + 1;
      self->field_24 = unk_66A7B5;
      self->field_1B = 2;
      if ( gta2::S95_sub_49CF10(self) )
        return 0;
      self->field_20 = unk_66A7B6;
      self->field_21 = unk_66A7B7 + 1;
      self->field_22 = unk_66A7B8;
      self->field_23 = unk_66A7B4;
      v36 = unk_66A7B5 + 1;
      self->field_1B = 3;
      self->field_24 = v36;
      if ( gta2::S95_sub_49CF10(self) )
        return 0;
      self->field_20 = unk_66A7B6 - 1;
      self->field_21 = unk_66A7B7;
      self->field_22 = unk_66A7B8;
      self->field_23 = unk_66A7B4 - 1;
      self->field_24 = unk_66A7B5;
      self->field_1B = 4;
      if ( gta2::S95_sub_49CF10(self) )
        return 0;
      ++*(_WORD *)&self->field_16;
      if ( (unsigned __int8)++v39 > 6u && !a6 )
        return 0;
      if ( !self->field_18 )
        return 1;
    }
    gta2::S202_sub_40CE30((S202 *)&v40.field_C, self->field_27);
    gta2::S202_sub_40CE30((S202 *)&v40.field_10, self->field_26);
    gta2::S202_sub_401B20(&unk_66AA40, (SpriteS1 *)&v40.pPlayer, v30);
    gta2::S202_sub_40CE30((S202 *)&v40.field_18, self->field_25);
    gta2::S202_sub_401B20(&unk_66AA40, (SpriteS1 *)&v40.field_1C, v31);
    gta2::S202_sub_40CE30((S202 *)&v41, *a5);
    v40.S202 = v32;
    gta2::S202_sub_40CE30((S202 *)&v42, *a4);
    v40.CarSystemManager = (CarSystemManager *)gta2::S202_sub_401B20(&unk_66AA40, (SpriteS1 *)&v43, v33);
    gta2::S202_sub_40CE30((S202 *)&v44, *a3);
    gta2::S202_sub_401B20(&unk_66AA40, (SpriteS1 *)&v45, v34);
    if ( gta2::MapRelatedStruct_sub_469F90(
           gMapRelatedStruct,
           (SpriteS1 *)unk_66AAC8.field_0,
           (SpriteS1 *)unk_66AA48.field_0,
           (Player *)unk_66AAC8.field_0) )
    {
      goto LABEL_17;
    }
LABEL_16:
    v35 = self->field_25;
    self->field_18 = 0;
    *a3 = v35;
    *a4 = self->field_26;
    *a5 = self->field_27;
    goto LABEL_17;
  }
  return 1;
}


// 0x0049dce0: S95::sub_49DCE0
// IDA: S95::sub_49DCE0
// Ghidra: FUN_0049dce0
void gta2::S95_sub_49DCE0(int param_1,undefined1 param_2,undefined1 param_3, undefined1 param_4,undefined4 param_5,undefined4 param_6)
{
  *(undefined1 *)(param_1 + 0x25) = param_2;
  *(undefined1 *)(param_1 + 0x26) = param_3;
  *(undefined1 *)(param_1 + 0x27) = param_4;
  FUN_0049cb60(param_5,param_6);
  return;
}



