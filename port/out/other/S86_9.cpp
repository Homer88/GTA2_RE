#include "gta2_shim.h"

// Module: other, Class: S86_9
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c6a60: S86_9::sub_4C6A60
// IDA: S86_9::sub_4C6A60
// Ghidra: FUN_004c6a60
void gta2::S86_9_sub_4C6A60(void *self)
{
  int iVar1;
  
                              // WARNING: Load size is inaccurate
  if (*self != '\0') {
    iVar1 = gta2::Font_GetStringWidth((wchar_t *)((int)self + 2),_DAT_00672f24);
    *(int *)((int)self + 0xcc) = iVar1;
  }
  return;
}


// 0x004c6a80: S86_9::sub_4C6A80
// IDA: S86_9::sub_4C6A80
// Ghidra: FUN_004c6a80
void gta2::S86_9_sub_4C6A80(void *self,wchar_t *param_1)
{
  *(undefined1 *)self = 0x78;
  CopyWideString((wchar_t *)((int)self + 2),param_1);
  FUN_004c6a60(self);
  return;
}


// 0x004c9750: S86_9::sub_4C9750
// IDA: S86_9::sub_4C9750
// Ghidra: ---
void gta2::S86_9_sub_4C9750(S86_9 *self, Player *a2, Player *a3)
{
  char *v4; // eax
  wchar_t *v5; // eax
  wchar_t *v6; // eax
  wchar_t *v7; // [esp-8h] [ebp-10h]
  wchar_t *v8; // [esp-8h] [ebp-10h]

  if ( gta2::Player_GetCurrentPlayer(a2) )
  {
    if ( gta2::Player_GetCurrentPlayer(a3) )
    {
      v4 = (char *)gta2::Text__Bsearch(gText, "mpkill1");
      ShowTextDisplay(&TextWcharT, v4);
    }
    else
    {
      v5 = gta2::Text__Bsearch(gText, "mpkill2");
      ShowTextDisplay(&TextWcharT, (char *)L"%s %s", v5, a3->string_Arr0x16);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_LAUGH__changes_each_time_you_play_it);
    }
    goto LABEL_4;
  }
  if ( gta2::Player_GetCurrentPlayer(a3) )
  {
    v7 = gta2::Text__Bsearch(gText, "mpkill3");
    ShowTextDisplay(&TextWcharT, (char *)L"%s %s", a2->string_Arr0x16, v7);
LABEL_4:
    gta2::S86_9_sub_4C6A80(self, &TextWcharT);
    return;
  }
  if ( a3 == a2 )
  {
    v8 = gta2::Text__Bsearch(gText, "mpkill5");
    ShowTextDisplay(&TextWcharT, (char *)L"%s %s", a3->string_Arr0x16, v8);
    goto LABEL_4;
  }
  v6 = gta2::Text__Bsearch(gText, "mpkill4");
  ShowTextDisplay(&TextWcharT, (char *)L"%s %s %s", a2->string_Arr0x16, v6, a3->string_Arr0x16);
  gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_laugh6);
  gta2::S86_9_sub_4C6A80(self, &TextWcharT);
}



