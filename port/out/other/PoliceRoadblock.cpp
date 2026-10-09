#include "gta2_shim.h"

// Module: other, Class: PoliceRoadblock
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004a99f0: PoliceRoadblock::sub_4A99F0
// IDA: PoliceRoadblock::sub_4A99F0
// Ghidra: ---
int gta2::PoliceRoadblock_sub_4A99F0(struct PoliceRoadblock *self)
{
  int result; // eax

  result = 0;
  self->field = 0;
  self->field_4 = 0;
  self->field_8 = 0;
  self->field_9 = 0;
  self->field_A = 0;
  self->field_C = 0;
  self->Car = 0;
  self->Car1 = 0;
  self->Car2 = 0;
  self->Car3 = 0;
  self->Car4 = 0;
  self->Car5 = 0;
  self->S63 = 0;
  self->S63_1_ = 0;
  self->S63_2 = 0;
  self->S63_3 = 0;
  self->S63_4 = 0;
  self->S63_5 = 0;
  self->S63_6 = 0;
  self->S63_7 = 0;
  self->S63_8 = 0;
  self->S63_9 = 0;
  self->S63_10 = 0;
  self->field_54 = 0;
  self->field_58 = 0;
  self->field_5C = 0;
  self->field_60 = 0;
  self->field_64 = 0;
  self->field_68 = 0;
  self->field_6C = 0;
  self->field_70 = 0;
  self->field_74 = 0;
  self->field_78 = 0;
  self->field_7C = 0;
  self->field_80 = 0;
  self->field_84 = 0;
  self->Ped_ = 0;
  self->Ped1 = 0;
  self->Ped2 = 0;
  self->Ped3 = 0;
  self->Ped4 = 0;
  self->Ped5 = 0;
  return result;
}


// 0x004abd70: PoliceRoadblock::sub_4ABD70
// IDA: PoliceRoadblock::sub_4ABD70
// Ghidra: PoliceRoadblock::FUN_004abd70
void gta2::PoliceRoadblock_sub_4ABD70(struct PoliceRoadblock *self)
{
  EventHandler *pEVar1;
  struct Car *pCVar2;
  GlassInfo *this_00;
  struct Ped *pS49;
  
  if (self->Car != NULL) {
    gta2::Car_isMask4(self->Car);
    gta2::Car_CarMakeDriveable1(self->Car,3);
    self->Car = NULL;
  }
  if (self->Car11 != NULL) {
    gta2::Car_isMask4(self->Car11);
    gta2::Car_CarMakeDriveable1(self->Car11,3);
    self->Car11 = NULL;
  }
  if (self->Car1 != NULL) {
    gta2::Car_isMask4(self->Car1);
    gta2::Car_CarMakeDriveable1(self->Car1,3);
    self->Car1 = NULL;
  }
  if (self->Car10 != NULL) {
    gta2::Car_isMask4(self->Car10);
    gta2::Car_CarMakeDriveable1(self->Car10,3);
    self->Car10 = NULL;
  }
  if (self->Car2 != NULL) {
    gta2::Car_isMask4(self->Car2);
    gta2::Car_CarMakeDriveable1(self->Car2,3);
    self->Car2 = NULL;
  }
  if (self->Car12 != NULL) {
    gta2::Car_isMask4(self->Car12);
    gta2::Car_CarMakeDriveable1(self->Car12,3);
    self->Car12 = NULL;
  }
  pEVar1 = self->EventHandler0;
  if (pEVar1 != NULL) {
    if (*(Ped **)&pEVar1->CameraX == self->Ped9) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->EventHandler0 = NULL;
  }
  pCVar2 = self->Car8;
  if (pCVar2 != NULL) {
    if (pCVar2->CarDoor_[0].PedInDoor == self->Ped7) {
      gta2::S63_sub_483C40((EventHandler *)pCVar2);
    }
    self->Car8 = NULL;
  }
  pCVar2 = self->Car4;
  if (pCVar2 != NULL) {
    if (pCVar2->CarDoor_[0].PedInDoor == self->Ped5) {
      gta2::S63_sub_483C40((EventHandler *)pCVar2);
    }
    self->Car4 = NULL;
  }
  pCVar2 = self->Car6;
  if (pCVar2 != NULL) {
    if (pCVar2->CarDoor_[0].PedInDoor == self->Ped6) {
      gta2::S63_sub_483C40((EventHandler *)pCVar2);
    }
    self->Car6 = NULL;
  }
  pCVar2 = self->Car5;
  if (pCVar2 != NULL) {
    if (pCVar2->CarDoor_[0].PedInDoor == self->Ped4) {
      gta2::S63_sub_483C40((EventHandler *)pCVar2);
    }
    self->Car5 = NULL;
  }
  pEVar1 = self->EventHandler2;
  if (pEVar1 != NULL) {
    if (*(Ped **)&pEVar1->CameraX == self->Ped10) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->EventHandler2 = NULL;
  }
  pEVar1 = self->EventHandler1;
  if (pEVar1 != NULL) {
    if (*(int *)&pEVar1->CameraX == self->field33_0x70) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->EventHandler1 = NULL;
  }
  pEVar1 = (EventHandler *)self->field22_0x44;
  if (pEVar1 != NULL) {
    if (*(int *)&pEVar1->CameraX == self->field34_0x74) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->field22_0x44 = 0;
  }
  pEVar1 = (EventHandler *)self->S63_1_;
  if (pEVar1 != NULL) {
    if (*(int *)&pEVar1->CameraX == self->field35_0x78) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->S63_1_ = 0;
  }
  pEVar1 = (EventHandler *)self->field24_0x4c;
  if (pEVar1 != NULL) {
    if (*(int *)&pEVar1->CameraX == self->field36_0x7c) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->field24_0x4c = 0;
  }
  pEVar1 = (EventHandler *)self->S63_2;
  if (pEVar1 != NULL) {
    if (*(int *)&pEVar1->CameraX == self->field37_0x80) {
      gta2::S63_sub_483C40(pEVar1);
    }
    self->S63_2 = 0;
  }
  this_00 = self->GlassInfo;
  if (this_00 != NULL) {
    if (this_00->field11_0x14 == self->field38_0x84) {
      gta2::S63_sub_483C40((EventHandler *)this_00);
    }
    self->GlassInfo = NULL;
  }
  pS49 = self->Ped_;
  if (pS49 != NULL) {
    if (pS49->uns51 == 0) {
      gta2::Ped_SetSearchType(pS49,3);
    }
    else {
      gta2::Ped_sub_43E650(pS49);
    }
    self->Ped_ = NULL;
  }
  pS49 = self->Ped0;
  if (pS49 != NULL) {
    if (pS49->uns51 == 0) {
      gta2::Ped_SetSearchType(pS49,3);
    }
    else {
      gta2::Ped_sub_43E650(pS49);
    }
    self->Ped0 = NULL;
  }
  pS49 = self->Ped1;
  if (pS49 != NULL) {
    if (pS49->uns51 == 0) {
      gta2::Ped_SetSearchType(pS49,3);
    }
    else {
      gta2::Ped_sub_43E650(pS49);
    }
    self->Ped1 = NULL;
  }
  pS49 = self->Ped2;
  if (pS49 != NULL) {
    if (pS49->uns51 == 0) {
      gta2::Ped_SetSearchType(pS49,3);
    }
    else {
      gta2::Ped_sub_43E650(pS49);
    }
    self->Ped2 = NULL;
  }
  pS49 = self->Ped3;
  if (pS49 != NULL) {
    if (pS49->uns51 == 0) {
      gta2::Ped_SetSearchType(pS49,3);
    }
    else {
      gta2::Ped_sub_43E650(pS49);
    }
    self->Ped3 = NULL;
  }
  pS49 = self->sPed;
  if (pS49 != NULL) {
    if (pS49->uns51 != 0) {
      gta2::Ped_sub_43E650(pS49);
      self->sPed = NULL;
      self->field0_0x0 = 0;
      return;
    }
    gta2::Ped_SetSearchType(pS49,3);
    self->sPed = NULL;
  }
  self->field0_0x0 = 0;
  return;
}


// 0x004ac040: PoliceRoadblock::PoliceRoadblock
// IDA: PoliceRoadblock::PoliceRoadblock
// Ghidra: ---
PoliceRoadblock * gta2::PoliceRoadblock_PoliceRoadblock(struct PoliceRoadblock *self)
{
  AudioSourceParams *pS9; // eax

  gta2::PoliceRoadblock_sub_4A99F0(self);
  pS9 = (AudioSourceParams *)gta2::operator_new(0x18u);
  if ( pS9 )
    self->S9 = gta2::AudioSourceParams_AudioSourceParams(pS9);
  else
    self->S9 = 0;
  return self;
}


// 0x004ad6c0: PoliceRoadblock::sub_4AD6C0
// IDA: PoliceRoadblock::sub_4AD6C0
// Ghidra: ---
void gta2::PoliceRoadblock_sub_4AD6C0(struct PoliceRoadblock *self)
{
  __int16 v2; // ax
  struct Car *Car; // eax
  struct Car *Car1; // eax
  struct Car *Car2; // eax
  struct Car *Car3; // eax
  struct Car *Car4; // eax
  struct Car *Car5; // eax
  EventHandler *S63; // eax
  EventHandler *S63_1; // eax
  EventHandler *S63_2; // eax
  EventHandler *S63_3; // eax
  EventHandler *S63_4; // eax
  EventHandler *S63_5; // eax
  EventHandler *S63_6; // eax
  EventHandler *S63_7; // eax
  EventHandler *S63_8; // eax
  EventHandler *S63_9; // eax
  EventHandler *S63_10; // eax
  EventHandler *v20; // eax
  struct Ped *Ped; // edi
  struct Ped *Ped1; // edi
  struct Ped *Ped2; // edi
  struct Ped *Ped3; // edi
  struct Ped *Ped4; // edi
  struct Ped *Ped5; // edi
  Game *v27; // edi
  char v28; // [esp+Bh] [ebp-15h]
  void *v29; // [esp+Ch] [ebp-14h] BYREF
  int v30; // [esp+10h] [ebp-10h] BYREF
  char v31[4]; // [esp+14h] [ebp-Ch] BYREF
  char v32[4]; // [esp+18h] [ebp-8h] BYREF
  char v33[4]; // [esp+1Ch] [ebp-4h] BYREF

  v28 = 1;
  if ( self->field )
  {
    v2 = self->field_C;
    if ( v2 )
      self->field_C = v2 - 1;
    if ( !self->field_C )
    {
      Car = self->Car;
      if ( Car )
      {
        if ( Car->SearchType == SEARCHTYPE_AREA_PLAYER_ONLY )
        {
          if ( !Car->field_76 )
            v28 = 0;
        }
        else
        {
          self->Car = 0;
        }
      }
      Car1 = self->Car1;
      if ( Car1 )
      {
        if ( Car1->SearchType == SEARCHTYPE_AREA_PLAYER_ONLY )
        {
          if ( !Car1->field_76 )
            v28 = 0;
        }
        else
        {
          self->Car1 = 0;
        }
      }
      Car2 = self->Car2;
      if ( Car2 )
      {
        if ( Car2->SearchType == SEARCHTYPE_AREA_PLAYER_ONLY )
        {
          if ( !Car2->field_76 )
            v28 = 0;
        }
        else
        {
          self->Car2 = 0;
        }
      }
      Car3 = self->Car3;
      if ( Car3 )
      {
        if ( Car3->SearchType == SEARCHTYPE_AREA_PLAYER_ONLY )
        {
          if ( !Car3->field_76 )
            v28 = 0;
        }
        else
        {
          self->Car3 = 0;
        }
      }
      Car4 = self->Car4;
      if ( Car4 )
      {
        if ( Car4->SearchType == SEARCHTYPE_AREA_PLAYER_ONLY )
        {
          if ( !Car4->field_76 )
            v28 = 0;
        }
        else
        {
          self->Car4 = 0;
        }
      }
      Car5 = self->Car5;
      if ( Car5 )
      {
        if ( Car5->SearchType == SEARCHTYPE_AREA_PLAYER_ONLY )
        {
          if ( !Car5->field_76 )
            v28 = 0;
        }
        else
        {
          self->Car5 = 0;
        }
      }
      S63 = self->S63;
      if ( S63
        && S63->field_14 == self->field_58
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_1 = self->S63_1_;
      if ( S63_1
        && S63_1->field_14 == self->field_5C
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_1->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_1->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_2 = self->S63_2;
      if ( S63_2
        && S63_2->field_14 == self->field_60
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_2->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_2->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_3 = self->S63_3;
      if ( S63_3
        && S63_3->field_14 == self->field_64
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_3->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_3->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_4 = self->S63_4;
      if ( S63_4
        && S63_4->field_14 == self->field_68
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_4->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_4->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_5 = self->S63_5;
      if ( S63_5
        && S63_5->field_14 == self->field_6C
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_5->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_5->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_6 = self->S63_6;
      if ( S63_6
        && S63_6->field_14 == self->field_70
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_6->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_6->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_7 = self->S63_7;
      if ( S63_7
        && S63_7->field_14 == self->field_74
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_7->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_7->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_8 = self->S63_8;
      if ( S63_8
        && S63_8->field_14 == self->field_78
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_8->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_8->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_9 = self->S63_9;
      if ( S63_9
        && S63_9->field_14 == self->field_7C
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_9->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_9->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      S63_10 = self->S63_10;
      if ( S63_10
        && S63_10->field_14 == self->field_80
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)S63_10->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)S63_10->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      v20 = self->field_54;
      if ( v20
        && v20->field_14 == self->field_84
        && gta2::Game_sub_45BC10(
             gGame,
             (Player *)v20->SpriteS1_->S3_arr5031[0].PositionX,
             (Player *)v20->SpriteS1_->S3_arr5031[0].PositionY) )
      {
        v28 = 0;
      }
      Ped = self->Ped_;
      if ( Ped )
      {
        if ( gta2::Ped_Get_433B40(self->Ped_) )
        {
          if ( HIWORD(Ped->ElvisLeader) < 0x50u )
            v28 = 0;
        }
        else
        {
          self->Ped_ = 0;
        }
      }
      Ped1 = self->Ped1;
      if ( Ped1 )
      {
        if ( gta2::Ped_Get_433B40(self->Ped1) )
        {
          if ( HIWORD(Ped1->ElvisLeader) < 0x50u )
            v28 = 0;
        }
        else
        {
          self->Ped1 = 0;
        }
      }
      Ped2 = self->Ped2;
      if ( Ped2 )
      {
        if ( gta2::Ped_Get_433B40(self->Ped2) )
        {
          if ( HIWORD(Ped2->ElvisLeader) < 0x50u )
            v28 = 0;
        }
        else
        {
          self->Ped2 = 0;
        }
      }
      Ped3 = self->Ped3;
      if ( Ped3 )
      {
        if ( gta2::Ped_Get_433B40(self->Ped3) )
        {
          if ( HIWORD(Ped3->ElvisLeader) < 0x50u )
            v28 = 0;
        }
        else
        {
          self->Ped3 = 0;
        }
      }
      Ped4 = self->Ped4;
      if ( Ped4 )
      {
        if ( gta2::Ped_Get_433B40(self->Ped4) )
        {
          if ( HIWORD(Ped4->ElvisLeader) < 0x50u )
            v28 = 0;
        }
        else
        {
          self->Ped4 = 0;
        }
      }
      Ped5 = self->Ped5;
      if ( Ped5 )
      {
        if ( gta2::Ped_Get_433B40(self->Ped5) )
        {
          if ( HIWORD(Ped5->ElvisLeader) < 0x50u )
          {
LABEL_116:
            *(_WORD *)&self->field_E = 0;
            return;
          }
        }
        else
        {
          self->Ped5 = 0;
        }
      }
      if ( v28 )
      {
        if ( ++*(_WORD *)&self->field_E <= 0xC8u )
          return;
        v27 = gGame;
        gta2::S202_sub_40CE30((S202 *)&v29, self->field_9);
        gta2::S202_sub_40CE30((S202 *)&v30, self->field_8);
        gta2::Ped_GetYCoordinate(v27->PlayerMain->MainPed, (int *)v31);
        gta2::Ped_GetXCoordinate(v27->PlayerMain->MainPed, (int)v32);
        v29 = gta2::sub_42A6B0(v33, v33)->Car;
        if ( gta2::Car_sub_403800((Car *)&v29, &unk_66B898) )
        {
          gta2::PoliceRoadblock_sub_4ABD70(self);
          return;
        }
      }
      goto LABEL_116;
    }
  }
}


// 0x004adb70: PoliceRoadblock::sub_4ADB70
// IDA: PoliceRoadblock::sub_4ADB70
// Ghidra: ---
char gta2::PoliceRoadblock_sub_4ADB70(
        struct PoliceRoadblock *self,
        unsigned __int8 arg0,
        unsigned __int8 a3,
        unsigned __int8 a4,
        int a5)
{
  struct Car *v5; // ebp
  unsigned __int8 v7; // bl
  char Car; // al
  char v9; // al
  S202 *v10; // eax
  struct Car **v11; // eax
  S202 *v12; // eax
  int v13; // edi
  _DWORD *v14; // eax
  int *v15; // eax
  int *v16; // eax
  int *v17; // eax
  SpriteS1 *v18; // eax
  SpriteS1 *v19; // eax
  SpriteS1 *v20; // eax
  SpriteS1 *v21; // eax
  int v22; // eax
  int v23; // ecx
  unsigned __int16 v24; // ax
  Player *v25; // eax
  SpriteS1 *v26; // eax
  SpriteS1 *v27; // eax
  struct Ped *v28; // eax
  S202 *v29; // eax
  S202 **v30; // edi
  Player **p_pPlayer; // ecx
  S202 *v32; // eax
  S202 **v33; // eax
  S202 *v34; // eax
  SpriteS1 *v35; // eax
  S202 *v36; // eax
  SpriteS1 *v37; // eax
  S202 *v38; // eax
  S202 *v39; // eax
  S202 **v40; // edi
  S202 *v41; // eax
  S202 **v42; // eax
  struct Ped *v43; // edi
  S202 *v44; // eax
  SpriteS1 *v45; // eax
  int *v46; // edi
  S202 *v47; // eax
  SpriteS1 *v48; // eax
  int *v49; // ebx
  int v50; // ecx
  EventHandler *pS63; // edi
  S202 *v52; // eax
  SpriteS1 *v53; // eax
  int *v54; // ebx
  S202 *v55; // eax
  SpriteS1 *v56; // eax
  int v57; // ecx
  EventHandler *v58; // eax
  S202 *v59; // eax
  int *v60; // edi
  S202 *v61; // eax
  SpriteS1 *v62; // eax
  S202 *v63; // ecx
  struct Ped **v64; // ebx
  struct Ped *v65; // eax
  bool v66; // cf
  char result; // al
  unsigned __int8 v68; // bl
  char v69; // al
  char v70; // al
  int *v71; // eax
  S202 *v72; // eax
  int v73; // edi
  _DWORD *v74; // eax
  S202 *v75; // eax
  int *v76; // eax
  int *v77; // eax
  int *v78; // eax
  SpriteS1 *v79; // eax
  SpriteS1 *v80; // eax
  SpriteS1 *v81; // eax
  SpriteS1 *v82; // eax
  int v83; // eax
  int v84; // ecx
  unsigned __int16 v85; // ax
  Player *v86; // eax
  SpriteS1 *v87; // eax
  SpriteS1 *v88; // eax
  struct Ped *v89; // eax
  S202 *v90; // eax
  S202 **v91; // ebx
  int *p_RecycledCars_1; // ecx
  S202 *v93; // eax
  S202 **v94; // eax
  S202 *v95; // eax
  SpriteS1 *v96; // eax
  S202 *v97; // eax
  SpriteS1 *v98; // eax
  S202 *v99; // eax
  S202 *v100; // eax
  S202 **v101; // ebx
  S202 *v102; // eax
  S202 **v103; // eax
  struct Ped *v104; // edi
  S202 *v105; // eax
  SpriteS1 *v106; // eax
  int v107; // ebx
  int *v108; // edi
  S202 *v109; // eax
  SpriteS1 *v110; // eax
  S202 *v111; // ecx
  int *v112; // ebp
  EventHandler *v113; // edi
  S202 *v114; // eax
  SpriteS1 *v115; // eax
  int *v116; // ebp
  S202 *v117; // eax
  SpriteS1 *v118; // eax
  S202 *v119; // edx
  int *v120; // ebx
  int v121; // ecx
  EventHandler *v122; // eax
  S202 *v123; // eax
  int *v124; // edi
  S202 *v125; // eax
  SpriteS1 *v126; // eax
  S202 *v127; // ecx
  struct Ped **v128; // ebx
  struct Ped *v129; // eax
  int v130; // [esp-10h] [ebp-C4h]
  int v131; // [esp-10h] [ebp-C4h]
  int v132; // [esp-Ch] [ebp-C0h]
  int v133; // [esp-Ch] [ebp-C0h]
  S202 v134; // [esp-8h] [ebp-BCh] BYREF
  CarSystemManager v135; // [esp+18h] [ebp-9Ch] BYREF
  int v136; // [esp+84h] [ebp-30h] BYREF
  S202 v137; // [esp+88h] [ebp-2Ch] BYREF
  int v138; // [esp+A8h] [ebp-Ch] BYREF
  int v139; // [esp+ACh] [ebp-8h] BYREF
  int v140; // [esp+B0h] [ebp-4h] BYREF

  v5 = 0;
  *(_DWORD *)&v135.field_10 = 0;
  HIBYTE(v134.field_18) = 0;
  LOBYTE(v135.Index) = 0;
  if ( a5 == 2 )
  {
    v7 = arg0;
    *(_DWORD *)&v134.field_1C = a4 - 1;
    while ( 2 )
    {
      --a3;
      LOBYTE(v135.Car) = 0;
      switch ( gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, arg0, a3, *(int *)&v134.field_1C) )
      {
        case 0:
          Car = 1;
          ++a3;
          goto LABEL_8;
        case 1:
          goto LABEL_7;
        case 2:
        case 3:
          if ( LOBYTE(v135.Index) )
          {
            Car = 1;
          }
          else
          {
            LOBYTE(v135.Index) = 1;
LABEL_7:
            Car = (char)v135.Car;
          }
LABEL_8:
          if ( ++HIBYTE(v134.field_18) > 0xCu )
            return 0;
          if ( !Car )
            continue;
          LOBYTE(v135.Weapon_) = 0;
          if ( LOBYTE(v135.Index) == 1 )
          {
            LOBYTE(v135.Weapon_) = 1;
            ++a3;
          }
          LOBYTE(v135.Index) = 0;
          v135.field_10 = a3;
          HIBYTE(v134.field_18) = 0;
          while ( 2 )
          {
            ++a3;
            LOBYTE(v135.Car) = 0;
            switch ( gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, arg0, a3, *(int *)&v134.field_1C) )
            {
              case 0:
                goto LABEL_18;
              case 1:
                ++LOBYTE(v135.Weapon_);
                v9 = (char)v135.Car;
                goto LABEL_19;
              case 2:
              case 3:
                if ( LOBYTE(v135.Index) )
                {
LABEL_18:
                  v9 = 1;
                }
                else
                {
                  LOBYTE(v135.Index) = 1;
                  ++LOBYTE(v135.Weapon_);
                  v9 = (char)v135.Car;
                }
LABEL_19:
                if ( ++HIBYTE(v134.field_18) > 0xCu )
                  return 0;
                if ( !v9 )
                  continue;
                if ( LOBYTE(v135.Weapon_) > 0xCu )
                  return 0;
                gta2::S202_sub_40CE30((S202 *)&v135.field_20, arg0);
                LOBYTE(v13) = v135.field_10;
                v135.ID = (int)gta2::S202_sub_401B20(v10, (SpriteS1 *)&v135.field_18, &unk_66BA04)->FirstElement;
                gta2::S202_sub_40CE30((S202 *)&v135.field_18, v135.field_10);
                v135.Car = *v11;
                gta2::S202_sub_40CE30((S202 *)&v135.field_10, arg0);
                v13 = (unsigned __int8)v13;
                *(_DWORD *)&v135.Index = gta2::S202_sub_401B20(v12, (SpriteS1 *)&v135.field_18, &unk_66BA04)->FirstElement;
                v135.field_20 = LOBYTE(v135.Weapon_);
                LOWORD(v14) = gta2::bitShiftLeft1(&v135.field_18, LOBYTE(v135.Weapon_) + (unsigned __int8)v13 + 1);
                *(_DWORD *)&v134.field_1C = *v14;
                gta2::S202_sub_40CE30((S202 *)&v135.field_18, a4);
                v135.field_4 = *v15;
                *(_DWORD *)&v135.field_10 = gta2::S202_sub_401B20((S202 *)&v135, (SpriteS1 *)&v135.field_18, &unk_66BA04);
                v16 = (int *)gta2::Player_sub_401B40((Player *)&v135.ID, (S202 *)&v135.RecycledCars, (int)&unk_66BA04);
                gta2::AudioSourceParams_sub_41E350(
                  self->S9,
                  *v16,
                  **(_DWORD **)&v135.field_10,
                  (int)v135.Car,
                  *(int *)&v134.field_1C);
                *(_DWORD *)&v135.field_10 = gta2::S202_sub_401B20(
                                              (S202 *)&v135.field_4,
                                              (SpriteS1 *)&v135.RecycledCars,
                                              &byte_66B838);
                v17 = (int *)gta2::Player_sub_401B40((Player *)&v135.field_4, (S202 *)&v135.field_18, (int)&byte_66B838);
                gta2::AudioSourceParams_sub_41E370(self->S9, *v17, **(_DWORD **)&v135.field_10);
                if ( gta2::S56_sub_4477B0(gCheckpoint1, self->S9, 0, 0, 0) )
                  return 0;
                v134.S202 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&v135.field_4);
                v18 = gta2::Player_sub_401B40((Player *)&v134.field_1C, (S202 *)&v135.RecycledCars, (int)&unk_66B808);
                v134.field_0 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v18);
                v132 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&v135.Car);
                v19 = gta2::S202_sub_401B20((S202 *)&v135, (SpriteS1 *)&v135.field_10, &unk_66BA04);
                v20 = gta2::Player_sub_401B40((Player *)v19, (S202 *)&v135.field_18, (int)&unk_66B808);
                v130 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v20);
                v21 = gta2::Player_sub_401B40((Player *)&v135.ID, (S202 *)&v134.field_1C, (int)&unk_66BA04);
                v22 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v21);
                if ( gta2::MapRelatedStruct_sub_466380(gMapRelatedStruct, v22, v130, v132, v134.field_0, (int)v134.S202) )
                  return 0;
                gta2::PoliceRoadblock_sub_4A99F0(self);
                HIBYTE(v134.field_18) = 0;
                if ( !LOBYTE(v135.Weapon_) )
                  goto LABEL_163;
                *(_DWORD *)&v135.field_10 = 0;
                v23 = 0;
                *(_DWORD *)&v134.field_1C = (unsigned __int8)v13;
                while ( 1 )
                {
                  if ( v23 % 2 )
                  {
                    if ( HIBYTE(v134.field_18) && v23 < v135.field_20 - 1 )
                    {
                      v134.S202 = (S202 *)&unk_66B938;
                      v134.field_0 = (int)&v135.RecycledCars;
                      v135.ID = 32;
                      v24 = gta2::Random_Random(&gRandom, (__int16 *)&v135.ID);
                      gta2::sub_401AE0(&v135.field_18, v24);
                      v26 = gta2::Player_sub_401B40(v25, (S202 *)v134.field_0, (int)v134.S202);
                      v27 = gta2::Radar_AddBlip((Tango *)&byte_66BA5C, (SpriteS1 *)&v135.Player, (PublicTransport *)v26);
                      v28 = sub_40F540((Ped *)&v135.Car, (int)v27);
                      LOWORD(v135.field_4) = *(_WORD *)gta2::sub_40E5A0(&unk_66B804, &v135, v28);
                    }
                    else
                    {
                      LOWORD(v135.field_4) = unk_66B804.Index;
                    }
                    if ( gta2::CarSystemManager_sub_420CE0(gCarSystemManager, 7) )
                    {
                      switch ( unk_66B798 )
                      {
                        case 1:
                          v134.S202 = (S202 *)&unk_66BA04;
                          v134.field_0 = (int)&v137.CarSystemManager;
                          LOWORD(v29) = gta2::bitShiftLeft1(&v137.field_10, v13);
                          v30 = (S202 **)gta2::S202_sub_401B20(v29, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                          v134.S202 = (S202 *)&unk_66BA04;
                          v134.field_0 = (int)&v137.field_18;
                          p_pPlayer = (Player **)&v138;
                          goto LABEL_35;
                        case 2:
                          v134.S202 = (S202 *)&unk_66BA04;
                          v134.field_0 = (int)&v135.MissionCars;
                          LOWORD(v34) = gta2::bitShiftLeft1(&v136, v13);
                          v35 = gta2::S202_sub_401B20(v34, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                          v134.S202 = (S202 *)&unk_66BA04;
                          v30 = (S202 **)v35;
                          v134.field_0 = (int)&v135.field_44;
                          p_pPlayer = &v137.pPlayer;
LABEL_35:
                          gta2::S202_sub_40CE30((S202 *)p_pPlayer, v7);
                          v33 = (S202 **)gta2::S202_sub_401B20(v32, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                          v134.S202 = (S202 *)12;
                          goto LABEL_36;
                        case 3:
                          v134.S202 = (S202 *)&unk_66BA04;
                          v134.field_0 = (int)&v135.UnitCars;
                          LOWORD(v36) = gta2::bitShiftLeft1(&v137.S202, v13);
                          v37 = gta2::S202_sub_401B20(v36, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                          v134.S202 = (S202 *)&unk_66BA04;
                          v134.field_0 = (int)&v135.field_54;
                          v30 = (S202 **)v37;
                          gta2::S202_sub_40CE30((S202 *)&v139, v7);
                          v33 = (S202 **)gta2::S202_sub_401B20(v38, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                          v134.S202 = (S202 *)84;
LABEL_36:
                          v5 = gta2::CarSystemManager_sub_426E40(
                                 gCarSystemManager,
                                 *v33,
                                 *v30,
                                 v135.field_4,
                                 (CarModel *)v134.S202);
                          byte_593E61 = 1;
                          byte_593E60 = 1;
                          break;
                        case 4:
                          if ( *(_DWORD *)&v135.field_10 != v135.field_20 - 1 )
                          {
                            v134.S202 = (S202 *)&unk_66BAB4;
                            v134.field_0 = (int)&v135.field_5C;
                            LOWORD(v39) = gta2::bitShiftLeft1(&v137.field_C, v13);
                            v40 = (S202 **)gta2::S202_sub_401B20(v39, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v134.S202 = (S202 *)&unk_66BA04;
                            v134.field_0 = (int)&v135.SpriteS1_0;
                            gta2::S202_sub_40CE30((S202 *)&v137.field_1C, v7);
                            v42 = (S202 **)gta2::S202_sub_401B20(v41, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v5 = gta2::CarSystemManager_sub_426E40(
                                   gCarSystemManager,
                                   *v42,
                                   *v40,
                                   v135.field_4,
                                   (CarModel *)0x36);
                            byte_593E61 = 0;
                            byte_593E60 = 0;
                            v43 = gta2::Character_CreatePedInCar(gCharacter, v5);
                            gta2::Ped_SetSearchType(v43, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
                            gta2::Ped_SetCurrentOccupation(v43, ROAD_BLOCK_TANK_MAN);
                            v134.S202 = (S202 *)148;
                            v43->field_228 = 1;
                            *((_WORD *)gta2::Car_sub_4BE980(v5, (int)v134.S202) + 8) = unk_66BACC.Index;
                          }
                          break;
                        default:
                          break;
                      }
                      if ( v5 )
                      {
                        gta2::Car_CarMakeDriveable1(v5, SEARCHTYPE_AREA_PLAYER_ONLY);
                        gta2::Car_sub_424630(v5, 7);
                        if ( gta2::Car_IsEmergencyOrFbiCar(v5) )
                          gta2::Car_sub_422D20(v5);
                        if ( self->Car )
                        {
                          if ( self->Car1 )
                          {
                            if ( self->Car2 )
                            {
                              if ( self->Car3 )
                              {
                                if ( self->Car4 )
                                  self->Car5 = v5;
                                else
                                  self->Car4 = v5;
                              }
                              else
                              {
                                self->Car3 = v5;
                              }
                            }
                            else
                            {
                              self->Car2 = v5;
                            }
                          }
                          else
                          {
                            self->Car1 = v5;
                          }
                        }
                        else
                        {
                          self->Car = v5;
                        }
                      }
                    }
                  }
                  else
                  {
                    if ( byte_593E61 )
                    {
                      v134.S202 = (S202 *)&unk_66BA04;
                      v134.field_0 = (int)&v135.field_38;
                      LOWORD(v44) = gta2::bitShiftLeft1(&v135.RecycledCars_1, *(int *)&v134.field_1C);
                      v45 = gta2::S202_sub_401B20(v44, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                      v134.S202 = (S202 *)&unk_66BA94;
                      v134.field_0 = (int)&v135.field_48;
                      v46 = (int *)v45;
                      gta2::S202_sub_40CE30((S202 *)&v135.field_50, arg0);
                      v48 = gta2::S202_sub_401B20(v47, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                      v49 = (int *)v48;
                      LOWORD(v48) = unk_66BACC.Index;
                      v134.S202 = (S202 *)v48;
                      v134.field_0 = v50;
                      gta2::S202_sub_40CE30(&v134, a4);
                      pS63 = gta2::Object_SpawnObject(gObject, 21, *v49, *v46, v134.field_0, (int)v134.S202);
                      v134.S202 = (S202 *)&unk_66BA04;
                      v134.field_0 = (int)&v135.CarType;
                      LOWORD(v52) = gta2::bitShiftLeft1(&v135.field_60, *(int *)&v134.field_1C);
                      v53 = gta2::S202_sub_401B20(v52, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                      v134.S202 = (S202 *)&unk_66B93C;
                      v134.field_0 = (int)&v135.bool;
                      v54 = (int *)v53;
                      gta2::S202_sub_40CE30(&v137, arg0);
                      v56 = gta2::S202_sub_401B20(v55, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                      v135.ID = (int)v56;
                      LOWORD(v56) = unk_66BACC.Index;
                      v134.S202 = (S202 *)v56;
                      v134.field_0 = v57;
                      gta2::S202_sub_40CE30(&v134, a4);
                      v58 = gta2::Object_SpawnObject(gObject, 21, *(_DWORD *)v135.ID, *v54, v134.field_0, (int)v134.S202);
                      if ( self->S63 )
                      {
                        if ( self->S63_2 )
                        {
                          if ( self->S63_4 )
                          {
                            if ( self->S63_6 )
                            {
                              if ( self->S63_8 )
                              {
                                if ( !self->S63_10 )
                                {
                                  self->S63_10 = pS63;
                                  self->field_54 = v58;
                                  self->field_80 = pS63->field_14;
                                  self->field_84 = v58->field_14;
                                }
                              }
                              else
                              {
                                self->S63_8 = pS63;
                                self->S63_9 = v58;
                                self->field_78 = pS63->field_14;
                                self->field_7C = v58->field_14;
                              }
                            }
                            else
                            {
                              self->S63_6 = pS63;
                              self->S63_7 = v58;
                              self->field_70 = pS63->field_14;
                              self->field_74 = v58->field_14;
                            }
                          }
                          else
                          {
                            self->S63_4 = pS63;
                            self->S63_5 = v58;
                            self->field_68 = pS63->field_14;
                            self->field_6C = v58->field_14;
                          }
                        }
                        else
                        {
                          self->S63_2 = pS63;
                          self->S63_3 = v58;
                          self->field_60 = pS63->field_14;
                          self->field_64 = v58->field_14;
                        }
                      }
                      else
                      {
                        self->S63 = pS63;
                        self->S63_1_ = v58;
                        self->field_58 = pS63->field_14;
                        self->field_5C = v58->field_14;
                      }
                    }
                    if ( byte_593E60 )
                    {
                      v134.S202 = (S202 *)&unk_66BA04;
                      v134.field_0 = (int)&v135.field_2C;
                      LOWORD(v59) = gta2::bitShiftLeft1(&v135.field_30, *(int *)&v134.field_1C);
                      v60 = (int *)gta2::S202_sub_401B20(v59, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                      v134.S202 = (S202 *)&unk_66B950;
                      v134.field_0 = (int)&v135.field_24;
                      gta2::S202_sub_40CE30((S202 *)&v135.field_1C, arg0);
                      v62 = gta2::S202_sub_401B20(v61, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                      LOWORD(v63) = unk_66BACC.Index;
                      v134.S202 = v63;
                      v134.field_0 = (int)v63;
                      v64 = (Ped **)v62;
                      gta2::S202_sub_40CE30(&v134, a4);
                      v65 = gta2::Police_sub_4A9B40(gPolice, *v64, *v60, v134.field_0, (__int16)v134.S202);
                      if ( self->Ped_ )
                      {
                        if ( self->Ped1 )
                        {
                          if ( self->Ped2 )
                          {
                            if ( self->Ped3 )
                            {
                              if ( self->Ped4 )
                              {
                                if ( !self->Ped5 )
                                  self->Ped5 = v65;
                              }
                              else
                              {
                                self->Ped4 = v65;
                              }
                            }
                            else
                            {
                              self->Ped3 = v65;
                            }
                          }
                          else
                          {
                            self->Ped2 = v65;
                          }
                        }
                        else
                        {
                          self->Ped1 = v65;
                        }
                      }
                      else
                      {
                        self->Ped_ = v65;
                      }
                    }
                  }
                  v23 = *(_DWORD *)&v135.field_10 + 1;
                  v13 = *(_DWORD *)&v134.field_1C + 1;
                  v66 = (unsigned __int8)++HIBYTE(v134.field_18) < LOBYTE(v135.Weapon_);
                  ++*(_DWORD *)&v135.field_10;
                  ++*(_DWORD *)&v134.field_1C;
                  if ( !v66 )
                    break;
                  v7 = arg0;
                }
                self->field = 1;
                self->field_C = 100;
                result = 1;
                break;
              default:
                return 0;
            }
            break;
          }
          break;
        default:
          return 0;
      }
      break;
    }
  }
  else
  {
    v68 = a3;
    *(_DWORD *)&v134.field_1C = a4 - 1;
    while ( 2 )
    {
      --arg0;
      LOBYTE(v135.Car) = 0;
      switch ( gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, arg0, a3, *(int *)&v134.field_1C) )
      {
        case 0:
          v69 = 1;
          ++arg0;
          goto LABEL_89;
        case 1:
          goto LABEL_88;
        case 2:
        case 3:
          if ( LOBYTE(v135.Index) )
          {
            v69 = 1;
          }
          else
          {
            LOBYTE(v135.Index) = 1;
LABEL_88:
            v69 = (char)v135.Car;
          }
LABEL_89:
          if ( ++HIBYTE(v134.field_18) > 0xCu )
            return 0;
          if ( !v69 )
            continue;
          LOBYTE(v135.Weapon_) = 0;
          if ( LOBYTE(v135.Index) == 1 )
          {
            LOBYTE(v135.Weapon_) = 1;
            ++arg0;
          }
          LOBYTE(v135.Index) = 0;
          LOBYTE(v135.field_20) = arg0;
          HIBYTE(v134.field_18) = 0;
          while ( 2 )
          {
            ++arg0;
            LOBYTE(v135.Car) = 0;
            switch ( gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, arg0, a3, *(int *)&v134.field_1C) )
            {
              case 0:
                goto LABEL_99;
              case 1:
                ++LOBYTE(v135.Weapon_);
                v70 = (char)v135.Car;
                goto LABEL_100;
              case 2:
              case 3:
                if ( LOBYTE(v135.Index) )
                {
LABEL_99:
                  v70 = 1;
                }
                else
                {
                  LOBYTE(v135.Index) = 1;
                  ++LOBYTE(v135.Weapon_);
                  v70 = (char)v135.Car;
                }
LABEL_100:
                if ( ++HIBYTE(v134.field_18) > 0xCu )
                  return 0;
                if ( !v70 )
                  continue;
                if ( LOBYTE(v135.Weapon_) > 0xCu )
                  return 0;
                LOBYTE(v73) = v135.field_20;
                gta2::S202_sub_40CE30((S202 *)&v135.field_1C, v135.field_20);
                v135.ID = *v71;
                gta2::S202_sub_40CE30((S202 *)&v135.field_24, a3);
                v73 = (unsigned __int8)v73;
                v135.Car = (Car *)gta2::S202_sub_401B20(v72, (SpriteS1 *)&v135.field_1C, &unk_66BA04)->FirstElement;
                v135.field_20 = LOBYTE(v135.Weapon_);
                LOWORD(v74) = gta2::bitShiftLeft1(&v135.field_1C, (unsigned __int8)v73 + LOBYTE(v135.Weapon_) + 1);
                *(_DWORD *)&v135.Index = *v74;
                gta2::S202_sub_40CE30((S202 *)&v135.field_24, a3);
                *(_DWORD *)&v134.field_1C = gta2::S202_sub_401B20(v75, (SpriteS1 *)&v135.field_1C, &unk_66BA04)->FirstElement;
                gta2::S202_sub_40CE30((S202 *)&v135.field_1C, a4);
                v135.field_4 = *v76;
                *(_DWORD *)&v135.field_18 = gta2::S202_sub_401B20(
                                              (S202 *)&v134.field_1C,
                                              (SpriteS1 *)&v135.field_1C,
                                              &unk_66BA04);
                v77 = (int *)gta2::Player_sub_401B40((Player *)&v135.Car, (S202 *)&v135.field_24, (int)&unk_66BA04);
                gta2::AudioSourceParams_sub_41E350(self->S9, v135.ID, *(int *)&v135.Index, *v77, **(_DWORD **)&v135.field_18);
                *(_DWORD *)&v135.field_18 = gta2::S202_sub_401B20(
                                              (S202 *)&v135.field_4,
                                              (SpriteS1 *)&v135.field_1C,
                                              &byte_66B838);
                v78 = (int *)gta2::Player_sub_401B40((Player *)&v135.field_4, (S202 *)&v135.field_24, (int)&byte_66B838);
                gta2::AudioSourceParams_sub_41E370(self->S9, *v78, **(_DWORD **)&v135.field_18);
                if ( gta2::S56_sub_4477B0(gCheckpoint1, self->S9, 0, 0, 0) )
                  return 0;
                v134.S202 = (S202 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&v135.field_4);
                v79 = gta2::S202_sub_401B20((S202 *)&v134.field_1C, (SpriteS1 *)&v135.field_24, &unk_66BA04);
                v80 = gta2::Player_sub_401B40((Player *)v79, (S202 *)&v135.field_1C, (int)&unk_66B808);
                v134.field_0 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v80);
                v81 = gta2::Player_sub_401B40((Player *)&v135.Car, (S202 *)&v135.field_30, (int)&unk_66BA04);
                v133 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v81);
                v82 = gta2::Player_sub_401B40((Player *)&v135, (S202 *)&v135.field_2C, (int)&unk_66B808);
                v131 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v82);
                v83 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&v135.ID);
                if ( gta2::MapRelatedStruct_sub_466380(gMapRelatedStruct, v83, v131, v133, v134.field_0, (int)v134.S202) )
                  return 0;
                gta2::PoliceRoadblock_sub_4A99F0(self);
                HIBYTE(v134.field_18) = 0;
                if ( LOBYTE(v135.Weapon_) )
                {
                  v135.ID = 0;
                  v84 = 0;
                  *(_DWORD *)&v134.field_1C = (unsigned __int8)v73;
                  while ( 1 )
                  {
                    if ( v84 % 2 )
                    {
                      if ( HIBYTE(v134.field_18) && v84 < v135.field_20 - 1 )
                      {
                        v134.S202 = (S202 *)&stru_66B7D0.TargetCar;
                        v134.field_0 = (int)&v135.field_1C;
                        *(_DWORD *)&v135.field_18 = 16;
                        v85 = gta2::Random_Random(&gRandom, (__int16 *)&v135.field_18);
                        gta2::sub_401AE0(&v135.field_24, v85);
                        v87 = gta2::Player_sub_401B40(v86, (S202 *)v134.field_0, (int)v134.S202);
                        v88 = gta2::Radar_AddBlip((Tango *)&byte_66BA5C, (SpriteS1 *)&v135.field_30, (PublicTransport *)v87);
                        v89 = sub_40F540((Ped *)&v135.Car, (int)v88);
                        LOWORD(v135.field_4) = *(_WORD *)gta2::sub_40E5A0(&unk_66BACC, &v135, v89);
                      }
                      else
                      {
                        LOWORD(v135.field_4) = unk_66BACC.Index;
                      }
                      if ( gta2::CarSystemManager_sub_420CE0(gCarSystemManager, 7) )
                      {
                        switch ( unk_66B798 )
                        {
                          case 1:
                            v134.S202 = (S202 *)&unk_66BA04;
                            v134.field_0 = (int)&v135.field_2C;
                            gta2::S202_sub_40CE30(&v137, v68);
                            v91 = (S202 **)gta2::S202_sub_401B20(v90, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v134.S202 = (S202 *)&unk_66BA04;
                            v134.field_0 = (int)&v135.bool;
                            p_RecycledCars_1 = &v135.field_60;
                            goto LABEL_116;
                          case 2:
                            v134.S202 = (S202 *)&unk_66BA04;
                            v134.field_0 = (int)&v135.CarType;
                            gta2::S202_sub_40CE30((S202 *)&v135.field_50, v68);
                            v96 = gta2::S202_sub_401B20(v95, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v134.S202 = (S202 *)&unk_66BA04;
                            v91 = (S202 **)v96;
                            v134.field_0 = (int)&v135.field_48;
                            p_RecycledCars_1 = &v135.RecycledCars_1;
LABEL_116:
                            LOWORD(v93) = gta2::bitShiftLeft1(p_RecycledCars_1, v73);
                            v94 = (S202 **)gta2::S202_sub_401B20(v93, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v134.S202 = (S202 *)12;
                            goto LABEL_117;
                          case 3:
                            v134.S202 = (S202 *)&unk_66BA04;
                            v134.field_0 = (int)&v135.field_38;
                            gta2::S202_sub_40CE30((S202 *)&v137.field_1C, v68);
                            v98 = gta2::S202_sub_401B20(v97, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v134.S202 = (S202 *)&unk_66BA04;
                            v134.field_0 = (int)&v135.SpriteS1_0;
                            v91 = (S202 **)v98;
                            LOWORD(v99) = gta2::bitShiftLeft1(&v137.field_C, v73);
                            v94 = (S202 **)gta2::S202_sub_401B20(v99, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                            v134.S202 = (S202 *)84;
LABEL_117:
                            v5 = gta2::CarSystemManager_sub_426E40(
                                   gCarSystemManager,
                                   *v94,
                                   *v91,
                                   v135.field_4,
                                   (CarModel *)v134.S202);
                            byte_593E61 = 1;
                            *(_DWORD *)&v135.field_10 = v5;
                            break;
                          case 4:
                            if ( v135.ID != v135.field_20 - 1 )
                            {
                              v134.S202 = (S202 *)&unk_66BA04;
                              v134.field_0 = (int)&v135.field_5C;
                              gta2::S202_sub_40CE30((S202 *)&v139, v68);
                              v101 = (S202 **)gta2::S202_sub_401B20(
                                                v100,
                                                (SpriteS1 *)v134.field_0,
                                                (PublicTransport *)v134.S202);
                              v134.S202 = (S202 *)&unk_66BAB4;
                              v134.field_0 = (int)&v135.field_54;
                              LOWORD(v102) = gta2::bitShiftLeft1(&v137.S202, v73);
                              v103 = (S202 **)gta2::S202_sub_401B20(
                                                v102,
                                                (SpriteS1 *)v134.field_0,
                                                (PublicTransport *)v134.S202);
                              v5 = gta2::CarSystemManager_sub_426E40(
                                     gCarSystemManager,
                                     *v103,
                                     *v101,
                                     v135.field_4,
                                     (CarModel *)0x36);
                              *(_DWORD *)&v135.field_10 = v5;
                              byte_593E61 = 0;
                              byte_593E60 = 0;
                              v104 = gta2::Character_CreatePedInCar(gCharacter, v5);
                              gta2::Ped_SetSearchType(v104, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
                              gta2::Ped_SetCurrentOccupation(v104, ROAD_BLOCK_TANK_MAN);
                              v104->field_228 = 1;
                            }
                            break;
                          default:
                            break;
                        }
                        if ( v5 )
                        {
                          gta2::Car_CarMakeDriveable1(v5, SEARCHTYPE_AREA_PLAYER_ONLY);
                          gta2::Car_sub_424630(v5, 7);
                          if ( gta2::Car_IsEmergencyOrFbiCar(v5) )
                            gta2::Car_sub_422D20(v5);
                          if ( self->Car )
                          {
                            if ( self->Car1 )
                            {
                              if ( self->Car2 )
                              {
                                if ( self->Car3 )
                                {
                                  if ( self->Car4 )
                                    self->Car5 = v5;
                                  else
                                    self->Car4 = v5;
                                }
                                else
                                {
                                  self->Car3 = v5;
                                }
                              }
                              else
                              {
                                self->Car2 = v5;
                              }
                            }
                            else
                            {
                              self->Car1 = v5;
                            }
                          }
                          else
                          {
                            self->Car = v5;
                          }
                        }
                      }
                    }
                    else
                    {
                      if ( byte_593E61 )
                      {
                        v134.S202 = (S202 *)&unk_66BA94;
                        v134.field_0 = (int)&v135.UnitCars;
                        gta2::S202_sub_40CE30((S202 *)&v137.pPlayer, a3);
                        v106 = gta2::S202_sub_401B20(v105, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                        v107 = *(_DWORD *)&v134.field_1C;
                        v108 = (int *)v106;
                        v134.S202 = (S202 *)&unk_66BA04;
                        v134.field_0 = (int)&v135.field_44;
                        LOWORD(v109) = gta2::bitShiftLeft1(&v136, *(int *)&v134.field_1C);
                        v110 = gta2::S202_sub_401B20(v109, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                        LOWORD(v111) = unk_66B804.Index;
                        v134.S202 = v111;
                        v134.field_0 = (int)v111;
                        v112 = (int *)v110;
                        gta2::S202_sub_40CE30(&v134, a4);
                        v113 = gta2::Object_SpawnObject(gObject, 21, *v112, *v108, v134.field_0, (int)v134.S202);
                        v134.S202 = (S202 *)&unk_66B93C;
                        v134.field_0 = (int)&v135.MissionCars;
                        gta2::S202_sub_40CE30((S202 *)&v138, a3);
                        v115 = gta2::S202_sub_401B20(v114, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                        v134.S202 = (S202 *)&unk_66BA04;
                        v134.field_0 = (int)&v137.field_18;
                        v116 = (int *)v115;
                        LOWORD(v117) = gta2::bitShiftLeft1(&v137.field_10, v107);
                        v118 = gta2::S202_sub_401B20(v117, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                        LOWORD(v119) = unk_66B804.Index;
                        v120 = (int *)v118;
                        v134.S202 = v119;
                        v134.field_0 = v121;
                        gta2::S202_sub_40CE30(&v134, a4);
                        v122 = gta2::Object_SpawnObject(gObject, 21, *v120, *v116, v134.field_0, (int)v134.S202);
                        if ( self->S63 )
                        {
                          if ( self->S63_2 )
                          {
                            if ( self->S63_4 )
                            {
                              if ( self->S63_6 )
                              {
                                if ( self->S63_8 )
                                {
                                  if ( !self->S63_10 )
                                  {
                                    self->S63_10 = v113;
                                    self->field_54 = v122;
                                    self->field_80 = v113->field_14;
                                    self->field_84 = v122->field_14;
                                  }
                                }
                                else
                                {
                                  self->S63_8 = v113;
                                  self->S63_9 = v122;
                                  self->field_78 = v113->field_14;
                                  self->field_7C = v122->field_14;
                                }
                              }
                              else
                              {
                                self->S63_6 = v113;
                                self->S63_7 = v122;
                                self->field_70 = v113->field_14;
                                self->field_74 = v122->field_14;
                              }
                            }
                            else
                            {
                              self->S63_4 = v113;
                              self->S63_5 = v122;
                              self->field_68 = v113->field_14;
                              self->field_6C = v122->field_14;
                            }
                          }
                          else
                          {
                            self->S63_2 = v113;
                            self->S63_3 = v122;
                            self->field_60 = v113->field_14;
                            self->field_64 = v122->field_14;
                          }
                        }
                        else
                        {
                          self->S63 = v113;
                          self->S63_1_ = v122;
                          self->field_58 = v113->field_14;
                          self->field_5C = v122->field_14;
                        }
                      }
                      if ( byte_593E60 )
                      {
                        v134.S202 = (S202 *)&unk_66B950;
                        v134.field_0 = (int)&v137.CarSystemManager;
                        gta2::S202_sub_40CE30((S202 *)&v135.Player, a3);
                        v124 = (int *)gta2::S202_sub_401B20(v123, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                        v134.S202 = (S202 *)&unk_66BA04;
                        v134.field_0 = (int)&v135.RecycledCars;
                        LOWORD(v125) = gta2::bitShiftLeft1(&v140, *(int *)&v134.field_1C);
                        v126 = gta2::S202_sub_401B20(v125, (SpriteS1 *)v134.field_0, (PublicTransport *)v134.S202);
                        LOWORD(v127) = unk_66B804.Index;
                        v134.S202 = v127;
                        v134.field_0 = (int)v127;
                        v128 = (Ped **)v126;
                        gta2::S202_sub_40CE30(&v134, a4);
                        v129 = gta2::Police_sub_4A9B40(gPolice, *v128, *v124, v134.field_0, (__int16)v134.S202);
                        if ( self->Ped_ )
                        {
                          if ( self->Ped1 )
                          {
                            if ( self->Ped2 )
                            {
                              if ( self->Ped3 )
                              {
                                if ( self->Ped4 )
                                {
                                  if ( !self->Ped5 )
                                    self->Ped5 = v129;
                                }
                                else
                                {
                                  self->Ped4 = v129;
                                }
                              }
                              else
                              {
                                self->Ped3 = v129;
                              }
                            }
                            else
                            {
                              self->Ped2 = v129;
                            }
                          }
                          else
                          {
                            self->Ped1 = v129;
                          }
                        }
                        else
                        {
                          self->Ped_ = v129;
                        }
                      }
                    }
                    v84 = v135.ID + 1;
                    v73 = *(_DWORD *)&v134.field_1C + 1;
                    v66 = (unsigned __int8)++HIBYTE(v134.field_18) < LOBYTE(v135.Weapon_);
                    ++v135.ID;
                    ++*(_DWORD *)&v134.field_1C;
                    if ( !v66 )
                      break;
                    v68 = a3;
                    v5 = *(Car **)&v135.field_10;
                  }
                }
LABEL_163:
                self->field = 1;
                self->field_C = 100;
                result = 1;
                break;
              default:
                return 0;
            }
            break;
          }
          break;
        default:
          return 0;
      }
      break;
    }
  }
  return result;
}



