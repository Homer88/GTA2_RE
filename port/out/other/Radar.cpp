#include "gta2_shim.h"

// Module: other, Class: Radar
// Functions: 381
// Source: unified (IDA+Ghidra)

// 0x004e58a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e58a0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord
            (gBufferSize + 0xf28,gBufferSize + 0xef8,
             (int *)(gBufferSize + 0x110c));
  return;
}


// 0x004e58c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e58c0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord
            (gBufferSize + 0x1160,gBufferSize + 0xfac,
             (int *)(gBufferSize + 0x110c));
  return;
}


// 0x004e58e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e58e0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord
            (gBufferSize + 0xed4,gBufferSize + 0xfec,
             (int *)(gBufferSize + 0x110c));
  return;
}


// 0x004e5900: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e5900
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord
            (gBufferSize + 0x11b8,gBufferSize + 0x1180,
             (int *)(gBufferSize + 0x110c));
  return;
}


// 0x004e5920: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e5920
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord
            (gBufferSize + 0xedc,gBufferSize + 0x1084,
             (int *)(gBufferSize + 0x110c));
  return;
}


// 0x004e7700: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e7700
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord
            (gBufferSize + 0x13e8,gBufferSize + 0x13b0,&DAT_005d2f7c);
  return;
}


// 0x004e7720: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e7720
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005d2fd0,gBufferSize + 0x1478,&DAT_005d2f7c)
  ;
  return;
}


// 0x004e7740: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e7740
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(gBufferSize + 0x1384,&DAT_005d2e28,&DAT_005d2f7c)
  ;
  return;
}


// 0x004e7760: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e7760
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005d3034,&DAT_005d2ff8,&DAT_005d2f7c);
  return;
}


// 0x004e7780: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_004e7780
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(gBufferSize + 0x1390,&DAT_005d2ed4,&DAT_005d2f7c)
  ;
  return;
}


// 0x004eaab0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D35B4, &byte_5D3578, (PublicTransport *)&unk_5D37E0);
}


// 0x004eaad0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D3838, (SpriteS1 *)&unk_5D3648, (PublicTransport *)&unk_5D37E0);
}


// 0x004eaaf0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_5D3548, (SpriteS1 *)&unk_5D3688, (PublicTransport *)&unk_5D37E0);
}


// 0x004eab10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D389C, (SpriteS1 *)&unk_5D3860, (PublicTransport *)&unk_5D37E0);
}


// 0x004eab30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&stru_5D3548.field_10, (SpriteS1 *)&unk_5D3738, (PublicTransport *)&unk_5D37E0);
}


// 0x004ed0f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D7EE4, (SpriteS1 *)&unk_5D7EAC, (PublicTransport *)&unk_5D8108);
}


// 0x004ed110: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D815C, (SpriteS1 *)&unk_5D7F74, (PublicTransport *)&unk_5D8108);
}


// 0x004ed130: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D7E80, (SpriteS1 *)&unk_5D7FB4, (PublicTransport *)&unk_5D8108);
}


// 0x004ed150: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D81C0, (SpriteS1 *)&unk_5D8184, (PublicTransport *)&unk_5D8108);
}


// 0x004ed170: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D7E8C, (SpriteS1 *)&unk_5D8060, (PublicTransport *)&unk_5D8108);
}


// 0x004ee870: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D8268, (SpriteS1 *)&unk_5D8230, (PublicTransport *)&unk_5D848C);
}


// 0x004ee890: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D84E0, (SpriteS1 *)&unk_5D82F8, (PublicTransport *)&unk_5D848C);
}


// 0x004ee8b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D8204, (SpriteS1 *)&unk_5D8338, (PublicTransport *)&unk_5D848C);
}


// 0x004ee8d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D8544, (SpriteS1 *)&unk_5D8508, (PublicTransport *)&unk_5D848C);
}


// 0x004ee8f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5D8210, (SpriteS1 *)&unk_5D83E4, (PublicTransport *)&unk_5D848C);
}


// 0x004efff0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DC470, (SpriteS1 *)&unk_5DC438, (PublicTransport *)&unk_5DC694);
}


// 0x004f0010: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DC6E8, (SpriteS1 *)&unk_5DC500, (PublicTransport *)&unk_5DC694);
}


// 0x004f0043: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DC74C, (SpriteS1 *)&unk_5DC710, (PublicTransport *)&unk_5DC694);
}


// 0x004f0070: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5D8590, (SpriteS1 *)&unk_5DC5EC, (PublicTransport *)&unk_5DC694);
}


// 0x004f1790: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DC800, (SpriteS1 *)&unk_5DC7C8, (PublicTransport *)&unk_5DCA38);
}


// 0x004f17b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DCA90, (SpriteS1 *)&unk_5DC8B0, (PublicTransport *)&unk_5DCA38);
}


// 0x004f17d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DC790, (SpriteS1 *)&unk_5DC8E4, (PublicTransport *)&unk_5DCA38);
}


// 0x004f17f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DCAEC, (SpriteS1 *)&unk_5DCAB8, (PublicTransport *)&unk_5DCA38);
}


// 0x004f1810: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DC7A8, (SpriteS1 *)&unk_5DC98C, (PublicTransport *)&unk_5DCA38);
}


// 0x004f2fc0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2164, (SpriteS1 *)&unk_5DCBB0, (PublicTransport *)&unk_5E238C);
}


// 0x004f2fe0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E23E0, (SpriteS1 *)&unk_5E21F4, (PublicTransport *)&unk_5E238C);
}


// 0x004f3000: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DCB84, (SpriteS1 *)&unk_5E2238, (PublicTransport *)&unk_5E238C);
}


// 0x004f3020: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2448, (SpriteS1 *)&unk_5E2408, (PublicTransport *)&unk_5E238C);
}


// 0x004f3040: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5DCB90, (SpriteS1 *)&unk_5E22E4, (PublicTransport *)&unk_5E238C);
}


// 0x004f4780: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2514, (SpriteS1 *)&unk_5E24E0, (PublicTransport *)&unk_5E2744);
}


// 0x004f47a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2798, (SpriteS1 *)&unk_5E25C0, (PublicTransport *)&unk_5E2744);
}


// 0x004f47c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E24AC, (SpriteS1 *)&unk_5E25F4, (PublicTransport *)&unk_5E2744);
}


// 0x004f47e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E27F0, (SpriteS1 *)&unk_5E27C0, (PublicTransport *)&unk_5E2744);
}


// 0x004f4800: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E24C0, (SpriteS1 *)&unk_5E2698, (PublicTransport *)&unk_5E2744);
}


// 0x004f5f00: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2898, (SpriteS1 *)&unk_5E2860, (PublicTransport *)&unk_5E2AC0);
}


// 0x004f5f20: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2B14, (SpriteS1 *)&unk_5E2928, (PublicTransport *)&unk_5E2AC0);
}


// 0x004f5f40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2834, (SpriteS1 *)&unk_5E2968, (PublicTransport *)&unk_5E2AC0);
}


// 0x004f5f60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2B7C, (SpriteS1 *)&unk_5E2B3C, (PublicTransport *)&unk_5E2AC0);
}


// 0x004f5f80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2840, (SpriteS1 *)&unk_5E2A14, (PublicTransport *)&unk_5E2AC0);
}


// 0x004f76a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2C2C, (SpriteS1 *)&unk_5E2BF4, (PublicTransport *)&unk_5E2E50);
}


// 0x004f76c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2EA4, (SpriteS1 *)&unk_5E2CBC, (PublicTransport *)&unk_5E2E50);
}


// 0x004f76e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2BC8, (SpriteS1 *)&unk_5E2CFC, (PublicTransport *)&unk_5E2E50);
}


// 0x004f7700: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2F08, (SpriteS1 *)&unk_5E2ECC, (PublicTransport *)&unk_5E2E50);
}


// 0x004f7720: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E2BD4, (SpriteS1 *)&unk_5E2DA8, (PublicTransport *)&unk_5E2E50);
}


// 0x004f8e20: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E2FAC, (SpriteS1 *)&unk_5E2F74, (PublicTransport *)&unk_5E31D0);
}


// 0x004f8e40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E3224, (SpriteS1 *)&unk_5E303C, (PublicTransport *)&unk_5E31D0);
}


// 0x004f8e60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E2F48, (SpriteS1 *)&unk_5E307C, (PublicTransport *)&unk_5E31D0);
}


// 0x004f8e80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E3288, (SpriteS1 *)&unk_5E324C, (PublicTransport *)&unk_5E31D0);
}


// 0x004f8ea0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E2F54, (SpriteS1 *)&unk_5E3128, (PublicTransport *)&unk_5E31D0);
}


// 0x004fa5a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E333C, (SpriteS1 *)&unk_5E3304, (PublicTransport *)&unk_5E3560);
}


// 0x004fa5c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E35B4, (SpriteS1 *)&unk_5E33CC, (PublicTransport *)&unk_5E3560);
}


// 0x004fa5e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E32D8, (SpriteS1 *)&unk_5E340C, (PublicTransport *)&unk_5E3560);
}


// 0x004fa600: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3618, (SpriteS1 *)&unk_5E35DC, (PublicTransport *)&unk_5E3560);
}


// 0x004fa620: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E32E4, (SpriteS1 *)&unk_5E34B8, (PublicTransport *)&unk_5E3560);
}


// 0x004fc660: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E39C0, (SpriteS1 *)&unk_5E3984, (PublicTransport *)&unk_5E3BF4);
}


// 0x004fc680: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3C4C, (SpriteS1 *)&unk_5E3A58, (PublicTransport *)&unk_5E3BF4);
}


// 0x004fc6a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3954, (SpriteS1 *)&unk_5E3A98, (PublicTransport *)&unk_5E3BF4);
}


// 0x004fc6c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3CA8, (SpriteS1 *)&unk_5E3C74, (PublicTransport *)&unk_5E3BF4);
}


// 0x004fc6e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3964, (SpriteS1 *)&unk_5E3B48, (PublicTransport *)&unk_5E3BF4);
}


// 0x004fde80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E3D60, (SpriteS1 *)&unk_5E3D24, (PublicTransport *)&unk_5E3FB0);
}


// 0x004fdea0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E4004, (SpriteS1 *)&unk_5E3DFC, (PublicTransport *)&unk_5E3FB0);
}


// 0x004fdec0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E3CF4, (SpriteS1 *)&unk_5E3E3C, (PublicTransport *)&unk_5E3FB0);
}


// 0x004fdee0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E406C, (SpriteS1 *)&unk_5E402C, (PublicTransport *)&unk_5E3FB0);
}


// 0x004fdf00: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3D04, (SpriteS1 *)&unk_5E3F00, (PublicTransport *)&unk_5E3FB0);
}


// 0x004fe250: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3D34, (SpriteS1 *)&unk_5E3F38, (PublicTransport *)&unk_5E3D64);
}


// 0x004fe290: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3D34, (SpriteS1 *)&unk_5E4050, (PublicTransport *)&unk_5E3E90);
}


// 0x004fe2d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E3D34, (SpriteS1 *)&unk_5E3DEC, (PublicTransport *)&unk_5E3CDC);
}


// 0x004ff790: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E4D48, (SpriteS1 *)&unk_5E4D08, (PublicTransport *)&unk_5E4F94);
}


// 0x004ff7b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E4FEC, (SpriteS1 *)&unk_5E4DEC, (PublicTransport *)&unk_5E4F94);
}


// 0x004ff7d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E4CD4, (SpriteS1 *)&unk_5E4E2C, (PublicTransport *)&unk_5E4F94);
}


// 0x004ff7f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E505C, (SpriteS1 *)&unk_5E5018, (PublicTransport *)&unk_5E4F94);
}


// 0x004ff810: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E4CE8, (SpriteS1 *)&unk_5E4EE8, (PublicTransport *)&unk_5E4F94);
}


// 0x004ffcb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E4EB0, (SpriteS1 *)&unk_5E4DD0, &unk_5E4E34);
}


// 0x00501190: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00501190
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5128,&DAT_005e51f8,&DAT_005e5360);
  return;
}


// 0x005011b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005011b0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e53b8,&DAT_005e5158,&DAT_005e5360);
  return;
}


// 0x005011d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005011d0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e50b8,&DAT_005e52b0,&DAT_005e5360);
  return;
}


// 0x005011f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005011f0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5424,&DAT_005e53e4,&DAT_005e5360);
  return;
}


// 0x00501210: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00501210
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e50cc,&DAT_005e53d0,&DAT_005e5360);
  return;
}


// 0x00502920: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00502920
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5510,&DAT_005e55d4,&DAT_005e573c);
  return;
}


// 0x00502940: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00502940
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5790,&DAT_005e553c,&DAT_005e573c);
  return;
}


// 0x00502960: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00502960
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e54b4,&DAT_005e5694,&DAT_005e573c);
  return;
}


// 0x00502980: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00502980
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e57f0,&DAT_005e57b8,&DAT_005e573c);
  return;
}


// 0x005029a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005029a0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e54c4,&DAT_005e57a8,&DAT_005e573c);
  return;
}


// 0x00504080: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00504080
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5898,&DAT_005e5864,&DAT_005e5ac8);
  return;
}


// 0x005040a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005040a0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5b1c,&DAT_005e5944,&DAT_005e5ac8);
  return;
}


// 0x005040c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005040c0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5830,&DAT_005e5978,&DAT_005e5ac8);
  return;
}


// 0x005040e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005040e0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5b74,&DAT_005e5b44,&DAT_005e5ac8);
  return;
}


// 0x00504100: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00504100
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5844,&DAT_005e5a1c,&DAT_005e5ac8);
  return;
}


// 0x00505800: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00505800
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5c90,&DAT_005e5c54,&DAT_005e5ecc);
  return;
}


// 0x00505820: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00505820
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5f28,&Int_1024,&DAT_005e5ecc);
  return;
}


// 0x00505840: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00505840
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5c20,&DAT_005e5d68,&DAT_005e5ecc);
  return;
}


// 0x00505860: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00505860
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5f9c,&DAT_005e5f5c,&DAT_005e5ecc);
  return;
}


// 0x00505880: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00505880
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5c34,&DAT_005e5e20,&DAT_005e5ecc);
  return;
}


// 0x005070c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005070c0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e6048,&DAT_005e6010,&DAT_005e626c);
  return;
}


// 0x005070e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005070e0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e62c0,&DAT_005e60d8,&DAT_005e626c);
  return;
}


// 0x00507100: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00507100
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5fe4,&DAT_005e6118,&DAT_005e626c);
  return;
}


// 0x00507120: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00507120
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e6324,&DAT_005e62e8,&DAT_005e626c);
  return;
}


// 0x00507140: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00507140
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e5ff0,&DAT_005e61c4,&DAT_005e626c);
  return;
}


// 0x00508840: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00508840
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e63b0,&DAT_005e6380,&DAT_005e6588);
  return;
}


// 0x00508860: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00508860
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e65dc,&DAT_005e6430,&DAT_005e6588);
  return;
}


// 0x00508880: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00508880
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e635c,&DAT_005e6470,&DAT_005e6588);
  return;
}


// 0x005088a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005088a0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e6634,&DAT_005e65fc,&DAT_005e6588);
  return;
}


// 0x005088c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_005088c0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e6364,&DAT_005e6500,&DAT_005e6588);
  return;
}


// 0x00509cf0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00509cf0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e6728,&DAT_005e66f0,&DAT_005e697c);
  return;
}


// 0x00509d10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00509d10
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e69d0,&DAT_005e67bc,&DAT_005e697c);
  return;
}


// 0x00509d30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00509d30
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e66c0,&DAT_005e67fc,&DAT_005e697c);
  return;
}


// 0x00509d50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00509d50
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e6a34,&DAT_005e69f8,&DAT_005e697c);
  return;
}


// 0x00509d70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00509d70
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e66cc,&DAT_005e68d0,&DAT_005e697c);
  return;
}


// 0x0050c480: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0050c480
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e7524,&DAT_005e74e4,&DAT_005e776c);
  return;
}


// 0x0050c4a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0050c4a0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e77cc,&DAT_005e75cc,&DAT_005e776c);
  return;
}


// 0x0050c4c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0050c4c0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e74a8,&DAT_005e760c,&DAT_005e776c);
  return;
}


// 0x0050c4e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0050c4e0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e7844,&DAT_005e77f8,&DAT_005e776c);
  return;
}


// 0x0050c500: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0050c500
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e74c4,&DAT_005e76c0,&DAT_005e776c);
  return;
}


// 0x0050c960: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0050c960
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_005e780c,&DAT_005e74ac,&DAT_005e7714);
  return;
}


// 0x0050e7b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E7A78, (SpriteS1 *)&unk_5E7A40, (PublicTransport *)&unk_5E7C9C);
}


// 0x0050e7d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E7CF0, (SpriteS1 *)&unk_5E7B08, (PublicTransport *)&unk_5E7C9C);
}


// 0x0050e7f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E7A14, (SpriteS1 *)&unk_5E7B48, (PublicTransport *)&unk_5E7C9C);
}


// 0x0050e810: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E7D54, (SpriteS1 *)&unk_5E7D18, (PublicTransport *)&unk_5E7C9C);
}


// 0x0050e830: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E7A20, (SpriteS1 *)&unk_5E7BF4, (PublicTransport *)&unk_5E7C9C);
}


// 0x0050ff30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E7DFC, (SpriteS1 *)&unk_5E7DC8, (PublicTransport *)&unk_5E8040);
}


// 0x0050ff50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8094, (SpriteS1 *)&unk_5E7EB0, (PublicTransport *)&unk_5E8040);
}


// 0x0050ff70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E7D94, (SpriteS1 *)&unk_5E7EE4, (PublicTransport *)&unk_5E8040);
}


// 0x0050ff90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E80EC, (SpriteS1 *)&unk_5E80BC, (PublicTransport *)&unk_5E8040);
}


// 0x0050ffb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E7DA8, (SpriteS1 *)&unk_5E7F90, (PublicTransport *)&unk_5E8040);
}


// 0x00511740: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8180, (SpriteS1 *)&unk_5E814C, (PublicTransport *)&unk_5E8368);
}


// 0x00511760: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E83C0, (SpriteS1 *)&unk_5E8208, (PublicTransport *)&unk_5E8368);
}


// 0x00511780: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8124, (SpriteS1 *)&unk_5E8248, (PublicTransport *)&unk_5E8368);
}


// 0x005117a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E841C, (SpriteS1 *)&unk_5E83E4, (PublicTransport *)&unk_5E8368);
}


// 0x005117c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8130, (SpriteS1 *)&unk_5E82E0, (PublicTransport *)&unk_5E8368);
}


// 0x00514780: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E88C4, (SpriteS1 *)&unk_5E8894, (PublicTransport *)&unk_5E8AB8);
}


// 0x005147a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8B10, (SpriteS1 *)&unk_5E8968, (PublicTransport *)&unk_5E8AB8);
}


// 0x005147c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8864, (SpriteS1 *)&unk_5E899C, (PublicTransport *)&unk_5E8AB8);
}


// 0x005147e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8B60, (SpriteS1 *)&unk_5E8B34, (PublicTransport *)&unk_5E8AB8);
}


// 0x00514800: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8878, (SpriteS1 *)&unk_5E8A2C, (PublicTransport *)&unk_5E8AB8);
}


// 0x00515d40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8C0C, (SpriteS1 *)&unk_5E8BD4, (PublicTransport *)&unk_5E8E30);
}


// 0x00515d60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E8E84, (SpriteS1 *)&unk_5E8C9C, (PublicTransport *)&unk_5E8E30);
}


// 0x00515d80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8BA8, (SpriteS1 *)&unk_5E8CDC, (PublicTransport *)&unk_5E8E30);
}


// 0x00515da0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8EE8, (SpriteS1 *)&unk_5E8EAC, (PublicTransport *)&unk_5E8E30);
}


// 0x00515dc0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8BB4, (SpriteS1 *)&unk_5E8D88, (PublicTransport *)&unk_5E8E30);
}


// 0x005174c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E902C, (SpriteS1 *)&unk_5E8FFC, (PublicTransport *)&unk_5E9270);
}


// 0x005174e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E92C8, (SpriteS1 *)&unk_5E90E0, (PublicTransport *)&unk_5E9270);
}


// 0x00517500: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8FC0, (SpriteS1 *)&unk_5E9120, (PublicTransport *)&unk_5E9270);
}


// 0x00517520: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E9324, (SpriteS1 *)&unk_5E92F4, (PublicTransport *)&unk_5E9270);
}


// 0x00517540: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E8FDC, (SpriteS1 *)&unk_5E91C8, (PublicTransport *)&unk_5E9270);
}


// 0x00518ce0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E9404, (SpriteS1 *)&unk_5E93CC, (PublicTransport *)&unk_5E9628);
}


// 0x00518d00: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E967C, (SpriteS1 *)&unk_5E9494, (PublicTransport *)&unk_5E9628);
}


// 0x00518d20: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E93A0, (SpriteS1 *)&unk_5E94D4, (PublicTransport *)&unk_5E9628);
}


// 0x00518d40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5E96E0, (SpriteS1 *)&unk_5E96A4, (PublicTransport *)&unk_5E9628);
}


// 0x00518d60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5E93AC, (SpriteS1 *)&unk_5E9580, (PublicTransport *)&unk_5E9628);
}


// 0x0051a460: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EA67C, (SpriteS1 *)&unk_5EA64C, (PublicTransport *)&unk_5EA900);
}


// 0x0051a480: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EA958, (SpriteS1 *)&unk_5EA760, (PublicTransport *)&unk_5EA900);
}


// 0x0051a4a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EA61C, (SpriteS1 *)&unk_5EA794, (PublicTransport *)&unk_5EA900);
}


// 0x0051a4c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EA9B0, (SpriteS1 *)&unk_5EA97C, (PublicTransport *)&unk_5EA900);
}


// 0x0051a4e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EA630, (SpriteS1 *)&unk_5EA824, (PublicTransport *)&unk_5EA900);
}


// 0x0051ba60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EAA58, (SpriteS1 *)&unk_5EAA20, (PublicTransport *)&unk_5EAC7C);
}


// 0x0051ba80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EACD0, (SpriteS1 *)&unk_5EAAE8, (PublicTransport *)&unk_5EAC7C);
}


// 0x0051baa0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EA9F4, (SpriteS1 *)&unk_5EAB28, (PublicTransport *)&unk_5EAC7C);
}


// 0x0051bac0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EAD34, (SpriteS1 *)&unk_5EACF8, (PublicTransport *)&unk_5EAC7C);
}


// 0x0051bae0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EAA00, (SpriteS1 *)&unk_5EABD4, (PublicTransport *)&unk_5EAC7C);
}


// 0x0051db30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB1E4, (SpriteS1 *)&unk_5EB1B4, (PublicTransport *)&unk_5EB428);
}


// 0x0051db50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB480, (SpriteS1 *)&unk_5EB298, (PublicTransport *)&unk_5EB428);
}


// 0x0051db70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB178, (SpriteS1 *)&unk_5EB2D8, (PublicTransport *)&unk_5EB428);
}


// 0x0051db90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB4E0, (SpriteS1 *)&unk_5EB4AC, (PublicTransport *)&unk_5EB428);
}


// 0x0051dbb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB194, (SpriteS1 *)&unk_5EB380, (PublicTransport *)&unk_5EB428);
}


// 0x0051f360: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB584, (SpriteS1 *)&unk_5EB54C, (PublicTransport *)&unk_5EB7B4);
}


// 0x0051f380: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB80C, (SpriteS1 *)&unk_5EB61C, (PublicTransport *)&unk_5EB7B4);
}


// 0x0051f3a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB51C, (SpriteS1 *)&unk_5EB668, (PublicTransport *)&unk_5EB7B4);
}


// 0x0051f3c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_5EB87C, (SpriteS1 *)&unk_5EB838, (PublicTransport *)&unk_5EB7B4);
}


// 0x0051f3e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EB52C, (SpriteS1 *)&unk_5EB710, (PublicTransport *)&unk_5EB7B4);
}


// 0x00521cd0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBBBC, (SpriteS1 *)&unk_5EBB84, (PublicTransport *)&unk_5EBDE0);
}


// 0x00521cf0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBE34, (SpriteS1 *)&unk_5EBC4C, (PublicTransport *)&unk_5EBDE0);
}


// 0x00521d10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBB58, (SpriteS1 *)&unk_5EBC8C, (PublicTransport *)&unk_5EBDE0);
}


// 0x00521d30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBE98, (SpriteS1 *)&unk_5EBE5C, (PublicTransport *)&unk_5EBDE0);
}


// 0x00521d50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBB64, (SpriteS1 *)&unk_5EBD38, (PublicTransport *)&unk_5EBDE0);
}


// 0x00523450: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBF40, (SpriteS1 *)&unk_5EBF0C, (PublicTransport *)&unk_5EC6EC);
}


// 0x00523470: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EC740, (SpriteS1 *)&unk_5EBFEC, (PublicTransport *)&unk_5EC6EC);
}


// 0x00523490: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBED8, (SpriteS1 *)&unk_5EC020, (PublicTransport *)&unk_5EC6EC);
}


// 0x005234b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EC798, (SpriteS1 *)&unk_5EC768, (PublicTransport *)&unk_5EC6EC);
}


// 0x005234d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EBEEC, (SpriteS1 *)&unk_5EC640, (PublicTransport *)&unk_5EC6EC);
}


// 0x00524be0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EC838, (SpriteS1 *)&unk_5EC804, (PublicTransport *)&unk_5ECA70);
}


// 0x00524c00: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&byte_661E14, (SpriteS1 *)&unk_5EC8D0, (PublicTransport *)&unk_5ECA70);
}


// 0x00524c20: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EC7D0, (SpriteS1 *)&unk_5EC91C, (PublicTransport *)&unk_5ECA70);
}


// 0x00524c40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_661E7C, (SpriteS1 *)&unk_661E40, (PublicTransport *)&unk_5ECA70);
}


// 0x00524c60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_5EC7E4, (SpriteS1 *)&unk_5EC9CC, (PublicTransport *)&unk_5ECA70);
}


// 0x00529800: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_662808, (SpriteS1 *)&unk_6627D8, (PublicTransport *)&unk_662A4C);
}


// 0x00529820: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_662AA4, (SpriteS1 *)&unk_6628BC, (PublicTransport *)&unk_662A4C);
}


// 0x00529840: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66279C, (SpriteS1 *)&unk_6628FC, (PublicTransport *)&unk_662A4C);
}


// 0x00529860: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_662B00, (SpriteS1 *)&unk_662AD0, (PublicTransport *)&unk_662A4C);
}


// 0x00529880: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6627B8, (SpriteS1 *)&unk_6629A4, (PublicTransport *)&unk_662A4C);
}


// 0x0052b020: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_662C94, (SpriteS1 *)&unk_662C5C, (PublicTransport *)&unk_6631BC);
}


// 0x0052b040: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_663210, (SpriteS1 *)&unk_662D24, (PublicTransport *)&unk_6631BC);
}


// 0x0052b060: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_662C30, (SpriteS1 *)&unk_662D64, (PublicTransport *)&unk_6631BC);
}


// 0x0052b080: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_663274, (SpriteS1 *)&unk_663238, (PublicTransport *)&unk_6631BC);
}


// 0x0052b0a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_662C3C, (SpriteS1 *)&unk_663114, (PublicTransport *)&unk_6631BC);
}


// 0x0052cd10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66344C, (SpriteS1 *)&unk_663410, &byte_66366C);
}


// 0x0052cd30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6636C4, (SpriteS1 *)&unk_6634DC, &byte_66366C);
}


// 0x0052cd50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0052cd50
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_006633e8,&DAT_00663528,(int *)&DAT_0066366c)
  ;
  return;
}


// 0x0052cd70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_663728, (SpriteS1 *)&unk_6636E8, &byte_66366C);
}


// 0x0052cd90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6633F4, (SpriteS1 *)&unk_6635C8, &byte_66366C);
}


// 0x0052f4b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_663E70, (SpriteS1 *)&unk_663E38, (PublicTransport *)&unk_664094);
}


// 0x0052f4d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6640E8, (SpriteS1 *)&unk_663F00, (PublicTransport *)&unk_664094);
}


// 0x0052f4f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_663E0C, (SpriteS1 *)&unk_663F40, (PublicTransport *)&unk_664094);
}


// 0x0052f510: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66414C, (SpriteS1 *)&unk_664110, (PublicTransport *)&unk_664094);
}


// 0x0052f530: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_663E18, (SpriteS1 *)&unk_663FEC, (PublicTransport *)&unk_664094);
}


// 0x00530c30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6641E4, (SpriteS1 *)&unk_6641B0, (PublicTransport *)&unk_6643CC);
}


// 0x00530c50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_664424, (SpriteS1 *)&unk_66426C, (PublicTransport *)&unk_6643CC);
}


// 0x00530c70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_664188, (SpriteS1 *)&unk_6642AC, (PublicTransport *)&unk_6643CC);
}


// 0x00530c90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_664480, (SpriteS1 *)&unk_664448, (PublicTransport *)&unk_6643CC);
}


// 0x00530cb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_664194, (SpriteS1 *)&unk_664344, (PublicTransport *)&unk_6643CC);
}


// 0x005321f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_664560, (SpriteS1 *)&unk_664524, &byte_664F14);
}


// 0x00532210: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_664F6C, (SpriteS1 *)&unk_664D7C, &byte_664F14);
}


// 0x00532230: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6644F4, (SpriteS1 *)&unk_664DBC, &byte_664F14);
}


// 0x00532250: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_664FD4, (SpriteS1 *)&unk_664F94, &byte_664F14);
}


// 0x00532270: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_664504, (SpriteS1 *)&unk_664E6C, &byte_664F14);
}


// 0x00533a50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6650F0, (SpriteS1 *)&unk_6650BC, (PublicTransport *)&unk_6652D8);
}


// 0x00533a70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_665330, (SpriteS1 *)&unk_665178, (PublicTransport *)&unk_6652D8);
}


// 0x00533a90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_665094, (SpriteS1 *)&unk_6651B8, (PublicTransport *)&unk_6652D8);
}


// 0x00533ab0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66538C, (SpriteS1 *)&unk_665354, (PublicTransport *)&unk_6652D8);
}


// 0x00533ad0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6650A0, (SpriteS1 *)&unk_665250, (PublicTransport *)&unk_6652D8);
}


// 0x00535010: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_665434, (SpriteS1 *)&unk_6653F8, (PublicTransport *)&unk_665660);
}


// 0x00535030: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6656B8, (SpriteS1 *)&unk_6654C8, (PublicTransport *)&unk_665660);
}


// 0x00535050: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6653C8, (SpriteS1 *)&unk_665508, (PublicTransport *)&unk_665660);
}


// 0x00535070: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_665744, (SpriteS1 *)&unk_6656E0, (PublicTransport *)&unk_665660);
}


// 0x00535090: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6653D8, (SpriteS1 *)&unk_6655B8, (PublicTransport *)&unk_665660);
}


// 0x00536840: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_665828, (SpriteS1 *)&unk_6657F0, (PublicTransport *)&unk_665A60);
}


// 0x00536860: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_665AB4, (SpriteS1 *)&unk_6658C0, (PublicTransport *)&unk_665A60);
}


// 0x00536880: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6657C0, (SpriteS1 *)&unk_665900, (PublicTransport *)&unk_665A60);
}


// 0x005368a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_665B20, (SpriteS1 *)&unk_665ADC, (PublicTransport *)&unk_665A60);
}


// 0x005368c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6657D0, (SpriteS1 *)&unk_6659B0, (PublicTransport *)&unk_665A60);
}


// 0x0053dc80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_669B70, &unk_669B3C, &byte_669DA4);
}


// 0x0053dca0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_669DFC, &unk_669C1C, &byte_669DA4);
}


// 0x0053dcc0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_669B08, &unk_669C50, &byte_669DA4);
}


// 0x0053dce0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_669E54, (SpriteS1 *)&unk_669E24, &byte_669DA4);
}


// 0x0053dd00: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)stru_669B08.gap14, &unk_669CF8, &byte_669DA4);
}


// 0x0053f420: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_669F10, (SpriteS1 *)&unk_669ED8, (PublicTransport *)&unk_66A148);
}


// 0x0053f440: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A1A0, (SpriteS1 *)&unk_669FA8, (PublicTransport *)&unk_66A148);
}


// 0x0053f460: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_669EA8, (SpriteS1 *)&unk_669FE8, (PublicTransport *)&unk_66A148);
}


// 0x0053f480: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A208, (SpriteS1 *)&unk_66A1C8, (PublicTransport *)&unk_66A148);
}


// 0x0053f4a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_669EB8, (SpriteS1 *)&unk_66A09C, (PublicTransport *)&unk_66A148);
}


// 0x005415c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A468, (SpriteS1 *)&unk_66A428, (PublicTransport *)&unk_66A6B8);
}


// 0x005415e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A71C, (SpriteS1 *)&unk_66A504, (PublicTransport *)&unk_66A6B8);
}


// 0x00541600: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66A3F0, (SpriteS1 *)&unk_66A544, (PublicTransport *)&unk_66A6B8);
}


// 0x00541620: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A794, (SpriteS1 *)&unk_66A750, (PublicTransport *)&unk_66A6B8);
}


// 0x00541640: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A404, (SpriteS1 *)&unk_66A604, (PublicTransport *)&unk_66A6B8);
}


// 0x00542f80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66A874, (SpriteS1 *)&unk_66A83C, (PublicTransport *)&unk_66AA98);
}


// 0x00542fa0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66AAEC, (SpriteS1 *)&unk_66A904, (PublicTransport *)&unk_66AA98);
}


// 0x00542fc0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66A810, (SpriteS1 *)&unk_66A944, (PublicTransport *)&unk_66AA98);
}


// 0x00542fe0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66AB50, (SpriteS1 *)&unk_66AB14, (PublicTransport *)&unk_66AA98);
}


// 0x00543000: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66A81C, (SpriteS1 *)&unk_66A9F0, (PublicTransport *)&unk_66AA98);
}


// 0x00544700: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00544700
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_0066ac48,&DAT_0066abf8,(int *)&DAT_0066af18)
  ;
  return;
}


// 0x00544720: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00544720
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_0066af8c,&DAT_0066ad28,(int *)&DAT_0066af18)
  ;
  return;
}


// 0x00544740: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00544740
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_0066abac,&DAT_0066ad78,(int *)&DAT_0066af18)
  ;
  return;
}


// 0x00544760: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00544760
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_0066b03c,&DAT_0066afcc,(int *)&DAT_0066af18)
  ;
  return;
}


// 0x00544780: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00544780
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_0066abd4,&DAT_0066ae64,(int *)&DAT_0066af18)
  ;
  return;
}


// 0x00544e30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66AC10, (SpriteS1 *)&unk_66AF80, (PublicTransport *)&MEMORY[0x66AD60]);
}


// 0x00544e50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66AFE4, (SpriteS1 *)&unk_66ACF8, (PublicTransport *)&MEMORY[0x66AD60]);
}


// 0x00546410: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66B0F4, (SpriteS1 *)&unk_66B0B8, (PublicTransport *)&unk_66B324);
}


// 0x00546430: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66B37C, (SpriteS1 *)&unk_66B188, (PublicTransport *)&unk_66B324);
}


// 0x00546450: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66B088, (SpriteS1 *)&unk_66B1C8, (PublicTransport *)&unk_66B324);
}


// 0x00546470: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66B3E4, (SpriteS1 *)&unk_66B3A4, (PublicTransport *)&unk_66B324);
}


// 0x00546490: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00546490
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&PTR_0066b098,&DAT_0066b278,(int *)&DAT_0066b324)
  ;
  return;
}


// 0x00547c80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66B490, (SpriteS1 *)&unk_66B458, (PublicTransport *)&stru_66B6B0.S202);
}


// 0x00547ca0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&stru_66B6D0.field_38, (SpriteS1 *)&unk_66B520, (PublicTransport *)&stru_66B6B0.S202);
}


// 0x00547cc0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66B42C, (SpriteS1 *)&unk_66B560, (PublicTransport *)&stru_66B6B0.S202);
}


// 0x00547ce0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_66B76C, (SpriteS1 *)&stru_66B6D0.field_60, (PublicTransport *)&stru_66B6B0.S202);
}


// 0x00547d00: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66B438, (SpriteS1 *)&stru_66B600.Car, (PublicTransport *)&stru_66B6B0.S202);
}


// 0x00549400: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66B834, (SpriteS1 *)&unk_66B7FC, &byte_66BA5C);
}


// 0x00549420: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66BAB0, &unk_66B8C4, &byte_66BA5C);
}


// 0x00549440: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_66B7D0, &unk_66B904, &byte_66BA5C);
}


// 0x00549460: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BB14, (SpriteS1 *)&unk_66BAD8, &byte_66BA5C);
}


// 0x00549480: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&stru_66B7D0.TargetCar, &unk_66B9B4, &byte_66BA5C);
}


// 0x0054ab90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BBE4, (SpriteS1 *)&unk_66BBAC, (PublicTransport *)&unk_66BE1C);
}


// 0x0054abb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BE74, (SpriteS1 *)&unk_66BC94, (PublicTransport *)&unk_66BE1C);
}


// 0x0054abd0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BB74, (SpriteS1 *)&unk_66BCC8, (PublicTransport *)&unk_66BE1C);
}


// 0x0054abf0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BECC, (SpriteS1 *)&unk_66BE9C, (PublicTransport *)&unk_66BE1C);
}


// 0x0054ac10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BB8C, (SpriteS1 *)&unk_66BD70, (PublicTransport *)&unk_66BE1C);
}


// 0x0054c3b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BF78, (SpriteS1 *)&unk_66BF40, (PublicTransport *)&unk_66C19C);
}


// 0x0054c3d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66C1F0, (SpriteS1 *)&unk_66C008, (PublicTransport *)&unk_66C19C);
}


// 0x0054c3f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BF14, (SpriteS1 *)&unk_66C048, (PublicTransport *)&unk_66C19C);
}


// 0x0054c410: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66C254, (SpriteS1 *)&unk_66C218, (PublicTransport *)&unk_66C19C);
}


// 0x0054c430: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66BF20, (SpriteS1 *)&unk_66C0F4, (PublicTransport *)&unk_66C19C);
}


// 0x0054db30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66C30C, (SpriteS1 *)&unk_66C2D4, (PublicTransport *)&unk_66C54C);
}


// 0x0054db50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66C5A0, (SpriteS1 *)&unk_66C3A0, (PublicTransport *)&unk_66C54C);
}


// 0x0054db70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66C2A4, (SpriteS1 *)&unk_66C3E0, (PublicTransport *)&unk_66C54C);
}


// 0x0054db90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66C608, (SpriteS1 *)&unk_66C5C8, (PublicTransport *)&unk_66C54C);
}


// 0x0054dbb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66C2B4, (SpriteS1 *)&unk_66C49C, (PublicTransport *)&unk_66C54C);
}


// 0x0054fc90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66C838, (SpriteS1 *)&unk_66C800, (PublicTransport *)&stru_66F170.S202);
}


// 0x0054fcb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&stru_66F190.field_38, (SpriteS1 *)&unk_66C8C8, (PublicTransport *)&stru_66F170.S202);
}


// 0x0054fcd0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66C7D4, (SpriteS1 *)&unk_66C908, (PublicTransport *)&stru_66F170.S202);
}


// 0x0054fcf0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_66F22C, (SpriteS1 *)&stru_66F190.field_60, (PublicTransport *)&stru_66F170.S202);
}


// 0x0054fd10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(
           (Tango *)&unk_66C7E0,
           (SpriteS1 *)&stru_66F090.MissionCars,
           (PublicTransport *)&stru_66F170.S202);
}


// 0x00551430: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_66F2D8, (SpriteS1 *)&unk_66F29C, (PublicTransport *)&unk_66F504);
}


// 0x00551450: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66F55C, &unk_66F36C, (PublicTransport *)&unk_66F504);
}


// 0x00551470: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_66F26C, &unk_66F3AC, (PublicTransport *)&unk_66F504);
}


// 0x00551490: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66F5C0, (SpriteS1 *)&unk_66F584, (PublicTransport *)&unk_66F504);
}


// 0x005514b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&stru_66F26C.field_10, &unk_66F45C, (PublicTransport *)&unk_66F504);
}


// 0x00552c50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66F664, (SpriteS1 *)&unk_66F630, (PublicTransport *)&unk_66F8A8);
}


// 0x00552c70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66F904, (SpriteS1 *)&unk_66F718, (PublicTransport *)&unk_66F8A8);
}


// 0x00552c90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66F5F4, (SpriteS1 *)&unk_66F758, (PublicTransport *)&unk_66F8A8);
}


// 0x00552cb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66F968, (SpriteS1 *)&unk_66F930, (PublicTransport *)&unk_66F8A8);
}


// 0x00552cd0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_00552cd0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&gSpawnPoint,&DAT_0066f800,(int *)&DAT_0066f8a8);
  return;
}


// 0x00554e70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66FB7C, (SpriteS1 *)&unk_66FB4C, (PublicTransport *)&unk_66FD54);
}


// 0x00554e90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66FDA8, (SpriteS1 *)&unk_66FBFC, (PublicTransport *)&unk_66FD54);
}


// 0x00554eb0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66FB28, (SpriteS1 *)&unk_66FC3C, (PublicTransport *)&unk_66FD54);
}


// 0x00554ed0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66FE00, (SpriteS1 *)&unk_66FDC8, (PublicTransport *)&unk_66FD54);
}


// 0x00554ef0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66FB30, (SpriteS1 *)&unk_66FCCC, (PublicTransport *)&unk_66FD54);
}


// 0x00556320: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66FFA8, (SpriteS1 *)&unk_66FF74, (PublicTransport *)&unk_6701E0);
}


// 0x00556340: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_670238, (SpriteS1 *)&unk_670040, (PublicTransport *)&unk_6701E0);
}


// 0x00556360: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_66FF40, (SpriteS1 *)&unk_67008C, (PublicTransport *)&unk_6701E0);
}


// 0x00556380: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6702A0, (SpriteS1 *)&unk_670264, (PublicTransport *)&unk_6701E0);
}


// 0x005563a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_66FF54, (SpriteS1 *)&unk_67013C, (PublicTransport *)&unk_6701E0);
}


// 0x00557b40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_670348, (SpriteS1 *)&unk_670310, (PublicTransport *)&unk_67056C);
}


// 0x00557b60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6705C0, (SpriteS1 *)&unk_6703D8, (PublicTransport *)&unk_67056C);
}


// 0x00557b80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6702E4, (SpriteS1 *)&unk_670418, (PublicTransport *)&unk_67056C);
}


// 0x00557ba0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_670624, (SpriteS1 *)&unk_6705E8, (PublicTransport *)&unk_67056C);
}


// 0x00557bc0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6702F0, (SpriteS1 *)&unk_6704C4, (PublicTransport *)&unk_67056C);
}


// 0x0055a2c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_67096C, (SpriteS1 *)&unk_670938, (PublicTransport *)&unk_670B9C);
}


// 0x0055a2e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_670BF0, (SpriteS1 *)&unk_670A18, (PublicTransport *)&unk_670B9C);
}


// 0x0055a300: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_670904, (SpriteS1 *)&unk_670A4C, (PublicTransport *)&unk_670B9C);
}


// 0x0055a320: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_670C48, (SpriteS1 *)&unk_670C18, (PublicTransport *)&unk_670B9C);
}


// 0x0055a340: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_670918, (SpriteS1 *)&unk_670AF0, (PublicTransport *)&unk_670B9C);
}


// 0x0055ba40: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_670D44, (SpriteS1 *)&unk_670D08, &byte_670F70);
}


// 0x0055ba60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_670FC8, &unk_670DD8, &byte_670F70);
}


// 0x0055ba80: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip(&stru_670CD8, &unk_670E18, &byte_670F70);
}


// 0x0055baa0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_671030, (SpriteS1 *)&unk_670FF0, &byte_670F70);
}


// 0x0055bac0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&stru_670CD8.field_10, &unk_670EC8, &byte_670F70);
}


// 0x0055d270: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6715C8, (SpriteS1 *)&unk_671594, (PublicTransport *)&unk_6717B0);
}


// 0x0055d290: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_671808, (SpriteS1 *)&unk_671650, (PublicTransport *)&unk_6717B0);
}


// 0x0055d2b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_67156C, (SpriteS1 *)&unk_671690, (PublicTransport *)&unk_6717B0);
}


// 0x0055d2d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_671864, (SpriteS1 *)&unk_67182C, (PublicTransport *)&unk_6717B0);
}


// 0x0055d2f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_671578, (SpriteS1 *)&unk_671728, (PublicTransport *)&unk_6717B0);
}


// 0x00560ab0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_671F18, (SpriteS1 *)&unk_671EE4, (PublicTransport *)&unk_672100);
}


// 0x00560ad0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672158, (SpriteS1 *)&unk_671FA0, (PublicTransport *)&unk_672100);
}


// 0x00560af0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_671EB8, (SpriteS1 *)&unk_671FE0, (PublicTransport *)&unk_672100);
}


// 0x00560b10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6721B4, (SpriteS1 *)&unk_67217C, (PublicTransport *)&unk_672100);
}


// 0x00560b30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_671EC8, (SpriteS1 *)&unk_672078, (PublicTransport *)&unk_672100);
}


// 0x00562080: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672260, (SpriteS1 *)&unk_672224, (PublicTransport *)&unk_672490);
}


// 0x005620a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6724EC, (SpriteS1 *)&unk_6722F8, (PublicTransport *)&unk_672490);
}


// 0x005620c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_6721F4, (SpriteS1 *)&unk_672338, (PublicTransport *)&unk_672490);
}


// 0x005620e0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672558, (SpriteS1 *)&unk_672514, (PublicTransport *)&unk_672490);
}


// 0x00562100: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672204, (SpriteS1 *)&unk_6723E8, (PublicTransport *)&unk_672490);
}


// 0x00564a50: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672898, (SpriteS1 *)&unk_672860, (PublicTransport *)&unk_672ABC);
}


// 0x00564a70: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672B10, (SpriteS1 *)&unk_672928, (PublicTransport *)&unk_672ABC);
}


// 0x00564a90: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672834, (SpriteS1 *)&unk_672968, (PublicTransport *)&unk_672ABC);
}


// 0x00564ab0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672B74, (SpriteS1 *)&unk_672B38, (PublicTransport *)&unk_672ABC);
}


// 0x00564ad0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672840, (SpriteS1 *)&unk_672A14, (PublicTransport *)&unk_672ABC);
}


// 0x005661d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672C1C, (SpriteS1 *)&unk_672BE4, (PublicTransport *)&unk_672E40);
}


// 0x005661f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672E94, (SpriteS1 *)&unk_672CAC, (PublicTransport *)&unk_672E40);
}


// 0x00566210: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672BB8, (SpriteS1 *)&unk_672CEC, (PublicTransport *)&unk_672E40);
}


// 0x00566230: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672EF8, (SpriteS1 *)&unk_672EBC, (PublicTransport *)&unk_672E40);
}


// 0x00566250: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672BC4, (SpriteS1 *)&unk_672D98, (PublicTransport *)&unk_672E40);
}


// 0x00567950: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672FC4, (SpriteS1 *)&unk_672F90, (PublicTransport *)&unk_6731FC);
}


// 0x00567970: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_673254, (SpriteS1 *)&unk_67305C, (PublicTransport *)&unk_6731FC);
}


// 0x00567990: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_672F5C, (SpriteS1 *)&unk_6730A8, (PublicTransport *)&unk_6731FC);
}


// 0x005679b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6732C0, (SpriteS1 *)&unk_673280, (PublicTransport *)&unk_6731FC);
}


// 0x005679d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_672F70, (SpriteS1 *)&unk_673158, (PublicTransport *)&unk_6731FC);
}


// 0x00569190: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_67362C, (SpriteS1 *)&unk_6735F8, (PublicTransport *)&unk_673864);
}


// 0x005691b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6738BC, (SpriteS1 *)&unk_6736C4, (PublicTransport *)&unk_673864);
}


// 0x005691d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6735C4, (SpriteS1 *)&unk_673710, (PublicTransport *)&unk_673864);
}


// 0x005691f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_673924, (SpriteS1 *)&unk_6738E8, (PublicTransport *)&unk_673864);
}


// 0x00569210: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6735D8, (SpriteS1 *)&unk_6737C0, (PublicTransport *)&unk_673864);
}


// 0x0056a9b0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_6739E0, (SpriteS1 *)&unk_6739A4, (PublicTransport *)&unk_673C34);
}


// 0x0056a9d0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_673C90, (SpriteS1 *)&unk_673A7C, (PublicTransport *)&unk_673C34);
}


// 0x0056a9f0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&dword_673970, (SpriteS1 *)&unk_673AC0, (PublicTransport *)&unk_673C34);
}


// 0x0056aa10: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_673CFC, (SpriteS1 *)&unk_673CBC, (PublicTransport *)&unk_673C34);
}


// 0x0056aa30: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
  return gta2::Radar_AddBlip((Tango *)&unk_673984, (SpriteS1 *)&unk_673B84, (PublicTransport *)&unk_673C34);
}


// 0x0056c340: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0056c340
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_00673fdc,&DAT_00673fa8,(int *)&DAT_00674214)
  ;
  return;
}


// 0x0056c360: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0056c360
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_00674f24,&DAT_00674074,(int *)&DAT_00674214)
  ;
  return;
}


// 0x0056c380: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0056c380
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_00673f74,&DAT_006740c0,(int *)&DAT_00674214)
  ;
  return;
}


// 0x0056c3a0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0056c3a0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_00674f8c,&DAT_00674f50,(int *)&DAT_00674214)
  ;
  return;
}


// 0x0056c3c0: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: FUN_0056c3c0
void gta2::Radar_AddBlip(void)
{
  gta2::WorldCoordinateToScreenCoord(&DAT_00673f88,&DAT_00674170,(int *)&DAT_00674214)
  ;
  return;
}



