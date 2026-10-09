#include "gta2_shim.h"

// Module: other, Class: Mike
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00474100: Mike::sub_474100
// IDA: Mike::sub_474100
// Ghidra: ---
void gta2::Mike_sub_474100(struct Mike *self)
{
  self->field_A78 = 0;
  self->field_A7C = 0;
}


// 0x00474530: Mike::sub_474530
// IDA: Mike::sub_474530
// Ghidra: ---
int gta2::Mike_sub_474530(struct Mike *self)
{
  int result; // eax
  int v2; // esi
  int *v3; // ebx
  int v4; // ebp
  int *v5; // edi
  int v6; // eax
  int UsedCache; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ebp
  int v13; // esi
  CarSystemManager **v14; // ebx
  char v15; // cl
  int v16; // edi
  S202 *v17; // eax
  int v18; // ecx
  int v19; // ecx
  S202 *v20; // edx
  int v21; // ecx
  int v22; // ecx
  S202 *v23; // ecx
  int v24; // ecx
  S202 *v25; // eax
  int v26; // ecx
  int v27; // ecx
  S202 *v28; // edx
  int v29; // ecx
  int v30; // ecx
  int v31; // eax
  CarSystemManager *v32; // edx
  S202 *v33; // edx
  int v34; // ecx
  int v35; // ecx
  S202 *v36; // ecx
  int v37; // ecx
  S202 *v38; // edx
  int v39; // ecx
  int v40; // ecx
  S202 *v41; // ecx
  int v42; // ecx
  S202 *v43; // edx
  int v44; // ecx
  int v45; // ecx
  S202 *v46; // ecx
  int v47; // ecx
  S202 *v48; // edx
  int v49; // ecx
  int v50; // ecx
  S202 *v51; // ecx
  int v52; // ecx
  _DWORD *v53; // edi
  _DWORD *v54; // ebx
  _DWORD *v55; // ebp
  int v56; // esi
  int v57; // esi
  int v58; // esi
  int v59; // esi
  int v60; // esi
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  unsigned int v67; // esi
  unsigned int v68; // ebx
  int v69; // [esp-14h] [ebp-A0h] BYREF
  S202 v70; // [esp-10h] [ebp-9Ch] BYREF
  int pTotalNumTextures; // [esp+10h] [ebp-7Ch]
  int v72; // [esp+14h] [ebp-78h]
  int v73; // [esp+18h] [ebp-74h]
  int v74; // [esp+1Ch] [ebp-70h]
  int v75; // [esp+20h] [ebp-6Ch]
  _DWORD *v76; // [esp+24h] [ebp-68h]
  int a5[25]; // [esp+28h] [ebp-64h]

  result = unk_673580;
  v2 = 0;
  a5[0] = (int)self;
  v72 = 0;
  pTotalNumTextures = 0;
  if ( unk_673580 )
  {
    v3 = (int *)gbh_GetGlobals[0]();
    v4 = 0;
    v73 = 0;
    v5 = v3 + 28;
    do
    {
      v6 = *v5;
      v70.field_C = v2;
      a5[v2 + 1] = v6;
      UsedCache = gbh_GetUsedCache(v70.field_C);
      v8 = a5[v2];
      v9 = v72;
      a5[v2 + 12] = UsedCache;
      v4 += v8;
      ++v2;
      ++v5;
      v72 = UsedCache + v9;
    }
    while ( v2 < 12 );
    v10 = *v3;
    v11 = v3[1];
    v74 = v4;
    v12 = 0;
    v73 = v10;
    v75 = v11;
    v13 = 20;
    v14 = (CarSystemManager **)(v3 + 16);
    do
    {
      v15 = v12;
      if ( v13 >= 140 )
        v15 = v12 - 6;
      v16 = 8 << v15;
      v70.CarSystemManager = (CarSystemManager *)(8 << v15);
      ShowTextDisplay(&TextWcharT, (char *)off_56E788);
      gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
      LOWORD(v17) = unk_670668;
      v70.S202 = v17;
      v70.field_0 = v18;
      gta2::S202_sub_41F980(&v70, v13);
      v69 = v19;
      gta2::bitShiftLeft1(&v69, 0);
      gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
      v70.CarSystemManager = *(v14 - 12);
      ShowTextDisplay(&TextWcharT, (char *)off_56E788);
      gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
      LOWORD(v20) = unk_670668;
      v70.S202 = v20;
      v70.field_0 = v21;
      gta2::S202_sub_41F980(&v70, v13);
      v69 = v22;
      gta2::bitShiftLeft1(&v69, 50);
      gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
      v70.CarSystemManager = *v14;
      ShowTextDisplay(&TextWcharT, (char *)off_56E788);
      gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
      LOWORD(v23) = unk_670668;
      v70.S202 = v23;
      v70.field_0 = (int)v23;
      gta2::S202_sub_41F980(&v70, v13);
      v69 = v24;
      gta2::bitShiftLeft1(&v69, 100);
      gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
      v70.CarSystemManager = (CarSystemManager *)a5[v12];
      ShowTextDisplay(&TextWcharT, (char *)off_56E788);
      gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
      LOWORD(v25) = unk_670668;
      v70.S202 = v25;
      v70.field_0 = v26;
      gta2::S202_sub_41F980(&v70, v13);
      v69 = v27;
      gta2::bitShiftLeft1(&v69, 150);
      gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
      v70.CarSystemManager = (CarSystemManager *)a5[v12 + 12];
      ShowTextDisplay(&TextWcharT, (char *)off_56E788);
      gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
      LOWORD(v28) = unk_670668;
      v70.S202 = v28;
      v70.field_0 = v29;
      gta2::S202_sub_41F980(&v70, v13);
      v69 = v30;
      gta2::bitShiftLeft1(&v69, 200);
      gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
      v31 = v16 * v16 * (_DWORD)*v14;
      pTotalNumTextures += (int)*v14;
      v13 += 20;
      ++v12;
      v32 = (CarSystemManager *)(*(_DWORD *)&v70.field_1C + 2 * v31);
      ++v14;
      *(_DWORD *)&v70.field_1C = v32;
    }
    while ( v13 < 260 );
    v70.CarSystemManager = v32;
    gta2::sub_4744C0(0, 280, L"Total Num Textures %d - %d bytes", pTotalNumTextures);
    ShowTextDisplay(&TextWcharT, (char *)L"Polys Drawn:");
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v33) = unk_670668;
    v70.S202 = v33;
    v70.field_0 = v34;
    gta2::bitShiftLeft1(&v70, 300);
    v69 = v35;
    gta2::bitShiftLeft1(&v69, 0);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    v70.CarSystemManager = (CarSystemManager *)v73;
    ShowTextDisplay(&TextWcharT, (char *)off_56E788);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v36) = unk_670668;
    v70.S202 = v36;
    v70.field_0 = (int)v36;
    gta2::bitShiftLeft1(&v70, 300);
    v69 = v37;
    gta2::bitShiftLeft1(&v69, 180);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    ShowTextDisplay(&TextWcharT, (char *)off_573E5C);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v38) = unk_670668;
    v70.S202 = v38;
    v70.field_0 = v39;
    gta2::bitShiftLeft1(&v70, 320);
    v69 = v40;
    gta2::bitShiftLeft1(&v69, 0);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    v70.CarSystemManager = (CarSystemManager *)v72;
    ShowTextDisplay(&TextWcharT, (char *)off_56E788);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v41) = unk_670668;
    v70.S202 = v41;
    v70.field_0 = (int)v41;
    gta2::bitShiftLeft1(&v70, 320);
    v69 = v42;
    gta2::bitShiftLeft1(&v69, 180);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    ShowTextDisplay(&TextWcharT, (char *)off_573E40);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v43) = unk_670668;
    v70.S202 = v43;
    v70.field_0 = v44;
    gta2::bitShiftLeft1(&v70, 340);
    v69 = v45;
    gta2::bitShiftLeft1(&v69, 0);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    v70.CarSystemManager = (CarSystemManager *)v74;
    ShowTextDisplay(&TextWcharT, (char *)off_56E788);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v46) = unk_670668;
    v70.S202 = v46;
    v70.field_0 = (int)v46;
    gta2::bitShiftLeft1(&v70, 340);
    v69 = v47;
    gta2::bitShiftLeft1(&v69, 180);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    ShowTextDisplay(&TextWcharT, (char *)off_573E24);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v48) = unk_670668;
    v70.S202 = v48;
    v70.field_0 = v49;
    gta2::bitShiftLeft1(&v70, 360);
    v69 = v50;
    gta2::bitShiftLeft1(&v69, 0);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    v70.CarSystemManager = (CarSystemManager *)v75;
    ShowTextDisplay(&TextWcharT, (char *)off_56E788);
    gta2::bitShiftLeft1(&v70.CarSystemManager, 1);
    LOWORD(v51) = unk_670668;
    v70.S202 = v51;
    v70.field_0 = (int)v51;
    gta2::bitShiftLeft1(&v70, 360);
    v69 = v52;
    gta2::bitShiftLeft1(&v69, 180);
    gta2::DrawGTATextRawMain(&TextWcharT, v69, v70.field_0, (unsigned __int16)v70.S202, (int)v70.CarSystemManager);
    ++unk_6644A8;
    if ( unk_6644A8 > 100 )
    {
      sub_4740F0(dword_66449C);
      unk_6644A8 = 0;
    }
    gta2::sub_4744C0(0, 380, (WCHAR *)&off_573E08, dword_66449C[0]);
    v53 = v76;
    v54 = v76 + 138;
    v55 = v76 + 106;
    v56 = sub_474490(v76 + 10);
    v57 = sub_474490(v53 + 42) + v56;
    v58 = sub_474490(v53 + 74) + v57;
    v59 = sub_474490(v55) + v58;
    v60 = sub_474490(v54) + v59;
    v61 = sub_474490(v53 + 10);
    gta2::sub_4744C0(280, 20, L"Process %3d", v61);
    v62 = sub_474490(v53 + 42);
    gta2::sub_4744C0(280, 40, L"Draw    %3d", v62);
    v63 = sub_474490(v53 + 74);
    gta2::sub_4744C0(280, 60, (WCHAR *)&off_573DC0, v63);
    v64 = sub_474490(v54);
    gta2::sub_4744C0(280, 80, L"Audio   %3d", v64);
    v65 = sub_474490(v55);
    gta2::sub_4744C0(280, 100, L"Input   %3d", v65);
    gta2::sub_4744C0(280, 120, L"Total   %3d", v60);
    if ( v60 <= 30 )
    {
      v66 = unk_664498;
      if ( !unk_664498 )
      {
LABEL_14:
        v67 = sub_4C3970(dword_5E8B78);
        v68 = sub_4C3970(dword_5E8B7C);
        gta2::sub_4744C0(280, 160, L"DisplayAdd   %3d", v67);
        gta2::sub_4744C0(280, 180, L"DisplayDraw  %3d", v68);
        dword_5E8B78 = 0;
        dword_5E8B7C = 0;
        return gta2::sub_4741F0(v53);
      }
    }
    else
    {
      v66 = 15;
    }
    unk_664498 = v66 - 1;
    gta2::sub_4744C0(280, 140, L"LARGE");
    goto LABEL_14;
  }
  return result;
}



