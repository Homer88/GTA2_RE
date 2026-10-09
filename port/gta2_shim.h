// gta2_shim.h - шим для компиляции декомпилированных тел GTA2.
// Подключается сконвертированными .cpp модулей. Собирает:
//   gta2_clean.h   - очищенный unified-заголовок (структуры игры)
//   gta2_globals.h - объявления глобалей данных (unk_*/DAT_*)
//   gta2_protos.h  - прототипы всех функций (для кросс-модульных вызовов)

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Windows 10 SDK (10.0.26100) объявляет struct _TEB неполным (только typedef),
// а интринсик NtCurrentTeb() возвращает _TEB*. Тела SEH-прологов декомпилятора
// читают NtTib.ExceptionList, поэтому достраиваем переднюю часть структуры.
struct _TEB
{
    struct _NT_TIB  NtTib;
    void *EnvironmentPointer;
    void *ClientId[2];
    void *ActiveRpcHandle;
    void *ThreadLocalStoragePointer;
    struct _PEB *ProcessEnvironmentBlock;
    unsigned long LastErrorValue;
    unsigned long CountOfOwnedCriticalSections;
    void *CsrClientThread;
    void *Win32ThreadInfo;
    unsigned long User32Reserved[26];
    unsigned long UserReserved[5];
    void *WOW32Reserved;
    unsigned long CurrentLocale;
    unsigned long FpSoftwareStatusRegister;
    void *ReservedForOS[0x69];
    void *ReservedForSubsystem;
    void *TlsSlots[0x40];
};

// --- макросы Ghidra CONCATxx ---
#define CONCAT22(hi, lo)  (((unsigned int)(lo)) | (((unsigned int)(hi)) << 16))
#define CONCAT31(hi, lo)  (((unsigned int)(lo)) | (((unsigned int)(hi)) << 24))
#define qmemcpy memcpy

// --- типы декомпилятора IDA/Ghidra ---
typedef unsigned char  _BYTE;
typedef unsigned short _WORD;
typedef unsigned int   _DWORD;
typedef unsigned __int64 _QWORD;

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;
typedef unsigned __int64 qword;
typedef unsigned short ushort;
typedef unsigned char  undefined;
typedef unsigned int   GLuint;
typedef unsigned int   GLenum;
typedef int            GLint;
typedef unsigned char  undefined1;
typedef unsigned short undefined2;
typedef unsigned int   undefined3;
typedef unsigned int   undefined4;
typedef unsigned __int64 undefined8;
typedef long double    float10;   // Ghidra 80-bit float тип

typedef unsigned char   uchar;
typedef unsigned int    uint;
typedef unsigned long   ulong;
typedef unsigned short  _BOOL2;
typedef unsigned int    _BOOL4;
typedef unsigned char   _BY;    // small int
typedef signed char     _SBYTE;
typedef unsigned char   _UBYTE;

// --- lvalue-макросы (IDA использует LOBYTE(x)=v как присваивание) ---
#undef  LOBYTE
#undef  HIBYTE
#undef  LOWORD
#undef  HIWORD
#undef  LODWORD
#undef  HIDWORD
#define LOBYTE(x)  (*((unsigned char *)&(x)))
#define HIBYTE(x)  (*((unsigned char *)&(x) + 1))
#ifndef BYTE1
#define BYTE1(x)   (*((unsigned char *)&(x) + 1))
#endif
#ifndef BYTE2
#define BYTE2(x)   (*((unsigned char *)&(x) + 2))
#endif
#ifndef BYTE3
#define BYTE3(x)   (*((unsigned char *)&(x) + 3))
#endif
#ifndef WORD1
#define WORD1(x)   (*((unsigned short *)&(x) + 1))
#endif
#define LOWORD(x)  (*((unsigned short *)&(x)))
#define HIWORD(x)  (*((unsigned short *)&(x) + 1))
#define LODWORD(x) (*((unsigned int *)&(x)))
#define HIDWORD(x) (*((unsigned int *)&(x) + 1))

#include "gta2_enums.h"
#include "gta2_clean.h"
#include "gta2_globals.h"
#include "structs_supplement.h"

// Структуры объявлены в глобальной области (gta2_clean.h), а прототипы живут
// в namespace gta2. Определения в port/out/*.cpp имеют вид
// "RET gta2::Class_Method(Type *self, ...)", где Type ищется в scope определения
// -> нужен using, иначе C2061/C2664.
// ВНИМАНИЕ: не добавлять сюда типы, уже видимые в gta2 через gta2_protos.h
// (SearchType, GlassInfo и т.п.) - using ломает их резолвинг.
namespace gta2 {
  using ::Ped;  using ::Car;  using ::Player;
  using ::SpriteS1;  using ::SpriteS2;  using ::SpriteS3;  using ::SpriteS4;
  using ::Style;  using ::Text;  using ::Object;  using ::PathNode;
  using ::PedManager;  using ::MissionManager;  using ::Hud;
  using ::AudioSourceParams;  using ::CarSystemManager;  using ::PublicTransport;
  using ::HudMessage;  using ::HudArrow;  using ::HudBrief;  using ::CameraOrPhysics;
  using ::SpriteEntry;  using ::Door;  using ::Character;
}

// --- системные typedef'ы, отсутствующие в windows.h при WIN32_LEAN_AND_MEAN ---
#include <time.h>

// DirectInput: только типы, используемые в декомпиляции GTA2 (dinput.h конфликтует
// с ручными LPDIENUMDEVICESCALLBACK в gta2_clean.h; LPDIRECTINPUTDEVICEA уже там)
struct IDirectInput8A;
typedef struct IDirectInput8A *LPDIRECTINPUTA8, *LPDIRECTINPUTDEVICEA8;
struct IDirectInputDevice8;
typedef struct IDirectInputDevice8 *LPDIRECTINPUTDEVICE8;
struct IDirectDraw;
typedef struct IDirectDraw *LPDIRECTDRAW;

// forward-объявления недостающих типов из прото
struct GlassInfo;
struct MissionManager;
struct Movie;
struct Keybord;
struct Police;
struct S410;
struct IImageList;
struct _IMAGELISTDRAWPARAMS;
typedef int (*_onexit_t)(void);
#include <commctrl.h>
#include <process.h>
#include <crtdbg.h>

// Miles Sound System SDK 5 (mss32.lib) — используется модулями audio/game
#include "../mss32/include/mss.h"

#include "gta2_protos.h"

// функции без тел в dump (Miles SDK-обёртки, gbh_*, внешние библиотеки)
#if defined(__has_include)
#  if __has_include("missing_protos.h")
#    include "missing_protos.h"
#  endif
#endif