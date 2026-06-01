#ifndef  __D3DDLL_H_
#define __D3DDLL_H_

#include "../dmavideo/dmavideo.h"

typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef unsigned char u8;

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
    struct Cache* NextCache;
};

struct Vert
{
    float x, y, z, w;
    DWORD diff;
    DWORD spec;
    float u, v;
};

struct Verts
{
    Vert mVerts[4];
};

struct Light
{
    DWORD field_0;
    float X;
    float Y;
    float Z;
    DWORD Colour;
};

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
unsigned int CC gbh_Convert16BitGraphic(int a1, unsigned int a2, WORD* a3, signed int a4);
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

signed int CC gbh_LoadImage(Image* pImage);
Texture* CC gbh_LockTexture(Texture* pTexture);
void CC gbh_Plot(int a1, int a2, int a3, int a4);
int CC gbh_PrintBitmap(int a1, int a2);
unsigned int CC gbh_RegisterPalette(int a1, DWORD* a2);
Texture* CC gbh_RegisterTexture(__int16 width, __int16 height, BYTE* pData, int a4, char a5);
void CC gbh_ResetLights();
void CC gbh_SetAmbient(float a1);
int CC gbh_SetCamera(float a1, float a2, float a3, float a4);
int CC gbh_SetColourDepth();
float CC gbh_SetWindow(float left, float top, float right, float bottom);
Texture* CC gbh_UnlockTexture(Texture* pTexture);

struct D3DFunctions
{
    void (CC *pConvertColourBank)(s32);
    int (CC *pDrawLine)(int, int, int, int, int);
    void (CC *pSetShadeTableA)(int, int, int, int, int);
    int* (CC *pMakeScreenTable)(int, int, unsigned int);
    int (CC *pgbh_AddLight)(Light*);
    char (CC *pgbh_AssignPalette)(Texture*, int);
    void (CC *pgbh_BeginLevel)();
    int (CC *pgbh_BeginScene)();
    int (CC *pgbh_BlitBuffer)(int, int, int, int, int, int);
    char (CC *pgbh_BlitImage)(int, int, int, int, int, int, int);
    void (CC *pgbh_CloseDLL)();
    void (CC *pgbh_CloseScreen)(Video*);
    unsigned int (CC *pgbh_Convert16BitGraphic)(int, unsigned int, WORD*, signed int);
    unsigned int (CC *pgbh_ConvertColour)(unsigned __int8, unsigned __int8, unsigned __int8);
    int (CC *pgbh_DrawFlatRect)(int, int);
    void (CC *pgbh_DrawQuad)(int, Texture*, Vert*, int);
    void (CC *pgbh_DrawQuadClipped)(int, int, int, int, int);
    s32 (CC *pgbh_DrawTilePart)(unsigned int, Texture*, Vert*, int);
    void (CC *pgbh_DrawTriangle)(int, Texture*, Vert*, int);
    void (CC *pgbh_EndLevel)();
    double (CC *pgbh_EndScene)();
    int (CC *pgbh_FreeImageTable)();
    void (CC *pgbh_FreePalette)(int);
    void (CC *pgbh_FreeTexture)(Texture*);
    u32* (CC *pgbh_GetGlobals)();
    int (CC *pgbh_GetUsedCache)(int);
    s32 (CC *pgbh_Init)(int);
    u32 (CC *pgbh_InitDLL)(Video*);
    signed int (CC *pgbh_InitImageTable)(int);
    signed int (CC *pgbh_LoadImage)(Image*);
    Texture* (CC *pgbh_LockTexture)(Texture*);
    void (CC *pgbh_Plot)(int, int, int, int);
    int (CC *pgbh_PrintBitmap)(int, int);
    unsigned int (CC *pgbh_RegisterPalette)(int, DWORD*);
    Texture* (CC *pgbh_RegisterTexture)(__int16, __int16, BYTE*, int, char);
    void (CC *pgbh_ResetLights)();
    void (CC *pgbh_SetAmbient)(float);
    int (CC *pgbh_SetCamera)(float, float, float, float);
    int (CC *pgbh_SetColourDepth)();
    float (CC *pgbh_SetWindow)(float, float, float, float);
    Texture* (CC *pgbh_UnlockTexture)(Texture*);

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
