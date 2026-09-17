#ifndef __GAME_H__
#define __GAME_H__
#include <assert.h>
#include "cPlayer.h"

// Game (S300), INSTANCE IS HEAP-ALLOCATED (operator_new(0x40) in InitFrontedLessGame),
// global cell gGame @0x005EB4FC holds the pointer. sizeof 0x40.
// Layout verified from Game::Game ctor asm tail (gta2.exe.asm Game__Game):
//   mov [esi+20h..22h], bl; mov dword ptr [esi],1; mov unk_5E7220,bl;
//   mov [esi+28h], ebp (isDead=-1); mov [esi+30h], bl (NoFrameLimit);
//   mov [esi+2Ch], ebx (State=0); mov [esi+34h], ebx (SkipPolice=0)
// and Game::sub_45A480 / Game::GetState decompilation.
struct Game{
	bool	Status;           // ctor sets 1
	Player* pPlayer[6];      // ArrayPlayer[6] (Player*), ctor memsets + builds
	Player* CurrentPlayer;   // current player, ctor copies from PlayerMain
	char	Index;            // CurrentPlayerNumber (IDA "Index")
	char	CurrentPlayerCopy;// IDA "CurrentPlayerCopy"
	char	fi_22;            // IDA "field_22"
	char	NumberPlayer;     // IDA "MaxIdx": total number of player slots (modeStatus arg)
	char	PlayerInFocus;
	char	fi_25;
	char	field_26;
	char	field_27;
	int		isDead;           // ctor = -1 (gate: sub_45A480 writes State only if isDead==-1||isDead>new)
	int		State;            // Game::GetState @0x004D09C0 returns this
	char	NoFrameLimit;     // byte @0x30 cleared by ctor (sub_45A460 NoFrameLimit)
	char	pad_31[3];
	int		SkipPolice;
	Player* Player;           // PlayerMain pointer (the active/focused player struct)
	char	gSkilPolice;      // IDA "gSkilPolice" / bSkipPolice: saved at ctor [esi+3Ch] <- al
	char	field_3D;
	char	field_3E;
	char	field_3F;
};

static_assert(sizeof(Game) == 0x40, "ERROR GAME Struct");

// gGame is a POINTER CELL @0x005EB4FC pointing at the heap Game instance.
Game* GetGamePtr(); // reads *(Game**)0x005EB4FC, may be NULL

// Hook prototypes (__fastcall: this + _EDX placeholder, matching __thiscall ABI)
int  __fastcall HookSetState(Game* g, void* _EDX, int isDeadNew, int state, char bonus);
Game* __fastcall HookGameCtor(Game* g, void* _EDX, int index, char data);
void __stdcall  HookInitFrontedLessGame(void);
// --- Init-chain crash isolation markers ---
void __fastcall HookResurs(Game* g, void* _EDX);
void __fastcall Hook_sub_45B5F0(Game* g, void* _EDX);
void __fastcall HookSub465390(void* thisp, void* _EDX);
void __fastcall HookSub481890(void* thisp, void* _EDX);
void __fastcall HookStartGames(void* thisp, void* _EDX);
void __fastcall HookUpdateWrapper(void* thisp, void* _EDX);

#endif // !__GAME_H__

