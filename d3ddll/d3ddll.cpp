#include "d3ddll.h"
#include <cmath>
#include <d3d.h>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <assert.h>

#define BYTEn(x, n)   (*((BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)

#pragma comment(lib, "dxguid.lib")

static bool gProxyOnly = false;      // Pass through all functions to real DLL
static bool gDetours = false;       // Used in combination with gProxyOnly=true to hook some internal functions to test them in isolation
static bool gRealPtrs = false;

// Other
static D3DFunctions gFuncs;

struct D3DDevice
{
    DWORD ID;
    char* DeviceName;
    char* DeviceDescription1;
    struct TextureFormat* FirstTextureFormat;
    struct TextureFormat* pFirstTextureFormat;
    struct HardwareTexture* pHead;
    struct HardwareTexture* IDirect3dTexture2List;
    DWORD NumTextureEnums;
    DWORD Flags;
    D3DDEVICEDESC DeviceDescription;
    DWORD Context;
    D3DDEVICEDESC field_124;
    GUID DeviceGuid;
    struct D3DDevice* NextD3DDevice;
    DWORD BackingBuffer;
    DWORD field_238;
};

static_assert(sizeof(D3DDEVICEDESC) == 0xfc, "Wrong size D3DDEVICEDESC");
static_assert(sizeof(D3DDevice) == 0x23C, "Wrong size D3DDevice");

struct D3dStruct
{
    Video* VideoDriver;
    D3DDevice* NextDevice;
    D3DDevice* FirstDevice;
    DWORD DeviceIDGen;
    DWORD NumEnums;
    D3DDevice* ActiveDevice;
    DWORD CurrentID;
    struct TextureFormat* TextureFormat;
    struct TextureFormat* TextureFormat1;
    IDirect3D3* pIDirect3D3;
    IDirect3DDevice3* pIDirect3DDevice3;
    IDirect3DViewport3* pIDirect3DViewPort3;
    D3DVIEWPORT2 D3DVIEWPORT2;
    DWORD pitchQ;// проверять
    IDirectDrawSurface4* IUnknown;
};
static_assert(sizeof(D3dStruct) == 0x64, "Wrong size D3dStruct");

// From dll
static bool gbSurfaceIsFreed = false;

static struct HardwareTexture* hack2 = nullptr;
static struct HardwareTexture** gActiveTextureId = &hack2;
static double qword_2B60848 = 0;
static DWORD FrameNumber = 0;

// Texture cache related
static WORD TextureSizes[12] = { 8, 16, 32, 64, 128, 256, 1032, 1040, 1056, 1088, 1152, 1280 };

struct Globals
{
    DWORD mNumPolysDrawn; // gNumPolysDrawn_dword_E43EA0
    DWORD mNumTextureSwaps; // gGlobals.mNumTextureSwaps
    DWORD mNumBatchFlushes;
    DWORD mSceneTime; // gSceneTime_2B93EAC


    DWORD gCacheSizes[12];
    DWORD gCacheSizes1[12];

    // TODO: This is displayed 1 column before where expected, some other 12 DWORD array
    // must be read for that one ??
    DWORD gCacheHitRates[12]; // Cache hit counters


    // TODO: Not really part of this
    DWORD gCacheUnknown[12] = { 10, 62, 62, 88, 1, 0, 110, 126, 126, 40, 10, 0 };
    Cache* CacheArray [12] = {};

};
static Globals gGlobals = {};


static DWORD bPointFilteringOn = 0;

DWORD hack3 = 0;
static DWORD* renderStateCache = &hack3;

static Video* gVideoDriver = nullptr;

D3dStruct* hack = nullptr;
static struct D3dStruct** gD3dPtr = &hack;
static VideoFunctions gVideoDriverFuncs;


static float gWindowLeft;
static float gWindowRight;
static float gWindowTop;
static float gWindowBottom;
static DWORD gWindow_d5;

static float k1_2B638A0;

static DWORD gGpuSpecificHack = 0;
static DWORD gbIsAtiRagePro = 0;




static int gScreenTableSize = 0;
static int gScreenTable[1700];
float gfAmbient = 1.0f;

struct ImageTableEntry
{
    BOOL Loaded;
    DWORD W;
    DWORD H;
    IDirectDrawSurface4* pSurface;
};
static_assert(sizeof(ImageTableEntry) == 0x10, "Wrong size ImageTableEntry");

static ImageTableEntry* gImageTable = nullptr;
static DWORD gImageTableCount = 0;

static u32 gTextureId = 0;

struct PalData
{
    DWORD* mPOriginalData;
    WORD* mPData;
    DWORD mbLoaded;
};
static_assert(sizeof(PalData) == 0xC, "Wrong size SPalData");

static PalData pals[16384];


struct Cache
{
    BYTE field_0;
    BYTE Flags;
    BYTE field_2;
    BYTE field_3;
    WORD field_4;
    WORD CacheIdx;
    DWORD UsedFrameNum;
    float field_C;
    DWORD field_10;
    DWORD field_14;
    struct Texture* pTexture;
    struct Cache* pNextCache;
    struct Cache* pCache;
    struct HardwareTexture* TextureId;
    DWORD field_28;
};
static_assert(sizeof(Cache) == 0x2C, "Wrong size Cache");

Texture* __stdcall TextureCache(Texture* pTexture)
{
    Cache* pCache = pTexture->NextCache;
    if (pCache)
    {
        pCache->Flags |= 0x80u;
        
        // Remove the active texture
        pCache->pTexture = nullptr;

        // Set the active frame to the current frame
        pCache->UsedFrameNum = FrameNumber - 1;

        // Remove the active cache
        pTexture->NextCache = 0;

        auto p20Cache = pCache->pCache;
        if (p20Cache)
        {
            // Set next free item to the no longer in use cache ?
            p20Cache->pNextCache = pCache->pNextCache;
            
            // If there is a next item point to root?
            auto pNext = pCache->pNextCache;
            if (pNext)
            {
                pNext->pCache = pCache->pCache;
            }
            else
            {
                // Otherwise this item is the root
                gGlobals.CacheArray [pCache->CacheIdx] = pCache->pCache;
            }

            // Set the first item to the root of the cache list ?
            pCache->pNextCache = gGlobals.CacheArray [pCache->CacheIdx];

            gGlobals.CacheArray [pCache->CacheIdx]->pCache = pCache;
            gGlobals.CacheArray [pCache->CacheIdx] = pCache;
            pCache->pCache = 0;
        }
    }
    return pTexture;
}


struct LightInternal{
    DWORD Flags;
    float Brightness;
    float Radius;
    float RadiusSquared;
    float RadiusNormalized; // A byte of Light field_10

                                      // x from Light?
    float X;

    // y from Light?
    float Y; // Light verts takes pointer to here

                      // z from Light?
    float Z;

    // Light field_10 bytes
    float Red;
    float Green;
    float Blue;
};
static_assert(sizeof(LightInternal) == 0x2c, "Wrong size LightInternal");

static LightInternal Lights[256] = {};


void CC ConvertColourBank(s32 unknown)
{
    // Empty/NOP in real game
}

const char *__stdcall D3dErr2String(int err)
{
    switch (err)
    {
    case D3D_OK: return "D3D_OK";
    case D3DERR_BADMAJORVERSION: return "D3DERR_BADMAJORVERSION";
    case D3DERR_ZBUFF_NEEDS_VIDEOMEMORY: return "D3DERR_ZBUFF_NEEDS_VIDEOMEMORY (new for DirectX 5)";
    case D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY: return "D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY (new for DirectX 5)";
    case D3DERR_VIEWPORTHASNODEVICE: return "D3DERR_VIEWPORTHASNODEVICE (new for DirectX 5)";
    case D3DERR_VIEWPORTDATANOTSET: return "D3DERR_VIEWPORTDATANOTSET (new for DirectX 5)";
    case D3DERR_TEXTURE_UNLOCK_FAILED: return "D3DERR_TEXTURE_UNLOCK_FAILED";
    case D3DERR_TEXTURE_SWAP_FAILED: return "D3DERR_TEXTURE_SWAP_FAILED";
    case D3DERR_TEXTURE_NOT_LOCKED: return "D3DERR_TEXTURE_NOT_LOCKED";
    case D3DERR_TEXTURE_NO_SUPPORT: return "D3DERR_TEXTURE_NO_SUPPORT";
    case D3DERR_TEXTURE_LOCKED: return "D3DERR_TEXTURE_LOCKED";
    case D3DERR_TEXTURE_LOCK_FAILED: return "D3DERR_TEXTURE_LOCK_FAILED";
    case D3DERR_TEXTURE_LOAD_FAILED: return "D3DERR_TEXTURE_LOAD_FAILED";
    case D3DERR_TEXTURE_GETSURF_FAILED: return "D3DERR_TEXTURE_GETSURF_FAILED";
    case D3DERR_TEXTURE_DESTROY_FAILED: return "D3DERR_TEXTURE_DESTROY_FAILED";
    case D3DERR_TEXTURE_CREATE_FAILED: return "D3DERR_TEXTURE_CREATE_FAILED";
    case D3DERR_TEXTURE_BADSIZE: return "D3DERR_TEXTURE_BADSIZE (new for DirectX 5)";
    case D3DERR_SURFACENOTINVIDMEM: return "D3DERR_SURFACENOTINVIDMEM (new for DirectX 5)";
    case D3DERR_SETVIEWPORTDATA_FAILED: return "D3DERR_SETVIEWPORTDATA_FAILED";
    case D3DERR_SCENE_NOT_IN_SCENE: return "D3DERR_SCENE_NOT_IN_SCENE";
    case D3DERR_SCENE_IN_SCENE: return "D3DERR_SCENE_IN_SCENE";
    case D3DERR_SCENE_END_FAILED: return "D3DERR_SCENE_END_FAILED";
    case D3DERR_SCENE_BEGIN_FAILED: return "D3DERR_SCENE_BEGIN_FAILED";
    case D3DERR_NOVIEWPORTS: return "D3DERR_NOVIEWPORTS (new for DirectX 5)";
    case D3DERR_NOTINBEGIN: return "D3DERR_NOTINBEGIN (new for DirectX 5)";
    case D3DERR_NOCURRENTVIEWPORT: return "D3DERR_NOCURRENTVIEWPORT (new for DirectX 5)";
    case D3DERR_MATRIX_SETDATA_FAILED: return "D3DERR_MATRIX_SETDATA_FAILED";
    case D3DERR_MATRIX_GETDATA_FAILED: return "D3DERR_MATRIX_GETDATA_FAILED";
    case D3DERR_MATRIX_DESTROY_FAILED: return "D3DERR_MATRIX_DESTROY_FAILED";
    case D3DERR_MATRIX_CREATE_FAILED: return "D3DERR_MATRIX_CREATE_FAILED";
    case D3DERR_MATERIAL_SETDATA_FAILED: return "D3DERR_MATERIAL_SETDATA_FAILED";
    case D3DERR_MATERIAL_GETDATA_FAILED: return "D3DERR_MATERIAL_GETDATA_FAILED";
    case D3DERR_MATERIAL_DESTROY_FAILED: return "D3DERR_MATERIAL_DESTROY_FAILED";
    case D3DERR_MATERIAL_CREATE_FAILED: return "D3DERR_MATERIAL_CREATE_FAILED";
    case D3DERR_LIGHTNOTINTHISVIEWPORT: return "D3DERR_LIGHTNOTINTHISVIEWPORT (new for DirectX 5)";
    case D3DERR_LIGHTHASVIEWPORT: return "D3DERR_LIGHTHASVIEWPORT (new for DirectX 5)";
    case D3DERR_LIGHT_SET_FAILED: return "D3DERR_LIGHT_SET_FAILED";
    case D3DERR_INVALIDVERTEXTYPE: return "D3DERR_INVALIDVERTEXTYPE (new for DirectX 5)";
    case D3DERR_INVALIDRAMPTEXTURE: return "D3DERR_INVALIDRAMPTEXTURE (new for DirectX 5)";
    case D3DERR_INVALIDPRIMITIVETYPE: return "D3DERR_INVALIDPRIMITIVETYPE (new for DirectX 5)";
    case D3DERR_INVALIDPALETTE: return "D3DERR_INVALIDPALETTE(new for DirectX 5)";
    case D3DERR_INVALIDCURRENTVIEWPORT: return "D3DERR_INVALIDCURRENTVIEWPORT (new for DirectX 5)";
    case D3DERR_INVALID_DEVICE: return "D3DERR_INVALID_DEVICE (new for DirectX 5)";
    case D3DERR_INBEGIN: return "D3DERR_INBEGIN (new for DirectX 5)";
    case D3DERR_INITFAILED: return "D3DERR_INITFAILED (new for DirectX 5)";
    case D3DERR_EXECUTE_UNLOCK_FAILED: return "D3DERR_EXECUTE_UNLOCK_FAILED";
    case D3DERR_EXECUTE_NOT_LOCKED: return "D3DERR_EXECUTE_NOT_LOCKED";
    case D3DERR_EXECUTE_LOCKED: return "D3DERR_EXECUTE_LOCKED";
    case D3DERR_EXECUTE_LOCK_FAILED: return "D3DERR_EXECUTE_LOCK_FAILED";
    case D3DERR_EXECUTE_CLIPPED_FAILED: return "D3DERR_EXECUTE_CLIPPED_FAILED";
    case D3DERR_DEVICEAGGREGATED: return "D3DERR_DEVICEAGGREGATED (new for DirectX 5)";
    case D3DERR_BADMINORVERSION: return "D3DERR_BADMINORVERSION";
    default: return "Unrecognized error value.";
    }
}

int CC DrawLine(int a1, int a2, int a3, int a4, int a5)
{
    return std::abs(a4 - a2);
}

void CC SetShadeTableA(int a1, int a2, int a3, int a4, int a5)
{
    __debugbreak();
}

int* CC MakeScreenTable(int value, int elementSize, unsigned int size)
{
    // TODO
    if (gProxyOnly)
    {
        return gFuncs.pMakeScreenTable(value, elementSize, size);
    }

    int* result = 0;
    gScreenTableSize= size;
    if (size)
    {
        result = gScreenTable;
        do
        {
            *result = value;
            value += elementSize;
            ++result;
            --size;
        } while (size);
    }
    return result;
}


char CC gbh_AssignPalette(Texture* pTexture, int palId)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_AssignPalette(pTexture, palId);
    }
    
    bool needUnlock = false;
    if (!(pTexture->Flags & 1))
    {
        gbh_LockTexture(pTexture);
        needUnlock = true;
    }

    pTexture->pPaltData = pals[palId].mPData;
    const auto result = pals[palId].mbLoaded;
    pTexture->PalIsValid = result;

    if (needUnlock)
    {
        gbh_UnlockTexture(pTexture);
    }
    return result;
}

void CC gbh_BeginLevel()
{
    __debugbreak();
}

static BOOL __stdcall DeviceBeginScene(D3dStruct* pCtx)
{
    return pCtx->pIDirect3DDevice3->BeginScene() != 0;
}

int gbh_BeginScene()
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_BeginScene();
    }

    if (gVideoDriver->Flags & 1)
    {
        gbSurfaceIsFreed= true;
        (*gVideoDriver->initDLL->pVid_FreeSurface)(gVideoDriver);
    }
    else
    {
        gbSurfaceIsFreed = false;
    }
    memset(gGlobals.gCacheHitRates, 0, sizeof(gGlobals.gCacheHitRates));
    gGlobals.mNumBatchFlushes = 0;
    gGlobals.mNumTextureSwaps = 0;
    gGlobals.mNumPolysDrawn = 0;
    (*gActiveTextureId) = (HardwareTexture*)-1;
    qword_2B60848 = 0i64;
    ++FrameNumber;
    return DeviceBeginScene((*gD3dPtr));
}

int CC gbh_BlitBuffer(int a1, int a2, int a3, int a4, int a5, int a6)
{
    __debugbreak();
    return 0;
}

char CC gbh_BlitImage(int imageIndex, int srcLeft, int srcTop, int srcRight, int srcBottom, int dstX, int dstY)
{
    if (gProxyOnly)
    {
         return gFuncs.pgbh_BlitImage(imageIndex, srcLeft, srcTop, srcRight, srcBottom, dstX, dstY);
    }

    int result = 0;
    if (imageIndex > gImageTableCount)
    {
        result = -1;
    }

    if (!gImageTable[imageIndex].Loaded)
    {
        return -1;
    }

    if (srcLeft < 0
        || srcTop < 0
        || srcRight < 0
        || srcBottom < 0
        || srcLeft >gImageTable[imageIndex].W
        || srcTop >gImageTable[imageIndex].H
        || srcRight >gImageTable[imageIndex].W
        || srcBottom >gImageTable[imageIndex].H)
    {
        return -2;
    }

    if (dstX < 0 || dstY < 0
        || (dstX - srcLeft + srcRight) > gVideoDriver->RectRight
        || (dstY - srcTop + srcBottom) > gVideoDriver->RectBottom)
    {
        return -3;
    }

    if (gImageTable[imageIndex].pSurface->IsLost())
    {
        gImageTable[imageIndex].pSurface->Release();
        gImageTable[imageIndex].pSurface = nullptr;
        return  -10;
    }

    RECT srcRect = {};
    srcRect.left = srcLeft;
    srcRect.top = srcTop;
    srcRect.right = srcRight;
    srcRect.bottom = srcBottom;

    RECT dstRect = {};
    dstRect.left = dstX;
    dstRect.top = dstY;
    dstRect.right = dstX - srcLeft + srcRight;
    dstRect.bottom = dstY - srcTop + srcBottom;

    if (!gVideoDriver->Surface)
    {
        return -4;
    }

    if (FAILED(gVideoDriver->Surface->Blt(
        &dstRect,
        (LPDIRECTDRAWSURFACE4)gImageTable[imageIndex].pSurface,
        &srcRect,
        DDBLT_WAIT,
        0)))
    {
        return -4;
    }

    return 0;
}

static int __stdcall FreeD3dDThings(D3dStruct* pD3d);

static void CleanUpD3d()
{
    for (int idx = 0; idx < 12; idx++)
    {
        auto pCache = gGlobals.CacheArray[idx];
        if (pCache)
        {
            Cache* pCurrentCache = nullptr;
            do
            {
                pCurrentCache = pCache->pNextCache;
                if (pCache->pTexture)
                {
                    TextureCache(pCache->pTexture);
                }

                auto nextPtr = pCache->pNextCache;
                if (nextPtr)
                {
                    nextPtr->pCache = 0;
                    gGlobals.CacheArray [idx] = pCache->pNextCache;
                }
                free(pCache);
                pCache = pCurrentCache;
            } while (pCurrentCache);
        }
        gGlobals.CacheArray [idx] = 0;
    }

    if (*gD3dPtr)
    {
        FreeD3dDThings(*gD3dPtr);
    }
    (*gD3dPtr) = 0;
}

static decltype(&Vid_CloseScreen) pOldCloseScreen = nullptr;
static decltype(&Vid_SetMode) pOldSetMode = nullptr;

void CC gbh_CloseDLL()
{


    if (gProxyOnly)
    {
        return gFuncs.pgbh_CloseDLL();
    }

    auto pVideoDriver = (*gD3dPtr)->VideoDriver;

    CleanUpD3d();

    pOldCloseScreen(pVideoDriver);

    *pVideoDriver->initDLL->pVid_CloseScreen = pOldCloseScreen;
    //*pVideoDriver->initDLL->pVid_GetSurface = gVideoDriverFuncs.pVid_GetSurface;
    //*pVideoDriver->initDLL->pVid_FreeSurface = gVideoDriverFuncs.pVid_FreeSurface;
    *pVideoDriver->initDLL->pVid_SetMode = pOldSetMode;

    /*
    free(gPtr_dword_E13864); // TODO: Lighting table
    gPtr_dword_E13864 = 0;
    free(gPtr_dword_E43E20); // TODO: Allocated but never used
    gPtr_dword_E43E20 = 0;*/

}

void CC gbh_CloseScreen(Video* pVideo)
{
    ///TRACE_ENTRYEXIT;

    CleanUpD3d();
    pOldCloseScreen(pVideo);
    //(*pVideo->initDLL->pVid_CloseScreen)(pVideo);
}

unsigned int CC gbh_Convert16BitGraphic(int a1, unsigned int a2, WORD *a3, signed int a4)
{
    __debugbreak();
    return 0;
}

unsigned int CC gbh_ConvertColour(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
    __debugbreak();
    return 0;
}

int CC gbh_DrawFlatRect(int a1, int a2)
{
    __debugbreak();
    return 0;
}

#undef max
#undef min

static bool Clipped(Vert* pVerts, int count)
{
    float maxX = pVerts[0].x;
    for (auto i = 1; i < count; i++)
    {
        maxX = std::max(maxX, pVerts[i].x);
    }

    float minX = pVerts[0].x;
    for (auto i = 1; i < count; i++)
    {
        minX = std::min(minX, pVerts[i].x);
    }

    float maxY = pVerts[0].y;
    for (auto i = 1; i < count; i++)
    {
        maxY = std::max(maxY, pVerts[i].y);
    }

    float minY = pVerts[0].y;
    for (auto i = 1; i < count; i++)
    {
        minY = std::min(minY, pVerts[i].y);
    }

    return (maxX < gWindowLeft
        && minX >= gWindowRight
        && minY < gWindowBottom
        && maxY >= gWindowTop);
}

static void  __stdcall SetRenderStates(int states);
decltype(&SetRenderStates) pSetRenderStates = 0x0;

static void  __stdcall SetRenderStates(int states)
{
    if (states & 0x380)
    {
        if (states & 0x200) 
        {
            auto result = (*renderStateCache);
            if ((*renderStateCache) == 1)
            {
                result = 0;
                (*renderStateCache) = 0;
            }

            if (!result)
            {
                (*renderStateCache) = 2;
                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 1); // 27, 1
                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE); // 19, 1
                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE); // 20, 1
            }
        }
        else if (states & 0x180)
        {
            auto result = (*renderStateCache);
            if ((*renderStateCache) == 2)
            {
                result = 0;
                (*renderStateCache) = 0;
            }
            if (!result)
            {
                (*renderStateCache) = 1;

                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA); // 21, 4
                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 1); // 27, 1
                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA); // 19, 5
                (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA); // 20, 6
            }
        }
    }
    else
    {
        if ((*renderStateCache))
        {
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 0); // 27, 0
            (*renderStateCache) = 0;
        }
    }
}

static Texture* pLast = nullptr;

#define HIBYTE(x)   (*((BYTE*)&(x)+1))

static signed int __stdcall D3dTextureUnknown(HardwareTexture* pHardwareTexture, BYTE* pixelData, WORD* pPalData, int textureW, int textureH, int palSize, int renderFlags, char textureFlags);

static unsigned __int16 __stdcall CacheFlushBatchRelated(Texture *pTexture, int renderFlags);
decltype(&CacheFlushBatchRelated) pCacheFlushBatchRelated_2B52810 = 0x0;

static unsigned __int16 __stdcall CacheFlushBatchRelated(Texture *pTexture, int renderFlags)
{
    int biggestSide = pTexture->Width;
    if (pTexture->Height  >biggestSide)
    {
        biggestSide = pTexture->Height;
    }

    auto flagsCopy = renderFlags;
    if (renderFlags & 0x380)
    {
        HIBYTE(biggestSide) |= 4u;
        flagsCopy = renderFlags | 0x80;
    }


    auto cache_index = 0;
    while (biggestSide > TextureSizes[cache_index])
    {
        if (++cache_index >= 12)
        {
            break;
        }
    }


    auto pCache = gGlobals.CacheArray [cache_index];
    if (pCache-> UsedFrameNum == FrameNumber)
    {
        ++gGlobals.mNumBatchFlushes;
        (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_FLUSHBATCH, 1);
        ++FrameNumber;
    }

    auto pCachedTexture = pCache->pTexture;
    if (pCachedTexture)
    {
        pCachedTexture->NextCache = 0;
    }

    pTexture->NextCache = pCache;

    pCache->field_0 &= 0x7FFFu;
    pCache->pTexture = pTexture;
    auto pPal = pTexture->pPaltData;
    
    // Pointer to texture pixel data TODO Why are field_C and D used? Some header data ?
    auto v8 = pTexture->field_C + (pTexture->field_D << 8) + pTexture->pOriginalPixelData;

    pCache->field_10 = 0.00390625 / (double)pTexture->PalIsValid;
    pCache->field_14 = 0.00390625 / (double)pTexture->PalIsValid * 255.0;
    
    auto textureFlags = pTexture->Flags;

    D3dTextureUnknown(
        pCache->TextureId,
        v8,
        flagsCopy & 0x380 ? (pPal + 256) : pPal,
        pTexture->Width,
        pTexture->Height,
        256,
        flagsCopy,
        textureFlags);

    auto result = pCache->CacheIdx;

    ++gGlobals.gCacheHitRates[result];

   return 0;

}

static DWORD NumLights = 0; // 43E38

int __stdcall LightVerts_new(int vertCount, Vert* pVerts, int alwaysZero, unsigned __int8 colourRelated)
{
    for (int vertIdx = 0; vertIdx < vertCount; vertIdx++)
    {
        float light_r = 0.0f;
        float light_g = 0.0f;
        float light_b = 0.0f;
        for (int j = 0; j < NumLights; j++)
        {
            if ((Lights[j].Flags & 0x30000) == 0x10000) // Light type ?
            {
                // Check if vertex point is within light radius

                // TODO: This has caused me no end of trouble, it appears no matter if quad or tri the 5th index
                // is used to check the position, this means we always have:
                // vert0
                // vert1
                // vert2
                // vert3 - optional, if tri then nothing
                // ?? 0-4 for lighting, perhaps actually normals ?

                const float dx = pVerts[vertIdx + 4].x - Lights[j].X ;
                const float dy = pVerts[vertIdx + 4].y - Lights[j].Y;
                const float dz = pVerts[vertIdx + 4].z - Lights[j].Z;


                const float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);

                if (distanceSquared <= Lights[j].RadiusSquared)
                {
                    const float distance = sqrt(distanceSquared);
                    const float normalizedDistance = (Lights[j].Radius - distance) * Lights[j].RadiusNormalized;
                    if (normalizedDistance > 0.0f)
                    {
                        auto lightWithBrightness = normalizedDistance * Lights[j].Brightness;
                        light_r = light_r + Lights[j].Red * lightWithBrightness;
                        light_g = light_g + Lights[j].Green * lightWithBrightness;
                        light_b = light_b + Lights[j].Blue * lightWithBrightness;
                    }
                }
            }
        }

        const float colourConverted = colourRelated * 0.0039215689f;

        const auto diffB2 = (double)(((unsigned int)pVerts[vertIdx].diff >> 16) & 0xFF);
        auto b1 = colourConverted * diffB2 * light_r + gfAmbient;
        if (b1 > 255.0f)
        {
            b1 = 255.0f;
        }

        const auto diffB1 = (double)((unsigned __int16)pVerts[vertIdx].diff >> 8);
        auto b2 = colourConverted * diffB1 * light_g + gfAmbient;
        if (b2 > 255.0f)
        {
            b2 = 255.0f;
        }

        auto diffB0 = (double)(unsigned __int8)pVerts[vertIdx].diff;
        auto b3 = colourConverted * diffB0 * light_b + gfAmbient;
        if (b3 > 255.0f)
        {
            b3 = 255.0f;
        }

        pVerts[vertIdx].diff = (signed int)b3 | pVerts[vertIdx].diff & 0xFF000000 | (((signed int)b2 | ((signed int)b1 << 8)) << 8);
    }

    return 0;
}

static signed int __stdcall D3dTextureSetCurrent(HardwareTexture *pHardwareTexture);

void CC gbh_DrawTriangle(int triFlags, Texture* pTexture, Vert* pVerts, int diffuseColour)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_DrawTriangle(triFlags, pTexture, pVerts, diffuseColour);
    }

    if (pVerts[0].z <= 0.0f)
    {
        return;
    }

    if (Clipped(pVerts, 3))
    {
        return;
    }

    SetRenderStates(triFlags);

    // TODO: All duplicated in quad rendering func
    if (triFlags & 0x20000)
    {
        if (!bPointFilteringOn)
        {
            bPointFilteringOn = 1;
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DTFG_POINT);
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DTFG_POINT);
        }
    }
    else
    {
        if (bPointFilteringOn)
        {
            bPointFilteringOn = 0;
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DTFG_LINEAR);
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DTFG_LINEAR);
        }
    }

    // TODO: Refactor with quad drawing

    pTexture->Flags &= 0xBF;
    pTexture->Flags |= 0x40;
    if (pTexture->NextCache)
    {
        if (pTexture->Flags & 0x80)
        {
            if (pTexture->Flags & 0x40 && triFlags & 0x300)
            {
                TextureCache(pTexture);
                CacheFlushBatchRelated(pTexture, triFlags);
                pTexture->Flags &= 0xBF;
            }
            else if (pTexture->Flags & 0x40 || triFlags & 0x300)
            {
                // Skip
            }
            else
            {
                TextureCache(pTexture);
                CacheFlushBatchRelated(pTexture, triFlags);

                pTexture->Flags |= 0x40;
            }
        }
    }
    else
    {
        CacheFlushBatchRelated(pTexture, triFlags);
        auto v9 = pTexture->Flags;
        if (triFlags & 0x300)
        {
            pTexture->Flags &= 0xBF;

        }
        else
        {
            pTexture->Flags |= 0x40;
        }
    }

    const auto pTextureCache = pTexture->NextCache;
    const auto pHardwareTexture = pTextureCache->TextureId;
    if ((*gActiveTextureId) != pHardwareTexture)
    {
        D3dTextureSetCurrent(pTextureCache->TextureId);
        (*gActiveTextureId) = pHardwareTexture;
        ++gGlobals.mNumTextureSwaps;
        const auto v15 = pTextureCache->pNextCache ;
        pTextureCache->UsedFrameNum = FrameNumber;
        if (v15)
        {
            auto pCache = pTextureCache->pCache;

            if (pCache)
            {
                pCache->pNextCache = v15;
            }
            else
            {
                gGlobals.CacheArray [pTextureCache->CacheIdx] = v15;
            }

            pTextureCache->pNextCache->pCache = pTextureCache->pCache;
            const auto cacheIdx = pTextureCache->CacheIdx;
            pTextureCache->pNextCache = 0;
            pTextureCache->pCache = gGlobals.CacheArray [cacheIdx];
            gGlobals.CacheArray [cacheIdx]->pNextCache = pTextureCache;
            gGlobals.CacheArray [pTextureCache->CacheIdx] = pTextureCache;
        }
    }

    const float uvScale = pTexture->NextCache->field_C;


    pVerts[0].w = pVerts[0].z;
    pVerts[1].w = pVerts[1].z;
    pVerts[2].w = pVerts[2].z;

    pVerts[0].u *= uvScale;
    pVerts[0].v *= uvScale;
    pVerts[1].u *= uvScale;
    pVerts[1].v *= uvScale;
    pVerts[2].u *= uvScale;
    pVerts[2].v *= uvScale;


    if (!(BYTE1(triFlags) & 0x20))
    {
        const auto finalDiffuseColour = (unsigned __int8)diffuseColour | (((unsigned __int8)diffuseColour | ((diffuseColour | 0xFFFFFF00) << 8)) << 8);
        pVerts[0].diff = finalDiffuseColour;
        pVerts[1].diff = finalDiffuseColour;
        pVerts[2].diff = finalDiffuseColour;
    }

    pVerts[0].spec = 0;
    pVerts[1].spec = 0;
    pVerts[2].spec = 0;


    if (BYTE1(triFlags) & 0x80 && gfAmbient != 255.0)
    {
        LightVerts_new(3, pVerts, 0, diffuseColour);
    }

    if (SUCCEEDED((*gD3dPtr)->pIDirect3DDevice3->DrawPrimitive(
        D3DPT_TRIANGLELIST, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1, pVerts, 3, D3DDP_DONOTUPDATEEXTENTS)))
    {
        gGlobals.mNumPolysDrawn++;
    }

    return;
}


void CC gbh_DrawQuad(int quadFlags, Texture* pTexture, Vert* pVerts, int baseColour)
{

    if (gProxyOnly)
    {

         return gFuncs.pgbh_DrawQuad(quadFlags, pTexture, pVerts, baseColour);
    }

    // Flags meanings:
    // 0x10000 = fit quad and texture coords to texture size
    // 0x20000 = texture filtering, force enabled by 0x10000
    // 0x300 = alpha blending, 0x80 picks sub blending mode
    // 0x8000 lighting? or shadow
    // 0x2000 = use alpha in diffuse colour
    if (pVerts[0].z <= 0.0f)
    {
        return;
    }

    
    if (Clipped(pVerts, 4))
    {
        return;
    }

    if (quadFlags & 0x10000) // whatever this flag is turns point filtering on
    {
        quadFlags |= 0x20000;
    }

    SetRenderStates(quadFlags);

    if (quadFlags & 0x20000)
    {
        if (!bPointFilteringOn)
        {
            bPointFilteringOn = 1;
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DTFG_POINT);
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DTFG_POINT);
        }
    }
    else
    {
        if (bPointFilteringOn)
        {
            bPointFilteringOn = 0;
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DTFG_LINEAR);
            (*gD3dPtr)->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DTFG_LINEAR);
        }
    } 

    pTexture->Flags &= 0xBF;
    pTexture->Flags |= 0x40;

    if (pTexture->NextCache)
    {
        
        if (pTexture->Flags & 0x80)
        {
            if (pTexture->Flags & 0x40 && quadFlags & 0x300)
            {
                TextureCache(pTexture);
                CacheFlushBatchRelated(pTexture, quadFlags);
                pTexture->Flags &= 0xBF;
            }
            else if (pTexture->Flags & 0x40 || quadFlags & 0x300)
            {
                // Skip
            }
            else
            {
                TextureCache(pTexture);
                CacheFlushBatchRelated(pTexture, quadFlags);

                pTexture->Flags |= 0x40;
            }
        }
    }
    else
    {
        CacheFlushBatchRelated(pTexture, quadFlags);
        auto v9 = pTexture->Flags;
        if (quadFlags & 0x300)
        {
            pTexture->Flags &= 0xBF;

        }
        else
        {
            pTexture->Flags |= 0x40;
        }
    }

    const auto pTextureCache = pTexture->NextCache;
    const auto pHardwareTexture = pTextureCache->TextureId;
    if ((*gActiveTextureId) != pHardwareTexture)
    {
        D3dTextureSetCurrent(pTextureCache->TextureId);
        (*gActiveTextureId) = pHardwareTexture;
        ++gGlobals.mNumTextureSwaps;
        const auto v15 = pTextureCache->pNextCache;
        pTextureCache->UsedFrameNum = FrameNumber;
        if (v15)
        {
            auto pCache = pTextureCache->pCache;

            if (pCache)
            {
                pCache->pNextCache = v15;
            }
            else
            {
                gGlobals.CacheArray [pTextureCache->CacheIdx] = v15;
            }

            pTextureCache->pNextCache->pCache = pTextureCache->pCache;
            const auto cacheIdx = pTextureCache->CacheIdx;
            pTextureCache->pNextCache = 0;
            pTextureCache->pCache = gGlobals.CacheArray [cacheIdx];
            gGlobals.CacheArray [cacheIdx]->pNextCache = pTextureCache;
            gGlobals.CacheArray [pTextureCache->CacheIdx] = pTextureCache;
        }
    }

    const float uvScale = pTexture->NextCache->field_C;
    if (quadFlags & 0x10000)
    {
        const float textureW = (float)pTexture->Width;
        const float textureH = (float)pTexture->Height;

        if (gGpuSpecificHack)
        {
            //v19 = pVerts->mVerts[0].x;
            //floor(v19);
            //pVerts->mVerts[0].x = v19;
            //v20 = pVerts->mVerts[0].y;
            //floor(v20);
            //pVerts->mVerts[0].y = v20;
        }


        const float flt_E10830 = 0.001f;
        const auto v21 = pVerts[0].x + textureW;
        const auto v23 = pVerts[0].x + textureW - flt_E10830;
        const auto v24 = pVerts[0].y + textureH;


        pVerts[1].z = pVerts[0].z;
        pVerts[2].z = pVerts[0].z;
        pVerts[3].z = pVerts[0].z;

        pVerts[1].x = v23;
        pVerts[1].y = pVerts[0].y;

        pVerts[2].x = v21 - flt_E10830;
        pVerts[2].y = v24 - flt_E10830;

        pVerts[3].x = pVerts[0].x;
        pVerts[3].y = v24 - flt_E10830;

        pVerts[0].u = 0;
        pVerts[0].v = 0;

        float flt_E1082C = 0.0f; // 0.25 or 0, TODO: Set me in init

        pVerts[1].u = textureW - flt_E1082C;
        pVerts[1].v = 0;

        pVerts[2].u = textureW - flt_E1082C;
        pVerts[2].v = textureH - flt_E1082C;

        pVerts[3].u = 0;
        pVerts[3].v = textureH - flt_E1082C;
    }

    pVerts[0].w = pVerts[0].z;
    pVerts[1].w = pVerts[1].z;
    pVerts[2].w = pVerts[2].z;
    pVerts[3].w = pVerts[3].z;

    pVerts[0].u = uvScale * pVerts[0].u;
    pVerts[0].v = uvScale * pVerts[0].v;

    pVerts[1].u = uvScale * pVerts[1].u;
    pVerts[1].v = uvScale * pVerts[1].v;

    pVerts[2].u = uvScale * pVerts[2].u;
    pVerts[2].v = uvScale * pVerts[2].v;

    pVerts[3].u = uvScale * pVerts[3].u;
    pVerts[3].v = uvScale * pVerts[3].v;

    if (!(quadFlags & 0x2000))
    {
        // Force RGBA to be 255, 255, 255, A
        auto finalDiffuse = (unsigned __int8)baseColour | (((unsigned __int8)baseColour | ((baseColour | 0xFFFFFF00) << 8)) << 8);
        int f = finalDiffuse;
        // f++;
         //finalDiffuse = f;

        pVerts[0].diff = finalDiffuse;
        pVerts[1].diff = finalDiffuse;
        pVerts[2].diff = finalDiffuse;
        pVerts[3].diff = finalDiffuse;
    }

    pVerts[0].spec = 255;
    pVerts[1].spec = 255;
    pVerts[2].spec = 255;
    pVerts[3].spec = 255;

    if (quadFlags & 0x8000)
    {
        if (gfAmbient != 255.0f)
        {
            LightVerts_new(4, pVerts, 0, baseColour);
        }
    }


    Vert myCopy[4];
    for (int i = 0; i < 4; i++)
    {
        myCopy[i] = pVerts[i];
    }

    (*gD3dPtr)->pIDirect3DDevice3->DrawPrimitive(D3DPT_TRIANGLEFAN, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1, pVerts, 4, D3DDP_DONOTUPDATEEXTENTS);
    gGlobals.mNumPolysDrawn += 2;
}

void CC gbh_DrawQuadClipped(int a1, int a2, int a3, int a4, int a5)
{
    __debugbreak();
}

// TODO: Refactor/clean up this func
// Same as gbh_DrawTile
s32 CC gbh_DrawTilePart(unsigned int flags, Texture* pTexture, Vert* pData, int diffuseColour)
{
    if (gProxyOnly)
    {
         return gFuncs.pgbh_DrawTilePart(flags, pTexture, pData, diffuseColour);
    }

    auto oldFlags = flags;

    if (!(flags & 0x4000))
    {
        pData[0].u = 0.5f;
        pData[0].v = 0.5f;
        pData[1].u = 63.499901f;
        pData[1].v = 0.5f;
        pData[2].u = 63.499901f;
        pData[2].v = 63.499901f;
        pData[3].u = 0.5f;
        pData[3].v = 63.499901f;
    }

    struct uv { float u; float v; };
    uv uvs[4];
    for (int i = 0; i < 4; i++)
    {
        uvs[i].u = pData[i].u;
        uvs[i].v = pData[i].v;
    }


    // Rotate around the texture
    bool updated = false;
    switch (flags & 0x60)
    {
    case 0x20:
        pData[0].u = uvs[3].u;
        pData[0].v = uvs[3].v;

        pData[1].u = uvs[0].u;
        pData[1].v = uvs[0].v;

        pData[2].u = uvs[1].u;
        pData[2].v = uvs[1].v;

        pData[3].u = uvs[2].u;
        pData[3].v = uvs[2].v;
        updated = true;
        break;

    case 0x40:
        oldFlags = flags ^ 0x18;
        break;

    case 0x60:
        pData[0].u = uvs[1].u;
        pData[0].v = uvs[1].v;

        pData[1].u = uvs[2].u;
        pData[1].v = uvs[2].v;

        pData[2].u = uvs[3].u;
        pData[2].v = uvs[3].v;

        pData[3].u = uvs[0].u;
        pData[3].v = uvs[0].v;
        updated = true;
        break;
    }

    if (updated)
    {
        for (int i = 0; i < 4; i++)
        {
            uvs[i].u = pData[i].u;
            uvs[i].v = pData[i].v;
        }
    }

    // Flip up/down?
    if (oldFlags & 8)
    {
        pData[0].u = uvs[1].u;
        pData[0].v = uvs[1].v;

        pData[1].u = uvs[0].u;
        pData[1].v = uvs[0].v;

        pData[2].u = uvs[3].u;
        pData[2].v = uvs[3].v;

        pData[3].u = uvs[2].u;
        pData[3].v = uvs[2].v;
        if (oldFlags & 0x10)
        {
            for (int i = 0; i < 4; i++)
            {
                uvs[i].u = pData[i].u;
                uvs[i].v = pData[i].v;
            }
        }
    }

    // Flip left/right?
    if (oldFlags & 0x10)
    {
        pData[0].u = uvs[3].u;
        pData[0].v = uvs[3].v;

        pData[1].u = uvs[2].u;
        pData[1].v = uvs[2].v;

        pData[2].u = uvs[1].u;
        pData[2].v = uvs[1].v;

        pData[3].u = uvs[0].u;
        pData[3].v = uvs[0].v;
    }

    gbh_DrawQuad(oldFlags, pTexture, pData, diffuseColour);
    return 0;
}

void CC gbh_EndLevel()
{
    __debugbreak();
}

static BOOL __stdcall DeviceEndScene_E01C10(D3dStruct* pD3d)
{
    return pD3d->pIDirect3DDevice3->EndScene() != 0;
}

double CC gbh_EndScene()
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_EndScene();
    }

    DeviceEndScene_E01C10((*gD3dPtr));
    if (gbSurfaceIsFreed == 1)
    {
        (*gVideoDriver->initDLL->pVid_GetSurface)(gVideoDriver);
    }
    double result = qword_2B60848 / k1_2B638A0;
    gGlobals.mSceneTime = qword_2B60848 / k1_2B638A0;// always 0 / 1 ?
    return result;
}

int CC gbh_FreeImageTable()
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_FreeImageTable();
    }

    if (gImageTableCount <= 0)
    {
        free(gImageTable);
    }
    else
    {
        for (int idx = 0; idx < gImageTableCount; idx++)
        {
            if (gImageTable[idx].Loaded)
            {
                gImageTable[idx].pSurface->Release();
                gImageTable[idx].Loaded = FALSE;
            }
        }
    }
    free(gImageTable);
    gImageTable = 0;
    return 0;
}

void CC gbh_FreePalette(int palId)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_FreePalette(palId);
    }

    free(pals[palId].mPData);
    pals[palId].mPData = 0;
}

void CC gbh_FreeTexture(Texture* pTexture)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_FreeTexture(pTexture);
    }

    TextureCache(pTexture);
    free(pTexture);
}

u32* CC gbh_GetGlobals()
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_GetGlobals();
    }

    return (u32*)&gGlobals;
}

// Only called with do_mike / profiling debugging opt enabled
int CC gbh_GetUsedCache(int cacheIdx)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_GetUsedCache(cacheIdx);
    }

    int usedCacheCount = 0;
    Cache* pCache = gGlobals.CacheArray [cacheIdx];
    while (pCache)
    {
        if (pCache->UsedFrameNum == FrameNumber)
        {
            ++usedCacheCount;
        }
        pCache = pCache->pNextCache;
    }
    return usedCacheCount;
}

static HRESULT WINAPI EnumD3DDevicesCallBack(
    GUID FAR* lpGuid, 
    LPSTR lpDeviceDescription, 
    LPSTR lpDeviceName, 
    LPD3DDEVICEDESC pDeviceDesc1, 
    LPD3DDEVICEDESC pDeviceDesc2, 
    LPVOID pContext)
{
    LPD3DDEVICEDESC pDeviceDesc = pDeviceDesc1;
    auto dcmColorModel = pDeviceDesc->dcmColorModel;
    if (dcmColorModel == 0)
    {
        pDeviceDesc = pDeviceDesc2;
    }

    D3dStruct* pCtx = (D3dStruct*)pContext;
    if (!(pCtx->pitchQ   & pDeviceDesc->dwDeviceRenderBitDepth))
    {
        return 1;
    }

    const auto shadeCaps = pDeviceDesc->dpcTriCaps.dwShadeCaps;
    if (pDeviceDesc->dcmColorModel == 1 || shadeCaps & 8)
    {
        if (!(shadeCaps & 8))
        {
            if (!(shadeCaps & 4))
            {
                return 1;
            }

        }

        int deviceDescrptionIndex = lpDeviceDescription ? strlen(lpDeviceDescription) : 0;
        int deviceNameIndex = lpDeviceName ? strlen(lpDeviceName) : 0;

        D3DDevice* pDevice = (D3DDevice *)malloc(deviceNameIndex + deviceDescrptionIndex + 566);
        if (!pDevice)
        {
            return 0;
        }

        ++pCtx->NumEnums;

        pDevice->NumTextureEnums  = 0;
        pDevice->Flags = 0;
        pDevice->NextD3DDevice = 0;
        pDevice->FirstTextureFormat  = 0;
        pDevice->pFirstTextureFormat  = 0;
        pDevice->pHead  = 0;
        pDevice->IDirect3dTexture2List  = 0;
        pDevice->ID  = pCtx->DeviceIDGen++;

        auto pFirstDevice = pCtx->FirstDevice;
        if (pFirstDevice)
        {
            pFirstDevice->NextD3DDevice = pDevice;
            pCtx->FirstDevice = pDevice;
        }
        else
        {
            pCtx->FirstDevice = pDevice;
            pCtx->NextDevice  = pDevice;
        }

        
        pDevice->DeviceGuid = *lpGuid;
       
       // pDevice->field_124.wMaxTextureBlendStages = pDeviceDesc->wMaxTextureBlendStages; //  TODO: (char *)v13 + 544; ???

        pDevice->DeviceName   = (char *)&pDevice->BackingBuffer ;

        char* v20 = (char *)&pDevice->BackingBuffer + deviceNameIndex + 1;
        pDevice->DeviceDescription1  = v20;

        strcpy(v20, lpDeviceDescription);
        strcpy(pDevice->DeviceName , lpDeviceName);

        memcpy(&pDevice->DeviceDescription, pDeviceDesc1, sizeof(D3DDEVICEDESC));
        
        // can't see how this would work 
        //memcpy(&pDevice->field_120_context, pContext, 0xFCu); // TODO: Actually copies to offset 0x120 the field before ??
        memcpy(&pDevice->field_124, pDeviceDesc2, sizeof(D3DDEVICEDESC));


        if (dcmColorModel != 0)
        {
            pDevice->Flags |= 1u;
        }

        auto v21 = pDeviceDesc->dwDeviceZBufferBitDepth;

        if (BYTE1(v21) & 4)
        {
            pDevice->Flags |= 2;
        }
        else if (BYTE1(v21) & 2)
        {
            pDevice->Flags |= 4;
        }
        else
        {
            if (!(BYTE1(v21) & 1))
            {
                
            }
            else
            {
                pDevice->Flags |= 8;
            }
        }

        if (pDeviceDesc->dpcTriCaps.dwDestBlendCaps & 2 && pDeviceDesc->dpcTriCaps.dwSrcBlendCaps & 2)
        {
            pDevice->Flags |= 0x40u;
        }

        if (pDeviceDesc->dpcTriCaps.dwAlphaCmpCaps & 0x10)
        {
            pDevice->Flags |= 0x10u;
        }

        if (pDeviceDesc->dpcTriCaps.dwTextureBlendCaps & 4)
        {
            pDevice->Flags |= 0x20u;
        }

        if (BYTE1(pDeviceDesc->dwDevCaps) & 0x10)
        {
            pDevice->Flags |= 0x80;
        }

        if (pDeviceDesc->dcmColorModel & 2)
        {
            pDevice->Flags |= 1;
        }

        if (pDeviceDesc->dpcTriCaps.dwTextureFilterCaps & 0x3C)
        {
            pDevice->Flags |= 2;
        }
        return 1;
    }
    
    return 1;
}

struct TextureFormat
{
    DWORD EnumIndex;
    DWORD dwRGBBitCount;
    DWORD AlphaBitCount;
    DWORD AlphaBitIndex;
    DWORD RedBitCount;
    DWORD RedBitIndex;
    DWORD GreenBitIndex;
    DWORD GreenBitCount;
    DWORD BlueBitCount;
    DWORD BlueBitIndex;
    DWORD Flags;
    struct TextureFormat* NextTextureFormat;
    DWORD field_30;
    DWORD field_34;
    DWORD field_38;
    DWORD field_3C;
    DWORD field_40;
    DWORD field_44;
    DWORD field_48;
    DWORD field_4C;
    DWORD field_50;
    DWORD field_54;
    DWORD field_58;
    DWORD field_5C;
    DWORD field_60;
    DWORD field_64;
    DWORD field_68;
    DWORD field_6C;
    DWORD field_70;
    DWORD field_74;
    DWORD field_78;
    DWORD field_7C;
    DWORD field_80;
    DWORD field_84;
    DWORD field_88;
    DWORD field_8C;
    DWORD field_90;
    DWORD field_94;
    DWORD field_98;
    DDPIXELFORMAT DDTextureFormat;
};
static_assert(sizeof(TextureFormat) == 0xBC, "Wrong size TextureFormat");

struct HardwareTexture
{
    DWORD TextureId;
    DWORD Flags;
    DWORD BitCount;
    DWORD BlueBitIndex;
    DWORD BlueUnknown;
    DWORD BlueBitCount;
    DWORD GreenBitIndex;
    DWORD GreenUnknown;
    DWORD GreenBitCount;
    DWORD RedBitIndex;
    DWORD RedUnknown;
    DWORD RedBitCount;
    DWORD AlphaBitIndex;
    DWORD AlphaUnknown;
    DWORD AlphaBitCount;
    DWORD LockedPixelData;
    DWORD pitch;
    WORD Width;
    WORD Height;
    struct D3dStruct* D3dStr;
    struct HardwareTexture* pNextHardwareTexture;
    struct HardwareTexture* pther;
    IDirect3DTexture2* IDirect3dTexture2;
    IDirectDrawSurface4* OtherSurface;
    IDirectDrawSurface4* pSurfaceForTexture;
//    DWORD field_60; 
};
static_assert(sizeof(HardwareTexture) == 0x60, "Wrong size HardwareTexture");

static void __stdcall ConvertPixelFormat(TextureFormat* pTextureFormat, const DDPIXELFORMAT* pDDFormat);
decltype(&ConvertPixelFormat) pConvertPixelFormat = (decltype(&ConvertPixelFormat))0x4A10;

static unsigned int countSetBits(unsigned int value)
{
    int i = 0;
    for (i = 0; (value & 1); ++i)
    {
        value >>= 1;
        if (i >= 32)
        {
            return i;
        }
    }
    return i;
}

static unsigned int firstUnSetBitIndex(DWORD& value)
{
    int i = 0;
    for (i = 0; !(value & 1); ++i)
    {
        value >>= 1;
        if (i >= 32)
        {
            return i;
        }
    }
    return i;
}

// TODO: Test VS real
static void __stdcall ConvertPixelFormat(TextureFormat* pTextureFormat, const DDPIXELFORMAT* pDDFormat)
{
    //TextureFormat old = *pTextureFormat;
    //pConvertPixelFormat_2B55A10(&old, pDDFormat);

    pTextureFormat->dwRGBBitCount  = pDDFormat->dwRGBBitCount;

    DWORD r = pDDFormat->dwRBitMask;
    unsigned int rBitIndex = 0;
    if (r & 1)
    {
        rBitIndex = 1;
    }
    else
    {
        rBitIndex = firstUnSetBitIndex(r);
    }

    const bool bHaveNoRedBits = rBitIndex == 32;

    if (bHaveNoRedBits)
    {
        pTextureFormat->RedBitIndex  = 0;
        pTextureFormat->RedBitCount  = 0;
        pTextureFormat->BlueBitIndex  = 0;
        pTextureFormat->BlueBitCount  = 0;
        pTextureFormat->GreenBitCount  = 0;
        pTextureFormat->GreenBitIndex  = 0;
        return;
    }
    pTextureFormat->RedBitIndex = rBitIndex;

    // TODO: This actually counted set bits up to the first non set bit, and the real function counted unset to set bits and returned the resulting value
    pTextureFormat->RedBitCount = countSetBits(r);

    DWORD g = pDDFormat->dwGBitMask;
    pTextureFormat->GreenBitCount = firstUnSetBitIndex(g);
    pTextureFormat->GreenBitIndex = countSetBits(g);

    DWORD b = pDDFormat->dwBBitMask;
    pTextureFormat->BlueBitIndex = firstUnSetBitIndex(b);
    pTextureFormat->BlueBitCount = countSetBits(b);

    pTextureFormat->AlphaBitIndex  = 0;
    pTextureFormat->AlphaBitCount = 0;

    if (pDDFormat->dwFlags & DDPF_ALPHAPIXELS)
    {
        auto rgbMask = (pDDFormat->dwBBitMask | pDDFormat->dwRBitMask | pDDFormat->dwGBitMask);

        // Get the alpha bits ??
        switch (pDDFormat->dwRGBBitCount)
        {
        case 8:
            rgbMask ^= 0xFFu;
            break;
        case 16:
            rgbMask ^= 0xFFFFu;
            break;
        case 24:
            rgbMask ^= 0xFFFFFFu;
            break;
        case 32:
            rgbMask = ~rgbMask;
            break;
        }

        if (rgbMask)
        {
            auto idx = firstUnSetBitIndex(rgbMask);
            pTextureFormat->AlphaBitIndex = idx;
            pTextureFormat->AlphaBitCount = countSetBits(rgbMask);

            if (idx >= pTextureFormat->dwRGBBitCount)
            {
                pTextureFormat->AlphaBitIndex = 0;
                pTextureFormat->AlphaBitCount = 0;
            }
            OutputDebugStringA("ALPHA - ");
        }
    }

    char buffer[120] = {};
    wsprintfA(buffer,
        "AlphaIn = %0x, Size<%d>, Shift<%d>",
        pDDFormat->dwRGBAlphaBitMask,
        pTextureFormat->AlphaBitCount,
        pTextureFormat->AlphaBitIndex);
    OutputDebugStringA(buffer);

    /*
    assert(old.dwRGBBitCount == pTextureFormat->dwRGBBitCount);
    assert(old.AlphaBitCount == pTextureFormat->AlphaBitCount);
    assert(old.AlphaBitIndex == pTextureFormat->AlphaBitIndex);
    assert(old.RedBitCount == pTextureFormat->RedBitCount);
    assert(old.RedBitIndex == pTextureFormat->RedBitIndex);
    assert(old.field_18_gBitCount == pTextureFormat->field_18_gBitCount);
    assert(old.field_1C_gBitIndex == pTextureFormat->field_1C_gBitIndex);
    assert(old.BlueBitCount == pTextureFormat->BlueBitCount);
    assert(old.BlueBitIndex == pTextureFormat->BlueBitIndex);
    assert(old.Flags == pTextureFormat->Flags);
    */
}

static TextureFormat* FindTextureFormatHelper(D3dStruct* pD3d, DWORD sizeToFind, DWORD flagsToMatch, bool flagsAndSizeValid, bool storeInFirstField)
{
    D3DDevice* device = pD3d->ActiveDevice ;
    for (TextureFormat* result = device->FirstTextureFormat; result; result = result->NextTextureFormat )
    {
        // If flagsAndSizeValid is false then look at this format, otherwise only look at it if the size and flags match the search criteria
        if (!flagsAndSizeValid || (flagsAndSizeValid && (result->Flags & flagsToMatch) && result->AlphaBitCount == sizeToFind))
        {
            if (result->dwRGBBitCount == 16 || result->dwRGBBitCount == 15)
            {
                if (storeInFirstField)
                {
                    pD3d->TextureFormat1  = result;
                }
                else
                {
                    pD3d->TextureFormat = result;
                }
                return result;
            }
        }
    }
    return nullptr;
}

static TextureFormat *__stdcall FindTextureFormat(D3dStruct* pD3d, unsigned int flags);
decltype(&FindTextureFormat) pFindTextureFormat = 0x0;


static TextureFormat *__stdcall FindTextureFormat(D3dStruct* pD3d, unsigned int flags)
{
    TextureFormat* result = nullptr;
    D3DDevice* device = pD3d->ActiveDevice;

    // 0x80000000 = reverse flag, or smallest/largest first ?
    // 0x40000000 = skip 4 sized, only valid when 0x80000000 is enabled

    if (flags & 0x80000000)
    {
        if (!(flags & 0x40000000))
        {
            result = FindTextureFormatHelper(pD3d, 4, 0x8000, true, true);
            if (result)
            {
                return result;
            }
        }

        result = FindTextureFormatHelper(pD3d, 1, 0x8000, true, true);
        if (result)
        {
            return result;
        }


        return FindTextureFormatHelper(pD3d, 0, 0, false, true);
    }
    

    result = FindTextureFormatHelper(pD3d, 0, 0, false, false);
    if (result)
    {
        return result;
    }

    result = FindTextureFormatHelper(pD3d, 1, 0x8000, true, false);
    if (result)
    {
        return result;
    }

    return FindTextureFormatHelper(pD3d, 4, 0x8000, true, false);
}

static HRESULT CALLBACK EnumTextureFormatsCallBack(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);
decltype(&EnumTextureFormatsCallBack) pEnumTextureFormatsCallBack = 0x0;

static HRESULT CALLBACK EnumTextureFormatsCallBack(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext)
{
    D3DDevice* pDevice = (D3DDevice*)lpContext;
    const auto flags = lpDDPixFmt->dwFlags;
    if (!(flags & 0xC0000) && !(flags & 0x20002) && !(flags & 0x204) && flags & 0x40)
    {
        auto pTextureFormat = (TextureFormat *)malloc(sizeof(TextureFormat));
        if (!pTextureFormat)
        {
            return 0;
        }

        memset(pTextureFormat, 0, sizeof(TextureFormat));

        ++pDevice->NumTextureEnums;
        pTextureFormat->Flags  = 0;
        pTextureFormat->NextTextureFormat = 0;
        pTextureFormat->EnumIndex = pDevice->NumTextureEnums;
        auto pFirst = pDevice->pFirstTextureFormat;
        if (pFirst)
        {
            pFirst->NextTextureFormat = pTextureFormat;
            pDevice->pFirstTextureFormat = pTextureFormat;
        }
        else
        {
            pDevice->pFirstTextureFormat = pTextureFormat;
            pDevice->FirstTextureFormat = pTextureFormat;
        }
        
        memcpy(&pTextureFormat->DDTextureFormat, lpDDPixFmt, sizeof(DDPIXELFORMAT));

        if (lpDDPixFmt->dwFlags & 1)
        {
            pTextureFormat->Flags |= 0x8000;
        }

        OutputDebugStringA("ENUM TEXTURE FORMAT - ");
        ConvertPixelFormat(pTextureFormat, lpDDPixFmt);
    }
    return 1;
}

static int CleanUpHelper(D3dStruct* pRenderer)
{
    // TODO: Also attempts to free memory that can't be seen being assigned to anywhere

    if (pRenderer->IUnknown )
    {
        pRenderer->VideoDriver->Surface->DeleteAttachedSurface(0, pRenderer->IUnknown);
        pRenderer->IUnknown->Release();
    }

    if (pRenderer->pIDirect3DViewPort3)
    {
        pRenderer->pIDirect3DViewPort3->Release();
    }
    return 1;
}

static HardwareTexture *__stdcall TextureAlloc(D3dStruct* pD3d, int width, int height, int flags)
{
    TextureFormat* pTextureFormat = FindTextureFormat(pD3d, flags);
    if (pTextureFormat)
    {
        HardwareTexture* pMem = (HardwareTexture *)malloc(sizeof(HardwareTexture));
        if (pMem)
        {
            memset(pMem, 0, sizeof(HardwareTexture));
            pMem->D3dStr  = pD3d;

            D3DDEVICEDESC hardwareCaps = {};
            D3DDEVICEDESC softwareCaps = {};
            hardwareCaps.dwSize = sizeof(D3DDEVICEDESC);
            softwareCaps.dwSize = sizeof(D3DDEVICEDESC);
            pD3d->pIDirect3DDevice3->GetCaps(&hardwareCaps, &softwareCaps);

            DDSURFACEDESC2 surfaceDesc = {};
            memcpy(&surfaceDesc.ddpfPixelFormat, &pTextureFormat->DDTextureFormat, sizeof(DDPIXELFORMAT));
            surfaceDesc.dwWidth = width;
            surfaceDesc.dwFlags |= 0x1007u;
            surfaceDesc.dwSize = sizeof(DDSURFACEDESC2);// 124;
            surfaceDesc.dwHeight = height;

            // v21 == ?
            if (/*v21 &&*/ flags & 2)
            {
                surfaceDesc.ddsCaps.dwCaps = 0x4005000;
            }
            else
            {
                surfaceDesc.ddsCaps.dwCaps = 6144;
                pMem->Flags  |= 1;
            }


            surfaceDesc.ddsCaps.dwCaps2 = 4;
            surfaceDesc.ddsCaps.dwCaps |= 0x1000;

            if (BYTE1(pD3d->ActiveDevice->Flags) & 2)
            {
                surfaceDesc.ddsCaps.dwCaps |= 0x401008;
                surfaceDesc.dwMipMapCount = 1;
                surfaceDesc.dwFlags |= 0x20000u;
            }

            if (FAILED(pD3d->VideoDriver->IDDraw4->CreateSurface(&surfaceDesc, &pMem->pSurfaceForTexture , 0)))
            {
                free(pMem);
                return 0;
            }

            pMem->pSurfaceForTexture->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pMem->IDirect3dTexture2);
            if (!(flags & 2))
            {
                pMem->Flags |= 4;
            }

            pMem->Width = width;
            pMem->Height = height;
            
            pMem->BitCount = pTextureFormat->dwRGBBitCount;

            /*
             nothing before this even though its usually 0x76 ?? Seems to be random value which you'd expect!
            .text:00005DBA mov byte ptr [esp+18h], 1
            .text:00005DBF mov byte ptr [esp+19h], 3
            .text:00005DC4 mov byte ptr [esp+1Ah], 7
            .text:00005DC9 mov byte ptr [esp+1Bh], 15
            .text:00005DCE mov byte ptr [esp+1Ch], 31
            .text:00005DD3 mov byte ptr [esp+1Dh], 63
            .text:00005DD8 mov byte ptr [esp+1Eh], 127
            */

            const BYTE unknown[] = { 0 /*not inited in real func??*/, 1,3,7,15,31,64,127 };

            // Blue
            pMem->BlueBitCount= unknown[pTextureFormat->BlueBitCount];
            pMem->BlueBitIndex  = pTextureFormat->BlueBitIndex;
            pMem->BlueUnknown  = 8 - pTextureFormat->BlueBitCount;

            // Green
            pMem->GreenBitCount  = unknown[pTextureFormat->GreenBitCount]; 
            pMem->GreenBitIndex = pTextureFormat->GreenBitIndex;
            pMem->GreenUnknown = 16 - pTextureFormat->GreenBitCount;

            // Red
            pMem->RedBitCount  = unknown[pTextureFormat->RedBitCount]; 
            pMem->RedBitIndex  = pTextureFormat->RedBitIndex;
            pMem->RedUnknown  = 24 - pTextureFormat->RedBitCount;

            // Alpha
            pMem->AlphaBitCount  = unknown[pTextureFormat->AlphaBitCount];
            pMem->AlphaBitIndex  = pTextureFormat->AlphaBitIndex;
            pMem->AlphaUnknown = 32 - pTextureFormat->AlphaBitCount;


            pMem->Flags |= pTextureFormat->Flags & 0x8000;

            auto pDevice = pD3d->ActiveDevice;
            if (pDevice->pHead)
            {
                pDevice->IDirect3dTexture2List->pNextHardwareTexture  = pMem;
                pD3d->ActiveDevice->IDirect3dTexture2List = pMem;
            }
            else
            {
                pDevice->pHead = pMem;
                pD3d->ActiveDevice->IDirect3dTexture2List = pMem;
            }
            return pMem;
        }
    }
    return 0;
}

static signed int __stdcall D3dTextureSetCurrent(HardwareTexture *pHardwareTexture)
{
    HardwareTexture* pOther = pHardwareTexture->pther;
    if (pHardwareTexture->Flags & 1
        && pHardwareTexture->D3dStr->ActiveDevice->Flags & 1
        && pOther == 0) // TODO: Check last conditional
    {
        return 1;
    }
    else
    {
        pHardwareTexture = pOther;
        if (pHardwareTexture->pSurfaceForTexture->IsLost() == DDERR_SURFACELOST)
        {
            pHardwareTexture->pSurfaceForTexture->Restore();
            pHardwareTexture->OtherSurface->PageLock(0);
            const auto ret = pHardwareTexture->IDirect3dTexture2->Load(pHardwareTexture->pther->IDirect3dTexture2) == 1;
            if (ret)
            {
                pHardwareTexture->OtherSurface->Unlock(0);
            }
            else
            {
                pHardwareTexture->OtherSurface->PageUnlock(0);
            }
        }

        pHardwareTexture->D3dStr->pIDirect3DDevice3->SetTexture(0,  pHardwareTexture->IDirect3dTexture2);
        return 0;
    }
}

static int __stdcall D3dTextureCopy(HardwareTexture* pFirst, HardwareTexture* pSecond)
{
    pFirst->OtherSurface = pSecond->pSurfaceForTexture;
    pSecond->pther = pFirst;
    pFirst->pther = pSecond;
    pSecond->Flags |= 2;
    pFirst->Flags |= 2;
    return 0;
}

static int __stdcall ClearTexture(D3dStruct* pCtx)
{
    pCtx->pIDirect3DDevice3->SetTexture(0, 0);
    return 0;
}

static int __stdcall FreeD3dDThings(D3dStruct* pD3d)
{
    if (pD3d->CurrentID )
    {
        // Free texture formats
        TextureFormat* pCurrentTextureFormat = pD3d->ActiveDevice->FirstTextureFormat;
        if (pCurrentTextureFormat)
        {
            struct TextureFormat* pTextureFormat = nullptr;
            do
            {
                pTextureFormat = pCurrentTextureFormat->NextTextureFormat;
                free(pCurrentTextureFormat);
                pCurrentTextureFormat = pTextureFormat;
            } while (pTextureFormat);
        }

        pD3d->ActiveDevice->FirstTextureFormat = 0;
        pD3d->ActiveDevice->pFirstTextureFormat = 0;

        
        // Free hardware textures
        HardwareTexture* pCurrentHardwareTexture = pD3d->ActiveDevice->pHead;
        if (pCurrentHardwareTexture)
        {
            HardwareTexture* pHardwareTexture = nullptr;
            do
            {
                pCurrentHardwareTexture->IDirect3dTexture2->Release();
                pCurrentHardwareTexture->pSurfaceForTexture->Release();
                pHardwareTexture = pCurrentHardwareTexture->pNextHardwareTexture;
                free(pCurrentHardwareTexture);
                pCurrentHardwareTexture = pHardwareTexture;
            } while (pHardwareTexture);
        }

        pD3d->ActiveDevice->pHead = 0;
        pD3d->ActiveDevice->IDirect3dTexture2List = 0;

        if (pD3d->pIDirect3DViewPort3)
        {
            pD3d->pIDirect3DDevice3->DeleteViewport(pD3d->pIDirect3DViewPort3);
            pD3d->pIDirect3DViewPort3->Release();
            pD3d->pIDirect3DViewPort3 = 0;
        }
        if (pD3d->pIDirect3DDevice3)
        {
            pD3d->pIDirect3DDevice3->Release();
            pD3d->pIDirect3DDevice3 = 0;
        }

        pD3d->CurrentID = 0;
        pD3d->ActiveDevice = 0;
    }
    return 0;
}

signed int __stdcall CreateD3DDevice(D3dStruct* pRenderer);
decltype(&CreateD3DDevice) pCreateD3DDevice = 0x0;

signed int __stdcall CreateD3DDevice(D3dStruct* pRenderer)
{
    hack = pRenderer;
  
    //return pCreateD3DDevice_E01840(pRenderer);


    if (FAILED(pRenderer->pIDirect3D3->CreateDevice(
        pRenderer->ActiveDevice->DeviceGuid ,
        pRenderer->VideoDriver->Surface,
        &pRenderer->pIDirect3DDevice3,
        nullptr)))
    {
        return CleanUpHelper(pRenderer);
    }

    if (FAILED(pRenderer->pIDirect3D3->CreateViewport(&pRenderer->pIDirect3DViewPort3, nullptr)))
    {
        return CleanUpHelper(pRenderer);
    }

    if (FAILED(pRenderer->pIDirect3DDevice3->AddViewport(pRenderer->pIDirect3DViewPort3)))
    {
        return CleanUpHelper(pRenderer);
    }

    if (FAILED(pRenderer->pIDirect3DDevice3->SetCurrentViewport(pRenderer->pIDirect3DViewPort3)))
    {
        return CleanUpHelper(pRenderer);
    }

    memset(&pRenderer->D3DVIEWPORT2, 0, sizeof(pRenderer->D3DVIEWPORT2));
    pRenderer->D3DVIEWPORT2.dwSize = sizeof(pRenderer->D3DVIEWPORT2);
    pRenderer->D3DVIEWPORT2.dwX = 0;
    pRenderer->D3DVIEWPORT2.dwY = 0;
    pRenderer->D3DVIEWPORT2.dwWidth = pRenderer->VideoDriver->RectRight;
    pRenderer->D3DVIEWPORT2.dwHeight = pRenderer->VideoDriver->RectBottom;
    pRenderer->D3DVIEWPORT2.dvClipWidth = pRenderer->VideoDriver->RectRight;
    pRenderer->D3DVIEWPORT2.dvClipX = pRenderer->VideoDriver->RectRight;
    pRenderer->D3DVIEWPORT2.dvClipY = pRenderer->VideoDriver->RectRight;
    pRenderer->D3DVIEWPORT2.dvMinZ = pRenderer->VideoDriver->RectRight;
    pRenderer->D3DVIEWPORT2.dvClipHeight = pRenderer->VideoDriver->RectBottom;
    pRenderer->D3DVIEWPORT2.dvMaxZ = 500.0f;

    if (FAILED(pRenderer->pIDirect3DViewPort3->SetViewport2(&pRenderer->D3DVIEWPORT2)))
    {
        return CleanUpHelper(pRenderer);
    }

    return pRenderer->pIDirect3DDevice3->EnumTextureFormats(EnumTextureFormatsCallBack, pRenderer->ActiveDevice) != 0;
}

D3dStruct* D3DCreate(Video* pVideoDriver)
{
    D3dStruct* pd3d = reinterpret_cast<D3dStruct*>(malloc(sizeof(D3dStruct)));
    if (pd3d)
    {
        memset(pd3d, 0, sizeof(D3dStruct));

        if (pVideoDriver->DirectDraw7->QueryInterface(IID_IDirect3D3,
            (LPVOID*)&pd3d->pIDirect3D3))
        {
            free(pd3d);
            return 0;
        }

        pd3d->VideoDriver = pVideoDriver;
        pd3d->DeviceIDGen = 1;

        DDSURFACEDESC2 surfaceDesc = {};
        surfaceDesc.dwSize = sizeof(DDSURFACEDESC2);
        
        DWORD pitch = 0;
        if (pVideoDriver->Surface->GetSurfaceDesc(&surfaceDesc) >= 0)
        {
            switch (surfaceDesc.ddpfPixelFormat.dwRGBBitCount)
            {
            case 1:     pitch = 16384;  break;
            case 2:     pitch = 8192;   break;
            case 4:     pitch = 4096;   break;
            case 8:     pitch = 2048;   break;
            case 16:    pitch = 1024;   break;
            case 24:    pitch = 512;    break;
            case 32:    pitch = 256;    break;
            default:    pitch = 0;      break;
            }
        }
        pd3d->pitchQ = pitch;

        if (pd3d->pIDirect3D3->EnumDevices(EnumD3DDevicesCallBack, pd3d) >= 0)
        {
            if (pd3d->NumEnums)
            {
                return pd3d;
            }
        }

        free(pd3d);
        return 0;
    }
    return pd3d;
}

static void SetDeviceDefaultRenderStates(D3dStruct* pCtx)
{
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0x8000);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATER);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_SUBPIXEL, TRUE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_MIRROR);
    pCtx->pIDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_CLAMP);
}

static signed int __stdcall Set3dDevice(D3dStruct* pContext, int id)
{
    if (pContext->CurrentID)
    {
        FreeD3dDThings(pContext);
    }

    auto pDevice = pContext->NextDevice;
    if (!pDevice)
    {
        return 1;
    }

    while (pDevice->ID != id)
    {
        pDevice = pDevice->NextD3DDevice;
        if (!pDevice)
        {
            return 1;
        }
    }
    pContext->ActiveDevice = pDevice;
    pContext->CurrentID = id;

    if (CreateD3DDevice(pContext))
    {
        return 1;
    }
    
    SetDeviceDefaultRenderStates(pContext);
    return 0;
}

static int CheckIfSpecialFindGfxEnabled()
{
    HKEY hKey = 0;
    DWORD Data = 1;
    DWORD cbData = sizeof(DWORD);
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\DMA Design Ltd\\GTA2\\Screen", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        DWORD Type = 0;
        if (RegQueryValueExA(hKey, "special_recognition", 0, &Type, reinterpret_cast<BYTE*>(&Data), &cbData) != ERROR_SUCCESS)
        {
            Data = 1;
            RegSetValueExA(hKey, "special_recognition", 0, REG_DWORD, reinterpret_cast<BYTE*>(&Data), cbData);
        }
    }
    else
    {
        DWORD dwDisposition = 0;
        if (RegCreateKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\DMA Design Ltd\\GTA2\\Screen", 0, "", 0, KEY_ALL_ACCESS, 0, &hKey, &dwDisposition) == ERROR_SUCCESS)
        {
            RegSetValueExA(hKey, "special_recognition", 0, REG_DWORD, reinterpret_cast<BYTE*>(&Data), cbData);
        }
    }

    if (hKey)
    {
        RegCloseKey(hKey);
    }

    return Data;
}

static HardwareTexture *__stdcall D3DTextureAllocate(D3dStruct* pd3d, int width, int height, int flags);

decltype(&D3DTextureAllocate) pD3DTextureAllocate = 0x0;

struct WidthFlags
{
    int width;
    int flags;
};
std::vector<WidthFlags> debugData;

static HardwareTexture *__stdcall D3DTextureAllocate(D3dStruct* pd3d, int width, int height, int flags)
{
    debugData.emplace_back(WidthFlags{ width, flags });

   // TextureFormat* pTextureFormat = FindTextureFormat(pd3d, flags);
   // pTextureFormat->BlueBitCount = 0;

//    auto real = pD3DTextureAllocate_2B560A0(pd3d, width, height, flags);
    auto re = TextureAlloc(pd3d, width, height, flags  | 2);
    /*
    assert(real->field_0_texture_id == re->field_0_texture_id);
    assert(real->Flags == re->Flags);
    assert(real->BitCount == re->BitCount);
    
    assert(real->BlueBitIndex == re->BlueBitIndex);
    assert(real->BlueUnknown == re->BlueUnknown);
    assert(real->BlueBitCount == re->BlueBitCount);

    assert(real->GreenBitIndex == re->GreenBitIndex);
    assert(real->GreenUnknown == re->GreenUnknown);
    assert(real->GreenBitCount == re->GreenBitCount);

    assert(real->RedBitIndex == re->RedBitIndex);
    assert(real->RedUnknown == re->RedUnknown);
    assert(real->RedBitCount == re->RedBitCount);

    
    assert(real->AlphaBitIndex == re->AlphaBitIndex);
    assert(real->AlphaUnknown == re->AlphaUnknown);
    if (real->AlphaBitIndex)
    {
        assert(real->AlphaBitCount == re->AlphaBitCount); // Possibly not inited sometimes? 0 seems to be random mem
    }

    assert(real->LockedPixelData == re->LockedPixelData);

    assert(real->pitch == re->pitch);

    assert(real->Width == re->Width);
    assert(real->Height == re->Height);
    */

    return re;
}

static HardwareTexture *__stdcall TextureAllocLocked(D3dStruct* pD3d, int width, int height, int flags)
{
    return TextureAlloc(pD3d, width, height, flags | 1);
}


static int Init2();
decltype(&Init2) pInit2 = 0x0;

static DWORD bShift2 = 0;
static DWORD bMask_2B93E30 = 0;
static DWORD bShift_2B63D58 = 0;
static DWORD gShift_2B93E34 = 0;
static DWORD gMask_2B985FC = 0;
static DWORD gShift2_2B985EC = 0;
static DWORD rShift_2B63DB0 = 0;
static DWORD rMask_2B63DF0 = 0;
static DWORD rShift2_2B93E8C = 0;

static DWORD bShift2_2B63DEC = 0;
static DWORD gShift_2B63DC0 = 0;
static DWORD bMask_2B959D0 = 0;
static DWORD bShift_2B93E1C = 0;
static DWORD rShift_2B63DD4 = 0;
static DWORD gMask_2B93E94 = 0;
static DWORD gShift2_2B93E2C = 0;
static DWORD rMask_2B959D4 = 0;
static DWORD rShift2_2B63DD0 = 0;


// TODO
static int Init2()
{
    int flags = 0;
    for (int i=12; --i >= 0;  )
    {
        WORD width = TextureSizes[i];
        if (width & 0x400)
        {
            width &= 0xFBFF;
            flags = 0x80000000;
        }
        else
        {
            flags = 0;
        }
        gGlobals.CacheArray [i] = 0;

        for (int j = 0; j < gGlobals.gCacheSizes[i]; j++)
        {
            Cache* pCache = (Cache *)malloc(sizeof(Cache));
            memset(pCache, 0, sizeof(Cache));

            // Correct num calls + args
            HardwareTexture* pTexture = D3DTextureAllocate((*gD3dPtr), width, width, flags);
            if (!pTexture)
            {
                break;
            }

            // probably correct, TODO CHECK ME
            HardwareTexture* pTexture2 = TextureAllocLocked((*gD3dPtr), width, width, flags);
            if (!pTexture2)
            {
                break;
            }

            D3dTextureCopy(pTexture, pTexture2);

            pCache->field_0 = 0x8000u;
            pCache->field_2 = width;  // TODO: Check me
            pCache->field_4 = width; // TODO: Check me
            pCache->field_C = 1.0f / static_cast<float>(width);
            pCache->pTexture = 0;
            pCache->UsedFrameNum = FrameNumber;
            pCache->CacheIdx = i;
            pCache->TextureId = pTexture2;
            pCache->pCache = 0;
            pCache->pNextCache = 0;

            if (gGlobals.CacheArray [i])
            {
                pCache->pCache = gGlobals.CacheArray [i];
                gGlobals.CacheArray [i]->pNextCache = pCache;
                gGlobals.CacheArray [i] = pCache;
            }
            else
            {
                gGlobals.CacheArray [i] = pCache;
            }
        }
    }

    ClearTexture(*gD3dPtr);

    (*renderStateCache) = 0;
    bPointFilteringOn = 0;

    // Same code as texture alloc func.. TODO: Merge into a helper
    const BYTE unknown[] = { 0 /*not inited in real func??*/, 1,3,7,15,31,64,127 };

    {
        TextureFormat format = {};
        ConvertPixelFormat(&format, &(*gD3dPtr)->TextureFormat->DDTextureFormat);



        rShift2_2B93E8C = format.BlueBitIndex;            // 0        // 43E8C
        rMask_2B63DF0 = unknown[format.BlueBitCount];     // 1f       // 13DF0
        rShift_2B63DB0 = 8 - format.BlueBitCount;         // 5        // 13DB0

        gShift2_2B985EC = format.GreenBitCount;            // 5        //
        gMask_2B985FC = unknown[format.GreenBitIndex];     // 1f       //
        gShift_2B93E34 = 16 - format.GreenBitIndex;        // b        //

        bShift_2B63D58 = format.RedBitIndex;             // a        //
        bMask_2B93E30 = unknown[format.RedBitCount];     // 1f       //
        bShift2 = 24 - format.RedBitCount;       // 13       //
    }


    {
        TextureFormat format = {};
        ConvertPixelFormat(&format, &(*gD3dPtr)->TextureFormat1->DDTextureFormat);

        rShift2_2B63DD0 = format.BlueBitIndex;            // 0 | 0
        rMask_2B959D4 = unknown[format.BlueBitCount];     // f | 5
        rShift_2B63DD4 = 8 - format.BlueBitCount;         // 4 | 5

        gShift2_2B93E2C = format.GreenBitCount;            // 4 | 5
        gMask_2B93E94 = unknown[format.GreenBitIndex];     // f | 5
        gShift_2B63DC0 = 16 - format.GreenBitIndex;        // c | 5

        bShift_2B93E1C = format.RedBitIndex;             // 8 | a
        bMask_2B959D0 = unknown[format.RedBitCount];     // f | 5
        bShift2_2B63DEC = 24 - format.RedBitCount;       // 14 | 5

        /*
        rShift2_2B63DD0 = 0x0;
        rMask_2B959D4 = 0xf;
        rShift_2B63DD4 = 0x4;

        gShift2_2B93E2C = 0x4;
        gMask_2B93E94 = 0xf;
        gShift_2B63DC0 = 0xc;

        bShift_2B93E1C = 0x8;
        bMask_2B959D0 = 0xf;
        bShift2_2B63DEC = 0x14;
        */
    }

    return 1;
}

static signed int Init()
{
    D3dStruct* pD3d = D3DCreate(gVideoDriver);
    (*gD3dPtr) = pD3d;
    if (Set3dDevice(pD3d, 2) != 1) // If it worked
    {
        memset(&gVideoDriver->DeviceCaps , 0, sizeof(DDCAPS));
        memset(&gVideoDriver->HelCaps, 0, sizeof(DDCAPS));
        gVideoDriver->DeviceCaps.dwSize = 0x17C;
        gVideoDriver->HelCaps.dwSize = 0x17C;
        auto err = gVideoDriver->IDDraw4->GetCaps(&gVideoDriver->DeviceCaps, &gVideoDriver->HelCaps);
        if (err)
        {
            D3dErr2String(err);
        }

        DDSCAPS2 ddcaps2 = {};
        ddcaps2.dwCaps = DDSCAPS_TEXTURE;

        DWORD totalMem = 0;
        DWORD freeMem = 0;
        gVideoDriver->IDDraw4->GetAvailableVidMem(&ddcaps2, &totalMem, &freeMem);
        auto cacheSize = totalMem >> 21;

        char buffer[120] = {};
        wsprintfA(buffer, "CacheMul = %d/VideMul %d", totalMem >> 21, totalMem);
        OutputDebugStringA(buffer);

        if (cacheSize <= 0)
        {
            cacheSize = 1;
        }

        if (cacheSize > 2)
        {
            cacheSize = 2;
        }

        if (cacheSize == 1 && (*gD3dPtr)->ActiveDevice->Flags & 0x80)
        {
            cacheSize = 2;
        }

        D3DDEVICEDESC hardwareCaps = {};
        D3DDEVICEDESC softwareCaps = {};
        hardwareCaps.dwSize = 0xFC;
        softwareCaps.dwSize = 0xFC;
        (*gD3dPtr)->pIDirect3DDevice3->GetCaps(&hardwareCaps, &softwareCaps);

        for (int i = 0; i < 12; i++)
        {
            gGlobals.gCacheSizes[i] = gGlobals.gCacheUnknown[i] * cacheSize;
            gGlobals.gCacheSizes[i] = gGlobals.gCacheUnknown[i] * cacheSize;
        }
        
        Init2();
  
        for (int i = 0; i < 12; i++)
        {
            if (gGlobals.gCacheUnknown[i] && !gGlobals.gCacheSizes[i])
            {
                return 1;
            }
        }

        

        (*gActiveTextureId) = (HardwareTexture*)-1;

        DDDEVICEIDENTIFIER deviceId = {};
        if (CheckIfSpecialFindGfxEnabled()
            && !(*gD3dPtr)->VideoDriver->IDDraw4->GetDeviceIdentifier(&deviceId, 0))
        {
            if (deviceId.dwVendorId == 4818)
            {
                if (deviceId.dwDeviceId == 24 || deviceId.dwDeviceId == 25)
                {
                    // TODO
                    //flt_2B60830 = 0;
                    //flt_2B6082C = 0x3E800000;

                    gGpuSpecificHack = 1;
                    OutputDebugStringA("THIS IS A RIVA");
                    return 0;
                }
            }
            else if (deviceId.dwVendorId == 4098)
            {
                if (deviceId.dwDeviceId == 18242)
                {
                    gbIsAtiRagePro = 1;
                    OutputDebugStringA("THIS IS AN ATI_RAGEPRO");
                    return 0;
                }
            }
            else if (deviceId.dwVendorId == 4172 && deviceId.dwDeviceId == 15623)
            {
                gGpuSpecificHack = 1;
                OutputDebugStringA("THIS IS AN PERMEDIA2 (with delta)");
            }
        }
        return 0;
    }

    return 1;
}

s32 CC gbh_Init(int a1)
{
    

    if (gProxyOnly)
    {
        auto r = gFuncs.pgbh_Init(a1);
        return r;
    }

    
    int result = Init();
    if (!result)
    {
        gbh_SetColourDepth();
        result = 0;
    }
    return result;
}

static int CC gbh_SetMode(Video* pVideoDriver, HWND hwnd, int modeId)
{
    pVideoDriver->ActiveDeviceId  = 0;

    int result = (gVideoDriverFuncs.pVid_SetMode)(pVideoDriver, hwnd, modeId);
    if (!result)
    {
        result = Init();
    }
    return result;
}



decltype(&D3dTextureUnknown) pD3dTextureUnknown_2B561D0 = 0;


static signed int __stdcall D3dTextureUnknown(HardwareTexture* pHardwareTexture, BYTE* pixelData, WORD* pPalData, int textureW, int textureH, int palSize, int renderFlags, char textureFlags)
{
    Video* pVideoDriver = pHardwareTexture->D3dStr->VideoDriver;
    memset(&pVideoDriver->DDSurfaceDesc7 , 0, sizeof(DDSURFACEDESC2));
    pVideoDriver->DDSurfaceDesc7.dwSize = sizeof(DDSURFACEDESC2);

    if (pHardwareTexture->pSurfaceForTexture->Lock(0, &pVideoDriver->DDSurfaceDesc7, 1, 0))
    {
        return 1;
    }

    DWORD local_dword_2B63CF0 = 0;
    if (renderFlags & 0x80)
    {
        // Transparent
        local_dword_2B63CF0 = 0xFFFFFFFF >> pHardwareTexture->AlphaUnknown;
        local_dword_2B63CF0 &= pHardwareTexture->AlphaBitCount;
        local_dword_2B63CF0 <<= pHardwareTexture->AlphaBitIndex;
    }
    else if (renderFlags & 0x380)
    {
        // Semi transparent
        local_dword_2B63CF0 = 0x88FFFFFF >> pHardwareTexture->AlphaUnknown;
        local_dword_2B63CF0 &= pHardwareTexture->AlphaBitCount;
        local_dword_2B63CF0 <<= pHardwareTexture->AlphaBitIndex;
    }

    BYTE* pPixels = (BYTE*)pVideoDriver->DDSurfaceDesc7.lpSurface;
    DWORD pitch = pVideoDriver->DDSurfaceDesc7.lPitch;


    DWORD sourcePixelIndex = 0;
    for (int y = 0; y < textureH; y++)
    {
        for (int x = 0; x < textureW; x++)
        {
            const DWORD surfaceIndex = (x * 2 + (y*(pitch)));
            const BYTE palIndex = pixelData[sourcePixelIndex++];
            WORD palValue = pPalData[palIndex];
            
            if (palIndex != 0)
            {
                palValue |= local_dword_2B63CF0;
            }

            WORD* p = (WORD*)(&pPixels[surfaceIndex]);
            *p = palValue;
        }
        
        const DWORD val =  palSize - textureW;
        sourcePixelIndex += val;
    }
  

    if (textureW < pHardwareTexture->Width)
    {
        // TODO: Clear remaining? Hardware texture is pre-cleared so probably don't need to?
    }
  
    if (textureH < pHardwareTexture->Height)
    {
        // TODO: Clear remaining? Hardware texture is pre-cleared so probably don't need to?
    }

    if (!pHardwareTexture->pSurfaceForTexture->Unlock(0))
    {
        pHardwareTexture->LockedPixelData  = 0;
        pHardwareTexture->pitch = 0;
    }
    
    auto pther = pHardwareTexture->pther;
    if (pther)
    {
        pther->pSurfaceForTexture->Restore();
        pther->OtherSurface->PageLock(0);
        auto hr = pther->IDirect3dTexture2->Load(pther->pther->IDirect3dTexture2);
        auto pSurface = pther->OtherSurface;
        if (hr == 1)
        {
            pSurface->Unlock(0);
            return 0;
        }
        pSurface->PageUnlock(0);
    }

    return 0;
}


decltype(&gbh_DrawQuad) pgbh_DrawQuad = 0x0;
decltype(&TextureAlloc) pTextureAlloc_2B55DA0 = 0x0;
decltype(&TextureCache) pTextureCache_E01EC0 = 0x0;
decltype(&D3dTextureSetCurrent) pD3dTextureSetCurrent_2B56110 = 0x0;


static void InstallHooks()
{
   // DetourAttach((PVOID*)(&pConvertPixelFormat_2B55A10), (PVOID)ConvertPixelFormat);
    //DetourAttach((PVOID*)(&pD3DTextureAllocate_2B560A0), (PVOID)D3DTextureAllocate_2B560A0);
   // DetourAttach((PVOID*)(&pFindTextureFormat_2B55C60), (PVOID)FindTextureFormat);

    
   
    //DetourAttach((PVOID*)(&pCreateD3DDevice_E01840), (PVOID)CreateD3DDevice);
    /*
    DetourAttach((PVOID*)(&pCacheFlushBatchRelated_2B52810), (PVOID)CacheFlushBatchRelated);
    DetourAttach((PVOID*)(&pD3dTextureUnknown_2B561D0), (PVOID)D3dTextureUnknown);
   // DetourAttach((PVOID*)(&pgbh_DrawQuad), (PVOID)gbh_DrawQuad);
   
    DetourAttach((PVOID*)(&pTextureCache_E01EC0), (PVOID)TextureCache);
    DetourAttach((PVOID*)(&pD3dTextureSetCurrent_2B56110), (PVOID)D3dTextureSetCurrent);
    DetourAttach((PVOID*)(&pSetRenderStates_E02960), (PVOID)SetRenderStates);
    */
   //DetourAttach((PVOID*)(&pInit2_2B51F40), (PVOID)Init2_2B51F40);

   //DetourAttach((PVOID*)(&pEnumTextureFormatsCallBack_E05BA0), (PVOID)EnumTextureFormatsCallBack);

}


//LightInternal Lights[256]; // 459E0

void CC gbh_ResetLights()
{
    if (gProxyOnly)
    {
        gFuncs.pgbh_ResetLights();
    }
    NumLights = 0;
}

int CC gbh_AddLight(Light* pLight)
{
    if (gProxyOnly)
    {
        auto ret = gFuncs.pgbh_AddLight(pLight);
        return ret;
    }

    DWORD idx = NumLights;

    Lights[idx].Flags = pLight->field_0;
    Lights[idx].Brightness = (float)((pLight->field_0 & 0xFF)) * 0.0039215689;
    Lights[idx].X = pLight->X;
    Lights[idx].Y = pLight->Y;
    Lights[idx].Z = pLight->Z;

    Lights[idx].Red = (float)(((unsigned int)pLight->Colour >> 16) & 0xFF) * 0.0039215689;
    Lights[idx].Green = (float)(((unsigned int)pLight->Colour >> 8) & 0xFF) * 0.0039215689;
    Lights[idx].Blue = (float)(pLight->Colour & 0xFF) * 0.0039215689;

    Lights[idx].Radius  =  ((pLight->field_0 >> 8) & 0xFF) * 0.0039215689 * 8.0;

    Lights[idx].RadiusSquared  = Lights[idx].Radius * Lights[idx].Radius;

    Lights[idx].RadiusNormalized = 1.0 / Lights[idx].Radius;

    NumLights++;

    return idx * sizeof(LightInternal);
}

static void RebasePtrs(DWORD baseAddr)
{
    // Funcs
    pConvertPixelFormat = (decltype(&ConvertPixelFormat))(baseAddr + 0x5A10);
    pD3DTextureAllocate = (decltype(&D3DTextureAllocate))(baseAddr + 0x60A0);
    pFindTextureFormat = (decltype(&FindTextureFormat))(baseAddr + 0x5C60);
    pInit2 = (decltype(&Init2))(baseAddr + 0x1F40);
    pCreateD3DDevice = (decltype(&CreateD3DDevice))(baseAddr + 0x01840);
    pEnumTextureFormatsCallBack = (decltype(&EnumTextureFormatsCallBack))(baseAddr + 0x5BA0);

    /*
  
    pD3dTextureUnknown_2B561D0 = (decltype(&D3dTextureUnknown))(baseAddr + 0x61D0);
    pCacheFlushBatchRelated_2B52810 = (decltype(&CacheFlushBatchRelated))(baseAddr + 0x2810);

    pTextureCache_E01EC0 = (decltype(&TextureCache))(baseAddr + 0x01EC0);
    pD3dTextureSetCurrent_2B56110 = (decltype(&D3dTextureSetCurrent))(baseAddr + 0x6110);
    pSetRenderStates_E02960 = (decltype(&SetRenderStates))(baseAddr + 0x2960);
    */

    // Vars
    //gGlobals.CacheArray  = (decltype(gGlobals.CacheArray ))(baseAddr + 0x13D4C);
    gActiveTextureId = (decltype(gActiveTextureId))(baseAddr + 0x13DF4);


    //real_texture_sizes_word_107E0 = (WORD*)(baseAddr + 0x107E0);
    //real_CacheSizes_word_10810 = (WORD*)(baseAddr + 0x10810);
    //real_CacheSizes_dword_43EB0 = (DWORD*)(baseAddr + 0x43EB0);


    //renderStateCache = (decltype(renderStateCache))(baseAddr + 0x43E24);

    //DWORD off = baseAddr + 0x485E0;
    //hack = (D3dStruct*)(off);
    //gD3dPtr = &hack;

}


u32 CC gbh_InitDLL(Video* pVideoDriver)
{
    

    
    HMODULE hOld = LoadLibrary("C:\\Program Files (x86)\\Rockstar Games\\GTA2\\_d3ddll.dll");

   // if (gProxyOnly)
    {
        PopulateS3DFunctions(hOld, gFuncs);
    }

    if (gDetours || gRealPtrs)
    {
        pgbh_DrawQuad = (decltype(pgbh_DrawQuad))GetProcAddress(hOld, "gbh_DrawQuad");
        RebasePtrs((DWORD)hOld);
    }

    if (gDetours)
    {
      
        InstallHooks();
       
    }

    gVideoDriver = pVideoDriver;

    if (gProxyOnly)
    {
        auto r = gFuncs.pgbh_InitDLL(pVideoDriver);
        return r;
    }
    


   
   /// PopulateVideoFunctions(pVideoDriver->SelfDllHandle, gVideoDriverFuncs);
    
    pOldCloseScreen = (*pVideoDriver->initDLL->pVid_CloseScreen);
    pOldSetMode = (*pVideoDriver->initDLL->pVid_SetMode);

    *pVideoDriver->initDLL->pVid_CloseScreen = gbh_CloseScreen;
    //*pVideoDriver->initDLL->pVid_GetSurface = gVideoDriverFuncs.pVid_GetSurface;
    //*pVideoDriver->initDLL->pVid_FreeSurface = gVideoDriverFuncs.pVid_FreeSurface;
    *pVideoDriver->initDLL->pVid_SetMode = gbh_SetMode;
    
    return 1;
}


signed int CC gbh_InitImageTable(int tableSize)
{
    if (gProxyOnly)
    {
        auto ret = gFuncs.pgbh_InitImageTable(tableSize);
        return ret;
    }
   
    gImageTable = reinterpret_cast<ImageTableEntry*>(malloc(sizeof(ImageTableEntry) * tableSize));
    if (!gImageTable)
    {
        return -1;
    }
    memset(gImageTable, 0, sizeof(ImageTableEntry) * tableSize);
    gImageTableCount = tableSize;
    return 0;
}

static WORD ConvertPixel(
    DWORD pixel,
    DWORD local_bMask_2B60828, DWORD local_bShift_2B93E00, DWORD local_Shift2_2B985F0,
    DWORD local_gMask_2B63DB4, DWORD local_gShift_2B93E84, DWORD local_gShift2_2B93E90,
    DWORD local_rMask_2B63DB8, DWORD local_rShift2_2B63D60, DWORD local_rShift_2B93E44
)
{
    DWORD r = pixel;
    DWORD g = pixel;
    DWORD b = pixel >> local_Shift2_2B985F0;

    return
        (((unsigned __int16)local_bMask_2B60828 & (unsigned __int16)b)
            << local_bShift_2B93E00) |
            ((local_gMask_2B63DB4 & (g >> local_gShift_2B93E84)) << local_gShift2_2B93E90)
        | ((local_rMask_2B63DB8 & (r >> local_rShift_2B93E44)) << local_rShift2_2B63D60);
}

signed int CC gbh_LoadImage(Image* pToLoad)
{
    if (gProxyOnly)
    {
        auto ret = gFuncs.pgbh_LoadImage(pToLoad);
        return ret;
    }

    DWORD freeImageIndex = 0;
    if (gImageTableCount > 0)
    {
        ImageTableEntry* pFreeImage = gImageTable;
        do
        {
            if (!pFreeImage->Loaded)
            {
                break;
            }
            ++freeImageIndex;
            ++pFreeImage;
        } while (freeImageIndex < gImageTableCount);
    }

    if (freeImageIndex >= gImageTableCount)
    {
        return -1;
    }

    if (!pToLoad || pToLoad->field_1 || pToLoad->field_2 != 2 || pToLoad->field_10 != 16)
    {
        return -2;
    }

    DDSURFACEDESC2 surfaceDesc = {};
    surfaceDesc.dwSize = sizeof(DDSURFACEDESC2);
    surfaceDesc.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
    surfaceDesc.ddsCaps.dwCaps = DDCAPS_BLT;
    if (gVideoDriver->DeviceCaps.dwCaps & DDCAPS_CANBLTSYSMEM)
    {
        surfaceDesc.ddsCaps.dwCaps = DDCAPS_BLT | DDCAPS_OVERLAY;
    }

    surfaceDesc.dwWidth = pToLoad->Width;
    surfaceDesc.dwHeight = pToLoad->Height;

    
    if (FAILED(gVideoDriver->IDDraw4->CreateSurface(&surfaceDesc,
        &gImageTable[freeImageIndex].pSurface, 0)))
    {
        return -3;
    }
    

    if (FAILED(gImageTable[freeImageIndex].pSurface->Lock(0,
        &surfaceDesc,
        DDLOCK_NOSYSLOCK | DDLOCK_WAIT,
        0)))
    {
        return -3;
    }

    TextureFormat format = {};
    ConvertPixelFormat(&format, &surfaceDesc.ddpfPixelFormat);

    const DWORD shiftR = format.RedBitIndex + format.RedBitCount - 5;
    const DWORD shiftG = format.GreenBitCount + format.GreenBitIndex - 5;
    const DWORD shiftB = format.BlueBitIndex + format.BlueBitCount - 5;


    BYTE* pPixels = (BYTE*)surfaceDesc.lpSurface;

    DWORD sourcePixelIndex = 0;
    for (int y = surfaceDesc.dwHeight-1; y >=0 ; y--)
    {
        for (int x = 0; x < surfaceDesc.dwWidth; x++)
        {
            const DWORD surfaceIndex = (x * 2 + (y*(surfaceDesc.lPitch)));
     
            BYTE* p = (BYTE*)(&pPixels[surfaceIndex]);
           
            BYTE* pSrc = (BYTE*)&pToLoad->field_12;
            pSrc += pToLoad->field_0;

            WORD pixelValue = ((WORD*)pSrc)[sourcePixelIndex];
            WORD r = (pixelValue & 0x7C00) >> 10;
            WORD g = (pixelValue & 0x03E0) >> 5;
            WORD b = pixelValue & 0x1F;
            WORD rgb = (r << shiftR) | (g << shiftG) | (b << shiftB);

            *(WORD*)p = rgb;
            
            sourcePixelIndex++;
        }
    }

    if (FAILED(gImageTable[freeImageIndex].pSurface->Unlock(NULL)))
    {
        // TODO: Real game bug, should be free'ing surface here?
        return -3;
    }

    gImageTable[freeImageIndex].Loaded = TRUE;
    gImageTable[freeImageIndex].W = surfaceDesc.dwWidth;
    gImageTable[freeImageIndex].H = surfaceDesc.dwHeight;

    return freeImageIndex;
}

Texture* CC gbh_LockTexture(Texture* pTexture)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_LockTexture(pTexture);
    }

    pTexture->pLockedPixels  = pTexture->pOriginalPixelData;
    pTexture->Flags |= 1;
    pTexture->PalSize  = 256;
    return TextureCache(pTexture);
}

void CC gbh_Plot(int a1, int a2, int a3, int a4)
{
    __debugbreak();
}

int CC gbh_PrintBitmap(int a1, int a2)
{
    __debugbreak();
    return 0;
}

unsigned int CC gbh_RegisterPalette(int paltId, DWORD* pData)
{
    if (gProxyOnly)
    {
        auto ret = gFuncs.pgbh_RegisterPalette(paltId, pData);
        return ret;
    }

    DWORD* pOriginal = pData;

    // A pass to fix up the source data
    for (int i = 0; i < 256; i++)
    {
        if (i == 0)
        {
            *pData = 0; // colour 0 of each palette is always transparent
        }
        else
        {
            if (*pData == 0)
            {
                *pData = 0x10000; // Flag to mark other would be transparent stuff as not transparent?
            }
        }
        pData += 64; // Pal data is stored in columns not rows
    }

    
    WORD* pAllocatedData = (WORD *)malloc(1024u); // Space for 2 16bit pals

    pals[paltId].mPOriginalData = pOriginal;
    pals[paltId].mbLoaded = 1;
    pals[paltId].mPData = pAllocatedData;



    DWORD local_Shift2_2B985F0 = bShift2;
    DWORD local_bMask_2B60828 = bMask_2B93E30;
    DWORD local_bShift_2B93E00 = bShift_2B63D58;
    DWORD local_gShift_2B93E84 = gShift_2B93E34;
    DWORD local_gMask_2B63DB4 = gMask_2B985FC;
    DWORD local_gShift2_2B93E90 = gShift2_2B985EC;
    DWORD local_rShift_2B93E44 = rShift_2B63DB0;
    DWORD local_rMask_2B63DB8 = rMask_2B63DF0;
    DWORD local_rShift2_2B63D60 = rShift2_2B93E8C;

    // Set the first pal to be a 16bit converted copy of the original
    pData = pOriginal;
    for (int i = 0; i < 256; i++)
    {
        pAllocatedData[i] = ConvertPixel(*pData,
            bMask_2B93E30, bShift_2B63D58, bShift2,
            gMask_2B985FC, gShift_2B93E34, gShift2_2B985EC,
            rMask_2B63DF0, rShift2_2B93E8C, rShift_2B63DB0);

        pData += 64; // Pal data is stored in columns not rows
    }

    local_Shift2_2B985F0 = bShift2_2B63DEC;
    local_gShift_2B93E84 = gShift_2B63DC0;
    local_bMask_2B60828 = bMask_2B959D0;
    local_bShift_2B93E00 = bShift_2B93E1C;
    local_rShift_2B93E44 = rShift_2B63DD4;
    local_gMask_2B63DB4 = gMask_2B93E94;
    local_gShift2_2B93E90 = gShift2_2B93E2C;
    local_rMask_2B63DB8 = rMask_2B959D4;
    local_rShift2_2B63D60 = rShift2_2B63DD0;

    // Set the 2nd pal to be a 16bit texture format converted copy of the original
    WORD* pSecond = pAllocatedData + 256;
    pData = pOriginal;
    for (int i = 0; i < 256; i++)
    {
        pSecond[i] = ConvertPixel(*pData,
            bMask_2B959D0, bShift_2B93E1C, bShift2_2B63DEC,
            gMask_2B93E94, gShift_2B63DC0, gShift2_2B93E2C,
            rMask_2B959D4, rShift2_2B63DD0, rShift_2B63DD4);

        pData += 64; // Pal data is stored in columns not rows
    }

    return paltId; // TODO: Func probably doesn't really return anything?
}

Texture* CC gbh_RegisterTexture(__int16 width, __int16 height, BYTE* pData, int pal_idx, char a5)
{
    if (gProxyOnly)
    {
        auto r = gFuncs.pgbh_RegisterTexture(width, height, pData, pal_idx, a5);
        return r;
    }

    
    Texture* result = reinterpret_cast<Texture*>(malloc(sizeof(Texture)));
    if (!result)
    {
        return 0;
    }

    memset(result, 0, sizeof(Texture));

    result->ID = gTextureId++;
    result->field_2 = 0;

    // TODO: What does this mean, should it have a de-ref to check if contains transparent colour ??
    result->PalIsTrans  = LOBYTE(pals[pal_idx].mPData);

    result->Width = width;
    result->PalSize = 0;
    result->pLockedPixels = 0;
    result->field_C = 0;
    result->field_D = 0;
    result->Height = height;
    result->PalIsValid =  pals[pal_idx].mbLoaded;

    if (a5 && gbIsAtiRagePro)
    {
        result->Flags = 0x80u;
    }
    else
    {
        result->Flags = 0;
    }
    result->pOriginalPixelData = pData;
    result->pPaltData = pals[pal_idx].mPData;
    result->NextCache = 0;

    return result;
}

void CC gbh_SetAmbient(float ambient)
{
    if (gProxyOnly)
    {
        gFuncs.pgbh_SetAmbient(ambient);
    }
    gfAmbient = ambient * 255.0f;
}


int CC gbh_SetCamera(float a1, float a2, float a3, float a4)
{
    // This function seems to do nothing
    return 0;
}

int CC gbh_SetColourDepth()
{
    // TODO
    //__debugbreak();
   // return 1;
    if (gProxyOnly)
    {
        return gFuncs.pgbh_SetColourDepth();
    }
    return 1;
}

float CC gbh_SetWindow(float left, float top, float right, float bottom)
{
    float ret = 0.0f;
    if (gProxyOnly)
    {
        ret = gFuncs.pgbh_SetWindow(left, top, right, bottom);
    }

    gWindowLeft = left;
    gWindowRight = right;
    gWindowTop = top;
    gWindowBottom = bottom;
   // gWindow_d5_dword_E13DC4 = gVideoDriver->Flags & 1; // TODO: Never used?

    if (gProxyOnly)
    {
        return ret;
    }

    return bottom;
}

Texture* CC gbh_UnlockTexture(Texture* pTexture)
{
    if (gProxyOnly)
    {
        return gFuncs.pgbh_UnlockTexture(pTexture);
    }

    pTexture->PalSize = 0;
    pTexture->pLockedPixels = 0;
    pTexture->Flags &= 0xFEu;
    return pTexture;
}
