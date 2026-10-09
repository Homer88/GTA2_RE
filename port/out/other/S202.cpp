#include "gta2_shim.h"

// Module: other, Class: S202
// Functions: 11
// Source: unified (IDA+Ghidra)

// 0x004c3c70: S202::sub_4C3C70
// IDA: S202::sub_4C3C70
// Ghidra: ---
GameObject * gta2::S202_sub_4C3C70(struct S202 *self, unsigned __int8 a2, int *a4, int arg8, SpriteS1 *pSpriteS1_4)
{
  unsigned __int8 v5; // bl
  int *v7; // ecx
  unsigned __int8 v8; // bp
  int *v9; // ebp
  int v10; // edi
  CarSystemManager *v11; // eax
  Player *v12; // eax
  int *v13; // eax
  int v14; // edx
  int *v15; // ebp
  CarSystemManager *v16; // eax
  Player *v17; // eax
  SpriteS1 *v18; // eax
  int *v19; // eax
  int v20; // edx
  CarSystemManager *v21; // eax
  int *v22; // eax
  int *v23; // edi
  Player *v24; // eax
  int *v25; // eax
  int v26; // eax
  int v27; // edi
  Weapon *v28; // eax
  int v29; // ebp
  S202 *v30; // eax
  int *v31; // eax
  int v32; // edx
  CarSystemManager *v33; // eax
  S202 *v34; // eax
  SpriteS1 *v35; // eax
  int *v36; // eax
  int v37; // edx
  EventHandler *v38; // eax
  int *v39; // eax
  int *v40; // edi
  S202 *v41; // eax
  int *v42; // eax
  int v43; // eax
  SpriteS1 *v44; // eax
  int *v45; // ebp
  Player *v46; // eax
  int v47; // edi
  int *v48; // eax
  int v49; // ecx
  int *v50; // ebp
  Player *v51; // eax
  SpriteS1 *v52; // eax
  int *v53; // eax
  int v54; // edx
  EventHandler *v55; // eax
  Player *v56; // eax
  int *v57; // ebp
  int *v58; // eax
  Weapon *v59; // eax
  int v60; // edi
  S202 *v61; // eax
  int v62; // ebp
  int *v63; // eax
  int v64; // ecx
  S202 *v65; // eax
  SpriteS1 *v66; // eax
  int *v67; // eax
  int v68; // ecx
  EventHandler *v69; // eax
  S202 *v70; // eax
  int *v71; // edi
  int *v72; // eax
  Player *v73; // eax
  Player *v74; // eax
  int *v75; // edi
  Player *v76; // eax
  int *v77; // eax
  int v78; // edx
  Player *v79; // eax
  int *v80; // edi
  S202 *v81; // eax
  int *v82; // eax
  int v83; // ecx
  S202 *v84; // eax
  int *v85; // edi
  S202 *v86; // eax
  int *v87; // eax
  int v88; // edx
  S202 *v89; // eax
  int *v90; // edi
  Player *v91; // eax
  int *v92; // eax
  int v93; // edx
  unsigned __int8 v94; // al
  int v95; // edi
  SpriteS1 *v96; // eax
  Player *v97; // eax
  SpriteS1 *v98; // eax
  S202 *v99; // eax
  SpriteS1 *v100; // eax
  int v101; // eax
  int v102; // eax
  Player *v103; // eax
  SpriteS1 *v104; // eax
  int *v105; // ebp
  S202 *v106; // eax
  int *v107; // eax
  int v108; // ecx
  int v109; // edi
  int v110; // ebp
  SpriteS1 *v111; // eax
  S202 *v112; // eax
  SpriteS1 *v113; // eax
  S202 *v114; // eax
  SpriteS1 *v115; // eax
  int v116; // eax
  int v117; // eax
  S202 *v118; // eax
  SpriteS1 *v119; // eax
  S202 *v120; // eax
  int *v121; // eax
  int v122; // edx
  int v123; // edi
  int v124; // ebp
  SpriteS1 *v125; // eax
  S202 *v126; // eax
  SpriteS1 *v127; // eax
  S202 *v128; // eax
  SpriteS1 *v129; // eax
  int v130; // eax
  int v131; // eax
  S202 *v132; // eax
  SpriteS1 *v133; // eax
  S202 *v134; // eax
  int *v135; // eax
  int v136; // edx
  GameObject *result; // eax
  int v138; // esi
  int v139; // ebx
  SpriteS1 *v140; // eax
  S202 *v141; // eax
  SpriteS1 *v142; // eax
  Player *v143; // eax
  SpriteS1 *v144; // eax
  int v145; // eax
  S202 *v146; // eax
  SpriteS1 *v147; // eax
  int *v148; // edi
  Player *v149; // eax
  int *v150; // eax
  int v151; // edx
  S202 *pS202_1; // [esp-8h] [ebp-50h] BYREF
  S202 *v153; // [esp-4h] [ebp-4Ch] BYREF
  int v154; // [esp+10h] [ebp-38h]
  S202 pS202; // [esp+14h] [ebp-34h] BYREF
  int v156; // [esp+34h] [ebp-14h] BYREF
  int v157; // [esp+38h] [ebp-10h] BYREF
  int v158; // [esp+3Ch] [ebp-Ch] BYREF
  int v159; // [esp+40h] [ebp-8h] BYREF
  int v160; // [esp+44h] [ebp-4h] BYREF

  v5 = (unsigned __int8)a4;
  v153 = self;
  gta2::S202_sub_40CE30((S202 *)&v153, (unsigned __int8)a4);
  pS202_1 = (S202 *)v7;
  gta2::S202_sub_40CE30((S202 *)&pS202_1, a2);
  gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, (int *)&a4, &pS202_1->field_0, v153);
  LOBYTE(v154) = gta2::Weapon_sub_41C1E0((Weapon *)&a4) - 1;
  v8 = v154;
  LOBYTE(pS202.S202) = (_BYTE)pSpriteS1_4 + v5;
  LOBYTE(pS202.field_C) = a2 - 1;
  if ( gta2::MapRelatedStruct_sub_42A8C0(gMapRelatedStruct, a2 - 1, (_BYTE)pSpriteS1_4 + v5 - 1, v154) )
  {
    pS202.CarSystemManager = (CarSystemManager *)a4;
    v9 = (int *)gta2::S202_sub_401B20((S202 *)&pS202.CarSystemManager, (SpriteS1 *)&pS202.pPlayer, &unk_672564);
    v10 = ((unsigned __int8)pSpriteS1_4 >> 1) + v5;
    LOWORD(v11) = gta2::bitShiftLeft1(&pS202.field_10, v10);
    pS202.CarSystemManager = v11;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = &pS202;
    gta2::S202_sub_40CE30((S202 *)&pS202.field_18, a2);
    v13 = (int *)gta2::Player_sub_401B40(v12, pS202_1, (int)v153);
    LOWORD(v14) = unk_672308;
    gta2::Object_SpawnObject(gObject, 170, *v13, *(_DWORD *)pS202.CarSystemManager, *v9, v14);
    pS202.CarSystemManager = (CarSystemManager *)a4;
    v15 = (int *)gta2::S202_sub_401B20((S202 *)&pS202.CarSystemManager, (SpriteS1 *)&pS202.field_18, &unk_672564);
    LOWORD(v16) = gta2::bitShiftLeft1(&pS202.pPlayer, v10);
    pS202.CarSystemManager = v16;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&pS202.field_1C;
    gta2::S202_sub_40CE30(&pS202, a2);
    v18 = gta2::Player_sub_401B40(v17, (S202 *)&pS202.field_10, (int)&unk_67253C);
    v19 = (int *)gta2::Player_sub_401B40((Player *)v18, pS202_1, (int)v153);
    LOWORD(v20) = unk_672308;
    v21 = (CarSystemManager *)gta2::Object_SpawnObject(gObject, 255, *v19, *(_DWORD *)pS202.CarSystemManager, *v15, v20);
    LOBYTE(v153) = 0;
    self->CarSystemManager_ = v21;
    gta2::S63_sub_483C20((EventHandler *)v21, (byte)v153);
    LOWORD(v22) = gta2::bitShiftLeft1(&pS202.field_1C, v10);
    v23 = v22;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&pS202.field_18;
    gta2::S202_sub_40CE30((S202 *)&pS202.pPlayer, a2);
    v25 = (int *)gta2::Player_sub_401B40(v24, pS202_1, (int)v153);
    v26 = gta2::S115_sub_469010(gS115, *v25, *v23, (int)a4, 16711680, (int)unk_6722A0.FirstElement, 0xC8u);
    v8 = v154;
    self->field_18 = v26;
  }
  else
  {
    self->CarSystemManager_ = 0;
  }
  LOBYTE(pS202.field_0) = arg8 + a2;
  if ( gta2::MapRelatedStruct_sub_42A8C0(gMapRelatedStruct, arg8 + a2, v5, v8) )
  {
    pS202.CarSystemManager = (CarSystemManager *)a4;
    pS202.CarSystemManager = (CarSystemManager *)gta2::S202_sub_401B20(
                                                   (S202 *)&pS202.CarSystemManager,
                                                   (SpriteS1 *)&pS202.field_1C,
                                                   &unk_672564);
    v27 = ((unsigned __int8)pSpriteS1_4 >> 1) + v5;
    LOWORD(v28) = gta2::bitShiftLeft1(&pS202.field_18, v27);
    pS202.field_10 = v28;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&pS202.pPlayer;
    v29 = a2 + (unsigned __int8)arg8;
    LOWORD(v30) = gta2::bitShiftLeft1(&v156, v29);
    v31 = (int *)gta2::S202_sub_401B20(v30, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    LOWORD(v32) = unk_672508.Index;
    gta2::Object_SpawnObject(gObject, 170, *v31, *(_DWORD *)pS202.field_10, *(_DWORD *)pS202.CarSystemManager, v32);
    pS202.field_10 = (Weapon *)a4;
    pS202.field_10 = (Weapon *)gta2::S202_sub_401B20((S202 *)&pS202.field_10, (SpriteS1 *)&v156, &unk_672564);
    LOWORD(v33) = gta2::bitShiftLeft1(&pS202.field_1C, v27);
    pS202.CarSystemManager = v33;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&v157;
    LOWORD(v34) = gta2::bitShiftLeft1(&pS202.pPlayer, v29);
    v35 = gta2::S202_sub_401B20(v34, (SpriteS1 *)&pS202.field_18, (PublicTransport *)&unk_67253C);
    v36 = (int *)gta2::S202_sub_401B20((S202 *)v35, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    LOWORD(v37) = unk_672508.Index;
    v38 = gta2::Object_SpawnObject(gObject, 255, *v36, *(_DWORD *)pS202.CarSystemManager, *(_DWORD *)pS202.field_10, v37);
    LOBYTE(v153) = 0;
    self->field_C = (int)v38;
    gta2::S63_sub_483C20(v38, (byte)v153);
    pS202.field_10 = (Weapon *)a4;
    pS202.field_10 = (Weapon *)gta2::S202_sub_401B20((S202 *)&pS202.field_10, (SpriteS1 *)&v157, &unk_672564);
    LOWORD(v39) = gta2::bitShiftLeft1(&v156, v27);
    v40 = v39;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&pS202.field_1C;
    LOWORD(v41) = gta2::bitShiftLeft1(&pS202.field_18, v29);
    v42 = (int *)gta2::S202_sub_401B20(v41, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    v43 = gta2::S115_sub_469010(gS115, *v42, *v40, *(_DWORD *)pS202.field_10, 16711680, (int)unk_6722A0.FirstElement, 0xC8u);
    v8 = v154;
    *(_DWORD *)&self->field_1C = v43;
  }
  else
  {
    self->field_C = 0;
  }
  LOBYTE(pS202.CarSystemManager) = v5 - 1;
  if ( gta2::MapRelatedStruct_sub_42A8C0(gMapRelatedStruct, a2, v5 - 1, v8) )
  {
    pS202.field_10 = (Weapon *)a4;
    v44 = gta2::S202_sub_401B20((S202 *)&pS202.field_10, (SpriteS1 *)&v157, &unk_672564);
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&v156;
    v45 = (int *)v44;
    gta2::S202_sub_40CE30((S202 *)&pS202.field_1C, v5);
    pS202.field_10 = (Weapon *)gta2::Player_sub_401B40(v46, pS202_1, (int)v153);
    v47 = ((unsigned __int8)arg8 >> 1) + a2;
    LOWORD(v48) = gta2::bitShiftLeft1(&pS202.field_18, v47);
    LOWORD(v49) = unk_6723DC.Index;
    gta2::Object_SpawnObject(gObject, 170, *v48, *(_DWORD *)pS202.field_10, *v45, v49);
    pS202.field_10 = (Weapon *)a4;
    v50 = (int *)gta2::S202_sub_401B20((S202 *)&pS202.field_10, (SpriteS1 *)&v157, &unk_672564);
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&pS202.pPlayer;
    gta2::S202_sub_40CE30((S202 *)&pS202.field_1C, v5);
    v52 = gta2::Player_sub_401B40(v51, (S202 *)&v156, (int)&unk_67253C);
    pS202.field_10 = (Weapon *)gta2::Player_sub_401B40((Player *)v52, pS202_1, (int)v153);
    LOWORD(v53) = gta2::bitShiftLeft1(&v158, v47);
    LOWORD(v54) = unk_6723DC.Index;
    v55 = gta2::Object_SpawnObject(gObject, 255, *v53, *(_DWORD *)pS202.field_10, *v50, v54);
    LOBYTE(v153) = 1;
    self->field_0 = (int)v55;
    gta2::S63_sub_483C20(v55, (byte)v153);
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&v158;
    gta2::S202_sub_40CE30((S202 *)&v157, v5);
    v57 = (int *)gta2::Player_sub_401B40(v56, pS202_1, (int)v153);
    LOWORD(v58) = gta2::bitShiftLeft1(&v159, v47);
    v59 = (Weapon *)gta2::S115_sub_469010(gS115, *v58, *v57, (int)a4, 65280, (int)unk_6722A0.FirstElement, 0xC8u);
    v8 = v154;
    self->field_10 = v59;
  }
  else
  {
    self->field_0 = 0;
  }
  if ( gta2::MapRelatedStruct_sub_42A8C0(gMapRelatedStruct, LOBYTE(pS202.field_0) - 1, (unsigned __int8)pS202.S202, v8) )
  {
    pS202.field_10 = (Weapon *)a4;
    pS202.field_10 = (Weapon *)gta2::S202_sub_401B20((S202 *)&pS202.field_10, (SpriteS1 *)&v159, &unk_672564);
    v60 = v5 + (unsigned __int8)pSpriteS1_4;
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&v158;
    LOWORD(v61) = gta2::bitShiftLeft1(&v157, v60);
    pS202.pPlayer = (Player *)gta2::S202_sub_401B20(v61, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    v62 = ((unsigned __int8)arg8 >> 1) + a2;
    LOWORD(v63) = gta2::bitShiftLeft1(&v156, v62);
    LOWORD(v64) = unk_672230.Index;
    gta2::Object_SpawnObject(gObject, 170, *v63, (int)pS202.pPlayer->CurrentPlayer, *(_DWORD *)pS202.field_10, v64);
    pS202.pPlayer = (Player *)a4;
    pS202.pPlayer = (Player *)gta2::S202_sub_401B20((S202 *)&pS202.pPlayer, (SpriteS1 *)&v159, &unk_672564);
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&pS202.field_1C;
    LOWORD(v65) = gta2::bitShiftLeft1(&v157, v60);
    v66 = gta2::S202_sub_401B20(v65, (SpriteS1 *)&v158, (PublicTransport *)&unk_67253C);
    pS202.field_10 = (Weapon *)gta2::S202_sub_401B20((S202 *)v66, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    LOWORD(v67) = gta2::bitShiftLeft1(&pS202.field_18, v62);
    LOWORD(v68) = unk_672230.Index;
    v69 = gta2::Object_SpawnObject(gObject, 255, *v67, *(_DWORD *)pS202.field_10, (int)pS202.pPlayer->CurrentPlayer, v68);
    LOBYTE(v153) = 1;
    self->S202_ = (S202 *)v69;
    gta2::S63_sub_483C20(v69, (byte)v153);
    v153 = (S202 *)&unk_6724E4;
    pS202_1 = (S202 *)&v159;
    LOWORD(v70) = gta2::bitShiftLeft1(&v158, v60);
    v71 = (int *)gta2::S202_sub_401B20(v70, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    LOWORD(v72) = gta2::bitShiftLeft1(&v160, v62);
    v73 = (Player *)gta2::S115_sub_469010(gS115, *v72, *v71, (int)a4, 65280, (int)unk_6722A0.FirstElement, 0xC8u);
    v8 = v154;
    self->pPlayer = v73;
  }
  else
  {
    self->S202_ = 0;
  }
  if ( (self->CarSystemManager_ || self->field_0)
    && gta2::MapRelatedStruct_sub_433530(gMapRelatedStruct, pS202.field_C, (unsigned __int8)pS202.CarSystemManager, v8) )
  {
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v160;
    gta2::S202_sub_40CE30((S202 *)&v159, v5);
    v75 = (int *)gta2::Player_sub_401B40(v74, pS202_1, (int)v153);
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v158;
    gta2::S202_sub_40CE30((S202 *)&v157, a2);
    v77 = (int *)gta2::Player_sub_401B40(v76, pS202_1, (int)v153);
    LOWORD(v78) = unk_672230.Index;
    gta2::Object_SpawnObject(gObject, 258, *v77, *v75, (int)a4, v78);
  }
  if ( (self->field_C || self->field_0)
    && gta2::MapRelatedStruct_sub_433530(gMapRelatedStruct, pS202.field_0, (unsigned __int8)pS202.CarSystemManager, v8) )
  {
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v160;
    gta2::S202_sub_40CE30((S202 *)&v159, v5);
    v80 = (int *)gta2::Player_sub_401B40(v79, pS202_1, (int)v153);
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v158;
    LOWORD(v81) = gta2::bitShiftLeft1(&v157, (unsigned __int8)arg8 + a2);
    v82 = (int *)gta2::S202_sub_401B20(v81, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    LOWORD(v83) = unk_672230.Index;
    gta2::Object_SpawnObject(gObject, 258, *v82, *v80, (int)a4, v83);
  }
  if ( (self->field_C || self->S202_)
    && gta2::MapRelatedStruct_sub_433530(gMapRelatedStruct, pS202.field_0, (unsigned __int8)pS202.S202, v8) )
  {
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v160;
    LOWORD(v84) = gta2::bitShiftLeft1(&v159, (unsigned __int8)pSpriteS1_4 + v5);
    v85 = (int *)gta2::S202_sub_401B20(v84, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v158;
    LOWORD(v86) = gta2::bitShiftLeft1(&v157, (unsigned __int8)arg8 + a2);
    v87 = (int *)gta2::S202_sub_401B20(v86, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    LOWORD(v88) = unk_672230.Index;
    gta2::Object_SpawnObject(gObject, 258, *v87, *v85, (int)a4, v88);
  }
  if ( (self->CarSystemManager_ || self->S202_)
    && gta2::MapRelatedStruct_sub_433530(gMapRelatedStruct, pS202.field_C, (unsigned __int8)pS202.S202, v8) )
  {
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v160;
    LOWORD(v89) = gta2::bitShiftLeft1(&v159, (unsigned __int8)pSpriteS1_4 + v5);
    v90 = (int *)gta2::S202_sub_401B20(v89, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
    v153 = &unk_672438;
    pS202_1 = (S202 *)&v158;
    gta2::S202_sub_40CE30((S202 *)&v157, a2);
    v92 = (int *)gta2::Player_sub_401B40(v91, pS202_1, (int)v153);
    LOWORD(v93) = unk_672230.Index;
    gta2::Object_SpawnObject(gObject, 258, *v92, *v90, (int)a4, v93);
  }
  v94 = arg8;
  if ( self->field_0 && (_BYTE)arg8 )
  {
    pS202.field_C = (unsigned __int8)arg8;
    v95 = a2;
    do
    {
      v96 = gta2::Player_sub_401B40((Player *)&a4, (S202 *)&v160, (int)&unk_672264);
      v153 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v96);
      pS202_1 = (S202 *)&unk_67252C;
      gta2::S202_sub_40CE30((S202 *)&v158, v5);
      v98 = gta2::Player_sub_401B40(v97, (S202 *)&v159, (int)pS202_1);
      pS202_1 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v98);
      gta2::S202_sub_41F980((S202 *)&v156, v95);
      v100 = gta2::S202_sub_401B20(v99, (SpriteS1 *)&v157, (PublicTransport *)&unk_672438);
      v101 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v100);
      v102 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v101, (int)pS202_1, (int)v153);
      if ( v102 && (*(_BYTE *)(v102 + 10) & 8) != 0 )
      {
        v153 = (S202 *)&unk_67252C;
        pS202_1 = (S202 *)&pS202.field_1C;
        gta2::S202_sub_40CE30((S202 *)&pS202.field_18, v5);
        v104 = gta2::Player_sub_401B40(v103, pS202_1, (int)v153);
        v153 = &unk_672438;
        pS202_1 = (S202 *)&pS202.pPlayer;
        v105 = (int *)v104;
        gta2::S202_sub_41F980((S202 *)&pS202.field_10, v95);
        v107 = (int *)gta2::S202_sub_401B20(v106, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
        LOWORD(v108) = unk_672230.Index;
        gta2::Object_SpawnObject(gObject, 122, *v107, *v105, (int)a4, v108);
      }
      ++v95;
      --pS202.field_C;
    }
    while ( pS202.field_C );
    v94 = arg8;
  }
  if ( self->S202_ && v94 )
  {
    v109 = a2;
    pS202.field_C = v94;
    v110 = v5 + (unsigned __int8)pSpriteS1_4;
    do
    {
      v111 = gta2::Player_sub_401B40((Player *)&a4, (S202 *)&v160, (int)&unk_672264);
      v153 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v111);
      pS202_1 = (S202 *)&unk_67252C;
      LOWORD(v112) = gta2::bitShiftLeft1(&v158, v110);
      v113 = gta2::S202_sub_401B20(v112, (SpriteS1 *)&v159, (PublicTransport *)pS202_1);
      pS202_1 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v113);
      gta2::S202_sub_41F980((S202 *)&v156, v109);
      v115 = gta2::S202_sub_401B20(v114, (SpriteS1 *)&v157, (PublicTransport *)&unk_672438);
      v116 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v115);
      v117 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v116, (int)pS202_1, (int)v153);
      if ( v117 && (*(_BYTE *)(v117 + 10) & 4) != 0 )
      {
        v153 = (S202 *)&unk_67252C;
        pS202_1 = (S202 *)&pS202.field_1C;
        LOWORD(v118) = gta2::bitShiftLeft1(&pS202.field_18, v110);
        v119 = gta2::S202_sub_401B20(v118, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
        v153 = &unk_672438;
        pS202_1 = (S202 *)&pS202.field_10;
        pS202.pPlayer = (Player *)v119;
        gta2::S202_sub_41F980((S202 *)&pS202.CarSystemManager, v109);
        v121 = (int *)gta2::S202_sub_401B20(v120, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
        LOWORD(v122) = unk_672230.Index;
        gta2::Object_SpawnObject(gObject, 122, *v121, (int)pS202.pPlayer->CurrentPlayer, (int)a4, v122);
      }
      ++v109;
      --pS202.field_C;
    }
    while ( pS202.field_C );
    v94 = arg8;
  }
  if ( self->field_C && (_BYTE)pSpriteS1_4 )
  {
    v123 = v5;
    arg8 = (unsigned __int8)pSpriteS1_4;
    v124 = a2 + v94;
    do
    {
      v125 = gta2::Player_sub_401B40((Player *)&a4, (S202 *)&v160, (int)&unk_672264);
      v153 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v125);
      pS202_1 = &unk_672438;
      gta2::S202_sub_41F980((S202 *)&v158, v123);
      v127 = gta2::S202_sub_401B20(v126, (SpriteS1 *)&v159, (PublicTransport *)pS202_1);
      pS202_1 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v127);
      LOWORD(v128) = gta2::bitShiftLeft1(&v156, v124);
      v129 = gta2::S202_sub_401B20(v128, (SpriteS1 *)&v157, (PublicTransport *)&unk_67252C);
      v130 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v129);
      v131 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v130, (int)pS202_1, (int)v153);
      if ( v131 && (*(_BYTE *)(v131 + 10) & 1) != 0 )
      {
        v153 = &unk_672438;
        pS202_1 = (S202 *)&pS202.field_1C;
        gta2::S202_sub_41F980((S202 *)&pS202.field_18, v123);
        v133 = gta2::S202_sub_401B20(v132, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
        v153 = (S202 *)&unk_67252C;
        pS202_1 = (S202 *)&pS202.field_10;
        pS202.pPlayer = (Player *)v133;
        LOWORD(v134) = gta2::bitShiftLeft1(&pS202.field_C, v124);
        v135 = (int *)gta2::S202_sub_401B20(v134, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
        LOWORD(v136) = unk_672508.Index;
        gta2::Object_SpawnObject(gObject, 122, *v135, (int)pS202.pPlayer->CurrentPlayer, (int)a4, v136);
      }
      ++v123;
      --arg8;
    }
    while ( arg8 );
  }
  result = (GameObject *)self->CarSystemManager_;
  if ( result )
  {
    result = (GameObject *)(unsigned __int8)pSpriteS1_4;
    if ( (_BYTE)pSpriteS1_4 )
    {
      v138 = v5;
      v139 = (unsigned __int8)pSpriteS1_4;
      do
      {
        v140 = gta2::Player_sub_401B40((Player *)&a4, (S202 *)&arg8, (int)&unk_672264);
        v153 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v140);
        pS202_1 = &unk_672438;
        gta2::S202_sub_41F980((S202 *)&v160, v138);
        v142 = gta2::S202_sub_401B20(v141, (SpriteS1 *)&pSpriteS1_4, (PublicTransport *)pS202_1);
        pS202_1 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v142);
        gta2::S202_sub_40CE30((S202 *)&v158, a2);
        v144 = gta2::Player_sub_401B40(v143, (S202 *)&v159, (int)&unk_67252C);
        v145 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v144);
        result = (GameObject *)gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v145, (int)pS202_1, (int)v153);
        if ( result )
        {
          if ( (result->field_8 & 0x20000) != 0 )
          {
            v153 = &unk_672438;
            pS202_1 = (S202 *)&v157;
            gta2::S202_sub_41F980((S202 *)&v156, v138);
            v147 = gta2::S202_sub_401B20(v146, (SpriteS1 *)pS202_1, (PublicTransport *)v153);
            v153 = (S202 *)&unk_67252C;
            pS202_1 = (S202 *)&pS202.field_1C;
            v148 = (int *)v147;
            gta2::S202_sub_40CE30((S202 *)&pS202.field_18, a2);
            v150 = (int *)gta2::Player_sub_401B40(v149, pS202_1, (int)v153);
            LOWORD(v151) = unk_672508.Index;
            result = (GameObject *)gta2::Object_SpawnObject(gObject, 122, *v150, *v148, (int)a4, v151);
          }
        }
        ++v138;
        --v139;
      }
      while ( v139 );
    }
  }
  return result;
}


// 0x004fe220: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)&unk_5E3D64, (SpriteS1 *)&unk_5E3F74, (PublicTransport *)&unk_5E3E90);
}


// 0x004ffbc0: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)&unk_5E4D4C, (SpriteS1 *)&unk_5E5040, (PublicTransport *)&unk_5E4E7C);
}


// 0x0050ca20: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: FUN_0050ca20
void gta2::S202_sub_401B20(void)
{
  gta2::S202_sub_401B20((Point2D *)&DAT_005e7528,(SpriteS1 *)&DAT_005e7794,
             (S127 *)&DAT_005e7714);
  return;
}


// 0x0050ca40: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: FUN_0050ca40
void gta2::S202_sub_401B20(void)
{
  gta2::S202_sub_401B20((Point2D *)&DAT_005e7614,(SpriteS1 *)&DAT_005e76d0,
             (S127 *)&DAT_005e7714);
  return;
}


// 0x0050ca60: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: FUN_0050ca60
void gta2::S202_sub_401B20(void)
{
  gta2::S202_sub_401B20((Point2D *)&DAT_005e7524,(SpriteS1 *)&DAT_005e761c,
             (S127 *)&DAT_005e7714);
  return;
}


// 0x0053f850: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)v0, (SpriteS1 *)&unk_66A178, (PublicTransport *)&unk_66A184);
}


// 0x00544eb0: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)&unk_66AC48, (SpriteS1 *)&unk_66AC3C, (PublicTransport *)&unk_66ADC0);
}


// 0x00544ee0: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)&MEMORY[0x66AD80], (SpriteS1 *)&unk_66ADB0, (PublicTransport *)&unk_66ADD8);
}


// 0x00544f00: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)&unk_66AF60, &unk_66B060, (PublicTransport *)&unk_66AB90);
}


// 0x005624f0: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
  return gta2::S202_sub_401B20((S202 *)&unk_672264, &unk_6722A0, (PublicTransport *)&unk_672384);
}



