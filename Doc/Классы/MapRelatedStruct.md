# MapRelatedStruct

- **Место**: `gta2/Engine/MapRelatedStruct/`
- **Файлы**: `.cpp` 6660 строк, `.h` 358 строк
- **Методов**: 135
- **Полностью реализовано**: 13
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 88
- **Объявлено, но не определено в .cpp**: 34
- **Реализация в целом: ~10%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `bool MapRelatedStruct::sub_48A350(unsigned char a2, unsigned char a3, unsigned char a4)` | 1372 | 5 |  |
| `bool MapRelatedStruct::sub_492140(int a2, int a3, int a4)` | 1392 | 5 |  |
| `char MapRelatedStruct::sub_49EBE0(int a2, int a3, int a4, _BYTE *a5, _BYTE *a6)` | 1403 | 7 |  |
| `bool MapRelatedStruct::sub_4B9F40(int a2, int a3, int a4)` | 1429 | 5 |  |
| `void MapRelatedStruct::sub_464330()` | 1484 | 20 |  |
| `bool MapRelatedStruct::sub_42A850(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4)` | 1601 | 4 | 0x0042A850 |
| `char MapRelatedStruct::sub_4632E0(int a1, int a2, char a3)` | 1789 | 5 | 0x004632E0 |
| `int MapRelatedStruct::sub_463570(int a2, int a3, _DWORD* a4)` | 1835 | 4 | 0x00463570 |
| `_WORD *MapRelatedStruct::sub_464980()` | 2520 | 4 |  |
| `_WORD *MapRelatedStruct::LoadMap(LPCSTR lpFileName)` | 2528 | 7 |  |
| `int MapRelatedStruct::sub_465250(unsigned char a2, unsigned char a3)` | 2795 | 7 |  |
| `_WORD *MapRelatedStruct::sub_465280(int a2, __int16 a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, __int16 a11, __int16 a12, __int16 a13)` | 2806 | 27 |  |
| `char *MapRelatedStruct::sub_465390()` | 2851 | 6 |  |

## Заглушки (однострочные / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `void MapRelatedStruct::sub_464B30()` | 197 | 2 |  |
| `char MapRelatedStruct::sub_463850(AudioSourceParams a2)` | 317 | 4 |  |
| `int *MapRelatedStruct::FindMaxZForLocation(int *arg0, int *a2, S202 *pS202)` | 391 | 4 |  |
| `int MapRelatedStruct::sub_46A4D0()` | 434 | 4 |  |
| `char MapRelatedStruct::sub_46A570( CarSystemManager *arg0, CarSystemManager *a3, CarSystemManager *a4, CarSystemManager *a5, CarSystemManager *a6, CarSystemManager *a2, int a8)` | 475 | 11 |  |
| `char MapRelatedStruct::sub_46B440( CarSystemManager *a6, CarSystemManager *a2, int a8, _DWORD *a5, __int16 arg10)` | 1284 | 9 |  |
| `void MapRelatedStruct::sub_492130()` | 1384 | 3 |  |
| `char *MapRelatedStruct::sub_464EE0(unsigned char arg0, unsigned char a2, char a4)` | 1441 | 4 |  |
| `char MapRelatedStruct::sub_420420(int a2, int a3, int a4)` | 1592 | 3 | 0x00420420 |
| `bool MapRelatedStruct::sub_42A8C0(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4)` | 1614 | 3 | 0x0042A8C0 |
| `bool MapRelatedStruct::sub_433430(int a2, int a3, int a4)` | 1620 | 3 | 0x00433430 |
| `bool MapRelatedStruct::sub_433470(unsigned __int8 a2, char a3, unsigned __int8 a4)` | 1632 | 3 | 0x00433470 |
| `bool MapRelatedStruct::sub_4334A0(char a2, unsigned __int8 a3, unsigned __int8 a4)` | 1638 | 3 | 0x004334A0 |
| `bool MapRelatedStruct::sub_4334D0(unsigned __int8 a2, char a3, unsigned __int8 a4)` | 1644 | 3 | 0x004334D0 |
| `bool MapRelatedStruct::sub_433500(char a2, unsigned __int8 a3, unsigned __int8 a4)` | 1650 | 3 | 0x00433500 |
| `bool MapRelatedStruct::sub_433530(unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4)` | 1656 | 3 | 0x00433530 |
| `int MapRelatedStruct::sub_462C60()` | 1662 | 3 | 0x00462C60 |
| `int MapRelatedStruct::sub_462CB0(unsigned short a2)` | 1671 | 3 | 0x00462CB0 |
| `_WORD* MapRelatedStruct::sub_462CE0(unsigned short a2, __int16 a3)` | 1677 | 3 | 0x00462CE0 |
| `int MapRelatedStruct::sub_462D00(unsigned short a2, __int16 a3)` | 1684 | 3 | 0x00462D00 |
| `int MapRelatedStruct::sub_462D20(unsigned short a2, __int16 a3)` | 1691 | 3 | 0x00462D20 |
| `int MapRelatedStruct::sub_462D40(unsigned short a2, __int16 a3)` | 1698 | 3 | 0x00462D40 |
| `int MapRelatedStruct::sub_462D60(unsigned short a2, __int16 a3)` | 1705 | 3 | 0x00462D60 |
| `int MapRelatedStruct::sub_462D80(unsigned short a2, __int16 a3)` | 1712 | 3 | 0x00462D80 |
| `int MapRelatedStruct::sub_462DA0(unsigned short a2, __int16 a3)` | 1719 | 3 | 0x00462DA0 |
| `int MapRelatedStruct::sub_462DC0(unsigned short a2, __int16 a3)` | 1726 | 3 | 0x00462DC0 |
| `int MapRelatedStruct::sub_462DE0(unsigned short a2, __int16 a3)` | 1733 | 3 | 0x00462DE0 |
| `int MapRelatedStruct::sub_462E00(unsigned short a2, __int16 a3)` | 1740 | 3 | 0x00462E00 |
| `int MapRelatedStruct::sub_462E20(unsigned short a2, __int16 a3)` | 1747 | 3 | 0x00462E20 |
| `char* MapRelatedStruct::sub_462E40(unsigned short a2)` | 1754 | 3 | 0x00462E40 |
| `char MapRelatedStruct::sub_462E80()` | 1759 | 3 | 0x00462E80 |
| `char MapRelatedStruct::sub_462F50(int a2, int a3)` | 1766 | 3 | 0x00462F50 |
| `int MapRelatedStruct::sub_4633A0(int a1, char a2)` | 1822 | 3 | 0x004633A0 |
| `int MapRelatedStruct::sub_4635F0(int a2, int a3, int* a4)` | 1861 | 3 | 0x004635F0 |
| `int MapRelatedStruct::sub_463A00(_DWORD* a2)` | 1895 | 3 | 0x00463A00 |
| `int MapRelatedStruct::sub_463A40(unsigned int a2)` | 1906 | 3 | 0x00463A40 |
| `unsigned int MapRelatedStruct::sub_463A90(unsigned int a2)` | 1921 | 3 | 0x00463A90 |
| `unsigned int MapRelatedStruct::sub_463AE0(unsigned int a2, int a3)` | 1935 | 3 | 0x00463AE0 |
| `unsigned int MapRelatedStruct::sub_463C30(unsigned int a2, int a3, char a4)` | 1987 | 3 | 0x00463C30 |
| `char MapRelatedStruct::sub_463F60(int a2, int a3, int a4, int a5, __int16 a6)` | 2113 | 3 | 0x00463F60 |
| `int MapRelatedStruct::sub_464060(int a2, int a3, int a4, _DWORD* a5)` | 2158 | 3 | 0x00464060 |
| `S16_01* MapRelatedStruct::sub_464110(int a2, int a3, int a4, char a5)` | 2182 | 3 | 0x00464110 |
| `char MapRelatedStruct::sub_464160(int a2, int a3)` | 2194 | 3 | 0x00464160 |
| `int MapRelatedStruct::sub_464210(int a2, int a3, int a4, int a5)` | 2228 | 4 |  |
| `unsigned int MapRelatedStruct::sub_464250(unsigned int a2, unsigned int a3, unsigned int a4)` | 2243 | 4 |  |
| `int MapRelatedStruct::sub_4642A0(_DWORD *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5, _DWORD *a6, int *a7)` | 2255 | 4 |  |
| `int MapRelatedStruct::sub_4644E0(unsigned int a2)` | 2270 | 4 |  |
| `int MapRelatedStruct::sub_464550(int a2)` | 2305 | 4 |  |
| `int MapRelatedStruct::sub_464590(SIZE_T dwBytes)` | 2324 | 4 |  |
| `int MapRelatedStruct::sub_4645F0(SIZE_T dwBytes)` | 2342 | 4 |  |
| `int MapRelatedStruct::sub_464640(FileMgr *dwBytes)` | 2360 | 4 |  |
| `int MapRelatedStruct::sub_464670(FileMgr *dwBytes)` | 2371 | 4 |  |
| `int MapRelatedStruct::sub_4646A0(int a2)` | 2382 | 4 |  |
| `unsigned char MapRelatedStruct::sub_464880()` | 2442 | 4 |  |
| `unsigned char MapRelatedStruct::ParseMapLine(_BYTE *a2, FileMgr *dwBytes)` | 2498 | 4 |  |
| `int MapRelatedStruct::sub_464C70(const char *a2)` | 2558 | 4 |  |
| `int MapRelatedStruct::sub_464D00(char *String2, unsigned char a3)` | 2590 | 4 |  |
| `char *MapRelatedStruct::sub_464DA0(char a2)` | 2612 | 4 |  |
| `char *MapRelatedStruct::sub_464E70(char a2)` | 2653 | 4 |  |
| `char *MapRelatedStruct::sub_464FE0(unsigned char a2, unsigned char a3, char a4)` | 2687 | 4 |  |
| `char *MapRelatedStruct::sub_465090(unsigned char a2, unsigned char a3)` | 2716 | 4 |  |
| `char *MapRelatedStruct::sub_465130(unsigned char a2, unsigned char a3)` | 2744 | 4 |  |
| `char *MapRelatedStruct::sub_4651C0()` | 2772 | 4 |  |
| `int MapRelatedStruct::sub_4653C0(int a2, int a3, int a4)` | 2861 | 3 | 0x4653C0 |
| `S16_02** MapRelatedStruct::sub_465410(int a2, int a3, int a4)` | 2877 | 3 | 0x465410 |
| `int MapRelatedStruct::sub_465490(int a2, int a3, int a4)` | 2898 | 3 | 0x465490 |
| `int MapRelatedStruct::sub_465650(int a2, int a3, Player* a4)` | 3012 | 3 | 0x465650 |
| `char MapRelatedStruct::sub_4656D0(int a2, int a3, int a4, int a5, _DWORD* a6, char a7)` | 3035 | 3 | 0x4656D0 |
| `char MapRelatedStruct::sub_465FE0(AudioSourceParams* arg0)` | 3533 | 3 | 0x465FE0 |
| `char MapRelatedStruct::sub_466170(int arg0)` | 3599 | 3 | 0x466170 |
| `char MapRelatedStruct::sub_466380(int a2, int a3, int a4, int a5, int a6)` | 3687 | 3 | 0x466380 |
| `char MapRelatedStruct::sub_466430(int arg0, int a3, int a2, int a5, int a6)` | 3748 | 3 | 0x466430 |
| `char MapRelatedStruct::sub_466620(void* a2)` | 3858 | 3 | 0x466620 |
| `char MapRelatedStruct::sub_466730(AudioSourceParams a2)` | 3924 | 3 | 0x466730 |
| `int MapRelatedStruct::sub_466910(int a2, int a3, _DWORD* a4)` | 3973 | 3 | 0x466910 |
| `_WORD* MapRelatedStruct::FindMaxZForTile(int a2, int a3, _DWORD* a4)` | 4010 | 3 | 0x466990 |
| `_WORD* MapRelatedStruct::sub_466A00(int a2, int a3, int* a4)` | 4047 | 3 | 0x466A00 |
| `char MapRelatedStruct::sub_466B70(int* a2, S202* pS202)` | 4116 | 3 | 0x466B70 |
| `char MapRelatedStruct::sub_469110(int a2, int a3, char a4)` | 5691 | 3 | 0x469110 |
| `unsigned int MapRelatedStruct::sub_4692B0()` | 5773 | 3 | 0x4692B0 |
| `char MapRelatedStruct::ScanZoneStars(_BYTE* a1, _BYTE* a2, _BYTE* a3, char a4)` | 5825 | 3 | 0x469400 |
| `_DWORD* MapRelatedStruct::sub_469570(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2)` | 5936 | 3 | 0x469570 |
| `int* MapRelatedStruct::sub_4696C0(int* arg0, AudioSourceParams* arg4)` | 6005 | 3 | 0x4696C0 |
| `SpriteS1** MapRelatedStruct::sub_469850(SpriteS1* arg0, AudioSourceParams* arg4)` | 6098 | 3 | 0x469850 |
| `_DWORD* MapRelatedStruct::sub_4699A0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2, SpriteS1* a4)` | 6168 | 3 | 0x4699A0 |
| `char MapRelatedStruct::sub_469B00(int* a2, SpriteS1* a3, Player* a4)` | 6242 | 3 | 0x469B00 |
| `bool MapRelatedStruct::sub_469C20(int* arg0, SpriteS1* a3, Player* a4)` | 6297 | 3 | 0x469C20 |
| `char MapRelatedStruct::sub_469F90(SpriteS1* a2, SpriteS1* arg4, Player* a4)` | 6507 | 3 | 0x469F90 |

## Объявлено в .h, без определения в .cpp (34)

| метод | строка в .h |
|---|---|
| `static void sub_44C840(S16_02* p)` | 61 |
| `static void sub_41F980(S202* p, int value)` | 77 |
| `bool sub_466CF0(int a2, int a3, int a4)` | 242 |
| `__int16 sub_466D30(AudioSourceParams a2)` | 243 |
| `_DWORD* sub_466E20(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2)` | 244 |
| `_DWORD* sub_466F70(_DWORD* arg0, S202* a2)` | 245 |
| `__int16 sub_467020(int*, SpriteS1*, void*, void*, void*)` | 246 |
| `int sub_467110(int* arg0, SpriteMain* pSpriteMian, int* a4, Player* pPlayer)` | 247 |
| `int sub_467F80(int** arg0, SpriteS1** a3, int* a4, Player* a5)` | 248 |
| `char sub_469DC0(int* a2, SpriteS1* pSpriteS1)` | 261 |
| `void FetchStoredId() {}` | 286 |
| `void SetFlagValue() {}` | 288 |
| `void RefreshFlag() {}` | 290 |
| `void Clear() {}` | 292 |
| `void AllocNode() {}` | 294 |
| `void FreeNode() {}` | 296 |
| `int GetElement(int arg0, int arg1) {}` | 300 |
| `void ResolveMapPosition(int arg0, int arg1) {}` | 303 |
| `int CollidesWithPed(int arg0, int arg1, int arg2) {}` | 306 |
| `void Update() {}` | 309 |
| `void Reset(int arg0) {}` | 312 |
| `void LoadTileData(int arg0, int arg1) {}` | 315 |
| `void AddPoint(int arg0, int arg1) {}` | 318 |
| `int DuplicatePoint(int arg0, int arg1) {}` | 321 |
| `void DuplicateHeight(int arg0, int arg1) {}` | 324 |
| `int SplitHeight(int arg0, int arg1, int arg2) {}` | 327 |
| `void ReduceHeight(int arg0, int arg1, int arg2) {}` | 330 |
| `void ParseNames(int arg0) {}` | 333 |
| `void* GetGangByName(int arg0) {}` | 336 |
| `int GetXStyle(int arg0) {}` | 339 |
| `int GetYStyle(int arg0) {}` | 342 |
| `int CheckCarTop(int arg0, int arg1) {}` | 345 |
| `int CheckCarPosition(int arg0) {}` | 348 |
| `void IsPointVisible() {}` | 351 |
