#include "gta2_shim.h"

// Module: other, Class: Game
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x00476790: Game::sub_476790
// IDA: Game::sub_476790
// Ghidra: ---
unsigned __int8 gta2::Game_sub_476790(struct Game *self)
{
  return self->PlayerInFocus;
}


// 0x004a4750: Game::sub_4A4750
// IDA: Game::sub_4A4750
// Ghidra: ---
bool gta2::Game_sub_4A4750(struct Game *self)
{
  bool result; // al

  result = LOBYTE(self->NoFrameLimit) == 0;
  LOBYTE(self->NoFrameLimit) = result;
  return result;
}


// 0x004b7590: Game::IsDeadPlayer
// IDA: Game::IsDeadPlayer
// Ghidra: ---
bool gta2::Game_IsDeadPlayer(struct Game *self)
{
  return self->isDead != -1;
}


// 0x004b92b0: Game::sub_4B92B0
// IDA: Game::sub_4B92B0
// Ghidra: TransmissionInfo::FUN_004b92b0
byte gta2::Game_sub_4B92B0(struct Game *self,int param_1,int *param_2)
{
  struct Player *pPVar1;
  struct SpriteS1 *X;
  bool bVar2;
  struct S127 *pS127;
  struct SpriteS1 *pSVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined4 *puVar4;
  undefined4 extraout_ECX;
  undefined2 extraout_var_03;
  int iVar5;
  int iVar6;
  undefined4 unaff_EDI;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  int local_8;
  undefined1 local_4 [4];
  int *pConditionValue;
  
  pPVar1 = gGame->PlayerMain;
  if (param_1 == 1) {
    iVar6 = 4;
  }
  else {
    iVar6 = 0;
  }
  gta2::CameraOrPhysics_WorldToScreen2D((struct CameraOrPhysics *)&pPVar1->pCameraOrPhysics,
             *(int *)&self[2].field_0x6,*(int *)&self[2].field_0xa,
             *(int *)&self[2].field_0xe,(int *)&local_10,&local_8);
  if (*(int *)&self[3].field_0x5 < 0) {
    iVar6 = (iVar6 - (int)param_2) * *(int *)&self[3].field_0x9;
    iVar5 = *(int *)&self[3].field_0xd * -7;
    gta2::S202_sub_41F980((struct SpriteS1 *)&param_2,-*(int *)&self[3].field_0x5);
    local_c = (struct SpriteS1 *)param_2;
  }
  else {
    iVar6 = iVar6 - (int)param_2;
    iVar5 = -7;
    local_c = _DAT_0066f668;
  }
  pS127 = (struct S127 *)param_2;
  gta2::S202_sub_41F980((struct SpriteS1 *)&param_2,iVar6);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)&local_10,(struct SpriteS1 *)local_4,pS127);
  X = pSVar3->FirstElement;
  param_2 = (int *)X;
  gta2::S202_sub_41F980((struct SpriteS1 *)local_4,iVar5);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)&local_8,(struct SpriteS1 *)&local_10,(struct S127 *)pSVar3);
  pSVar3 = pSVar3->FirstElement;
  local_10 = pSVar3;
  bVar2 = gta2::Player_sub_40CE70((struct Player *)&param_2,(struct Player *)&DAT_0066f6d4);
  pConditionValue = (int *)CONCAT31(extraout_var,bVar2);
  if (pConditionValue != NULL) {
    decoderfloat(local_4,0x280);
    bVar2 = gta2::Player_CheckCondition((struct Player *)&param_2,pConditionValue);
    pConditionValue = (int *)CONCAT31(extraout_var_00,bVar2);
    if (pConditionValue != NULL) {
      bVar2 = gta2::Player_sub_40CE70((struct Player *)&local_10,(struct Player *)&DAT_0066f6d4)
      ;
      pConditionValue = (int *)CONCAT31(extraout_var_01,bVar2);
      if (pConditionValue != NULL) {
        decoderfloat(&param_2,0x1e0);
        bVar2 = gta2::Player_CheckCondition((struct Player *)&local_10,pConditionValue);
        pConditionValue = (int *)CONCAT31(extraout_var_02,bVar2);
        if (pConditionValue != NULL) {
          param_2 = (int *)0x7;
          puVar4 = (undefined4 *)
                   gta2::WorldCoordinateToScreenCoord
                             (&pPVar1->field_0x1f4,local_4,(int *)&local_c);
          pConditionValue =
               (int *)CONCAT22((short)((uint)puVar4 >> 0x10),_DAT_0066f7a0);
          gta2::sub_4CBA50((struct SpriteS1 *)(param_1 + 0xa3),6,(struct SpriteS1 *)(param_1 + 0xa3)
                     ,X,pSVar3,pConditionValue,*puVar4,&param_2,
                     CONCAT22(extraout_var_03,
                              *(undefined2 *)((int)&self[3].select + 1)),1,
                     CONCAT31((int3)((uint)extraout_ECX >> 8),
                              *(undefined1 *)((int)&self[3].select + 3)),1,
                     unaff_EDI);
        }
      }
    }
  }
  return (byte)pConditionValue;
}


// 0x004b94b0: Game::sub_4B94B0
// IDA: Game::sub_4B94B0
// Ghidra: ---
char gta2::Game_sub_4B94B0(struct Game *self)
{
  int *p_State; // ebx
  int *p_isDead; // edi
  struct Tango *v4; // eax
  struct Tango *v5; // eax
  unsigned int Status; // eax
  struct SpriteS1 *a3; // [esp+Ch] [ebp-Ch] BYREF
  int Camer_Z_View; // [esp+10h] [ebp-8h] BYREF
  _BYTE a2[4]; // [esp+14h] [ebp-4h] BYREF

  p_State = &self->State;
  p_isDead = &self->isDead;
  gta2::CameraOrPhysics_WorldToScreen2D(
    &gGame->PlayerMain->CameraOrPhysics_,
    self->isDead,
    self->State,
    self->NoFrameLimit,
    (int *)&a3,
    &Camer_Z_View);
  if ( gta2::sub_4037E0(&a3) )
  {
    a3 = gta2::Player_sub_401B40((struct Player *)&unk_66F950, (struct S202 *)a2, (int)&a3)->FirstElement;
    v4 = (struct Tango *)gta2::sub_401B90(&a3, a2, &unk_66F8F0);
  }
  else
  {
    if ( !gta2::Car_sub_403800((struct Car *)&a3, (int)&unk_66F964) )
      goto LABEL_6;
    a3 = gta2::Player_sub_401B40(&unk_66F964, (struct S202 *)a2, (int)&a3)->FirstElement;
    v4 = (struct Tango *)gta2::sub_401B90(&a3, a2, &unk_66F8F0);
  }
  gta2::Player_sub_40E530((struct Player *)p_isDead, v4);
LABEL_6:
  if ( gta2::sub_4037E0(&Camer_Z_View) )
  {
    Camer_Z_View = (int)gta2::Player_sub_401B40(&unk_66F654, (struct S202 *)a2, (int)&Camer_Z_View)->FirstElement;
    v5 = (struct Tango *)gta2::sub_401B90(&Camer_Z_View, a2, &unk_66F8F0);
  }
  else
  {
    if ( !gta2::Car_sub_403800((struct Car *)&Camer_Z_View, (int)&unk_66F8E0) )
      goto LABEL_11;
    Camer_Z_View = (int)gta2::Player_sub_401B40((struct Player *)&unk_66F8E0, (struct S202 *)a2, (int)&Camer_Z_View)->FirstElement;
    v5 = (struct Tango *)gta2::sub_401B90(&Camer_Z_View, a2, &unk_66F8F0);
  }
  gta2::Player_sub_40E530((struct Player *)p_State, v5);
LABEL_11:
  Status = self->Status;
  switch ( self->Status )
  {
    case 0u:
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], 10);
      break;
    case 1u:
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], 21);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], 0);
      break;
    case 2u:
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], 31);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], 10);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -11);
      break;
    case 3u:
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[3], 42);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], 21);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], 0);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -21);
      break;
    case 4u:
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[4], 52);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[3], 31);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], 10);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], -11);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -32);
      break;
    case 5u:
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[5], 63);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[4], 42);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[3], 21);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], 0);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], -21);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -42);
      break;
    case 6u:
      gta2::Game_sub_4B92B0(self, self->CurrentPlayer, 73);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[5], 52);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[4], 31);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[3], 10);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], -11);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], -32);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -53);
      break;
    case 7u:
      gta2::Game_sub_4B92B0(self, *(Player **)&self->CurrentPlayerCopy, 84);
      gta2::Game_sub_4B92B0(self, self->CurrentPlayer, 63);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[5], 42);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[4], 21);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[3], 0);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], -21);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], -42);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -63);
      break;
    case 8u:
      gta2::Game_sub_4B92B0(self, *(Player **)&self->PlayerInFocus, 94);
      gta2::Game_sub_4B92B0(self, *(Player **)&self->CurrentPlayerCopy, 73);
      gta2::Game_sub_4B92B0(self, self->CurrentPlayer, 52);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[5], 31);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[4], 10);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[3], -11);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[2], -32);
      gta2::Game_sub_4B92B0(self, self->ArrayPlayer[1], -53);
      LOBYTE(Status) = gta2::Game_sub_4B92B0(self, self->ArrayPlayer[0], -74);
      break;
    default:
      return Status;
  }
  return Status;
}


// 0x004d09c0: Game::GetState
// IDA: Game::GetState
// Ghidra: ---
int gta2::Game_GetState(struct Game *self)
{
  return self->State;
}



