#include "gta2_shim.h"

// Module: other, Class: MissionObjective
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c4ea0: MissionObjective::sub_4C4EA0
// IDA: MissionObjective::sub_4C4EA0
// Ghidra: FUN_004c4ea0
void gta2::MissionObjective_sub_4C4EA0(int param_1,uint param_2)
{
  undefined4 *puVar1;
  struct EventHandler *self;
  
  puVar1 = (undefined4 *)(param_1 + (param_2 & 0xff) * 0x18);
  self = *(EventHandler **)(param_1 + 4 + (param_2 & 0xff) * 0x18);
  puVar1[2] = 0;
  puVar1[3] = 0;
  *puVar1 = 0;
  puVar1[5] = 2;
  gta2::S63_sub_483C40(self);
  puVar1[1] = 0;
  return;
}


// 0x004c4f30: MissionObjective::sub_4C4F30
// IDA: MissionObjective::sub_4C4F30
// Ghidra: ---
char gta2::MissionObjective_sub_4C4F30(
        struct MissionObjective *self,
        _DWORD *a2,
        _DWORD *a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9)
{
  char v10; // bl
  struct MissionObjective *i; // esi
  int v13; // edx
  int *v14; // eax

  v10 = 0;
  for ( i = self; *(_DWORD *)&i->gap4[4]; i = (struct MissionObjective *)((char *)i + 24) )
  {
    if ( (unsigned __int8)++v10 >= 0x16u )
      return -1;
  }
  *(_DWORD *)&i->gap4[4] = *a2;
  *(_DWORD *)&i->gap4[8] = *a3;
  *(_DWORD *)&i->a = a4;
  *(_DWORD *)&i->gap4[16] = 1;
  HIWORD(v13) = unk_67289E;
  LOWORD(v13) = unk_672868;
  v14 = gta2::Object_sub_485290(gObject, (struct S900 *)0xA1, a5, a6, a7, v13, (struct SpriteS1 *)a8, (struct SpriteS3 *)a9, unk_67289C);
  *(_DWORD *)i->gap4 = v14;
  gta2::sub_4C4F10(v14, v10);
  ++*(_WORD *)&self->gap133[221];
  return v10;
}


// 0x004c4fe0: MissionObjective::sub_4C4FE0
// IDA: MissionObjective::sub_4C4FE0
// Ghidra: ---
void gta2::MissionObjective_sub_4C4FE0(struct MissionObjective *self, unsigned __int8 a2, SpriteS1 *a3)
{
  char *v3; // esi
  struct SpriteS1 *v4; // edi
  struct Car *Car; // edi
  struct SpriteS1 *v6; // edi
  struct SpriteS1 *v7; // edi
  struct GameObject *v8; // eax
  struct Ped *v9; // ebx
  unsigned __int16 *v10; // eax
  __int16 v11; // cx
  MissionManager *v12; // eax
  bool v13; // zf
  struct SpriteS1 *v14; // edi
  struct GameObject *GameObject; // eax
  struct Ped *Driver; // ebx
  unsigned __int16 *v17; // eax
  MissionManager *started; // ebp
  struct SpriteS1 *v19; // edi
  struct SpriteS1 *v20; // edi
  struct GameObject *v21; // eax
  struct Ped *v22; // edi
  MissionManager *v23; // ebx
  struct Player *v24; // eax
  struct SpriteS1 *v25; // edi
  struct GameObject *v26; // eax
  struct Player *v27; // eax
  struct Ped *v28; // ebx
  MissionManager *v29; // ebp
  struct Player *v30; // eax
  bool v31; // zf
  struct SpriteS1 *v32; // edi
  struct Player *v33; // eax
  unsigned __int16 *v34; // esi
  _BYTE v36[4]; // [esp+8h] [ebp-8h] BYREF
  _BYTE v37[4]; // [esp+Ch] [ebp-4h] BYREF

  v3 = &self->a + 24 * a2;
  if ( *((_DWORD *)v3 + 5) == 1 && *((_DWORD *)v3 + 1) )
  {
    switch ( *((_DWORD *)v3 + 2) )
    {
      case 1:
        v4 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) != 2 )
          goto LABEL_34;
        *((_DWORD *)v3 + 5) = 0;
        Car = gta2::SpriteS1_GetCar(v4);
        goto LABEL_35;
      case 2:
        v6 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) != 2 )
          goto LABEL_34;
        Car = gta2::SpriteS1_GetCar(v6);
        if ( Car->ID == *(_DWORD *)(gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(*(_DWORD *)v3 + 8))->arr_96[1]
                                  + 108) )
          *((_DWORD *)v3 + 5) = 0;
        goto LABEL_35;
      case 3:
        v14 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) == 3 )
        {
          GameObject = gta2::SpriteS1_GetGameObject(v14);
          v9 = gta2::GameObject_sub_433A20(GameObject);
          if ( !v9 )
            goto LABEL_34;
          v10 = *(unsigned __int16 **)v3;
          if ( *(_WORD *)(*(_DWORD *)v3 + 2) != 434 )
            goto LABEL_14;
          goto LABEL_13;
        }
        if ( gta2::SpriteS1_getSpriteType(v14) != 2 )
          goto LABEL_34;
        Car = gta2::SpriteS1_GetCar(v14);
        Driver = gta2::Car_GetDriver(Car);
        if ( Driver )
        {
          v17 = *(unsigned __int16 **)v3;
          if ( *(_WORD *)(*(_DWORD *)v3 + 2) != 434 )
            goto LABEL_27;
          started = gta2::MissionManager_StartMission(gMissionManager, v17[18]);
          goto LABEL_50;
        }
        goto LABEL_35;
      case 4:
        v7 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) != 3 )
          goto LABEL_34;
        v8 = gta2::SpriteS1_GetGameObject(v7);
        v9 = gta2::GameObject_sub_433A20(v8);
        v10 = *(unsigned __int16 **)v3;
        v11 = *(_WORD *)(*(_DWORD *)v3 + 2);
        if ( v11 == 212 )
        {
          v12 = gta2::MissionManager_StartMission(gMissionManager, v10[8]);
        }
        else if ( v11 == 214 )
        {
LABEL_13:
          v12 = gta2::MissionManager_StartMission(gMissionManager, v10[18]);
        }
        else
        {
LABEL_14:
          v12 = gta2::MissionManager_StartMission(gMissionManager, v10[4]);
        }
        v13 = gta2::Ped_GetID(v9) == *(_DWORD *)(v12->arr_96[1] + 512);
        goto LABEL_32;
      case 5:
        v19 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) != 2 )
          goto LABEL_34;
        Car = gta2::SpriteS1_GetCar(v19);
        Driver = gta2::Car_GetDriver(Car);
        if ( !Driver )
          goto LABEL_35;
        v17 = *(unsigned __int16 **)v3;
LABEL_27:
        started = gta2::MissionManager_StartMission(gMissionManager, v17[4]);
LABEL_50:
        v31 = gta2::Ped_GetID(Driver) == *(_DWORD *)(started->arr_96[1] + 512);
        goto LABEL_51;
      case 6:
        v25 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) == 3 )
        {
          v26 = gta2::SpriteS1_GetGameObject(v25);
          v22 = gta2::GameObject_sub_433A20(v26);
          if ( v22 )
          {
            v23 = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(*(_DWORD *)v3 + 8));
            v27 = (struct Player *)gta2::Ped_sub_433C20(v22, &a2);
            if ( gta2::Player_IsCurrentPlayer(v27, (struct Player *)&unk_672900) )
            {
LABEL_31:
              v13 = gta2::Ped_GetID(v22) == *(_DWORD *)(v23->arr_96[1] + 512);
LABEL_32:
              if ( v13 )
                *((_DWORD *)v3 + 5) = 0;
            }
          }
          goto LABEL_34;
        }
        if ( gta2::SpriteS1_getSpriteType(v25) != 2 )
        {
LABEL_34:
          Car = (struct Car *)a3;
          goto LABEL_35;
        }
        Car = gta2::SpriteS1_GetCar(v25);
        v28 = gta2::Car_GetDriver(Car);
        if ( v28 )
        {
          v29 = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(*(_DWORD *)v3 + 8));
          v30 = gta2::Ped_sub_436160(v28, v36);
          if ( gta2::Player_IsCurrentPlayer(v30, (struct Player *)&unk_672900) )
          {
            v31 = gta2::Ped_GetID(v28) == *(_DWORD *)(v29->arr_96[1] + 512);
LABEL_51:
            if ( v31 )
              *((_DWORD *)v3 + 5) = 0;
          }
        }
LABEL_35:
        if ( !*((_DWORD *)v3 + 5) )
        {
          if ( *((_DWORD *)v3 + 3) == 2 )
          {
            v34 = *(unsigned __int16 **)v3;
            *((_DWORD *)v34 + 2) = gta2::MissionManager_sub_47F200(gMissionManager, v34[7], 0);
          }
          else if ( *((_DWORD *)v3 + 3) == 3 )
          {
            gta2::MissionManager_sub_47ED20(gMissionManager, (void *)Car->CarType, *(void **)v3);
            gta2::MissionObjective_sub_4C4EA0(self, v3[16]);
          }
        }
        break;
      case 7:
        v20 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) == 3 )
        {
          v21 = gta2::SpriteS1_GetGameObject(v20);
          v22 = gta2::GameObject_sub_433A20(v21);
          if ( v22 )
          {
            v23 = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(*(_DWORD *)v3 + 8));
            v24 = (struct Player *)gta2::Ped_sub_433C20(v22, &a3);
            if ( gta2::Player_IsCurrentPlayer(v24, (struct Player *)&unk_672900) )
              goto LABEL_31;
          }
        }
        goto LABEL_34;
      case 8:
        v32 = a3;
        if ( gta2::SpriteS1_getSpriteType(a3) != 2 )
          goto LABEL_34;
        Car = gta2::SpriteS1_GetCar(v32);
        Driver = gta2::Car_GetDriver(Car);
        if ( Driver )
        {
          started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(*(_DWORD *)v3 + 8));
          v33 = gta2::Ped_sub_436160(Driver, v37);
          if ( gta2::Player_IsCurrentPlayer(v33, (struct Player *)&unk_672900) )
            goto LABEL_50;
        }
        goto LABEL_35;
      default:
        goto LABEL_34;
    }
  }
}



