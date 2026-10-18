#pragma once
#include <Windows.h>
#include <stdio.h>

// ---- Player observer hooks ------------------------------------------------------
// Every Player::* function listed in AddrToFunc.h is wrapped by an observer
// that records (caller, this, up to four args, return) into a ring and forwards
// to the retail trampoline. Nothing about the game's behaviour is changed.
//
// Signatures taken from dump\IDA\gta2.exe.c. All are __thiscall: this in ECX,
// remaining args on the stack. Each hook is __fastcall(self, dummy_edx, args...).
// ECX (self) and EDX are restored to their entry values before returning: some
// retail callers reuse the live `this` in ECX across a thiscall (Player::Player
// relies on SetActivePowerUps leaving ECX==this for the following sub_4A5180 call)
// and keep values in EDX across a call (see the S169 ctor crash).
//
// Player::StartGames (0x4A6DA0) is intentionally absent: already detoured by Game.
// Trampolines are detached LPVOID slots patched by DetourAttach (dllmain.cpp).

extern LPVOID _Player_401B40;   // Player::sub_401B40               thiscall,3 -> SpriteS1 *
extern LPVOID _Player_401B90;   // Player::sub_401B90               thiscall,3 -> void *
extern LPVOID _Player_40CE50;   // Player::CheckCondition           thiscall,2 -> bool
extern LPVOID _Player_40CE70;   // Player::sub_40CE70               thiscall,2 -> BOOL
extern LPVOID _Player_40E530;   // Player::sub_40E530               thiscall,2 -> void
extern LPVOID _Player_40E570;   // Player::IsCurrentPlayer          thiscall,2 -> BOOL
extern LPVOID _Player_40E8D0;   // Player::sub_40E8D0               thiscall,4 -> __int16 *
extern LPVOID _Player_40EC20;   // Player::TransformSprite          thiscall,5 -> int
extern LPVOID _Player_40F790;   // Player::sub_40F790               thiscall,2 -> __int16 *
extern LPVOID _Player_40F820;   // Player::sub_40F820               thiscall,2 -> void
extern LPVOID _Player_40F840;   // Player::IsOnScreen               thiscall,1 -> bool
extern LPVOID _Player_411810;   // Player::sub_411810               thiscall,1 -> char
extern LPVOID _Player_411820;   // Player::sub_411820               thiscall,2 -> void
extern LPVOID _Player_411830;   // Player::IsAudioEnabled           thiscall,1 -> char
extern LPVOID _Player_411840;   // Player::ReadEngineValue          thiscall,2 -> void
extern LPVOID _Player_411850;   // Player::ReadEngineValue2         thiscall,2 -> int *
extern LPVOID _Player_411860;   // Player::GetSoundHandle           thiscall,1 -> AudioManager *
extern LPVOID _Player_41D020;   // Player::GetPed                   thiscall,1 -> Ped *
extern LPVOID _Player_41DC40;   // Player::AddMoney                 thiscall,2 -> int
extern LPVOID _Player_41DC70;   // Player::GetCurrentPlayer         thiscall,1 -> char
extern LPVOID _Player_41E1E0;   // Player::Init                     thiscall,1 -> ushort
extern LPVOID _Player_41E260;   // Player::WorldToScreen            thiscall,2 -> int
extern LPVOID _Player_41E390;   // Player::IsActionAllowed          thiscall,1 -> bool
extern LPVOID _Player_4202A0;   // Player::sub_4202A0               thiscall,3 -> S103 *
extern LPVOID _Player_4202E0;   // Player::sub_4202E0               thiscall,3 -> _DWORD *
extern LPVOID _Player_420360;   // Player::sub_420360               thiscall,1 -> BOOL
extern LPVOID _Player_420390;   // Player::sub_420390               thiscall,2 -> _DWORD *
extern LPVOID _Player_421100;   // Player::IsStateEightWithCondition thiscall,1 -> bool
extern LPVOID _Player_421150;   // Player::sub_421150               thiscall,2 -> void
extern LPVOID _Player_4211A0;   // Player::GetSpeed                 thiscall,2 -> void
extern LPVOID _Player_4211C0;   // Player::sub_4211C0               thiscall,2 -> S900 *
extern LPVOID _Player_421260;   // Player::ClearPlayerFlag          thiscall,1 -> void
extern LPVOID _Player_421270;   // Player::sub_421270               thiscall,1 -> char
extern LPVOID _Player_4212A0;   // Player::SetAttackChanged         thiscall,1 -> void
extern LPVOID _Player_4212B0;   // Player::SetAttackIsChanged       thiscall,1 -> void
extern LPVOID _Player_421980;   // Player::GetMoneyPlayer           thiscall,1 -> int
extern LPVOID _Player_421990;   // Player::DecreaseInMoney          thiscall,2 -> int
extern LPVOID _Player_4219A0;   // Player::sub_4219A0               thiscall,2 -> bool
extern LPVOID _Player_4219D0;   // Player::GetId                    thiscall,1 -> char
extern LPVOID _Player_424470;   // Player::NotMoney                 thiscall,2 -> char
extern LPVOID _Player_4348F0;   // Player::GetFW                    thiscall,2 -> FW *
extern LPVOID _Player_434900;   // Player::GetMultiPlayerMode       thiscall,1 -> CameraOrPhysics *
extern LPVOID _Player_434920;   // Player::GetPowerUp               thiscall,2 -> bool
extern LPVOID _Player_434940;   // Player::DecrPowerUp              thiscall,2 -> void
extern LPVOID _Player_434950;   // Player::SetPlayerState           thiscall,2 -> void
extern LPVOID _Player_453A90;   // Player::sub_453A90               thiscall,2 -> char
extern LPVOID _Player_453AB0;   // Player::sub_453AB0               thiscall,1 -> unsigned __int8
extern LPVOID _Player_45A970;   // Player::Player_Des               thiscall,2 -> Player *
extern LPVOID _Player_45B0C0;   // Player::IsMainPedSet             thiscall,1 -> bool
extern LPVOID _Player_45B0D0;   // Player::SetActive                thiscall,1 -> void
extern LPVOID _Player_461DB0;   // Player::NextPlayer               thiscall,1 -> byte
extern LPVOID _Player_4766A0;   // Player::GetMultiPlayer           thiscall,1 -> PlayerStats *
extern LPVOID _Player_4766B0;   // Player::SetMultiPlayer           thiscall,2 -> int
extern LPVOID _Player_4766C0;   // Player::getMoney                 thiscall,1 -> PlayerStats *
extern LPVOID _Player_4766D0;   // Player::GetRespect               thiscall,1 -> Gang *
extern LPVOID _Player_476700;   // Player::sub_476700               thiscall,1 -> bool
extern LPVOID _Player_476730;   // Player::sub_476730               thiscall,1 -> bool
extern LPVOID _Player_482CC0;   // Player::sub_482CC0               thiscall,4 -> int
extern LPVOID _Player_49DD10;   // Player::GetCarWithTrailer        thiscall,1 -> Car *
extern LPVOID _Player_49DD20;   // Player::SetActivePlayer          thiscall,2 -> void
extern LPVOID _Player_49DD30;   // Player::ApplyEntryControlState   thiscall,1 -> Car *
extern LPVOID _Player_49DD80;   // Player::IsTrailerAttached        thiscall,1 -> bool
extern LPVOID _Player_49DDF0;   // Player::sub_49DDF0               thiscall,1 -> char
extern LPVOID _Player_49DE40;   // Player::sub_49DE40               thiscall,1 -> _DWORD *
extern LPVOID _Player_49DEF0;   // Player::SavePlayerGlobals2       thiscall,1 -> TrailerCtrl *
extern LPVOID _Player_49DF90;   // Player::sub_49DF90               thiscall,1 -> _DWORD *
extern LPVOID _Player_49E040;   // Player::RestorePlayerGlobals     thiscall,1 -> TrailerCtrl *
extern LPVOID _Player_49E270;   // Player::IsVisible                thiscall,1 -> char
extern LPVOID _Player_49E650;   // Player::GetRelativePosition      thiscall,3 -> _DWORD *
extern LPVOID _Player_49E820;   // Player::IsFlagAndEngineActive    thiscall,1 -> bool
extern LPVOID _Player_49E850;   // Player::sub_49E850               thiscall,2 -> SpriteS1 *
extern LPVOID _Player_49E8E0;   // Player::sub_49E8E0               thiscall,2 -> SpriteS1 *
extern LPVOID _Player_49E950;   // Player::UpdateSoundFlagDispatch  thiscall,1 -> AudioManager *
extern LPVOID _Player_49E980;   // Player::UpdateTargetScreenPos    thiscall,1 -> int *
extern LPVOID _Player_49EA60;   // Player::UseAmmo                  thiscall,1 -> void
extern LPVOID _Player_49EA70;   // Player::AmmunitionUpdate         thiscall,1 -> Tango *
extern LPVOID _Player_49EC80;   // Player::CacheCarEngineValue      thiscall,1 -> Car *
extern LPVOID _Player_49ECA0;   // Player::CacheCarEngineState      thiscall,1 -> int
extern LPVOID _Player_49ECC0;   // Player::SetActiveEngine          thiscall,1 -> Car *
extern LPVOID _Player_49ED00;   // Player::UpdateCarPosition        thiscall,1 -> S103 *
extern LPVOID _Player_49ED60;   // Player::sub_49ED60               thiscall,1 -> _DWORD *
extern LPVOID _Player_49EDC0;   // Player::ConvertToScreen          thiscall,1 -> S103 **
extern LPVOID _Player_49EE10;   // Player::sub_49EE10               thiscall,2 -> _DWORD *
extern LPVOID _Player_49EE80;   // Player::UpdateCarSprite          thiscall,1 -> SpriteS3 *
extern LPVOID _Player_49EEB0;   // Player::UpdateCarSpriteWithTrailer thiscall,1 -> TrailerCtrl *
extern LPVOID _Player_49EF50;   // Player::sub_49EF50               thiscall,2 -> unsigned int
extern LPVOID _Player_49EF80;   // Player::IsSpriteActiveAndCurrent thiscall,1 -> bool
extern LPVOID _Player_49F010;   // Player::sub_49F010               thiscall,1 -> char
extern LPVOID _Player_49F170;   // Player::AreTrailerSpritesActive  thiscall,1 -> bool
extern LPVOID _Player_49F1B0;   // Player::SetupCarBlips            thiscall,1 -> SpriteS1 *
extern LPVOID _Player_49F280;   // Player::ApplyAlarmControlState   thiscall,1 -> char
extern LPVOID _Player_49F2D0;   // Player::sub_49F2D0               thiscall,1 -> char
extern LPVOID _Player_49F350;   // Player::HandleCarSurface         thiscall,1 -> char
extern LPVOID _Player_49F460;   // Player::sub_49F460               thiscall,2 -> unsigned int
extern LPVOID _Player_49F4E0;   // Player::sub_49F4E0               thiscall,1 -> void *
extern LPVOID _Player_49F4F0;   // Player::sub_49F4F0               thiscall,1 -> Weapon *
extern LPVOID _Player_49F500;   // Player::sub_49F500               thiscall,1 -> ushort
extern LPVOID _Player_49F570;   // Player::sub_49F570               thiscall,2 -> int *
extern LPVOID _Player_49F660;   // Player::GetCarHudSourcePosition  thiscall,2 -> SpriteS1 *
extern LPVOID _Player_49F6C0;   // Player::GetCarHudTransform       thiscall,2 -> SpriteS1 *
extern LPVOID _Player_49F720;   // Player::GetCarBlipTransform      thiscall,2 -> SpriteS1 *
extern LPVOID _Player_49F930;   // Player::UpdateTrackedCar         thiscall,2 -> int *
extern LPVOID _Player_49FAC0;   // Player::ResetWeaponTimers        thiscall,1 -> ushort
extern LPVOID _Player_49FB00;   // Player::sub_49FB00               thiscall,6 -> char
extern LPVOID _Player_49FBE0;   // Player::sub_49FBE0               thiscall,3 -> SpriteS1 **
extern LPVOID _Player_49FDC0;   // Player::RefreshCarSpriteAndBlip  thiscall,2 -> __int16
extern LPVOID _Player_49FF70;   // Player::sub_49FF70               thiscall,2 -> __int16
extern LPVOID _Player_49FF80;   // Player::sub_49FF80               thiscall,2 -> char
extern LPVOID _Player_4A0020;   // Player::AddCarSpriteToRender     thiscall,1 -> char
extern LPVOID _Player_4A0080;   // Player::sub_4A0080               thiscall,1 -> char
extern LPVOID _Player_4A0120;   // Player::sub_4A0120               thiscall,5 -> __int16
extern LPVOID _Player_4A0290;   // Player::UpdatePlayerCarVisual    thiscall,1 -> char
extern LPVOID _Player_4A0560;   // Player::RenderArrowsTrailer      thiscall,1 -> TrailerCtrl *
extern LPVOID _Player_4A0850;   // Player::UpdateCarArrows          thiscall,4 -> _DWORD *
extern LPVOID _Player_4A0900;   // Player::sub_4A0900               thiscall,2 -> void *
extern LPVOID _Player_4A0930;   // Player::sub_4A0930               thiscall,2 -> void *
extern LPVOID _Player_4A0960;   // Player::sub_4A0960               thiscall,2 -> Car *
extern LPVOID _Player_4A09B0;   // Player::sub_4A09B0               thiscall,3 -> void
extern LPVOID _Player_4A0C60;   // Player::UpdateHudCarPosition     thiscall,1 -> _DWORD *
extern LPVOID _Player_4A0CC0;   // Player::FinalizeHudCarPosition   thiscall,1 -> int
extern LPVOID _Player_4A0D10;   // Player::sub_4A0D10               thiscall,3 -> _DWORD *
extern LPVOID _Player_4A0D40;   // Player::UpdateCarWeapon          thiscall,6 -> _DWORD *
extern LPVOID _Player_4A0F30;   // Player::UpdateCarArrows2         thiscall,2 -> SpriteS1 **
extern LPVOID _Player_4A1130;   // Player::UpdateFirstCarBlip       thiscall,2 -> _DWORD *
extern LPVOID _Player_4A1360;   // Player::UpdateSecondCarBlip      thiscall,2 -> _DWORD *
extern LPVOID _Player_4A16B0;   // Player::UpdateTargetArrowScreenPos thiscall,1 -> SpriteS1 *
extern LPVOID _Player_4A1B20;   // Player::UpdateCarMarkerScreenPos thiscall,1 -> char
extern LPVOID _Player_4A1BA0;   // Player::IncCounterTo20           thiscall,1 -> char
extern LPVOID _Player_4A1BE0;   // Player::ResetPlayerState         thiscall,1 -> int
extern LPVOID _Player_4A1DA0;   // Player::sub_4A1DA0               thiscall,1 -> char
extern LPVOID _Player_4A20E0;   // Player::UpdateStateBlip          thiscall,1 -> void
extern LPVOID _Player_4A2240;   // Player::UpdateCarTransform       thiscall,2 -> __int16
extern LPVOID _Player_4A2640;   // Player::UpdateTrailerCarTransform thiscall,2 -> TrailerCtrl *
extern LPVOID _Player_4A26C0;   // Player::UpdatePlayerSpriteFlag   thiscall,2 -> bool
extern LPVOID _Player_4A2980;   // Player::ProcessArrows            thiscall,1 -> char
extern LPVOID _Player_4A2A30;   // Player::sub_4A2A30               thiscall,1 -> void *
extern LPVOID _Player_4A2B40;   // Player::sub_4A2B40               thiscall,1 -> void *
extern LPVOID _Player_4A2C70;   // Player::sub_4A2C70               thiscall,1 -> void *
extern LPVOID _Player_4A2D70;   // Player::sub_4A2D70               thiscall,1 -> char
extern LPVOID _Player_4A2DB0;   // Player::TryStartRaceMusic        thiscall,1 -> char
extern LPVOID _Player_4A2E00;   // Player::sub_4A2E00               thiscall,4 -> int
extern LPVOID _Player_4A2E30;   // Player::PlaceCar                 thiscall,2 -> SpriteS1 *
extern LPVOID _Player_4A2F20;   // Player::UpdateHudCarState        thiscall,1 -> int
extern LPVOID _Player_4A2F90;   // Player::sub_4A2F90               thiscall,3 -> char
extern LPVOID _Player_4A30A0;   // Player::sub_4A30A0               thiscall,3 -> int
extern LPVOID _Player_4A3120;   // Player::Render                   thiscall,1 -> SpriteS1 *
extern LPVOID _Player_4A3140;   // Player::sub_4A3140               thiscall,3 -> Car *
extern LPVOID _Player_4A31B0;   // Player::sub_4A31B0               thiscall,5 -> int **
extern LPVOID _Player_4A32D0;   // Player::sub_4A32D0               thiscall,2 -> char
extern LPVOID _Player_4A34A0;   // Player::sub_4A34A0               thiscall,2 -> EngineStruct *
extern LPVOID _Player_4A3A40;   // Player::sub_4A3A40               thiscall,3 -> char
extern LPVOID _Player_4A3DF0;   // Player::sub_4A3DF0               thiscall,3 -> char
extern LPVOID _Player_4A3FB0;   // Player::sub_4A3FB0               thiscall,3 -> char
extern LPVOID _Player_4A4170;   // Player::sub_4A4170               thiscall,3 -> void
extern LPVOID _Player_4A4270;   // Player::sub_4A4270               thiscall,3 -> void
extern LPVOID _Player_4A4310;   // Player::sub_4A4310               thiscall,1 -> char
extern LPVOID _Player_4A4490;   // Player::UpdateHornState          thiscall,1 -> char
extern LPVOID _Player_4A4570;   // Player::UpdateControlState       thiscall,1 -> bool
extern LPVOID _Player_4A4780;   // Player::UpdateRecentCarList      thiscall,3 -> char
extern LPVOID _Player_4A47F0;   // Player::sub_4A47F0               thiscall,2 -> void *
extern LPVOID _Player_4A4890;   // Player::sub_4A4890               thiscall,2 -> int
extern LPVOID _Player_4A48C0;   // Player::SetDefautWeapon          thiscall,1 -> void
extern LPVOID _Player_4A48E0;   // Player::SetActivePowerUps        thiscall,1 -> int
extern LPVOID _Player_4A4930;   // Player::SetPlayer                thiscall,2 -> void
extern LPVOID _Player_4A4940;   // Player::sub_4A4940               thiscall,2 -> char
extern LPVOID _Player_4A49B0;   // Player::sub_4A49B0               thiscall,1 -> byte
extern LPVOID _Player_4A49C0;   // Player::sub_4A49C0               thiscall,2 -> char
extern LPVOID _Player_4A4AE0;   // Player::sub_4A4AE0               thiscall,1 -> bool
extern LPVOID _Player_4A4C40;   // Player::sub_4A4C40               thiscall,2 -> char
extern LPVOID _Player_4A4C90;   // Player::sub_4A4C90               thiscall,1 -> int
extern LPVOID _Player_4A4CB0;   // Player::sub_4A4CB0               thiscall,1 -> void
extern LPVOID _Player_4A4CF0;   // Player::sub_4A4CF0               thiscall,2 -> int
extern LPVOID _Player_4A4D50;   // Player::AddLives                 thiscall,2 -> int
extern LPVOID _Player_4A4E10;   // Player::GetDeathDescription      thiscall,1 -> const char *
extern LPVOID _Player_4A4E70;   // Player::sub_4A4E70               thiscall,1 -> void
extern LPVOID _Player_4A4EA0;   // Player::PlayerControl            thiscall,1 -> void
extern LPVOID _Player_4A5100;   // Player::HasPedInCar              thiscall,1 -> char
extern LPVOID _Player_4A5130;   // Player::GetCurrentPed            thiscall,1 -> Ped *
extern LPVOID _Player_4A5150;   // Player::GetActivePed             thiscall,1 -> Ped *
extern LPVOID _Player_4A5180;   // Player::sub_4A5180               thiscall,1 -> void
extern LPVOID _Player_4A51C0;   // Player::sub_4A51C0               thiscall,2 -> char
extern LPVOID _Player_4A5220;   // Player::sub_4A5220               thiscall,3 -> void
extern LPVOID _Player_4A5300;   // Player::ProcessWeaponChange      thiscall,1 -> void
extern LPVOID _Player_4A53D0;   // Player::sub_4A53D0               thiscall,1 -> bool
extern LPVOID _Player_4A5400;   // Player::sub_4A5400               thiscall,3 -> char
extern LPVOID _Player_4A5460;   // Player::sub_4A5460               thiscall,3 -> char
extern LPVOID _Player_4A5570;   // Player::GetCarWeapons            thiscall,2 -> char
extern LPVOID _Player_4A5600;   // Player::sub_4A5600               thiscall,1 -> void
extern LPVOID _Player_4A5640;   // Player::RestoreOnFootWeapons     thiscall,1 -> char
extern LPVOID _Player_4A5690;   // Player::StoreOnFootWeapons       thiscall,1 -> char
extern LPVOID _Player_4A5710;   // Player::sub_4A5710               thiscall,1 -> int
extern LPVOID _Player_4A5780;   // Player::GivePowerUp              thiscall,2 -> char
extern LPVOID _Player_4A59A0;   // Player::sub_4A59A0               thiscall,1 -> char
extern LPVOID _Player_4A5A50;   // Player::sub_4A5A50               thiscall,2 -> int
extern LPVOID _Player_4A5AD0;   // Player::DoTeleport               thiscall,1 -> void
extern LPVOID _Player_4A5B40;   // Player::sub_4A5B40               thiscall,2 -> int
extern LPVOID _Player_4A5E90;   // Player::sub_4A5E90               thiscall,2 -> char
extern LPVOID _Player_4A6050;   // Player::sub_4A6050               thiscall,1 -> void
extern LPVOID _Player_4A6100;   // Player::sub_4A6100               thiscall,1 -> unsigned __int8 *
extern LPVOID _Player_4A61F0;   // Player::sub_4A61F0               thiscall,1 -> int
extern LPVOID _Player_4A62B0;   // Player::SetPedOutOfCar           thiscall,1 -> char
extern LPVOID _Player_4A6310;   // Player::sub_4A6310               thiscall,1 -> byte
extern LPVOID _Player_4A6350;   // Player::sub_4A6350               thiscall,2 -> char
extern LPVOID _Player_4A6400;   // Player::sub_4A6400               thiscall,2 -> char
extern LPVOID _Player_4A6530;   // Player::GetPedScreenPosition     thiscall,4 -> int
extern LPVOID _Player_4A65E0;   // Player::GetActivePlayerCar       thiscall,1 -> Car *
extern LPVOID _Player_4A6610;   // Player::GetPosition              thiscall,4 -> GameObject *
extern LPVOID _Player_4A6900;   // Player::sub_4A6900               thiscall,1 -> int
extern LPVOID _Player_4A69A0;   // Player::sub_4A69A0               thiscall,1 -> int
extern LPVOID _Player_4A6A80;   // Player::sub_4A6A80               thiscall,1 -> int
extern LPVOID _Player_4A6B20;   // Player::sub_4A6B20               thiscall,2 -> int
extern LPVOID _Player_4A6C80;   // Player::sub_4A6C80               thiscall,2 -> int
extern LPVOID _Player_4A6EF0;   // Player::sub_4A6EF0               thiscall,1 -> void
extern LPVOID _Player_4A6FD0;   // Player::sub_4A6FD0               thiscall,1 -> char
extern LPVOID _Player_4A7010;   // Player::sub_4A7010               thiscall,2 -> void
extern LPVOID _Player_4A7680;   // Player::sub_4A7680               thiscall,1 -> void
extern LPVOID _Player_4A76D0;   // Player::sub_4A76D0               thiscall,2 -> char
extern LPVOID _Player_4A7910;   // Player::HandleDeath              thiscall,1 -> void
extern LPVOID _Player_4A7B70;   // Player::sub_4A7B70               thiscall,1 -> void
extern LPVOID _Player_4A7BA0;   // Player::sub_4A7BA0               thiscall,1 -> char
extern LPVOID _Player_4A7E80;   // Player::sub_4A7E80               thiscall,1 -> __int16
extern LPVOID _Player_4A81E0;   // Player::sub_4A81E0               thiscall,1 -> __int16
extern LPVOID _Player_4A8340;   // Player::sub_4A8340               thiscall,1 -> void
extern LPVOID _Player_4A83C0;   // Player::Player                   thiscall,2 -> Player *
extern LPVOID _Player_4BA0A0;   // Player::GetScreenDimensions      thiscall,3 -> int
extern LPVOID _Player_4C7340;   // Player::GetPlayerTangible        thiscall,1 -> Tango *
extern LPVOID _Player_4CCAB0;   // Player::sub_4CCAB0               thiscall,1 -> int
extern LPVOID _Player_4CCAD0;   // Player::sub_4CCAD0               thiscall,1 -> int
extern LPVOID _Player_4CCAE0;   // Player::sub_4CCAE0               thiscall,1 -> int

DWORD __fastcall HookPlayer_401B40(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_401B90(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_40CE50(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_40CE70(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_40E530(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_40E570(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_40E8D0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookPlayer_40EC20(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookPlayer_40F790(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_40F820(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_40F840(void* self, DWORD d);
DWORD __fastcall HookPlayer_411810(void* self, DWORD d);
void __fastcall HookPlayer_411820(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_411830(void* self, DWORD d);
void __fastcall HookPlayer_411840(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_411850(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_411860(void* self, DWORD d);
DWORD __fastcall HookPlayer_41D020(void* self, DWORD d);
DWORD __fastcall HookPlayer_41DC40(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_41DC70(void* self, DWORD d);
DWORD __fastcall HookPlayer_41E1E0(void* self, DWORD d);
DWORD __fastcall HookPlayer_41E260(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_41E390(void* self, DWORD d);
DWORD __fastcall HookPlayer_4202A0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4202E0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_420360(void* self, DWORD d);
DWORD __fastcall HookPlayer_420390(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_421100(void* self, DWORD d);
void __fastcall HookPlayer_421150(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4211A0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4211C0(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_421260(void* self, DWORD d);
DWORD __fastcall HookPlayer_421270(void* self, DWORD d);
void __fastcall HookPlayer_4212A0(void* self, DWORD d);
void __fastcall HookPlayer_4212B0(void* self, DWORD d);
DWORD __fastcall HookPlayer_421980(void* self, DWORD d);
DWORD __fastcall HookPlayer_421990(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4219A0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4219D0(void* self, DWORD d);
DWORD __fastcall HookPlayer_424470(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4348F0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_434900(void* self, DWORD d);
DWORD __fastcall HookPlayer_434920(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_434940(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_434950(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_453A90(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_453AB0(void* self, DWORD d);
DWORD __fastcall HookPlayer_45A970(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_45B0C0(void* self, DWORD d);
void __fastcall HookPlayer_45B0D0(void* self, DWORD d);
DWORD __fastcall HookPlayer_461DB0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4766A0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4766B0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4766C0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4766D0(void* self, DWORD d);
DWORD __fastcall HookPlayer_476700(void* self, DWORD d);
DWORD __fastcall HookPlayer_476730(void* self, DWORD d);
DWORD __fastcall HookPlayer_482CC0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookPlayer_49DD10(void* self, DWORD d);
void __fastcall HookPlayer_49DD20(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49DD30(void* self, DWORD d);
DWORD __fastcall HookPlayer_49DD80(void* self, DWORD d);
DWORD __fastcall HookPlayer_49DDF0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49DE40(void* self, DWORD d);
DWORD __fastcall HookPlayer_49DEF0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49DF90(void* self, DWORD d);
DWORD __fastcall HookPlayer_49E040(void* self, DWORD d);
DWORD __fastcall HookPlayer_49E270(void* self, DWORD d);
DWORD __fastcall HookPlayer_49E650(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_49E820(void* self, DWORD d);
DWORD __fastcall HookPlayer_49E850(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49E8E0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49E950(void* self, DWORD d);
DWORD __fastcall HookPlayer_49E980(void* self, DWORD d);
void __fastcall HookPlayer_49EA60(void* self, DWORD d);
DWORD __fastcall HookPlayer_49EA70(void* self, DWORD d);
DWORD __fastcall HookPlayer_49EC80(void* self, DWORD d);
DWORD __fastcall HookPlayer_49ECA0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49ECC0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49ED00(void* self, DWORD d);
DWORD __fastcall HookPlayer_49ED60(void* self, DWORD d);
DWORD __fastcall HookPlayer_49EDC0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49EE10(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49EE80(void* self, DWORD d);
DWORD __fastcall HookPlayer_49EEB0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49EF50(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49EF80(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F010(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F170(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F1B0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F280(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F2D0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F350(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F460(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49F4E0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F4F0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F500(void* self, DWORD d);
DWORD __fastcall HookPlayer_49F570(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49F660(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49F6C0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49F720(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49F930(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49FAC0(void* self, DWORD d);
DWORD __fastcall HookPlayer_49FB00(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4);
DWORD __fastcall HookPlayer_49FBE0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_49FDC0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49FF70(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_49FF80(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A0020(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A0080(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A0120(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookPlayer_4A0290(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A0560(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A0850(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookPlayer_4A0900(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A0930(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A0960(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A09B0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A0C60(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A0CC0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A0D10(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A0D40(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4);
DWORD __fastcall HookPlayer_4A0F30(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A1130(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A1360(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A16B0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A1B20(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A1BA0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A1BE0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A1DA0(void* self, DWORD d);
void __fastcall HookPlayer_4A20E0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2240(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A2640(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A26C0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A2980(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2A30(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2B40(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2C70(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2D70(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2DB0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2E00(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookPlayer_4A2E30(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A2F20(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A2F90(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A30A0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A3120(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A3140(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A31B0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3);
DWORD __fastcall HookPlayer_4A32D0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A34A0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A3A40(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A3DF0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A3FB0(void* self, DWORD d, DWORD a0, DWORD a1);
void __fastcall HookPlayer_4A4170(void* self, DWORD d, DWORD a0, DWORD a1);
void __fastcall HookPlayer_4A4270(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A4310(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A4490(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A4570(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A4780(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A47F0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A4890(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A48C0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A48E0(void* self, DWORD d);
void __fastcall HookPlayer_4A4930(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A4940(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A49B0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A49C0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A4AE0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A4C40(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A4C90(void* self, DWORD d);
void __fastcall HookPlayer_4A4CB0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A4CF0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A4D50(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A4E10(void* self, DWORD d);
void __fastcall HookPlayer_4A4E70(void* self, DWORD d);
void __fastcall HookPlayer_4A4EA0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5100(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5130(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5150(void* self, DWORD d);
void __fastcall HookPlayer_4A5180(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A51C0(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A5220(void* self, DWORD d, DWORD a0, DWORD a1);
void __fastcall HookPlayer_4A5300(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A53D0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5400(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A5460(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4A5570(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A5600(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5640(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5690(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5710(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5780(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A59A0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5A50(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A5AD0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A5B40(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A5E90(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A6050(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6100(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A61F0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A62B0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6310(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6350(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A6400(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A6530(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookPlayer_4A65E0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6610(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2);
DWORD __fastcall HookPlayer_4A6900(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A69A0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6A80(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6B20(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4A6C80(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A6EF0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A6FD0(void* self, DWORD d);
void __fastcall HookPlayer_4A7010(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A7680(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A76D0(void* self, DWORD d, DWORD a0);
void __fastcall HookPlayer_4A7910(void* self, DWORD d);
void __fastcall HookPlayer_4A7B70(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A7BA0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A7E80(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A81E0(void* self, DWORD d);
void __fastcall HookPlayer_4A8340(void* self, DWORD d);
DWORD __fastcall HookPlayer_4A83C0(void* self, DWORD d, DWORD a0);
DWORD __fastcall HookPlayer_4BA0A0(void* self, DWORD d, DWORD a0, DWORD a1);
DWORD __fastcall HookPlayer_4C7340(void* self, DWORD d);
DWORD __fastcall HookPlayer_4CCAB0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4CCAD0(void* self, DWORD d);
DWORD __fastcall HookPlayer_4CCAE0(void* self, DWORD d);

void DumpPlayerRing(FILE* f);     // full ring dump (crash forensics)
void DumpPlayerRingFile(void);    // append new entries to player_trace.log
