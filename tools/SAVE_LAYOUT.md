# GTA2 save (.svg) field layout — verified against retail code
# Base = 0x00000000, i.e. byte 0 of plyslotN.svg
# Sources: gta2.exe.c:103226 MissionManager::SaveFile, 137315 Player::sub_4A6B20,
#          137385 Player::sub_4A6C80, 136498 Player::sub_4A5A50, 98621 MissionManager::sub_475CA0
#
# FILE LAYOUT
#   0x0000..0x0747  1864 B   block0 = unk_664590 (player + level state)
#   0x0748..0x074B  u32 size  (636)
#   0x074C..0x09C7  636 B    block1  <- MapRelatedStruct::sub_4642A0 out#1
#   0x09C8..0x09CB  u32 size  (432)
#   0x09CC..0x0B7B  432 B    block2  <- MapRelatedStruct::sub_4642A0 out#2
#   0x0B7C..0x0B7F  u32 size  (288)
#   0x0B80..0x0C9F  288 B    block3  <- MapRelatedStruct::sub_4642A0 out#3
#   total 3232 B  (3232 = 1864 + 4+636 + 4+432 + 4+288)
#
# FIELD MAP
#  off     size  name
#  0x0000  24    mapName      char[24]  "data\wil.gmp"     MapGm::GetMapName
#  0x0018  1     unk_1        = 0x0A (10)                unk_6645A8
#  0x0019  24    styleName    char[24]  "data\wil.sty"     MapGm::GetStyleFile
#  0x0031  1     unk_2        = 0x0A (10)                unk_6645C1
#  0x0032  24    scriptName   char[24]  "data\wil.scr"     MapGm::GetScriptName
#  0x004A  1     unk_3        = 0x0A (10)                unk_6645DA
#  0x004B  1     playerArena  MapGm::GetPlayerArena      unk_6645DB
#  0x004C  1     bonusStage   MapGm::GetBonusStage       unk_6645DC   (0xFF = none)
#  0x004D  1     gang         MapGm::GetGang             unk_6645DD
#  0x0054  4     posX         Ped::GetXCoordinate
#  0x0058  4     posY
#  0x005C  4     posZ
#  0x0060  2     rotation
#  0x0064  4     money        Player::GetMoneyPlayer   -> this->Money
#  0x0068  4     MULTIPLIER   Player::GetMultiPlayer   -> this->MultiPlayer  (1..99, MULTIPLIER powerup)
#  0x006C  2     health       Ped::GetHealth
#  0x006E  34    powerups      u16[17]  enum POWERUP_TYPE (enum : __int16)
#                          = 0x6E + 2*idx, fills 0x6E..0x8F EXACTLY, field_644 starts at 0x90
#         in-game values (Player::GivePowerUp / Player::sub_4A59A0 per-tick decrement):
#           idx 3  ARMOR      0x0074  max 10, NOT decremented per tick (persistent points)
#           idx 4  JAIL_CARD  0x0076
#           idx 5  COP_BRIBE  0x0078
#           idx 6  INVULN     0x007A  1200 ticks -> Ped::sub_43B560 (immortality)
#           idx 7  DOUBLE_DMG 0x007C  1800 ticks
#           idx 8  FAST_RELOAD0x007E  1800 ticks
#           idx 9  ELECTRO    0x0080  2100 ticks -> Ped::sub_4A5060
#           idx10  RESPECT     0x0082  +20 respect
#           idx11  INVISIBLE   0x0084  1800 ticks -> Ped::EnableInvisibility
#           idx12  INSTANT_GANG0x0086
#  0x0090  40    field644[10] int[10]  Player::field_644[10]  (cities/bonuses/level flag?)
#  0x00B8  2     unused
#  0x00BA  15    ammo[15]     Weapon::GetDisplayAmmo per weapon (0=disabled)
#  0x00C9  10    gangRespect[10]  Gang::GetRespectForPlayer
#  0x00D3  1     remap        Ped::GetRemap
#  0x00D4  1     LIVES        (u8)  -> this->Lives   [SaveEdit calls this "PointMultiplier" - WRONG]
#  0x00D5  1     unused
#  0x00D6  2     selectWeapon u16 -> this->SelectWeapon (0xFFFF = no weapon in current save)
#  0x00D8  4     field678     Player::field_678
#  0x00DC  4     field67C     Player::field_67C
#  0x00E0  2     wantedLevel  Ped::GetPoliceStar / Ped::UpdateWantedLevel
#  0x00E4  68    carSpawn[3]  Player::sub_4A6A80  (not player state)
#  0x0128  12    unknown
#  0x0134  1200  objectives   unk_6646C4  300 x {u16 id, u16 val}
#  0x05E4  300   objectState  byte_664B74  Object::sub_483D90
#  0x0710  50    S63copy      unk_664CA0  = gObject->S63[0].S63_1 (50 bytes)
#  0x0742  2     unknown
#  0x0744  4     specialToken MapGm::GetSpecialTokens
#
# SAVEDIT (SOFT/GTA2-SaveEdit-1.04) CROSS-CHECK
#   0x64 Cash, 0x68 Lives, 0x6C Health, 0xD4 PointMultiplier, 0xD6 WeaponEquipped  -> MATCH
#   0xE1 WantedLevel                                                                 -> OFF BY ONE (real 0xE0)
#   0x74 Armor, 0x76 JailCard, 0x7B/0x7D/0x7F/0x81/0x85 powerups                      -> WRONG
#   0xBA..0xC4 ammo (11)                                                               -> INCOMPLETE (real 0xBA..0xC8, 15)
#
# VERIFIED BY EXPERIMENT  (baseline = pristine plyslot0.svg, one change per copy,
#                          C:\work\log\exp, tools\cmpexp.ps1)
#   tokens200.svg   0x744  00 -> C8   specialToken = 200            [CONFIRMED]
#   respect1.svg   0xC9   00 -> 9C   gang 0 respect = 156          [CONFIRMED]
#   respect2.svg   0xCA   00 -> 64   gang 1 respect = 100          [CONFIRMED]
#   respect3.svg   0xCB   00 -> 64   gang 2 respect = 100          [CONFIRMED]
#   => gang respect = 0xC9 + gangIndex, 10 gangs (0xC9..0xD2), matches Gang::GetRespectForPlayer
#   armor.svg      0x74   00 -> 14   editor "Armor" = 20           [editor label is WRONG]
#                             0x74 = 0x6E + 6 = POWERUP_TYPE_INVULNERABILITY.
#                             GTA2 has no armour pickup at all, so the editor just mislabelled it.
#   wanted.svg     0xE1   00 -> 2F   editor "WantedLevel"           [SUSPECT - needs re-test]
#                             retail Ped::UpdateWantedLevel is a u16 at 0xE0, editor only
#                             touches 0xE1 (high byte) and leaves 0xE0 = 0. 0x2F = 47 is not
#                             a legal wanted level (max 6), so either the field is different
#                             or the editor value must be re-checked.
#
# STILL UNKNOWN
#   armor offset, each power-up byte (theory: 0x6E + POWERUP_TYPE, 0x6E..0x7E)
#   wantedLevel byte (theory 0xE0, SaveEdit says 0xE1)
#   0x90..0xB7  Player::field_644[10]  (int[10] - cities / bonuses / next-level flag?)
#   0xD8, 0xDC  Player::field_678 / field_67C
#   0x128..0x133 (0x12A = 155, looks like a count)
#   blocks 636 / 432 / 288  (MapRelatedStruct::sub_4642A0)
#   .dat 12 records semantics
#
# .dat (plyslotN.dat, 126 B)  = one PlayerSlotSave slot
#   memory: struct PlayerSlotSave (gta2.exe.h:10390), stride 164 B per slot
#     +0x000 ArenaSlots[3]      -> 3 CITIES      (gta2.exe.c:138819, 69921/69944/70030)
#     +0x090 PlayerName[8]      -> written as wchar[9] = 18 B  (gta2.exe.c:138951)
#     +0x0A0 field_A0
#     each ArenaSlot = SubSlot[4], each SubSlot = BonusStage[3][4] = 12 B in RAM
#
#   file layout
#     0x000  18   wchar PlayerName[9]
#     0x012  108  12 records x 9 B  { u8 flag, u32 best, u32 last }
#              record N:  city = N / 4      level = N % 4
#              file offset of record N = 0x12 + 9*N
#              flag  = BonusStage[0][0]  level completed / city unlocked   (0/1)
#              best  = BonusStage[1][0]  best (max) money on that level
#              last  = BonusStage[2][0]  money at the moment of the last save
#              (bytes 1..3 of each 12-byte RAM record are NOT written)
#
#   semantics confirmed in gta2.exe.c:
#     138984 PlayerData::sub_4A8F90  - if (money > best) best = money; last = money
#     138743 PlayerSlotSave::sub_4A8780 - sums BonusStage[1] of all 12 -> TOTAL SCORE
#     138714 sub_4A8750               - sums BonusStage[2] of all 12 -> CURRENT MONEY
#     138681 PlayerSlotSave::sub_4A8700 - new slot: zeroes everything, then sets
#                                        ArenaSlots[0].SubSlot[0].BonusStage[0][0] = 1
#                                        -> record 0 is ALWAYS flag=1 in every slot
#     69921 / 69944 / 70030           - "find next unlocked city" loops on
#                                        ArenaSlots[i].SubSlot[0] -> SubSlot[0] IS the city
#
#   measured (C:\work\log\player, tools\datdump.ps1):
#     plyslot0 'CUTIE1'  cities 0,1,2 + c0.s1 done   total best 9011961  total last 8758305
#     plyslot1 'ABCDEFGH' cities 0,1                 total best 891      total last 2
#     plyslot2..7         city 0 only (fresh slots)
#     plyslot0 rec0.last = 8750000 == money in plyslot0.svg 0x64  -> confirms it is money
#
#   NEXT-LEVEL MARKER lives in the .svg, not the .dat:
#     0x4B = MapGm::playerArea  (current city)
#     0x4C = MapGm::bonusStage  = PACKED BYTE  city<<4 | level,  0xFF = none selected
#                                  (gta2.exe.c:70407 MapGm::DecodeBonusStage)
#     0x4D = MapGm::Gang
#
# .hsc (hiscores.hsc, 3264 B) = 136 x {wchar name[10], int score}   (24 B, matches struct S151)
#   PlayerData::sub_4A8D80 @0x004A8D80
