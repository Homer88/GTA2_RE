#include "gta2_shim.h"

// Module: other, Class: PathNode
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00488f70: PathNode::sub_488F70
// IDA: PathNode::sub_488F70
// Ghidra: ---
char gta2::PathNode_sub_488F70(struct PathNode *self)
{
  struct S58 *v2; // eax
  struct S58 *v3; // eax
  struct S58 *v4; // eax
  struct S58 *v5; // eax
  struct S58 *v6; // eax
  struct S58 *v7; // eax
  struct S58 *v8; // eax
  struct S58 *v9; // eax
  struct S58 *v10; // eax
  int v11; // ecx
  struct S58 *v12; // eax
  int v13; // ecx
  struct S58 *v14; // eax
  int v15; // ecx
  struct S58 *v16; // eax
  int v17; // ecx
  struct S58 *v18; // eax
  struct S58 *v19; // eax
  struct S58 *v20; // edi
  struct S58 *v21; // edi
  int *v22; // eax
  int v23; // ecx
  struct S58 *v24; // eax
  struct S58 *v25; // eax
  struct S58 *v26; // eax
  struct S58 *v27; // eax
  int v28; // ecx
  int v29; // eax
  struct S58 *v30; // eax
  int v31; // ecx
  struct S58 *v32; // eax
  int v33; // ecx
  struct S58 *v34; // eax
  int v35; // ecx
  struct S58 *v36; // eax
  int v37; // ecx
  struct S58 *v38; // eax
  int v39; // ecx
  struct S58 *v40; // eax
  int v41; // ecx
  struct S58 *v42; // eax
  int v43; // ecx
  struct S58 *v44; // eax
  int v45; // ecx
  struct S58 *v46; // eax
  int v47; // ecx
  struct S58 *v48; // eax
  int v49; // ecx
  struct S58 *v50; // eax
  int v51; // ecx
  struct S58 *v52; // eax
  __int16 v53; // dx
  int v54; // ebp
  struct S58 *v55; // edi
  int v56; // edx
  struct SpriteS1 *FirstElement; // eax
  int v58; // eax
  int v60; // [esp+10h] [ebp-10h] BYREF
  int v61; // [esp+14h] [ebp-Ch] BYREF
  char v62; // [esp+18h] [ebp-8h] BYREF
  char v63; // [esp+1Ch] [ebp-4h] BYREF

  v2 = gta2::PathNode_sub_488180(self, 147, 144);
  sub_488060(v2, 4);
  v3 = gta2::PathNode_sub_488180(self, 250, 253);
  sub_488060(v3, 4);
  v4 = gta2::PathNode_sub_488180(self, 120, 121);
  sub_488060(v4, 4);
  v5 = gta2::PathNode_sub_488180(self, 117, 118);
  sub_488060(v5, 4);
  v6 = gta2::PathNode_sub_488180(self, 146, 144);
  sub_488060(v6, 3);
  v7 = gta2::PathNode_sub_488180(self, 249, 253);
  sub_488060(v7, 3);
  v8 = gta2::PathNode_sub_488180(self, 119, 121);
  sub_488060(v8, 3);
  v9 = gta2::PathNode_sub_488180(self, 116, 118);
  sub_488060(v9, 3);
  v10 = gta2::PathNode_sub_488180(self, 145, 144);
  sub_488060(v10, 5);
  *(_BYTE *)(v11 + 100) = 3;
  v12 = gta2::PathNode_sub_488180(self, 124, 253);
  sub_488060(v12, 5);
  *(_BYTE *)(v13 + 100) = 3;
  v14 = gta2::PathNode_sub_488180(self, 125, 121);
  sub_488060(v14, 5);
  *(_BYTE *)(v15 + 100) = 3;
  v16 = gta2::PathNode_sub_488180(self, 126, 118);
  sub_488060(v16, 5);
  *(_BYTE *)(v17 + 100) = 3;
  v18 = gta2::PathNode_sub_488180(self, 154, 254);
  if ( !do_show_imaginary )
    v18->field_40 = 2;
  gta2::PathNode_sub_488180(self, 265, 254);
  v19 = gta2::PathNode_sub_488180(self, 159, 128);
  if ( !do_show_imaginary )
    v19->field_40 = 2;
  gta2::PathNode_sub_488180(self, 277, 254);
  v20 = gta2::PathNode_sub_488180(self, 110, 155);
  v20->field_38 = 110;
  v20->field_3C = 110;
  v20->field_54 = 2;
  gta2::sub_487F60(v20, unk_669AC0, unk_669AC0, unk_669AAC);
  v20->field_18 = (int)byte_66921C;
  v20->field_40 = 2 - (do_show_imaginary != 0);
  v20->field_44 = 2;
  v20->field_58 = 1;
  v20->field_50 = 1;
  v21 = gta2::PathNode_sub_488180(self, 127, 155);
  v21->field_38 = 0;
  v21->field_3C = 0;
  v21->field_54 = 2;
  v60 = 8;
  v61 = 8;
  v60 = (int)gta2::sub_401BD0(&unk_665B88, (struct SpriteS1 *)&v62, &v60);
  v22 = (int *)gta2::sub_401BD0(&unk_665B88, (struct SpriteS1 *)&v63, &v61);
  gta2::sub_487F60(v21, *v22, *(_DWORD *)v60, unk_669AAC);
  v21->field_18 = (int)byte_66921C;
  v23 = 2 - (do_show_imaginary != 0);
  v21->field_44 = 2;
  v21->field_40 = v23;
  v21->field_58 = 1;
  v21->field_50 = 1;
  v24 = gta2::PathNode_sub_488180(self, 193, 192);
  v24->field_38 = 0;
  v24->field_3C = 0;
  if ( !do_show_imaginary )
    v24->field_40 = 2;
  v25 = gta2::PathNode_sub_488180(self, 185, 163);
  v25->field_38 = 184;
  v25->field_3C = 184;
  v25->field_44 = 4;
  v25->field_40 = 3;
  v25->byte_ = 1;
  v26 = gta2::PathNode_sub_488180(self, 184, 163);
  v26->field_38 = 185;
  v26->field_3C = 164;
  v26->field_65 = 100;
  v26->byte_ = 1;
  v26->field_34 = 2;
  v26->field_6C = 1;
  v26->field_64 = 1;
  v26->field_40 = 3;
  v26->field_44 = 5;
  v27 = gta2::PathNode_sub_488180(self, 176, 163);
  sub_488060(v27, 1);
  *(_DWORD *)(v28 + 56) = 177;
  *(_DWORD *)(v28 + 60) = 177;
  if ( do_kill_phones_on_answer )
  {
    v29 = gta2::PathNode_sub_488170(self, 164);
    *(_DWORD *)(v29 + 56) = 174;
    *(_DWORD *)(v29 + 60) = 174;
  }
  v30 = gta2::PathNode_sub_488180(self, 177, 164);
  sub_488060(v30, 1);
  if ( !do_kill_phones_on_answer )
  {
    *(_DWORD *)(v31 + 56) = 187;
    *(_DWORD *)(v31 + 60) = 187;
  }
  v32 = gta2::PathNode_sub_488180(self, 187, 185);
  sub_488060(v32, 1);
  *(_DWORD *)(v33 + 56) = 186;
  *(_DWORD *)(v33 + 60) = 186;
  v34 = gta2::PathNode_sub_488180(self, 186, 184);
  sub_488060(v34, 1);
  *(_DWORD *)(v35 + 56) = 187;
  *(_DWORD *)(v35 + 60) = 177;
  v36 = gta2::PathNode_sub_488180(self, 178, 163);
  sub_488060(v36, 2);
  *(_DWORD *)(v37 + 56) = 179;
  *(_DWORD *)(v37 + 60) = 179;
  v38 = gta2::PathNode_sub_488180(self, 179, 164);
  sub_488060(v38, 2);
  if ( !do_kill_phones_on_answer )
  {
    *(_DWORD *)(v39 + 56) = 189;
    *(_DWORD *)(v39 + 60) = 189;
  }
  v40 = gta2::PathNode_sub_488180(self, 189, 185);
  sub_488060(v40, 2);
  *(_DWORD *)(v41 + 56) = 188;
  *(_DWORD *)(v41 + 60) = 188;
  v42 = gta2::PathNode_sub_488180(self, 188, 184);
  sub_488060(v42, 2);
  *(_DWORD *)(v43 + 56) = 189;
  *(_DWORD *)(v43 + 60) = 179;
  v44 = gta2::PathNode_sub_488180(self, 180, 163);
  sub_488060(v44, 0);
  *(_DWORD *)(v45 + 56) = 181;
  *(_DWORD *)(v45 + 60) = 181;
  v46 = gta2::PathNode_sub_488180(self, 181, 164);
  sub_488060(v46, 0);
  if ( !do_kill_phones_on_answer )
  {
    *(_DWORD *)(v47 + 56) = 191;
    *(_DWORD *)(v47 + 60) = 191;
  }
  v48 = gta2::PathNode_sub_488180(self, 191, 185);
  sub_488060(v48, 0);
  *(_DWORD *)(v49 + 56) = 190;
  *(_DWORD *)(v49 + 60) = 190;
  v50 = gta2::PathNode_sub_488180(self, 190, 184);
  sub_488060(v50, 0);
  *(_DWORD *)(v51 + 56) = 191;
  *(_DWORD *)(v51 + 60) = 181;
  gta2::PathNode_sub_488180(self, 174, 163)->field_44 = 0;
  v52 = gta2::PathNode_sub_488180(self, 182, 183);
  v52->field_38 = 183;
  v52->field_34 = 2;
  v52->field_44 = 2;
  v52->field_14 = unk_665BF8;
  v53 = v52->field_6C - 1;
  v52->field_10 = unk_665BF8;
  v52->field_4C = 0;
  v52->field_50 = 0;
  v52->field_64 = 8;
  gta2::sub_4880A0(v52, v53, 1);
  v54 = 200;
  v60 = 45;
  do
  {
    v55 = gta2::PathNode_sub_488180(self, v54 - 136, v54);
    v56 = v55->field_34;
    v55->field_38 = v54;
    v55->field_34 = 2 * (v56 != 6) + 7;
    FirstElement = gta2::JustCopyByPtrAtoC(&unk_665B54, (struct SpriteS1 *)&v63)->FirstElement;
    v55->field_4C = 1;
    v55->field_14 = (int)FirstElement;
    v58 = v60;
    v55->field_50 = 1;
    v55->byte_ = 1;
    v55->field_58 = 1;
    v55->field_40 = 3;
    ++v54;
    v55->field_18 = unk_665B50;
    v55->field_10 = *(_DWORD *)&stru_66923C.field_1C;
    v60 = v58 - 1;
  }
  while ( v58 != 1 );
  return sub_488F10(self);
}


// 0x00489530: PathNode::sub_489530
// IDA: PathNode::sub_489530
// Ghidra: ---
__int16 gta2::PathNode_sub_489530(struct PathNode *self)
{
  __int16 result; // ax
  int v2; // ecx

  gta2::PathNode_sub_488450(self);
  gta2::PathNode_sub_4884B0(self);
  gta2::PathNode_sub_488570(self);
  gta2::PathNode_sub_488D10(self);
  gta2::PathNode_sub_488F70(self);
  result = *(_WORD *)(gta2::PathNode_sub_488170(self, 112) + 30);
  *(_WORD *)(v2 + 36004) = result;
  return result;
}



