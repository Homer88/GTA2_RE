#include "gta2_shim.h"

// Module: other, Class: S86_10
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004c71a0: S86_10::S86_10
// IDA: S86_10::S86_10
// Ghidra: ---
void gta2::S86_10_S86_10(struct S86_10 *self)
{
  self->field_0 = 0;
  self->field_1 = 45;
}


// 0x004c9fa0: S86_10::sub_4C9FA0
// IDA: S86_10::sub_4C9FA0
// Ghidra: ---
void gta2::S86_10_sub_4C9FA0(struct S86_10 *self)
{
  struct Game *pGame; // edi
  int v2; // esi
  struct CarSystemManager *v3; // edx
  int v4; // ecx
  struct Hud *v5; // ecx
  struct CarSystemManager *v6; // ecx
  int v7; // ecx
  struct Hud *v8; // ecx
  struct CarSystemManager *v9; // eax
  struct S202 *v10; // ecx
  int v11; // ecx
  struct Hud *v12; // ecx
  wchar_t *v13; // edi
  struct CarSystemManager *v14; // eax
  struct CarSystemManager *v15; // ebx
  struct S202 *v16; // ecx
  int v17; // ecx
  char *pscore; // eax
  int v19; // ebx
  int v20; // eax
  struct S202 *v21; // ecx
  int v22; // edi
  unsigned __int16 GlobalSpriteId; // ax
  unsigned __int8 sprite_width; // al
  struct CarSystemManager *v25; // ecx
  int v26; // ebp
  int v27; // edi
  int v28; // ecx
  struct Hud *v29; // ecx
  struct CarSystemManager *v30; // eax
  int v31; // edi
  unsigned __int8 *FirstUsedGang; // esi
  struct Player **v33; // eax
  struct Player *v34; // eax
  int v35; // ecx
  unsigned __int8 *NextUsedGang; // esi
  struct Player **v37; // eax
  struct Player *v38; // eax
  char *pgmiss; // eax
  struct Player **v40; // eax
  char *pgmiss_1; // eax
  struct Player **v42; // eax
  struct Player *v43; // eax
  char *pmiss; // eax
  struct Player **v45; // eax
  struct Player *v46; // eax
  char *psec; // eax
  int v48; // eax
  char *pbon; // eax
  int v50; // eax
  int v51; // kr04_4
  int v52; // ecx
  S202 v53; // [esp-1Ch] [ebp-34h] BYREF
  int a2; // [esp+10h] [ebp-8h] BYREF
  int mode; // [esp+14h] [ebp-4h] BYREF

  pGame = gGame;
  mode = (int)self;
  v2 = 0;
  if ( gta2::Game_GetIsUserPaused(gGame) && !pGame->PlayerMain->quit1 )
  {
    LOWORD(v3) = unk_672F98.Index;
    memset(&v53.field_10, 0, 12);
    v53.field_C = (int)&a2;
    v53.CarSystemManager = v3;
    v53.S202 = (struct S202 *)&a2;
    a2 = 2;
    gta2::bitShiftLeft1(&v53.S202, 180);
    v53.field_0 = v4;
    gta2::bitShiftLeft1(&v53, 227);
    gta2::Hud_DrawSprite(
      v5,
      6,
      134,
      v53.field_0,
      (int)v53.S202,
      (char)v53.CarSystemManager,
      (const int *)v53.field_C,
      (int)v53.field_10,
      (int)v53.pPlayer);
    LOWORD(v6) = unk_672F98.Index;
    memset(&v53.field_10, 0, 12);
    v53.field_C = (int)&a2;
    v53.CarSystemManager = v6;
    v53.S202 = (struct S202 *)v6;
    a2 = 2;
    gta2::bitShiftLeft1(&v53.S202, 180);
    v53.field_0 = v7;
    gta2::bitShiftLeft1(&v53, 320);
    v9 = (struct CarSystemManager *)gta2::Hud_DrawSprite(
                               v8,
                               6,
                               136,
                               v53.field_0,
                               (int)v53.S202,
                               (char)v53.CarSystemManager,
                               (const int *)v53.field_C,
                               (int)v53.field_10,
                               (int)v53.pPlayer);
    LOWORD(v9) = unk_672F98.Index;
    memset(&v53.field_10, 0, 12);
    v53.field_C = (int)&a2;
    v53.CarSystemManager = v9;
    v53.S202 = v10;
    a2 = 2;
    gta2::bitShiftLeft1(&v53.S202, 180);
    v53.field_0 = v11;
    gta2::bitShiftLeft1(&v53, 413);
    gta2::Hud_DrawSprite(
      v12,
      6,
      135,
      v53.field_0,
      (int)v53.S202,
      (char)v53.CarSystemManager,
      (const int *)v53.field_C,
      (int)v53.field_10,
      (int)v53.pPlayer);
    v13 = gta2::Text__Bsearch(gText, "pause");
    LOWORD(v14) = gta2::Font_GetStringWidth(v13, unk_672F20);
    v15 = v14;
    LOWORD(v14) = unk_672F20;
    memset(&v53.field_10, 0, 12);
    v53.field_C = (int)&a2;
    v53.CarSystemManager = v14;
    v53.S202 = v16;
    a2 = 2;
    gta2::bitShiftLeft1(&v53.S202, 158);
    v53.field_0 = v17;
    gta2::S202_sub_41F980(&v53, (640 - (int)v15) / 2);
    sub_4C7280(v13, v53.field_0, (struct SpriteS1 *)v53.S202);
    if ( !gta2::MapGm_GetGang(&gMapGm) )
    {
      switch ( *(_BYTE *)mode )
      {
        case 0:
          v53.field_18 = gMissionManager->Health;
          pscore = (char *)gta2::Text__Bsearch(gText, "pscore");
          ShowTextDisplay(&TextWcharT, pscore);
          goto LABEL_6;
        case 1:
          FirstUsedGang = (unsigned __int8 *)gta2::Gangs_GetFirstUsedGang(gGangs);
          v33 = (Player **)gMissionManager->field_32C;
          if ( v33 )
          {
            v34 = *v33;
            v35 = gMissionManager->field_31C;
          }
          else
          {
            v35 = gMissionManager->field_31C;
            v34 = 0;
          }
          goto LABEL_20;
        case 2:
          gta2::Gangs_GetFirstUsedGang(gGangs);
          NextUsedGang = (unsigned __int8 *)gta2::Gangs_GetNextUsedGang(gGangs);
          v37 = (Player **)gMissionManager->field_330;
          if ( v37 )
            v38 = *v37;
          else
            v38 = 0;
          v53.field_18 = gMissionManager->field_320;
          v53.pPlayer = v38;
          v53.field_10 = (struct Weapon *)gta2::sub_45DD20(NextUsedGang);
          pgmiss = (char *)gta2::Text__Bsearch(gText, "pgmiss");
          ShowTextDisplay(&TextWcharT, pgmiss);
          LOWORD(NextUsedGang) = NextUsedGang[312];
          v19 = 6;
          v2 = (int)(NextUsedGang + 63);
          goto LABEL_7;
        case 3:
          gta2::Gangs_GetFirstUsedGang(gGangs);
          gta2::Gangs_GetNextUsedGang(gGangs);
          FirstUsedGang = (unsigned __int8 *)gta2::Gangs_GetNextUsedGang(gGangs);
          v40 = (Player **)gMissionManager->field_334;
          if ( v40 )
            v34 = *v40;
          else
            v34 = 0;
          v35 = gMissionManager->field_324;
LABEL_20:
          v53.field_18 = v35;
          v53.pPlayer = v34;
          v53.field_10 = (struct Weapon *)gta2::sub_45DD20(FirstUsedGang);
          pgmiss_1 = (char *)gta2::Text__Bsearch(gText, "pgmiss");
          ShowTextDisplay(&TextWcharT, pgmiss_1);
          LOWORD(FirstUsedGang) = FirstUsedGang[312];
          v19 = 6;
          v2 = (int)(FirstUsedGang + 63);
          goto LABEL_7;
        case 4:
          v42 = (Player **)gMissionManager->field_328;
          if ( v42 )
            v43 = *v42;
          else
            v43 = 0;
          v53.field_18 = gMissionManager->field_314;
          v53.pPlayer = v43;
          pmiss = (char *)gta2::Text__Bsearch(gText, "pmiss");
          ShowTextDisplay(&TextWcharT, pmiss);
          goto LABEL_6;
        case 5:
          v45 = (Player **)gMissionManager->field_338;
          if ( v45 )
            v46 = *v45;
          else
            v46 = 0;
          v53.field_18 = gMissionManager->field_318;
          v53.pPlayer = v46;
          psec = (char *)gta2::Text__Bsearch(gText, "psec");
          ShowTextDisplay(&TextWcharT, psec);
          v19 = 4;
          LOWORD(v48) = gta2::S57_sub_4C6E30((struct PathNode *)gCarSystemManager2.field_24, 286);
          v2 = v48;
          goto LABEL_7;
        case 6:
          v53.field_18 = 50;
          v53.pPlayer = (struct Player *)gta2::MapGm_GetSpecialTokens(&gMapGm);
          pbon = (char *)gta2::Text__Bsearch(gText, "pbon");
          ShowTextDisplay(&TextWcharT, pbon);
          v19 = 4;
          LOWORD(v50) = gta2::S57_sub_4C6E30((struct PathNode *)gCarSystemManager2.field_24, 266);
          v2 = v50;
          goto LABEL_7;
        default:
LABEL_6:
          v19 = a2;
LABEL_7:
          LOWORD(v20) = gta2::Font_GetStringWidth(&TextWcharT, Len);
          v22 = v20;
          if ( (_WORD)v2 )
          {
            GlobalSpriteId = gta2::Style_GetGlobalSpriteId(gStyle, v19, v2);
            sprite_width = gta2::Style_get_sprite_width(gStyle, GlobalSpriteId);
            LOWORD(v25) = unk_672F98.Index;
            v26 = sprite_width + 10;
            memset(&v53.field_10, 0, 12);
            mode = 2;
            v53.field_C = (int)&mode;
            v53.CarSystemManager = v25;
            v53.S202 = (struct S202 *)v25;
            v27 = (640 - v26 - v22) / 2;
            gta2::bitShiftLeft1(&v53.S202, 235);
            v53.field_0 = v28;
            gta2::S202_sub_41F980(&v53, v27 + v26 / 2);
            v30 = (struct CarSystemManager *)gta2::Hud_DrawSprite(
                                        v29,
                                        v19,
                                        v2,
                                        v53.field_0,
                                        (int)v53.S202,
                                        (char)v53.CarSystemManager,
                                        (const int *)v53.field_C,
                                        (int)v53.field_10,
                                        (int)v53.pPlayer);
            v31 = v26 + v27;
          }
          else
          {
            v51 = 640 - v20;
            v30 = (struct CarSystemManager *)(640 - v20 - ((640 - v20) >> 31));
            v31 = v51 / 2;
          }
          LOWORD(v30) = Len;
          v53.field_18 = 0;
          v53.pPlayer = 0;
          v53.field_10 = (struct Weapon *)6;
          v53.field_C = (int)&mode;
          v53.CarSystemManager = v30;
          v53.S202 = v21;
          mode = 8;
          gta2::bitShiftLeft1(&v53.S202, 220);
          v53.field_0 = v52;
          gta2::S202_sub_41F980(&v53, v31);
          sub_4C7280(&TextWcharT, v53.field_0, (struct SpriteS1 *)v53.S202);
          break;
      }
    }
  }
}



