#include "MapRelatedStruct.h"
#include <cstring>
#include <new>

// Forward declarations for external functions
void* operator_new(size_t size);

// S16_02::sub_44C840 - init/zero the struct
void S16_02::sub_44C840(S16_02* p)
{
    memset(p, 0, sizeof(S16_02));
}

// S202::sub_41F980 - write value into field_0
void S202::sub_41F980(S202* p, int value)
{
    p->field_0 = value;
}
void free_0(void* ptr);
void* createBuffer(size_t size);
int debug_log(unsigned int a1, const char* a2, int a3);
void* malloc_0(size_t size);

// Additional missing struct/class forward declarations
class Car;
class Data16 { public: static int sub_40CE90(void*); unsigned short field_0; unsigned short field_2; int field_4; };
class FileMgr { public: static void* FileOpen(void*, LPCSTR); static int CloseFile(void*); static int Read(void*, void*); static int ReadLine(void*, char*, int); static int SeekPosition(void*, int); };
class Gangs { public: static int FindByName(int, const char*); static int AddNewGang(int, int); };
class JuncIds {
public:
    static int sub_40C6D0(void*, int, int, int);
    int Arr_0x884[128];
    int arr_0x884[128];
    int field_4;
    int field_CC62;
    int field_CC64;
    int Count;
    int Arr_316_Data16[32];
};
class Player { public: static int CheckCondition(void*, void*); static int IsCurrentPlayer(void*); static void* sub_401B40(void*, void*, int); static int sub_40CE70(void*); static int sub_41E260(void*); };
class PublicTransport;
class Radar { public: static void AddBlip(int, int, int, int); };
class S103 { public: static int sub_401D20(void*, int); };
class S115 { public: static int sub_469010(void*, int, int, int, int); static int sub_469070(void*, int, int, int, int); };
class Tango;
class TileAnim { public: static int sub_4C3470(void*, int); };
class Weapon { public: static int sub_41C1E0(void*); static int sub_432860(void*, int, void**); static int UseAmmo(void*, int); };

// Forward declarations for missing types/functions
struct Object;
struct Ped;

extern void* gObject;
void SpawnObject(Object* obj, unsigned char a2, int a3, int a4, int a5, int a6);
int sub_4BB860(void* a1, int a2, int a3, int a4);
int sub_4BB910(void* a1, int a2, int a3, int a4);
unsigned int sub_463940(Map* a1, int a2);
int bitShiftLeft1(int value, int shift);
int _strnicmp(const char*, const char*, size_t);
SpriteS1* sub_462ED0(SpriteS1* a1, __int16* a2);
int sub_40CE30(void* a1, int a2);
struct S200 { int A; };
struct WithS200 { S200 S200[1]; };
WithS200* sub_462EF0(Ped* a1, SpriteS1* a2);
struct Style { static int sub_49E540(void*, int); static int sub_49E570(void*, int); static int sub_462FB0(void*, int); static int sub_462FD0(void*, int); };
extern void* gStyle;

// Additional missing function forward declarations
int sub_4037E0(void*);
void* sub_42A630(void*, void*);
int sub_42A660(void*, int);
struct CarHolder { int Car; };
CarHolder* sub_42A6B0(void*, void*);
void* sub_462EA0(void*, void*);
int sub_463020(void*, unsigned char, unsigned char);
int sub_4630D0(int, int, int);
int sub_463150(int, int, int);
int sub_463210(int, int, int);
int sub_463480(int);
int sub_4634B0(int);
int sub_4634E0(void*);
int sub_463690(void*, int, int);
int sub_4637B0(int, int);
int sub_4690B0(void*, int, int, int, int);
int sub_4693A0(void*, int, int, int, int);
int sub_4725B0(unsigned short*, void*);
int sub_4828F0(void*, int);
int sub_4BB9C0(void*, int, int);
int sub_40E5A0(void*, void*, void*);
int sub_40E8D0(void*, void*, void*);
int sub_40FEE0(int, void*);
int sub_401B90(void*, int, void*);
int sub_41FC20(int, int, void*);
unsigned char CopyBuffer(unsigned char dest, const char* src);

// Global variable extern declarations
extern _WORD* dword_662B84;
extern _WORD* dword_662B8C;
extern _WORD* dword_662B90;
extern _WORD* dword_662BE8;
extern _BYTE* dword_662BA0;
extern _BYTE* dword_662BA4;
extern _BYTE* dword_662BCC;
extern _BYTE* dword_662BDC;
extern _BYTE* dword_662BE0;
extern _DWORD* dword_662BF0;
extern __int16 word_662BEC;
extern CarSystemManager* dword_662BAC;
extern CarSystemManager* dword_662BF8;
extern int arg0;  // global tile coord, used as ::arg0 in sub_465FE0/466170
extern unsigned char unk_662B88;
extern S16_02 unk_662B94;

extern unsigned char unk_662BA8;
extern unsigned char unk_662BB0;
extern unsigned char unk_662BBE;
extern unsigned char unk_662BBC;
extern S16_02 unk_662BC0;
extern unsigned char unk_662BD0;
extern int unk_662BF4;
extern unsigned char unk_662BD2;
extern unsigned char unk_662BE4;
extern unsigned char unk_662C00;
extern unsigned char unk_662C04;
extern unsigned char unk_662C98;
extern unsigned char unk_662CFC;
extern unsigned char byte_5EA6B8;
extern __int16 word_663290;
extern unsigned char unk_662DB0;
extern unsigned char unk_662DB1;
extern unsigned char unk_6630B0;
extern unsigned char unk_663108;
extern int glob_a8;  // was ::a8 in dump
extern CarSystemManager* glob_a5;  // was ::a5 in dump
extern int a5;  // global tile coordinate used as boundary in sub_465FE0/466170

// Additional missing extern globals
extern void* gJuncIds;
extern void* gTileAnim;
extern void* gGangs;
extern void* gS115;
extern unsigned char unk_662B80;
extern unsigned char unk_662BB4;
extern unsigned char unk_662BB8;
extern unsigned char unk_662C3C;
extern void* unk_662C50;
extern void* unk_662CF8;
extern int dword_5E6874;
extern void* unk_6630B8;
extern void* unk_663164;
extern void* unk_6631EC;
extern int log_routefinder;
extern char gStr[256];

// S16_01 helper - searches gap0 for entry matching coordinates a2,a3
static S16_01* S16_01_sub_463990(S16_01* s, char a2, char a3, int a4) {
    (void)a4;
    if (s->field_320 <= 0)
        return (S16_01*)-1;
    S16_01* result = s;
    while (result->gap0[4] != a2 || result->gap0[5] != a3) {
        result = (S16_01*)((char*)result + 8);
        if ((int)result >= (int)&s->gap0[8 * s->field_320])
            return (S16_01*)-1;
    }
    s->field_320++;
    return result;
}

//=============================================================================
// MapRelatedStruct::MapRelatedStruct - Constructor
//=============================================================================
// MapRelatedStruct::MapRelatedStruct - Constructor
//=============================================================================
MapRelatedStruct::MapRelatedStruct()
{
  s16_01.field_320 = 0;
  Len = -1;
  field_369 = -1;
  Buffer_ZONE = 0;
  count = 0;
  Buffer_MOBJ = 0;
  field_344 = 0;
  getMap() = 0;
  field_330 = 0;
  field_334 = 0;
  Buffer_ANIM = 0;
  Buffer_LGHT = 0;
  field_348 = 0;
  field_350 = 0;
  field_34C = 0;
  field_354 = 0;
  field_358 = 0;
  field_35C = 0;
  field_360 = 0;
  field_364 = -1;
  field_36A = 0;
  field_36B = 0;
  field_36C = 0;
  field_366 = 0;
  field_36D = 0;
  field_36E = 0;
  field_36F = 0;
  S16_02::sub_44C840(&unk_662BC0);
  S16_02::sub_44C840(&unk_662B94);
  unk_662B94.field = 3073;
  unk_662B94.field_2 = 3073;
  unk_662B94.field_4 = 3073;
  unk_662B94.field_6 = 3073;
  unk_662B94.field_8 = 1;
  unk_662B94.field_B = 3;
}

//=============================================================================
// MapRelatedStruct::~MapRelatedStruct - Destructor
//=============================================================================
MapRelatedStruct::~MapRelatedStruct()
{
  sub_464B30();
}

//=============================================================================
// MapRelatedStruct::sub_464B30 - Destructor helper
//=============================================================================
void MapRelatedStruct::sub_464B30()
{
  void *v2;
  void *v3;
  void *v4;
  int v5;
  void *v6;
  void *v7;
  void *v8;

  if ( Buffer_LGHT )
    free_0(Buffer_LGHT);
  v2 = (void *)count;
  Buffer_LGHT = 0;
  if ( v2 )
    free_0(v2);
  v3 = field_330;
  count = 0;
  if ( v3 )
    free_0(v3);
  v4 = Buffer_ANIM;
  field_330 = 0;
  if ( v4 )
    free_0(v4);
  v5 = (int)getMap();
  Buffer_ANIM = 0;
  if ( v5 )
  {
    v6 = *(void **)(v5 + 262152);
    if ( v6 )
      free_0(v6);
    *(_DWORD *)((int)getMap() + 262152) = 0;
    if ( *(_DWORD *)((int)getMap() + 262156) )
      free_0(*(void **)((int)getMap() + 262156));
    *(_DWORD *)((int)getMap() + 262156) = 0;
    free((LPVOID)(int)getMap());
  }
  if ( field_334 )
    free_0(field_334);
  v7 = Buffer_MOBJ;
  field_334 = 0;
  if ( v7 )
    free_0(v7);
  v8 = (void *)field_344;
  Buffer_MOBJ = 0;
  if ( v8 )
    free_0(v8);
  field_344 = 0;
}

//=============================================================================
// MapRelatedStruct::sub_466D30 - AudioSourceParams
//=============================================================================
__int16 MapRelatedStruct::sub_466D30(AudioSourceParams a2)
{
  int v3;
  __int16 result;
  int v5;
  int v6;
  bool v7;
  int v8;
  bool v9;
  int v10;
  int v11;
  int v12;
  int v13;
  int v14;

  v13 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.z);
  v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.y);
  v3 = AudioSourceParams::sub_41F9D0(&a2);
  if ( !sub_466CF0( v3, v11, v13) )
    return 1;
  v14 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.z);
  v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.y);
  v5 = AudioSourceParams::sub_41F9D0(&a2);
  dword_662B90 = (_WORD *)sub_4653C0( v5, v12, v14);
  v6 = *((unsigned __int8 *)&unk_662DB0 + 12 * (*((unsigned __int8 *)dword_662B90 + 11) >> 2));
  dword_662BE0 = (_BYTE *)(12 * (*((unsigned __int8 *)dword_662B90 + 11) >> 2) + 6696368);
  switch ( v6 )
  {
    case 1:
      v8 = a2.type - 1;
      v7 = a2.type == 1;
      goto LABEL_5;
    case 2:
      v10 = a2.type - 1;
      v9 = a2.type == 1;
      goto LABEL_9;
    case 3:
      v10 = a2.type - 3;
      v9 = a2.type == 3;
LABEL_9:
      if ( v9 )
        goto LABEL_7;
      if ( v10 != 1 )
        goto LABEL_14;
LABEL_11:
      result = 3 - (LOBYTE(a2.field_10) != 0);
      break;
    case 4:
      v8 = a2.type - 3;
      v7 = a2.type == 3;
LABEL_5:
      if ( v7 )
        goto LABEL_11;
      if ( v8 == 1 )
LABEL_7:
        result = (LOBYTE(a2.field_10) != 0) + 2;
      else
LABEL_14:
        result = 0;
      break;
    default:
      goto LABEL_14;
  }
  return result;
}

//=============================================================================
// MapRelatedStruct::sub_463850
//=============================================================================
char MapRelatedStruct::sub_463850(AudioSourceParams a2)
{
  int v3;
  Map *Map;
  int v5;
  int v6;
  unsigned __int8 *v7;
  int v8;
  int v10;
  int v11;
  int v12;
  __int16 v13;
  char v14;
  unsigned __int8 v15;
  int v16;
  int v17;
  unsigned __int8 *i;
  __int16 v19;
  unsigned __int8 v20;
  int v21;

  v3 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.z);
  Map = getMap();
  v5 = v3;
  v21 = AudioSourceParams::sub_41F9D0(&a2);
  v6 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.y);
  v7 = (unsigned __int8 *)(Map->field_40008 + 4 * *(_DWORD *)Map->sub_42A830(v6, v21));
  v8 = *v7;
  a2.z = v8;
  if ( v5 >= v8 )
    return 0;
  v10 = v7[1];
  if ( v5 < v10 )
    v5 = v7[1];
  v11 = Map->field_4000C;
  v12 = v5 - v10;
  v13 = *(_WORD *)(v11 + 12 * *(_DWORD *)&v7[4 * (v5 - v10) + 4] + 8);
  if ( v13 )
  {
    if ( (v13 & 0x1000) == 0 )
    {
      v14 = *(_BYTE *)(v11 + 12 * *(_DWORD *)&v7[4 * (v5 - v10) + 4] + 11);
      v15 = v14 & 0xFC;
      if ( ((v14 & 0xFCu) < 0xB4 || v15 > 0xF4u) && (!v15 || v15 >= 0xB4u || (v14 & 3) == 0) )
        return 1;
    }
  }
  v16 = v12 + 1;
  v17 = a2.z - v10;
  if ( v12 + 1 < a2.z - v10 )
  {
    for ( i = &v7[4 * v16 + 4]; ; i += 4 )
    {
      v19 = *(_WORD *)(v11 + 12 * *(_DWORD *)i + 8);
      if ( v19 )
      {
        if ( (v19 & 0x1000) == 0 )
        {
          v20 = *(_BYTE *)(v11 + 12 * *(_DWORD *)i + 11) & 0xFC;
          if ( v20 < 0xB4u || v20 > 0xF4u )
            break;
        }
      }
      if ( ++v16 >= v17 )
        return 0;
    }
    return 1;
  }
  return 0;
}

//=============================================================================
// MapRelatedStruct::FindMaxZForLocation
//=============================================================================
int *MapRelatedStruct::FindMaxZForLocation(int *arg0, int *a2, S202 *pS202)
{
  int v5;
  _WORD *MaxZForTile;
  char v8;
  int *v9;
  int *v10;
  int v11;
  int a4;

  v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)pS202);
  v5 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)a2);
  MaxZForTile = FindMaxZForTile( v5, v11, &a4);
  dword_662B90 = MaxZForTile;
  if ( MaxZForTile )
  {
    v8 = *((_BYTE *)MaxZForTile + 11);
    if ( (v8 & 0xFC) != 0 && (v8 & 0xFCu) < 0xB4 && (v8 & 3) != 0 )
    {
      S202::sub_41F980((S202 *)&a4, a4);
      a4 = *v9;
      sub_466B70( a2, pS202);
      *arg0 = a4;
      return arg0;
    }
    else
    {
      S202::sub_41F980((S202 *)pS202, a4 + 1);
      *arg0 = *v10;
      return arg0;
    }
  }
  else
  {
    bitShiftLeft1((int)arg0, 0);
    return arg0;
  }
}

//=============================================================================
// MapRelatedStruct::sub_46A4D0
//=============================================================================
int MapRelatedStruct::sub_46A4D0()
{
  int result;
  FILE *Buffer_MOBJ;
  int *FirstElement;
  SpriteS1 *v5;
  int *MaxZForLocation;
  unsigned int v7;
  char v8[2];
  unsigned int v9;
  int a5;
  char v11[4];
  char v12[4];
  char v13[4];

  v9 = 0;
  result = field_344;
  Buffer_MOBJ = (FILE *)this->Buffer_MOBJ;
  if ( result )
  {
    do
    {
      FirstElement = (int *)sub_462ED0((SpriteS1 *)v11, (__int16 *)Buffer_MOBJ)->FirstElement;
      v5 = sub_462ED0((SpriteS1 *)v12, (__int16 *)&Buffer_MOBJ->_Placeholder + 1)->FirstElement;
      *(_WORD *)&a5 = *(_WORD *)&sub_462EF0((Ped *)v8, (SpriteS1 *)v8)->S200[0].A;
      MaxZForLocation = FindMaxZForLocation( (int *)v13, FirstElement, (S202 *)v5);
      SpawnObject((Object*)gObject, BYTE1(Buffer_MOBJ[1]._Placeholder), (int)FirstElement, (int)v5, *MaxZForLocation, a5);
      v7 = field_344;
      result = v9 + 1;
      Buffer_MOBJ = (FILE *)((char *)Buffer_MOBJ + 6);
      ++v9;
    }
    while ( v9 < v7 );
  }
  return result;
}

//=============================================================================
// MapRelatedStruct::sub_46A570
//=============================================================================
char MapRelatedStruct::sub_46A570(
        CarSystemManager *arg0,
        CarSystemManager *a3,
        CarSystemManager *a4,
        CarSystemManager *a5,
        CarSystemManager *a6,
        CarSystemManager *a2,
        int a8)
{
  _DWORD *v8;
  char v11;
  int v12;
  _WORD *v14;
  int v15;
  int v16;
  char v17;
  _BYTE *v18;
  _WORD *v19;
  int v20;
  int v21;
  S202 *v22;
  int v23;
  CarSystemManager *v24;
  S202 *v25;
  int v26;
  S16_02 **v27;
  CarSystemManager *v28;
  S202 *v29;
  int v30;
  CarSystemManager *v31;
  CarSystemManager *v32;
  S202 *v33;
  int v34;
  CarSystemManager *v35;
  S202 *v36;
  int v37;
  S16_02 **v38;
  S202 *v39;
  int v40;
  CarSystemManager *v41;
  S202 *v42;
  int v43;
  S202 *v44;
  int v45;
  S16_02 **v46;
  CarSystemManager *v47;
  S16_02 **v48;
  S202 *v49;
  int v50;
  S202 *v51;
  int v52;
  int v53;
  S202 *v54;
  int v55;
  S16_02 **v56;
  int v57;
  int v58;
  S202 *v59;
  int v60;
  CarSystemManager *v61;
  S202 *v62;
  int v63;
  S202 *v64;
  int v65;
  int v66;
  int v67;
  CarSystemManager *v68;
  S202 *v69;
  int v70;
  char *v71;
  S16_02 **v72;
  int v73;
  int v74;
  S202 *v75;
  int v76;
  CarSystemManager *v77;
  S202 *v78;
  int v79;
  S202 *v80;
  int v81;
  S202 *v82;
  int v83;
  char *v84;
  S16_02 **v85;
  int v86;
  S16_02 **v87;
  CarSystemManager *v88;
  S202 *v89;
  int v90;
  S202 *v91;
  int v92;
  int v93;
  S202 *v94;
  int v95;
  S16_02 **v96;
  int v97;
  CarSystemManager *v98;
  S202 *v99;
  int v100;
  S202 *v101;
  int v102;
  S202 *v103;
  int v104;
  int v105;
  int v106;
  CarSystemManager *v107;
  S202 *v108;
  int v109;
  char *v110;
  S16_02 **v111;
  int v112;
  CarSystemManager *v113;
  S202 *v114;
  int v115;
  S202 *v116;
  int v117;
  S202 v118;
  char a8a;

  v8 = dword_662BF0;
  *(_DWORD *)&v118.field_1C = (_DWORD)this;
  unk_662BF4 = a8;
  glob_a8 = a8;
  unk_662BD0 = a8;
  unk_662BBC = a8;
  if ( dword_662BF0 )
  {
    v11 = sub_469B00(
            (int *)dword_662BF0[5],
            (SpriteS1 *)dword_662BF0[6],
            (Player *)dword_662BF0[7]);
    v8 = dword_662BF0;
    if ( !v11 )
    {
      v118.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)(dword_662BF0 + 7));
      v118.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v8 + 1);
      v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)(v8 + 5));
      if ( !sub_466CF0( v12, (int)v118.self, (int)v118.carMgr) )
        return sub_466430( (int)arg0, (int)a3, (int)a4, (int)a5, a8);
    }
  }
  v14 = (_WORD*)sub_465410( (int)a6, (int)a2, a8);
  dword_662B90 = v14;
  if ( !v14 )
  {
    v14 = (_WORD *)&unk_662BC0;
    dword_662B90 = (_WORD *)&unk_662BC0;
  }
  v15 = *((unsigned __int8 *)v14 + 11) >> 2;
  v16 = 3 * v15;
  v17 = *((_BYTE *)&unk_662DB0 + 12 * v15);
  v18 = (_BYTE *)(4 * v16 + 6696368);
  dword_662BE0 = v18;
  if ( !v17 || v18[2] )
  {
    v19 = dword_662BE8;
    a8a = 0;
  }
  else
  {
    a8a = v17;
    switch ( v17 )
    {
      case 1:
        ++unk_662BF4;
        break;
      case 2:
        ++glob_a8;
        break;
      case 3:
        ++unk_662BBC;
        break;
      case 4:
        ++unk_662BD0;
        break;
      default:
        break;
    }
    v19 = (_WORD *)sub_4653C0( (int)a6, (int)a2, a8 + 1);
    dword_662BE8 = v19;
  }
  *((_WORD *)&v20 + 1) = *((_WORD *)&a2 + 1);
  v21 = *(_DWORD *)&word_662BEC;
  if ( (int)a4 >= (int)a2 )
    goto LABEL_36;
  if ( a8a == 1 )
  {
    if ( !v19 || ((unsigned __int16)word_662BEC & v19[2]) == 0 )
      goto LABEL_29;
    if ( !v8 )
      return 1;
    v118.carMgr = a2;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
    v118.self = v22;
    S202::sub_41F980((S202 *)&v118.self, (int)&a6->Index + 1);
    v118.field_0 = v23;
    S202::sub_41F980(&v118, (int)a6);
    if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
  }
  else
  {
    *(_WORD *)&v20 = dword_662B90[2];
    v24 = (CarSystemManager *)(*(_DWORD *)&word_662BEC & v20);
    if ( !(_WORD)v24 || *dword_662BE0 == 3 || *dword_662BE0 == 4 )
      goto LABEL_29;
    if ( !v8 )
      return 1;
    v118.carMgr = v24;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
    v118.self = v25;
    S202::sub_41F980((S202 *)&v118.self, (int)&a6->Index + 1);
    v118.field_0 = v26;
    S202::sub_41F980(&v118, (int)a6);
    if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
  }
  v8 = dword_662BF0;
  v21 = *(_DWORD *)&word_662BEC;
LABEL_29:
  v27 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410( (int)a6, (int)&a2[-1].field_0, unk_662BF4);
  dword_662B84 = (_WORD*)v27;
  if ( v27 )
  {
    if ( ((unsigned __int16)v21 & *((_WORD *)v27 + 3)) != 0 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = v28;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
      v118.self = v29;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->Index + 1);
      v118.field_0 = v30;
      S202::sub_41F980(&v118, (int)a6);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v27 = (S16_02 **)dword_662B84;
      v21 = *(_DWORD *)&word_662BEC;
    }
    dword_662BA4 = (_BYTE *)(12 * (*((unsigned __int8 *)v27 + 11) >> 2) + 6696368);
  }
  v19 = dword_662BE8;
LABEL_36:
  *((_WORD *)&v31 + 1) = HIWORD(a5);
  if ( (int)a5 <= (int)a2 )
    goto LABEL_55;
  if ( a8a == 2 )
  {
    if ( v19 )
    {
      *(_WORD *)&v31 = v19[3];
      v32 = (CarSystemManager *)(v21 & (unsigned int)v31);
      if ( (_WORD)v32 )
      {
        if ( !v8 )
          return 1;
        v118.carMgr = v32;
        S202::sub_41F980((S202 *)&v118.carMgr, (int)&a2->Index + 1);
        v118.self = v33;
        S202::sub_41F980((S202 *)&v118.self, (int)&a6->Index + 1);
        v118.field_0 = v34;
        S202::sub_41F980(&v118, (int)a6);
        if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
          return 1;
LABEL_48:
        v8 = dword_662BF0;
        v21 = *(_DWORD *)&word_662BEC;
      }
    }
  }
  else
  {
    *(_WORD *)&v31 = dword_662B90[3];
    v35 = (CarSystemManager *)(v21 & (unsigned int)v31);
    if ( (_WORD)v35 && *dword_662BE0 != 3 && *dword_662BE0 != 4 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = v35;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)&a2->Index + 1);
      v118.self = v36;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->Index + 1);
      v118.field_0 = v37;
      S202::sub_41F980(&v118, (int)a6);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      goto LABEL_48;
    }
  }
  v38 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410( (int)a6, (int)&a2->Index + 1, glob_a8);
  dword_662B8C = (_WORD*)v38;
  if ( v38 )
  {
    if ( ((unsigned __int16)v21 & (_WORD)v38[1]) != 0 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = v31;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)&a2->Index + 1);
      v118.self = v39;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->Index + 1);
      v118.field_0 = v40;
      S202::sub_41F980(&v118, (int)a6);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v38 = (S16_02 **)dword_662B8C;
      v21 = *(_DWORD *)&word_662BEC;
    }
    v31 = (CarSystemManager *)*((unsigned __int8 *)v38 + 11);
    dword_662BA0 = (_BYTE *)(12 * ((unsigned int)v31 >> 2) + 6696368);
  }
LABEL_55:
  if ( (int)arg0 >= (int)a6 )
    goto LABEL_132;
  if ( a8a == 3 )
  {
    if ( dword_662BE8 )
    {
      *(_WORD *)&v31 = *dword_662BE8;
      v41 = (CarSystemManager *)(v21 & (unsigned int)v31);
      if ( (_WORD)v41 )
      {
        if ( !v8 )
          return 1;
        v118.carMgr = v41;
        S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
        v118.self = v42;
        S202::sub_41F980((S202 *)&v118.self, (int)&a2->Index + 1);
        v118.field_0 = v43;
        S202::sub_41F980(&v118, (int)a2);
        if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
          return 1;
LABEL_67:
        v8 = dword_662BF0;
        v21 = *(_DWORD *)&word_662BEC;
      }
    }
  }
  else if ( ((unsigned __int16)v21 & *dword_662B90) != 0 && *dword_662BE0 != 1 && *dword_662BE0 != 2 )
  {
    if ( !v8 )
      return 1;
    v118.carMgr = (CarSystemManager *)dword_662B90;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
    v118.self = v44;
    S202::sub_41F980((S202 *)&v118.self, (int)&a2->Index + 1);
    v118.field_0 = v45;
    S202::sub_41F980(&v118, (int)a2);
    if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
    goto LABEL_67;
  }
  v46 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410( (int)&a6[-1].field_0, (int)a2, unk_662BBC);
  v48 = v46;
  unk_662B88 = (unsigned char)v46;
  if ( v46 )
  {
    if ( ((unsigned __int16)v21 & *((_WORD *)v46 + 1)) != 0 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = v47;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
      v118.self = v49;
      S202::sub_41F980((S202 *)&v118.self, (int)&a2->Index + 1);
      v118.field_0 = v50;
      S202::sub_41F980(&v118, (int)a2);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v48 = (S16_02 **)unk_662B88;
      v21 = *(_DWORD *)&word_662BEC;
    }
    dword_662BCC = (_BYTE *)(12 * (*((unsigned __int8 *)v48 + 11) >> 2) + 6696368);
  }
  if ( (int)a4 >= (int)a2 )
    goto LABEL_103;
  if ( dword_662B84
    && unk_662BBC <= unk_662BF4
    && ((unsigned __int16)v21 & *dword_662B84) != 0
    && *dword_662BA4 != 1
    && *dword_662BA4 != 2 )
  {
    if ( !v8 )
      return 1;
    v118.carMgr = (CarSystemManager *)dword_662BA4;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
    v118.self = v51;
    S202::sub_41F980((S202 *)&v118.self, (int)a2);
    v118.field_0 = v52;
    S202::sub_41F980(&v118, (int)&a2[-1].field_0);
    if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
    v8 = dword_662BF0;
    v48 = (S16_02 **)unk_662B88;
    v21 = *(_DWORD *)&word_662BEC;
  }
  if ( !v48 )
    goto LABEL_91;
  v53 = unk_662BF4;
  if ( unk_662BF4 <= unk_662BBC )
  {
    if ( ((unsigned __int16)v21 & (_WORD)v48[1]) != 0 && *dword_662BCC != 3 && *dword_662BCC != 4 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = (CarSystemManager *)dword_662BCC;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
      v118.self = v54;
      S202::sub_41F980((S202 *)&v118.self, (int)a6);
      v118.field_0 = v55;
      S202::sub_41F980(&v118, (int)&a6[-1].field_0);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v48 = (S16_02 **)unk_662B88;
      v21 = *(_DWORD *)&word_662BEC;
    }
LABEL_91:
    v53 = unk_662BF4;
    if ( unk_662BF4 <= unk_662BBC )
      v53 = unk_662BBC;
  }
  v56 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410(
          (int)&a6[-1].field_0,
          (int)&a2[-1].field_0,
          v53);
  unk_662C00 = (unsigned char)v56;
  if ( v56 )
  {
    *(_WORD *)&v57 = *((_WORD *)v56 + 1);
    v58 = v21 & v57;
    if ( (_WORD)v58 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = (CarSystemManager *)v58;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
      v118.self = v59;
      S202::sub_41F980((S202 *)&v118.self, (int)a2);
      v118.field_0 = v60;
      S202::sub_41F980(&v118, (int)&a2[-1].field_0);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v48 = (S16_02 **)unk_662B88;
      v56 = (S16_02 **)unk_662C00;
      v21 = *(_DWORD *)&word_662BEC;
    }
    if ( v56 )
    {
      *(_WORD *)&v58 = *((_WORD *)v56 + 3);
      v61 = (CarSystemManager *)(v21 & v58);
      if ( (_WORD)v61 )
      {
        if ( !v8 )
          return 1;
        v118.carMgr = v61;
        S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
        v118.self = v62;
        S202::sub_41F980((S202 *)&v118.self, (int)a6);
        v118.field_0 = v63;
        S202::sub_41F980(&v118, (int)&a6[-1].field_0);
        if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
          return 1;
        v8 = dword_662BF0;
        v48 = (S16_02 **)unk_662B88;
        v21 = *(_DWORD *)&word_662BEC;
      }
    }
  }
LABEL_103:
  if ( (int)a5 <= (int)a2 )
    goto LABEL_132;
  if ( dword_662B8C
    && unk_662BBC <= glob_a8
    && ((unsigned __int16)v21 & *dword_662B8C) != 0
    && *dword_662BA0 != 1
    && *dword_662BA0 != 2 )
  {
    if ( !v8 )
      return 1;
    v118.carMgr = (CarSystemManager *)unk_662BBC;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
    v118.self = v64;
    S202::sub_41F980((S202 *)&v118.self, (int)&a2->field_2);
    v118.field_0 = v65;
    S202::sub_41F980(&v118, (int)&a2->Index + 1);
    if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
    v8 = dword_662BF0;
    v48 = (S16_02 **)unk_662B88;
    v21 = *(_DWORD *)&word_662BEC;
  }
  if ( !v48 )
    goto LABEL_120;
  v66 = glob_a8;
  *((_WORD *)&v67 + 1) = unk_662BBE;
  if ( glob_a8 <= unk_662BBC )
  {
    *(_WORD *)&v67 = *((_WORD *)v48 + 3);
    v68 = (CarSystemManager *)(v21 & v67);
    if ( (_WORD)v68 && *dword_662BCC != 3 && *dword_662BCC != 4 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = v68;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)&a2->Index + 1);
      v118.self = v69;
      S202::sub_41F980((S202 *)&v118.self, (int)a6);
      v118.field_0 = v70;
      S202::sub_41F980(&v118, (int)&a6[-1].field_0);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v21 = *(_DWORD *)&word_662BEC;
    }
LABEL_120:
    v66 = glob_a8;
    if ( glob_a8 <= unk_662BBC )
      v66 = unk_662BBC;
  }
  v71 = (char *)&a2->Index + 1;
  v72 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410(
          (int)&a6[-1].field_0,
          (int)&a2->Index + 1,
          v66);
  unk_662BA8 = (unsigned char)v72;
  if ( v72 )
  {
    *(_WORD *)&v73 = *((_WORD *)v72 + 1);
    v74 = v21 & v73;
    if ( (_WORD)v74 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = (CarSystemManager *)v74;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a6);
      v118.self = v75;
      S202::sub_41F980((S202 *)&v118.self, (int)&a2->field_2);
      v118.field_0 = v76;
      S202::sub_41F980(&v118, (int)v71);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v8 = dword_662BF0;
      v72 = (S16_02 **)unk_662BA8;
      v21 = *(_DWORD *)&word_662BEC;
    }
    if ( v72 )
    {
      *(_WORD *)&v74 = *((_WORD *)v72 + 2);
      v77 = (CarSystemManager *)(v21 & v74);
      if ( (_WORD)v77 )
      {
        if ( !v8 )
          return 1;
        v118.carMgr = v77;
        S202::sub_41F980((S202 *)&v118.carMgr, (int)v71);
        v118.self = v78;
        S202::sub_41F980((S202 *)&v118.self, (int)a6);
        v118.field_0 = v79;
        S202::sub_41F980(&v118, (int)&a6[-1].field_0);
        if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
          return 1;
        v8 = dword_662BF0;
        v21 = *(_DWORD *)&word_662BEC;
      }
    }
  }
LABEL_132:
  if ( (int)a3 <= (int)a6 )
    return 0;
  if ( a8a == 4 )
  {
    if ( dword_662BE8 && ((unsigned __int16)v21 & dword_662BE8[1]) != 0 )
    {
      if ( !v8 )
        return 1;
      v118.carMgr = a6;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)&a6->Index + 1);
      v118.self = v80;
      S202::sub_41F980((S202 *)&v118.self, (int)&a2->Index + 1);
      v118.field_0 = v81;
      S202::sub_41F980(&v118, (int)a2);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      goto LABEL_144;
    }
  }
  else if ( ((unsigned __int16)v21 & dword_662B90[1]) != 0 && *dword_662BE0 != 1 && *dword_662BE0 != 2 )
  {
    if ( !v8 )
      return 1;
    v118.carMgr = a6;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)&a6->Index + 1);
    v118.self = v82;
    S202::sub_41F980((S202 *)&v118.self, (int)&a2->Index + 1);
    v118.field_0 = v83;
    S202::sub_41F980(&v118, (int)a2);
    if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
LABEL_144:
    v21 = *(_DWORD *)&word_662BEC;
  }
  v84 = (char *)&a6->Index + 1;
  v85 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410( (int)&a6->Index + 1, (int)a2, unk_662BD0);
  v87 = v85;
  unk_662C04 = (unsigned char)v85;
  if ( v85 )
  {
    *(_WORD *)&v86 = *(_WORD *)v85;
    v88 = (CarSystemManager *)(v21 & v86);
    if ( (_WORD)v88 )
    {
      if ( !dword_662BF0 )
        return 1;
      v118.carMgr = v88;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)v84);
      v118.self = v89;
      S202::sub_41F980((S202 *)&v118.self, (int)&a2->Index + 1);
      v118.field_0 = v90;
      S202::sub_41F980(&v118, (int)a2);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v87 = (S16_02 **)unk_662C04;
      v21 = *(_DWORD *)&word_662BEC;
    }
    dword_662BDC = (_BYTE *)(12 * (*((unsigned __int8 *)v87 + 11) >> 2) + 6696368);
  }
  if ( (int)a4 >= (int)a2 )
    goto LABEL_180;
  if ( dword_662B84
    && unk_662BD0 <= unk_662BF4
    && ((unsigned __int16)v21 & dword_662B84[1]) != 0
    && *dword_662BA4 != 1
    && *dword_662BA4 != 2 )
  {
    if ( !dword_662BF0 )
      return 1;
    v118.carMgr = (CarSystemManager *)dword_662BA4;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)v84);
    v118.self = v91;
    S202::sub_41F980((S202 *)&v118.self, (int)a2);
    v118.field_0 = v92;
    S202::sub_41F980(&v118, (int)&a2[-1].field_0);
    if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
    v87 = (S16_02 **)unk_662C04;
    v21 = *(_DWORD *)&word_662BEC;
  }
  if ( !v87 )
    goto LABEL_168;
  v93 = unk_662BF4;
  if ( unk_662BF4 <= unk_662BD0 )
  {
    if ( ((unsigned __int16)v21 & (_WORD)v87[1]) != 0 && *dword_662BDC != 3 && *dword_662BDC != 4 )
    {
      if ( !dword_662BF0 )
        return 1;
      v118.carMgr = (CarSystemManager *)unk_662BD0;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
      v118.self = v94;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->field_2);
      v118.field_0 = v95;
      S202::sub_41F980(&v118, (int)v84);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v87 = (S16_02 **)unk_662C04;
      v21 = *(_DWORD *)&word_662BEC;
    }
LABEL_168:
    v93 = unk_662BF4;
    if ( unk_662BF4 <= unk_662BD0 )
      v93 = unk_662BD0;
  }
  v96 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410( (int)v84, (int)&a2[-1].field_0, v93);
  unk_662BE4 = (unsigned char)v96;
  if ( v96 )
  {
    *(_WORD *)&v97 = *(_WORD *)v96;
    v98 = (CarSystemManager *)(v21 & v97);
    if ( (_WORD)v98 )
    {
      if ( !dword_662BF0 )
        return 1;
      v118.carMgr = v98;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)v84);
      v118.self = v99;
      S202::sub_41F980((S202 *)&v118.self, (int)a2);
      v118.field_0 = v100;
      S202::sub_41F980(&v118, (int)&a2[-1].field_0);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v87 = (S16_02 **)unk_662C04;
      v96 = (S16_02 **)unk_662BE4;
      v21 = *(_DWORD *)&word_662BEC;
    }
    if ( v96 && ((unsigned __int16)v21 & *((_WORD *)v96 + 3)) != 0 )
    {
      if ( !dword_662BF0 )
        return 1;
      v118.carMgr = v98;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)a2);
      v118.self = v101;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->field_2);
      v118.field_0 = v102;
      S202::sub_41F980(&v118, (int)v84);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v87 = (S16_02 **)unk_662C04;
      v21 = *(_DWORD *)&word_662BEC;
    }
  }
LABEL_180:
  if ( (int)a5 <= (int)a2 )
    return 0;
  if ( dword_662B8C
    && unk_662BD0 <= glob_a8
    && ((unsigned __int16)v21 & dword_662B8C[1]) != 0
    && *dword_662BA0 != 1
    && *dword_662BA0 != 2 )
  {
    if ( !dword_662BF0 )
      return 1;
    v118.carMgr = (CarSystemManager *)unk_662BD0;
    S202::sub_41F980((S202 *)&v118.carMgr, (int)v84);
    v118.self = v103;
    S202::sub_41F980((S202 *)&v118.self, (int)&a2->field_2);
    v118.field_0 = v104;
    S202::sub_41F980(&v118, (int)&a2->Index + 1);
    if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
      return 1;
    v87 = (S16_02 **)unk_662C04;
    v21 = *(_DWORD *)&word_662BEC;
  }
  if ( v87 )
  {
    v105 = glob_a8;
    *((_WORD *)&v106 + 1) = unk_662BD2;
    if ( glob_a8 > unk_662BD0 )
      goto LABEL_199;
    *(_WORD *)&v106 = *((_WORD *)v87 + 3);
    v107 = (CarSystemManager *)(v21 & v106);
    if ( (_WORD)v107 && *dword_662BDC != 3 && *dword_662BDC != 4 )
    {
      if ( !dword_662BF0 )
        return 1;
      v118.carMgr = v107;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)&a2->Index + 1);
      v118.self = v108;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->field_2);
      v118.field_0 = v109;
      S202::sub_41F980(&v118, (int)v84);
      if ( sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v21 = *(_DWORD *)&word_662BEC;
    }
  }
  v105 = glob_a8;
  if ( glob_a8 <= unk_662BD0 )
    v105 = unk_662BD0;
LABEL_199:
  v110 = (char *)&a2->Index + 1;
  v111 = (*(MapRelatedStruct **)&v118.field_1C)->sub_465410( (int)v84, (int)&a2->Index + 1, v105);
  unk_662BB0 = (unsigned char)v111;
  if ( v111 )
  {
    *(_WORD *)&v112 = *(_WORD *)v111;
    v113 = (CarSystemManager *)(v21 & v112);
    if ( (_WORD)v113 )
    {
      if ( !dword_662BF0 )
        return 1;
      v118.carMgr = v113;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)v84);
      v118.self = v114;
      S202::sub_41F980((S202 *)&v118.self, (int)&a2->field_2);
      v118.field_0 = v115;
      S202::sub_41F980(&v118, (int)v110);
      if ( sub_4BB910(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 1;
      v111 = (S16_02 **)unk_662BB0;
      *(_WORD *)&v21 = word_662BEC;
    }
    if ( !v111 )
      return 0;
    if ( ((unsigned __int16)v21 & (_WORD)v111[1]) == 0 )
      return 0;
    if ( dword_662BF0 )
    {
      v118.carMgr = v113;
      S202::sub_41F980((S202 *)&v118.carMgr, (int)v110);
      v118.self = v116;
      S202::sub_41F980((S202 *)&v118.self, (int)&a6->field_2);
      v118.field_0 = v117;
      S202::sub_41F980(&v118, (int)v84);
      if ( !sub_4BB860(dword_662BF0, v118.field_0, (int)v118.self, (int)v118.carMgr) )
        return 0;
    }
    return 1;
  }
  return 0;
}

//=============================================================================
// MapRelatedStruct::sub_46B440
//=============================================================================
char MapRelatedStruct::sub_46B440(
        CarSystemManager *a6,
        CarSystemManager *a2,
        int a8,
        _DWORD *a5,
        __int16 arg10)
{
  CarSystemManager* arg0_csm = (CarSystemManager*)arg0;
  dword_662BF0 = a5;
  word_662BEC = arg10;
  if ( (char *)dword_662BF8 - (char *)arg0_csm >= 3
    || (int)a6 > (int)((char *)&arg0_csm->Index + 1)
    || (int)a6 < (int)&dword_662BF8[-1].field_0 )
  {
    if ( sub_46A570(
           (CarSystemManager *)((char *)a6 - 1),
           (CarSystemManager *)((char *)&a6->Index + 1),
           dword_662BAC,
           (CarSystemManager*)glob_a5,
           a6,
           a2,
           a8) )
    {
      return 1;
    }
    if ( dword_662BF8 == (CarSystemManager *)&a6->field_2 )
      return sub_46A570(
               (CarSystemManager *)((char *)dword_662BF8 - 1),
               dword_662BF8,
               dword_662BAC,
               (CarSystemManager*)glob_a5,
               (CarSystemManager *)((char *)dword_662BF8 - 1),
               a2,
               unk_662BD0);
    else
      return sub_46A570(
               arg0_csm,
               (CarSystemManager *)((char *)&arg0_csm->Index + 1),
               dword_662BAC,
               (CarSystemManager*)glob_a5,
               (CarSystemManager *)((char *)&arg0_csm->Index + 1),
               a2,
               unk_662BBC);
  }
  else
  {
    if ( (char *)glob_a5 - (char *)dword_662BAC < 3
      && (int)a2 <= (int)((char *)&dword_662BAC->Index + 1)
      && (int)a2 >= (int)&((CarSystemManager*)glob_a5)[-1].field_0 )
    {
      return sub_46A570( arg0_csm, dword_662BF8, dword_662BAC, (CarSystemManager*)glob_a5, a6, a2, a8);
    }
    if ( sub_46A570(
           arg0_csm,
           dword_662BF8,
           (CarSystemManager *)((char *)a2 - 1),
           (CarSystemManager *)((char *)&a2->Index + 1),
           a6,
           a2,
           a8) )
    {
      return 1;
    }
    if ( (CarSystemManager*)glob_a5 == (CarSystemManager *)&a2->field_2 )
      return sub_46A570(
               arg0_csm,
               dword_662BF8,
               (CarSystemManager *)((char *)glob_a5 - 1),
               (CarSystemManager*)glob_a5,
               a6,
               (CarSystemManager *)((char *)glob_a5 - 1),
               a8);
    else
      return sub_46A570(
               arg0_csm,
               dword_662BF8,
               dword_662BAC,
               (CarSystemManager *)((char *)&dword_662BAC->Index + 1),
               a6,
               (CarSystemManager *)((char *)&dword_662BAC->Index + 1),
               unk_662BF4);
  }
}

//=============================================================================
// MapRelatedStruct::sub_48A350
//=============================================================================
bool MapRelatedStruct::sub_48A350(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4)
{
  int v4;

  v4 = sub_42A850( a2, a3, a4);
  return v4 && (*(_BYTE *)(v4 + 11) & 3) != 0;
}

//=============================================================================
// MapRelatedStruct::sub_492130
//=============================================================================
void MapRelatedStruct::sub_492130()
{
  field_36E = 0;
}

//=============================================================================
// MapRelatedStruct::sub_492140
//=============================================================================
bool MapRelatedStruct::sub_492140(int a2, int a3, int a4)
{
  int v4;

  v4 = sub_4653C0( a2, a3, a4);
  return v4 && *(_BYTE *)(v4 + 10);
}

//=============================================================================
// MapRelatedStruct::sub_49EBE0
//=============================================================================
char MapRelatedStruct::sub_49EBE0(int a2, int a3, int a4, _BYTE *a5, _BYTE *a6)
{
  int v6;
  int v7;
  char *v9;

  v6 = sub_4653C0( a2, a3, a4);
  v7 = v6;
  if ( !v6 )
    return 5;
  if ( Style::sub_49E540(gStyle, *(_WORD *)(v6 + 8) & 0x3FF) )
    return 7;
  if ( (*(_BYTE *)(v7 + 11) & 3) == 0 )
    return 5;
  if ( Style::sub_49E570(gStyle, *(_WORD *)(v7 + 8) & 0x3FF) )
    return 9;
  v9 = (char *)(12 * (*(unsigned __int8 *)(v7 + 11) >> 2) + 6696368);
  *a5 = *((_BYTE *)&unk_662DB1 + 12 * (*(unsigned __int8 *)(v7 + 11) >> 2));
  *a6 = v9[2];
  return *v9;
}

//=============================================================================
// MapRelatedStruct::sub_4B9F40
//=============================================================================
bool MapRelatedStruct::sub_4B9F40(int a2, int a3, int a4)
{
  int v4;

  v4 = sub_4653C0( a2, a3, a4);
  return v4 && Style::sub_49E540(gStyle, *(_WORD *)(v4 + 8) & 0x3FF);
}

//=============================================================================
// MapRelatedStruct::sub_464EE0
//=============================================================================
char *MapRelatedStruct::sub_464EE0(unsigned __int8 arg0, unsigned __int8 a2, char a4)
{
  int v4;
  int v6;
  char *v7;
  char *v8;
  int v10;
  int v11;
  int v12;
  int v13;
  void *Car;
  char v15[4];

  v4 = 0;
  v8 = 0;
  if ( !Buffer_ZONE )
    return 0;
  v6 = *(unsigned __int16 *)count;
  if ( (_WORD)v6 )
  {
    while ( 1 )
    {
      v7 = sub_462E40( v4);
      if ( *v7 == a4 )
      {
        sub_40CE30((S202 *)&v10, a2);
        sub_40CE30((S202 *)&v11, arg0);
        bitShiftLeft1((int)&v12, (unsigned __int8)v7[2] + ((unsigned __int8)v7[4] >> 1));
        bitShiftLeft1((int)&v13, (unsigned __int8)v7[1] + ((unsigned __int8)v7[3] >> 1));
        Car = (void*)(unsigned int)sub_42A6B0(&v13, v15)->Car;
        if ( sub_4037E0(&Car) )
          v8 = v7;
      }
      if ( ++v4 >= v6 )
        break;
    }
  }
  return v8;
}

//=============================================================================
// MapRelatedStruct::sub_464330 - Zone indexing helper
//=============================================================================
void MapRelatedStruct::sub_464330()
{
  unsigned __int16 v2;
  int v3;
  int v4;
  char *v5;
  char v6;
  unsigned __int16 v7;
  char v8;
  char *v9;
  void *Buffer;
  int v11;
  int v12;
  int v13;
  _WORD *result;
  int v15;
  int v16;
  unsigned __int16 v17;
  unsigned __int16 v18;

  v2 = 0;
  v18 = 0;
  if ( count )
  {
    v17 = *(_WORD *)field_330;
    if ( v17 )
      field_334 = (_WORD *)createBuffer(*(unsigned __int16 *)field_330);
  }
  else
  {
    v17 = 0;
  }
  *(_WORD *)&v3 = 0;
  v16 = 0;
  if ( v17 )
  {
    v15 = 0;
    while ( 1 )
    {
      v5 = sub_462E40( v3);
      v6 = *v5;
      if ( *v5 != 10 && v6 != 1 && v6 != 15 )
      {
        *(_BYTE *)(v15 + (int)field_334) = 0;
        goto LABEL_18;
      }
      v7 = 0;
      if ( !(_WORD)v4 )
      {
LABEL_17:
        *(_BYTE *)(v15 + (int)field_334) = ++v18;
        goto LABEL_18;
      }
      while ( 1 )
      {
        v8 = *(_BYTE *)(v7 + (int)field_334);
        if ( !v8 )
          goto LABEL_16;
        v9 = sub_462E40( v7);
        if ( v5[5] != v9[5] )
          goto LABEL_16;
        if ( !strncmp(v5 + 6, v9 + 6, (unsigned __int8)v5[5]) )
          break;
        v4 = v16;
LABEL_16:
        if ( ++v7 >= (unsigned __int16)v4 )
          goto LABEL_17;
      }
      *(_BYTE *)(v15 + (int)field_334) = v8;
      v4 = v16;
LABEL_18:
      v3 = v4 + 1;
      v16 = v3;
      ++v15;
      if ( (unsigned __int16)v3 >= v17 )
      {
        v2 = v18;
        break;
      }
    }
  }
  Buffer = createBuffer(22 * (v2 + 1));
  v11 = 0;
  Buffer_MOBJ = Buffer;
  v12 = (unsigned __int16)(v2 + 1);
  do
  {
    v13 = (int)Buffer_MOBJ;
    *(_WORD *)(v13 + v11) = 500;
    result = (_WORD *)(v11 + v13);
    v11 += 22;
    --v12;
    result[1] = 300;
    result[2] = 300;
    result[3] = 100;
    result[4] = 0;
    result[5] = 500;
    result[6] = 50;
    result[7] = 40;
    result[8] = 10;
    result[9] = 200;
    result[10] = 40;
  }
  while ( v12 );
}


// 0x00420420
char MapRelatedStruct::sub_420420(int a2, int a3, int a4) {
    int v4 = sub_4653C0(a2, a3, a4);
    if (v4)
        return *(_BYTE*)(v4 + 11) & 3;
    else
        return 0;
}

// 0x0042A850
int MapRelatedStruct::sub_42A850(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4) {
    Map* Map = getMap();
    int v5 = *(_DWORD*)getMap()->sub_42A830( a3, a2);
    int v6 = Map->field_40008;
    unsigned __int8 v7 = *(_BYTE*)(v6 + 4 * v5);
    int v8 = v6 + 4 * v5;
    if (a4 >= v7 || a4 < *(_BYTE*)(v8 + 1))
        return 0;
    else
        return Map->field_4000C + 12 * *(_DWORD*)(v8 + 4 * (a4 - *(unsigned __int8*)(v8 + 1)) + 4);
}

// 0x0042A8C0
bool MapRelatedStruct::sub_42A8C0(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4) {
    int v4 = sub_42A850(a2, a3, a4);
    return v4 && (*(_BYTE*)(v4 + 11) & 3) == 1;
}

// 0x00433430
bool MapRelatedStruct::sub_433430(int a2, int a3, int a4) {
    int v4 = sub_4653C0(a2, a3, a4);
    bool result = 0;
    if (v4) {
        unsigned int v5 = *(_BYTE*)(v4 + 11) & 0xFC;
        if (v5 >= 0xB4 && v5 <= 0xD0)
            return 1;
    }
    return result;
}

// 0x00433470
bool MapRelatedStruct::sub_433470(unsigned __int8 a2, char a3, unsigned __int8 a4) {
    int v4 = sub_42A850(a2, a3 - 1, a4);
    return v4 && (*(_BYTE*)(v4 + 11) & 3) == 1;
}

// 0x004334A0
bool MapRelatedStruct::sub_4334A0(char a2, unsigned __int8 a3, unsigned __int8 a4) {
    int v4 = sub_42A850(a2 + 1, a3, a4);
    return v4 && (*(_BYTE*)(v4 + 11) & 3) == 1;
}

// 0x004334D0
bool MapRelatedStruct::sub_4334D0(unsigned __int8 a2, char a3, unsigned __int8 a4) {
    int v4 = sub_42A850(a2, a3 + 1, a4);
    return v4 && (*(_BYTE*)(v4 + 11) & 3) == 1;
}

// 0x00433500
bool MapRelatedStruct::sub_433500(char a2, unsigned __int8 a3, unsigned __int8 a4) {
    int v4 = sub_42A850(a2 - 1, a3, a4);
    return v4 && (*(_BYTE*)(v4 + 11) & 3) == 1;
}

// 0x00433530
bool MapRelatedStruct::sub_433530(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4) {
    int v4 = sub_42A850(a2, a3, a4);
    return v4 && (*(_BYTE*)(v4 + 11) & 3) == 2;
}

// 0x00462C60
int MapRelatedStruct::sub_462C60() {
    unsigned __int8 v2;
    if (Buffer_ZONE && (v2 = *(_BYTE*)(field_364 + field_330)) != 0)
        return (int)(field_334 + 22 * v2);
    else
        return 0;
}

// 0x00462CB0
int MapRelatedStruct::sub_462CB0(unsigned __int16 a2) {
    return (int)(field_334 + 22 * *(unsigned __int8*)(field_330 + a2));
}

// 0x00462CE0
_WORD* MapRelatedStruct::sub_462CE0(unsigned __int16 a2, __int16 a3) {
    _WORD* result = (_WORD*)sub_462CB0(a2);
    *result = a3;
    return result;
}

// 0x00462D00
int MapRelatedStruct::sub_462D00(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 2) = a3;
    return result;
}

// 0x00462D20
int MapRelatedStruct::sub_462D20(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 4) = a3;
    return result;
}

// 0x00462D40
int MapRelatedStruct::sub_462D40(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 6) = a3;
    return result;
}

// 0x00462D60
int MapRelatedStruct::sub_462D60(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 8) = a3;
    return result;
}

// 0x00462D80
int MapRelatedStruct::sub_462D80(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 10) = a3;
    return result;
}

// 0x00462DA0
int MapRelatedStruct::sub_462DA0(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 12) = a3;
    return result;
}

// 0x00462DC0
int MapRelatedStruct::sub_462DC0(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 14) = a3;
    return result;
}

// 0x00462DE0
int MapRelatedStruct::sub_462DE0(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 16) = a3;
    return result;
}

// 0x00462E00
int MapRelatedStruct::sub_462E00(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 18) = a3;
    return result;
}

// 0x00462E20
int MapRelatedStruct::sub_462E20(unsigned __int16 a2, __int16 a3) {
    int result = sub_462CB0(a2);
    *(_WORD*)(result + 20) = a3;
    return result;
}

// 0x00462E40
char* MapRelatedStruct::sub_462E40(unsigned __int16 a2) {
    return *(char**)(count + 4 * a2 + 4);
}

// 0x00462E80
char MapRelatedStruct::sub_462E80() {
    char result = field_36E;
    field_36E = 0;
    return result;
}

// 0x00462F50
char MapRelatedStruct::sub_462F50(int a2, int a3) {
    char result;
    switch (a2) {
    case 1:
        result = (*(_BYTE*)(a3 + 10) & 4) != 0;
        break;
    case 2:
        result = (*(_BYTE*)(a3 + 10) & 8) != 0;
        break;
    case 3:
        result = (*(_BYTE*)(a3 + 10) & 2) != 0;
        break;
    case 4:
        result = *(_BYTE*)(a3 + 10) & 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

// 0x004632E0
char MapRelatedStruct::sub_4632E0(int a1, int a2, char a3) {
    char result;
    char a3a;
    switch (a2) {
    case 1:
        if (!a3)
            return JuncIds::sub_40C6D0(gJuncIds, a1, 1, 2);
        return JuncIds::sub_40C6D0(gJuncIds, a1, 1, 1);
    case 2:
        if (a3)
            return JuncIds::sub_40C6D0(gJuncIds, a1, 1, 2);
        else
            return JuncIds::sub_40C6D0(gJuncIds, a1, 1, 1);
    case 3:
        if (a3)
            goto LABEL_9;
        result = JuncIds::sub_40C6D0(gJuncIds, a1, 1, 3);
        break;
    case 4:
        a3a = 3;
        if (!a3)
LABEL_9:
            a3a = 4;
        result = JuncIds::sub_40C6D0(gJuncIds, a1, 1, a3a);
        break;
    default:
        result = a3;
        break;
    }
    return result;
}

// 0x004633A0
int MapRelatedStruct::sub_4633A0(int a1, char a2) {
    if (JuncIds::sub_40C6D0(gJuncIds, a1, 3, 4))
        return 4 - (a2 != 0);
    if (JuncIds::sub_40C6D0(gJuncIds, a1, 3, 2))
        return (a2 != 0) + 1;
    if (JuncIds::sub_40C6D0(gJuncIds, a1, 3, 3))
        return (a2 != 0) + 3;
    if (JuncIds::sub_40C6D0(gJuncIds, a1, 3, 1))
        return 2 - (a2 != 0);
    return 0;
}

// 0x00463570
int MapRelatedStruct::sub_463570(int a2, int a3, _DWORD* a4) {
    Map* Map = getMap();
    int v5 = *(_DWORD*)getMap()->sub_42A830( a3, a2);
    int v6 = Map->field_40008;
    int v7 = *(unsigned __int8*)(v6 + 4 * v5 + 1);
    unsigned __int8* v8 = (unsigned __int8*)(v6 + 4 * v5);
    int v9 = v7;
    int v10 = *v8 - v7 - 1;
    if (v10 < 0)
        return 0;
    int result;
    int v11 = Map->field_4000C;
    for (unsigned __int8* i = &v8[4 * v10 + 4]; ; i -= 4) {
        result = v11 + 12 * *(_DWORD*)i;
        char v14 = *(_BYTE*)(result + 11) & 3;
        dword_662B90 = (_WORD*)result;
        if (v14 == 3 && (*(_BYTE*)(result + 10) & 0xF) != 0)
            break;
        if (--v10 < 0)
            return 0;
    }
    *a4 = v10 + v9;
    return result;
}

// 0x004635F0
int MapRelatedStruct::sub_4635F0(int a2, int a3, int* a4) {
    Map* Map = getMap();
    int v5 = *(_DWORD*)getMap()->sub_42A830( a3, a2);
    int v6 = Map->field_40008;
    int v7 = *(unsigned __int8*)(v6 + 4 * v5 + 1);
    unsigned __int8* v8 = (unsigned __int8*)(v6 + 4 * v5);
    int v9 = v7;
    int v10 = *a4;
    if (*a4 < v7)
        return 0;
    int v12 = *v8;
    int v13;
    if (v10 < v12)
        v13 = v10 - v9;
    else
        v13 = v12 - v9 - 1;
    if (v13 < 0)
        return 0;
    int result;
    int v14 = Map->field_4000C;
    for (unsigned __int8* i = &v8[4 * v13 + 4]; ; i -= 4) {
        result = v14 + 12 * *(_DWORD*)i;
        char v16 = *(_BYTE*)(result + 11) & 3;
        dword_662B90 = (_WORD*)result;
        if (v16 == 3 && (*(_BYTE*)(result + 10) & 0xF) != 0)
            break;
        if (--v13 < 0)
            return 0;
    }
    *a4 = v13 + v9;
    return result;
}

// 0x00463A00
int MapRelatedStruct::sub_463A00(_DWORD* a2) {
    int result = field_354;
    field_354 = result + 1;
    _DWORD* v3 = (_DWORD*)(getMap()->field_4000C + 12 * result);
    *v3 = *a2;
    v3[1] = a2[1];
    v3[2] = a2[2];
    return result;
}

// 0x00463A40
int MapRelatedStruct::sub_463A40(unsigned int a2) {
    if (a2 >= field_34C)
        return a2;
    int result = field_354;
    field_354 = result + 1;
    int v3 = getMap()->field_4000C;
    _DWORD* v4 = (_DWORD*)(v3 + 12 * a2);
    _DWORD* v5 = (_DWORD*)(v3 + 12 * result);
    *v5 = *v4;
    v5[1] = v4[1];
    v5[2] = v4[2];
    return result;
}

// 0x00463A90
unsigned int MapRelatedStruct::sub_463A90(unsigned int a2) {
    unsigned int result = a2;
    if (a2 < field_358) {
        Map* Map = getMap();
        unsigned __int8* v5 = (unsigned __int8*)(getMap()->field_40008 + 4 * a2);
        result = field_360;
        int v6 = *v5 - v5[1] + 1;
        field_360 = result + v6;
        memcpy((void*)(Map->field_40008 + 4 * result), v5, 4 * v6);
    }
    return result;
}

// 0x00463AE0
unsigned int MapRelatedStruct::sub_463AE0(unsigned int a2, int a3) {
    int v4 = getMap()->field_40008;
    unsigned __int8* v5 = (unsigned __int8*)(v4 + 4 * a2);
    int v6 = *v5;
    if (a3 < v6 && a3 >= v5[1])
        return sub_463A90(a2);
    int v17 = field_360;
    unsigned __int8* v8 = (unsigned __int8*)(v4 + 4 * v17);
    if (a3 < v6) {
        *v8 = *v5;
        v8[1] = a3;
        int v13 = v5[1] - (unsigned __int8)a3;
        if (v13 > 0)
            memset(v8 + 4, 0, 4 * v13);
        int v14 = 0;
        if (*v5 - v5[1] > 0) {
            _DWORD* v15 = (_DWORD*)(v5 + 4);
            unsigned __int8* v16 = &v8[4 * v13 + 4];
            do {
                *(_DWORD*)v16 = *v15;
                ++v14;
                ++v15;
                v16 += 4;
            } while (v14 < *v5 - v5[1]);
        }
    } else {
        *v8 = a3 + 1;
        v8[1] = v5[1];
        int v9 = 0;
        if (*v5 - v5[1] > 0) {
            _DWORD* v10 = (_DWORD*)(v8 + 4);
            do {
                *v10 = *(_DWORD*)((char*)v10 + (v5 - v8));
                ++v9;
                ++v10;
            } while (v9 < *v5 - v5[1]);
        }
        int v11 = *v5 - v5[1];
        if (v11 < *v8 - v8[1]) {
            unsigned __int8* v12 = &v8[4 * v11 + 4];
            do {
                *(_DWORD*)v12 = 0;
                ++v11;
                v12 += 4;
            } while (v11 < *v8 - v8[1]);
        }
    }
    field_360 += *v8 - v8[1] + 1;
    return v17;
}

// 0x00463C30
unsigned int MapRelatedStruct::sub_463C30(unsigned int a2, int a3, char a4) {
    int v4 = getMap()->field_40008;
    unsigned int result = a2;
    unsigned __int8 v7 = *(_BYTE*)(v4 + 4 * a2);
    unsigned __int8* v8 = (unsigned __int8*)(v4 + 4 * a2);
    if (a3 >= v7)
        return -1;
    int a2a = v8[1];
    if (a3 < a2a)
        return -1;
    if (result >= field_358) {
        if (a4) {
            int v36 = a3 - a2a;
            if (v36 < v7 - a2a - 1) {
                unsigned __int8* v37 = &v8[4 * v36 + 4];
                do {
                    *(_DWORD*)v37 = *((_DWORD*)v37 + 1);
                    ++v36;
                    v37 += 4;
                } while (v36 < *v8 - v8[1] - 1);
            }
            --*v8;
        } else if (a3 == v7 - 1) {
            *v8 = v7 - 1;
        } else {
            *(_DWORD*)&v8[4 * (a3 - a2a) + 4] = 0;
        }
    } else {
        int v9 = v7 - 1;
        unsigned int a3a = field_360;
        unsigned __int8* v10 = (unsigned __int8*)(v4 + 4 * a3a);
        if (a4) {
            *v10 = v7 - 1;
            unsigned __int8 v11 = v8[1];
            v10[1] = v11;
            if (a3 == v9) {
                int v12 = 0;
                if (*v10 - v11 > 0) {
                    _DWORD* v13 = (_DWORD*)(v10 + 4);
                    int v14 = v8 - v10;
                    do {
                        *v13 = *(_DWORD*)((char*)v13 + v14);
                        ++v12;
                        ++v13;
                    } while (v12 < *v10 - v10[1]);
                }
            } else {
                int v15 = 0;
                if (a3 - v11 > 0) {
                    _DWORD* v16 = (_DWORD*)(v10 + 4);
                    for (int i = v8 - v10; ; i = v8 - v10) {
                        *v16 = *(_DWORD*)((char*)v16 + i);
                        ++v15;
                        ++v16;
                        if (v15 >= a3 - v10[1])
                            break;
                    }
                }
                int v18 = v10[1];
                int v19 = a3 - v18;
                if (v19 < *v10 - v18) {
                    unsigned __int8* v20 = &v10[4 * v19 + 4];
                    unsigned __int8* v21 = &v8[4 * v19 + 8];
                    do {
                        *(_DWORD*)v20 = *(_DWORD*)v21;
                        ++v19;
                        v21 += 4;
                        v20 += 4;
                    } while (v19 < *v10 - v10[1]);
                }
            }
        } else if (a3 == v9) {
            *v10 = v7 - 1;
            unsigned __int8 v22 = v8[1];
            int v23 = *v10;
            v10[1] = v22;
            int v24 = 0;
            if (v23 - v22 > 0) {
                _DWORD* v25 = (_DWORD*)(v10 + 4);
                int v26 = v8 - v10;
                do {
                    *v25 = *(_DWORD*)((char*)v25 + v26);
                    ++v24;
                    ++v25;
                } while (v24 < *v10 - v10[1]);
            }
        } else if (a3 == a2a) {
            *v10 = v7 - 1;
            int v27 = *v10;
            unsigned __int8 v28 = v8[1] + 1;
            v10[1] = v28;
            int v29 = 0;
            if (v27 - v28 > 0) {
                _DWORD* v30 = (_DWORD*)(v10 + 4);
                _DWORD* v31 = (_DWORD*)(v8 + 8);
                do {
                    *v30 = *v31;
                    ++v29;
                    ++v31;
                    ++v30;
                } while (v29 < *v10 - v10[1]);
            }
        } else {
            *v10 = v7;
            unsigned __int8 v32 = v8[1];
            v10[1] = v32;
            int v33 = 0;
            if (*v10 - v32 > 0) {
                _DWORD* v34 = (_DWORD*)(v10 + 4);
                for (int j = v8 - v10; ; j = v8 - v10) {
                    *v34 = *(_DWORD*)((char*)v34 + j);
                    ++v33;
                    ++v34;
                    if (v33 >= *v10 - v10[1])
                        break;
                }
            }
            *(_DWORD*)&v10[4 * (a3 - v8[1]) + 4] = 0;
        }
        result = a3a;
        field_360 += *v10 - v10[1] + 1;
    }
    return result;
}

// 0x00463F60
char MapRelatedStruct::sub_463F60(int a2, int a3, int a4, int a5, __int16 a6) {
    unsigned int* v7 = (unsigned int*)getMap()->sub_42A830( a3, a2);
    unsigned int v8 = sub_463A90(*v7);
    *(_DWORD*)getMap()->sub_42A830( a3, a2) = v8;
    S16_01_sub_463990(&s16_01, a2, a3, v8);
    int v9 = getMap()->field_40008;
    int v10 = *(unsigned __int8*)(v9 + 4 * v8 + 1);
    unsigned int v11 = v9 + 4 * v8;
    int v12 = sub_463A40(*(_DWORD*)(v11 + 4 * (a4 - v10) + 4));
    *(_DWORD*)(v11 + 4 * (a4 - *(unsigned __int8*)(v11 + 1)) + 4) = v12;
    int v13 = getMap()->field_4000C + 12 * v12;
    char result = a5 - 1;
    dword_662B90 = (_WORD*)v13;
    switch (a5) {
    case 1:
        *(_WORD*)v13 = a6;
        break;
    case 2:
        result = a6;
        *(_WORD*)(v13 + 2) = a6;
        break;
    case 3:
        *(_WORD*)(v13 + 4) = a6;
        break;
    case 4:
        result = a6;
        *(_WORD*)(v13 + 6) = a6;
        break;
    case 5:
        *(_WORD*)(v13 + 8) = a6;
        break;
    case 6:
        result = a6;
        *(_BYTE*)(v13 + 11) = a6;
        break;
    case 7:
        *(_BYTE*)(v13 + 10) = a6;
        break;
    default:
        return result;
    }
    return result;
}

// 0x00464060
int MapRelatedStruct::sub_464060(int a2, int a3, int a4, _DWORD* a5) {
    unsigned int* v6 = (unsigned int*)getMap()->sub_42A830( a3, a2);
    unsigned int v7 = sub_463AE0(*v6, a4);
    *(_DWORD*)getMap()->sub_42A830( a3, a2) = v7;
    S16_01_sub_463990(&s16_01, a2, a3, v7);
    int v8 = getMap()->field_40008;
    int v9 = *(unsigned __int8*)(v8 + 4 * v7 + 1);
    unsigned int v10 = v8 + 4 * v7;
    unsigned int v11 = *(_DWORD*)(v10 + 4 * (a4 - v9) + 4);
    int result;
    if (v11 >= field_34C) {
        _DWORD* v13 = (_DWORD*)(getMap()->field_4000C + 12 * v11);
        *v13 = *a5;
        result = a5[1];
        v13[1] = result;
        v13[2] = a5[2];
    } else {
        result = sub_463A00(a5);
        *(_DWORD*)(v10 + 4 * (a4 - *(unsigned __int8*)(v10 + 1)) + 4) = result;
    }
    return result;
}

// 0x00464110
S16_01* MapRelatedStruct::sub_464110(int a2, int a3, int a4, char a5) {
    unsigned int* v6 = (unsigned int*)getMap()->sub_42A830( a3, a2);
    S16_01* result = (S16_01*)sub_463C30(*v6, a4, a5);
    S16_01* v8 = result;
    if (result != (S16_01*)-1) {
        *(_DWORD*)getMap()->sub_42A830( a3, a2) = (_DWORD)result;
        return S16_01_sub_463990(&s16_01, a2, a3, (int)v8);
    }
    return result;
}

// 0x00464160
char MapRelatedStruct::sub_464160(int a2, int a3) {
    Map* Map = getMap();
    char* v5 = getMap()->sub_42A830( a3, a2);
    unsigned int v6 = *(_DWORD*)v5;
    int v7 = Map->field_40008;
    unsigned __int8 v8 = *(_BYTE*)(v7 + 4 * *(_DWORD*)v5);
    unsigned __int8 v9 = *(_BYTE*)(v7 + 4 * v6 + 1);
    char v14;
    if (v9 == v8 - 1 && v9) {
        char v10 = v9 - 1;
        if (v6 >= field_358) {
            v14 = (char)(v8 - 1);
            *(_BYTE*)(v7 + 4 * v6 + 1) = v10;
            *(_BYTE*)(v7 + 4 * v6) = v14;
        } else {
            int v11 = field_360;
            *(_BYTE*)(v7 + 4 * v11 + 1) = v10;
            unsigned __int8 v12 = *(_BYTE*)(v7 + 4 * v11);
            int v13 = v7 + 4 * v11;
            *(_BYTE*)v13 = v12 - 1;
            *(_DWORD*)(v13 + 4) = *(_DWORD*)(v7 + 4 * v6 + 4);
            v14 = field_360 + 2;
            field_360 = v14;
        }
    } else {
        v14 = (char)sub_464110(a2, a3, v9, 1);
    }
    return v14;
}


//=============================================================================
// sub_464210: Fill tile rect
//=============================================================================
int MapRelatedStruct::sub_464210(int a2, int a3, int a4, int a5)
{
    int result = a5;
    for (int i = a4; i <= a5; ++i)
    {
        for (int j = a2; j <= a3; ++j)
            sub_464160(j, i);
        result = a5;
    }
    return result;
}

//=============================================================================
// sub_464250: Set up zone/tile indices for map loading
//=============================================================================
unsigned int MapRelatedStruct::sub_464250(unsigned int a2, unsigned int a3, unsigned int a4)
{
    Map *v4 = getMap();
    field_360 = (int)((char *)v4->File + (a2 >> 2));
    field_358 = v4->field_40004 + a3 / 0xC;
    Buffer_ZONE = (void *)(a4 >> 3);
    return sub_463940(v4, (int)((char *)this + 4));
}

//=============================================================================
// sub_4642A0: Get map data pointers and sizes
//=============================================================================
int MapRelatedStruct::sub_4642A0(_DWORD *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5, _DWORD *a6, int *a7)
{
    *a2 = getMap()->field_40008 + 4 * (int)getMap()->File;
    *a3 = 4 * (field_360 - (unsigned int)getMap()->File);
    *a4 = getMap()->field_4000C + 12 * getMap()->field_40004;
    *a5 = 12 * (field_354 - getMap()->field_40004);
    *a6 = (_DWORD)&s16_01;
    int result = 8 * s16_01.field_320;
    *a7 = result;
    return result;
}

//=============================================================================
// sub_4644E0: Build ZONE index from buffer
//=============================================================================
int MapRelatedStruct::sub_4644E0(unsigned int a2)
{
    unsigned int v3 = 0;
    int v4 = 0;
    FILE *i;
    for (i = (FILE *)Buffer_ZONE; v3 < a2; ++v4)
    {
        int v6 = BYTE1(i[1]._Placeholder) + 6;
        v3 += v6;
        i = (FILE *)((char *)i + v6);
    }
    int result = (int)createBuffer(4 * v4 + 4);
    count = (int *)result;
    v3 = 0;
    *(_WORD *)result = v4;
    FILE *Buffer_ZONE_copy = (FILE *)Buffer_ZONE;
    if (a2)
    {
        int v10 = 0;
        do
        {
            v10 += 4;
            *(_DWORD *)((int)count + v10) = (int)Buffer_ZONE_copy;
            result = BYTE1(Buffer_ZONE_copy[1]._Placeholder) + 6;
            v3 += result;
            Buffer_ZONE_copy = (FILE *)((char *)Buffer_ZONE_copy + result);
        }
        while (v3 < a2);
    }
    return result;
}

//=============================================================================
// sub_464550: Load ANIM tiles
//=============================================================================
int MapRelatedStruct::sub_464550(int a2)
{
    FILE *Buffer_ANIM_copy = (FILE *)Buffer_ANIM;
    int result = (int)Buffer_ANIM_copy + a2;
    if (Buffer_ANIM_copy != (FILE *)((char *)Buffer_ANIM_copy + a2))
    {
        do
        {
            result = TileAnim::sub_4C3470(gTileAnim, (int)Buffer_ANIM_copy);
            Buffer_ANIM_copy = (FILE *)((char *)Buffer_ANIM_copy + 2 * LOBYTE(Buffer_ANIM_copy[1]._Placeholder) + 6);
        }
        while (Buffer_ANIM_copy != (FILE *)((char *)Buffer_ANIM + a2));
    }
    return result;
}

//=============================================================================
// sub_464590: Load MOBJ chunk
//=============================================================================
int MapRelatedStruct::sub_464590(SIZE_T dwBytes)
{
    SIZE_T v7;
    FILE *Buffer = (FILE *)createBuffer(v7);
    Buffer_MOBJ = Buffer;
    FileMgr::Read(Buffer, &v7);
    SIZE_T v4 = v7;
    int result = -1431655765 * v7;
    SIZE_T v6 = v7 / 6;
    field_344 = v7 / 6;
    if (6 * v6 != v4)
        return debug_log(0x28u, "map.cpp", 6024);
    return result;
}

//=============================================================================
// sub_4645F0: Load LGHT chunk
//=============================================================================
int MapRelatedStruct::sub_4645F0(SIZE_T dwBytes)
{
    SIZE_T v7;
    FILE *Buffer = (FILE *)createBuffer(v7);
    Buffer_LGHT = Buffer;
    FileMgr::Read(Buffer, &v7);
    SIZE_T v4 = v7;
    SIZE_T v5 = v7 >> 4;
    field_348 = v7 >> 4;
    int result = 16 * (int)v5;
    if (result != (int)v4)
        return debug_log(0x33u, "map.cpp", 6046);
    return result;
}

//=============================================================================
// sub_464640: Load ZONE chunk
//=============================================================================
int MapRelatedStruct::sub_464640(FileMgr *dwBytes)
{
    FILE *Buffer = (FILE *)createBuffer((SIZE_T)dwBytes);
    Buffer_ZONE = Buffer;
    FileMgr::Read(Buffer, (SIZE_T *)&dwBytes);
    return sub_4644E0((unsigned int)dwBytes);
}

//=============================================================================
// sub_464670: Load ANIM chunk
//=============================================================================
int MapRelatedStruct::sub_464670(FileMgr *dwBytes)
{
    FILE *Buffer = (FILE *)createBuffer((SIZE_T)dwBytes);
    Buffer_ANIM = Buffer;
    FileMgr::Read(Buffer, (SIZE_T *)&dwBytes);
    return sub_464550((int)dwBytes);
}

//=============================================================================
// sub_4646A0: Allocate and read .MAP file data (DMAP handler)
//=============================================================================
int MapRelatedStruct::sub_4646A0(int a2)
{
    int v23 = 0;
    Map *pMap = (Map *)operator_new(0x40010u);
    Map *pMap1;
    if (pMap)
        pMap1 = ::new (pMap) Map();
    else
        pMap1 = 0;
    getMap() = pMap1;
    if (!pMap1)
        debug_log(0x20u, "map.cpp", 6147);
    FILE *Map_file = (FILE *)getMap();
    SIZE_T v18 = 0x40000;
    FileMgr::Read(Map_file, &v18);
    FILE **p_File = (FILE**)&getMap()->File;
    v18 = 4;
    FileMgr::Read((FILE *)p_File, &v18);
    if ((unsigned int)((int*)&getMap()->File + 256) > 0x20000)
        debug_log(0x467u, "map.cpp", 6150);
    Map *pMap2 = getMap();
    int v6 = (int)((int*)&getMap()->File + 256);
    field_35C = v6;
    int v19 = 4 * (int)pMap2->File;
    getMap()->field_40008 = (int)createBuffer(4 * v6);
    FileMgr::Read((FILE *)getMap()->field_40008, (SIZE_T *)&v19);
    int *v7 = (int *)getMap();
    SIZE_T v21[2];
    v21[0] = 4;
    int Placeholder = v7[0x10000];
    field_358 = Placeholder;
    field_360 = Placeholder;
    FileMgr::Read(v7 + 65537, v21);
    if ((unsigned int)(getMap()->field_40004 + 200) > 0x20000)
        debug_log(0x469u, "map.cpp", 6161);
    Map *v9 = getMap();
    int v10 = getMap()->field_40004 + 200;
    field_350 = v10;
    int v22 = 12 * v9->field_40004;
    void *Buffer = createBuffer(12 * v10);
    Map *v12 = getMap();
    SIZE_T *v20 = (SIZE_T *)&v22;
    v12->field_4000C = (int)Buffer;
    FileMgr::Read((FILE *)getMap()->field_4000C, v20);
    int v13 = v22;
    int v14 = getMap()->field_40004;
    field_34C = v14;
    field_354 = v14;
    int result = v23;
    if (v23 != v13 + v21[1] + 262152)
    {
        v21[0] = v23;
        return debug_log(0x409u, "map.cpp", 6170);
    }
    return result;
}

//=============================================================================
// sub_464880: Read RGEN chunk and debug-print junctions
//=============================================================================
unsigned char MapRelatedStruct::sub_464880()
{
    JuncIds *pJuncIds = (JuncIds *)gJuncIds;
    SIZE_T v12 = 8720;
    FileMgr::Read((FILE *)pJuncIds->Arr_316_Data16, &v12);
    v12 = 4360;
    FileMgr::Read((FILE *)pJuncIds->Arr_0x884, &v12);
    v12 = 4360;
    FileMgr::Read((FILE *)pJuncIds->arr_0x884, &v12);
    v12 = 2;
    FileMgr::Read((FILE *)&pJuncIds->field_4, &v12);
    v12 = 2;
    FileMgr::Read((FILE *)&pJuncIds->field_CC62, &v12);
    v12 = 2;
    FileMgr::Read((FILE *)&pJuncIds->field_CC64, &v12);
    pJuncIds->Count = 0;
    unsigned char result = log_routefinder;
    if (log_routefinder)
    {
        int v3 = 0;
        Data16 *v4 = (Data16 *)((char *)&((Data16 *)pJuncIds->Arr_316_Data16)->field_4 + 2);
        do
        {
            int v11, v10, v9;
            unsigned __int16 v5 = Data16::sub_40CE90((Data16 *)((char *)v4 - 2));
            v11 = v5;
            unsigned __int16 v6 = Data16::sub_40CE90(v4);
            v10 = v6;
            unsigned __int16 v7 = Data16::sub_40CE90((Data16 *)((char *)v4 - 4));
            v9 = v7;
            unsigned __int16 v8 = Data16::sub_40CE90((Data16 *)((char *)v4 - 6));
            sprintf(
                gStr,
                "Junc: %d (%d, %d) n %d s %d w %d e %d",
                v3,
                BYTE2(v4->field_4),
                HIBYTE(v4->field_4),
                v8,
                v9,
                v10,
                v11);
            CopyBuffer(byte_5EA6B8, gStr);
            if (v3 > 0 && !BYTE2(v4->field_4) && !HIBYTE(v4->field_4))
                break;
            ++v3;
            ++v4;
        }
        while (v3 < 545);
        return (unsigned char)CopyBuffer(byte_5EA6B8, "     ");
    }
    return result;
}

//=============================================================================
// sub_464890: Dispatch chunk loading by four-cc ident
//=============================================================================
unsigned char MapRelatedStruct::sub_464890(_BYTE *a2, FileMgr *dwBytes)
{
    if (!strncmp((const char*)a2, "DMAP", 4))
        return sub_4646A0((int)dwBytes);
    if (!strncmp((const char*)a2, "ZONE", 4))
        return sub_464640(dwBytes);
    if (!strncmp((const char*)a2, "MOBJ", 4))
        return sub_464590((SIZE_T)dwBytes);
    if (!strncmp((const char*)a2, "ANIM", 4))
        return sub_464670(dwBytes);
    if (!strncmp((const char*)a2, "LGHT", 4))
        return sub_4645F0((SIZE_T)dwBytes);
    if (!strncmp((const char*)a2, "RGEN", 4))
        return sub_464880();
    FileMgr *v5;
    return FileMgr::SeekPosition(v5, (int)&dwBytes);
}

//=============================================================================
// sub_464980: Post-load helper (returns this as _WORD*)
//=============================================================================
_WORD *MapRelatedStruct::sub_464980()
{
    return (_WORD *)this;
}

//=============================================================================
// sub_464990: Load a .MAP file by name
//=============================================================================
_WORD *MapRelatedStruct::sub_464990(LPCSTR lpFileName)
{
    FileMgr *v3;
    unsigned int size;
    FILE v6[2];
    char a1[4];
    SIZE_T dwBytes;

    FileMgr::FileOpen(this, lpFileName);
    size = 6;
    FileMgr::Read(v6, &size);
    for (size = 8; FileMgr::ReadLine((FileMgr *)a1, a1, (SIZE_T)&size); size = 8)
    {
        if (dwBytes)
            sub_464890((_BYTE*)a1, (FileMgr *)dwBytes);
    }
    FileMgr::CloseFile(v3);
    _WORD *result = sub_464980();
    if (!getMap())
        return (_WORD *)debug_log(0x84u, "map.cpp", 6329);
    return result;
}

//=============================================================================
// sub_464C70: Find ZONE entry by string
//=============================================================================
int MapRelatedStruct::sub_464C70(const char *a2)
{
    unsigned int v3 = strlen(a2);
    unsigned int v8 = v3;
    if (!Buffer_ZONE)
        return 0;
    _WORD *count_ptr = (_WORD *)count;
    field_364 = 0;
    if (*count_ptr)
    {
        unsigned short v7;
        do
        {
            unsigned __int16 v6 = field_364;
            int result = (int)sub_462E40(v6);
            if (*(unsigned char *)(result + 5) == v3)
            {
                if (!memcmp((const void *)(result + 6), a2, v3))
                    return result;
                v3 = v8;
            }
            v7 = v6 + 1;
            field_364 = v7;
        }
        while (v7 < *(_WORD *)count);
    }
    return 0;
}

//=============================================================================
// sub_464D00: Find ZONE entry by name with length prefix
//=============================================================================
int MapRelatedStruct::sub_464D00(char *String2, unsigned char a3)
{
    if (!Buffer_ZONE)
        return 0;
    _WORD *count_ptr = (_WORD *)count;
    field_364 = 0;
    if (!*count_ptr)
        return -1;
    while (1)
    {
        char *v6 = sub_462E40(field_364);
        if (v6[5] == a3 && !_strnicmp(v6 + 6, String2, a3))
            break;
        if (++field_364 >= *(_WORD *)count)
            return -1;
    }
    return field_364;
}

//=============================================================================
// sub_464DA0: Select a random ZONE entry matching a type character
//=============================================================================
char *MapRelatedStruct::sub_464DA0(char a2)
{
    if (!Buffer_ZONE)
        return 0;
    _WORD *count_ptr = (_WORD *)count;
    unsigned __int16 v5 = 0;
    field_36C = 0;
    Len = a2;
    field_364 = 0;
    if (!*count_ptr)
        return 0;
    unsigned __int16 a2a[40];
    unsigned short v8;
    do
    {
        unsigned __int16 v6 = field_364;
        if (*sub_462E40(v6) == a2)
        {
            int v7 = v5++;
            a2a[v7] = v6;
            if (v5 >= 0x28u)
                break;
        }
        v8 = v6 + 1;
        field_364 = v8;
    }
    while (v8 < *(_WORD *)count);
    if (!v5)
        return 0;
    __int16 v9 = ++word_663290;
    if (word_663290 >= (int)v5)
    {
        v9 = 0;
        word_663290 = 0;
    }
    return sub_462E40(a2a[v9]);
}

//=============================================================================
// sub_464E70: Find first ZONE entry matching a type character
//=============================================================================
char *MapRelatedStruct::sub_464E70(char a2)
{
    char *result = 0;
    if (Buffer_ZONE)
    {
        _WORD *count_ptr = (_WORD *)count;
        field_36C = 0;
        Len = a2;
        field_364 = 0;
        if (*count_ptr)
        {
            while (1)
            {
                unsigned __int16 v5 = field_364;
                result = sub_462E40(v5);
                if (*result == a2)
                    break;
                unsigned short v6 = v5 + 1;
                field_364 = v6;
                if (v6 >= *(_WORD *)count)
                    return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    return result;
}

//=============================================================================
// sub_464FE0: Find ZONE entry by type + coordinate match
//=============================================================================
char *MapRelatedStruct::sub_464FE0(unsigned char a2, unsigned char a3, char a4)
{
    if (!Buffer_ZONE)
        return 0;
    _WORD *count_ptr = (_WORD *)count;
    field_36A = a2;
    Len = a4;
    field_36B = a3;
    field_36C = 1;
    field_364 = 0;
    if (!*count_ptr)
        return 0;
    while (1)
    {
        unsigned short v7 = field_364;
        char *v8 = sub_462E40(v7);
        if (*v8 == a4 && sub_463020(v8, a2, a3))
            break;
        unsigned short v9 = v7 + 1;
        field_364 = v9;
        if (v9 >= *(_WORD *)count)
            return 0;
    }
    return v8;
}

//=============================================================================
// sub_465090: Find ZONE entry with special types + coordinate match
//=============================================================================
char *MapRelatedStruct::sub_465090(unsigned char a2, unsigned char a3)
{
    if (!Buffer_ZONE)
        return 0;
    _WORD *count_ptr = (_WORD *)count;
    field_36A = a2;
    field_36B = a3;
    field_364 = 0;
    if (!*count_ptr)
        return 0;
    while (1)
    {
        unsigned short v6 = field_364;
        char *v7 = sub_462E40(v6);
        char v8 = *v7;
        if ((*v7 == 10 || v8 == 1 || v8 == 15) && sub_463020(v7, a2, a3))
            break;
        unsigned short v9 = v6 + 1;
        field_364 = v9;
        if (v9 >= *(_WORD *)count)
            return 0;
    }
    return v7;
}

//=============================================================================
// sub_465130: Find ZONE entry by coordinate match (any type)
//=============================================================================
char *MapRelatedStruct::sub_465130(unsigned char a2, unsigned char a3)
{
    if (!Buffer_ZONE)
        return 0;
    _WORD *count_ptr = (_WORD *)count;
    field_36A = a2;
    field_36B = a3;
    field_36C = 1;
    field_364 = 0;
    if (!*count_ptr)
        return 0;
    while (1)
    {
        unsigned short v6 = field_364;
        char *v7 = sub_462E40(v6);
        if (sub_463020(v7, a2, a3))
            break;
        unsigned short v8 = v6 + 1;
        field_364 = v8;
        if (v8 >= *(_WORD *)count)
            return 0;
    }
    return v7;
}

//=============================================================================
// sub_4651C0: Iterate to next ZONE entry matching current search criteria
//=============================================================================
char *MapRelatedStruct::sub_4651C0()
{
    if (!Buffer_ZONE)
        return 0;
    unsigned __int16 v3 = ++field_364;
    if (v3 >= *(_WORD *)count)
        return 0;
    char Len_copy = Len;
    while (1)
    {
        void *v5 = sub_462E40(v3);
        if (*(_BYTE *)v5 == Len_copy && (!field_36C || sub_463020(v5, field_36A, field_36B)))
            break;
        field_364 = ++v3;
        if (v3 >= *(_WORD *)count)
            return 0;
    }
    return (char *)v5;
}

//=============================================================================
// sub_465250: Query tile and return associated data
//=============================================================================
int MapRelatedStruct::sub_465250(unsigned char a2, unsigned char a3)
{
    if (sub_465090(a2, a3))
        return sub_462C60();
    else
        return (int)field_334;
}

//=============================================================================
// sub_465280: Set tile data fields
//=============================================================================
_WORD *MapRelatedStruct::sub_465280(int a2, __int16 a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, __int16 a11, __int16 a12, __int16 a13)
{
    _WORD *result = (_WORD *)(this->field_334 + 22 * *(unsigned char *)(this->field_330 + a2));
    if (a3 != -1)
        *result = (unsigned short)a3;
    if (a4 != -1)
        result[1] = (unsigned short)a4;
    if (a5 != -1)
        result[2] = (unsigned short)a5;
    if (a6 != -1)
        result[3] = (unsigned short)a6;
    if (a7 != -1)
        result[4] = (unsigned short)a7;
    if (a8 != -1)
        result[5] = (unsigned short)a8;
    if (a9 != -1)
        result[6] = (unsigned short)a9;
    if (a10 != -1)
        result[7] = (unsigned short)a10;
    if (a11 != -1)
        result[8] = (unsigned short)a11;
    if (a12 != -1)
        result[9] = (unsigned short)a12;
    if (a13 != -1)
        result[10] = (unsigned short)a13;
    return result;
}

//=============================================================================
// sub_465350: Get gang for tile coordinates
//=============================================================================
Gang *MapRelatedStruct::sub_465350(int a2, int a3)
{
    unsigned char v7 = Weapon::sub_41C1E0((Weapon *)&a3);
    unsigned char v4 = Weapon::sub_41C1E0((Weapon *)&a2);
    char *v5 = sub_464FE0(v4, v7, 14);
    if (v5)
        return Gangs::FindByName(gGangs, (int)(v5 + 6));
    else
        return 0;
}

//=============================================================================
// sub_465390: Iterate all 14-type ZONE entries and add gangs
//=============================================================================
char *MapRelatedStruct::sub_465390()
{
    char *result;
    for (result = sub_464E70(14); result; result = sub_4651C0())
        Gangs::AddNewGang(gGangs, (int)result);
    return result;
}


// 0x4653C0
int MapRelatedStruct::sub_4653C0(int a2, int a3, int a4) {
  Map *Map; 
  unsigned __int8 *v5; 
  int v6; 
  Map = getMap();
  v5 = (unsigned __int8 *)(Map->field_40008 + 4 * *(_DWORD *)getMap()->sub_42A830( a3, a2));
  if ( a4 >= *v5 )
    return 0;
  v6 = v5[1];
  if ( a4 < v6 )
    return 0;
  else
    return Map->field_4000C + 12 * *(_DWORD *)&v5[4 * (a4 - v6) + 4];
}

// 0x465410
S16_02** MapRelatedStruct::sub_465410(int a2, int a3, int a4) {
  Map *Map; 
  unsigned __int8 *v5; 
  int v6; 
  S16_02 **result; 
  Map = getMap();
  v5 = (unsigned __int8 *)(Map->field_40008 + 4 * *(_DWORD *)getMap()->sub_42A830( a3, a2));
  if ( a4 >= *v5 )
    return 0;
  v6 = v5[1];
  if ( a4 < v6 )
    return 0;
  result = (S16_02 **)(Map->field_4000C + 12 * *(_DWORD *)&v5[4 * (a4 - v6) + 4]);
  if ( (*((_BYTE *)result + 11) & 0xFCu) >= 0xD4 && (*((_BYTE *)result + 11) & 0xFCu) <= 0xF4 )
    return 0;
  if ( (*((_BYTE *)result + 11) & 0xFCu) >= 0xC4 && (*((_BYTE *)result + 11) & 0xFCu) <= 0xD0 )
    return (S16_02 **)&unk_662B94;
  return result;
}

// 0x465490
int MapRelatedStruct::sub_465490(int a2, int a3, int a4) {
  int v4; 
  int v5; 
  Map *Map; 
  int v7; 
  int v8; 
  int v9; 
  int v10; 
  int v11; 
  v4 = a2;
  if ( a2 >= 0 )
  {
    if ( a2 > 255 )
      v4 = 255;
  }
  else
  {
    v4 = 0;
  }
  v5 = a3;
  if ( a3 >= 0 )
  {
    if ( a3 > 255 )
      v5 = 255;
  }
  else
  {
    v5 = 0;
  }
  Map = getMap();
  v7 = *(_DWORD *)getMap()->sub_42A830( v5, v4);
  v8 = Map->field_40008;
  v9 = *(unsigned __int8 *)(v8 + 4 * v7);
  v10 = v8 + 4 * v7;
  if ( a4 >= v9 )
    return 0;
  v11 = *(unsigned __int8 *)(v10 + 1);
  if ( a4 < v11 )
    return 0;
  else
    return Map->field_4000C + 12 * *(_DWORD *)(v10 + 4 * (a4 - v11) + 4);
}

// 0x465510
int MapRelatedStruct::sub_465510(GameEntity* a2) {
  SpriteS1 *v3; 
  int v4; 
  int v5; 
  __int16 v6; // ax
  int v7; 
  __int16 *v8; 
  int v10; // [esp-8h] [ebp-10h]
  int v11; // [esp-8h] [ebp-10h]
  int v12; // [esp-4h] [ebp-Ch]
  int v13; // [esp-4h] [ebp-Ch]
  int v14;
  AudioSourceParams v15;
  v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v15.y);
  v10 = AudioSourceParams::sub_41F9D0(&v15);
  v3 = Player::sub_401B40((Player *)&a2, (S202 *)&v14, (int)&unk_662C98);
  v4 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v3);
  v5 = sub_4653C0( v4, v10, v12);
  if ( v5 )
  {
    v6 = *(_WORD *)(v5 + 2);
    if ( v6 )
      return Style::sub_462FD0(gStyle, v6 & 0x3FF);
  }
  v13 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v15.y);
  v11 = AudioSourceParams::sub_41F9D0(&v15);
  v7 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v8 = (__int16 *)sub_4653C0( v7, v11, v13);
  if ( v8 && (v6 = *v8) != 0 )
    return Style::sub_462FD0(gStyle, v6 & 0x3FF);
  else
    return 0;
}

// 0x4655B0
int MapRelatedStruct::sub_4655B0(int a2, GameEntity* a3) {
  SpriteS1 *v4; 
  int v5; 
  int v6; 
  __int16 v7; // ax
  int v8; 
  int v9; 
  int v11; // [esp-8h] [ebp-10h]
  int v12; // [esp-8h] [ebp-10h]
  int v13; // [esp-4h] [ebp-Ch]
  int v14; // [esp-4h] [ebp-Ch]
  _BYTE v15[4];
  AudioSourceParams a3_4;
  v13 = AudioSourceParams::sub_41F9D0(&a3_4);
  v4 = Player::sub_401B40((Player *)&a3, (S202 *)v15, (int)&unk_662C98);
  v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v4);
  v5 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v6 = sub_4653C0( v5, v11, v13);
  if ( v6 )
  {
    v7 = *(_WORD *)(v6 + 6);
    if ( v7 )
      return Style::sub_462FD0(gStyle, v7 & 0x3FF);
  }
  v14 = AudioSourceParams::sub_41F9D0(&a3_4);
  v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
  v8 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v9 = sub_4653C0( v8, v12, v14);
  if ( v9 && (v7 = *(_WORD *)(v9 + 4)) != 0 )
    return Style::sub_462FD0(gStyle, v7 & 0x3FF);
  else
    return 0;
}

// 0x465650
int MapRelatedStruct::sub_465650(int a2, int a3, Player* a4) {
  int v4; 
  int v5; 
  unsigned __int16 index; // ax
  int v8; // [esp-8h] [ebp-8h]
  int v9; // [esp-4h] [ebp-4h]
  if ( Player::sub_40CE70((Player *)&a4, &unk_662CFC)
    && sub_4037E0(&a4)
    && (v9 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a4),
        v8 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3),
        v4 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2),
        (v5 = gMapRelatedStruct->sub_4653C0( v4, v8, v9)) != 0)
    && (index = *(_WORD *)(v5 + 8)) != 0 )
  {
    return Style::sub_462FD0(gStyle, index & 1023);
  }
  else
  {
    return 0;
  }
}

// 0x4656D0
char MapRelatedStruct::sub_4656D0(int a2, int a3, int a4, int a5, _DWORD* a6, char a7) {
  S16_02 **v9; 
  S16_02 **v10; 
  unsigned __int8 v11; // cl
  S16_02 **v12; 
  unsigned __int8 v13; // al
  int v14; 
  char v15; // cl
  _BYTE *v16; 
  char result; // al
  int v18; 
  S16_02 **v19; 
  bool v20; // zf
  int v21; 
  S16_02 **v22; 
  unsigned __int8 v23; // al
  char v24; // dl
  int v25; 
  S16_02 **v26; 
  char v27; // cl
  unsigned __int8 v28; // al
  S16_02 **v29; 
  unsigned __int8 v30; // al
  int v31; 
  char v32; // cl
  _BYTE *v33; 
  S16_02 **v34; 
  S16_02 **v35; 
  S16_02 **v36; 
  unsigned __int8 v37; // al
  unsigned __int8 v38; // dl
  int v39; 
  S16_02 **v40; 
  S16_02 **v41; 
  S16_02 **v42; 
  unsigned __int8 v43; // al
  int v44; 
  char v45; // cl
  _BYTE *v46; 
  S16_02 **v47; 
  unsigned __int8 v48; // al
  char v49; // cl
  unsigned __int8 v50; // cl
  int v51; 
  S16_02 **v52; 
  S16_02 **v53; 
  S16_02 **v54; 
  unsigned __int8 v55; // al
  int v56; 
  char v57; // cl
  _BYTE *v58; 
  S16_02 **v59; 
  unsigned __int8 v60; // al
  char v61; // cl
  _BYTE *v62;
  _BYTE *v63;
  S16_02 **v64;
  v62 = 0;
  v63 = 0;
  this->field_36E = 0;
  v9 = sub_465410( a2, a3, a4);
  v64 = v9;
  if ( v9 )
  {
    v63 = (_BYTE *)(12 * (*((unsigned __int8 *)v9 + 11) >> 2) + 6696368);
  }
  else if ( a4 > 0 )
  {
    v10 = sub_465410( a2, a3, a4 - 1);
    if ( v10 )
      v63 = (_BYTE *)(12 * (*((unsigned __int8 *)v10 + 11) >> 2) + 6696368);
  }
  switch ( a5 )
  {
    case 1:
      if ( !v64 )
        goto LABEL_27;
      if ( !a3 )
        return 1;
      v62 = (_BYTE *)(12 * (*((unsigned __int8 *)v64 + 11) >> 2) + 6696368);
      if ( 12 * (*((unsigned __int8 *)v64 + 11) >> 2) == -6696368 )
        goto LABEL_27;
      v11 = *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v64 + 11) >> 2));
      if ( v11 == 1 )
      {
        if ( !byte_662DB2[12 * (*((unsigned __int8 *)v64 + 11) >> 2)] )
        {
          v18 = a3 - 1;
          v19 = sub_465410( a2, a3 - 1, a4 + 1);
          if ( !v19 )
            goto LABEL_63;
          v20 = (*((_BYTE *)v19 + 7) & 4) == 0;
          goto LABEL_62;
        }
        goto LABEL_26;
      }
      if ( v11 > 2u && v11 <= 4u )
      {
        if ( a3 <= 0 )
          goto LABEL_42;
        v12 = sub_465410( a2, a3 - 1, a4);
        if ( !v12 )
          goto LABEL_42;
        v13 = *((_BYTE *)v12 + 11);
        if ( (v13 & 0xFC) != 0 && (v13 & 0xFCu) < 0xB4 && (v13 & 3) != 0 )
        {
          v14 = 3 * (v13 >> 2);
          v15 = byte_662DB2[4 * v14];
          v16 = (_BYTE *)(4 * v14 + 6696368);
          if ( v15 != v62[2] && *v62 != *v16 )
          {
            this->field_36E = 1;
            return 1;
          }
        }
LABEL_26:
        if ( (*((_BYTE *)v64 + 5) & 4) != 0 )
          return 1;
LABEL_27:
        v21 = a3 - 1;
        v22 = sub_465410( a2, a3 - 1, a4);
        if ( !v22 )
          goto LABEL_33;
        if ( (*((_BYTE *)v22 + 7) & 4) == 0 )
        {
          v23 = *((_BYTE *)v22 + 11);
          if ( (v23 & 0xFC) != 0 && (v23 & 0xFCu) < 0xB4 && (v23 & 3) != 0 )
          {
            v24 = *((_BYTE *)&unk_662DB0 + 12 * (v23 >> 2));
            v25 = 12 * (v23 >> 2) + 6696368;
            switch ( v24 )
            {
              case 1:
              case 2:
                return 0;
              case 3:
              case 4:
                goto LABEL_148;
              default:
                return 1;
            }
          }
          goto LABEL_33;
        }
        return 1;
      }
      if ( (*((_BYTE *)v64 + 5) & 4) == 0 )
        goto LABEL_26;
      return 1;
    case 2:
      if ( !v64 )
        goto LABEL_70;
      if ( a3 == 255 )
        return 1;
      v62 = (_BYTE *)(12 * (*((unsigned __int8 *)v64 + 11) >> 2) + 6696368);
      if ( 12 * (*((unsigned __int8 *)v64 + 11) >> 2) == -6696368 )
        goto LABEL_69;
      if ( *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v64 + 11) >> 2)) == 2 )
      {
        if ( !byte_662DB2[12 * (*((unsigned __int8 *)v64 + 11) >> 2)] )
        {
          v18 = a3 + 1;
          v34 = sub_465410( a2, a3 + 1, a4 + 1);
          if ( v34 )
          {
            v20 = (*((_BYTE *)v34 + 5) & 4) == 0;
LABEL_62:
            if ( !v20 )
              return 1;
          }
LABEL_63:
          if ( sub_465410( a2, v18, a4 + 1) )
          {
            if ( !a7 )
              return 0;
            *a6 = 1;
            return 0;
          }
          v35 = sub_465410( a2, v18, a4);
          if ( !v35 )
            goto LABEL_42;
          if ( (*((_BYTE *)v35 + 11) & 3) == 0 )
          {
            this->field_36E = 1;
            return 1;
          }
          goto LABEL_127;
        }
      }
      else if ( *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v64 + 11) >> 2)) <= 2u
             || *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v64 + 11) >> 2)) > 4u )
      {
        if ( (*((_BYTE *)v64 + 7) & 4) != 0 )
          return 1;
      }
      else
      {
        v29 = sub_465410( a2, a3 + 1, a4);
        if ( !v29 )
          goto LABEL_42;
        v30 = *((_BYTE *)v29 + 11);
        if ( (v30 & 0xFC) != 0 && (v30 & 0xFCu) < 0xB4 && (v30 & 3) != 0 )
        {
          v31 = 3 * (v30 >> 2);
          v32 = byte_662DB2[4 * v31];
          v33 = (_BYTE *)(4 * v31 + 6696368);
          if ( v32 != v62[2] && *v62 != *v33 )
          {
            this->field_36E = 1;
            return 1;
          }
        }
      }
LABEL_69:
      if ( (*((_BYTE *)v64 + 7) & 4) != 0 )
        return 1;
LABEL_70:
      v21 = a3 + 1;
      v36 = sub_465410( a2, a3 + 1, a4);
      if ( v36 )
      {
        if ( (*((_BYTE *)v36 + 5) & 4) != 0 )
          return 1;
        v37 = *((_BYTE *)v36 + 11);
        if ( (v37 & 0xFC) != 0 && (v37 & 0xFCu) < 0xB4 && (v37 & 3) != 0 )
        {
          v24 = *((_BYTE *)&unk_662DB0 + 12 * (v37 >> 2));
          v25 = 12 * (v37 >> 2) + 6696368;
          switch ( v24 )
          {
            case 1:
            case 2:
              return 0;
            case 3:
            case 4:
              goto LABEL_148;
            default:
              return 1;
          }
        }
      }
LABEL_33:
      if ( a4 <= 0 )
        goto LABEL_112;
      v26 = sub_465410( a2, v21, a4 - 1);
      if ( !v26 )
        goto LABEL_113;
      v27 = *((_BYTE *)v26 + 11);
      if ( (v27 & 3) == 0 )
        goto LABEL_113;
      if ( (v27 & 0xFC) == 0 || (v27 & 0xFCu) >= 0xB4 )
        return 0;
      v28 = *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v26 + 11) >> 2));
      if ( v28 && v28 <= 2u )
        goto LABEL_160;
      goto LABEL_40;
    case 3:
      if ( !v64 )
        goto LABEL_98;
      if ( a2 == 255 )
        return 1;
      v62 = (_BYTE *)(12 * (*((unsigned __int8 *)v64 + 11) >> 2) + 6696368);
      if ( 12 * (*((unsigned __int8 *)v64 + 11) >> 2) == -6696368 )
        goto LABEL_98;
      v38 = *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v64 + 11) >> 2));
      if ( !v38 )
        goto LABEL_96;
      if ( v38 <= 2u )
      {
        v42 = sub_465410( a2 + 1, a3, a4);
        if ( !v42 )
          goto LABEL_42;
        v43 = *((_BYTE *)v42 + 11);
        if ( (v43 & 0xFC) != 0 && (v43 & 0xFCu) < 0xB4 && (v43 & 3) != 0 )
        {
          v44 = 3 * (v43 >> 2);
          v45 = byte_662DB2[4 * v44];
          v46 = (_BYTE *)(4 * v44 + 6696368);
          if ( v45 != v62[2] && *v62 != *v46 )
          {
            this->field_36E = 1;
            return 1;
          }
        }
      }
      else if ( v38 == 4 )
      {
        if ( !byte_662DB2[12 * (*((unsigned __int8 *)v64 + 11) >> 2)] )
        {
          v39 = a2 + 1;
          v40 = sub_465410( a2 + 1, a3, a4 + 1);
          if ( v40 && (*((_BYTE *)v40 + 1) & 4) != 0 )
            return 1;
          if ( sub_465410( v39, a3, a4 + 1) )
            goto LABEL_127;
          v41 = sub_465410( v39, a3, a4);
          if ( v41 )
          {
            if ( (*((_BYTE *)v41 + 11) & 3) != 0 )
              goto LABEL_131;
            this->field_36E = 1;
            return 1;
          }
          goto LABEL_42;
        }
      }
      else
      {
LABEL_96:
        if ( (*((_BYTE *)v64 + 3) & 4) != 0 )
          return 1;
      }
      if ( (*((_BYTE *)v64 + 3) & 4) != 0 )
        return 1;
LABEL_98:
      v47 = sub_465410( a2 + 1, a3, a4);
      if ( v47 )
      {
        if ( (*((_BYTE *)v47 + 1) & 4) != 0 )
          return 1;
        v48 = *((_BYTE *)v47 + 11);
        if ( (v48 & 0xFC) != 0 && (v48 & 0xFCu) < 0xB4 && (v48 & 3) != 0 )
        {
          v24 = *((_BYTE *)&unk_662DB0 + 12 * (v48 >> 2));
          v25 = 12 * (v48 >> 2) + 6696368;
          switch ( v24 )
          {
            case 1:
            case 2:
              goto LABEL_148;
            case 3:
            case 4:
              return 0;
            default:
              return 1;
          }
        }
      }
      if ( a4 <= 0 )
        goto LABEL_112;
      v26 = sub_465410( a2 + 1, a3, a4 - 1);
      if ( !v26 )
        goto LABEL_113;
      v49 = *((_BYTE *)v26 + 11);
      if ( (v49 & 3) == 0 )
        goto LABEL_113;
      if ( (v49 & 0xFC) == 0 || (v49 & 0xFCu) >= 0xB4 )
        return 0;
      v28 = *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v26 + 11) >> 2));
      if ( v28 >= 3u && v28 <= 4u )
      {
        *a6 = -1;
        return 0;
      }
      goto LABEL_40;
    case 4:
      if ( !v64 )
        goto LABEL_142;
      if ( !a2 )
        return 1;
      v62 = (_BYTE *)(12 * (*((unsigned __int8 *)v64 + 11) >> 2) + 6696368);
      if ( 12 * (*((unsigned __int8 *)v64 + 11) >> 2) == -6696368 )
        goto LABEL_142;
      v50 = *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v64 + 11) >> 2));
      if ( !v50 )
        goto LABEL_140;
      if ( v50 <= 2u )
      {
        v54 = sub_465410( a2 - 1, a3, a4);
        if ( !v54 )
        {
LABEL_42:
          this->field_36E = 1;
          return 1;
        }
        v55 = *((_BYTE *)v54 + 11);
        if ( (v55 & 0xFC) != 0 && (v55 & 0xFCu) < 0xB4 && (v55 & 3) != 0 )
        {
          v56 = 3 * (v55 >> 2);
          v57 = byte_662DB2[4 * v56];
          v58 = (_BYTE *)(4 * v56 + 6696368);
          if ( v57 != v62[2] && *v62 != *v58 )
          {
            this->field_36E = 1;
            return 1;
          }
        }
LABEL_141:
        if ( (*((_BYTE *)v64 + 1) & 4) != 0 )
          return 1;
LABEL_142:
        v59 = sub_465410( a2 - 1, a3, a4);
        if ( v59 )
        {
          if ( (*((_BYTE *)v59 + 3) & 4) != 0 )
            return 1;
          v60 = *((_BYTE *)v59 + 11);
          if ( (v60 & 0xFC) != 0 && (v60 & 0xFCu) < 0xB4 && (v60 & 3) != 0 )
          {
            v24 = *((_BYTE *)&unk_662DB0 + 12 * (v60 >> 2));
            v25 = 12 * (v60 >> 2) + 6696368;
            switch ( v24 )
            {
              case 1:
              case 2:
LABEL_148:
                if ( !v62 )
                  return 1;
                if ( *(_BYTE *)(v25 + 2) == v62[2] || *v62 == v24 )
                  return 0;
                result = 1;
                break;
              case 3:
              case 4:
                return 0;
              default:
                return 1;
            }
            return result;
          }
        }
        if ( a4 <= 0 )
        {
LABEL_112:
          v26 = 0;
        }
        else
        {
          v26 = sub_465410( a2 - 1, a3, a4 - 1);
          if ( v26 )
          {
            v61 = *((_BYTE *)v26 + 11);
            if ( (v61 & 3) != 0 )
            {
              if ( (v61 & 0xFC) == 0 || (v61 & 0xFCu) >= 0xB4 )
                return 0;
              v28 = *((_BYTE *)&unk_662DB0 + 12 * (*((unsigned __int8 *)v26 + 11) >> 2));
              if ( v28 >= 3u && v28 <= 4u )
              {
                this->field_36E = 1;
LABEL_160:
                *a6 = -1;
                return 0;
              }
LABEL_40:
              if ( v63 && *v63 == v28 )
                return 0;
              goto LABEL_42;
            }
          }
        }
LABEL_113:
        this->field_36E = 1;
        if ( v26 && *((_BYTE *)v26 + 10) )
        {
          this->field_36F = 1;
          return 0;
        }
        return 1;
      }
      if ( v50 != 3 )
      {
LABEL_140:
        if ( (*((_BYTE *)v64 + 1) & 4) != 0 )
          return 1;
        goto LABEL_141;
      }
      if ( byte_662DB2[12 * (*((unsigned __int8 *)v64 + 11) >> 2)] )
        goto LABEL_141;
      v51 = a2 - 1;
      v52 = sub_465410( a2 - 1, a3, a4 + 1);
      if ( v52 && (*((_BYTE *)v52 + 3) & 4) != 0 )
        return 1;
      if ( sub_465410( v51, a3, a4 + 1) )
      {
LABEL_127:
        if ( a7 )
        {
          *a6 = 1;
          return 0;
        }
        return 0;
      }
      v53 = sub_465410( v51, a3, a4);
      if ( !v53 || (*((_BYTE *)v53 + 11) & 3) == 0 )
        goto LABEL_42;
LABEL_131:
      if ( !a7 )
        return 0;
      *a6 = 1;
      return 0;
    default:
      return 0;
  }
}

// 0x465FE0
char MapRelatedStruct::sub_465FE0(AudioSourceParams* arg0) {
  int v2; 
  int v3; 
  int v4; 
  int v5; 
  int v6; 
  int v7; 
  int v9;
  S202 a2;
  int v12[2];
  int v13[2];
  AudioSourceParams::sub_4BA5E0(arg0);
  v2 = sub_463760(arg0);
  v3 = dword_662BAC;
  v9 = v2;
  if ( (int)dword_662BAC > a5 )
    return 0;
  while ( 1 )
  {
    v4 = ::arg0;
    if ( ::arg0 <= dword_662BF8 )
      break;
LABEL_15:
    if ( ++v3 > a5 )
      return 0;
  }
  v5 = ::arg0 + 1;
  while ( 1 )
  {
    v6 = sub_4653C0( v4, v3, v9);
    if ( v6 )
    {
      v7 = *(_BYTE *)(v6 + 11) & 0xFC;
      if ( v7 >= 180 && v7 <= 208 )
      {
        if ( v7 == 180 || v7 == 192 || v7 == 196 || v7 == 208 )
        {
          S202::sub_41F980((S202 *)&a2.field_10, v3 + 1);
          S202::sub_41F980((S202 *)&a2.pPlayer, v4);
          Weapon::sub_432860((Weapon *)v13, &a2.pPlayer, &a2.field_10);
          S202::sub_41F980((S202 *)&a2.field_18, v3);
          S202::sub_41F980((S202 *)&a2.field_1C, v5);
          Weapon::sub_432860((Weapon *)v12, &a2.field_1C, &a2.field_18);
        }
        else
        {
          S202::sub_41F980(&a2, v3);
          S202::sub_41F980((S202 *)&a2.self, v4);
          Weapon::sub_432860((Weapon *)v13, &a2.self, &a2);
          S202::sub_41F980((S202 *)&a2.carMgr, v3 + 1);
          S202::sub_41F980((S202 *)&a2.field_C, v5);
          Weapon::sub_432860((Weapon *)v12, &a2.field_C, &a2.carMgr);
        }
        if ( sub_463690(arg0, (int)v13, (int)v12) )
          return 1;
      }
    }
    ++v4;
    ++v5;
    if ( v4 > dword_662BF8 )
      goto LABEL_15;
  }
}

// 0x466170
char MapRelatedStruct::sub_466170(int arg0) {
  int v2; 
  int v3; 
  int v4; 
  unsigned int v5; 
  CarSystemManager **p_CarSystemManager; 
  void *v7; 
  SpriteS1 *v9; 
  S202 *v10; 
  int *v11; 
  S202 *v12; 
  SpriteS1 *v13; 
  int v14; 
  int *v15; 
  int v16[5]; // [esp-4h] [ebp-4Ch]
  int v17;
  MapRelatedStruct *pMapRelatedStruct;
  S202 a2;
  _DWORD v20[2];
  _DWORD v21[2];
  v2 = dword_662BAC;
  pMapRelatedStruct = this;
  if ( (int)dword_662BAC > a5 )
    return 0;
  while ( 1 )
  {
    v3 = ::arg0;
    if ( ::arg0 <= dword_662BF8 )
      break;
LABEL_15:
    if ( ++v2 > a5 )
      return 0;
  }
  v17 = ::arg0 + 1;
  while ( 1 )
  {
    v4 = pMapRelatedStruct->sub_4653C0( v3, v2, arg0);
    if ( v4 )
    {
      v5 = *(_BYTE *)(v4 + 11) & 0xFC;
      if ( v5 >= 0xB4 && v5 <= 0xD0 )
      {
        if ( v5 == 180 || v5 == 192 || v5 == 196 || v5 == 208 )
        {
          S202::sub_41F980((S202 *)&a2.field_10, v2 + 1);
          S202::sub_41F980((S202 *)&a2.pPlayer, v3);
          Weapon::sub_432860((Weapon *)v21, &a2.pPlayer, &a2.field_10);
          S202::sub_41F980((S202 *)&a2.field_18, v2);
          S202::sub_41F980((S202 *)&a2.field_1C, v17);
          p_CarSystemManager = (CarSystemManager **)&a2.field_18;
          v7 = &a2.field_1C;
        }
        else
        {
          S202::sub_41F980(&a2, v2);
          S202::sub_41F980((S202 *)&a2.self, v3);
          Weapon::sub_432860((Weapon *)v21, &a2.self, &a2);
          S202::sub_41F980((S202 *)&a2.carMgr, v2 + 1);
          S202::sub_41F980((S202 *)&a2.field_C, v17);
          p_CarSystemManager = &a2.carMgr;
          v7 = &a2.field_C;
        }
        Weapon::sub_432860((Weapon *)v20, v7, p_CarSystemManager);
        if ( sub_4BB9C0(dword_662BF0, (int)v21, (int)v20) )
          break;
      }
    }
    ++v3;
    ++v17;
    if ( v3 > dword_662BF8 )
      goto LABEL_15;
  }
  v9 = *(SpriteS1 **)(sub_4828F0((int *)gObject, v5) + 4);
  S202::sub_41F980((S202 *)&a2.field_18, v2);
  v11 = (int *)S202::sub_401B20(v10, (SpriteS1 *)&a2.field_1C, (PublicTransport *)&unk_663164);
  S202::sub_41F980((S202 *)&a2.field_10, v3);
  v13 = S202::sub_401B20(v12, (SpriteS1 *)&a2.pPlayer, (PublicTransport *)&unk_663164);
  v16[0] = v14;
  a2.field_C = (int)v16;
  v15 = (int *)v13;
  S202::sub_41F980((S202 *)v16, arg0);
  SpriteS1::sub_420600(v9, *v15, *v11, v16[0]);
  SpriteS1::sub_4BCB40(v9);
  sub_40FEE0(&dword_5E6874, (int)v9);
  return 1;
}

// 0x466380
char MapRelatedStruct::sub_466380(int a2, int a3, int a4, int a5, int a6) {
  int v6; 
  int v8; 
  bool v9; // cc
  S16_02 **v10; 
  S16_02 **v11; 
  S16_02 **v12; 
  S16_02 **v13; 
  v6 = a4;
  if ( a4 > a5 )
    return 0;
  while ( 1 )
  {
    v8 = a2;
    v9 = a2 < a3;
    if ( a2 <= a3 )
      break;
LABEL_14:
    if ( ++v6 > a5 )
      return 0;
  }
  while ( 1 )
  {
    if ( v9 )
    {
      v10 = sub_465410( v8, v6, a6);
      if ( v10 )
      {
        if ( (*((_BYTE *)v10 + 3) & 4) != 0 )
          return 1;
      }
      v11 = sub_465410( v8 + 1, v6, a6);
      if ( v11 )
      {
        if ( (*((_BYTE *)v11 + 1) & 4) != 0 )
          return 1;
      }
    }
    if ( v6 < a5 )
    {
      v12 = sub_465410( v8, v6, a6);
      if ( v12 )
      {
        if ( (*((_BYTE *)v12 + 7) & 4) != 0 )
          return 1;
      }
      v13 = sub_465410( v8, v6 + 1, a6);
      if ( v13 )
      {
        if ( (*((_BYTE *)v13 + 5) & 4) != 0 )
          return 1;
      }
    }
    v9 = ++v8 < a3;
    if ( v8 > a3 )
      goto LABEL_14;
  }
}

// 0x466430
char MapRelatedStruct::sub_466430(int arg0, int a3, int a2, int a5, int a6) {
  int v6; 
  int v8; 
  bool v9; // cc
  S16_02 **v10; 
  int v11; 
  int v12; 
  int v13; 
  S16_02 **v14; 
  int v15; 
  int v16; 
  int v17; 
  S16_02 **v18; 
  int v19; 
  int v20; 
  int v21; 
  S16_02 **v22; 
  int v23; 
  int v24; 
  int v25; 
  _BYTE v27[28]; // [esp-Ch] [ebp-1Ch]
  v6 = a2;
  if ( a2 > a5 )
    return 0;
  while ( 1 )
  {
    v8 = arg0;
    v9 = arg0 < a3;
    if ( arg0 <= a3 )
      break;
LABEL_22:
    if ( ++v6 > a5 )
      return 0;
  }
  while ( 1 )
  {
    if ( v9 )
    {
      v10 = sub_465410( v8, v6, a6);
      if ( v10 )
      {
        if ( ((unsigned __int16)word_662BEC & *((_WORD *)v10 + 1)) != 0 && !sub_4634B0((int)v10) )
        {
          *(_DWORD *)&v27[8] = v11;
          S202::sub_41F980((S202 *)&v27[8], v8 + 1);
          *(_DWORD *)&v27[4] = v12;
          S202::sub_41F980((S202 *)&v27[4], v6 + 1);
          *(_DWORD *)v27 = v13;
          S202::sub_41F980((S202 *)v27, v6);
          if ( sub_4BB910(dword_662BF0, *(int *)v27, *(int *)&v27[4], *(int *)&v27[8]) )
            return 1;
        }
      }
      v14 = sub_465410( v8 + 1, v6, a6);
      if ( v14 )
      {
        if ( ((unsigned __int16)word_662BEC & *(_WORD *)v14) != 0 && !sub_4634B0((int)v14) )
        {
          *(_DWORD *)&v27[8] = v15;
          S202::sub_41F980((S202 *)&v27[8], v8 + 1);
          *(_DWORD *)&v27[4] = v16;
          S202::sub_41F980((S202 *)&v27[4], v6 + 1);
          *(_DWORD *)v27 = v17;
          S202::sub_41F980((S202 *)v27, v6);
          if ( sub_4BB910(dword_662BF0, *(int *)v27, *(int *)&v27[4], *(int *)&v27[8]) )
            return 1;
        }
      }
    }
    if ( v6 < a5 )
    {
      v18 = sub_465410( v8, v6, a6);
      if ( v18 )
      {
        if ( ((unsigned __int16)word_662BEC & *((_WORD *)v18 + 3)) != 0 && !sub_463480((int)v18) )
        {
          *(_DWORD *)&v27[8] = v19;
          S202::sub_41F980((S202 *)&v27[8], v6 + 1);
          *(_DWORD *)&v27[4] = v20;
          S202::sub_41F980((S202 *)&v27[4], v8 + 1);
          *(_DWORD *)v27 = v21;
          S202::sub_41F980((S202 *)v27, v8);
          if ( sub_4BB860(dword_662BF0, *(int *)v27, *(int *)&v27[4], *(int *)&v27[8]) )
            return 1;
        }
      }
      v22 = sub_465410( v8, v6 + 1, a6);
      if ( v22 )
      {
        if ( ((unsigned __int16)word_662BEC & (_WORD)v22[1]) != 0 && !sub_463480((int)v22) )
        {
          *(_DWORD *)&v27[8] = v23;
          S202::sub_41F980((S202 *)&v27[8], v6 + 1);
          *(_DWORD *)&v27[4] = v24;
          S202::sub_41F980((S202 *)&v27[4], v8 + 1);
          *(_DWORD *)v27 = v25;
          S202::sub_41F980((S202 *)v27, v8);
          if ( sub_4BB860(dword_662BF0, *(int *)v27, *(int *)&v27[4], *(int *)&v27[8]) )
            return 1;
        }
      }
    }
    v9 = ++v8 < a3;
    if ( v8 > a3 )
      goto LABEL_22;
  }
}

// 0x466620
char MapRelatedStruct::sub_466620(void* a2) {
  int v3; 
  SpriteS1 *v4; 
  int v5; 
  int v6; 
  int v7; 
  int v8; 
  unsigned __int8 v9; // al
  unsigned __int8 v10; // cl
  int v11; 
  int v12; 
  int v13; 
  char v15;
  char v16;
  v3 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v15 = 0;
  v4 = sub_42A630((SpriteS1 *)&v16, (S202 *)&a2);
  *(_WORD *)&v5 = Car::sub_403820((Car *)v4, &unk_662CFC);
  v6 = dword_662BAC;
  *(_BYTE *)&a2 = v5 != 0;
  if ( (int)dword_662BAC > a5 )
    return v15;
  while ( 1 )
  {
    v7 = arg0;
    if ( arg0 <= dword_662BF8 )
      break;
LABEL_14:
    if ( ++v6 > a5 )
      return v15;
  }
  while ( 1 )
  {
    v8 = sub_4653C0( v7, v6, v3);
    dword_662B90 = (_WORD *)v8;
    if ( v8 )
      break;
LABEL_13:
    if ( ++v7 > dword_662BF8 )
      goto LABEL_14;
  }
  v9 = *(_BYTE *)(v8 + 11);
  v10 = v9 & 0xFC;
  if ( (v9 & 0xFC) != 0 && v10 < 0xB4u && (v9 & 3) != 0 )
  {
    if ( (_BYTE)a2 )
    {
      v15 = 1;
    }
    else
    {
      v11 = 3 * (v9 >> 2);
      v12 = (unsigned __int8)byte_662DB2[4 * v11];
      v13 = *((unsigned __int8 *)&unk_662DB1 + 4 * v11) - 1;
      dword_662BE0 = (_BYTE *)(4 * v11 + 6696368);
      if ( v12 == v13 )
        v15 = 1;
    }
    goto LABEL_13;
  }
  if ( !(_BYTE)a2 || v10 != 0xFC )
    goto LABEL_13;
  return 2;
}

// 0x466730
char MapRelatedStruct::sub_466730(AudioSourceParams a2) {
  int v3; 
  int v4; 
  int v5; 
  int v6; 
  int v7; 
  char v8; // al
  char v10;
  v3 = AudioSourceParams::sub_41F9D0(&a2);
  v4 = dword_662BAC;
  v5 = v3;
  *(_BYTE *)&a2.field = 0;
  v10 = 0;
  if ( (int)dword_662BAC > a5 )
    return 0;
  while ( 1 )
  {
    v6 = arg0;
    if ( arg0 <= dword_662BF8 )
      break;
LABEL_12:
    if ( ++v4 > a5 )
      return 0;
  }
  while ( 1 )
  {
    v7 = sub_4653C0( v6, v4, v5);
    dword_662B90 = (_WORD *)v7;
    if ( !v7 )
      break;
    v8 = *(_BYTE *)(v7 + 11);
    if ( (v8 & 0xFC) == 0 || (v8 & 0xFCu) >= 0xB4 || (v8 & 3) == 0 )
      break;
    if ( v10 )
      return 1;
    *(_BYTE *)&a2.field = 1;
LABEL_11:
    if ( ++v6 > dword_662BF8 )
      goto LABEL_12;
  }
  if ( !LOBYTE(a2.field) )
  {
    v10 = 1;
    goto LABEL_11;
  }
  return 1;
}

// 0x466910
int MapRelatedStruct::sub_466910(int a2, int a3, _DWORD* a4) {
  Map *Map; 
  int v5; 
  int v6; 
  int v7; 
  unsigned __int8 *v8; 
  int v9; 
  int v10; 
  int v11; 
  unsigned __int8 *i; 
  int result; 
  Map = getMap();
  v5 = *(_DWORD *)getMap()->sub_42A830( a3, a2);
  v6 = Map->field_40008;
  v7 = *(unsigned __int8 *)(v6 + 4 * v5 + 1);
  v8 = (unsigned __int8 *)(v6 + 4 * v5);
  v9 = v7;
  v10 = *v8 - v7 - 1;
  if ( v10 < 0 )
    return 0;
  v11 = Map->field_4000C;
  for ( i = &v8[4 * v10 + 4]; ; i -= 4 )
  {
    result = v11 + 12 * *(_DWORD *)i;
    dword_662B90 = result;
    if ( (*(_BYTE *)(result + 11) & 3) != 0 )
      break;
    if ( --v10 < 0 )
      return 0;
  }
  if ( (*(_BYTE *)(result + 11) & 3) != 2 )
    return 0;
  *a4 = v10 + v9;
  return result;
}

// 0x466990
_WORD* MapRelatedStruct::FindMaxZForTile(int a2, int a3, _DWORD* a4) {
  Map *Map; 
  int v5; 
  int v6; 
  int v7; 
  unsigned __int8 *v8; 
  int v9; 
  int v10; 
  int v11; 
  unsigned __int8 *i; 
  bool v13; // zf
  _WORD *result; 
  Map = getMap();
  v5 = *(_DWORD *)getMap()->sub_42A830( a3, a2);
  v6 = Map->field_40008;
  v7 = *(unsigned __int8 *)(v6 + 4 * v5 + 1);
  v8 = (unsigned __int8 *)(v6 + 4 * v5);
  v9 = v7;
  v10 = *v8 - v7 - 1;
  if ( v10 < 0 )
    return 0;
  v11 = Map->field_4000C;
  for ( i = &v8[4 * v10 + 4]; ; i -= 4 )
  {
    v13 = (*(_BYTE *)(v11 + 12 * *(_DWORD *)i + 11) & 3) == 0;
    result = (_WORD *)(v11 + 12 * *(_DWORD *)i);
    dword_662B90 = result;
    if ( !v13 )
      break;
    if ( --v10 < 0 )
      return 0;
  }
  *a4 = v10 + v9;
  return result;
}

// 0x466A00
_WORD* MapRelatedStruct::sub_466A00(int a2, int a3, int* a4) {
  Map *Map; 
  int v5; 
  int v6; 
  int v7; 
  unsigned __int8 *v8; 
  int v9; 
  int v10; 
  int v11; 
  int v12; 
  int v13; 
  unsigned __int8 *i; 
  bool v15; // zf
  _WORD *result; 
  Map = getMap();
  v5 = *(_DWORD *)getMap()->sub_42A830( a3, a2);
  v6 = Map->field_40008;
  v7 = *(unsigned __int8 *)(v6 + 4 * v5 + 1);
  v8 = (unsigned __int8 *)(v6 + 4 * v5);
  v9 = *a4;
  v10 = v7;
  if ( *a4 < v7 )
    return 0;
  v11 = *v8;
  v12 = v9 < v11 ? v9 - v10 : v11 - v10 - 1;
  if ( v12 < 0 )
    return 0;
  v13 = Map->field_4000C;
  for ( i = &v8[4 * v12 + 4]; ; i -= 4 )
  {
    v15 = (*(_BYTE *)(v13 + 12 * *(_DWORD *)i + 11) & 3) == 0;
    result = (_WORD *)(v13 + 12 * *(_DWORD *)i);
    dword_662B90 = result;
    if ( !v15 )
      break;
    if ( --v12 < 0 )
      return 0;
  }
  *a4 = v12 + v10;
  return result;
}

// 0x466AF0
char MapRelatedStruct::sub_466AF0(int a2, int a3, GameEntity* a4) {
  SpriteS1 *v5; 
  int v6; 
  _WORD *v7; 
  _WORD *v8; 
  int v10; // [esp-8h] [ebp-10h]
  int v11; // [esp-4h] [ebp-Ch]
  int v12;
  v5 = Player::sub_401B40((Player *)&a4, (S202 *)&v12, (int)&unk_662C98);
  v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v5);
  v10 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
  v6 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v7 = (_WORD *)sub_4653C0( v6, v10, v11);
  v8 = v7;
  dword_662B90 = v7;
  if ( !v7 )
    return 5;
  if ( Style::sub_462FB0(gStyle, v7[4] & 0x3FF) )
    return 7;
  if ( (*((_BYTE *)v8 + 11) & 3) != 0 )
    return 0;
  else
    return 5;
}

// 0x466B70
char MapRelatedStruct::sub_466B70(int* a2, S202* pS202) {
  SpriteS1 *FirstElement; 
  int v5; 
  int v6; 
  unsigned __int8 v7; // al
  int v8; 
  int v9; 
  int v10; 
  SpriteS1 *v11; 
  SpriteS1 *v12; 
  S202 **v13; 
  Tango *v14; 
  SpriteS1 *v15; 
  SpriteS1 *v16; 
  int v18; // [esp-8h] [ebp-18h]
  int v19; // [esp-4h] [ebp-14h]
  char v20;
  _BYTE v21[4];
  SpriteS1 pSpriteS1_4;
  FirstElement = pSpriteS1_4.FirstElement;
  v19 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)pSpriteS1_4.FirstElement);
  v18 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&pS202);
  v5 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v6 = sub_4653C0( v5, v18, v19);
  dword_662B90 = v6;
  if ( !v6 )
    return 0;
  v7 = *(_BYTE *)(v6 + 11);
  if ( (v7 & 3) == 0 )
    return 0;
  v8 = 3 * (v7 >> 2);
  v9 = *((unsigned __int8 *)&unk_662DB0 + 12 * (v7 >> 2));
  v10 = 4 * v8 + 6696368;
  dword_662BE0 = v10;
  switch ( v9 )
  {
    case 0:
      return 0;
    case 1:
      v11 = sub_42A630((SpriteS1 *)&a2, (S202 *)&pS202);
      pS202 = (S202 *)Player::sub_401B40((Player *)&unk_662C98, (S202 *)&pS202, (int)v11)->FirstElement;
      break;
    case 2:
      pS202 = (S202 *)sub_42A630(&pSpriteS1_4, (S202 *)&pS202)->FirstElement;
      break;
    case 3:
      v12 = sub_42A630((SpriteS1 *)&v20, (S202 *)&a2);
      v13 = (S202 **)Player::sub_401B40((Player *)&unk_662C98, (S202 *)v21, (int)v12);
      goto LABEL_8;
    case 4:
      v13 = (S202 **)sub_42A630(&pSpriteS1_4, (S202 *)&a2);
LABEL_8:
      pS202 = *v13;
      break;
    default:
      break;
  }
  v14 = (Tango *)sub_4634E0((int *)&pSpriteS1_4, *(_BYTE *)(v10 + 1));
  v15 = Radar::AddBlip(v14, (SpriteS1 *)&a2, (PublicTransport *)&pS202);
  pS202 = (S202 *)S202::sub_401B20((S202 *)v15, (SpriteS1 *)&pS202, (PublicTransport *)(v10 + 4))->FirstElement;
  if ( Player::IsCurrentPlayer((Player *)&pS202, (Player *)&unk_662CFC) )
    pS202 = unk_6631EC;
  v16 = sub_462EA0((SpriteS1 *)&a2, FirstElement);
  FirstElement->FirstElement = S202::sub_401B20((S202 *)&pS202, &pSpriteS1_4, (PublicTransport *)v16)->FirstElement;
  return *(_BYTE *)v10;
}

// 0x466CF0
bool MapRelatedStruct::sub_466CF0(int a2, int a3, int a4) {
  int v4; 
  char v5; // al
  bool result; // al
  v4 = sub_4653C0( a2, a3, a4);
  result = 0;
  if ( v4 )
  {
    v5 = *(_BYTE *)(v4 + 11);
    if ( (v5 & 0xFC) != 0 && (v5 & 0xFCu) < 0xB4 && (v5 & 3) != 0 )
      return 1;
  }
  return result;
}

// 0x466D30
__int16 MapRelatedStruct::sub_466D30(AudioSourceParams a2) {
  int v3; 
  __int16 result; // ax
  int v5; 
  int v6; 
  bool v7; // zf
  int v8; 
  bool v9; // zf
  int v10; 
  int v11; // [esp-8h] [ebp-Ch]
  int v12; // [esp-8h] [ebp-Ch]
  int v13; // [esp-4h] [ebp-8h]
  int v14; // [esp-4h] [ebp-8h]
  v13 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.z);
  v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.y);
  v3 = AudioSourceParams::sub_41F9D0(&a2);
  if ( !sub_466CF0( v3, v11, v13) )
    return 1;
  v14 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.z);
  v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2.y);
  v5 = AudioSourceParams::sub_41F9D0(&a2);
  dword_662B90 = (_WORD *)sub_4653C0( v5, v12, v14);
  v6 = *((unsigned __int8 *)&unk_662DB0 + 12 * (*((unsigned __int8 *)dword_662B90 + 11) >> 2));
  dword_662BE0 = (_BYTE *)(12 * (*((unsigned __int8 *)dword_662B90 + 11) >> 2) + 6696368);
  switch ( v6 )
  {
    case 1:
      v8 = a2.type - 1;
      v7 = a2.type == 1;
      goto LABEL_5;
    case 2:
      v10 = a2.type - 1;
      v9 = a2.type == 1;
      goto LABEL_9;
    case 3:
      v10 = a2.type - 3;
      v9 = a2.type == 3;
LABEL_9:
      if ( v9 )
        goto LABEL_7;
      if ( v10 != 1 )
        goto LABEL_14;
LABEL_11:
      result = 3 - (LOBYTE(a2.field_10) != 0);
      break;
    case 4:
      v8 = a2.type - 3;
      v7 = a2.type == 3;
LABEL_5:
      if ( v7 )
        goto LABEL_11;
      if ( v8 == 1 )
LABEL_7:
        result = (LOBYTE(a2.field_10) != 0) + 2;
      else
LABEL_14:
        result = 0;
      break;
    default:
      goto LABEL_14;
  }
  return result;
}

// 0x466E20
_DWORD* MapRelatedStruct::sub_466E20(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2) {
  SpriteS1 *v6; 
  int v7; 
  SpriteS1 *v8; 
  int *v9; 
  int v10; 
  int v11; 
  _DWORD *result; 
  int v13; 
  int v14; 
  char v15; // cl
  SpriteS1 **v16; 
  _DWORD *v17; 
  int v18; // [esp-8h] [ebp-18h]
  int v19; // [esp-8h] [ebp-18h]
  int v20; // [esp-4h] [ebp-14h]
  SpriteS1 *FirstElement;
  v6 = sub_42A630((SpriteS1 *)&FirstElement, (S202 *)&a2);
  *(_WORD *)&v7 = Car::sub_403820((Car *)v6, &unk_662CFC);
  v8 = a3;
  v9 = arg4;
  if ( v7
    && (v20 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2),
        v18 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3),
        v10 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4),
        sub_466CF0( v10, v18, v20))
    && (FirstElement = sub_462EA0((SpriteS1 *)&FirstElement, &a2)->FirstElement,
        sub_466B70( v9, (S202 *)v8),
        *(_BYTE *)&v11 = Player::CheckCondition((Player *)&FirstElement, &a2),
        v11) )
  {
    result = arg0;
    *arg0 = FirstElement;
  }
  else
  {
    a2 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2) - 1;
    v19 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v13 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
    v14 = sub_4635F0( v13, v19, &a2);
    dword_662B90 = (_WORD *)v14;
    if ( v14 )
    {
      v15 = *(_BYTE *)(v14 + 11);
      if ( (v15 & 0xFC) != 0 && (v15 & 0xFCu) < 0xB4 && (v15 & 3) != 0 )
      {
        S202::sub_41F980((S202 *)&a2, a2);
        FirstElement = *v16;
        sub_466B70( v9, (S202 *)v8);
        *arg0 = FirstElement;
        return arg0;
      }
      else
      {
        S202::sub_41F980((S202 *)&a2, a2 + 1);
        *arg0 = *v17;
        return arg0;
      }
    }
    else
    {
      bitShiftLeft1((int)arg0, 1);
      return arg0;
    }
  }
  return result;
}

// 0x466F70
_DWORD* MapRelatedStruct::sub_466F70(_DWORD* arg0, S202* a2) {
  int v4; 
  int v5; 
  char v7; // al
  int *v8; 
  _DWORD *v9; 
  int v10; // [esp-8h] [ebp-10h]
  int v11;
  S202 a3;
  v10 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
  v4 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v5 = sub_463570( v4, v10, &v11);
  dword_662B90 = (_WORD *)v5;
  if ( v5 )
  {
    v7 = *(_BYTE *)(v5 + 11);
    if ( (v7 & 0xFC) != 0 && (v7 & 0xFCu) < 0xB4 && (v7 & 3) != 0 )
    {
      S202::sub_41F980((S202 *)&v11, v11);
      v11 = *v8;
      sub_466B70( &a2->field_0, (S202 *)a3.field_0);
      *arg0 = v11;
      return arg0;
    }
    else
    {
      S202::sub_41F980(&a3, v11 + 1);
      *arg0 = *v9;
      return arg0;
    }
  }
  else
  {
    bitShiftLeft1((int)arg0, 0);
    return arg0;
  }
}

// 0x467020
__int16 MapRelatedStruct::sub_467020(int*, SpriteS1*, void*, void*, void*) {
    return 0;
}

// 0x467110
int MapRelatedStruct::sub_467110(int* arg0, SpriteS1* a3, int* a4, Player* pPlayer) {
  int *field; 
  int v7; 
  SpriteS1 *FirstElement; 
  SpriteS1 *v9; 
  int v10; 
  int v11; 
  int v12; 
  CarSystemManager *v13; 
  int v14; 
  CarSystemManager *v15; 
  SpriteS1 *v16; 
  CarSystemManager *v17; 
  int v18; 
  SpriteS1 *v19; 
  SpriteS1 *v20; 
  int v21; 
  int v22; 
  int v23; 
  BOOL v24; 
  SpriteS1 *v25; 
  SpriteS1 *v26; 
  int v27; 
  int v28; 
  SpriteS1 *v29; 
  int v30; 
  int v31; 
  CarSystemManager *v32; 
  int v33; 
  CarSystemManager *v34; 
  SpriteS1 *v35; 
  SpriteS1 *v36; 
  SpriteS1 *v37; 
  int v38; 
  int v39; 
  int v40; 
  BOOL v41; 
  SpriteS1 *v42; 
  int v43; 
  int v44; 
  SpriteS1 *v45; 
  int v46; 
  int v47; 
  int v48; 
  BOOL v49; 
  SpriteS1 *v50; 
  int v51; 
  int v52; 
  SpriteS1 *v53; 
  int v54; 
  int v55; 
  CarSystemManager *v56; 
  CarSystemManager *v57; 
  SpriteS1 *v58; 
  SpriteS1 *v59; 
  SpriteS1 *v60; 
  int v61; 
  int v62; 
  SpriteS1 *v63; 
  int v64; 
  int v65; 
  int v66; 
  SpriteS1 *v67; 
  int v68; 
  int v69; 
  int v70; 
  SpriteS1 *v71; 
  int v72; 
  int v73; 
  SpriteS1 *v74; 
  int v75; 
  bool v76; // zf
  SpriteS1 *v77; 
  int v78; 
  int v79; 
  S202 *v80; 
  SpriteS1 *v81; 
  int v82; 
  int v83; 
  int v84; 
  int v85; 
  int result; 
  S202 v87; // [esp-Ch] [ebp-80h]
  unsigned __int16 v88;
  unsigned __int16 v89;
  AudioSourceParams v90;
  S202 pS202;
  S202 v92;
  _BYTE v93[4];
  v7 = *a4;
  FirstElement = a3->FirstElement;
  v87.field_1D = 0;
  v90.field = *arg0;
  field = (int *)v90.field;
  v90.y = (int)FirstElement;
  v90.z = v7;
  sub_467020( (int *)v90.field, FirstElement, &v90.z, (void *)1, 0);
  v9 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
  v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v9);
  v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
  v10 = AudioSourceParams::sub_41F9D0(&v90);
  v11 = sub_4653C0( v10, (int)v87.self, (int)v87.carMgr);
  if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
  {
    v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
    v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
    v12 = AudioSourceParams::sub_41F9D0(&v90);
    v11 = sub_4653C0( v12, (int)v87.self, (int)v87.carMgr);
  }
  v90.type = sub_4633A0( v11, 1);
  v13 = (CarSystemManager *)sub_4725B0((unsigned __int16 *)&v87.field_1E, &v90.type);
  *(_WORD *)&v13 = v13->Index;
  v87.carMgr = v13;
  v87.self = (S202 *)FirstElement;
  v87.field_0 = (int)field;
  v90.field_10 = (int)*sub_463150((SpriteS1 **)&pS202, v87);
  if ( Car::sub_403800((Car *)&v90.field_10, (int)&unk_6630B0) )
  {
    switch ( v90.type )
    {
      case 1:
        goto LABEL_5;
      case 2:
        goto LABEL_9;
      case 3:
        goto LABEL_6;
      case 4:
        goto LABEL_10;
      default:
        break;
    }
  }
  else
  {
    v87.carMgr = (CarSystemManager *)&unk_6630B0;
    if ( sub_4037E0(&v90.field_10) )
    {
      switch ( v90.type )
      {
        case 1:
LABEL_9:
          v90.type = 3;
          break;
        case 2:
LABEL_5:
          v90.type = 4;
          break;
        case 3:
LABEL_10:
          v90.type = 2;
          break;
        case 4:
LABEL_6:
          v90.type = 1;
          break;
        default:
          break;
      }
    }
  }
  *(_WORD *)&v14 = Car::sub_403820((Car *)&v90.field_10, &unk_6630B0);
  v87.carMgr = (CarSystemManager *)&v90.type;
  v87.self = (S202 *)&v87.field_1E;
  if ( v14 )
  {
    *(_WORD *)&v15 = *sub_4725B0((unsigned __int16 *)v87.self, &v87.carMgr->Index);
    v87.carMgr = v15;
    v87.self = (S202 *)FirstElement;
    v87.field_0 = (int)field;
    v90.field_10 = (int)*sub_463210((SpriteS1 **)&pS202, v87);
    v90.field_10 = (int)Player::sub_401B40((Player *)&v90.field_10, &pS202, (int)&unk_6630B0)->FirstElement;
    if ( !Car::sub_403800((Car *)&v90.field_10, (int)&unk_662CFC) )
      goto LABEL_46;
    if ( !Player::sub_40CE70((Player *)&pPlayer, &v90.field_10) )
    {
      v87.carMgr = (CarSystemManager *)v90.type;
      v87.self = (S202 *)pPlayer;
      sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
      field = (int *)v90.field;
      FirstElement = (SpriteS1 *)v90.y;
      pPlayer = (Player *)unk_662CFC;
      goto LABEL_46;
    }
    sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
    v16 = Player::sub_401B40((Player *)&pPlayer, &pS202, (int)&v90.field_10)->FirstElement;
    pPlayer = (Player *)v16;
    v17 = (CarSystemManager *)sub_4633A0( v11, 1);
    v90.type = (int)v17;
    if ( !Player::sub_40CE70((Player *)&pPlayer, &unk_6630B0) )
    {
      v87.carMgr = (CarSystemManager *)v90.type;
      v87.self = (S202 *)v16;
      sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
      field = (int *)v90.field;
      FirstElement = (SpriteS1 *)v90.y;
      pPlayer = (Player *)unk_662CFC;
      goto LABEL_46;
    }
    v18 = v11;
    sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
    v19 = Player::sub_401B40((Player *)&pPlayer, &pS202, (int)&unk_6630B0)->FirstElement;
    pPlayer = (Player *)v19;
    v20 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
    v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v20);
    v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
    v21 = AudioSourceParams::sub_41F9D0(&v90);
    v22 = sub_4653C0( v21, (int)v87.self, (int)v87.carMgr);
    if ( (*(_BYTE *)(v22 + 11) & 0xFC) == 0xFC )
    {
      v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
      v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
      v23 = AudioSourceParams::sub_41F9D0(&v90);
      v22 = sub_4653C0( v23, (int)v87.self, (int)v87.carMgr);
    }
    if ( v22 )
    {
      if ( sub_4632E0( v22, (int)v17, 1) )
        goto LABEL_24;
      v17 = (CarSystemManager *)v90.type;
    }
    v24 = Player::sub_40CE70((Player *)&pPlayer, &unk_662C98);
    v87.carMgr = v17;
    if ( v24 )
    {
      sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
      v25 = Player::sub_401B40((Player *)&pPlayer, &pS202, (int)&unk_662C98)->FirstElement;
    }
    else
    {
      v87.self = (S202 *)v19;
      sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
      v25 = (SpriteS1 *)unk_662CFC;
    }
    pPlayer = (Player *)v25;
LABEL_24:
    v26 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
    v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v26);
    v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
    v27 = AudioSourceParams::sub_41F9D0(&v90);
    v11 = sub_4653C0( v27, (int)v87.self, (int)v87.carMgr);
    if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
    {
      v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
      v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
      v28 = AudioSourceParams::sub_41F9D0(&v90);
      v11 = sub_4653C0( v28, (int)v87.self, (int)v87.carMgr);
    }
    FirstElement = (SpriteS1 *)v90.y;
    v76 = v11 == v18;
    field = (int *)v90.field;
    if ( !v76 )
    {
      sub_467020(
        (int *)v90.field,
        (SpriteS1 *)v90.y,
        &v90.z,
        (void *)1,
        0);
      v29 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
      v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v29);
      v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
      v30 = AudioSourceParams::sub_41F9D0(&v90);
      v11 = sub_4653C0( v30, (int)v87.self, (int)v87.carMgr);
      if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
        goto LABEL_28;
    }
    goto LABEL_46;
  }
  *(_WORD *)&v32 = *sub_4725B0((unsigned __int16 *)v87.self, &v87.carMgr->Index);
  v87.carMgr = v32;
  v87.self = (S202 *)FirstElement;
  v87.field_0 = (int)field;
  v90.field_10 = (int)*sub_463210((SpriteS1 **)&pS202, v87);
  if ( Car::sub_403800((Car *)&v90.field_10, (int)&unk_662CFC) )
  {
    sub_467020( field, FirstElement, &v90.z, (void *)1, (void *)1);
    v33 = v11;
    Player::sub_401B40((Player *)&unk_662C98, &pS202, (int)&v90.field_10);
    v34 = (CarSystemManager *)sub_4725B0(&v88, &v90.type);
    v35 = (SpriteS1 *)sub_40E5A0(v34, (CarSystemManager *)&v87.field_1E, &unk_663108);
    SpriteS1::sub_472C00(v35);
    sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
    v36 = Player::sub_401B40((Player *)&unk_662C98, &pS202, (int)&v90.field_10);
    pPlayer = (Player *)S202::sub_401B20((S202 *)&pPlayer, (SpriteS1 *)&v90.field_14, (PublicTransport *)v36)->FirstElement;
    v37 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
    v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v37);
    v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
    v38 = AudioSourceParams::sub_41F9D0(&v90);
    v39 = sub_4653C0( v38, (int)v87.self, (int)v87.carMgr);
    if ( !v39 )
      goto LABEL_37;
    if ( (*(_BYTE *)(v39 + 11) & 0xFC) == 0xFC )
    {
      v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
      v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
      v40 = AudioSourceParams::sub_41F9D0(&v90);
      v39 = sub_4653C0( v40, (int)v87.self, (int)v87.carMgr);
    }
    if ( !v39 || !sub_4632E0( v39, v90.type, 1) )
    {
LABEL_37:
      v41 = Player::sub_40CE70((Player *)&pPlayer, &unk_662C98);
      v87.carMgr = (CarSystemManager *)v90.type;
      if ( v41 )
      {
        sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
        pPlayer = (Player *)Player::sub_401B40((Player *)&pPlayer, &pS202, (int)&unk_662C98)->FirstElement;
      }
      else
      {
        v87.self = (S202 *)pPlayer;
        sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
        pPlayer = (Player *)unk_662CFC;
      }
    }
    v42 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
    v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v42);
    v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
    v43 = AudioSourceParams::sub_41F9D0(&v90);
    v11 = sub_4653C0( v43, (int)v87.self, (int)v87.carMgr);
    if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
    {
      v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
      v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
      v44 = AudioSourceParams::sub_41F9D0(&v90);
      v11 = sub_4653C0( v44, (int)v87.self, (int)v87.carMgr);
    }
    field = (int *)v90.field;
    v87.carMgr = 0;
    v76 = v11 == v33;
    FirstElement = (SpriteS1 *)v90.y;
    v87.self = (S202 *)1;
    v87.field_0 = (int)&v90.z;
    if ( v76 )
    {
      sub_467020(
        (int *)v90.field,
        (SpriteS1 *)v90.y,
        (void *)v87.field_0,
        v87.self,
        v87.carMgr);
    }
    else
    {
      sub_467020(
        (int *)v90.field,
        (SpriteS1 *)v90.y,
        (void *)v87.field_0,
        v87.self,
        v87.carMgr);
      v45 = Player::sub_401B40((Player *)&v90.z, &pS202, (int)&unk_662C98);
      v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v45);
      v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
      v46 = AudioSourceParams::sub_41F9D0(&v90);
      v11 = sub_4653C0( v46, (int)v87.self, (int)v87.carMgr);
      if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
      {
LABEL_28:
        v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
        v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
        v31 = AudioSourceParams::sub_41F9D0(&v90);
        v11 = sub_4653C0( v31, (int)v87.self, (int)v87.carMgr);
      }
    }
  }
LABEL_46:
  *(_WORD *)&v47 = Car::sub_403820((Car *)&pPlayer, &unk_662CFC);
  if ( v47 )
  {
    do
    {
      if ( !sub_4632E0( v11, v90.type, 1) || v87.field_1D )
      {
        v87.field_1D = 0;
        v66 = v11;
        if ( Player::sub_40CE70((Player *)&pPlayer, &unk_662C98) )
        {
          sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
          v67 = Player::sub_401B40((Player *)&v90.z, (S202 *)&v92.carMgr, (int)&unk_662C98);
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v67);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v68 = AudioSourceParams::sub_41F9D0(&v90);
          v69 = sub_4653C0( v68, (int)v87.self, (int)v87.carMgr);
          if ( (*(_BYTE *)(v69 + 11) & 0xFC) == 0xFC )
          {
            v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
            v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
            v70 = AudioSourceParams::sub_41F9D0(&v90);
            v69 = sub_4653C0( v70, (int)v87.self, (int)v87.carMgr);
          }
          v90.type = sub_4633A0( v69, 1);
          sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
          pPlayer = (Player *)Player::sub_401B40((Player *)&pPlayer, (S202 *)&v92.field_C, (int)&unk_662C98)->FirstElement;
          v71 = Player::sub_401B40((Player *)&v90.z, (S202 *)&v92.field_10, (int)&unk_662C98);
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v71);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v72 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v72, (int)v87.self, (int)v87.carMgr);
          if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
          {
            v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
            v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
            v73 = AudioSourceParams::sub_41F9D0(&v90);
            v11 = sub_4653C0( v73, (int)v87.self, (int)v87.carMgr);
          }
          field = (int *)v90.field;
          v76 = v11 == v66;
          FirstElement = (SpriteS1 *)v90.y;
          if ( v76 )
            goto LABEL_80;
          sub_467020(
            (int *)v90.field,
            (SpriteS1 *)v90.y,
            &v90.z,
            (void *)1,
            0);
          v74 = Player::sub_401B40((Player *)&v90.z, (S202 *)&v92.pPlayer, (int)&unk_662C98);
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v74);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v75 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v75, (int)v87.self, (int)v87.carMgr);
          v76 = (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC;
        }
        else
        {
          if ( Car::sub_403800((Car *)&pPlayer, (int)&unk_6630B0) )
          {
            sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
            v77 = Player::sub_401B40((Player *)&v90.z, (S202 *)&v92.field_18, (int)&unk_662C98);
            v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v77);
            v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
            v78 = AudioSourceParams::sub_41F9D0(&v90);
            v11 = sub_4653C0( v78, (int)v87.self, (int)v87.carMgr);
            if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
            {
              v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
              v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
              v79 = AudioSourceParams::sub_41F9D0(&v90);
              v11 = sub_4653C0( v79, (int)v87.self, (int)v87.carMgr);
            }
            v90.type = sub_4633A0( v11, 1);
            v80 = (S202 *)Player::sub_401B40((Player *)&pPlayer, (S202 *)&v92.field_1C, (int)&unk_6630B0)->FirstElement;
          }
          else
          {
            v80 = (S202 *)pPlayer;
          }
          v87.self = v80;
          sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
          bitShiftLeft1((int)&pS202, 0);
          field = (int *)v90.field;
          v76 = v11 == v66;
          FirstElement = (SpriteS1 *)v90.y;
          pPlayer = (Player *)pS202.field_0;
          if ( v76 )
            goto LABEL_80;
          sub_467020(
            (int *)v90.field,
            (SpriteS1 *)v90.y,
            &v90.z,
            (void *)1,
            0);
          v81 = Player::sub_401B40((Player *)&v90.z, (S202 *)v93, (int)&unk_662C98);
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v81);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v82 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v82, (int)v87.self, (int)v87.carMgr);
          v76 = (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC;
        }
        if ( v76 )
        {
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v83 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v83, (int)v87.self, (int)v87.carMgr);
        }
      }
      else
      {
        v48 = v11;
        v49 = Player::sub_40CE70((Player *)&pPlayer, &unk_662C98);
        v87.carMgr = (CarSystemManager *)v90.type;
        if ( v49 )
        {
          sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
          pPlayer = (Player *)Player::sub_401B40((Player *)&pPlayer, (S202 *)&pS202.self, (int)&unk_662C98)->FirstElement;
        }
        else
        {
          v87.self = (S202 *)pPlayer;
          sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
          pPlayer = (Player *)unk_662CFC;
        }
        v50 = Player::sub_401B40((Player *)&v90.z, (S202 *)&pS202.carMgr, (int)&unk_662C98);
        v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v50);
        v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
        v51 = AudioSourceParams::sub_41F9D0(&v90);
        v11 = sub_4653C0( v51, (int)v87.self, (int)v87.carMgr);
        if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
        {
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v52 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v52, (int)v87.self, (int)v87.carMgr);
        }
        field = (int *)v90.field;
        v76 = v11 == v48;
        FirstElement = (SpriteS1 *)v90.y;
        if ( !v76 )
        {
          sub_467020(
            (int *)v90.field,
            (SpriteS1 *)v90.y,
            &v90.z,
            (void *)1,
            0);
          v53 = Player::sub_401B40((Player *)&v90.z, (S202 *)&pS202.field_C, (int)&unk_662C98);
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v53);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v54 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v54, (int)v87.self, (int)v87.carMgr);
          if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
          {
            v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
            v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
            v55 = AudioSourceParams::sub_41F9D0(&v90);
            v11 = sub_4653C0( v55, (int)v87.self, (int)v87.carMgr);
          }
        }
        if ( !sub_4632E0( v11, v90.type, 1) )
        {
          v90.field_14 = v11;
          *(_WORD *)&v56 = *sub_4725B0(&v88, &v90.type);
          v87.carMgr = v56;
          v87.self = (S202 *)FirstElement;
          v87.field_0 = (int)field;
          v90.field_10 = (int)*sub_463210((SpriteS1 **)&pS202.field_10, v87);
          Player::sub_401B40((Player *)&unk_662C98, (S202 *)&pS202.pPlayer, (int)&v90.field_10);
          v57 = (CarSystemManager *)sub_4725B0(&v89, &v90.type);
          v58 = (SpriteS1 *)sub_40E5A0(v57, (CarSystemManager *)&v87.field_1E, &unk_663108);
          SpriteS1::sub_472C00(v58);
          sub_4630D0((SpriteS1 *)&v90, (SpriteS1 *)&v90.y);
          v59 = Player::sub_401B40((Player *)&unk_662C98, (S202 *)&pS202.field_18, (int)&v90.field_10);
          pPlayer = (Player *)S202::sub_401B20((S202 *)&pPlayer, (SpriteS1 *)&pS202.field_1C, (PublicTransport *)v59)->FirstElement;
          v60 = Player::sub_401B40((Player *)&v90.z, &v92, (int)&unk_662C98);
          v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v60);
          v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
          v61 = AudioSourceParams::sub_41F9D0(&v90);
          v11 = sub_4653C0( v61, (int)v87.self, (int)v87.carMgr);
          if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
          {
            v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
            v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
            v62 = AudioSourceParams::sub_41F9D0(&v90);
            v11 = sub_4653C0( v62, (int)v87.self, (int)v87.carMgr);
          }
          field = (int *)v90.field;
          FirstElement = (SpriteS1 *)v90.y;
          if ( v11 != v90.field_14 )
          {
            sub_467020(
              (int *)v90.field,
              (SpriteS1 *)v90.y,
              &v90.z,
              (void *)1,
              0);
            v63 = Player::sub_401B40((Player *)&v90.z, (S202 *)&v92.self, (int)&unk_662C98);
            v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v63);
            v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
            v64 = AudioSourceParams::sub_41F9D0(&v90);
            v11 = sub_4653C0( v64, (int)v87.self, (int)v87.carMgr);
            if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
            {
              v87.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.z);
              v87.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v90.y);
              v65 = AudioSourceParams::sub_41F9D0(&v90);
              v11 = sub_4653C0( v65, (int)v87.self, (int)v87.carMgr);
            }
          }
          v87.field_1D = 1;
        }
      }
LABEL_80:
      *(_WORD *)&v84 = Car::sub_403820((Car *)&pPlayer, &unk_662CFC);
    }
    while ( v84 );
  }
  v87.carMgr = (CarSystemManager *)v90.z;
  *arg0 = (int)field;
  a3->FirstElement = FirstElement;
  v85 = *sub_466E20( &pPlayer, field, FirstElement, (int)v87.carMgr);
  result = v90.type;
  *a4 = v85;
  return result;
}

// 0x467F80
int MapRelatedStruct::sub_467F80(int** arg0, SpriteS1** a3, int* a4, Player* a5) {
  int *field; 
  SpriteS1 *v7; 
  SpriteS1 *v8; 
  int v9; 
  int v10; 
  int v11; 
  CarSystemManager *v12; 
  int v13; 
  CarSystemManager *v14; 
  BOOL v15; 
  SpriteS1 *v16; 
  int v17; 
  int v18; 
  int v19; 
  char v20; // al
  CarSystemManager *v21; 
  BOOL v22; 
  SpriteS1 *v23; 
  int v24; 
  int v25; 
  SpriteS1 *v26; 
  int v27; 
  int v28; 
  CarSystemManager *v29; 
  int v30; 
  CarSystemManager *v31; 
  SpriteS1 *v32; 
  SpriteS1 *v33; 
  SpriteS1 *v34; 
  int v35; 
  int v36; 
  int v37; 
  BOOL v38; 
  SpriteS1 *v39; 
  int v40; 
  int v41; 
  SpriteS1 *v42; 
  int v43; 
  int v44; 
  BOOL v45; 
  SpriteS1 *v46; 
  int v47; 
  int v48; 
  int v49; 
  SpriteS1 *v50; 
  int v51; 
  int v52; 
  int v53; 
  CarSystemManager *v54; 
  CarSystemManager *v55; 
  SpriteS1 *v56; 
  CarSystemManager *v57; 
  SpriteS1 *v58; 
  SpriteS1 *v59; 
  SpriteS1 *v60; 
  int v61; 
  int v62; 
  SpriteS1 *v63; 
  int v64; 
  int v65; 
  CarSystemManager *v66; 
  SpriteS1 *v67; 
  SpriteS1 *v68; 
  int v69; 
  int v70; 
  SpriteS1 *v71; 
  SpriteS1 *v72; 
  SpriteS1 *v73; 
  SpriteS1 *v74; 
  int v75; 
  int v76; 
  SpriteS1 *v77; 
  SpriteS1 *v78; 
  int v79; 
  int v80; 
  SpriteS1 *FirstElement; 
  BOOL v82; 
  SpriteS1 *v83; 
  SpriteS1 *v84; 
  int v85; 
  int v86; 
  SpriteS1 *v87; 
  int v88; 
  bool v89; // zf
  SpriteS1 *v90; 
  int v91; 
  int v92; 
  S202 *v93; 
  SpriteS1 *v94; 
  int v95; 
  int v96; 
  int v97; 
  S202 v99; // [esp-Ch] [ebp-BCh]
  AudioSourceParams v100;
  SpriteS1 *v101;
  CarSystemManager pCarSystemManager;
  char v103;
  _BYTE v104[4];
  char v105;
  _BYTE v106[4];
  field = *arg0;
  v100.y = *a4;
  *(_DWORD *)&pCarSystemManager.field_2 = v100.y;
  v7 = *a3;
  HIBYTE(v100.field_10) = 0;
  v100.field = (int)field;
  *(Weapon **)((char *)&pCarSystemManager.Weapon + 2) = (Weapon *)field;
  *(_DWORD *)&v99.field_1C = v7;
  *(int *)((char *)&pCarSystemManager.field_4 + 2) = (int)v7;
  sub_467020( field, v7, &v100.y, 0, 0);
  v8 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
  v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v8);
  v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
  v9 = AudioSourceParams::sub_41F9D0(&v100);
  v10 = sub_4653C0( v9, (int)v99.self, (int)v99.carMgr);
  if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
  {
    v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
    v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
    v11 = AudioSourceParams::sub_41F9D0(&v100);
    v10 = sub_4653C0( v11, (int)v99.self, (int)v99.carMgr);
  }
  v100.z = sub_4633A0( v10, 0);
  *(_WORD *)&v12 = *sub_4725B0(&pCarSystemManager.Index, &v100.z);
  v99.carMgr = v12;
  v99.self = (S202 *)v7;
  v99.field_0 = (int)field;
  v101 = *sub_463150((SpriteS1 **)&v100.type, v99);
  if ( Car::sub_403800((Car *)&v101, (int)&unk_6630B0) )
  {
    switch ( v100.z )
    {
      case 1:
        goto LABEL_5;
      case 2:
        goto LABEL_9;
      case 3:
        goto LABEL_6;
      case 4:
        goto LABEL_10;
      default:
        break;
    }
  }
  else
  {
    v99.carMgr = (CarSystemManager *)&unk_6630B0;
    if ( sub_4037E0(&v101) )
    {
      switch ( v100.z )
      {
        case 1:
LABEL_9:
          v100.z = 4;
          break;
        case 2:
LABEL_5:
          v100.z = 3;
          break;
        case 3:
LABEL_10:
          v100.z = 1;
          break;
        case 4:
LABEL_6:
          v100.z = 2;
          break;
        default:
          break;
      }
    }
  }
  *(_WORD *)&v13 = Car::sub_403820((Car *)&v101, &unk_6630B0);
  v99.carMgr = (CarSystemManager *)&v100.z;
  v99.self = (S202 *)&pCarSystemManager;
  if ( v13 )
  {
    v101 = (SpriteS1 *)v10;
    *(_WORD *)&v14 = *sub_4725B0((unsigned __int16 *)v99.self, &v99.carMgr->Index);
    v99.carMgr = v14;
    v99.self = (S202 *)v7;
    v99.field_0 = (int)field;
    v100.field_14 = (int)*sub_463210((SpriteS1 **)&v100.type, v99);
    if ( Car::sub_403800((Car *)&v100.field_14, (int)&unk_662CFC) )
    {
      v15 = Player::sub_40CE70((Player *)&a5, &v100.field_14);
      v99.carMgr = (CarSystemManager *)v100.z;
      if ( v15 )
      {
        sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
        a5 = (Player *)Player::sub_401B40((Player *)&a5, (S202 *)&v100.type, (int)&v100.field_14)->FirstElement;
      }
      else
      {
        v99.self = (S202 *)a5;
        sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
        a5 = (Player *)unk_662CFC;
      }
      field = (int *)v100.field;
      v7 = *(SpriteS1 **)&v99.field_1C;
    }
    v16 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
    v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v16);
    v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
    v17 = AudioSourceParams::sub_41F9D0(&v100);
    v18 = sub_4653C0( v17, (int)v99.self, (int)v99.carMgr);
    if ( (*(_BYTE *)(v18 + 11) & 0xFC) == 0xFC )
    {
      v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
      v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
      v19 = AudioSourceParams::sub_41F9D0(&v100);
      v18 = sub_4653C0( v19, (int)v99.self, (int)v99.carMgr);
    }
    v20 = sub_4632E0( v18, v100.z, 0);
    v21 = (CarSystemManager *)v100.z;
    if ( !v20 )
    {
      v22 = Player::sub_40CE70((Player *)&a5, &unk_662C98);
      v99.carMgr = v21;
      if ( v22 )
      {
        sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
        a5 = (Player *)Player::sub_401B40((Player *)&a5, (S202 *)&v100.type, (int)&unk_662C98)->FirstElement;
      }
      else
      {
        v99.self = (S202 *)a5;
        sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
        a5 = (Player *)unk_662CFC;
      }
      field = (int *)v100.field;
      v7 = *(SpriteS1 **)&v99.field_1C;
    }
    v23 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
    v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v23);
    v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
    v24 = AudioSourceParams::sub_41F9D0(&v100);
    v10 = sub_4653C0( v24, (int)v99.self, (int)v99.carMgr);
    if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
    {
      v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
      v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
      v25 = AudioSourceParams::sub_41F9D0(&v100);
      v10 = sub_4653C0( v25, (int)v99.self, (int)v99.carMgr);
    }
    if ( (SpriteS1 *)v10 != v101 )
    {
      sub_467020( field, v7, &v100.y, 0, 0);
      v26 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
      v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v26);
      v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
      v27 = AudioSourceParams::sub_41F9D0(&v100);
      v10 = sub_4653C0( v27, (int)v99.self, (int)v99.carMgr);
      if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
        goto LABEL_28;
    }
  }
  else
  {
    *(_WORD *)&v29 = *sub_4725B0((unsigned __int16 *)v99.self, &v99.carMgr->Index);
    v99.carMgr = v29;
    v99.self = (S202 *)v7;
    v99.field_0 = (int)field;
    v100.field_14 = (int)*sub_463210((SpriteS1 **)&v100.type, v99);
    if ( Car::sub_403800((Car *)&v100.field_14, (int)&unk_662CFC) )
    {
      sub_467020( field, v7, &v100.y, 0, (void *)1);
      v30 = v10;
      Player::sub_401B40((Player *)&unk_662C98, (S202 *)&v100.type, (int)&v100.field_14);
      v31 = (CarSystemManager *)sub_4725B0((unsigned __int16 *)&pCarSystemManager.field_10, &v100.z);
      v32 = (SpriteS1 *)sub_40E5A0(v31, &pCarSystemManager, &unk_663108);
      SpriteS1::sub_472C00(v32);
      sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
      v33 = Player::sub_401B40((Player *)&unk_662C98, (S202 *)&v100.type, (int)&v100.field_14);
      a5 = (Player *)S202::sub_401B20((S202 *)&a5, (SpriteS1 *)&v101, (PublicTransport *)v33)->FirstElement;
      v34 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
      v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v34);
      v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
      v35 = AudioSourceParams::sub_41F9D0(&v100);
      v36 = sub_4653C0( v35, (int)v99.self, (int)v99.carMgr);
      if ( !v36 )
        goto LABEL_35;
      if ( (*(_BYTE *)(v36 + 11) & 0xFC) == 0xFC )
      {
        v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
        v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
        v37 = AudioSourceParams::sub_41F9D0(&v100);
        v36 = sub_4653C0( v37, (int)v99.self, (int)v99.carMgr);
      }
      if ( !v36 || !sub_4632E0( v36, v100.z, 0) )
      {
LABEL_35:
        v38 = Player::sub_40CE70((Player *)&a5, &unk_662C98);
        v99.carMgr = (CarSystemManager *)v100.z;
        if ( v38 )
        {
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          a5 = (Player *)Player::sub_401B40((Player *)&a5, (S202 *)&v100.type, (int)&unk_662C98)->FirstElement;
        }
        else
        {
          v99.self = (S202 *)a5;
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          a5 = (Player *)unk_662CFC;
        }
      }
      v39 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
      v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v39);
      v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
      v40 = AudioSourceParams::sub_41F9D0(&v100);
      v10 = sub_4653C0( v40, (int)v99.self, (int)v99.carMgr);
      if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
      {
        v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
        v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
        v41 = AudioSourceParams::sub_41F9D0(&v100);
        v10 = sub_4653C0( v41, (int)v99.self, (int)v99.carMgr);
      }
      field = (int *)v100.field;
      v99.carMgr = 0;
      v89 = v10 == v30;
      v7 = *(SpriteS1 **)&v99.field_1C;
      v99.self = 0;
      v99.field_0 = (int)&v100.y;
      if ( v89 )
      {
        sub_467020(
          (int *)v100.field,
          *(SpriteS1 **)&v99.field_1C,
          (void *)v99.field_0,
          v99.self,
          v99.carMgr);
      }
      else
      {
        sub_467020(
          (int *)v100.field,
          *(SpriteS1 **)&v99.field_1C,
          (void *)v99.field_0,
          v99.self,
          v99.carMgr);
        v42 = Player::sub_401B40((Player *)&v100.y, (S202 *)&v100.type, (int)&unk_662C98);
        v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v42);
        v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
        v43 = AudioSourceParams::sub_41F9D0(&v100);
        v10 = sub_4653C0( v43, (int)v99.self, (int)v99.carMgr);
        if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
        {
LABEL_28:
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v28 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v28, (int)v99.self, (int)v99.carMgr);
        }
      }
    }
  }
  *(_WORD *)&v44 = Car::sub_403820((Car *)&a5, &unk_662CFC);
  if ( v44 )
  {
    do
    {
      if ( !sub_4632E0( v10, v100.z, 0) || HIBYTE(v100.field_10) )
      {
        v66 = 0;
        HIBYTE(v100.field_10) = 0;
        switch ( v100.z )
        {
          case 1:
          case 2:
            v67 = Player::sub_401B40(
                    (Player *)&pCarSystemManager.field_2,
                    (S202 *)((char *)&pCarSystemManager.field_44 + 2),
                    (int)&unk_662C98);
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v67);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)((char *)&pCarSystemManager.field_4 + 2));
            v68 = S202::sub_401B20(
                    (S202 *)((char *)&pCarSystemManager.Weapon + 2),
                    (SpriteS1 *)&v103,
                    (PublicTransport *)&unk_662C98);
            v69 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v68);
            v70 = gMapRelatedStruct->sub_4653C0( v69, (int)v99.self, (int)v99.carMgr);
            v10 = v70;
            if ( !v70
              || (v66 = (CarSystemManager *)sub_4633A0( v70, 0), v66 != (CarSystemManager *)3) )
            {
              v71 = Player::sub_401B40(
                      (Player *)&pCarSystemManager.field_2,
                      (S202 *)((char *)&pCarSystemManager.Player + 2),
                      (int)&unk_662C98);
              v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v71);
              v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)((char *)&pCarSystemManager.field_4
                                                                                   + 2));
              v72 = Player::sub_401B40(
                      (Player *)((char *)&pCarSystemManager.Weapon + 2),
                      (S202 *)((char *)&pCarSystemManager.field_20 + 2),
                      (int)&unk_662C98);
              goto LABEL_72;
            }
            break;
          case 3:
          case 4:
            v73 = Player::sub_401B40(
                    (Player *)&pCarSystemManager.field_2,
                    (S202 *)((char *)&pCarSystemManager.RecycledCars + 2),
                    (int)&unk_662C98);
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v73);
            v74 = S202::sub_401B20(
                    (S202 *)((char *)&pCarSystemManager.field_4 + 2),
                    (SpriteS1 *)((char *)&pCarSystemManager.field_30 + 2),
                    (PublicTransport *)&unk_662C98);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v74);
            v75 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)((char *)&pCarSystemManager.Weapon + 2));
            v76 = gMapRelatedStruct->sub_4653C0( v75, (int)v99.self, (int)v99.carMgr);
            v10 = v76;
            if ( !v76
              || (v66 = (CarSystemManager *)sub_4633A0( v76, 0), v66 != (CarSystemManager *)2) )
            {
              v77 = Player::sub_401B40(
                      (Player *)&pCarSystemManager.field_2,
                      (S202 *)((char *)&pCarSystemManager.field_38 + 2),
                      (int)&unk_662C98);
              v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v77);
              v78 = Player::sub_401B40(
                      (Player *)((char *)&pCarSystemManager.field_4 + 2),
                      (S202 *)((char *)&pCarSystemManager.RecycledCars_1 + 2),
                      (int)&unk_662C98);
              v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v78);
              v72 = (SpriteS1 *)((char *)&pCarSystemManager.Weapon + 2);
LABEL_72:
              v79 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v72);
              v10 = gMapRelatedStruct->sub_4653C0( v79, (int)v99.self, (int)v99.carMgr);
              v66 = (CarSystemManager *)sub_4633A0( v10, 0);
            }
            break;
          default:
            break;
        }
        v80 = v10;
        if ( Player::sub_40CE70((Player *)&a5, &unk_662C98) )
        {
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          v100.z = (int)v66;
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          FirstElement = Player::sub_401B40(
                           (Player *)&a5,
                           (S202 *)((char *)&pCarSystemManager.field_48 + 2),
                           (int)&unk_662C98)->FirstElement;
          a5 = (Player *)FirstElement;
          v82 = Player::sub_40CE70((Player *)&a5, &unk_662C98);
          v99.carMgr = v66;
          if ( v82 )
          {
            sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
            v83 = Player::sub_401B40((Player *)&a5, (S202 *)&pCarSystemManager.field_52, (int)&unk_662C98)->FirstElement;
          }
          else
          {
            v99.self = (S202 *)FirstElement;
            sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
            v83 = (SpriteS1 *)unk_662CFC;
          }
          a5 = (Player *)v83;
          v84 = Player::sub_401B40(
                  (Player *)&v100.y,
                  (S202 *)((char *)&pCarSystemManager.CarType + 2),
                  (int)&unk_662C98);
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v84);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v85 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v85, (int)v99.self, (int)v99.carMgr);
          if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
          {
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
            v86 = AudioSourceParams::sub_41F9D0(&v100);
            v10 = sub_4653C0( v86, (int)v99.self, (int)v99.carMgr);
          }
          field = (int *)v100.field;
          v89 = v10 == v80;
          v7 = *(SpriteS1 **)&v99.field_1C;
          if ( v89 )
            goto LABEL_90;
          sub_467020(
            (int *)v100.field,
            *(SpriteS1 **)&v99.field_1C,
            &v100.y,
            0,
            0);
          v87 = Player::sub_401B40(
                  (Player *)&v100.y,
                  (S202 *)((char *)&pCarSystemManager.field_60 + 2),
                  (int)&unk_662C98);
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v87);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v88 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v88, (int)v99.self, (int)v99.carMgr);
          v89 = (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC;
        }
        else
        {
          if ( Car::sub_403800((Car *)&a5, (int)&unk_6630B0) )
          {
            sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
            v90 = Player::sub_401B40(
                    (Player *)&v100.y,
                    (S202 *)&pCarSystemManager.field_6A,
                    (int)&unk_662C98);
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v90);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
            v91 = AudioSourceParams::sub_41F9D0(&v100);
            v10 = sub_4653C0( v91, (int)v99.self, (int)v99.carMgr);
            if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
            {
              v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
              v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
              v92 = AudioSourceParams::sub_41F9D0(&v100);
              v10 = sub_4653C0( v92, (int)v99.self, (int)v99.carMgr);
            }
            v100.z = (int)v66;
            v93 = (S202 *)Player::sub_401B40((Player *)&a5, (S202 *)v104, (int)&unk_6630B0)->FirstElement;
          }
          else
          {
            v93 = (S202 *)a5;
          }
          v99.self = v93;
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          bitShiftLeft1((int)&v100.type, 0);
          field = (int *)v100.field;
          v89 = v10 == v80;
          v7 = *(SpriteS1 **)&v99.field_1C;
          a5 = (Player *)v100.type;
          if ( v89 )
            goto LABEL_90;
          sub_467020(
            (int *)v100.field,
            *(SpriteS1 **)&v99.field_1C,
            &v100.y,
            0,
            0);
          v94 = Player::sub_401B40(
                  (Player *)&v100.y,
                  (S202 *)((char *)&pCarSystemManager.ID + 2),
                  (int)&unk_662C98);
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v94);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v95 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v95, (int)v99.self, (int)v99.carMgr);
          v89 = (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC;
        }
        if ( v89 )
        {
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v96 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v96, (int)v99.self, (int)v99.carMgr);
        }
      }
      else
      {
        v101 = (SpriteS1 *)v10;
        *(Weapon **)((char *)&pCarSystemManager.Weapon + 2) = (Weapon *)field;
        *(int *)((char *)&pCarSystemManager.field_4 + 2) = (int)v7;
        *(_DWORD *)&pCarSystemManager.field_2 = v100.y;
        v45 = Player::sub_40CE70((Player *)&a5, &unk_662C98);
        v99.carMgr = (CarSystemManager *)v100.z;
        if ( v45 )
        {
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          a5 = (Player *)Player::sub_401B40(
                           (Player *)&a5,
                           (S202 *)((char *)&pCarSystemManager.field_2C + 2),
                           (int)&unk_662C98)->FirstElement;
        }
        else
        {
          v99.self = (S202 *)a5;
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          a5 = (Player *)unk_662CFC;
        }
        v46 = Player::sub_401B40((Player *)&v100.y, (S202 *)v106, (int)&unk_662C98);
        v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v46);
        v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
        v47 = AudioSourceParams::sub_41F9D0(&v100);
        v48 = sub_4653C0( v47, (int)v99.self, (int)v99.carMgr);
        field = (int *)v100.field;
        v7 = *(SpriteS1 **)&v99.field_1C;
        v10 = v48;
        if ( !v48 )
          goto LABEL_59;
        if ( (*(_BYTE *)(v48 + 11) & 0xFC) == 0xFC )
        {
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v49 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v49, (int)v99.self, (int)v99.carMgr);
        }
        if ( (SpriteS1 *)v10 != v101 )
        {
          sub_467020( field, v7, &v100.y, 0, 0);
          v50 = Player::sub_401B40(
                  (Player *)&v100.y,
                  (S202 *)((char *)&pCarSystemManager.field_24 + 2),
                  (int)&unk_662C98);
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v50);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v51 = AudioSourceParams::sub_41F9D0(&v100);
          v52 = sub_4653C0( v51, (int)v99.self, (int)v99.carMgr);
          v10 = v52;
          if ( !v52 )
            goto LABEL_59;
          if ( (*(_BYTE *)(v52 + 11) & 0xFC) == 0xFC )
          {
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
            v53 = AudioSourceParams::sub_41F9D0(&v100);
            v10 = sub_4653C0( v53, (int)v99.self, (int)v99.carMgr);
          }
        }
        if ( !v10 || !sub_4632E0( v10, v100.z, 0) )
        {
LABEL_59:
          v101 = (SpriteS1 *)v10;
          *(_WORD *)&v54 = *sub_4725B0((unsigned __int16 *)&pCarSystemManager.field_10, &v100.z);
          v99.carMgr = v54;
          v99.self = (S202 *)v7;
          v99.field_0 = (int)field;
          v100.field_14 = (int)*sub_463210((SpriteS1 **)((char *)&pCarSystemManager.SpriteS1_0 + 2), v99);
          v55 = (CarSystemManager *)sub_4725B0(
                                      (unsigned __int16 *)&pCarSystemManager.field_1C,
                                      &v100.z);
          v56 = (SpriteS1 *)sub_40E5A0(v55, &pCarSystemManager, &unk_663108);
          SpriteS1::sub_472C00(v56);
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          Player::sub_401B40(
            (Player *)&unk_662C98,
            (S202 *)((char *)&pCarSystemManager.field_1C + 2),
            (int)&v100.field_14);
          v57 = (CarSystemManager *)sub_4725B0((unsigned __int16 *)&pCarSystemManager.ID, &v100.z);
          v58 = (SpriteS1 *)sub_40E5A0(v57, (CarSystemManager *)&pCarSystemManager.field_12, &unk_663108);
          SpriteS1::sub_472C00(v58);
          sub_4630D0((SpriteS1 *)&v100, (SpriteS1 *)&v99.field_1C);
          v99.carMgr = (CarSystemManager *)Player::sub_401B40(
                                                       (Player *)&unk_662C98,
                                                       (S202 *)&pCarSystemManager.field_56,
                                                       (int)&v100.field_14);
          v59 = S202::sub_401B20((S202 *)&a5, (SpriteS1 *)&v105, (PublicTransport *)&unk_662C98);
          a5 = (Player *)S202::sub_401B20(
                           (S202 *)v59,
                           (SpriteS1 *)((char *)&pCarSystemManager.UnitCars + 2),
                           (PublicTransport *)v99.carMgr)->FirstElement;
          v100.y = *(_DWORD *)&pCarSystemManager.field_2;
          v60 = Player::sub_401B40(
                  (Player *)&v100.y,
                  (S202 *)((char *)&pCarSystemManager.MissionCars + 2),
                  (int)&unk_662C98);
          v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v60);
          v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
          v61 = AudioSourceParams::sub_41F9D0(&v100);
          v10 = sub_4653C0( v61, (int)v99.self, (int)v99.carMgr);
          if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
          {
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
            v62 = AudioSourceParams::sub_41F9D0(&v100);
            v10 = sub_4653C0( v62, (int)v99.self, (int)v99.carMgr);
          }
          field = (int *)v100.field;
          v7 = *(SpriteS1 **)&v99.field_1C;
          if ( (SpriteS1 *)v10 != v101 )
          {
            sub_467020(
              (int *)v100.field,
              *(SpriteS1 **)&v99.field_1C,
              &v100.y,
              0,
              0);
            v63 = Player::sub_401B40(
                    (Player *)&v100.y,
                    (S202 *)&pCarSystemManager.field_5E,
                    (int)&unk_662C98);
            v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)v63);
            v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
            v64 = AudioSourceParams::sub_41F9D0(&v100);
            v10 = sub_4653C0( v64, (int)v99.self, (int)v99.carMgr);
            if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
            {
              v99.carMgr = (CarSystemManager *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v100.y);
              v99.self = (S202 *)AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v99.field_1C);
              v65 = AudioSourceParams::sub_41F9D0(&v100);
              v10 = sub_4653C0( v65, (int)v99.self, (int)v99.carMgr);
            }
          }
          HIBYTE(v100.field_10) = 1;
        }
      }
LABEL_90:
      *(_WORD *)&v97 = Car::sub_403820((Car *)&a5, &unk_662CFC);
    }
    while ( v97 );
  }
  v99.carMgr = (CarSystemManager *)v100.y;
  *arg0 = field;
  *a3 = v7;
  *a4 = *sub_466E20(
           (int *)((char *)&pCarSystemManager.ID + 2),
           field,
           v7,
           (int)v99.carMgr);
  return sub_42A660(&v100.z);
}

// 0x469110
char MapRelatedStruct::sub_469110(int a2, int a3, char a4) {
  char *v5; 
  _WORD *count; 
  int v8; 
  char *v9; 
  char *v10; 
  unsigned __int16 v11; // dx
  int v12; 
  int v13; 
  char *v14; 
  int v15; 
  char *v16;
  void *Car;
  int v18;
  int v19;
  int v20;
  int v21;
  int v22;
  char v23[4];
  v5 = 0;
  v16 = 0;
  if ( !this->Buffer_ZONE )
    return 0;
  count = (_WORD *)this->count;
  *(_WORD *)&v8 = 0;
  v18 = 0;
  if ( !*count )
    goto LABEL_17;
  do
  {
    v9 = sub_462E40( v8);
    v10 = v9;
    if ( *v9 == a4 && !sub_4690B0(v9) )
    {
      S202::sub_40CE30((S202 *)&v19, a2);
      S202::sub_40CE30((S202 *)&v20, arg0);
      S202::sub_40CE30((S202 *)&v21, v10[2]);
      S202::sub_40CE30((S202 *)&v22, v10[1]);
      Car = sub_42A6B0(&v22, v23)->Car;
      if ( sub_4037E0(&Car) )
      {
        if ( Car::sub_403800((Car *)&Car, (int)&unk_662CF8) )
        {
          v5 = v16;
          if ( !v16 )
            v5 = v10;
          v16 = v10;
        }
      }
      else if ( sub_4037E0(&Car) )
      {
        v5 = v10;
      }
    }
    v8 = v18 + 1;
    v11 = *(_WORD *)this->count;
    v18 = v8;
  }
  while ( v8 < v11 );
  if ( v5 )
    return v5;
  if ( !v16 )
  {
LABEL_17:
    *(_WORD *)&v12 = 0;
    v13 = *(unsigned __int16 *)this->count;
    if ( (_WORD)v13 )
    {
      do
      {
        v14 = sub_462E40( v12);
        if ( *v14 == a4 )
          v16 = v14;
        v12 = v15 + 1;
      }
      while ( v12 < v13 );
    }
  }
  return v16;
}

// 0x4692B0
unsigned int MapRelatedStruct::sub_4692B0() {
  unsigned int result; 
  FILE *Buffer_LGHT; 
  SpriteS1 *FirstElement; 
  SpriteS1 *v4; 
  SpriteS1 *v5; 
  int v6; 
  char v7; // cl
  unsigned int v8; 
  int v9;
  unsigned int v10;
  MapRelatedStruct *v11;
  char v12[4];
  char v13[4];
  char v14[4];
  char v15[4];
  result = this->field_348;
  v11 = this;
  if ( result )
  {
    Buffer_LGHT = this->Buffer_LGHT;
    v10 = 0;
    do
    {
      FirstElement = sub_462ED0((SpriteS1 *)v12, (__int16 *)&Buffer_LGHT[1])->FirstElement;
      v4 = sub_462ED0((SpriteS1 *)v13, (__int16 *)&Buffer_LGHT[1]._Placeholder + 1)->FirstElement;
      v5 = sub_462ED0((SpriteS1 *)v14, (__int16 *)&Buffer_LGHT[2])->FirstElement;
      v9 = (int)sub_462ED0((SpriteS1 *)v15, (__int16 *)&Buffer_LGHT[2]._Placeholder + 1)->FirstElement;
      if ( Player::IsCurrentPlayer((Player *)&v9, (Player *)&unk_662C3C) )
        Weapon::UseAmmo((Weapon *)&v9, &unk_6630B8);
      v6 = S115::sub_469010(
             gS115,
             (int)FirstElement,
             (int)v4,
             (int)v5,
             (int)Buffer_LGHT->_Placeholder,
             v9,
             (unsigned __int8)Buffer_LGHT[3]._Placeholder);
      v7 = BYTE2(Buffer_LGHT[3]._Placeholder);
      if ( v7 )
        S115::sub_469070(gS115, v6, v7, HIBYTE(Buffer_LGHT[3]._Placeholder), BYTE1(Buffer_LGHT[3]._Placeholder));
      result = v10 + 1;
      Buffer_LGHT += 4;
      v8 = v11->field_348;
      v10 = result;
    }
    while ( result < v8 );
  }
  return result;
}

// 0x469400
char MapRelatedStruct::sub_469400(_BYTE* a1, _BYTE* a2, _BYTE* a3, char a4) {
  int v5; 
  int v6; 
  int v7; 
  int v8; 
  int v9; 
  int v10; 
  int v11; 
  int v12; 
  char result; // al
  v5 = (unsigned __int8)*a1;
  unk_662B80 = v5;
  unk_662BB4 = (unsigned __int8)*a2;
  v6 = 1;
  unk_662BB8 = (unsigned __int8)*a3;
  while ( 2 )
  {
    v7 = 3;
LABEL_3:
    v8 = v7 - 1;
    switch ( v7 )
    {
      case 1:
        v12 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_19;
        do
        {
          --unk_662BB4;
          if ( sub_4693A0(v8, a4) )
            goto LABEL_22;
          ++v12;
        }
        while ( (unsigned __int16)v12 < (unsigned __int16)v6 );
LABEL_19:
        ++v6;
        continue;
      case 2:
        v10 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_11;
        while ( 1 )
        {
          ++unk_662BB4;
          if ( sub_4693A0(v8, a4) )
            break;
          if ( (unsigned __int16)++v10 >= (unsigned __int16)v6 )
          {
LABEL_11:
            v7 = 4;
            ++v6;
            goto LABEL_3;
          }
        }
        *a1 = v5;
        *a2 = unk_662BB4;
        result = unk_662BB8;
        *a3 = unk_662BB8;
        return result;
      case 3:
        v9 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_7;
        while ( 1 )
        {
          unk_662B80 = ++v5;
          if ( sub_4693A0(v8, a4) )
            break;
          if ( (unsigned __int16)++v9 >= (unsigned __int16)v6 )
          {
LABEL_7:
            v7 = 2;
            goto LABEL_3;
          }
        }
LABEL_22:
        *a1 = v5;
        *a2 = unk_662BB4;
        result = (char)a3;
        *a3 = unk_662BB8;
        return result;
      case 4:
        v11 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_15;
        break;
      default:
        goto LABEL_3;
    }
    break;
  }
  while ( 1 )
  {
    unk_662B80 = --v5;
    if ( sub_4693A0(v8, a4) )
      break;
    if ( (unsigned __int16)++v11 >= (unsigned __int16)v6 )
    {
LABEL_15:
      v7 = 1;
      goto LABEL_3;
    }
  }
  result = (char)a2;
  *a1 = v5;
  *a2 = unk_662BB4;
  *a3 = unk_662BB8;
  return result;
}

// 0x469570
_DWORD* MapRelatedStruct::sub_469570(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2) {
  SpriteS1 *v6; 
  int v7; 
  SpriteS1 *v8; 
  int *v9; 
  int v10; 
  int v11; 
  _DWORD *result; 
  int v13; 
  _WORD *v14; 
  char v15; // cl
  SpriteS1 **v16; 
  _DWORD *v17; 
  int v18; // [esp-8h] [ebp-18h]
  int v19; // [esp-8h] [ebp-18h]
  int v20; // [esp-4h] [ebp-14h]
  SpriteS1 *FirstElement;
  v6 = sub_42A630((SpriteS1 *)&FirstElement, (S202 *)&a2);
  *(_WORD *)&v7 = Car::sub_403820((Car *)v6, &unk_662CFC);
  v8 = a3;
  v9 = arg4;
  if ( v7
    && (v20 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2),
        v18 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3),
        v10 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4),
        sub_466CF0( v10, v18, v20))
    && (FirstElement = sub_462EA0((SpriteS1 *)&FirstElement, &a2)->FirstElement,
        sub_466B70( v9, (S202 *)v8),
        *(_BYTE *)&v11 = Player::CheckCondition((Player *)&FirstElement, &a2),
        v11) )
  {
    result = arg0;
    *arg0 = FirstElement;
  }
  else
  {
    a2 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2) - 1;
    v19 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v13 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
    v14 = sub_466A00( v13, v19, &a2);
    dword_662B90 = v14;
    if ( v14 )
    {
      v15 = *((_BYTE *)v14 + 11);
      if ( (v15 & 0xFC) != 0 && (v15 & 0xFCu) < 0xB4 && (v15 & 3) != 0 )
      {
        S202::sub_41F980((S202 *)&a2, a2);
        FirstElement = *v16;
        sub_466B70( v9, (S202 *)v8);
        *arg0 = FirstElement;
        return arg0;
      }
      else
      {
        S202::sub_41F980((S202 *)&a2, a2 + 1);
        *arg0 = *v17;
        return arg0;
      }
    }
    else
    {
      result = arg0;
      *arg0 = unk_662C98;
    }
  }
  return result;
}

// 0x4696C0
_DWORD* MapRelatedStruct::sub_4696C0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2) {
  void *AudioSourceParams; 
  S202 *field; 
  AudioSourceParams *v6; 
  int v7; 
  int v8; 
  char v9; // al
  unsigned __int8 v10; // al
  int *result; 
  SpriteS1 *v12; 
  int v13; 
  int v14; 
  char v15; // al
  unsigned __int8 v16; // al
  SpriteS1 *v17; 
  int v18; // [esp-8h] [ebp-34h]
  int v19; // [esp-8h] [ebp-34h]
  int v20; // [esp-4h] [ebp-30h]
  int v21; // [esp-4h] [ebp-30h]
  AudioSourceParams a2;
  char v23;
  AudioSourceParams v24;
  AudioSourceParams = v24.y;
  a2.field = (int)v24.y;
  S202::sub_401B20((S202 *)&v24.y, (SpriteS1 *)&a2.z, (PublicTransport *)&unk_662C98);
  if ( !sub_4037E0(&a2) )
  {
LABEL_14:
    result = arg0;
    *arg0 = (int)v24.y;
    return result;
  }
  field = (S202 *)v24.field;
  v6 = arg4;
  while ( 1 )
  {
    v20 = AudioSourceParams::sub_41F9D0(&a2);
    v18 = AudioSourceParams::sub_41F9D0(&v24);
    v7 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
    v8 = sub_4653C0( v7, v18, v20);
    dword_662B90 = (_WORD *)v8;
    if ( !v8 )
      break;
    v9 = *(_BYTE *)(v8 + 11);
    if ( (v9 & 3) == 0 )
      break;
    v10 = v9 & 0xFC;
    if ( v10 )
    {
      if ( v10 < 0xB4u )
      {
        a2.y = (AudioSourceParams *)sub_462EA0((SpriteS1 *)&a2.type, &a2)->FirstElement;
        sub_466B70( &v6->field, field);
        if ( Player::sub_40CE70((Player *)&a2.y, &a2) )
        {
          result = arg0;
          *arg0 = (int)a2.y;
          return result;
        }
      }
    }
LABEL_13:
    v17 = sub_462EA0((SpriteS1 *)&v23, &a2);
    AudioSourceParams = S202::sub_401B20((S202 *)v17, (SpriteS1 *)&a2.field_14, (PublicTransport *)&unk_662C98)->FirstElement;
    a2.field = (int)AudioSourceParams;
    S202::sub_401B20((S202 *)&v24.y, (SpriteS1 *)&a2.z, (PublicTransport *)&unk_662C98);
    if ( !sub_4037E0(&a2) )
      goto LABEL_14;
  }
  v12 = Player::sub_401B40((Player *)&a2, (S202 *)&a2.field_10, (int)&unk_662C98);
  v21 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v12);
  v19 = AudioSourceParams::sub_41F9D0(&v24);
  v13 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
  v14 = sub_4653C0( v13, v19, v21);
  dword_662B90 = (_WORD *)v14;
  if ( !v14 )
    goto LABEL_13;
  v15 = *(_BYTE *)(v14 + 11);
  if ( (v15 & 3) == 0 )
    goto LABEL_13;
  v16 = v15 & 0xFC;
  if ( v16 )
  {
    if ( v16 < 0xB4u )
      goto LABEL_13;
  }
  result = arg0;
  *arg0 = (int)AudioSourceParams;
  return result;
}

// 0x469850
SpriteS1** MapRelatedStruct::sub_469850(SpriteS1* arg0, AudioSourceParams* arg4) {
  SpriteS1 *v4; 
  int v5; 
  S202 *field; 
  AudioSourceParams *v7; 
  int v8; 
  int v9; 
  SpriteS1 **result; 
  int v11; 
  _WORD *v12; 
  char v13; // cl
  SpriteS1 **v14; 
  SpriteS1 **v15; 
  int v16; // [esp-8h] [ebp-18h]
  int v17; // [esp-8h] [ebp-18h]
  int v18; // [esp-4h] [ebp-14h]
  SpriteS1 *FirstElement;
  AudioSourceParams v20;
  v4 = sub_42A630((SpriteS1 *)&FirstElement, (S202 *)&v20.y);
  *(_WORD *)&v5 = Car::sub_403820((Car *)v4, &unk_662CFC);
  field = (S202 *)v20.field;
  v7 = arg4;
  if ( v5
    && (v18 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v20.y),
        v16 = AudioSourceParams::sub_41F9D0(&v20),
        v8 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4),
        sub_466CF0( v8, v16, v18))
    && (FirstElement = sub_462EA0((SpriteS1 *)&FirstElement, &v20.y)->FirstElement,
        sub_466B70( &v7->field, field),
        *(_BYTE *)&v9 = Player::CheckCondition((Player *)&FirstElement, &v20.y),
        v9) )
  {
    result = &arg0->FirstElement;
    arg0->FirstElement = FirstElement;
  }
  else
  {
    v20.y = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v20.y) - 1;
    v17 = AudioSourceParams::sub_41F9D0(&v20);
    v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
    v12 = sub_466A00( v11, v17, &v20.y);
    dword_662B90 = v12;
    if ( v12 )
    {
      v13 = *((_BYTE *)v12 + 11);
      if ( (v13 & 0xFC) != 0 && (v13 & 0xFCu) < 0xB4 && (v13 & 3) != 0 )
      {
        S202::sub_41F980((S202 *)&v20.y, v20.y);
        FirstElement = *v14;
        sub_466B70( &v7->field, field);
        arg0->FirstElement = FirstElement;
        return &arg0->FirstElement;
      }
      else
      {
        S202::sub_41F980((S202 *)&v20.y, v20.y + 1);
        arg0->FirstElement = *v15;
        return &arg0->FirstElement;
      }
    }
    else
    {
      result = &arg0->FirstElement;
      arg0->FirstElement = (SpriteS1 *)unk_662CFC;
    }
  }
  return result;
}

// 0x4699A0
_DWORD* MapRelatedStruct::sub_4699A0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2, SpriteS1* a4) {
  SpriteS1 *v6; 
  SpriteS1 *v8; 
  int v9; 
  SpriteS1 *v10; 
  int *v11; 
  int v12; 
  int v13; 
  _DWORD *result; 
  int v15; 
  _WORD *v16; 
  char v17; // al
  SpriteS1 **v18; 
  _DWORD *v19; 
  int v20; // [esp-8h] [ebp-18h]
  int v21; // [esp-8h] [ebp-18h]
  int v22; // [esp-4h] [ebp-14h]
  v6 = FirstElement;
  *(_BYTE *)&FirstElement->FirstElement = 0;
  v8 = sub_42A630((SpriteS1 *)&FirstElement, (S202 *)&a2);
  *(_WORD *)&v9 = Car::sub_403820((Car *)v8, &unk_662CFC);
  v10 = a3;
  v11 = arg4;
  if ( v9 )
  {
    v22 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
    v20 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
    if ( sub_466CF0( v12, v20, v22) )
    {
      FirstElement = sub_462EA0((SpriteS1 *)&FirstElement, &a2)->FirstElement;
      sub_466B70( v11, (S202 *)v10);
      *(_BYTE *)&v13 = Player::CheckCondition((Player *)&FirstElement, &a2);
      if ( v13 )
      {
        result = arg0;
        *arg0 = FirstElement;
        return result;
      }
      *(_BYTE *)&v6->FirstElement = 1;
    }
  }
  a2 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2) - 1;
  v21 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
  v15 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg4);
  v16 = sub_466A00( v15, v21, &a2);
  dword_662B90 = v16;
  if ( v16 )
  {
    v17 = *((_BYTE *)v16 + 11);
    if ( (v17 & 0xFC) != 0 && (v17 & 0xFCu) < 0xB4 && (v17 & 3) != 0 )
    {
      S202::sub_41F980((S202 *)&a2, a2);
      FirstElement = *v18;
      sub_466B70( v11, (S202 *)v10);
      *arg0 = FirstElement;
      return arg0;
    }
    else
    {
      S202::sub_41F980((S202 *)&a2, a2 + 1);
      *arg0 = *v19;
      return arg0;
    }
  }
  else
  {
    result = arg0;
    *arg0 = unk_662C98;
  }
  return result;
}

// 0x469B00
char MapRelatedStruct::sub_469B00(int* a2, SpriteS1* a3, Player* a4) {
  SpriteS1 *v5; 
  int v6; 
  int v7; 
  int v8; 
  char v9; // cl
  SpriteS1 *v11; 
  int v12; 
  int v13; 
  int v14; // [esp-8h] [ebp-10h]
  int v15; // [esp-8h] [ebp-10h]
  int v16; // [esp-4h] [ebp-Ch]
  int v17; // [esp-4h] [ebp-Ch]
  SpriteS1 *FirstElement;
  v5 = sub_42A630((SpriteS1 *)&FirstElement, (S202 *)&a4);
  *(_WORD *)&v6 = Car::sub_403820((Car *)v5, &unk_662CFC);
  if ( v6 )
  {
    v16 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a4);
    v14 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v7 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
    v8 = sub_4653C0( v7, v14, v16);
    dword_662B90 = v8;
    if ( v8 )
    {
      v9 = *(_BYTE *)(v8 + 11);
      if ( (v9 & 0xFC) != 0 && (v9 & 0xFCu) < 0xB4 && (v9 & 3) != 0 )
      {
        FirstElement = sub_462EA0((SpriteS1 *)&FirstElement, &a4)->FirstElement;
        sub_466B70( a2, (S202 *)a3);
        if ( Player::IsCurrentPlayer((Player *)&FirstElement, (Player *)&a4) )
          return 1;
      }
    }
  }
  else
  {
    if ( Player::IsCurrentPlayer((Player *)&a4, (Player *)&unk_662C98) )
      return 1;
    v11 = Player::sub_401B40((Player *)&a4, (S202 *)&FirstElement, (int)&unk_662C98);
    v17 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v11);
    v15 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v12 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
    v13 = sub_4653C0( v12, v15, v17);
    dword_662B90 = v13;
    if ( v13 )
    {
      if ( (*(_BYTE *)(v13 + 11) & 3) != 0 )
        return 1;
    }
  }
  return 0;
}

// 0x469C20
bool MapRelatedStruct::sub_469C20(int* arg0, SpriteS1* a3, Player* a4) {
  int v5; 
  int v6; 
  char v7; // al
  unsigned __int8 v8; // al
  int v10; 
  int v11; 
  SpriteS1 *v12; 
  int *v13; 
  char v14; // al
  unsigned __int8 v15; // al
  int v16; 
  int v17; 
  char v18; // al
  unsigned __int8 v19; // al
  int v20; 
  int v21; // [esp-8h] [ebp-1Ch]
  int v22; // [esp-8h] [ebp-1Ch]
  int v23; // [esp-8h] [ebp-1Ch]
  int v24; // [esp-4h] [ebp-18h]
  int v25; // [esp-4h] [ebp-18h]
  int v26; // [esp-4h] [ebp-18h]
  int a2;
  int v28;
  Player v29;
  sub_462EA0((SpriteS1 *)&v28, &a4);
  sub_462EA0((SpriteS1 *)&a2, &v29);
  if ( Player::IsCurrentPlayer((Player *)&v28, (Player *)&a2) )
  {
    v24 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v28);
    v21 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v5 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg0);
    v6 = sub_4653C0( v5, v21, v24);
    dword_662B90 = (_WORD *)v6;
    if ( !v6 )
      return 0;
    v7 = *(_BYTE *)(v6 + 11);
    if ( (v7 & 3) == 0 )
      return 0;
    v8 = v7 & 0xFC;
    if ( !v8 )
      return 0;
    if ( v8 >= 0xB4u )
      return 0;
    a2 = v28;
    sub_466B70( arg0, (S202 *)a3);
    if ( !Player::sub_40CE70(&v29, &a2) )
      return 0;
  }
  else
  {
    v25 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
    v22 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v10 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg0);
    v11 = sub_4653C0( v10, v22, v25);
    v12 = a3;
    v13 = arg0;
    dword_662B90 = (_WORD *)v11;
    if ( v11 )
    {
      v14 = *(_BYTE *)(v11 + 11);
      if ( (v14 & 3) != 0 )
      {
        v15 = v14 & 0xFC;
        if ( v15 )
        {
          if ( v15 < 0xB4u )
          {
            sub_466B70( arg0, (S202 *)a3);
            if ( Player::sub_40CE70(&v29, &a2) )
              return 1;
          }
        }
      }
    }
    v26 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v28);
    v23 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3);
    v16 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&arg0);
    v17 = sub_4653C0( v16, v23, v26);
    dword_662B90 = (_WORD *)v17;
    if ( !v17 )
      return 0;
    v18 = *(_BYTE *)(v17 + 11);
    if ( (v18 & 3) == 0 )
      return 0;
    v19 = v18 & 0xFC;
    if ( !v19 || v19 >= 0xB4u )
      return 1;
    a2 = v28;
    sub_466B70( v13, (S202 *)v12);
  }
  *(_BYTE *)&v20 = Player::CheckCondition((Player *)&a4, &a2);
  return v20 != 0;
}

// 0x469DC0
char MapRelatedStruct::sub_469DC0(int* a2, SpriteS1* pSpriteS1) {
  int v4; 
  int v5; 
  char v6; // al
  unsigned __int8 v7; // al
  int *v8; 
  int v9; 
  int v11; 
  int v12; 
  int *v13; 
  SpriteS1 *v14; 
  int *v15; 
  char v16; // al
  unsigned __int8 v17; // al
  int v18; 
  int v19; 
  char v20; // al
  unsigned __int8 v21; // al
  int v22; 
  int *v23; // [esp-Ch] [ebp-24h]
  int *v24; // [esp-Ch] [ebp-24h]
  int v25; // [esp-8h] [ebp-20h]
  SpriteS1 *v26; // [esp-8h] [ebp-20h]
  int v27; // [esp-8h] [ebp-20h]
  SpriteS1 *v28; // [esp-8h] [ebp-20h]
  int v29; // [esp-8h] [ebp-20h]
  int v30; // [esp-4h] [ebp-1Ch]
  int v31; // [esp-4h] [ebp-1Ch]
  int v32; // [esp-4h] [ebp-1Ch]
  Player *pPlayer;
  int v34;
  Player pSpriteS1_4;
  sub_462EA0((SpriteS1 *)&pPlayer, &pSpriteS1_4);
  sub_462EA0((SpriteS1 *)&v34, &pSpriteS1_4.Player);
  if ( Player::IsCurrentPlayer((Player *)&pPlayer, (Player *)&v34) )
  {
    v30 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&pPlayer);
    v25 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&pSpriteS1);
    v4 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
    v5 = sub_4653C0( v4, v25, v30);
    dword_662B90 = (_WORD *)v5;
    if ( v5 )
    {
      v6 = *(_BYTE *)(v5 + 11);
      if ( (v6 & 3) != 0 )
      {
        v7 = v6 & 0xFC;
        if ( v7 )
        {
          if ( v7 < 0xB4u )
          {
            v8 = *(int **)&pSpriteS1_4.Rotate;
            v26 = pSpriteS1;
            v23 = a2;
            **(_DWORD **)&pSpriteS1_4.Rotate = pPlayer;
            sub_466B70( v23, (S202 *)v26);
            if ( Player::sub_40CE70((Player *)&pSpriteS1_4.Player, v8) )
            {
              *(_BYTE *)&v9 = Player::CheckCondition(&pSpriteS1_4, v8);
              if ( v9 )
                return 1;
            }
          }
        }
      }
    }
    return 0;
  }
  v31 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&v34);
  v27 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&pSpriteS1);
  v11 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
  v12 = sub_4653C0( v11, v27, v31);
  v13 = *(int **)&pSpriteS1_4.Rotate;
  v14 = pSpriteS1;
  v15 = a2;
  dword_662B90 = (_WORD *)v12;
  if ( !v12
    || (v16 = *(_BYTE *)(v12 + 11), (v16 & 3) == 0)
    || (v17 = v16 & 0xFC) == 0
    || v17 >= 0xB4u
    || (v28 = pSpriteS1,
        v24 = a2,
        **(_DWORD **)&pSpriteS1_4.Rotate = v34,
        sub_466B70( v24, (S202 *)v28),
        !Player::sub_40CE70((Player *)&pSpriteS1_4.Player, v13)) )
  {
    v32 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&pPlayer);
    v29 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&pSpriteS1);
    v18 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a2);
    v19 = sub_4653C0( v18, v29, v32);
    dword_662B90 = (_WORD *)v19;
    if ( !v19 )
      return 0;
    v20 = *(_BYTE *)(v19 + 11);
    if ( (v20 & 3) == 0 )
      return 0;
    v21 = v20 & 0xFC;
    if ( v21 && v21 < 0xB4u )
    {
      *v13 = (int)pPlayer;
      sub_466B70( v15, (S202 *)v14);
      *(_BYTE *)&v22 = Player::CheckCondition(&pSpriteS1_4, v13);
      if ( !v22 )
        return 0;
    }
    else
    {
      *v13 = (int)S202::sub_401B20((S202 *)&pPlayer, (SpriteS1 *)&pSpriteS1, (PublicTransport *)&unk_662C98)->FirstElement;
    }
  }
  return 1;
}

// 0x469F90
char MapRelatedStruct::sub_469F90(SpriteS1* a2, SpriteS1* arg4, Player* a4) {
  S202 *S202; 
  SpriteS1 *v5; 
  SpriteS1 *v6; 
  Ped *v7; 
  int v8; 
  int v9; 
  int v10; 
  SpriteS1 **v11; 
  int **p_pPlayer; 
  int *v13; 
  int *v14; 
  int *v15; 
  SpriteS1 *v16; 
  int v17; 
  int v18; 
  int *v19; 
  int v20; 
  int v21; 
  int v22; 
  int v24; // [esp-8h] [ebp-48h]
  int v25; // [esp-8h] [ebp-48h]
  int v26; // [esp-8h] [ebp-48h]
  int v27; // [esp-8h] [ebp-48h]
  SpriteS1 *v28; // [esp-4h] [ebp-44h]
  int v29; // [esp-4h] [ebp-44h]
  int v30; // [esp-4h] [ebp-44h]
  int v31; // [esp-4h] [ebp-44h]
  int v32; // [esp-4h] [ebp-44h]
  S202 pS202;
  char v34;
  char v35;
  _DWORD arg0a[2];
  PublicTransport a3;
  S202 = gObject->S63[1].self;
  Player::sub_401B40((Player *)&a3.BaseCar[0].Status, &pS202, (int)&a3.BaseCar[0].field_8);
  CarSystemManager::SetIndexDefautCarManager((CarSystemManager *)&a3.BaseCar[0].Status);
  v28 = Player::sub_401B40((Player *)&a3.BaseCar[0].count, (S202 *)&pS202.self, (int)&a3.BaseCar[0].field_4);
  v5 = Player::sub_401B40((Player *)&a3.BaseCar[0].field_C, (S202 *)&pS202.carMgr, (int)&a3);
  S103::sub_401D20((S103 *)arg0a, v5, v28);
  sub_4637B0(&dword_5E6874);
  Player::sub_401B40((Player *)&a3.BaseCar[0].field_C, (S202 *)&pS202.carMgr, (int)&a3);
  v6 = Player::sub_401B40((Player *)&a3.BaseCar[0].count, (S202 *)&pS202.self, (int)&a3.BaseCar[0].field_4);
  *(_WORD *)&a3.BaseCar[0].Status = *sub_40E8D0(v7, (Car *)&a3.BaseCar[0].field_C, v6);
  v8 = *(_DWORD *)Player::sub_41E260((Player *)arg0a, (int)&a3.BaseCar[0].field_C);
  a3.BaseCar[0].field_C = v8;
  SpriteS1::sub_420600((SpriteS1 *)S202, a3.BaseCar[0].field, a3.BaseCar[0].field_4, a3.BaseCar[0].field_8);
  SpriteS1::SetRotation((SpriteS1 *)S202, (CarSystemManager *)a3.BaseCar[0].Status);
  SpriteS1::sub_4BCB90((SpriteS1 *)S202, a2, (SpriteS3 *)arg4, (EventHandler *)a4);
  *(_WORD *)&v9 = Car::sub_403820((Car *)&a3.BaseCar[0].field_C, &unk_662CFC);
  if ( v9 )
  {
    a3.BaseCar[0].field_4 = *(_DWORD *)sub_401B90(&a3.BaseCar[0].field_C, &a3.BaseCar[0].field_4, &arg4);
    v10 = *(_DWORD *)sub_401B90(&a3.BaseCar[0].field_C, &a3, &a3.BaseCar[0].field_4);
    a3.BaseCar[0].field = *(_DWORD *)sub_401B90(&pS202, &a3, &a3.BaseCar[0].field_4);
  }
  else
  {
    v10 = unk_662CFC;
    a3.BaseCar[0].field_4 = unk_662CFC;
  }
  if ( sub_4037E0(&a3.BaseCar[0].field_4) )
  {
    a3.BaseCar[0].field_4 = (int)unk_662C98;
    v10 = v8;
    a3.BaseCar[0].field = pS202.field_0;
  }
  a3.BaseCar[0].field_C = v10;
  sub_41FC20(&a3.BaseCar[0].Status, &a3.BaseCar[0].Status);
  *(_BYTE *)&arg4 = 1;
  if ( AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3.BaseCar[0].field_4) < 1 )
    return 1;
  v11 = (SpriteS1 **)&S202->field_18;
  p_pPlayer = (int **)&S202->pPlayer;
  v13 = (int *)&S202->field_1C;
  while ( 1 )
  {
    a3.BaseCar[0].field_C = *gMapRelatedStruct->sub_469570( &a2, *p_pPlayer, *v11, *v13);
    if ( Player::IsCurrentPlayer((Player *)&a3, (Player *)&unk_662CFC) )
    {
      a3.BaseCar[0].field_C = (int)S202::sub_401B20((S202 *)&S202->field_1C, (SpriteS1 *)&pS202.carMgr, &a3);
      a3.BaseCar[0].Status = (int)S202::sub_401B20(
                                    (S202 *)v11,
                                    (SpriteS1 *)&pS202.self,
                                    (PublicTransport *)&a3.BaseCar[0].count);
      v14 = (int *)S202::sub_401B20(
                     (S202 *)&S202->pPlayer,
                     (SpriteS1 *)&pS202,
                     (PublicTransport *)&a3.BaseCar[0].field_8);
      SpriteS1::sub_420600((SpriteS1 *)S202, *v14, *(_DWORD *)a3.BaseCar[0].Status, *(_DWORD *)a3.BaseCar[0].field_C);
      goto LABEL_21;
    }
    if ( !Car::sub_403800((Car *)&a3, (int)&unk_662CFC) )
      break;
    a3.BaseCar[0].field_C = (int)S202::sub_401B20((S202 *)&S202->field_1C, (SpriteS1 *)&pS202.field_C, &a3);
    a3.BaseCar[0].Status = (int)S202::sub_401B20(
                                  (S202 *)v11,
                                  (SpriteS1 *)&pS202.field_10,
                                  (PublicTransport *)&a3.BaseCar[0].count);
    v15 = (int *)S202::sub_401B20(
                   (S202 *)&S202->pPlayer,
                   (SpriteS1 *)&pS202.pPlayer,
                   (PublicTransport *)&a3.BaseCar[0].field_8);
    SpriteS1::sub_420600((SpriteS1 *)S202, *v15, *(_DWORD *)a3.BaseCar[0].Status, *(_DWORD *)a3.BaseCar[0].field_C);
    a3.BaseCar[0].field_C = *v13;
    if ( Car::sub_403800((Car *)&a3.BaseCar[0].field_C, (int)&unk_662C50) )
      return 0;
    if ( !sub_4037E0(&S202->field_1C)
      || (v16 = S202::sub_401B20((S202 *)&S202->field_1C, (SpriteS1 *)&pS202.field_18, (PublicTransport *)&unk_663164),
          v29 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v16),
          v24 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v11),
          v17 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->pPlayer),
          gMapRelatedStruct->sub_420420( v17, v24, v29)) )
    {
      v30 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->field_1C);
      v25 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v11);
      v18 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->pPlayer);
      if ( !gMapRelatedStruct->sub_466CF0( v18, v25, v30) )
        return 0;
    }
    SpriteS1::sub_420600((SpriteS1 *)S202, (int)*p_pPlayer, (int)*v11, a3.BaseCar[0].field_C);
LABEL_21:
    if ( SpriteS1::sub_4BD670((SpriteS1 *)S202) )
      return 0;
    *(_BYTE *)&arg4 = (_BYTE)arg4 + 1;
    v22 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&a3.BaseCar[0].field_4);
    if ( (unsigned __int8)arg4 > v22 )
      return 1;
  }
  a3.BaseCar[0].Status = (int)S202::sub_401B20((S202 *)&S202->field_1C, (SpriteS1 *)&pS202.field_1C, &a3);
  a4 = (Player *)S202::sub_401B20((S202 *)v11, (SpriteS1 *)&v34, (PublicTransport *)&a3.BaseCar[0].count);
  v19 = (int *)S202::sub_401B20((S202 *)&S202->pPlayer, (SpriteS1 *)&v35, (PublicTransport *)&a3.BaseCar[0].field_8);
  SpriteS1::sub_420600((SpriteS1 *)S202, *v19, (int)a4->CurrentPlayer, *(_DWORD *)a3.BaseCar[0].Status);
  v31 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->field_1C);
  v26 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v11);
  v20 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->pPlayer);
  if ( gMapRelatedStruct->sub_466CF0( v20, v26, v31) )
  {
    v32 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->field_1C);
    v27 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)v11);
    v21 = AudioSourceParams::sub_41F9D0((AudioSourceParams *)&S202->pPlayer);
    if ( gMapRelatedStruct->sub_420420( v21, v27, v32) )
    {
      a3.BaseCar[0].field_C = *gMapRelatedStruct->sub_469570( arg0a, *p_pPlayer, *v11, *v13);
      if ( Car::sub_403800((Car *)&a3.BaseCar[0].field_C, (int)&S202->field_1C) )
        return 0;
    }
    goto LABEL_21;
  }
  if ( !Car::sub_403800((Car *)&a3.BaseCar[0].field_C, (int)&S202->field_1C) )
    goto LABEL_21;
  SpriteS1::sub_420600((SpriteS1 *)S202, (int)*p_pPlayer, (int)*v11, a3.BaseCar[0].field_C);
  return 0;
}
