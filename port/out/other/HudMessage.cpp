#include "gta2_shim.h"

// Module: other, Class: HudMessage
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004c5fe0: HudMessage::ShowBigOnScreenLabel_0
// IDA: HudMessage::ShowBigOnScreenLabel_0
// Ghidra: ---
void gta2::HudMessage_ShowBigOnScreenLabel_0(HudMessage *self)
{
  int v2; // eax

  if ( self->m_nTimeToShow )
  {
    gta2::HudBrief_sub_4C2450((HudBrief *)self->str, self->gap, 580, (__int16)unk_672F2C);
    LOWORD(v2) = gta2::Font_GetStringWidth(self->str, (__int16)unk_672F2C);
    self->m_nStringWidth = (unsigned __int16)((640 - v2) / 2);
    self->m_nNumberLines = (unsigned __int16)((480 - gta2::Font_GetNumberLines(self->str, (__int16)unk_672F2C)) / 4);
  }
}


// 0x004c6060: HudMessage::ShowBigOnScreenLabel
// IDA: HudMessage::ShowBigOnScreenLabel
// Ghidra: ---
void gta2::HudMessage_ShowBigOnScreenLabel(HudMessage *self, wchar_t *a2, int a3)
{
  const wchar_t *retaddr; // [esp+4h] [ebp+0h]

  if ( !self->m_nTimeToShow || (int)a2 >= self->m_nType )
  {
    self->m_nType = (int)a2;
    CopyWideString(self->gap, retaddr);
    gta2::Text_ConvertWordsToBig(gText, self->gap);
    self->m_nTimeToShow = 90;
    gta2::HudMessage_ShowBigOnScreenLabel_0(self);
  }
}


// 0x004c60b0: HudMessage::DicrementTimeToShow
// IDA: HudMessage::DicrementTimeToShow
// Ghidra: ---
char gta2::HudMessage_DicrementTimeToShow(HudMessage *self)
{
  char result; // al

  result = self->m_nTimeToShow;
  if ( self->m_nTimeToShow )
    self->m_nTimeToShow = --result;
  return result;
}


// 0x004c60c0: HudMessage::HudMessage
// IDA: HudMessage::HudMessage
// Ghidra: ---
void gta2::HudMessage_HudMessage(HudMessage *self)
{
  self->m_nTimeToShow = 0;
  self->m_nType = 1;
}


// 0x004c8a40: HudMessage::sub_4C8A40
// IDA: HudMessage::sub_4C8A40
// Ghidra: ---
void gta2::HudMessage_sub_4C8A40(HudMessage *self)
{
  HudMessage *v1; // esi
  int m_nNumberLines; // edx
  int m_nStringWidth; // eax
  int v4; // ecx
  S202 v5; // [esp-1Ch] [ebp-24h] BYREF
  int v6; // [esp+4h] [ebp-4h] BYREF

  v1 = self;
  if ( self->m_nTimeToShow )
  {
    LOWORD(self) = (_WORD)unk_672F2C;
    m_nNumberLines = v1->m_nNumberLines;
    memset(&v5.field_10, 0, 12);
    v5.field_C = (int)&v6;
    v5.CarSystemManager = (CarSystemManager *)self;
    v5.S202 = (S202 *)self;
    v6 = 2;
    gta2::S202_sub_41F980((S202 *)&v5.S202, m_nNumberLines);
    m_nStringWidth = v1->m_nStringWidth;
    v5.field_0 = v4;
    gta2::S202_sub_41F980(&v5, m_nStringWidth);
    sub_4C7280(v1->str, v5.field_0, (SpriteS1 *)v5.S202);
  }
}



