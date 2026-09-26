#ifndef __CSAVELOG_H__
#define __CSAVELOG_H__

// ---------------------------------------------------------------------------
// Save-file write logger (S16 saves).
//
// Retail has exactly three writers, all __thiscall, all going through
// WriteSub_402CF0 ("wb") + ARWBinarySub_402DA0 ("ab", gta2.exe.c:3888/3926):
//
//   MissionManager::SaveFile        @0x0047EF40  player\plyslot%d.svg
//   PlayerData::WriteFileNamePlayer @0x004A89E0  player\plyslot%d.dat
//   PlayerData::sub_4A8D80          @0x004A8D80  player\hiscores.hsc
//
// Each detour runs the original first and then reads the produced file back
// off disk, so Save.log holds the literal bytes that reached the file rather
// than a reconstruction of what the writer meant to store.
//
// Detours must mirror the retail __thiscall ABI exactly. The __fastcall form
// (this in ECX, dummy EDX, real args on the stack) is how MSVC expresses that.
// ---------------------------------------------------------------------------

int __fastcall HookSaveFile(void* thisp, void* _EDX, char* pSaveFileName);
int __fastcall HookWriteFileNamePlayer(void* thisp, void* _EDX, unsigned short slot);
int __fastcall HookWriteHiscores(void* thisp, void* _EDX);

// ---------------------------------------------------------------------------
// Ручные правки сейва из инспектора / хоткеев. Все пишут и в block0 (файл .svg)
// и в живой Player (кошелёк), пишут в Save.log и возвращают новое значение.
// Суммы для кнопок "+ДЕНЬГИ" / "+РОЗЫСК" и хоткеев F8 / F9 - здесь, чтобы
// cInspector.cpp и cSaveLog.cpp видели одно и то же значение.
// ---------------------------------------------------------------------------
#define SAVE_HOTKEY_MONEY       50000UL
#define SAVE_HOTKEY_WANTED      1
#define WANTED_MAX_IN_GAME      6

unsigned long SaveDebugAddMoney(unsigned long delta);
unsigned int SaveDebugAddWanted(int delta);
void SaveDebugWhereAmI(const char* why);
void SaveDebugStartHotkeys(void);

#endif // __CSAVELOG_H__
