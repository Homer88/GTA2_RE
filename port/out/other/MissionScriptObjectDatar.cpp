#include "gta2_shim.h"

// Module: other, Class: MissionScriptObjectDatar
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00478a80: MissionScriptObjectDatar::sub_478A80
// IDA: MissionScriptObjectDatar::sub_478A80
// Ghidra: ---
void gta2::MissionScriptObjectDatar_sub_478A80(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *started; // ebx

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  switch ( v1->field_2 )
  {
    case '/':
    case '0':
    case '2':
    case '3':
      gta2::MissionScriptObjectData_sub_476FF0(self, (int)v1);
      goto LABEL_4;
    case '1':
    case '4':
      gta2::MissionScriptObjectData_sub_476EA0(self, (int)v1);
LABEL_4:
      v1 = dword_6644CC;
      break;
    default:
      break;
  }
  if ( !self->field_118 )
    gta2::TrafficManager_sub_476D50(gTrafficManager, (S32 *)started->arr_96[1], 0);
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x00481400: MissionScriptObjectDatar::sub_481400
// IDA: MissionScriptObjectDatar::sub_481400
// Ghidra: ---
char * gta2::MissionScriptObjectDatar_sub_481400(struct MissionScriptObjectData *self)
{
  int Index; // esi
  unsigned __int8 v2; // dl
  ushort *v3; // eax
  char *result; // eax
  unsigned __int8 v5; // dl
  unsigned __int16 i; // di
  MissionManager *started; // eax
  int v9; // ecx
  S107 *pS107; // ecx

  for ( i = 1; i < 0x1770u; ++i )
  {
    started = gta2::MissionManager_StartMission(gMissionManager, i);
    if ( started )
    {
      v9 = started->field_2;
      if ( (unsigned __int16)v9 > 240u )
      {
        switch ( started->field_2 )
        {
          case 0x117u:
          case 0x141u:
LABEL_38:
            gta2::MissionScriptObjectData_sub_4755F0(self, (int)started);
            break;
          case 0x11Du:
          case 0x11Eu:
            gta2::MissionScriptObjectData_sub_4752F0(self, (int)started);
            break;
          case 0x11Fu:
            gta2::MissionScriptObjectData_sub_4753B0(self, (int)started);
            break;
          case 0x127u:
          case 0x128u:
          case 0x129u:
          case 0x12Au:
            gta2::MissionScriptObjectData_sub_4753D0(self, (int)started);
            break;
          case 0x12Eu:
LABEL_28:
            gta2::MissionScriptObjectData_sub_47F710(self, (int)started);
            break;
          case 0x130u:
            gta2::MissionScriptObjectData_sub_475420(self, started);
            break;
          case 0x147u:
            gta2::MissionScriptObjectData_sub_475460(self, (int)started);
            break;
          case 0x157u:
            gta2::MissionScriptObjectData_sub_4755B0(self, (int)started);
            break;
          case 0x158u:
          case 0x159u:
          case 0x182u:
          case 0x183u:
          case 0x184u:
            gta2::MissionScriptObjectData_sub_4754E0(self, (int)started);
            break;
          case 0x15Au:
          case 0x15Bu:
          case 0x15Cu:
          case 0x15Du:
          case 0x185u:
          case 0x186u:
            gta2::MissionScriptObjectData_sub_478170(self, (int)started);
            break;
          case 0x161u:
            gta2::MissionScriptObjectData_sub_4755D0(self, (int)started);
            break;
          case 0x177u:
          case 0x17Au:
            gta2::MissionScriptObjectData_sub_477D20(self, (int)started);
            break;
          case 0x178u:
          case 0x17Bu:
            gta2::MissionScriptObjectData_sub_477EE0(self, (int)started);
            break;
          case 0x1A6u:
            gta2::MissionScriptObjectData_sub_4756B0(self, (int)started);
            break;
          case 0x1A9u:
          case 0x1AAu:
          case 0x1ABu:
          case 0x1ACu:
            gta2::MissionScriptObjectData_sub_477530(self, (int)started);
            break;
          case 0x1ADu:
          case 0x1AEu:
          case 0x1AFu:
            goto LABEL_27;
          case 0x1B2u:
LABEL_24:
            gta2::MissionScriptObjectData_sub_477AC0(self, (int)started);
            break;
          case 0x1B3u:
          case 0x1B4u:
          case 0x1B5u:
            gta2::MissionScriptObjectData_sub_475650(self, (int)started);
            break;
          case 0x1B7u:
            gta2::MissionScriptObjectData_sub_4784A0(self, (int)started);
            break;
          default:
            continue;
        }
      }
      else if ( (unsigned __int16)v9 == 240 )
      {
LABEL_27:
        gta2::MissionScriptObjectData_sub_478120(self, (int)started);
      }
      else
      {
        switch ( started->field_2 )
        {
          case 5u:
            gta2::MissionScriptObjectData_sub_477140(self, (int)started);
            break;
          case 7u:
          case 8u:
            gta2::MissionScriptObjectData_sub_477560(self, (int)started);
            break;
          case 0xAu:
          case 0xBu:
          case 0xCu:
          case 0xDu:
            gta2::MissionScriptObjectData_sub_477290(self, (int)started);
            break;
          case 0xFu:
          case 0x10u:
            gta2::MissionScriptObjectData_sub_476EA0(self, (int)started);
            break;
          case 0x11u:
          case 0x12u:
          case 0x13u:
          case 0x14u:
            gta2::MissionScriptObjectData_sub_476FF0(self, (int)started);
            break;
          case 0x17u:
            gta2::MissionScriptObjectData_sub_475290(self, (int)started);
            break;
          case 0x1Au:
          case 0x1Bu:
            gta2::MissionScriptObjectData_sub_4777E0(self, (int)started);
            break;
          case 0x1Du:
          case 0x1Eu:
          case 0x1Fu:
          case 0x20u:
            gta2::MissionScriptObjectData_sub_477870(self, (int)started);
            break;
          case 0x22u:
          case 0x23u:
            gta2::MissionScriptObjectData_sub_477920(self, (int)started);
            break;
          case 0x25u:
          case 0x26u:
          case 0x27u:
            gta2::MissionScriptObjectData_sub_477660(self, (int)started);
            break;
          case 0x28u:
            gta2::MissionScriptObjectData_sub_4752A0(self, (int)started);
            break;
          case 0x66u:
            gta2::MissionScriptObjectData_sub_475230(self, (int)started);
            break;
          case 0x75u:
          case 0x76u:
            goto LABEL_38;
          case 0xD3u:
            gta2::MissionScriptObjectData_sub_4779A0(self, (int)started);
            break;
          case 0xD4u:
            gta2::MissionScriptObjectData_sub_477A00(self, (int)started);
            break;
          case 0xD5u:
            gta2::MissionScriptObjectData_sub_477B70(self, (int)started);
            break;
          case 0xD6u:
            goto LABEL_24;
          case 0xD9u:
            goto LABEL_28;
          case 0xDFu:
            gta2::MissionScriptObjectData_sub_477BD0(self, (int)started);
            break;
          case 0xE6u:
            gta2::MissionScriptObjectData_sub_4752D0(self, (int)started);
            break;
          default:
            continue;
        }
      }
    }
  }
  gta2::MissionManager_sub_481200(gMissionManager);
  gta2::MissionScriptObjectData_sub_481270(self);
  pS107 = gS107;
  Index = gS107->Index;
  gS107->field_14A8 = Index / 3;
  if ( !(unsigned __int8)(Index / 3) )
    pS107->field_14A8 = pS107->Index;
  if ( Index > 4 )
  {
    v2 = 0;
    if ( Index > 0 )
    {
      v3 = &pS107->S108_[0].field_14;
      do
      {
        *(v3 - 1) >>= 2;
        *v3 >>= 2;
        v3 += 22;
        ++v2;
      }
      while ( v2 < pS107->Index );
    }
  }
  result = (char *)gNetworkGame;
  if ( gNetworkGame )
  {
    result = (char *)pS107->Index;
    v5 = 0;
    if ( (int)result > 0 )
    {
      result = (char *)&pS107->S108_[0].Cycle;
      do
      {
        *(_DWORD *)result = 1;
        result += 44;
        ++v5;
      }
      while ( v5 < pS107->Index );
    }
  }
  return result;
}



