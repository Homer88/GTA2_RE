#include "gta2_shim.h"

// Module: other, Class: MissionScriptObjects
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004767a0: MissionScriptObjects::RemoveFirstElement
// IDA: MissionScriptObjects::RemoveFirstElement
// Ghidra: ---
MissionScriptObjectData * gta2::MissionScriptObjects_RemoveFirstElement(struct MissionScriptObjects *self)
{
  MissionScriptObjectData *FirstElement; // ecx
  MissionScriptObjectData *v3; // ecx

  FirstElement = self->FirstElement;
  self->FirstElement = FirstElement->NextElement;
  FirstElement->NextElement = self->MissionScriptObjectDataNextElement;
  self->MissionScriptObjectDataNextElement = FirstElement;
  gta2::MissionScriptObjectData_sub_4751B0(FirstElement);
  return v3;
}


// 0x004812e0: MissionScriptObjects::MissionScriptObjectsDes
// IDA: MissionScriptObjects::MissionScriptObjectsDes
// Ghidra: ---
int gta2::MissionScriptObjects_MissionScriptObjectsDes(struct MissionScriptObjects *self)
{
  self->FirstElement = 0;
  self->MissionScriptObjectDataNextElement = 0;
  return gta2::Construct_0(self->MissionScriptObjectData_, 284, 8, MissionScriptObjectData::MissionScriptObjectData_Des);
}


// 0x00481310: MissionScriptObjects::MissionScriptObjects
// IDA: MissionScriptObjects::MissionScriptObjects
// Ghidra: ---
MissionScriptObjects * gta2::MissionScriptObjects_MissionScriptObjects(struct MissionScriptObjects *self)
{
  MissionScriptObjectData *pS28; // esi

  pS28 = self->MissionScriptObjectData_;
  gta2::Construct(
    self->MissionScriptObjectData_,
    284,
    8,
    MissionScriptObjectData::MissionScriptObjectData,
    MissionScriptObjectData::MissionScriptObjectData_Des);
  pS28->NextElement = pS28 + 1;
  pS28[1].NextElement = pS28 + 2;
  pS28[2].NextElement = pS28 + 3;
  pS28[3].NextElement = pS28 + 4;
  pS28[4].NextElement = pS28 + 5;
  pS28[5].NextElement = pS28 + 6;
  pS28[6].NextElement = pS28 + 7;
  self->MissionScriptObjectData_[7].NextElement = 0;
  self->MissionScriptObjectDataNextElement = 0;
  self->field_8E8 = 0;
  self->FirstElement = pS28;
  return self;
}


// 0x00481380: MissionScriptObjects::sub_481380
// IDA: MissionScriptObjects::sub_481380
// Ghidra: ---
void gta2::MissionScriptObjects_sub_481380(struct MissionScriptObjects *self)
{
  MissionScriptObjectData *MissionScriptObjectDataNextElement; // esi
  MissionScriptObjectData *v3; // edi
  MissionScriptObjectData *NextElement; // ebp
  MissionScriptObjectData *v5; // eax
  MissionScriptObjectData *FirstElement; // eax

  MissionScriptObjectDataNextElement = self->MissionScriptObjectDataNextElement;
  v3 = 0;
  self->field_8E8 = 0;
  if ( MissionScriptObjectDataNextElement )
  {
    do
    {
      ++self->field_8E8;
      NextElement = MissionScriptObjectDataNextElement->NextElement;
      if ( gta2::MissionScriptObjectData_sub_481120(MissionScriptObjectDataNextElement) )
      {
        if ( !v3 )
          goto LABEL_6;
        if ( v3->NextElement != MissionScriptObjectDataNextElement )
        {
          v3 = 0;
LABEL_6:
          v5 = self->MissionScriptObjectDataNextElement;
          if ( v5 == MissionScriptObjectDataNextElement )
          {
            FirstElement = self->FirstElement;
            self->MissionScriptObjectDataNextElement = MissionScriptObjectDataNextElement->NextElement;
            MissionScriptObjectDataNextElement->NextElement = FirstElement;
            self->FirstElement = MissionScriptObjectDataNextElement;
          }
          else
          {
            v3 = self->MissionScriptObjectDataNextElement;
            if ( v5->NextElement != MissionScriptObjectDataNextElement )
            {
              do
                v3 = v3->NextElement;
              while ( v3->NextElement != MissionScriptObjectDataNextElement );
            }
            v3->NextElement = MissionScriptObjectDataNextElement->NextElement;
            MissionScriptObjectDataNextElement->NextElement = self->FirstElement;
            self->FirstElement = MissionScriptObjectDataNextElement;
          }
          goto LABEL_13;
        }
        v3->NextElement = MissionScriptObjectDataNextElement->NextElement;
        MissionScriptObjectDataNextElement->NextElement = self->FirstElement;
        self->FirstElement = MissionScriptObjectDataNextElement;
      }
      else
      {
        v3 = MissionScriptObjectDataNextElement;
      }
LABEL_13:
      MissionScriptObjectDataNextElement = NextElement;
    }
    while ( NextElement );
  }
}


// 0x00481c10: MissionScriptObjects::MissionScriptObjects_des
// IDA: MissionScriptObjects::MissionScriptObjects_des
// Ghidra: ---
MissionScriptObjects * gta2::MissionScriptObjects_MissionScriptObjects_des(struct MissionScriptObjects *self, char a2)
{
  gta2::MissionScriptObjects_MissionScriptObjectsDes(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}



