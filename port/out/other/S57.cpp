#include "gta2_shim.h"

// Module: other, Class: S57
// Functions: 10
// Source: unified (IDA+Ghidra)

// 0x00488170: S57::sub_488170
// IDA: S57::sub_488170
// Ghidra: ---
int gta2::S57_sub_488170(PathNode *self, int index)
{
  return *(_DWORD *)&self->buffer_0x4B0[4 * index];
}


// 0x00488180: S57::sub_488180
// IDA: S57::sub_488180
// Ghidra: PathNode::FUN_00488180
RouteInfo * gta2::S57_sub_488180(PathNode *self,int param_1,int param_2)
{
  RouteInfo *pRVar1;
  int iVar2;
  undefined4 *puVar3;
  RouteInfo *pRVar4;
  
  pRVar1 = self->ArrayRouteInfo + (ushort)self->field0_0x0;
  *(RouteInfo **)(self->buffer_0x4B0 + param_1 * 4) = pRVar1;
  self->field0_0x0 = self->field0_0x0 + 1;
  puVar3 = *(undefined4 **)(self->buffer_0x4B0 + param_2 * 4);
  pRVar4 = pRVar1;
  for (iVar2 = 0x1d; iVar2 != 0; iVar2 = iVar2 + -1) {
    pRVar4->field0_0x0 = *puVar3;
    puVar3 = puVar3 + 1;
    pRVar4 = (RouteInfo *)&pRVar4->field1_0x4;
  }
  pRVar1->field13_0x24 = param_1;
  return pRVar1;
}


// 0x004881d0: S57::sub_4881D0
// IDA: S57::sub_4881D0
// Ghidra: PathNode::FUN_004881d0
void gta2::S57_sub_4881D0(PathNode *self,int param_1)
{
  ushort uVar1;
  
  uVar1 = self->field0_0x0;
  *(RouteInfo **)(self->buffer_0x4B0 + param_1 * 4) =
       self->ArrayRouteInfo + uVar1;
  self->field0_0x0 = self->field0_0x0 + 1;
  self->ArrayRouteInfo[uVar1].field13_0x24 = param_1;
  return;
}


// 0x00488420: S57::sub_488420
// IDA: S57::sub_488420
// Ghidra: ---
S58 * gta2::S57_sub_488420(PathNode *self, int a2, int a3, __int16 a4, unsigned __int8 a5)
{
  S58 *result; // eax

  result = gta2::S57_sub_4881D0(self, a2);
  result->field_28 = a3;
  result->field_1E = a4;
  result->field_6C = a5;
  result->field_30 = 2;
  return result;
}


// 0x00488450: S57::sub_488450
// IDA: S57::sub_488450
// Ghidra: ---
unsigned __int8 * gta2::S57_sub_488450(PathNode *self)
{
  __int16 v1; // di
  unsigned __int8 *result; // eax
  unsigned __int8 *v4; // esi
  unsigned __int16 i; // bx
  S58 *v6; // eax

  v1 = 0;
  result = (unsigned __int8 *)gta2::Style_get_obji_by_idx(gStyle, 0);
  v4 = result;
  for ( i = 1; result; ++i )
  {
    v6 = gta2::S57_sub_488420(self, *v4, 5, v1, v4[1]);
    v1 += v4[1];
    sub_487FA0(v6);
    result = (unsigned __int8 *)gta2::Style_get_obji_by_idx(gStyle, i);
    v4 = result;
  }
  return result;
}


// 0x004884b0: S57::sub_4884B0
// IDA: S57::sub_4884B0
// Ghidra: ---
void gta2::S57_sub_4884B0(PathNode *self)
{
  int v1; // esi
  _DWORD *v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int v7; // ecx

  v1 = dword_593218;
  if ( dword_593218 > 0 )
  {
    v3 = &unk_6692C8;
    do
    {
      v4 = gta2::PathNode_sub_488170(self, *(v3 - 2));
      v6 = *(_DWORD *)(v5 - 4);
      v3 = (_DWORD *)(v5 + 84);
      *(_DWORD *)(v4 + 52) = v6;
      *(_DWORD *)(v4 + 56) = *(v3 - 21);
      *(_DWORD *)(v4 + 60) = *(v3 - 21);
      *(_BYTE *)(v4 + 97) = *((_BYTE *)v3 - 80);
      *(_DWORD *)(v4 + 64) = *(v3 - 17);
      *(_DWORD *)(v4 + 68) = *(v3 - 19);
      *(_DWORD *)(v4 + 72) = *(v3 - 18);
      *(_DWORD *)(v4 + 16) = *(v3 - 16);
      *(_BYTE *)(v4 + 101) = *((_BYTE *)v3 - 56);
      *(_DWORD *)(v4 + 20) = *(v3 - 15);
      *(_DWORD *)(v4 + 76) = *(v3 - 13);
      *(_BYTE *)(v4 + 100) = *((_BYTE *)v3 - 44);
      *(_DWORD *)(v4 + 88) = *(v3 - 10);
      *(_DWORD *)(v4 + 24) = *(v3 - 9);
      *(_BYTE *)(v4 + 32) = *((_BYTE *)v3 - 28);
      *(_DWORD *)(v4 + 44) = *(v3 - 8);
      *(_BYTE *)(v4 + 96) = 1;
      v7 = *(v3 - 4);
      *(_DWORD *)(v4 + 104) = 0;
      *(_DWORD *)(v4 + 92) = v7;
      *(_DWORD *)(v4 + 112) = *(v3 - 6);
      *(_BYTE *)(v4 + 98) = *((_BYTE *)v3 - 20);
      --v1;
      *(_BYTE *)(v4 + 99) = *((_BYTE *)v3 - 12);
      *(_DWORD *)(v4 + 84) = 0;
    }
    while ( v1 );
  }
}


// 0x00488570: S57::sub_488570
// IDA: S57::sub_488570
// Ghidra: ---
int gta2::S57_sub_488570(PathNode *self)
{
  _BYTE *v2; // eax
  int v3; // ecx
  S58 *v4; // eax
  int v5; // ecx
  S58 *v6; // eax
  int v7; // ecx
  _BYTE *v8; // eax
  int v9; // ecx
  S58 *v10; // eax
  int v11; // ecx
  S58 *v12; // ebp
  S58 *v13; // eax
  S58 *v14; // ebp
  S58 *v15; // eax
  S58 *v16; // ebp
  S58 *v17; // eax
  S58 *v18; // ebp
  S58 *v19; // ebp
  S58 *v20; // eax
  S58 *v21; // ebp
  S58 *v22; // eax
  S58 *v23; // ebp
  S58 *v24; // eax
  S58 *v25; // ebp
  S58 *v26; // ebp
  S58 *v27; // eax
  S58 *v28; // ebp
  S58 *v29; // eax
  S58 *v30; // ebp
  S58 *v31; // ebp
  S58 *v32; // eax
  S58 *v33; // ebp
  S58 *v34; // ebp
  int result; // eax
  char v36[4]; // [esp+10h] [ebp-4h] BYREF

  gta2::PathNode_sub_488180(self, 151, 6);
  v2 = (_BYTE *)gta2::PathNode_sub_488170(self, 151);
  gta2::sub_4880A0(v2, 1, v2[108] - 1);
  *(_DWORD *)(v3 + 52) = 2;
  *(_BYTE *)(v3 + 100) = 5;
  *(_DWORD *)(v3 + 56) = 152;
  *(_DWORD *)(v3 + 60) = 152;
  *(_DWORD *)(v3 + 64) = 0;
  *(_DWORD *)(v3 + 68) = 0;
  *(_BYTE *)(v3 + 101) = 1;
  *(_BYTE *)(v3 + 97) = 1;
  v4 = gta2::PathNode_sub_488180(self, 152, 6);
  gta2::sub_4880A0(v4, v4->field_6C - 1, 1);
  *(_DWORD *)(v5 + 52) = 0;
  *(_DWORD *)(v5 + 56) = 0;
  *(_DWORD *)(v5 + 60) = 0;
  *(_DWORD *)(v5 + 64) = 0;
  *(_DWORD *)(v5 + 68) = 0;
  *(_BYTE *)(v5 + 97) = 0;
  v6 = gta2::PathNode_sub_488180(self, 52, 4);
  gta2::sub_4880A0(v6, v6->field_6C - 1, 1);
  *(_DWORD *)(v7 + 52) = 0;
  *(_DWORD *)(v7 + 56) = 0;
  *(_DWORD *)(v7 + 60) = 0;
  *(_DWORD *)(v7 + 64) = 0;
  *(_DWORD *)(v7 + 68) = 0;
  *(_BYTE *)(v7 + 97) = 0;
  gta2::PathNode_sub_488180(self, 50, 12);
  v8 = (_BYTE *)gta2::PathNode_sub_488170(self, 50);
  gta2::sub_4880A0(v8, 1, v8[108] - 1);
  *(_DWORD *)(v9 + 52) = 2;
  *(_BYTE *)(v9 + 100) = 3;
  *(_DWORD *)(v9 + 56) = 51;
  *(_DWORD *)(v9 + 60) = 51;
  *(_DWORD *)(v9 + 64) = 0;
  *(_DWORD *)(v9 + 68) = 0;
  *(_BYTE *)(v9 + 101) = 1;
  *(_BYTE *)(v9 + 97) = 1;
  v10 = gta2::PathNode_sub_488180(self, 51, 12);
  gta2::sub_4880A0(v10, v10->field_6C - 1, 1);
  *(_DWORD *)(v11 + 52) = 0;
  *(_DWORD *)(v11 + 56) = 0;
  *(_DWORD *)(v11 + 60) = 0;
  *(_DWORD *)(v11 + 64) = 0;
  *(_DWORD *)(v11 + 68) = 0;
  *(_BYTE *)(v11 + 97) = 0;
  v12 = gta2::PathNode_sub_488180(self, 155, 3);
  gta2::sub_4880A0(v12, 1, v12->field_6C - 1);
  v12->field_34 = 4;
  v12->field_40 = 4;
  v12->field_64 = 1;
  v12->field_38 = 53;
  v12->field_3C = 53;
  v12->field_44 = 0;
  v12->field_10 = unk_665B50;
  v12->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v12->byte_ = 1;
  v12->field_4C = 3;
  v12->field_50 = 3;
  v12->field_65 = -1;
  v12->field_58 = 1;
  v13 = gta2::PathNode_sub_488180(self, 53, 3);
  gta2::sub_4880A0(v13, v13->field_6C - 1, 1);
  v14 = gta2::PathNode_sub_488180(self, 123, 11);
  gta2::sub_4880A0(v14, 1, v14->field_6C - 1);
  v14->field_34 = 4;
  v14->field_64 = 1;
  v14->field_38 = 55;
  v14->field_3C = 55;
  v14->field_40 = 4;
  v14->field_44 = 0;
  v14->field_10 = unk_665B50;
  v14->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v14->byte_ = 1;
  v14->field_4C = 3;
  v14->field_50 = 3;
  v14->field_65 = -1;
  v14->field_58 = 1;
  v15 = gta2::PathNode_sub_488180(self, 55, 11);
  gta2::sub_4880A0(v15, v15->field_6C - 1, 1);
  v16 = gta2::PathNode_sub_488180(self, 156, 5);
  gta2::sub_4880A0(v16, 1, v16->field_6C - 1);
  v16->field_38 = 54;
  v16->field_3C = 54;
  v16->field_34 = 4;
  v16->field_64 = 1;
  v16->field_40 = 4;
  v16->field_44 = 0;
  v16->field_10 = unk_665B50;
  v16->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v16->byte_ = 1;
  v16->field_4C = 3;
  v16->field_50 = 3;
  v16->field_65 = -1;
  v16->field_58 = 1;
  v17 = gta2::PathNode_sub_488180(self, 54, 5);
  gta2::sub_4880A0(v17, v17->field_6C - 1, 1);
  v18 = gta2::PathNode_sub_488180(self, 56, 13);
  gta2::sub_4880A0(v18, 1, v18->field_6C - 1);
  v18->field_64 = 1;
  v18->field_34 = 4;
  v18->field_38 = 13;
  v18->field_3C = 13;
  v18->field_40 = 4;
  v18->field_44 = 0;
  v18->field_10 = unk_665B50;
  v18->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v18->byte_ = 1;
  v18->field_4C = 3;
  v18->field_50 = 3;
  v18->field_65 = -1;
  v18->field_58 = 1;
  v19 = gta2::PathNode_sub_488180(self, 57, 14);
  gta2::sub_4880A0(v19, 1, v19->field_6C - 1);
  v19->field_34 = 4;
  v19->field_64 = 1;
  v19->field_38 = 58;
  v19->field_3C = 58;
  v19->field_40 = 4;
  v19->field_44 = 0;
  v19->field_10 = unk_665B50;
  v19->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v19->byte_ = 1;
  v19->field_4C = 3;
  v19->field_50 = 3;
  v19->field_65 = -1;
  v19->field_58 = 1;
  v20 = gta2::PathNode_sub_488180(self, 58, 14);
  gta2::sub_4880A0(v20, v20->field_6C - 1, 1);
  v21 = gta2::PathNode_sub_488180(self, 59, 15);
  gta2::sub_4880A0(v21, 1, v21->field_6C - 1);
  v21->field_34 = 4;
  v21->field_64 = 1;
  v21->field_38 = 60;
  v21->field_3C = 60;
  v21->field_40 = 4;
  v21->field_44 = 0;
  v21->field_10 = unk_665B50;
  v21->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v21->byte_ = 1;
  v21->field_4C = 3;
  v21->field_50 = 3;
  v21->field_65 = -1;
  v21->field_58 = 1;
  v22 = gta2::PathNode_sub_488180(self, 60, 15);
  gta2::sub_4880A0(v22, v22->field_6C - 1, 1);
  v23 = gta2::PathNode_sub_488180(self, 61, 16);
  gta2::sub_4880A0(v23, 1, v23->field_6C - 1);
  v23->field_38 = 62;
  v23->field_3C = 62;
  v23->field_34 = 4;
  v23->field_64 = 1;
  v23->field_40 = 4;
  v23->field_44 = 0;
  v23->field_10 = unk_665B50;
  v23->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v23->byte_ = 1;
  v23->field_4C = 3;
  v23->field_50 = 3;
  v23->field_65 = -1;
  v23->field_58 = 1;
  v24 = gta2::PathNode_sub_488180(self, 62, 16);
  gta2::sub_4880A0(v24, v24->field_6C - 1, 1);
  v25 = gta2::PathNode_sub_488180(self, 49, 18);
  gta2::sub_4880A0(v25, 1, v25->field_6C - 1);
  v25->field_64 = 1;
  v25->field_34 = 4;
  v25->field_38 = 18;
  v25->field_3C = 18;
  v25->field_40 = 4;
  v25->field_44 = 0;
  v25->field_10 = unk_665B50;
  v25->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v25->byte_ = 1;
  v25->field_4C = 3;
  v25->field_50 = 3;
  v25->field_65 = -1;
  v25->field_58 = 1;
  v26 = gta2::PathNode_sub_488180(self, 45, 22);
  gta2::sub_4880A0(v26, 1, v26->field_6C - 1);
  v26->field_34 = 4;
  v26->field_64 = 1;
  v26->field_38 = 46;
  v26->field_3C = 46;
  v26->field_40 = 4;
  v26->field_44 = 0;
  v26->field_10 = unk_665B50;
  v26->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v26->byte_ = 1;
  v26->field_4C = 3;
  v26->field_50 = 3;
  v26->field_65 = -1;
  v26->field_58 = 1;
  v27 = gta2::PathNode_sub_488180(self, 46, 22);
  gta2::sub_4880A0(v27, v27->field_6C - 1, 1);
  v28 = gta2::PathNode_sub_488180(self, 47, 21);
  gta2::sub_4880A0(v28, 1, v28->field_6C - 1);
  v28->field_34 = 4;
  v28->field_64 = 1;
  v28->field_38 = 48;
  v28->field_3C = 48;
  v28->field_40 = 4;
  v28->field_44 = 0;
  v28->field_10 = unk_665B50;
  v28->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v28->byte_ = 1;
  v28->field_4C = 3;
  v28->field_50 = 3;
  v28->field_65 = -1;
  v28->field_58 = 1;
  v29 = gta2::PathNode_sub_488180(self, 48, 21);
  gta2::sub_4880A0(v29, v29->field_6C - 1, 1);
  v30 = gta2::PathNode_sub_488180(self, 63, 17);
  v30->field_38 = 17;
  v30->field_3C = 17;
  v30->field_34 = 3;
  v30->field_40 = 4;
  v30->field_44 = 0;
  v30->field_10 = unk_665B50;
  v30->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v30->byte_ = 1;
  v30->field_4C = 3;
  v30->field_50 = 3;
  v30->field_58 = 1;
  v31 = gta2::PathNode_sub_488180(self, 43, 23);
  gta2::sub_4880A0(v31, 1, v31->field_6C - 1);
  v31->field_38 = 44;
  v31->field_3C = 44;
  v31->field_34 = 4;
  v31->field_64 = 1;
  v31->field_40 = 4;
  v31->field_44 = 0;
  v31->field_10 = unk_665B50;
  v31->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v31->byte_ = 1;
  v31->field_4C = 3;
  v31->field_50 = 3;
  v31->field_65 = -1;
  v31->field_58 = 1;
  v32 = gta2::PathNode_sub_488180(self, 44, 23);
  gta2::sub_4880A0(v32, v32->field_6C - 1, 1);
  v33 = gta2::PathNode_sub_488180(self, 157, 7);
  v33->field_34 = 3;
  v33->field_4C = 2;
  v33->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v33->field_40 = 4;
  v33->field_38 = 7;
  v33->field_3C = 7;
  v33->field_44 = 0;
  v33->byte_ = 1;
  v33->field_58 = 1;
  v34 = gta2::PathNode_sub_488180(self, 158, 1);
  v34->field_34 = 3;
  v34->field_4C = 2;
  v34->field_14 = (int)gta2::JustCopyByPtrAtoC(&unk_665B54, (SpriteS1 *)v36)->FirstElement;
  v34->field_38 = 1;
  v34->field_3C = 1;
  v34->field_44 = 0;
  v34->byte_ = 1;
  v34->field_58 = 1;
  result = gta2::PathNode_sub_488170(self, 25);
  *(_DWORD *)(result + 40) = 1;
  *(_DWORD *)(result + 8) = unk_665C48;
  return result;
}


// 0x00488d10: S57::sub_488D10
// IDA: S57::sub_488D10
// Ghidra: ---
int gta2::S57_sub_488D10(PathNode *self)
{
  int result; // eax
  __int16 v2; // bp
  unsigned __int8 *v3; // esi
  S58 *v4; // edi
  int v5; // ecx
  int v6; // [esp+4h] [ebp-8h]

  result = dword_59321C;
  v2 = 0;
  if ( dword_59321C > 0 )
  {
    v3 = (unsigned __int8 *)&unk_665C54;
    v6 = dword_59321C;
    do
    {
      v4 = gta2::S57_sub_488420(self, *((_DWORD *)v3 - 1), 4, v2, *v3);
      v2 += *v3;
      v4->field_28 = *((_DWORD *)v3 + 13);
      if ( gta2::Player_IsCurrentPlayer((Player *)(v3 + 68), (Player *)&unk_665BF8)
        && gta2::Player_IsCurrentPlayer((Player *)(v3 + 72), (Player *)&unk_665BF8)
        && gta2::Player_IsCurrentPlayer((Player *)(v3 + 76), (Player *)&unk_665BF8) )
      {
        sub_487FA0(v4);
      }
      else
      {
        gta2::sub_487F60(v4, *((_DWORD *)v3 + 17), *((_DWORD *)v3 + 18), *((_DWORD *)v3 + 19));
      }
      v5 = *((_DWORD *)v3 + 1);
      v3 += 108;
      v4->field_34 = v5;
      v4->field_38 = *((_DWORD *)v3 - 25);
      v4->field_3C = *((_DWORD *)v3 - 24);
      v4->byte_ = *(v3 - 92);
      v4->field_40 = *((_DWORD *)v3 - 20);
      v4->field_44 = *((_DWORD *)v3 - 22);
      v4->field_48 = *((_DWORD *)v3 - 21);
      v4->field_10 = *((_DWORD *)v3 - 19);
      v4->field_65 = *(v3 - 68);
      v4->field_14 = *((_DWORD *)v3 - 18);
      v4->field_4C = *((_DWORD *)v3 - 16);
      v4->field_50 = *((_DWORD *)v3 - 15);
      v4->field_64 = *(v3 - 52);
      v4->field_54 = 0;
      v4->field_58 = *((_DWORD *)v3 - 12);
      v4->field_18 = *((_DWORD *)v3 - 11);
      v4->field_2C = *((_DWORD *)v3 - 7);
      v4->field_20 = *(v3 - 24);
      v4->field_60 = *(v3 - 23);
      v4->field_5C = *((_DWORD *)v3 - 5);
      v4->field_68 = *((_DWORD *)v3 - 4);
      v4->field_70 = *((_DWORD *)v3 - 3);
      v4->field_62 = *(v3 - 8);
      result = v6 - 1;
      v4->field_63 = *(v3 - 7);
      v6 = result;
    }
    while ( result );
  }
  return result;
}


// 0x00488eb0: S57::S57
// IDA: S57::S57
// Ghidra: ---
PathNode * gta2::S57_S57(PathNode *self)
{
  gta2::Construct(self->S58_, 116, 300, S58::S58, S58::S58_Des);
  memset(self->buffer_0x4B0, 0, sizeof(self->buffer_0x4B0));
  self->Index = 0;
  self->field_8CA4 = 99;
  return self;
}


// 0x004c6e30: S57::sub_4C6E30
// IDA: S57::sub_4C6E30
// Ghidra: ---
__int16 gta2::S57_sub_4C6E30(PathNode *self, int index)
{
  return *(_WORD *)(gta2::PathNode_sub_488170(self, index) + 30);
}



