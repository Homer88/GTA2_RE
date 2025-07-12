#ifndef  __D3DDLL_H_
#define __D3DDLL_H_





#include "../dmavideo/dmavideo.h"

using u16 = unsigned short int;
using s32 = signed int;
using u32 = unsigned int;
using f32 = float;
using u8 = unsigned char;

#define CC __stdcall

struct Texture
{
    unsigned short ID;
    unsigned short field_2;
    unsigned short PalIsTrans;
    unsigned short PalSize;
    void* pLockedPixels;
    BYTE field_C;
    BYTE field_D;
    unsigned short Width;
    unsigned short Height;
    u8 PalIsValid;
    u8 Flags;
    BYTE* pOriginalPixelData;
    WORD* pPaltData;
    struct Cache* NextCache; // +32 == IUnknown, DDSurface ptr ?
};
static_assert(sizeof(Texture) == 0x20, "Wrong sized STexture");

struct Vert
{
    float x, y, z, w;
    DWORD diff;
    DWORD spec;
    float u, v;
};
static_assert(sizeof(Vert) == 0x20, "wrong size");

struct Verts
{
    Vert mVerts[4];
};

struct Light
{
    DWORD field_0;  // ?? looking at map format maybe on/off time and strength/radius?
    float X;  // x ?
    float Y;  // y ?
    float Z;  // z ?
    DWORD Colour; // ARGB?
};
static_assert(sizeof(Light) == 0x14, "Wrong size SLight");

void CC ConvertColourBank(s32 unknown);
int CC DrawLine(int a1, int a2, int a3, int a4, int a5);
void CC SetShadeTableA(int a1, int a2, int a3, int a4, int a5);
int* CC MakeScreenTable(int result, int a2, unsigned int a3);
int CC gbh_AddLight(Light* pLight);
char CC gbh_AssignPalette(Texture* pTexture, int palId);
void CC gbh_BeginLevel();
int gbh_BeginScene();
int CC gbh_BlitBuffer(int a1, int a2, int a3, int a4, int a5, int a6);
char CC gbh_BlitImage(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
void CC gbh_CloseDLL();
void CC gbh_CloseScreen(Video* pVideo);
unsigned int CC gbh_Convert16BitGraphic(int a1, unsigned int a2, WORD *a3, signed int a4);
unsigned int CC gbh_ConvertColour(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3);
int CC gbh_DrawFlatRect(int a1, int a2);
void CC gbh_DrawQuad(int flags, Texture* pTexture, Vert* pVerts, int baseColour);
void CC gbh_DrawQuadClipped(int a1, int a2, int a3, int a4, int a5);
s32 CC gbh_DrawTilePart(unsigned int flags, Texture* pTexture, Vert* pData, int diffuseColour);
void CC gbh_DrawTriangle(int triFlags, Texture* pTexture, Vert* pVerts, int diffuseColour);
void CC gbh_EndLevel();
double CC gbh_EndScene();
int CC gbh_FreeImageTable();
void CC gbh_FreePalette(int a1);
void CC gbh_FreeTexture(Texture* pTexture);
u32* CC gbh_GetGlobals();
int CC gbh_GetUsedCache(int a1);
s32 CC gbh_Init(int a1);
u32 CC gbh_InitDLL(Video* pVideoDriver);
signed int CC gbh_InitImageTable(int tableSize);

#pragma pack(push)
#pragma pack(1)
struct Image
{
    BYTE field_0;
    BYTE field_1;
    BYTE field_2;
    BYTE field_3;
    DWORD field_4;
    DWORD field_8;
    WORD Width;
    WORD Height;
    BYTE field_10;
    BYTE field_11;
    DWORD field_12;
};
#pragma pack(pop)
static_assert(sizeof(Image) == 0x16, "Wrong sized SImage");

signed int CC gbh_LoadImage(Image* pImage);
Texture* CC gbh_LockTexture(Texture* pTexture);
void CC gbh_Plot(int a1, int a2, int a3, int a4);
int CC gbh_PrintBitmap(int a1, int a2);
unsigned int CC gbh_RegisterPalette(int a1, DWORD *a2);
Texture* CC gbh_RegisterTexture(__int16 width, __int16 height, BYTE* pData, int a4, char a5);
void CC gbh_ResetLights();
void CC gbh_SetAmbient(float a1);
int CC gbh_SetCamera(float a1, float a2, float a3, float a4);
int CC gbh_SetColourDepth();
float CC gbh_SetWindow(float left, float top, float right, float bottom);
Texture* CC gbh_UnlockTexture(Texture* pTexture);


struct D3DFunctions
{
    // TODO: Should probably also be pointers to function pointers
    decltype(&ConvertColourBank) pConvertColourBank;
    decltype(&DrawLine) pDrawLine;
    decltype(&SetShadeTableA) pSetShadeTableA;
    decltype(&MakeScreenTable) pMakeScreenTable;
    decltype(&gbh_AddLight) pgbh_AddLight;
    decltype(&gbh_AssignPalette) pgbh_AssignPalette;
    decltype(&gbh_BeginLevel) pgbh_BeginLevel;
    decltype(&gbh_BeginScene) pgbh_BeginScene;
    decltype(&gbh_BlitBuffer) pgbh_BlitBuffer;
    decltype(&gbh_BlitImage) pgbh_BlitImage;
    decltype(&gbh_CloseDLL) pgbh_CloseDLL;
    decltype(&gbh_CloseScreen) pgbh_CloseScreen;
    decltype(&gbh_Convert16BitGraphic) pgbh_Convert16BitGraphic;
    decltype(&gbh_ConvertColour) pgbh_ConvertColour;
    decltype(&gbh_DrawFlatRect) pgbh_DrawFlatRect;
    decltype(&gbh_DrawQuad) pgbh_DrawQuad;
    decltype(&gbh_DrawQuadClipped) pgbh_DrawQuadClipped;
    decltype(&gbh_DrawTilePart) pgbh_DrawTilePart;
    decltype(&gbh_DrawTriangle) pgbh_DrawTriangle;
    decltype(&gbh_EndLevel) pgbh_EndLevel;
    decltype(&gbh_EndScene) pgbh_EndScene;
    decltype(&gbh_FreeImageTable) pgbh_FreeImageTable;
    decltype(&gbh_FreePalette) pgbh_FreePalette;
    decltype(&gbh_FreeTexture) pgbh_FreeTexture;
    decltype(&gbh_GetGlobals) pgbh_GetGlobals;
    decltype(&gbh_GetUsedCache) pgbh_GetUsedCache;
    decltype(&gbh_Init) pgbh_Init;
    decltype(&gbh_InitDLL) pgbh_InitDLL;
    decltype(&gbh_InitImageTable) pgbh_InitImageTable;
    decltype(&gbh_LoadImage) pgbh_LoadImage;
    decltype(&gbh_LockTexture) pgbh_LockTexture;
    decltype(&gbh_Plot) pgbh_Plot;
    decltype(&gbh_PrintBitmap) pgbh_PrintBitmap;
    decltype(&gbh_RegisterPalette) pgbh_RegisterPalette;
    decltype(&gbh_RegisterTexture) pgbh_RegisterTexture;
    decltype(&gbh_ResetLights) pgbh_ResetLights;
    decltype(&gbh_SetAmbient) pgbh_SetAmbient;
    decltype(&gbh_SetCamera) pgbh_SetCamera;
    decltype(&gbh_SetColourDepth) pgbh_SetColourDepth;
    decltype(&gbh_SetWindow) pgbh_SetWindow;
    decltype(&gbh_UnlockTexture) pgbh_UnlockTexture;

    HINSTANCE hinstance;
};


inline void PopulateS3DFunctions(HINSTANCE h, D3DFunctions& f)
{
    f.hinstance = h;
    GetFunc(h, f.pConvertColourBank, "ConvertColourBank");
    GetFunc(h, f.pDrawLine, "DrawLine");
    GetFunc(h, f.pSetShadeTableA, "SetShadeTableA");
    GetFunc(h, f.pMakeScreenTable, "MakeScreenTable");
    GetFunc(h, f.pgbh_AddLight, "gbh_AddLight");
    GetFunc(h, f.pgbh_AssignPalette, "gbh_AssignPalette");
    GetFunc(h, f.pgbh_BeginLevel, "gbh_BeginLevel");
    GetFunc(h, f.pgbh_BeginScene, "gbh_BeginScene");
    GetFunc(h, f.pgbh_BlitBuffer, "gbh_BlitBuffer");
    GetFunc(h, f.pgbh_BlitImage, "gbh_BlitImage");
    GetFunc(h, f.pgbh_CloseDLL, "gbh_CloseDLL");
    GetFunc(h, f.pgbh_CloseScreen, "gbh_CloseScreen");
    GetFunc(h, f.pgbh_Convert16BitGraphic, "gbh_Convert16BitGraphic");
    GetFunc(h, f.pgbh_ConvertColour, "gbh_ConvertColour");
    GetFunc(h, f.pgbh_DrawFlatRect, "gbh_DrawFlatRect");
    GetFunc(h, f.pgbh_DrawQuad, "gbh_DrawQuad");
    GetFunc(h, f.pgbh_DrawQuadClipped, "gbh_DrawQuadClipped");
    GetFunc(h, f.pgbh_DrawTilePart, "gbh_DrawTilePart");
    GetFunc(h, f.pgbh_DrawTriangle, "gbh_DrawTriangle");
    GetFunc(h, f.pgbh_EndLevel, "gbh_EndLevel");
    GetFunc(h, f.pgbh_EndScene, "gbh_EndScene");
    GetFunc(h, f.pgbh_FreeImageTable, "gbh_FreeImageTable");
    GetFunc(h, f.pgbh_FreePalette, "gbh_FreePalette");
    GetFunc(h, f.pgbh_FreeTexture, "gbh_FreeTexture");
    GetFunc(h, f.pgbh_GetGlobals, "gbh_GetGlobals");
    GetFunc(h, f.pgbh_GetUsedCache, "gbh_GetUsedCache");
    GetFunc(h, f.pgbh_Init, "gbh_Init");
    GetFunc(h, f.pgbh_InitDLL, "gbh_InitDLL");
    GetFunc(h, f.pgbh_InitImageTable, "gbh_InitImageTable");
    GetFunc(h, f.pgbh_LoadImage, "gbh_LoadImage");
    GetFunc(h, f.pgbh_LockTexture, "gbh_LockTexture");
    GetFunc(h, f.pgbh_Plot, "gbh_Plot");
    GetFunc(h, f.pgbh_PrintBitmap, "gbh_PrintBitmap");
    GetFunc(h, f.pgbh_RegisterPalette, "gbh_RegisterPalette");
    GetFunc(h, f.pgbh_RegisterTexture, "gbh_RegisterTexture");
    GetFunc(h, f.pgbh_ResetLights, "gbh_ResetLights");
    GetFunc(h, f.pgbh_SetAmbient, "gbh_SetAmbient");
    GetFunc(h, f.pgbh_SetCamera, "gbh_SetCamera");
    GetFunc(h, f.pgbh_SetColourDepth, "gbh_SetColourDepth");
    GetFunc(h, f.pgbh_SetWindow, "gbh_SetWindow");
    GetFunc(h, f.pgbh_UnlockTexture, "gbh_UnlockTexture");
}

#endif // ! __D3DDLL_H_
