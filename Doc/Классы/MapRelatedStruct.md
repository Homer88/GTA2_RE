# MapRelatedStruct

- **Место**: `gta2/Engine/MapRelatedStruct/`
- **Файлы**: `.cpp` 6686 строк, `.h` 368 строк
- **Методов**: 110
- **Полностью реализовано**: 15
- **Частично (TODO/незавершено)**: 1
- **Заглушки**: 88
- **Объявлено, но не определено**: 6
- **Реализация в целом: ~14%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `sub_466D30(AudioSourceParams a2)` | 274 | 64 |  |
| `sub_48A350(unsigned char a2, unsigned char a3, unsigned char a4)` | 1397 | 8 |  |
| `sub_492140(int a2, int a3, int a4)` | 1417 | 7 |  |
| `sub_49EBE0(int a2, int a3, int a4, _BYTE* a5, _BYTE* a6)` | 1428 | 22 |  |
| `sub_4B9F40(int a2, int a3, int a4)` | 1454 | 8 |  |
| `sub_464330()` | 1509 | 105 |  |
| `sub_42A850(unsigned char a2, unsigned char a3, unsigned char a4)` | 1626 | 11 |  |
| `sub_4632E0(int a1, int a2, char a3)` | 1814 | 31 |  |
| `sub_463570(int a2, int a3, _DWORD* a4)` | 1860 | 24 |  |
| `sub_464980()` | 2545 | 5 |  |
| `sub_465250(unsigned char a2, unsigned char a3)` | 2820 | 7 |  |
| `sub_465280(int a2, __int16 a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, __int16 a11, __int16 a12, __int16 a13)` | 2831 | 27 |  |
| `sub_465390()` | 2876 | 7 |  |
| `sub_469C20(int* arg0, SpriteS1* a3, Player* a4)` | 6322 | 94 |  |
| `sub_469DC0(int* a2, SpriteS1* pSpriteS1)` | 6418 | 112 |  |

## Частично реализованные (есть TODO/не завершены)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `LoadMap(LPCSTR lpFileName)` | 2553 | 26 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `sub_464B30()` | 222 | 48 |  |
| `sub_463850(AudioSourceParams a2)` | 342 | 70 |  |
| `FindMaxZForLocation(int* arg0, int* a2, S202* pS202)` | 416 | 39 |  |
| `sub_46A4D0()` | 459 | 37 |  |
| `sub_46A570(CarSystemManager* arg0, CarSystemManager* a3, CarSystemManager* a4, CarSystemManager* a5, CarSystemManager* a6, CarSystemManager* a2, int a8)` | 500 | 805 |  |
| `sub_46B440(CarSystemManager* a6, CarSystemManager* a2, int a8, _DWORD* a5, __int16 arg10)` | 1309 | 84 |  |
| `sub_492130()` | 1409 | 4 |  |
| `sub_464EE0(unsigned char arg0, unsigned char a2, char a4)` | 1466 | 39 |  |
| `sub_420420(int a2, int a3, int a4)` | 1617 | 7 |  |
| `sub_42A8C0(unsigned char a2, unsigned char a3, unsigned char a4)` | 1639 | 4 |  |
| `sub_433430(int a2, int a3, int a4)` | 1645 | 10 |  |
| `sub_433470(unsigned char a2, char a3, unsigned char a4)` | 1657 | 4 |  |
| `sub_4334A0(char a2, unsigned char a3, unsigned char a4)` | 1663 | 4 |  |
| `sub_4334D0(unsigned char a2, char a3, unsigned char a4)` | 1669 | 4 |  |
| `sub_433500(char a2, unsigned char a3, unsigned char a4)` | 1675 | 4 |  |
| `sub_433530(unsigned char a2, unsigned char a3, unsigned char a4)` | 1681 | 4 |  |
| `sub_462C60()` | 1687 | 7 |  |
| `sub_462CB0(unsigned short a2)` | 1696 | 4 |  |
| `sub_462CE0(unsigned short a2, __int16 a3)` | 1702 | 5 |  |
| `sub_462D00(unsigned short a2, __int16 a3)` | 1709 | 5 |  |
| `sub_462D20(unsigned short a2, __int16 a3)` | 1716 | 5 |  |
| `sub_462D40(unsigned short a2, __int16 a3)` | 1723 | 5 |  |
| `sub_462D60(unsigned short a2, __int16 a3)` | 1730 | 5 |  |
| `sub_462D80(unsigned short a2, __int16 a3)` | 1737 | 5 |  |
| `sub_462DA0(unsigned short a2, __int16 a3)` | 1744 | 5 |  |
| `sub_462DC0(unsigned short a2, __int16 a3)` | 1751 | 5 |  |
| `sub_462DE0(unsigned short a2, __int16 a3)` | 1758 | 5 |  |
| `sub_462E00(unsigned short a2, __int16 a3)` | 1765 | 5 |  |
| `sub_462E20(unsigned short a2, __int16 a3)` | 1772 | 5 |  |
| `sub_462E40(unsigned short a2)` | 1779 | 3 |  |
| `sub_462E80()` | 1784 | 5 |  |
| `sub_462F50(int a2, int a3)` | 1791 | 21 |  |
| `sub_4633A0(int a1, char a2)` | 1847 | 11 |  |
| `sub_4635F0(int a2, int a3, int* a4)` | 1886 | 32 |  |
| `sub_463A00(_DWORD* a2)` | 1920 | 9 |  |
| `sub_463A40(unsigned int a2)` | 1931 | 13 |  |
| `sub_463A90(unsigned int a2)` | 1946 | 12 |  |
| `sub_463AE0(unsigned int a2, int a3)` | 1960 | 50 |  |
| `sub_463C30(unsigned int a2, int a3, char a4)` | 2012 | 124 |  |
| `sub_463F60(int a2, int a3, int a4, int a5, __int16 a6)` | 2138 | 43 |  |
| `sub_464060(int a2, int a3, int a4, _DWORD* a5)` | 2183 | 22 |  |
| `sub_464110(int a2, int a3, int a4, char a5)` | 2207 | 10 |  |
| `sub_464160(int a2, int a3)` | 2219 | 29 |  |
| `sub_464210(int a2, int a3, int a4, int a5)` | 2253 | 11 |  |
| `sub_464250(unsigned int a2, unsigned int a3, unsigned int a4)` | 2268 | 8 |  |
| `sub_4642A0(_DWORD* a2, _DWORD* a3, _DWORD* a4, _DWORD* a5, _DWORD* a6, int* a7)` | 2280 | 11 |  |
| `sub_4644E0(unsigned int a2)` | 2295 | 31 |  |
| `sub_464550(int a2)` | 2330 | 15 |  |
| `sub_464590(SIZE_T dwBytes)` | 2349 | 14 |  |
| `sub_4645F0(SIZE_T dwBytes)` | 2367 | 14 |  |
| `sub_464640(FileMgr* dwBytes)` | 2385 | 7 |  |
| `sub_464670(FileMgr* dwBytes)` | 2396 | 7 |  |
| `sub_4646A0(int a2)` | 2407 | 56 |  |
| `sub_464880()` | 2467 | 52 |  |
| `ParseMapLine(_BYTE* a2, FileMgr* dwBytes)` | 2523 | 18 |  |
| `sub_464C70(const char* a2)` | 2583 | 28 |  |
| `sub_464D00(char* String2, unsigned char a3)` | 2615 | 18 |  |
| `sub_464DA0(char a2)` | 2637 | 37 |  |
| `sub_464E70(char a2)` | 2678 | 30 |  |
| `sub_464FE0(unsigned char a2, unsigned char a3, char a4)` | 2712 | 25 |  |
| `sub_465090(unsigned char a2, unsigned char a3)` | 2741 | 24 |  |
| `sub_465130(unsigned char a2, unsigned char a3)` | 2769 | 24 |  |
| `sub_4651C0()` | 2797 | 19 |  |
| `sub_4653C0(int a2, int a3, int a4)` | 2886 | 14 |  |
| `sub_465410(int a2, int a3, int a4)` | 2902 | 19 |  |
| `sub_465490(int a2, int a3, int a4)` | 2923 | 42 |  |
| `sub_465650(int a2, int a3, Player* a4)` | 3037 | 21 |  |
| `sub_4656D0(int a2, int a3, int a4, int a5, _DWORD* a6, char a7)` | 3060 | 496 |  |
| `sub_465FE0(AudioSourceParams* arg0)` | 3558 | 64 |  |
| `sub_466170(int arg0)` | 3624 | 86 |  |
| `sub_466380(int a2, int a3, int a4, int a5, int a6)` | 3712 | 59 |  |
| `sub_466430(int arg0, int a3, int a2, int a5, int a6)` | 3773 | 108 |  |
| `sub_466620(void* a2)` | 3883 | 64 |  |
| `sub_466730(AudioSourceParams a2)` | 3949 | 47 |  |
| `sub_466910(int a2, int a3, _DWORD* a4)` | 3998 | 35 |  |
| `FindMaxZForTile(int a2, int a3, _DWORD* a4)` | 4035 | 35 |  |
| `sub_466A00(int a2, int a3, int* a4)` | 4072 | 41 |  |
| `sub_466B70(int* a2, S202* pS202)` | 4141 | 66 |  |
| `sub_469110(int a2, int a3, char a4)` | 5716 | 80 |  |
| `sub_4692B0()` | 5798 | 50 |  |
| `ScanZoneStars(_BYTE* a1, _BYTE* a2, _BYTE* a3, char a4)` | 5850 | 109 |  |
| `sub_469570(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2)` | 5961 | 67 |  |
| `sub_4696C0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2)` | 6030 | 1 |  |
| `sub_4696C0(int* arg0, AudioSourceParams* arg4)` | 6030 | 1 |  |
| `sub_469850(SpriteS1* arg0, AudioSourceParams* arg4)` | 6123 | 68 |  |
| `sub_4699A0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2, SpriteS1* a4)` | 6193 | 72 |  |
| `sub_469B00(int* a2, SpriteS1* a3, Player* a4)` | 6267 | 53 |  |
| `sub_469F90(SpriteS1* a2, SpriteS1* arg4, Player* a4)` | 6532 | 154 |  |

## Объявлены в .h, но не определены

- `sub_466CF0(int a2, int a3, int a4)`
- `sub_466E20(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2)`
- `sub_466F70(_DWORD* arg0, S202* a2)`
- `sub_467020(int*, SpriteS1*, void*, void*, void*)`
- `sub_467110(int* arg0, Sprite* pSprite, int* a4, Player* pPlayer)`
- `sub_467F80(int** arg0, SpriteS1** a3, int* a4, Player* a5)`

## Свободные функции в .cpp (глобальные)

`sub_465350`
