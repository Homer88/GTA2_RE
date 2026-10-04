// structs_supplement.h - недостающие полные определения структур GTA2.
// Скопированы из dump/Ghidra/gta2.exe.h (построчно) с заменой типов декомпилятора
// (undefined -> unsigned char, pointer -> void *, undefined4 -> int и т.п.).

#pragma once

// --- struct AIController (Ghidra gta2.exe.h:1059) ---
struct AIController
{
    byte field0_0x0;
    byte field1_0x1;
    unsigned char field2_0x2;
    unsigned char field3_0x3;
    struct Ped *Ped_[9];               // Ghidra: Ped
    unsigned char field5_0x28;
    unsigned char field6_0x29;
    unsigned char field7_0x2a;
    unsigned char field8_0x2b;
    struct Ped *PedDefault;
    int field10_0x30;
    byte IndexPed;
    byte field12_0x35;
    byte IndexPed1;                    // Created by retype action
    unsigned char field14_0x37;
    int field15_0x38;
    int field16_0x3c;
    byte field17_0x40;
    unsigned char field18_0x41;
    unsigned char field19_0x42;
    unsigned char field20_0x43;
};

// --- struct SpawnPoint (Ghidra gta2.exe.h:2788) ---
struct SpawnPoint
{
    byte field0_0x0;
    byte field1_0x1;
    byte field2_0x2;
    byte field3_0x3;
    struct Ped *Ped_Array[9];
    byte field5_0x28;
    byte field6_0x29;
    byte field7_0x2a;
    byte field8_0x2b;
    struct Ped *Ped_;
    int field10_0x30;
    byte Index;
    byte field12_0x35;
    byte field13_0x36;
    byte field14_0x37;
    int field15_0x38;
    int field16_0x3c;
    byte field17_0x40;
    byte field18_0x41;
    byte field19_0x42;
    byte field20_0x43;
    void *field21_0x44;
    unsigned char field22_0x48;
    unsigned char field23_0x49;
    unsigned char field24_0x4a;
    unsigned char field25_0x4b;
    unsigned char field26_0x4c;
    unsigned char field27_0x4d;
    unsigned char field28_0x4e;
    unsigned char field29_0x4f;
    unsigned char field30_0x50;
    unsigned char field31_0x51;
    unsigned char field32_0x52;
    unsigned char field33_0x53;
    unsigned char field34_0x54;
    unsigned char field35_0x55;
    unsigned char field36_0x56;
    unsigned char field37_0x57;
    struct Player *Player;             // Created by retype action
    unsigned char field39_0x5c;
    unsigned char field40_0x5d;
    unsigned char field41_0x5e;
    unsigned char field42_0x5f;
    unsigned char field43_0x60;
    unsigned char field44_0x61;
    unsigned char field45_0x62;
    unsigned char field46_0x63;
    unsigned char field47_0x64;
    unsigned char field48_0x65;
    unsigned char field49_0x66;
    unsigned char field50_0x67;
    unsigned char field51_0x68;
    unsigned char field52_0x69;
    unsigned char field53_0x6a;
    unsigned char field54_0x6b;
    unsigned char field55_0x6c;
    unsigned char field56_0x6d;
    unsigned char field57_0x6e;
    unsigned char field58_0x6f;
    unsigned char field59_0x70;
};

// --- struct GlassInfo (Ghidra gta2.exe.h:12113) ---
struct GlassInfo
{
    struct Car *car;
    struct Ped *pPed;
    struct SpawnPoint *SpawnPoint;
    unsigned char field3_0xc;
    unsigned char field4_0xd;
    unsigned char field5_0xe;
    unsigned char field6_0xf;
    unsigned char field7_0x10;
    unsigned char field8_0x11;
    unsigned char field9_0x12;
    unsigned char field10_0x13;
    int field11_0x14;
    unsigned short field12_0x18;
    unsigned short field13_0x1a;
    short count;
    byte field15_0x1e;
    unsigned char field16_0x1f;
    int field17_0x20;
    int field18_0x24;
    int field19_0x28;
    byte field20_0x2c;
    unsigned char field21_0x2d;
    unsigned char field22_0x2e;
    unsigned char field23_0x2f;
};