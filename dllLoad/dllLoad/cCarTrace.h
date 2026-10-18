#pragma once
#include <Windows.h>
#include <stdio.h>

// ---- Car observer hooks -------------------------------------------------------
// Every Car::* function listed in AddrToFunc.h is wrapped by an observer
// that records (caller, this, up to four args, return) into a ring and
// forwards to the retail trampoline. Nothing about the game's behaviour
// is changed.
//
// Signatures taken from dump\IDA\gta2.exe.c. All are __thiscall: this in
// ECX, remaining args on the stack. Each hook is __fastcall(self, dummy_edx, args...).
// ECX (self) and EDX are restored to their entry values before returning:
// retail callers reuse the live `this` in ECX across a thiscall and keep
// values in EDX across a call (cf. the S169 ctor crash). A plain C hook
// would let the trace push clobber both.
//
// Argument counts come from the binary `ret N`, not the decompiler: a wrong
// `ret N` corrupts the caller stack.
//
// Trampolines are detached LPVOID slots patched by DetourAttach (dllmain.cpp).
// Flip GTA2_NOCARTRACE=1 to skip the whole set.

extern LPVOID _Car_403800;   // Car::sub_403800                       thiscall,2 -> AudioManager *
extern LPVOID _Car_403820;   // Car::sub_403820                       thiscall,2 -> __int16
extern LPVOID _Car_403BA0;   // Car::IsTrainOrTrainCarriage           thiscall,1 -> bool
extern LPVOID _Car_403BC0;   // Car::isSWATVANOrBankVan               thiscall,1 -> bool
extern LPVOID _Car_40F890;   // Car::GetFullDamage                    thiscall,1 -> bool
extern LPVOID _Car_4112A0;   // Car::HasEmergencyLights               thiscall,1 -> bool
extern LPVOID _Car_4118B0;   // Car::GetDriver                        thiscall,1 -> Ped *
extern LPVOID _Car_4118C0;   // Car::IsEngineOn                       thiscall,1 -> bool
extern LPVOID _Car_4118D0;   // Car::IsDriverPlayer                   thiscall,1 -> bool
extern LPVOID _Car_4118F0;   // Car::isFileTruck                      thiscall,1 -> bool
extern LPVOID _Car_411900;   // Car::isTank                           thiscall,1 -> bool
extern LPVOID _Car_411910;   // Car::isGunJeep                        thiscall,1 -> bool
extern LPVOID _Car_411920;   // Car::isEDSELFBI                       thiscall,1 -> bool
extern LPVOID _Car_411930;   // Car::sub_411930                       thiscall,2 -> bool
extern LPVOID _Car_411940;   // Car::GetModelCar                      thiscall,1 -> CarModel
extern LPVOID _Car_411950;   // Car::sub_411950                       thiscall,1 -> int
extern LPVOID _Car_411970;   // Car::sub_411970                       thiscall,1 -> bool
extern LPVOID _Car_411990;   // Car::sub_411990                       thiscall,1 -> int
extern LPVOID _Car_414F20;   // Car::IsEmergencyOrFbiCar              thiscall,1 -> bool
extern LPVOID _Car_414F60;   // Car::sub_414F60                       thiscall,1 -> bool
extern LPVOID _Car_414F70;   // Car::sub_414F70                       thiscall,1 -> bool
extern LPVOID _Car_414F80;   // Car::sub_414F80                       thiscall,1 -> bool
extern LPVOID _Car_416B80;   // Car::sub_416B80                       thiscall,4 -> void
extern LPVOID _Car_416BB0;   // Car::sub_416BB0                       thiscall,2 -> void
extern LPVOID _Car_41E430;   // Car::GetX                             thiscall,2 -> void
extern LPVOID _Car_41E440;   // Car::GetY                             thiscall,2 -> void
extern LPVOID _Car_41E450;   // Car::GetZ                             thiscall,2 -> void
extern LPVOID _Car_41E460;   // Car::sub_41E460                       thiscall,1 -> bool
extern LPVOID _Car_41F6E0;   // Car::IsCopCar                         thiscall,1 -> bool
extern LPVOID _Car_41F700;   // Car::GetInfoByTypeCar                 thiscall,1 -> void *
extern LPVOID _Car_41F730;   // Car::sub_41F730                       thiscall,2 -> Car *
extern LPVOID _Car_41F750;   // Car::IsCurrentCarBus                  thiscall,1 -> bool
extern LPVOID _Car_41F860;   // Car::GetCarDoor                       thiscall,2 -> CarDoor *
extern LPVOID _Car_41F880;   // Car::sub_41F880                       thiscall,1 -> char
extern LPVOID _Car_41F8A0;   // Car::sub_41F8A0                       thiscall,1 -> char
extern LPVOID _Car_41F8F0;   // Car::sub_41F8F0                       thiscall,1 -> char
extern LPVOID _Car_41F940;   // Car::sub_41F940                       thiscall,1 -> char
extern LPVOID _Car_41F960;   // Car::sub_41F960                       thiscall,1 -> char
extern LPVOID _Car_41FA60;   // Car::sub_41FA60                       thiscall,1 -> bool
extern LPVOID _Car_41FAB0;   // Car::sub_41FAB0                       thiscall,1 -> Car *
extern LPVOID _Car_41FAC0;   // Car::sub_41FAC0                       thiscall,2 -> __int16 *
extern LPVOID _Car_41FBB0;   // Car::sub_41FBB0                       thiscall,1 -> char
extern LPVOID _Car_41FBD0;   // Car::sub_41FBD0                       thiscall,2 -> void
extern LPVOID _Car_41FD50;   // Car::AddRoofWaterGun                  thiscall,1 -> void
extern LPVOID _Car_41FDA0;   // Car::AddRoofTankTurret                thiscall,1 -> void
extern LPVOID _Car_41FDF0;   // Car::AddRoofGun                       thiscall,1 -> void
extern LPVOID _Car_41FF00;   // Car::CanDriverOverCars                thiscall,1 -> bool
extern LPVOID _Car_420330;   // Car::DecrementHorn                    thiscall,1 -> char
extern LPVOID _Car_420450;   // Car::sub_420450                       thiscall,1 -> char
extern LPVOID _Car_4207F0;   // Car::SetPosition                      thiscall,4 -> int
extern LPVOID _Car_420840;   // Car::sub_420840                       thiscall,2 -> CarSystemManager *
extern LPVOID _Car_4208F0;   // Car::TransformToRecycledType          thiscall,1 -> void
extern LPVOID _Car_420950;   // Car::sub_420950                       thiscall,5 -> void
extern LPVOID _Car_4209F0;   // Car::UpdateDamageCooldown             thiscall,1 -> char
extern LPVOID _Car_4213D0;   // Car::sub_4213D0                       thiscall,1 -> void
extern LPVOID _Car_421430;   // Car::sub_421430                       thiscall,1 -> void
extern LPVOID _Car_421460;   // Car::SetHornDefault                   thiscall,1 -> void
extern LPVOID _Car_421470;   // Car::isMask4                          thiscall,1 -> void
extern LPVOID _Car_421490;   // Car::isMask3                          thiscall,1 -> void
extern LPVOID _Car_4214B0;   // Car::isMask                           thiscall,1 -> bool
extern LPVOID _Car_4214D0;   // Car::GetMask7                         thiscall,1 -> bool
extern LPVOID _Car_4214E0;   // Car::SetMask7                         thiscall,1 -> void
extern LPVOID _Car_4214F0;   // Car::IsDriverActive                   thiscall,1 -> bool
extern LPVOID _Car_421510;   // Car::CarMakeDriveable2                thiscall,1 -> EngineStruct *
extern LPVOID _Car_421540;   // Car::sub_421540                       thiscall,1 -> void
extern LPVOID _Car_421550;   // Car::sub_421550                       thiscall,1 -> void
extern LPVOID _Car_421560;   // Car::CarMakeDriveable1                thiscall,2 -> void
extern LPVOID _Car_421570;   // Car::FixCarBrokenEngine               thiscall,1 -> void
extern LPVOID _Car_421590;   // Car::sub_421590                       thiscall,1 -> void
extern LPVOID _Car_4215B0;   // Car::GetMask                          thiscall,1 -> bool
extern LPVOID _Car_4215C0;   // Car::sub_4215C0                       thiscall,1 -> bool
extern LPVOID _Car_4215F0;   // Car::SetMask                          thiscall,1 -> void
extern LPVOID _Car_421610;   // Car::is_train                         thiscall,1 -> bool
extern LPVOID _Car_421620;   // Car::IsCar                            thiscall,1 -> bool
extern LPVOID _Car_421640;   // Car::is_trailer                       thiscall,1 -> bool
extern LPVOID _Car_421660;   // Car::sub_421660                       thiscall,1 -> bool
extern LPVOID _Car_421680;   // Car::sub_421680                       thiscall,1 -> bool
extern LPVOID _Car_4216A0;   // Car::sub_4216A0                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_4216C0;   // Car::has_for_hire_lights              thiscall,1 -> bool
extern LPVOID _Car_4216E0;   // Car::sub_4216E0                       thiscall,1 -> bool
extern LPVOID _Car_421700;   // Car::sub_421700                       thiscall,1 -> bool
extern LPVOID _Car_421720;   // Car::sub_421720                       thiscall,1 -> bool
extern LPVOID _Car_421740;   // Car::sub_421740                       thiscall,1 -> bool
extern LPVOID _Car_421760;   // Car::sub_421760                       thiscall,1 -> bool
extern LPVOID _Car_421780;   // Car::isMedicCar                       thiscall,1 -> bool
extern LPVOID _Car_421790;   // Car::isCopCar                         thiscall,1 -> bool
extern LPVOID _Car_4217A0;   // Car::isSWATVAN                        thiscall,1 -> bool
extern LPVOID _Car_4217B0;   // Car::isJeep                           thiscall,1 -> bool
extern LPVOID _Car_4217C0;   // Car::IsAPC                            thiscall,1 -> bool
extern LPVOID _Car_4217D0;   // Car::GetGT24640                       thiscall,1 -> bool
extern LPVOID _Car_4217E0;   // Car::isTVVAN                          thiscall,1 -> bool
extern LPVOID _Car_4217F0;   // Car::isTaxi                           thiscall,1 -> bool
extern LPVOID _Car_421810;   // Car::sub_421810                       thiscall,1 -> _DWORD *
extern LPVOID _Car_421830;   // Car::sub_421830                       thiscall,1 -> bool
extern LPVOID _Car_421870;   // Car::GetPlayer                        thiscall,1 -> Player *
extern LPVOID _Car_421890;   // Car::sub_421890                       thiscall,2 -> void
extern LPVOID _Car_4218A0;   // Car::sub_4218A0                       thiscall,1 -> void
extern LPVOID _Car_4218B0;   // Car::sub_4218B0                       thiscall,1 -> void
extern LPVOID _Car_4218C0;   // Car::sub_4218C0                       thiscall,1 -> void
extern LPVOID _Car_4218D0;   // Car::sub_4218D0                       thiscall,1 -> void
extern LPVOID _Car_4218E0;   // Car::sub_4218E0                       thiscall,1 -> void
extern LPVOID _Car_4218F0;   // Car::sub_4218F0                       thiscall,1 -> bool
extern LPVOID _Car_421900;   // Car::sub_421900                       thiscall,2 -> void
extern LPVOID _Car_421910;   // Car::sub_421910                       thiscall,3 -> SpriteS1 *
extern LPVOID _Car_421950;   // Car::SetSound                         thiscall,2 -> void
extern LPVOID _Car_421C40;   // Car::sub_421C40                       thiscall,2 -> _DWORD *
extern LPVOID _Car_421CF0;   // Car::sub_421CF0                       thiscall,2 -> S900 *
extern LPVOID _Car_421D80;   // Car::sub_421D80                       thiscall,1 -> bool
extern LPVOID _Car_421D90;   // Car::sub_421D90                       thiscall,2 -> SpriteS1 *
extern LPVOID _Car_421DF0;   // Car::IsPlayerDriving                  thiscall,1 -> bool
extern LPVOID _Car_421E70;   // Car::sub_421E70                       thiscall,2 -> _DWORD *
extern LPVOID _Car_421EC0;   // Car::sub_421EC0                       thiscall,2 -> Car *
extern LPVOID _Car_421F40;   // Car::sub_421F40                       thiscall,2 -> bool
extern LPVOID _Car_421F80;   // Car::sub_421F80                       thiscall,2 -> bool
extern LPVOID _Car_421FD0;   // Car::SetRemap                         thiscall,2 -> char
extern LPVOID _Car_4220A0;   // Car::sub_4220A0                       thiscall,1 -> char
extern LPVOID _Car_4221D0;   // Car::sub_4221D0                       thiscall,2 -> void
extern LPVOID _Car_422260;   // Car::sub_422260                       thiscall,1 -> void
extern LPVOID _Car_4222A0;   // Car::sub_4222A0                       thiscall,1 -> bool
extern LPVOID _Car_4222D0;   // Car::sub_4222D0                       thiscall,1 -> void
extern LPVOID _Car_4222F0;   // Car::sub_4222F0                       thiscall,1 -> void
extern LPVOID _Car_422360;   // Car::sub_422360                       thiscall,2 -> bool
extern LPVOID _Car_422500;   // Car::sub_422500                       thiscall,4 -> void *
extern LPVOID _Car_422670;   // Car::sub_422670                       thiscall,1 -> _DWORD *
extern LPVOID _Car_4226C0;   // Car::sub_4226C0                       thiscall,3 -> void *
extern LPVOID _Car_422980;   // Car::sub_422980                       thiscall,1 -> char
extern LPVOID _Car_422A40;   // Car::sub_422A40                       thiscall,1 -> void
extern LPVOID _Car_422AA0;   // Car::sub_422AA0                       thiscall,1 -> char
extern LPVOID _Car_422B70;   // Car::sub_422B70                       thiscall,1 -> char
extern LPVOID _Car_422BD0;   // Car::sub_422BD0                       thiscall,1 -> char
extern LPVOID _Car_422CB0;   // Car::sub_422CB0                       thiscall,1 -> void
extern LPVOID _Car_422D20;   // Car::sub_422D20                       thiscall,1 -> void
extern LPVOID _Car_422D80;   // Car::sub_422D80                       thiscall,1 -> bool
extern LPVOID _Car_422DE0;   // Car::sub_422DE0                       thiscall,1 -> void
extern LPVOID _Car_422E00;   // Car::sub_422E00                       thiscall,2 -> _DWORD *
extern LPVOID _Car_422F00;   // Car::sub_422F00                       thiscall,2 -> unsigned __int8
extern LPVOID _Car_4230D0;   // Car::sub_4230D0                       thiscall,2 -> bool
extern LPVOID _Car_423180;   // Car::sub_423180                       thiscall,3 -> char
extern LPVOID _Car_423290;   // Car::sub_423290                       thiscall,1 -> void
extern LPVOID _Car_423310;   // Car::sub_423310                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_423480;   // Car::sub_423480                       thiscall,1 -> Ped *
extern LPVOID _Car_4234A0;   // Car::sub_4234A0                       thiscall,2 -> SpriteS1 *
extern LPVOID _Car_423510;   // Car::CarPutDummyDriverIn              thiscall,1 -> void
extern LPVOID _Car_423590;   // Car::sub_423590                       thiscall,2 -> void
extern LPVOID _Car_4235D0;   // Car::sub_4235D0                       thiscall,1 -> void
extern LPVOID _Car_423630;   // Car::sub_423630                       thiscall,2 -> char
extern LPVOID _Car_423720;   // Car::sub_423720                       thiscall,2 -> char
extern LPVOID _Car_4237B0;   // Car::sub_4237B0                       thiscall,5 -> char
extern LPVOID _Car_4237F0;   // Car::sub_4237F0                       thiscall,5 -> char
extern LPVOID _Car_423830;   // Car::sub_423830                       thiscall,1 -> void
extern LPVOID _Car_423850;   // Car::sub_423850                       thiscall,1 -> char
extern LPVOID _Car_423940;   // Car::sub_423940                       thiscall,2 -> char
extern LPVOID _Car_423A50;   // Car::sub_423A50                       thiscall,1 -> Player *
extern LPVOID _Car_423A70;   // Car::sub_423A70                       thiscall,1 -> char
extern LPVOID _Car_423AA0;   // Car::sub_423AA0                       thiscall,1 -> void
extern LPVOID _Car_423B30;   // Car::sub_423B30                       thiscall,1 -> char
extern LPVOID _Car_423B50;   // Car::sub_423B50                       thiscall,1 -> void
extern LPVOID _Car_423B80;   // Car::sub_423B80                       thiscall,1 -> char
extern LPVOID _Car_423C30;   // Car::sub_423C30                       thiscall,1 -> void
extern LPVOID _Car_424010;   // Car::sub_424010                       thiscall,1 -> bool
extern LPVOID _Car_424030;   // Car::sub_424030                       thiscall,1 -> bool
extern LPVOID _Car_424090;   // Car::sub_424090                       thiscall,1 -> char
extern LPVOID _Car_4241C0;   // Car::HandleMaskTransition             thiscall,1 -> char
extern LPVOID _Car_424220;   // Car::sub_424220                       thiscall,2 -> int
extern LPVOID _Car_424280;   // Car::sub_424280                       thiscall,1 -> __int16
extern LPVOID _Car_4243C0;   // Car::sub_4243C0                       thiscall,1 -> int
extern LPVOID _Car_424400;   // Car::sub_424400                       thiscall,1 -> int
extern LPVOID _Car_4244A0;   // Car::sub_4244A0                       thiscall,2 -> void
extern LPVOID _Car_424630;   // Car::sub_424630                       thiscall,2 -> int
extern LPVOID _Car_424660;   // Car::sub_424660                       thiscall,2 -> void
extern LPVOID _Car_424680;   // Car::sub_424680                       thiscall,2 -> CarSystemManager *
extern LPVOID _Car_4246A0;   // Car::sub_4246A0                       thiscall,1 -> unsigned int
extern LPVOID _Car_424700;   // Car::sub_424700                       thiscall,1 -> bool
extern LPVOID _Car_424880;   // Car::sub_424880                       thiscall,1 -> int
extern LPVOID _Car_424960;   // Car::Car_Des                          thiscall,1 -> int
extern LPVOID _Car_424E30;   // Car::sub_424E30                       thiscall,2 -> bool
extern LPVOID _Car_424F80;   // Car::sub_424F80                       thiscall,1 -> bool
extern LPVOID _Car_425590;   // Car::sub_425590                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_425650;   // Car::sub_425650                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_425760;   // Car::sub_425760                       thiscall,1 -> bool
extern LPVOID _Car_425770;   // Car::sub_425770                       thiscall,1 -> bool
extern LPVOID _Car_425780;   // Car::sub_425780                       thiscall,1 -> bool
extern LPVOID _Car_425790;   // Car::sub_425790                       thiscall,2 -> _DWORD *
extern LPVOID _Car_4257B0;   // Car::sub_4257B0                       thiscall,1 -> bool
extern LPVOID _Car_425A40;   // Car::sub_425A40                       thiscall,2 -> char
extern LPVOID _Car_425B60;   // Car::sub_425B60                       thiscall,2 -> bool
extern LPVOID _Car_425CA0;   // Car::sub_425CA0                       thiscall,2 -> Car *
extern LPVOID _Car_425D60;   // Car::sub_425D60                       thiscall,2 -> bool
extern LPVOID _Car_425D90;   // Car::sub_425D90                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_425DD0;   // Car::CarMakeDriveable4                thiscall,1 -> unsigned __int8
extern LPVOID _Car_425DF0;   // Car::sub_425DF0                       thiscall,1 -> char
extern LPVOID _Car_425E30;   // Car::EnableSiren                      thiscall,1 -> char
extern LPVOID _Car_425E60;   // Car::sub_425E60                       thiscall,1 -> char
extern LPVOID _Car_425ED0;   // Car::sub_425ED0                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_425F20;   // Car::FixCarDamage                     thiscall,1 -> void
extern LPVOID _Car_425FD0;   // Car::AddRoofAntenna                   thiscall,1 -> void
extern LPVOID _Car_426030;   // Car::sub_426030                       thiscall,1 -> bool
extern LPVOID _Car_4260C0;   // Car::sub_4260C0                       thiscall,2 -> void
extern LPVOID _Car_426120;   // Car::sub_426120                       thiscall,1 -> Ped *
extern LPVOID _Car_426140;   // Car::sub_426140                       thiscall,1 -> char
extern LPVOID _Car_426220;   // Car::sub_426220                       thiscall,1 -> char
extern LPVOID _Car_4262B0;   // Car::sub_4262B0                       thiscall,2 -> Car *
extern LPVOID _Car_4262E0;   // Car::sub_4262E0                       thiscall,1 -> void
extern LPVOID _Car_426580;   // Car::sub_426580                       thiscall,2 -> CarSystemManager *
extern LPVOID _Car_4266F0;   // Car::sub_4266F0                       thiscall,1 -> EngineStruct *
extern LPVOID _Car_426730;   // Car::sub_426730                       thiscall,1 -> int
extern LPVOID _Car_4267B0;   // Car::Car                              thiscall,1 -> void
extern LPVOID _Car_426E00;   // Car::ENGINE_ON                        thiscall,1 -> void
extern LPVOID _Car_426EE0;   // Car::sub_426EE0                       thiscall,1 -> CAR_ENGINE_STATE
extern LPVOID _Car_426F00;   // Car::sub_426F00                       thiscall,1 -> char
extern LPVOID _Car_426F40;   // Car::sub_426F40                       thiscall,1 -> Ped *
extern LPVOID _Car_426F60;   // Car::sub_426F60                       thiscall,1 -> char
extern LPVOID _Car_426FA0;   // Car::ExplodeCar                       thiscall,2 -> char
extern LPVOID _Car_427180;   // Car::CollisionOnCar                   thiscall,3 -> __int16
extern LPVOID _Car_427290;   // Car::sub_427290                       thiscall,1 -> unsigned __int8
extern LPVOID _Car_427450;   // Car::sub_427450                       thiscall,1 -> bool
extern LPVOID _Car_4274C0;   // Car::sub_4274C0                       thiscall,2 -> char
extern LPVOID _Car_4279E0;   // Car::CarMakeDummy                     thiscall,1 -> void
extern LPVOID _Car_427A20;   // Car::sub_427A20                       thiscall,2 -> void
extern LPVOID _Car_427B20;   // Car::sub_427B20                       thiscall,1 -> int
extern LPVOID _Car_427B40;   // Car::sub_427B40                       thiscall,1 -> void
extern LPVOID _Car_427BD0;   // Car::MaxPaynt                         thiscall,2 -> int
extern LPVOID _Car_427CA0;   // Car::sub_427CA0                       thiscall,2 -> char
extern LPVOID _Car_427D10;   // Car::sub_427D10                       thiscall,2 -> char
extern LPVOID _Car_4292F0;   // Car::sub_4292F0                       thiscall,2 -> __int16
extern LPVOID _Car_429370;   // Car::sub_429370                       thiscall,2 -> void
extern LPVOID _Car_4293D0;   // Car::sub_4293D0                       thiscall,2 -> char
extern LPVOID _Car_429660;   // Car::sub_429660                       thiscall,1 -> void
extern LPVOID _Car_429800;   // Car::sub_429800                       thiscall,1 -> CarModel *
extern LPVOID _Car_429810;   // Car::sub_429810                       thiscall,9 -> char
extern LPVOID _Car_4298B0;   // Car::sub_4298B0                       thiscall,1 -> char
extern LPVOID _Car_429E50;   // Car::sub_429E50                       thiscall,1 -> char
extern LPVOID _Car_429FC0;   // Car::sub_429FC0                       thiscall,1 -> void
extern LPVOID _Car_429FF0;   // Car::sub_429FF0                       thiscall,5 -> char
extern LPVOID _Car_42A360;   // Car::sub_42A360                       thiscall,2 -> int
extern LPVOID _Car_42A510;   // Car::sub_42A510                       thiscall,1 -> void *
extern LPVOID _Car_42A5B0;   // Car::sub_42A5B0                       thiscall,1 -> bool
extern LPVOID _Car_42AC60;   // Car::sub_42AC60                       thiscall,1 -> bool
extern LPVOID _Car_42C030;   // Car::sub_42C030                       thiscall,1 -> void
extern LPVOID _Car_42C8B0;   // Car::sub_42C8B0                       thiscall,1 -> char
extern LPVOID _Car_42D390;   // Car::sub_42D390                       thiscall,1 -> char
extern LPVOID _Car_42D820;   // Car::sub_42D820                       thiscall,1 -> void
extern LPVOID _Car_42FB80;   // Car::sub_42FB80                       thiscall,1 -> char
extern LPVOID _Car_430090;   // Car::sub_430090                       thiscall,1 -> char
extern LPVOID _Car_430320;   // Car::sub_430320                       thiscall,1 -> void
extern LPVOID _Car_430CC0;   // Car::sub_430CC0                       thiscall,1 -> void
extern LPVOID _Car_431770;   // Car::sub_431770                       thiscall,1 -> int
extern LPVOID _Car_431C10;   // Car::sub_431C10                       thiscall,1 -> char
extern LPVOID _Car_432370;   // Car::sub_432370                       thiscall,1 -> __int16
extern LPVOID _Car_4327A0;   // Car::sub_4327A0                       thiscall,1 -> __int16
extern LPVOID _Car_447EA0;   // Car::SetMask1                         thiscall,1 -> void
extern LPVOID _Car_447EB0;   // Car::sub_447EB0                       thiscall,1 -> bool
extern LPVOID _Car_447EC0;   // Car::is_truck                         thiscall,1 -> bool
extern LPVOID _Car_447ED0;   // Car::sub_447ED0                       thiscall,1 -> bool
extern LPVOID _Car_447F00;   // Car::sub_447F00                       thiscall,1 -> bool
extern LPVOID _Car_44A3E0;   // Car::sub_44A3E0                       thiscall,1 -> void
extern LPVOID _Car_450CC0;   // Car::sub_450CC0                       thiscall,1 -> bool
extern LPVOID _Car_475AA0;   // Car::sub_475AA0                       thiscall,1 -> bool
extern LPVOID _Car_475C10;   // Car::SetLocksDoor                     thiscall,1 -> void
extern LPVOID _Car_475C30;   // Car::SetLocksDoor_4                   thiscall,1 -> void
extern LPVOID _Car_475C40;   // Car::SetLocksDoor2                    thiscall,1 -> void
extern LPVOID _Car_475C80;   // Car::sub_475C80                       thiscall,1 -> void
extern LPVOID _Car_4761F0;   // Car::sub_4761F0                       thiscall,2 -> void
extern LPVOID _Car_476230;   // Car::sub_476230                       thiscall,1 -> void
extern LPVOID _Car_476270;   // Car::sub_476270                       thiscall,1 -> void
extern LPVOID _Car_4762D0;   // Car::sub_4762D0                       thiscall,1 -> void
extern LPVOID _Car_4762E0;   // Car::jam_accelerator                  thiscall,1 -> void
extern LPVOID _Car_4762F0;   // Car::sub_4762F0                       thiscall,1 -> int
extern LPVOID _Car_476300;   // Car::sub_476300                       thiscall,1 -> void
extern LPVOID _Car_476310;   // Car::sub_476310                       thiscall,1 -> int
extern LPVOID _Car_476350;   // Car::unjam_accelerator                thiscall,1 -> int
extern LPVOID _Car_482D90;   // Car::sub_482D90                       thiscall,3 -> void
extern LPVOID _Car_4895E0;   // Car::sub_4895E0                       thiscall,1 -> int
extern LPVOID _Car_48A930;   // Car::sub_48A930                       thiscall,2 -> void
extern LPVOID _Car_49EFC0;   // Car::sub_49EFC0                       thiscall,1 -> __int16
extern LPVOID _Car_49EFD0;   // Car::sub_49EFD0                       thiscall,1 -> void
extern LPVOID _Car_49EFE0;   // Car::sub_49EFE0                       thiscall,1 -> bool
extern LPVOID _Car_4A9AD0;   // Car::sub_4A9AD0                       thiscall,1 -> __int16
extern LPVOID _Car_4AFB30;   // Car::sub_4AFB30                       thiscall,1 -> char
extern LPVOID _Car_4B9A30;   // Car::sub_4B9A30                       thiscall,2 -> char
extern LPVOID _Car_4BE7A0;   // Car::sub_4BE7A0                       thiscall,2 -> int
extern LPVOID _Car_4BE980;   // Car::sub_4BE980                       thiscall,2 -> _DWORD *
extern LPVOID _Car_4BE9C0;   // Car::sub_4BE9C0                       thiscall,2 -> GameObject *
extern LPVOID _Car_4BE9F0;   // Car::sub_4BE9F0                       thiscall,1 -> SpriteS1 **
extern LPVOID _Car_4BEA20;   // Car::sub_4BEA20                       thiscall,1 -> void
extern LPVOID _Car_4BEAC0;   // Car::sub_4BEAC0                       thiscall,3 -> Car *
extern LPVOID _Car_4BEB30;   // Car::sub_4BEB30                       thiscall,1 -> char *
extern LPVOID _Car_4BEB70;   // Car::sub_4BEB70                       thiscall,1 -> void
extern LPVOID _Car_4BEBC0;   // Car::sub_4BEBC0                       thiscall,3 -> char
extern LPVOID _Car_4BED90;   // Car::sub_4BED90                       thiscall,5 -> _DWORD *
extern LPVOID _Car_4BEE10;   // Car::sub_4BEE10                       thiscall,1 -> SpriteS1 *
extern LPVOID _Car_4BEF70;   // Car::sub_4BEF70                       thiscall,2 -> void
extern LPVOID _Car_4BF000;   // Car::sub_4BF000                       thiscall,1 -> int
extern LPVOID _Car_4BF070;   // Car::ExtinguishCar                    thiscall,1 -> void
extern LPVOID _Car_4BF100;   // Car::sub_4BF100                       thiscall,1 -> void
extern LPVOID _Car_4BF180;   // Car::sub_4BF180                       thiscall,2 -> void

DWORD __fastcall HookCar_403800(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_403820(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_403BA0(void* self, DWORD d);
DWORD __fastcall HookCar_403BC0(void* self, DWORD d);
DWORD __fastcall HookCar_40F890(void* self, DWORD d);
DWORD __fastcall HookCar_4112A0(void* self, DWORD d);
DWORD __fastcall HookCar_4118B0(void* self, DWORD d);
DWORD __fastcall HookCar_4118C0(void* self, DWORD d);
DWORD __fastcall HookCar_4118D0(void* self, DWORD d);
DWORD __fastcall HookCar_4118F0(void* self, DWORD d);
DWORD __fastcall HookCar_411900(void* self, DWORD d);
DWORD __fastcall HookCar_411910(void* self, DWORD d);
DWORD __fastcall HookCar_411920(void* self, DWORD d);
DWORD __fastcall HookCar_411930(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_411940(void* self, DWORD d);
DWORD __fastcall HookCar_411950(void* self, DWORD d);
DWORD __fastcall HookCar_411970(void* self, DWORD d);
DWORD __fastcall HookCar_411990(void* self, DWORD d);
DWORD __fastcall HookCar_414F20(void* self, DWORD d);
DWORD __fastcall HookCar_414F60(void* self, DWORD d);
DWORD __fastcall HookCar_414F70(void* self, DWORD d);
DWORD __fastcall HookCar_414F80(void* self, DWORD d);
void __fastcall HookCar_416B80(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
void __fastcall HookCar_416BB0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_41E430(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_41E440(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_41E450(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_41E460(void* self, DWORD d);
DWORD __fastcall HookCar_41F6E0(void* self, DWORD d);
DWORD __fastcall HookCar_41F700(void* self, DWORD d);
DWORD __fastcall HookCar_41F730(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_41F750(void* self, DWORD d);
DWORD __fastcall HookCar_41F860(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_41F880(void* self, DWORD d);
DWORD __fastcall HookCar_41F8A0(void* self, DWORD d);
DWORD __fastcall HookCar_41F8F0(void* self, DWORD d);
DWORD __fastcall HookCar_41F940(void* self, DWORD d);
DWORD __fastcall HookCar_41F960(void* self, DWORD d);
DWORD __fastcall HookCar_41FA60(void* self, DWORD d);
DWORD __fastcall HookCar_41FAB0(void* self, DWORD d);
DWORD __fastcall HookCar_41FAC0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_41FBB0(void* self, DWORD d);
void __fastcall HookCar_41FBD0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_41FD50(void* self, DWORD d);
void __fastcall HookCar_41FDA0(void* self, DWORD d);
void __fastcall HookCar_41FDF0(void* self, DWORD d);
DWORD __fastcall HookCar_41FF00(void* self, DWORD d);
DWORD __fastcall HookCar_420330(void* self, DWORD d);
DWORD __fastcall HookCar_420450(void* self, DWORD d);
DWORD __fastcall HookCar_4207F0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookCar_420840(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_4208F0(void* self, DWORD d);
void __fastcall HookCar_420950(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookCar_4209F0(void* self, DWORD d);
void __fastcall HookCar_4213D0(void* self, DWORD d);
void __fastcall HookCar_421430(void* self, DWORD d);
void __fastcall HookCar_421460(void* self, DWORD d);
void __fastcall HookCar_421470(void* self, DWORD d);
void __fastcall HookCar_421490(void* self, DWORD d);
DWORD __fastcall HookCar_4214B0(void* self, DWORD d);
DWORD __fastcall HookCar_4214D0(void* self, DWORD d);
void __fastcall HookCar_4214E0(void* self, DWORD d);
DWORD __fastcall HookCar_4214F0(void* self, DWORD d);
DWORD __fastcall HookCar_421510(void* self, DWORD d);
void __fastcall HookCar_421540(void* self, DWORD d);
void __fastcall HookCar_421550(void* self, DWORD d);
void __fastcall HookCar_421560(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_421570(void* self, DWORD d);
void __fastcall HookCar_421590(void* self, DWORD d);
DWORD __fastcall HookCar_4215B0(void* self, DWORD d);
DWORD __fastcall HookCar_4215C0(void* self, DWORD d);
void __fastcall HookCar_4215F0(void* self, DWORD d);
DWORD __fastcall HookCar_421610(void* self, DWORD d);
DWORD __fastcall HookCar_421620(void* self, DWORD d);
DWORD __fastcall HookCar_421640(void* self, DWORD d);
DWORD __fastcall HookCar_421660(void* self, DWORD d);
DWORD __fastcall HookCar_421680(void* self, DWORD d);
DWORD __fastcall HookCar_4216A0(void* self, DWORD d);
DWORD __fastcall HookCar_4216C0(void* self, DWORD d);
DWORD __fastcall HookCar_4216E0(void* self, DWORD d);
DWORD __fastcall HookCar_421700(void* self, DWORD d);
DWORD __fastcall HookCar_421720(void* self, DWORD d);
DWORD __fastcall HookCar_421740(void* self, DWORD d);
DWORD __fastcall HookCar_421760(void* self, DWORD d);
DWORD __fastcall HookCar_421780(void* self, DWORD d);
DWORD __fastcall HookCar_421790(void* self, DWORD d);
DWORD __fastcall HookCar_4217A0(void* self, DWORD d);
DWORD __fastcall HookCar_4217B0(void* self, DWORD d);
DWORD __fastcall HookCar_4217C0(void* self, DWORD d);
DWORD __fastcall HookCar_4217D0(void* self, DWORD d);
DWORD __fastcall HookCar_4217E0(void* self, DWORD d);
DWORD __fastcall HookCar_4217F0(void* self, DWORD d);
DWORD __fastcall HookCar_421810(void* self, DWORD d);
DWORD __fastcall HookCar_421830(void* self, DWORD d);
DWORD __fastcall HookCar_421870(void* self, DWORD d);
void __fastcall HookCar_421890(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_4218A0(void* self, DWORD d);
void __fastcall HookCar_4218B0(void* self, DWORD d);
void __fastcall HookCar_4218C0(void* self, DWORD d);
void __fastcall HookCar_4218D0(void* self, DWORD d);
void __fastcall HookCar_4218E0(void* self, DWORD d);
DWORD __fastcall HookCar_4218F0(void* self, DWORD d);
void __fastcall HookCar_421900(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421910(void* self, DWORD d, DWORD a0, DWORD a1);
void __fastcall HookCar_421950(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421C40(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421CF0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421D80(void* self, DWORD d);
DWORD __fastcall HookCar_421D90(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421DF0(void* self, DWORD d);
DWORD __fastcall HookCar_421E70(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421EC0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421F40(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421F80(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_421FD0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4220A0(void* self, DWORD d);
void __fastcall HookCar_4221D0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_422260(void* self, DWORD d);
DWORD __fastcall HookCar_4222A0(void* self, DWORD d);
void __fastcall HookCar_4222D0(void* self, DWORD d);
void __fastcall HookCar_4222F0(void* self, DWORD d);
DWORD __fastcall HookCar_422360(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_422500(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookCar_422670(void* self, DWORD d);
DWORD __fastcall HookCar_4226C0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookCar_422980(void* self, DWORD d);
void __fastcall HookCar_422A40(void* self, DWORD d);
DWORD __fastcall HookCar_422AA0(void* self, DWORD d);
DWORD __fastcall HookCar_422B70(void* self, DWORD d);
DWORD __fastcall HookCar_422BD0(void* self, DWORD d);
void __fastcall HookCar_422CB0(void* self, DWORD d);
void __fastcall HookCar_422D20(void* self, DWORD d);
DWORD __fastcall HookCar_422D80(void* self, DWORD d);
void __fastcall HookCar_422DE0(void* self, DWORD d);
DWORD __fastcall HookCar_422E00(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_422F00(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4230D0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_423180(void* self, DWORD d, DWORD a0, DWORD a1);
void __fastcall HookCar_423290(void* self, DWORD d);
DWORD __fastcall HookCar_423310(void* self, DWORD d);
DWORD __fastcall HookCar_423480(void* self, DWORD d);
DWORD __fastcall HookCar_4234A0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_423510(void* self, DWORD d);
void __fastcall HookCar_423590(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_4235D0(void* self, DWORD d);
DWORD __fastcall HookCar_423630(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_423720(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4237B0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookCar_4237F0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
void __fastcall HookCar_423830(void* self, DWORD d);
DWORD __fastcall HookCar_423850(void* self, DWORD d);
DWORD __fastcall HookCar_423940(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_423A50(void* self, DWORD d);
DWORD __fastcall HookCar_423A70(void* self, DWORD d);
void __fastcall HookCar_423AA0(void* self, DWORD d);
DWORD __fastcall HookCar_423B30(void* self, DWORD d);
void __fastcall HookCar_423B50(void* self, DWORD d);
DWORD __fastcall HookCar_423B80(void* self, DWORD d);
void __fastcall HookCar_423C30(void* self, DWORD d);
DWORD __fastcall HookCar_424010(void* self, DWORD d);
DWORD __fastcall HookCar_424030(void* self, DWORD d);
DWORD __fastcall HookCar_424090(void* self, DWORD d);
DWORD __fastcall HookCar_4241C0(void* self, DWORD d);
DWORD __fastcall HookCar_424220(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_424280(void* self, DWORD d);
DWORD __fastcall HookCar_4243C0(void* self, DWORD d);
DWORD __fastcall HookCar_424400(void* self, DWORD d);
void __fastcall HookCar_4244A0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_424630(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_424660(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_424680(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4246A0(void* self, DWORD d);
DWORD __fastcall HookCar_424700(void* self, DWORD d);
DWORD __fastcall HookCar_424880(void* self, DWORD d);
DWORD __fastcall HookCar_424960(void* self, DWORD d);
DWORD __fastcall HookCar_424E30(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_424F80(void* self, DWORD d);
DWORD __fastcall HookCar_425590(void* self, DWORD d);
DWORD __fastcall HookCar_425650(void* self, DWORD d);
DWORD __fastcall HookCar_425760(void* self, DWORD d);
DWORD __fastcall HookCar_425770(void* self, DWORD d);
DWORD __fastcall HookCar_425780(void* self, DWORD d);
DWORD __fastcall HookCar_425790(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4257B0(void* self, DWORD d);
DWORD __fastcall HookCar_425A40(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_425B60(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_425CA0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_425D60(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_425D90(void* self, DWORD d);
DWORD __fastcall HookCar_425DD0(void* self, DWORD d);
DWORD __fastcall HookCar_425DF0(void* self, DWORD d);
DWORD __fastcall HookCar_425E30(void* self, DWORD d);
DWORD __fastcall HookCar_425E60(void* self, DWORD d);
DWORD __fastcall HookCar_425ED0(void* self, DWORD d);
void __fastcall HookCar_425F20(void* self, DWORD d);
void __fastcall HookCar_425FD0(void* self, DWORD d);
DWORD __fastcall HookCar_426030(void* self, DWORD d);
void __fastcall HookCar_4260C0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_426120(void* self, DWORD d);
DWORD __fastcall HookCar_426140(void* self, DWORD d);
DWORD __fastcall HookCar_426220(void* self, DWORD d);
DWORD __fastcall HookCar_4262B0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_4262E0(void* self, DWORD d);
DWORD __fastcall HookCar_426580(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4266F0(void* self, DWORD d);
DWORD __fastcall HookCar_426730(void* self, DWORD d);
void __fastcall HookCar_4267B0(void* self, DWORD d);
void __fastcall HookCar_426E00(void* self, DWORD d);
DWORD __fastcall HookCar_426EE0(void* self, DWORD d);
DWORD __fastcall HookCar_426F00(void* self, DWORD d);
DWORD __fastcall HookCar_426F40(void* self, DWORD d);
DWORD __fastcall HookCar_426F60(void* self, DWORD d);
DWORD __fastcall HookCar_426FA0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_427180(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookCar_427290(void* self, DWORD d);
DWORD __fastcall HookCar_427450(void* self, DWORD d);
DWORD __fastcall HookCar_4274C0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_4279E0(void* self, DWORD d);
void __fastcall HookCar_427A20(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_427B20(void* self, DWORD d);
void __fastcall HookCar_427B40(void* self, DWORD d);
DWORD __fastcall HookCar_427BD0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_427CA0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_427D10(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4292F0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_429370(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4293D0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_429660(void* self, DWORD d);
DWORD __fastcall HookCar_429800(void* self, DWORD d);
DWORD __fastcall HookCar_429810(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7);
DWORD __fastcall HookCar_4298B0(void* self, DWORD d);
DWORD __fastcall HookCar_429E50(void* self, DWORD d);
void __fastcall HookCar_429FC0(void* self, DWORD d);
DWORD __fastcall HookCar_429FF0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookCar_42A360(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_42A510(void* self, DWORD d);
DWORD __fastcall HookCar_42A5B0(void* self, DWORD d);
DWORD __fastcall HookCar_42AC60(void* self, DWORD d);
void __fastcall HookCar_42C030(void* self, DWORD d);
DWORD __fastcall HookCar_42C8B0(void* self, DWORD d);
DWORD __fastcall HookCar_42D390(void* self, DWORD d);
void __fastcall HookCar_42D820(void* self, DWORD d);
DWORD __fastcall HookCar_42FB80(void* self, DWORD d);
DWORD __fastcall HookCar_430090(void* self, DWORD d);
void __fastcall HookCar_430320(void* self, DWORD d);
void __fastcall HookCar_430CC0(void* self, DWORD d);
DWORD __fastcall HookCar_431770(void* self, DWORD d);
DWORD __fastcall HookCar_431C10(void* self, DWORD d);
DWORD __fastcall HookCar_432370(void* self, DWORD d);
DWORD __fastcall HookCar_4327A0(void* self, DWORD d);
void __fastcall HookCar_447EA0(void* self, DWORD d);
DWORD __fastcall HookCar_447EB0(void* self, DWORD d);
DWORD __fastcall HookCar_447EC0(void* self, DWORD d);
DWORD __fastcall HookCar_447ED0(void* self, DWORD d);
DWORD __fastcall HookCar_447F00(void* self, DWORD d);
void __fastcall HookCar_44A3E0(void* self, DWORD d);
DWORD __fastcall HookCar_450CC0(void* self, DWORD d);
DWORD __fastcall HookCar_475AA0(void* self, DWORD d);
void __fastcall HookCar_475C10(void* self, DWORD d);
void __fastcall HookCar_475C30(void* self, DWORD d);
void __fastcall HookCar_475C40(void* self, DWORD d);
void __fastcall HookCar_475C80(void* self, DWORD d);
void __fastcall HookCar_4761F0(void* self, DWORD d, DWORD a0);
void __fastcall HookCar_476230(void* self, DWORD d);
void __fastcall HookCar_476270(void* self, DWORD d);
void __fastcall HookCar_4762D0(void* self, DWORD d);
void __fastcall HookCar_4762E0(void* self, DWORD d);
DWORD __fastcall HookCar_4762F0(void* self, DWORD d);
void __fastcall HookCar_476300(void* self, DWORD d);
DWORD __fastcall HookCar_476310(void* self, DWORD d);
DWORD __fastcall HookCar_476350(void* self, DWORD d);
void __fastcall HookCar_482D90(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookCar_4895E0(void* self, DWORD d);
void __fastcall HookCar_48A930(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_49EFC0(void* self, DWORD d);
void __fastcall HookCar_49EFD0(void* self, DWORD d);
DWORD __fastcall HookCar_49EFE0(void* self, DWORD d);
DWORD __fastcall HookCar_4A9AD0(void* self, DWORD d);
DWORD __fastcall HookCar_4AFB30(void* self, DWORD d);
DWORD __fastcall HookCar_4B9A30(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4BE7A0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4BE980(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4BE9C0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4BE9F0(void* self, DWORD d);
void __fastcall HookCar_4BEA20(void* self, DWORD d);
DWORD __fastcall HookCar_4BEAC0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookCar_4BEB30(void* self, DWORD d);
void __fastcall HookCar_4BEB70(void* self, DWORD d);
DWORD __fastcall HookCar_4BEBC0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookCar_4BED90(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookCar_4BEE10(void* self, DWORD d);
void __fastcall HookCar_4BEF70(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookCar_4BF000(void* self, DWORD d);
void __fastcall HookCar_4BF070(void* self, DWORD d);
void __fastcall HookCar_4BF100(void* self, DWORD d);
void __fastcall HookCar_4BF180(void* self, DWORD d, DWORD a0);

void DumpCarRing(FILE* f);     // full ring dump (crash forensics)
void DumpCarRingFile(void);    // append new entries to car_trace.log
