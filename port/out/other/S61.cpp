#include "gta2_shim.h"

// Module: other, Class: S61
// Functions: 9
// Source: unified (IDA+Ghidra)

// 0x004829a0: S61::sub_4829A0
// IDA: S61::sub_4829A0
// Ghidra: ---
EventHandler * gta2::S61_sub_4829A0(struct CollisionBox *self)
{
  struct EventHandler *pS63; // edx
  struct EventHandler *FirstElement; // esi

  pS63 = self->pS63;
  FirstElement = self->FirstElement;
  self->FirstElement = self->FirstElement->NextElement;
  FirstElement->NextElement = pS63;
  self->pS63 = FirstElement;
  gta2::sub_482490((int)FirstElement);
  return FirstElement;
}


// 0x004829c0: S61::sub_4829C0
// IDA: S61::sub_4829C0
// Ghidra: ---
EventHandler * gta2::S61_sub_4829C0(struct CollisionBox *self)
{
  struct EventHandler *FirstElement; // esi

  FirstElement = self->FirstElement;
  self->FirstElement = self->FirstElement->NextElement;
  FirstElement->NextElement = 0;
  gta2::sub_482490((int)FirstElement);
  return FirstElement;
}


// 0x004829e0: S61::sub_4829E0
// IDA: S61::sub_4829E0
// Ghidra: ---
EventHandler * gta2::S61_sub_4829E0(struct CollisionBox *self, EventHandler *a2)
{
  struct EventHandler *result; // eax

  result = a2;
  a2->NextElement = self->pS63;
  self->pS63 = a2;
  return result;
}


// 0x004829f0: S61::sub_4829F0
// IDA: S61::sub_4829F0
// Ghidra: ---
EventHandler * gta2::S61_sub_4829F0(struct CollisionBox *self, EventHandler *a2)
{
  struct EventHandler *v2; // eax

  *(_QWORD *)&v2 = (unsigned int)self->pS63;
  if ( v2 )
  {
    while ( v2 != a2 )
    {
      *(&v2 + 1) = v2;
      v2 = v2->NextElement;
      if ( !v2 )
        return v2;
    }
    if ( *(&v2 + 1) )
      (*(&v2 + 1))->NextElement = v2->NextElement;
    else
      self->pS63 = v2->NextElement;
    v2->NextElement = 0;
  }
  return v2;
}


// 0x00483ea0: S61::sub_483EA0
// IDA: S61::sub_483EA0
// Ghidra: ---
int gta2::S61_sub_483EA0(struct CollisionBox *self)
{
  self->FirstElement = 0;
  self->pS63 = 0;
  return gta2::Construct_0(self->S63, 44, 3825, S63::S63_dec);
}


// 0x00483f10: S61::S61
// IDA: S61::S61
// Ghidra: ---
CollisionBox * gta2::S61_S61(struct CollisionBox *self)
{
  struct EventHandler *S63; // edi
  struct EventHandler *pS63; // eax
  int count; // edx

  S63 = self->S63;
  gta2::Construct(self->S63, 0x2C, 3825, S63::S63, S63::S63_dec);
  pS63 = S63;
  count = 3824;
  do
  {
    --count;
    pS63->NextElement = pS63 + 1;
    ++pS63;
  }
  while ( count );
  self->FirstElement = S63;
  self->S63[3824].NextElement = 0;
  self->pS63 = 0;
  self->field_29174 = 0;
  return self;
}


// 0x00484820: S61::S61_Des
// IDA: S61::S61_Des
// Ghidra: ---
CollisionBox * gta2::S61_S61_Des(struct CollisionBox *self, char a2)
{
  gta2::S61_sub_483EA0(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}


// 0x00484d60: S61::sub_484D60
// IDA: S61::sub_484D60
// Ghidra: ---
SpriteS1 * gta2::S61_sub_484D60(struct CollisionBox *self, SpriteS1 *a2)
{
  struct SpriteS1 *pS63; // esi
  struct SpriteS1 *v4; // edi
  struct SpriteS1 *result; // eax
  struct EventHandler *FirstElement; // edx

  pS63 = (struct SpriteS1 *)self->pS63;
  v4 = 0;
  if ( pS63 )
  {
    result = a2;
    while ( pS63 != a2 )
    {
      v4 = pS63;
      pS63 = pS63->FirstElement;
      if ( !pS63 )
        return result;
    }
    result = gta2::S63_sub_484910((struct EventHandler *)pS63);
    if ( v4 )
    {
      result = pS63->FirstElement;
      v4->FirstElement = pS63->FirstElement;
      pS63->FirstElement = (struct SpriteS1 *)self->FirstElement;
    }
    else
    {
      FirstElement = self->FirstElement;
      self->pS63 = (struct EventHandler *)pS63->FirstElement;
      pS63->FirstElement = (struct SpriteS1 *)FirstElement;
    }
    self->FirstElement = (struct EventHandler *)pS63;
  }
  return result;
}


// 0x00484db0: S61::sub_484DB0
// IDA: S61::sub_484DB0
// Ghidra: ---
EventHandler * gta2::S61_sub_484DB0(struct CollisionBox *self, EventHandler *a2)
{
  struct EventHandler *result; // eax

  gta2::S63_sub_484910(a2);
  result = self->FirstElement;
  a2->NextElement = self->FirstElement;
  self->FirstElement = a2;
  return result;
}



