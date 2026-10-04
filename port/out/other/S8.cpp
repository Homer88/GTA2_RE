#include "gta2_shim.h"

// Module: other, Class: S8
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x004b34e0: S8::sub_4B34E0
// IDA: S8::sub_4B34E0
// Ghidra: ---
char gta2::S8_sub_4B34E0(struct CarAudioSettings *self, SpriteS1 *a2, int a3, int a4)
{
  unsigned int v5; // ecx
  char result; // al
  int CarModelById; // eax
  int v8; // ecx
  int v9; // ebp
  struct Tango *v10; // ecx
  char *v11; // ebx
  struct SpriteS1 *FirstElement; // edi
  char v13; // al
  int *v14; // ebx
  char *v15; // ebx
  char v16; // al
  char *v17; // edi
  char v18; // al
  struct S202 *v19; // edx
  struct SpriteS1 *v20; // eax
  char v21; // al
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int MaxZForTile; // ebp
  int v26; // ecx
  char v27; // al
  struct SpriteS1 *v28; // eax
  struct SpriteS1 *v29; // eax
  int *v30; // edi
  int *v31; // ebp
  int *v32; // ebx
  int *v33; // eax
  int *v34; // edi
  int *v35; // eax
  unsigned __int8 v36; // al
  _WORD *v37; // eax
  unsigned __int8 v38; // al
  CarModel CarType; // edi
  int v40; // eax
  struct Gang *pGang; // eax
  struct Gang *v42; // edi
  struct Car *v43; // eax
  struct Player **v44; // eax
  struct SpriteS1 *v45; // eax
  struct SpriteS1 *v46; // eax
  struct SpriteS1 *v47; // eax
  struct SpriteS1 *v48; // eax
  int *v49; // edi
  int *v50; // ebx
  int *v51; // ebp
  int *v52; // eax
  int *v53; // edi
  int *v54; // eax
  struct Player **v55; // eax
  struct SpriteS1 *v56; // eax
  struct SpriteS1 *v57; // eax
  struct SpriteS1 *v58; // eax
  struct SpriteS1 *v59; // eax
  int *v60; // edi
  int *v61; // ebx
  int *v62; // ebp
  int *v63; // eax
  int *v64; // edi
  int *v65; // eax
  struct Player **v66; // eax
  struct SpriteS1 *v67; // eax
  struct SpriteS1 *v68; // eax
  struct SpriteS1 *v69; // eax
  struct SpriteS1 *v70; // eax
  int *v71; // edi
  int *v72; // ebx
  int *v73; // ebp
  int *v74; // eax
  int *v75; // edi
  int *v76; // eax
  struct Player **v77; // eax
  struct SpriteS1 *v78; // eax
  struct SpriteS1 *v79; // eax
  struct SpriteS1 *v80; // eax
  struct SpriteS1 *v81; // eax
  int *v82; // edi
  int *v83; // ebp
  int *v84; // ebx
  int *v85; // eax
  int *v86; // edi
  int *v87; // eax
  S410 *v88; // edi
  struct SpriteS1 *v89; // eax
  struct SpriteS1 *v90; // ebp
  struct SpriteS1 *v91; // eax
  struct SpriteS1 *v92; // ebx
  struct SpriteS1 *v93; // edi
  S410 *v94; // edi
  struct SpriteS1 *v95; // eax
  struct SpriteS1 *v96; // eax
  S410 *v97; // edi
  struct SpriteS1 *v98; // eax
  struct SpriteS1 *v99; // eax
  S410 *v100; // edi
  struct SpriteS1 *v101; // eax
  struct SpriteS1 *v102; // eax
  S410 *v103; // edi
  struct SpriteS1 *v104; // eax
  struct SpriteS1 *v105; // eax
  struct SpriteS1 *v106; // eax
  struct SpriteS1 *v107; // eax
  struct SpriteS1 *v108; // eax
  struct SpriteS1 *v109; // eax
  int *v110; // edi
  int *v111; // ebx
  int *v112; // ebp
  int *v113; // eax
  int *v114; // edi
  int *v115; // eax
  char v116; // al
  struct SpriteS1 *v117; // eax
  struct SpriteS1 *v118; // edi
  struct SpriteS1 *v119; // eax
  struct SpriteS1 *v120; // ebx
  unsigned __int8 v121; // al
  __int16 *v122; // eax
  int v123; // ebp
  struct Car *v124; // eax
  struct Car *v125; // edi
  int v126; // ebx
  unsigned __int8 v127; // al
  struct Player *Player; // esi
  unsigned __int16 v129; // ax
  unsigned __int16 v130; // cx
  int v131; // [esp-10h] [ebp-244h]
  unsigned __int8 v132; // [esp-10h] [ebp-244h]
  unsigned __int8 v133; // [esp-Ch] [ebp-240h]
  struct AudioSourceParams *S9; // [esp-Ch] [ebp-240h]
  int v135; // [esp-Ch] [ebp-240h]
  char v136; // [esp+Bh] [ebp-229h] BYREF
  S410 *v137; // [esp+Ch] [ebp-228h] BYREF
  S410 v138; // [esp+13h] [ebp-221h] BYREF
  S900 a2a; // [esp+114h] [ebp-120h] BYREF
  int v140; // [esp+218h] [ebp-1Ch] BYREF
  int v141; // [esp+21Ch] [ebp-18h] BYREF
  char v142[4]; // [esp+220h] [ebp-14h] BYREF
  int v143; // [esp+224h] [ebp-10h] BYREF
  int v144; // [esp+228h] [ebp-Ch] BYREF
  int v145; // [esp+22Ch] [ebp-8h] BYREF
  char v146[4]; // [esp+230h] [ebp-4h] BYREF

  v5 = gCarSystemManager->RecycledCars + gCarSystemManager->RecycledCars_1;
  v138.gap61[0] = 0;
  BYTE2(v138.field_39) = 0;
  *(_DWORD *)&v138.gap61[12] = 0;
  v138.gap51[4] = 0;
  if ( v5 >= byte_3F130D[gGame->MaxIdx] || a3 == a4 || gCarSystemManager->field_54 )
    return 0;
  CarModelById = gta2::Style_GetCarModelById(gStyle, self->field_9);
  v8 = *(unsigned __int8 *)(CarModelById + 3);
  *(_DWORD *)&v138.field_15 = *(&gSpriteS3_0.S39_Arr48[0].field_0 + *(unsigned __int8 *)(CarModelById + 2));
  v138.field_19 = *(&gSpriteS3_0.S39_Arr48[0].field_0 + v8);
  sub_41FE40(a3, &v138.field_15, &v138.field_19);
  v138.a = 100;
  unk_66C278 = gta2::Random_PauseGame((struct Game *)&gRandom, &v138);
  v9 = a3 - 1;
  switch ( a3 )
  {
    case 1:
    case 2:
      v10 = (struct Tango *)&v138.field_19;
      goto LABEL_8;
    case 3:
    case 4:
      v10 = (struct Tango *)&v138.field_15;
LABEL_8:
      gta2::Tango_sub_41E0D0(v10, &unk_66C514.field_0);
      break;
    default:
      break;
  }
  switch ( (unsigned int)a2 )
  {
    case 1u:
      v11 = (char *)self->Flag;
      FirstElement = gta2::Player_sub_401B40((struct Player *)((char *)self->Flag + 128), (struct S202 *)&v138.gap61[4], (int)&unk_66C360)->FirstElement;
      v13 = self->sirenActive1;
      *(_DWORD *)&v138.field_21 = FirstElement;
      if ( v13 )
      {
        v14 = (int *)gta2::S202_sub_401B20((struct S202 *)(v11 + 124), (struct SpriteS1 *)&v137, (struct PublicTransport *)&unk_66C310)->FirstElement;
        v138.gap61[0] = -1;
      }
      else
      {
        v14 = (int *)gta2::Player_sub_401B40((struct Player *)(v11 + 120), (struct S202 *)&v138.gap61[8], (int)&unk_66C310)->FirstElement;
        v138.gap61[0] = 1;
      }
      *(_DWORD *)&v138.field_1D = v14;
      break;
    case 2u:
      v15 = (char *)self->Flag;
      FirstElement = gta2::S202_sub_401B20(
                       (struct S202 *)((char *)self->Flag + 132),
                       (struct SpriteS1 *)&v138.field_4D,
                       (struct PublicTransport *)&unk_66C360)->FirstElement;
      v16 = self->sirenActive1;
      *(_DWORD *)&v138.field_21 = FirstElement;
      if ( v16 )
      {
        v14 = (int *)gta2::S202_sub_401B20((struct S202 *)(v15 + 124), (struct SpriteS1 *)&v138.field_59, (struct PublicTransport *)&unk_66C310)->FirstElement;
        v138.gap61[0] = -1;
      }
      else
      {
        v14 = (int *)gta2::Player_sub_401B40((struct Player *)(v15 + 120), (struct S202 *)&v138.field_5D, (int)&unk_66C310)->FirstElement;
        v138.gap61[0] = 1;
      }
      *(_DWORD *)&v138.field_1D = v14;
      break;
    case 3u:
      v17 = (char *)self->Flag;
      v14 = (int *)gta2::S202_sub_401B20(
                     (struct S202 *)((char *)self->Flag + 124),
                     (struct SpriteS1 *)&v138.field_3D,
                     (struct PublicTransport *)&unk_66C360)->FirstElement;
      v21 = self->sirenActive1;
      *(_DWORD *)&v138.field_1D = v14;
      if ( !v21 )
      {
        v19 = (struct S202 *)&v138.field_35;
        goto LABEL_20;
      }
      v20 = (struct SpriteS1 *)&v138.field_31;
      goto LABEL_25;
    case 4u:
      v17 = (char *)self->Flag;
      v14 = (int *)gta2::Player_sub_401B40((struct Player *)((char *)self->Flag + 120), (struct S202 *)v138.gap49, (int)&unk_66C360)->FirstElement;
      v18 = self->sirenActive1;
      *(_DWORD *)&v138.field_1D = v14;
      if ( v18 )
      {
        v20 = (struct SpriteS1 *)&v138.field_41;
LABEL_25:
        FirstElement = gta2::S202_sub_401B20((struct S202 *)(v17 + 132), v20, (struct PublicTransport *)&unk_66C310)->FirstElement;
        v138.gap51[4] = -1;
        *(_DWORD *)&v138.field_21 = FirstElement;
      }
      else
      {
        v19 = (struct S202 *)v138.gap51;
LABEL_20:
        FirstElement = gta2::Player_sub_401B40((struct Player *)(v17 + 128), v19, (int)&unk_66C310)->FirstElement;
        v138.gap51[4] = 1;
        *(_DWORD *)&v138.field_21 = FirstElement;
      }
      break;
    default:
      v14 = *(int **)&v138.field_1D;
      FirstElement = *(SpriteS1 **)&v138.field_21;
      break;
  }
  v138.field_2D = unk_66C374;
  v138.field_29 = unk_66C374;
  v138.field_31 = unk_66C374;
  v138.field_35 = unk_66C374;
  switch ( v9 )
  {
    case 0:
      v138.field_2D = unk_66C310;
      v138.field_31 = unk_66C3E8;
      break;
    case 1:
      v138.field_2D = (int)gta2::JustCopyByPtrAtoC(&unk_66C310, (struct SpriteS1 *)&v138.gap61[4])->FirstElement;
      v138.field_31 = (int)gta2::JustCopyByPtrAtoC(&unk_66C3E8, (struct SpriteS1 *)&v138.gap61[8])->FirstElement;
      break;
    case 2:
      v138.field_29 = unk_66C310;
      v138.field_35 = unk_66C3E8;
      break;
    case 3:
      v138.field_29 = (int)gta2::JustCopyByPtrAtoC(&unk_66C310, (struct SpriteS1 *)&v138.gap61[4])->FirstElement;
      v138.field_35 = (int)gta2::JustCopyByPtrAtoC(&unk_66C3E8, (struct SpriteS1 *)&v138.gap61[8])->FirstElement;
      break;
    default:
      goto LABEL_32;
  }
  while ( 1 )
  {
LABEL_32:
    LOBYTE(v22) = gta2::Player_CheckCondition((struct Player *)&v138.field_1D, &unk_66C374);
    if ( v22 )
      return 0;
    LOBYTE(v23) = gta2::Player_CheckCondition((struct Player *)&v138.field_21, &unk_66C374);
    if ( v23
      || gta2::Player_sub_40CE70((struct Player *)&v138.field_1D, &unk_66C58C)
      || gta2::Player_sub_40CE70((struct Player *)&v138.field_21, &unk_66C58C) )
    {
      return 0;
    }
    v131 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v138.field_21);
    v24 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v138.field_1D);
    MaxZForTile = gta2::MapRelatedStruct_FindMaxZForTile(gMapRelatedStruct, v24, v131, &a2a.gap3[213]);
    v26 = *gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, (int *)v138.gap79, v14, (struct S202 *)FirstElement);
    *(_DWORD *)&v138.field_11 = v26;
    if ( !MaxZForTile )
      goto LABEL_118;
    v27 = *(_BYTE *)(MaxZForTile + 11);
    if ( (v27 & 0xFC) != 0 && (*(_BYTE *)(MaxZForTile + 11) & 0xFCu) < 0xB4 && (v27 & 3) != 0 )
      goto LABEL_118;
    if ( (v27 & 3) != 1 )
      goto LABEL_118;
    v138.field_25 = v26;
    unk_66C378 = unk_66C584;
    *(_DWORD *)&v138.gap4[1] = v14;
    *(_DWORD *)v138.gap1 = FirstElement;
    v28 = gta2::sub_462EA0((struct SpriteS1 *)&v138.gap79[8], &v138.field_1D);
    v138.field_9 = (int)gta2::S202_sub_401B20((struct S202 *)v28, (struct SpriteS1 *)&a2a.gap3[229], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
    v29 = gta2::sub_462EA0((struct SpriteS1 *)&v138.gap79[16], &v138.field_21);
    v138.field_D = (int)gta2::S202_sub_401B20((struct S202 *)v29, (struct SpriteS1 *)&a2a.gap3[77], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
    v30 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_D, (struct SpriteS1 *)&a2a.gap3[181], (struct PublicTransport *)&v138.field_19);
    v31 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_D, (struct S202 *)&v138.gap79[24], (int)&v138.field_19);
    v32 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_9, (struct SpriteS1 *)&a2a.gap3[85], (struct PublicTransport *)&v138.field_15);
    v33 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_9, (struct S202 *)&v138.gap79[32], (int)&v138.field_15);
    gta2::AudioSourceParams_sub_41E350(self->AudioSourceParams_, *v33, *v32, *v31, *v30);
    v34 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_11, (struct SpriteS1 *)&v143, (struct PublicTransport *)&unk_66C310);
    v35 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_11, (struct S202 *)&v138.gap79[40], (int)&unk_66C310);
    gta2::AudioSourceParams_sub_41E370(self->AudioSourceParams_, *v35, *v34);
    if ( !gta2::sub_4BA8F0(&self->AudioSourceParams_->field, a3) )
      goto LABEL_118;
    v133 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v138.field_D);
    v36 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v138.field_9);
    v37 = (_WORD *)gta2::MapRelatedStruct_sub_465250(gMapRelatedStruct, v36, v133);
    if ( v37 && !*v37 )
      return 0;
    if ( gPolice->WantedLevel < 1
      || (*(_DWORD *)&v138.field_11 = 40, v38 = gta2::Random_Random(&gRandom, (__int16 *)&v138.field_11), v38 <= 0x14u)
      || v38 >= 0x1Eu )
    {
      CarType = gta2::CarSystemManager_sub_424980(gCarSystemManager, (int)self->Player_, (void *)self->int_);
      *(_DWORD *)&a2a.gap3[5] = CarType;
      if ( !*(_WORD *)&a2a.gap3[57] )
        return 0;
    }
    else
    {
      CarType = COPCAR;
      *(_DWORD *)&v138.gap44[1] = 4;
      *(_DWORD *)&v138.field_11 = 12;
    }
    if ( gta2::Police_sub_4A9A90(gPolice) )
    {
      BYTE2(v138.field_39) = 1;
      CarType = BANKVAN;
LABEL_73:
      *(_DWORD *)&v138.field_11 = CarType;
      goto LABEL_74;
    }
    if ( CarType != COPCAR )
    {
      if ( gPolice->field_65C != 6 )
        goto LABEL_69;
      *(_DWORD *)&v138.field_11 = 10;
      switch ( gta2::Random_Random(&gRandom, (__int16 *)&v138.field_11) )
      {
        case 0u:
        case 1u:
        case 2u:
        case 3u:
          CarType = APC;
          break;
        case 4u:
        case 5u:
        case 6u:
          CarType = Tank;
          break;
        default:
          CarType = JEEP;
          break;
      }
      goto LABEL_68;
    }
    if ( gPolice->Count < (unsigned int)gPolice->field_659 && !gSkilPolice )
    {
      switch ( gPolice->field_65C )
      {
        case 3:
          CarType = COPCAR;
          break;
        case 4:
          CarType = EDSELFBI;
          break;
        case 6:
          CarType = GunJeep;
          break;
        default:
          goto LABEL_69;
      }
LABEL_68:
      *(_DWORD *)&v138.field_11 = CarType;
      goto LABEL_69;
    }
    v40 = gta2::CarSystemManager_sub_424980(gCarSystemManager, (int)self->Player_, (void *)self->int_);
    LOBYTE(CarType) = v40;
    *(_DWORD *)&a2a.gap3[5] = v40;
    if ( v40 == 12 || !*(_WORD *)&a2a.gap3[57] )
      return 0;
LABEL_69:
    if ( *(_WORD *)&v138.gap44[1] == 5 )
    {
      pGang = gta2::Player_GetRespect(self->Player_);
      v42 = pGang;
      *(_DWORD *)&v138.gap61[12] = pGang;
      if ( !pGang || !gta2::Gang_GetVisibleGang(pGang) )
        return 0;
      CarType = v42->CarType;
      goto LABEL_73;
    }
LABEL_74:
    v43 = gta2::CarEngines_sub_4327E0(gCarEngines, CarType);
    unk_66C378 = gta2::sub_4B3230((struct SpriteS1 *)&a2a.gap3[93], *(SpriteS1 **)&v43->CarDoor_[1].field_C)->FirstElement;
    v136 = 1;
    v138.gap51[0] = 2;
    LOBYTE(v138.field_3D) = 2;
    gta2::Player_sub_401B40((struct Player *)v138.gap1, (struct S202 *)&v138.gap79[48], (int)&v138.field_29);
    v44 = (Player **)gta2::Player_sub_401B40((struct Player *)&v138.gap4[1], (struct S202 *)&a2a.gap3[189], (int)&v138.field_2D);
    if ( gta2::sub_4B33F0(*v44) )
    {
      v45 = gta2::Player_sub_401B40((struct Player *)&v138.gap4[1], (struct S202 *)&a2a.gap3[101], (int)&v138.field_2D);
      v46 = gta2::sub_462EA0((struct SpriteS1 *)&v138.gap79[64], v45);
      v138.field_9 = (int)gta2::S202_sub_401B20((struct S202 *)v46, (struct SpriteS1 *)&v138.gap79[56], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v47 = gta2::Player_sub_401B40((struct Player *)v138.gap1, (struct S202 *)&v138.gap79[72], (int)&v138.field_29);
      v48 = gta2::sub_462EA0((struct SpriteS1 *)&a2a.gap3[109], v47);
      v138.field_D = (int)gta2::S202_sub_401B20((struct S202 *)v48, (struct SpriteS1 *)&a2a.gap3[237], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v49 = (int *)gta2::S202_sub_401B20(
                     (struct S202 *)&v138.field_D,
                     (struct SpriteS1 *)&v138.gap79[80],
                     (struct PublicTransport *)&v138.field_19);
      v50 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_D, (struct S202 *)&a2a.gap3[197], (int)&v138.field_19);
      v51 = (int *)gta2::S202_sub_401B20(
                     (struct S202 *)&v138.field_9,
                     (struct SpriteS1 *)&v138.gap79[88],
                     (struct PublicTransport *)&v138.field_15);
      v52 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_9, (struct S202 *)&a2a.gap3[117], (int)&v138.field_15);
      gta2::AudioSourceParams_sub_41E350(self->AudioSourceParams_, *v52, *v51, *v50, *v49);
      v53 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_25, (struct SpriteS1 *)&v138.gap79[96], (struct PublicTransport *)&unk_66C310);
      v54 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_25, (struct S202 *)&v141, (int)&unk_66C310);
      gta2::AudioSourceParams_sub_41E370(self->AudioSourceParams_, *v54, *v53);
      if ( gta2::sub_4BA8F0(&self->AudioSourceParams_->field, a3) )
      {
        v136 = 2;
        v138.gap51[0] = 1;
      }
    }
    gta2::Player_sub_401B40((struct Player *)v138.gap1, (struct S202 *)&v138.gap79[104], (int)&v138.field_35);
    v55 = (Player **)gta2::Player_sub_401B40((struct Player *)&v138.gap4[1], (struct S202 *)&a2a.gap3[125], (int)&v138.field_31);
    if ( gta2::sub_4B33F0(*v55) )
    {
      v56 = gta2::Player_sub_401B40((struct Player *)&v138.gap4[1], (struct S202 *)&a2a.gap3[205], (int)&v138.field_31);
      v57 = gta2::sub_462EA0((struct SpriteS1 *)&v138.gap79[120], v56);
      v138.field_9 = (int)gta2::S202_sub_401B20((struct S202 *)v57, (struct SpriteS1 *)&v138.gap79[112], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v58 = gta2::Player_sub_401B40((struct Player *)v138.gap1, (struct S202 *)&v138.gap79[128], (int)&v138.field_35);
      v59 = gta2::sub_462EA0((struct SpriteS1 *)&a2a.gap3[245], v58);
      v138.field_D = (int)gta2::S202_sub_401B20((struct S202 *)v59, (struct SpriteS1 *)&a2a.gap3[133], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v60 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_D, (struct SpriteS1 *)&a2a, (struct PublicTransport *)&v138.field_19);
      v61 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_D, (struct S202 *)&a2a.gap3[141], (int)&v138.field_19);
      v62 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_9, (struct SpriteS1 *)&a2a.gap3[5], (struct PublicTransport *)&v138.field_15);
      v63 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_9, (struct S202 *)&v138.gap61[16], (int)&v138.field_15);
      gta2::AudioSourceParams_sub_41E350(self->AudioSourceParams_, *v63, *v62, *v61, *v60);
      v64 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_25, (struct SpriteS1 *)&a2a.gap3[13], (struct PublicTransport *)&unk_66C310);
      v65 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_25, (struct S202 *)&a2a.gap3[149], (int)&unk_66C310);
      gta2::AudioSourceParams_sub_41E370(self->AudioSourceParams_, *v65, *v64);
      if ( gta2::sub_4BA8F0(&self->AudioSourceParams_->field, a3) )
      {
        v138.gap51[0] = 0;
        ++v136;
      }
    }
    gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[21], (struct PublicTransport *)&v138.field_29);
    v66 = (Player **)gta2::S202_sub_401B20((struct S202 *)&v138.gap4[1], (struct SpriteS1 *)&v145, (struct PublicTransport *)&v138.field_2D);
    if ( gta2::sub_4B33F0(*v66) )
    {
      v67 = gta2::S202_sub_401B20((struct S202 *)&v138.gap4[1], (struct SpriteS1 *)&a2a.gap3[157], (struct PublicTransport *)&v138.field_2D);
      v68 = gta2::sub_462EA0((struct SpriteS1 *)&a2a.gap3[37], v67);
      v138.field_9 = (int)gta2::S202_sub_401B20((struct S202 *)v68, (struct SpriteS1 *)&a2a.gap3[29], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v69 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[45], (struct PublicTransport *)&v138.field_29);
      v70 = gta2::sub_462EA0((struct SpriteS1 *)&a2a.gap3[165], v69);
      v138.field_D = (int)gta2::S202_sub_401B20((struct S202 *)v70, (struct SpriteS1 *)&a2a.gap3[221], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v71 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_D, (struct SpriteS1 *)&a2a.gap3[53], (struct PublicTransport *)&v138.field_19);
      v72 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_D, (struct S202 *)&a2a.field_100, (int)&v138.field_19);
      v73 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_9, (struct SpriteS1 *)&a2a.gap3[61], (struct PublicTransport *)&v138.field_15);
      v74 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_9, (struct S202 *)&a2a.gap3[173], (int)&v138.field_15);
      gta2::AudioSourceParams_sub_41E350(self->AudioSourceParams_, *v74, *v73, *v72, *v71);
      v75 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_25, (struct SpriteS1 *)&a2a.gap3[69], (struct PublicTransport *)&unk_66C310);
      v76 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_25, (struct S202 *)&v138.field_75, (int)&unk_66C310);
      gta2::AudioSourceParams_sub_41E370(self->AudioSourceParams_, *v76, *v75);
      if ( gta2::sub_4BA8F0(&self->AudioSourceParams_->field, a3) )
      {
        LOBYTE(v138.field_3D) = 3;
        ++v136;
      }
    }
    gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&v138.gap79[4], (struct PublicTransport *)&v138.field_35);
    v77 = (Player **)gta2::S202_sub_401B20(
                       (struct S202 *)&v138.gap4[1],
                       (struct SpriteS1 *)&v138.gap79[12],
                       (struct PublicTransport *)&v138.field_31);
    if ( gta2::sub_4B33F0(*v77) )
    {
      v78 = gta2::S202_sub_401B20((struct S202 *)&v138.gap4[1], (struct SpriteS1 *)&v138.gap79[28], (struct PublicTransport *)&v138.field_31);
      v79 = gta2::sub_462EA0((struct SpriteS1 *)&v138.gap79[36], v78);
      v138.field_9 = (int)gta2::S202_sub_401B20((struct S202 *)v79, (struct SpriteS1 *)&v138.gap79[20], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v80 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&v138.gap79[52], (struct PublicTransport *)&v138.field_35);
      v81 = gta2::sub_462EA0((struct SpriteS1 *)&v138.gap79[60], v80);
      v138.field_D = (int)gta2::S202_sub_401B20((struct S202 *)v81, (struct SpriteS1 *)&v138.gap79[44], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
      v82 = (int *)gta2::S202_sub_401B20(
                     (struct S202 *)&v138.field_D,
                     (struct SpriteS1 *)&v138.gap79[68],
                     (struct PublicTransport *)&v138.field_19);
      v83 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_D, (struct S202 *)&v138.gap79[76], (int)&v138.field_19);
      v84 = (int *)gta2::S202_sub_401B20(
                     (struct S202 *)&v138.field_9,
                     (struct SpriteS1 *)&v138.gap79[84],
                     (struct PublicTransport *)&v138.field_15);
      v85 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_9, (struct S202 *)&v138.gap79[92], (int)&v138.field_15);
      gta2::AudioSourceParams_sub_41E350(self->AudioSourceParams_, *v85, *v84, *v83, *v82);
      v86 = (int *)gta2::S202_sub_401B20(
                     (struct S202 *)&v138.field_25,
                     (struct SpriteS1 *)&v138.gap79[100],
                     (struct PublicTransport *)&unk_66C310);
      v87 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_25, (struct S202 *)&v138.gap79[108], (int)&unk_66C310);
      gta2::AudioSourceParams_sub_41E370(self->AudioSourceParams_, *v87, *v86);
      if ( gta2::sub_4BA8F0(&self->AudioSourceParams_->field, a3) )
      {
        LOBYTE(v138.field_3D) = 4;
        ++v136;
      }
    }
    switch ( v136 )
    {
      case 1:
        v88 = (S410 *)sub_4B30A0(v138.field_3D);
        v137 = v88;
        v89 = gta2::sub_401BD0(&v138.field_2D, (struct SpriteS1 *)&v138.gap79[116], &v137);
        v90 = gta2::S202_sub_401B20((struct S202 *)&v138.gap4[1], (struct SpriteS1 *)&v138.gap79[124], (struct PublicTransport *)v89)->FirstElement;
        *(_DWORD *)v138.gap49 = v90;
        v137 = v88;
        v91 = gta2::sub_401BD0(&v138.field_29, (struct SpriteS1 *)&v138.gap79[132], &v137);
        v92 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[1], (struct PublicTransport *)v91)->FirstElement;
        v93 = v92;
        v138.field_59 = (int)v92;
        *(_DWORD *)&v138.field_4D = v90;
        v137 = (S410 *)v92;
        *(_DWORD *)&v138.field_41 = v90;
        v138.field_5D = (int)v92;
        unk_66C378 = gta2::sub_4B3230((struct SpriteS1 *)&a2a.gap3[9], (struct SpriteS1 *)unk_66C5EC.field_0)->FirstElement;
        break;
      case 2:
        v94 = (S410 *)sub_4B30A0(v138.field_3D);
        v137 = v94;
        v95 = gta2::sub_401BD0(&v138.field_2D, (struct SpriteS1 *)&a2a.gap3[17], &v137);
        v90 = gta2::S202_sub_401B20((struct S202 *)&v138.gap4[1], (struct SpriteS1 *)&a2a.gap3[25], (struct PublicTransport *)v95)->FirstElement;
        *(_DWORD *)v138.gap49 = v90;
        v137 = v94;
        v96 = gta2::sub_401BD0(&v138.field_29, (struct SpriteS1 *)&a2a.gap3[33], &v137);
        v92 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[41], (struct PublicTransport *)v96)->FirstElement;
        v138.field_59 = (int)v92;
        v97 = (S410 *)sub_4B30A0(v138.gap51[0]);
        v137 = v97;
        v98 = gta2::sub_401BD0(&v138.field_2D, (struct SpriteS1 *)&a2a.gap3[49], &v137);
        *(_DWORD *)&v138.field_41 = gta2::S202_sub_401B20(
                                      (struct S202 *)&v138.gap4[1],
                                      (struct SpriteS1 *)&a2a.gap3[57],
                                      (struct PublicTransport *)v98)->FirstElement;
        v137 = v97;
        v99 = gta2::sub_401BD0(&v138.field_29, (struct SpriteS1 *)&a2a.gap3[65], &v137);
        v93 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[73], (struct PublicTransport *)v99)->FirstElement;
        v138.field_5D = (int)v93;
        *(_DWORD *)&v138.field_4D = *(_DWORD *)&v138.field_41;
        v137 = (S410 *)v93;
        break;
      case 3:
        v100 = (S410 *)sub_4B30A0(v138.field_3D);
        v137 = v100;
        v101 = gta2::sub_401BD0(&v138.field_2D, (struct SpriteS1 *)&a2a.gap3[81], &v137);
        v90 = gta2::S202_sub_401B20((struct S202 *)&v138.gap4[1], (struct SpriteS1 *)&a2a.gap3[89], (struct PublicTransport *)v101)->FirstElement;
        *(_DWORD *)v138.gap49 = v90;
        v137 = v100;
        v102 = gta2::sub_401BD0(&v138.field_29, (struct SpriteS1 *)&a2a.gap3[97], &v137);
        v92 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[105], (struct PublicTransport *)v102)->FirstElement;
        v138.field_59 = (int)v92;
        v103 = (S410 *)sub_4B30A0(v138.gap51[0]);
        v137 = v103;
        v104 = gta2::sub_401BD0(&v138.field_2D, (struct SpriteS1 *)&a2a.gap3[113], &v137);
        *(_DWORD *)&v138.field_41 = gta2::S202_sub_401B20(
                                      (struct S202 *)&v138.gap4[1],
                                      (struct SpriteS1 *)&a2a.gap3[121],
                                      (struct PublicTransport *)v104)->FirstElement;
        v137 = v103;
        v105 = gta2::sub_401BD0(&v138.field_29, (struct SpriteS1 *)&a2a.gap3[129], &v137);
        v93 = gta2::S202_sub_401B20((struct S202 *)v138.gap1, (struct SpriteS1 *)&a2a.gap3[137], (struct PublicTransport *)v105)->FirstElement;
        v138.field_5D = (int)v93;
        v106 = gta2::S202_sub_401B20((struct S202 *)v138.gap49, (struct SpriteS1 *)&a2a.gap3[153], (struct PublicTransport *)&v138.field_41);
        *(_DWORD *)&v138.field_4D = *(_DWORD *)gta2::sub_401B90(v106, &a2a.gap3[145], &unk_66C3E8);
        v107 = gta2::S202_sub_401B20((struct S202 *)&v138.field_59, (struct SpriteS1 *)&a2a.gap3[169], (struct PublicTransport *)&v138.field_5D);
        v137 = *(S410 **)gta2::sub_401B90(v107, &a2a.gap3[161], &unk_66C3E8);
        break;
      default:
        v90 = *(SpriteS1 **)v138.gap49;
        v92 = (struct SpriteS1 *)v138.field_59;
        v93 = (struct SpriteS1 *)v138.field_5D;
        break;
    }
    if ( v138.a == 2 )
    {
      if ( unk_66C278 > 2u )
      {
        *(_DWORD *)&v138.gap4[1] = v93;
        *(_DWORD *)v138.gap1 = *(_DWORD *)&v138.field_41;
        goto LABEL_102;
      }
      if ( unk_66C278 )
      {
        *(_DWORD *)v138.gap1 = *(_DWORD *)&v138.field_4D;
        *(_DWORD *)&v138.gap4[1] = v137;
        goto LABEL_102;
      }
    }
    else if ( v138.a == 1 && unk_66C278 > 1u )
    {
      *(_DWORD *)v138.gap1 = *(_DWORD *)&v138.field_4D;
      *(_DWORD *)&v138.gap4[1] = v137;
      goto LABEL_102;
    }
    *(_DWORD *)v138.gap1 = v90;
    *(_DWORD *)&v138.gap4[1] = v92;
LABEL_102:
    v108 = gta2::sub_462EA0((struct SpriteS1 *)&a2a.gap3[185], v138.gap1);
    v138.field_9 = (int)gta2::S202_sub_401B20((struct S202 *)v108, (struct SpriteS1 *)&a2a.gap3[177], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
    v109 = gta2::sub_462EA0((struct SpriteS1 *)&a2a.gap3[201], &v138.gap4[1]);
    v138.field_D = (int)gta2::S202_sub_401B20((struct S202 *)v109, (struct SpriteS1 *)&a2a.gap3[193], (struct PublicTransport *)&unk_66C4F0)->FirstElement;
    v110 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_D, (struct SpriteS1 *)&a2a.gap3[209], (struct PublicTransport *)&v138.field_19);
    v111 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_D, (struct S202 *)&a2a.gap3[217], (int)&v138.field_19);
    v112 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_9, (struct SpriteS1 *)&a2a.gap3[225], (struct PublicTransport *)&v138.field_15);
    v113 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_9, (struct S202 *)&a2a.gap3[233], (int)&v138.field_15);
    gta2::AudioSourceParams_sub_41E350(self->AudioSourceParams_, *v113, *v112, *v111, *v110);
    v114 = (int *)gta2::S202_sub_401B20((struct S202 *)&v138.field_25, (struct SpriteS1 *)&a2a.gap3[241], (struct PublicTransport *)&unk_66C310);
    v115 = (int *)gta2::Player_sub_401B40((struct Player *)&v138.field_25, (struct S202 *)&a2a.gap3[249], (int)&unk_66C310);
    gta2::AudioSourceParams_sub_41E370(self->AudioSourceParams_, *v115, *v114);
    if ( gNetworkGame )
    {
      v116 = 0;
    }
    else
    {
      v136 = 100;
      v116 = gta2::Random_PauseGame((struct Game *)&gRandom, (S410 *)&v136);
    }
    if ( v138.a == 2 )
      break;
    if ( v138.a == 1 )
    {
      if ( (unsigned __int8)v116 >= 0x43u )
        goto LABEL_118;
      goto LABEL_112;
    }
    if ( !v138.a )
      goto LABEL_112;
LABEL_118:
    gta2::sub_42A620(&v138.gap61[8], v138.gap61[0]);
    gta2::Player_sub_40E530((struct Player *)&v138.field_1D, (struct Tango *)&v138.gap61[8]);
    gta2::sub_42A620(&v138.gap61[4], v138.gap51[4]);
    gta2::Player_sub_40E530((struct Player *)&v138.field_21, (struct Tango *)&v138.gap61[4]);
    FirstElement = *(SpriteS1 **)&v138.field_21;
    v14 = *(int **)&v138.field_1D;
    result = sub_4B3150(self, a2);
    if ( !result )
      return result;
  }
  if ( (unsigned __int8)v116 >= 0x21u )
    goto LABEL_118;
LABEL_112:
  if ( gta2::S56_sub_4477B0(gCheckpoint1, self->AudioSourceParams_, 0, 0, 0) )
    goto LABEL_118;
  if ( gta2::AudioSourceParams_sub_4BA720(self->AudioSourceParams_) )
    goto LABEL_118;
  if ( gta2::sub_4BA850(&self->AudioSourceParams_->field, 2) )
    goto LABEL_118;
  v117 = gta2::sub_462EA0((struct SpriteS1 *)v142, &v138.field_9);
  v118 = gta2::S202_sub_401B20((struct S202 *)v117, (struct SpriteS1 *)&v140, (struct PublicTransport *)&unk_66C4F0)->FirstElement;
  *(_DWORD *)v138.gap1 = v118;
  v119 = gta2::sub_462EA0((struct SpriteS1 *)v146, &v138.field_D);
  v120 = gta2::S202_sub_401B20((struct S202 *)v119, (struct SpriteS1 *)&v144, (struct PublicTransport *)&unk_66C4F0)->FirstElement;
  S9 = self->AudioSourceParams_;
  v138.field_25 = (int)v120;
  if ( gta2::Game_sub_45BC90(gGame, S9) )
    goto LABEL_118;
  if ( BYTE2(v138.field_39) )
  {
    v135 = a3;
    v132 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v138.field_25);
    v121 = gta2::Weapon_sub_41C1E0((struct Weapon *)v138.gap1);
    gta2::Police_sub_4AEE70(gPolice, v121, v132, v135);
    goto LABEL_118;
  }
  v122 = (__int16 *)gta2::sub_4725B0((unsigned __int16 *)&v138.field_39 + 1, &a3);
  v123 = *(_DWORD *)&v138.field_11;
  v124 = gta2::CarSystemManager_sub_426E40(
           gCarSystemManager,
           (struct S202 *)v118,
           (struct S202 *)v120,
           *v122,
           *(CarModel **)&v138.field_11);
  v125 = v124;
  if ( v123 == 52 || v123 == 12 || v123 == 30 || v123 == 84 )
  {
    if ( gta2::CarSystemManager_sub_420CE0(gCarSystemManager, 6) && gta2::Police_sub_4AA7B0(gPolice, (int)v125) )
    {
      gta2::Car_sub_424630(v125, 6);
    }
    else
    {
      gta2::Car_sub_424630(v125, 1);
      gta2::Car_isMask3(v125);
    }
  }
  else
  {
    gta2::Car_sub_424630(v124, 1);
    if ( *(_WORD *)&v138.gap44[1] == 5 )
    {
      v126 = *(_DWORD *)&v138.gap61[12];
      v127 = *(_BYTE *)(*(_DWORD *)&v138.gap61[12] + 320);
      if ( v127 == 0xFF )
        gta2::SpriteS1_SetTo2(v125->CarSprite);
      else
        gta2::SpriteS1_SetRemap(v125->CarSprite, v127);
      sub_423560(v125, v126);
      gta2::Car_sub_41FBD0(v125, *(_BYTE *)(v126 + 312));
    }
    else
    {
      gta2::sub_422020((int)v125);
      gta2::Car_CarPutDummyDriverIn(v125);
    }
    gta2::Car_CarMakeDummy(v125);
    gta2::Car_ENGINE_ON(v125);
    v125->EngineStruct_->field_74 = unk_66C378;
  }
  gta2::Game_sub_45BD40(gGame, v125->CarSprite, (int)self->Player_);
  Player = self->Player_;
  v129 = Player->field_680;
  v130 = Player->field_682;
  if ( v129 <= v130 )
  {
    Player->field_680 = 0;
    return 1;
  }
  else
  {
    Player->field_680 = v129 - v130;
    return 0;
  }
}


// 0x004b4a00: S8::sub_4B4A00
// IDA: S8::sub_4B4A00
// Ghidra: FUN_004b4a00
byte gta2::S8_sub_4B4A00(void *self,int param_1)
{
  int iVar1;
  
  iVar1 = param_1 + -1;
  switch(iVar1) {
  case 0:
    gta2::S8_sub_4B34E0((Rect2D *)self,1,1,0);
    return (byte)iVar1;
  case 1:
    gta2::S8_sub_4B34E0((Rect2D *)self,2,2,0);
    return (byte)iVar1;
  case 2:
    gta2::S8_sub_4B34E0((Rect2D *)self,3,3,0);
    return (byte)iVar1;
  case 3:
    gta2::S8_sub_4B34E0((Rect2D *)self,4,4,0);
    return (byte)iVar1;
  default:
    return 1;
  }
}


// 0x004b4a60: S8::sub_4B4A60
// IDA: S8::sub_4B4A60
// Ghidra: ---
void gta2::S8_sub_4B4A60(struct CarAudioSettings *self)
{
  struct SpriteS1 *v2; // eax
  int v3; // ebp
  int v4; // eax
  _DWORD *v5; // edi
  _DWORD *v6; // eax
  char v7; // al
  void *v8; // ecx
  struct Car *pCar; // eax
  bool v10; // cl
  int v11; // [esp+4h] [ebp-10h] BYREF
  struct SpriteS1 *a2; // [esp+8h] [ebp-Ch] BYREF
  struct SpriteS1 *FirstElement; // [esp+Ch] [ebp-8h] BYREF
  int v14; // [esp+10h] [ebp-4h] BYREF

  if ( (!limit_recycling || gCarSystemManager->RecycledCars < 2)
    && gCarSystemManager->RecycledCars + gCarSystemManager->RecycledCars_1 < (unsigned int)byte_3F130D[gGame->MaxIdx] )
  {
    v2 = (struct SpriteS1 *)sub_41E620(self->Flag, (struct CarSystemManager *)&v11);
    v3 = gta2::SpriteS1_sub_472C00(v2);
    switch ( gPolice->WantedLevel )
    {
      case 0:
      case 1:
        v11 = unk_66C310;
        break;
      case 2:
      case 5:
        v11 = unk_66C41C;
        break;
      case 3:
        v4 = unk_66C334;
        goto LABEL_10;
      case 4:
        v11 = unk_66C56C.field_0;
        break;
      case 6:
        v4 = unk_66C56C.field_0;
LABEL_10:
        v11 = v4;
        break;
      default:
        break;
    }
    v5 = self->Flag;
    FirstElement = gta2::sub_4B3110(self->Flag, (struct SpriteS1 *)&FirstElement)->FirstElement;
    a2 = gta2::sub_4B3130(v5, (struct SpriteS1 *)&a2)->FirstElement;
    FirstElement = gta2::Radar_AddBlip((struct Tango *)&FirstElement, (struct SpriteS1 *)&v14, (struct PublicTransport *)&a2)->FirstElement;
    LOWORD(v6) = gta2::bitShiftLeft1(&v14, 86);
    FirstElement = *(SpriteS1 **)gta2::sub_401B90(&FirstElement, &a2, v6);
    unk_66C460 = gta2::Radar_AddBlip((struct Tango *)&FirstElement, (struct SpriteS1 *)&v14, (struct PublicTransport *)&v11)->FirstElement;
    self->field_9 = 1;
    self->field_A = 1;
    LOBYTE(v11) = 5;
    v7 = gta2::Random_PauseGame((struct Game *)&gRandom, (S410 *)&v11);
    v8 = self->Flag;
    LOBYTE(FirstElement) = v7;
    pCar = (struct Car *)sub_41DFC0(v8, (struct SpriteS1 *)&v14);
    v10 = gta2::Car_sub_403800(pCar, (int)&unk_66C4CC) != 0;
    LOBYTE(v11) = v10;
    switch ( (char)FirstElement )
    {
      case 0:
        self->sirenActive1 = 1;
        if ( !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)1, 2, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)2, 1, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)4, 3, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)3, 4, 0)
          && gPolice->WantedLevel < 3 )
        {
          if ( (_BYTE)v11 )
            gta2::S8_sub_4B4A00(self, v3);
        }
        break;
      case 1:
        self->sirenActive1 = 0;
        if ( !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)2, 1, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)4, 3, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)3, 4, 0)
          && (gPolice->WantedLevel >= 3 || !(_BYTE)v11 || !gta2::S8_sub_4B4A00(self, v3)) )
        {
          gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)1, 2, 0);
        }
        break;
      case 2:
        self->sirenActive1 = 1;
        if ( !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)4, 3, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)3, 4, 0)
          && (gPolice->WantedLevel >= 3 || !(_BYTE)v11 || !gta2::S8_sub_4B4A00(self, v3))
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)1, 2, 0) )
        {
          gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)2, 1, 0);
        }
        break;
      case 3:
        self->sirenActive1 = 0;
        if ( !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)3, 4, 0)
          && (gPolice->WantedLevel >= 3 || !(_BYTE)v11 || !gta2::S8_sub_4B4A00(self, v3))
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)1, 2, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)2, 1, 0) )
        {
          gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)4, 3, 0);
        }
        break;
      case 4:
        self->sirenActive1 = 1;
        if ( (gPolice->WantedLevel >= 3 || !v10 || !gta2::S8_sub_4B4A00(self, v3))
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)1, 2, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)2, 1, 0)
          && !gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)4, 3, 0) )
        {
          gta2::S8_sub_4B34E0(self, (struct SpriteS1 *)3, 4, 0);
        }
        break;
      default:
        return;
    }
  }
}


// 0x004b4e60: S8::sub_4B4E60
// IDA: S8::sub_4B4E60
// Ghidra: ---
char gta2::S8_sub_4B4E60(struct CarAudioSettings *self)
{
  struct Player *NextActivePlayer; // eax
  struct Ped *MainPed; // edi
  int *v4; // eax
  unsigned __int8 v5; // al
  struct Player *Player; // ecx
  struct Ped *pPassenger; // edi
  int *v8; // eax
  unsigned __int8 v9; // al
  unsigned __int8 v11; // [esp-8h] [ebp-1Ch]
  unsigned __int8 v12; // [esp-8h] [ebp-1Ch]
  int Y; // [esp+4h] [ebp-10h] BYREF
  int X; // [esp+8h] [ebp-Ch] BYREF
  char v15[4]; // [esp+Ch] [ebp-8h] BYREF
  char v16[4]; // [esp+10h] [ebp-4h] BYREF

  LOBYTE(NextActivePlayer) = skip_recycling;
  if ( !skip_recycling )
  {
    self->Flag = gta2::Game_GetCurrentPlayerSlot(gGame);
    NextActivePlayer = gta2::Game_start1(gGame);
    self->Player_ = NextActivePlayer;
    if ( NextActivePlayer )
    {
      MainPed = NextActivePlayer->MainPed;
      X = *(_DWORD *)gta2::Ped_GetXCoordinate(MainPed, (int)&X);
      gta2::Ped_GetYCoordinate(MainPed, &Y);
      Y = *v4;
      v11 = gta2::Weapon_sub_41C1E0((struct Weapon *)&Y);
      v5 = gta2::Weapon_sub_41C1E0((struct Weapon *)&X);
      NextActivePlayer = (struct Player *)gta2::MapRelatedStruct_sub_465250(gMapRelatedStruct, v5, v11);
      self->int_ = (int)NextActivePlayer;
    }
    if ( self->Flag )
    {
      while ( 1 )
      {
        if ( gta2::sub_433E90(self->Flag) )
          gta2::S8_sub_4B4A60(self);
        NextActivePlayer = (struct Player *)gta2::Game_SwitchToNextPlayer(gGame);
        Player = self->Player_;
        self->Flag = NextActivePlayer;
        if ( NextActivePlayer == (struct Player *)&Player->CameraOrPhysics2 )
          break;
        NextActivePlayer = gta2::Game_CycleToNextPlayer(gGame);
        self->Player_ = NextActivePlayer;
        if ( NextActivePlayer )
        {
          pPassenger = NextActivePlayer->MainPed;
LABEL_11:
          if ( pPassenger )
          {
            X = *(_DWORD *)gta2::Ped_GetXCoordinate(pPassenger, (int)v15);
            gta2::Ped_GetYCoordinate(pPassenger, (int *)v16);
            Y = *v8;
            v12 = gta2::Weapon_sub_41C1E0((struct Weapon *)&Y);
            v9 = gta2::Weapon_sub_41C1E0((struct Weapon *)&X);
            NextActivePlayer = (struct Player *)gta2::MapRelatedStruct_sub_465250(gMapRelatedStruct, v9, v12);
            self->int_ = (int)NextActivePlayer;
          }
        }
        if ( !self->Flag )
          return (char)NextActivePlayer;
      }
      pPassenger = Player->pPassenger;
      goto LABEL_11;
    }
  }
  return (char)NextActivePlayer;
}



