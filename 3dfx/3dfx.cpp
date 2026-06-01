#include "3dfx.h"
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#define NUM_CACHE_POOLS 12
#define MAX_PALETTES 16384
#define MAX_LIGHTS 256
#define MAX_IMAGE_TABLE 1024

#define ARGB_A(color) (((color) >> 24) & 0xFF)
#define ARGB_R(color) (((color) >> 16) & 0xFF)
#define ARGB_G(color) (((color) >> 8) & 0xFF)
#define ARGB_B(color) ((color) & 0xFF)

static WORD TextureSizes[12] = { 8, 16, 32, 64, 128, 256, 1032, 1040, 1056, 1088, 1152, 1280 };

struct Cache
{
    WORD field_0;
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
    FxU32 texAddress;
    FxU32 texEvenOdd;
    WORD texWidth;
    WORD texHeight;
    DWORD field_30;
};

struct Globals
{
    DWORD mNumPolysDrawn;
    DWORD mNumTextureSwaps;
    DWORD mNumBatchFlushes;
    DWORD mSceneTime;
    DWORD gCacheSizes[12];
    DWORD gCacheSizes1[12];
    DWORD gCacheHitRates[12];
    DWORD gCacheUnknown[12];
    Cache* CacheArray[12];
};

struct LightInternal
{
    DWORD Flags;
    float Brightness;
    float Radius;
    float RadiusSquared;
    float RadiusNormalized;
    float X;
    float Y;
    float Z;
    float Red;
    float Green;
    float Blue;
};

struct PalData
{
    DWORD* mPOriginalData;
    WORD* mPData;
    DWORD mbLoaded;
};

struct ImageTableEntry
{
    BOOL Loaded;
    DWORD W;
    DWORD H;
    void* pSurface;
};

static Globals gGlobals;
static Video* gVideoDriver;
static LightInternal Lights[256];
static PalData pals[16384];
static ImageTableEntry* gImageTable;
static int gImageTableCount;

static DWORD gTextureId;
static int NumLights;
static float gfAmbient;
static DWORD FrameNumber;
static int gbSurfaceIsFreed;
static int gWindowActive;
static float gWindowLeft;
static float gWindowTop;
static float gWindowRight;
static float gWindowBottom;
static int gGlideInitDone;
static FxU32 gScreenWidth;
static FxU32 gScreenHeight;
static int gTexMemInitialized;
static FxU32 gTexMemStart;
static FxU32 gTexMemEnd;
static FxU32 gTexMemCurrent;
static int gRenderStateCache;
static int gPointFilteringOn;

static void (CC *pOldCloseScreen)(Video*);
static s32 (CC *pOldSetMode)(Video*, HWND, s32);

static GrVertex gVertices[4];
static int gVertexCount;

static int gScreenTable[3200];
static int gScreenTableSize;

static DWORD gD3dPerfCounters[10];

static DWORD Convert32To1555(DWORD color32)
{
    int a = (color32 >> 24) & 0x80 ? 1 : 0;
    int r = ((color32 >> 16) & 0xFF) >> 3;
    int g = ((color32 >> 8) & 0xFF) >> 3;
    int b = (color32 & 0xFF) >> 3;
    return (a << 15) | (r << 10) | (g << 5) | b;
}

static void ColorToFloats(DWORD color, float& r, float& g, float& b, float& a)
{
    a = (float)((color >> 24) & 0xFF) / 255.0f;
    r = (float)((color >> 16) & 0xFF) / 255.0f;
    g = (float)((color >> 8) & 0xFF) / 255.0f;
    b = (float)(color & 0xFF) / 255.0f;
}

static void GetScreenSize(GrScreenResolution_t res, FxU32& w, FxU32& h)
{
    switch (res)
    {
    case GR_RESOLUTION_320x200:   w = 320;  h = 200;  break;
    case GR_RESOLUTION_320x240:   w = 320;  h = 240;  break;
    case GR_RESOLUTION_400x256:   w = 400;  h = 256;  break;
    case GR_RESOLUTION_512x384:   w = 512;  h = 384;  break;
    case GR_RESOLUTION_640x200:   w = 640;  h = 200;  break;
    case GR_RESOLUTION_640x350:   w = 640;  h = 350;  break;
    case GR_RESOLUTION_640x400:   w = 640;  h = 400;  break;
    case GR_RESOLUTION_640x480:   w = 640;  h = 480;  break;
    case GR_RESOLUTION_800x600:   w = 800;  h = 600;  break;
    case GR_RESOLUTION_856x480:   w = 856;  h = 480;  break;
    case GR_RESOLUTION_960x720:   w = 960;  h = 720;  break;
    case GR_RESOLUTION_1024x768:  w = 1024; h = 768;  break;
    case GR_RESOLUTION_1280x1024: w = 1280; h = 1024; break;
    case GR_RESOLUTION_1600x1200: w = 1600; h = 1200; break;
    case GR_RESOLUTION_400x300:   w = 400;  h = 300;  break;
    default:                      w = 640;  h = 480;  break;
    }
}

static FxU32 FindBestResolution(int width, int height)
{
    if (width <= 320 && height <= 200) return GR_RESOLUTION_320x200;
    if (width <= 320 && height <= 240) return GR_RESOLUTION_320x240;
    if (width <= 400 && height <= 256) return GR_RESOLUTION_400x256;
    if (width <= 512 && height <= 384) return GR_RESOLUTION_512x384;
    if (width <= 640 && height <= 200) return GR_RESOLUTION_640x200;
    if (width <= 640 && height <= 350) return GR_RESOLUTION_640x350;
    if (width <= 640 && height <= 400) return GR_RESOLUTION_640x400;
    if (width <= 640 && height <= 480) return GR_RESOLUTION_640x480;
    if (width <= 800 && height <= 600) return GR_RESOLUTION_800x600;
    if (width <= 856 && height <= 480) return GR_RESOLUTION_856x480;
    if (width <= 960 && height <= 720) return GR_RESOLUTION_960x720;
    if (width <= 1024 && height <= 768) return GR_RESOLUTION_1024x768;
    if (width <= 1280 && height <= 1024) return GR_RESOLUTION_1280x1024;
    if (width <= 1600 && height <= 1200) return GR_RESOLUTION_1600x1200;
    return GR_RESOLUTION_640x480;
}

static void ConvertVertToGrVertex(const Vert& src, GrVertex& dst, float uvScale, DWORD diffuse, BOOL hasLighting)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.ooz = 1.0f;
    dst.oow = 1.0f / src.z;

    ColorToFloats(diffuse, dst.r, dst.g, dst.b, dst.a);

    dst.z = 1.0f - (1.0f / src.z);

    dst.tmuvtx[0].sow = src.u * uvScale;
    dst.tmuvtx[0].tow = src.v * uvScale;
    dst.tmuvtx[0].oow = 1.0f;

    dst.tmuvtx[1].sow = src.u * uvScale;
    dst.tmuvtx[1].tow = src.v * uvScale;
    dst.tmuvtx[1].oow = 1.0f;
}

static Texture* TextureCache(Texture* pTexture)
{
    Cache* pCache = pTexture->NextCache;
    if (pCache)
    {
        pCache->Flags |= 0x80;
        pCache->pTexture = 0;
        pCache->UsedFrameNum = FrameNumber - 1;
        pTexture->NextCache = 0;

        Cache* p20Cache = pCache->pCache;
        if (p20Cache)
        {
            p20Cache->pNextCache = pCache->pNextCache;
            Cache* pNext = pCache->pNextCache;
            if (pNext)
            {
                pNext->pCache = pCache->pCache;
            }
            else
            {
                gGlobals.CacheArray[pCache->CacheIdx] = pCache->pCache;
            }

            pCache->pNextCache = gGlobals.CacheArray[pCache->CacheIdx];
            gGlobals.CacheArray[pCache->CacheIdx]->pCache = pCache;
            gGlobals.CacheArray[pCache->CacheIdx] = pCache;
            pCache->pCache = 0;
        }
    }
    return pTexture;
}

static void UploadTextureToTMU(Cache* pCache, Texture* pTexture, int renderFlags)
{
    if (!gGlideInitDone) return;

    int width = pTexture->Width;
    int height = pTexture->Height;
    WORD* pPal = pTexture->pPaltData;
    BYTE* pPixels = pTexture->pOriginalPixelData;
    BYTE addY = pTexture->field_C;
    BYTE addX = pTexture->field_D;

    if (addY || addX)
    {
        pPixels = pPixels + addX + (addY << 8);
    }

    FxU32 addr = pCache->texAddress;

    GrLOD_t lod = GR_LOD_256;
    if (width <= 256) lod = GR_LOD_256;
    if (width <= 128) lod = GR_LOD_128;
    if (width <= 64) lod = GR_LOD_64;
    if (width <= 32) lod = GR_LOD_32;
    if (width <= 16) lod = GR_LOD_16;
    if (width <= 8) lod = GR_LOD_8;
    if (width <= 4) lod = GR_LOD_4;
    if (width <= 2) lod = GR_LOD_2;
    if (width <= 1) lod = GR_LOD_1;

    GrAspectRatio_t aspect = GR_ASPECT_1x1;
    if (width == height * 8) aspect = GR_ASPECT_8x1;
    else if (width == height * 4) aspect = GR_ASPECT_4x1;
    else if (width == height * 2) aspect = GR_ASPECT_2x1;
    else if (width == height) aspect = GR_ASPECT_1x1;
    else if (height == width * 2) aspect = GR_ASPECT_1x2;
    else if (height == width * 4) aspect = GR_ASPECT_1x4;
    else if (height == width * 8) aspect = GR_ASPECT_1x8;

    BYTE* converted = (BYTE*)malloc(width * height);
    if (!converted) return;

    memcpy(converted, pPixels, width * height);

    GrTexInfo texInfo;
    texInfo.smallLod = lod;
    texInfo.largeLod = lod;
    texInfo.aspectRatio = aspect;
    texInfo.format = GR_TEXFMT_P_8;
    texInfo.data = converted;

    grTexDownloadMipMap(GR_TMU0, addr, 0, &texInfo);

    FxU32 palette32[256];
    for (int i = 0; i < 256; i++)
    {
        WORD pal16 = pPal[i];
        if (renderFlags & 0x80)
        {
            int r = (pal16 >> 10) & 0x1F;
            int g = (pal16 >> 5) & 0x1F;
            int b = pal16 & 0x1F;
            int a = (i == 0) ? 0 : 1;

            palette32[i] = (a << 24) | ((r << 19) | (r << 14) | (r << 9) | (r << 4) | (r >> 1)) & 0xFF0000
                         | ((g << 19) | (g << 14) | (g << 9) | (g << 4) | (g >> 1)) & 0xFF00
                         | ((b << 19) | (b << 14) | (b << 9) | (b << 4) | (b >> 1)) & 0xFF;
        }
        else if (renderFlags & 0x380)
        {
            int r = (pal16 >> 10) & 0x1F;
            int g = (pal16 >> 5) & 0x1F;
            int b = pal16 & 0x1F;
            int a = (i == 0) ? 0 : 1;

            palette32[i] = (a << 24) | ((r * 255 / 31) << 16) | ((g * 255 / 31) << 8) | (b * 255 / 31);
        }
        else
        {
            int r = (pal16 >> 10) & 0x1F;
            int g = (pal16 >> 5) & 0x1F;
            int b = pal16 & 0x1F;

            palette32[i] = (0xFF << 24) | ((r * 255 / 31) << 16) | ((g * 255 / 31) << 8) | (b * 255 / 31);
        }
    }

    grTexDownloadTable(GR_TMU0, palette32);

    free(converted);

    pCache->texAddress = addr;
    pCache->texWidth = width;
    pCache->texHeight = height;
}

static int GetCacheSizeIndex(int size)
{
    if (size & 0x400)
    {
        size &= 0xFBFF;
    }
    for (int i = 0; i < 12; i++)
    {
        if (size <= TextureSizes[i])
            return i;
    }
    return 11;
}

static void CacheFlushBatchRelated(Texture* pTexture, int renderFlags)
{
    int biggestSide = pTexture->Width;
    if (pTexture->Height > biggestSide)
    {
        biggestSide = pTexture->Height;
    }

    int flagsCopy = renderFlags;
    if (renderFlags & 0x380)
    {
        WORD wSide = (WORD)biggestSide;
        wSide = (wSide & 0x00FF) | ((((wSide >> 8) & 0xFF) | 4) << 8);
        biggestSide = wSide;
        flagsCopy = renderFlags | 0x80;
    }

    int cacheIndex = GetCacheSizeIndex(biggestSide);

    Cache* pCache = gGlobals.CacheArray[cacheIndex];
    if (pCache->UsedFrameNum == FrameNumber)
    {
        ++gGlobals.mNumBatchFlushes;
        ++FrameNumber;
    }

    Texture* pCachedTexture = pCache->pTexture;
    if (pCachedTexture)
    {
        pCachedTexture->NextCache = 0;
    }

    pTexture->NextCache = pCache;
    pCache->field_0 &= 0x7FFF;
    pCache->pTexture = pTexture;
    pCache->field_10 = (DWORD)(0.00390625f / (float)pTexture->PalIsValid);
    pCache->field_14 = (DWORD)(pCache->field_10 * 255.0f);

    UploadTextureToTMU(pCache, pTexture, renderFlags);

    ++gGlobals.gCacheHitRates[pCache->CacheIdx];
}

static void SetRenderStates(int states)
{
    if (states & 0x380)
    {
        if (states & 0x200)
        {
            if (gRenderStateCache != 2)
            {
                gRenderStateCache = 2;
                grAlphaBlendFunction(GR_BLEND_ONE, GR_BLEND_ONE, GR_BLEND_ONE, GR_BLEND_ONE);
                grColorCombine(GR_COMBINE_FUNCTION_LOCAL, GR_COMBINE_FACTOR_NONE, GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_ITERATED, FXFALSE);
            }
        }
        else if (states & 0x180)
        {
            if (gRenderStateCache != 1)
            {
                gRenderStateCache = 1;
                grAlphaBlendFunction(GR_BLEND_SRC_ALPHA, GR_BLEND_ONE_MINUS_SRC_ALPHA, GR_BLEND_SRC_ALPHA, GR_BLEND_ONE_MINUS_SRC_ALPHA);
                grColorCombine(GR_COMBINE_FUNCTION_SCALE_OTHER, GR_COMBINE_FACTOR_LOCAL, GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE);
                grAlphaCombine(GR_COMBINE_FUNCTION_SCALE_OTHER, GR_COMBINE_FACTOR_LOCAL, GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE);
            }
        }
    }
    else
    {
        if (gRenderStateCache)
        {
            gRenderStateCache = 0;
            grAlphaBlendFunction(GR_BLEND_ONE, GR_BLEND_ZERO, GR_BLEND_ONE, GR_BLEND_ZERO);
            grColorCombine(GR_COMBINE_FUNCTION_SCALE_OTHER, GR_COMBINE_FACTOR_ONE, GR_COMBINE_LOCAL_NONE, GR_COMBINE_OTHER_TEXTURE, FXFALSE);
        }
    }
}

static int LightVerts_new(int vertCount, Vert* pVerts, int alwaysZero, unsigned __int8 colourRelated)
{
    for (int vertIdx = 0; vertIdx < vertCount; vertIdx++)
    {
        float lightR = 0.0f;
        float lightG = 0.0f;
        float lightB = 0.0f;

        for (int j = 0; j < NumLights; j++)
        {
            if ((Lights[j].Flags & 0x30000) == 0x10000)
            {
                float dx = pVerts[vertIdx].x - Lights[j].X;
                float dy = pVerts[vertIdx].y - Lights[j].Y;
                float dz = pVerts[vertIdx].z - Lights[j].Z;

                float distSq = (dx * dx) + (dy * dy) + (dz * dz);

                if (distSq <= Lights[j].RadiusSquared)
                {
                    float dist = (float)sqrt(distSq);
                    float normDist = (Lights[j].Radius - dist) * Lights[j].RadiusNormalized;
                    if (normDist > 0.0f)
                    {
                        float lightVal = normDist * Lights[j].Brightness;
                        lightR += Lights[j].Red * lightVal;
                        lightG += Lights[j].Green * lightVal;
                        lightB += Lights[j].Blue * lightVal;
                    }
                }
            }
        }

        float colourConv = colourRelated * 0.0039215689f;

        float b1 = colourConv * (float)((pVerts[vertIdx].diff >> 16) & 0xFF) * lightR + gfAmbient;
        if (b1 > 255.0f) b1 = 255.0f;

        float b2 = colourConv * (float)((pVerts[vertIdx].diff >> 8) & 0xFF) * lightG + gfAmbient;
        if (b2 > 255.0f) b2 = 255.0f;

        float b3 = colourConv * (float)(pVerts[vertIdx].diff & 0xFF) * lightB + gfAmbient;
        if (b3 > 255.0f) b3 = 255.0f;

        DWORD newDiff = ((DWORD)(b1) << 16) | ((DWORD)(b2) << 8) | (DWORD)(b3);
        newDiff = (pVerts[vertIdx].diff & 0xFF000000) | newDiff;
        pVerts[vertIdx].diff = newDiff;
    }
    return 0;
}

static void CleanUpGlide()
{
    for (int idx = 0; idx < 12; idx++)
    {
        Cache* pCache = gGlobals.CacheArray[idx];
        if (pCache)
        {
            Cache* pCurrentCache = 0;
            do
            {
                pCurrentCache = pCache->pNextCache;
                if (pCache->pTexture)
                {
                    TextureCache(pCache->pTexture);
                }
                Cache* nextPtr = pCache->pNextCache;
                if (nextPtr)
                {
                    nextPtr->pCache = 0;
                    gGlobals.CacheArray[idx] = pCache->pNextCache;
                }
                free(pCache);
                pCache = pCurrentCache;
            } while (pCurrentCache);
        }
        gGlobals.CacheArray[idx] = 0;
    }
}

static int Init2()
{
    for (int i = 11; i >= 0; i--)
    {
        WORD width = TextureSizes[i];
        DWORD flags = 0;
        if (width & 0x400)
        {
            width &= 0xFBFF;
            flags = 0x80000000;
        }

        gGlobals.CacheArray[i] = 0;

        for (DWORD j = 0; j < gGlobals.gCacheSizes[i]; j++)
        {
            Cache* pCache = (Cache*)malloc(sizeof(Cache));
            memset(pCache, 0, sizeof(Cache));

            pCache->field_0 = 0x8000;
            pCache->field_2 = (BYTE)width;
            pCache->field_4 = width;
            pCache->field_C = 1.0f / (float)width;
            pCache->pTexture = 0;
            pCache->UsedFrameNum = FrameNumber;
            pCache->CacheIdx = (BYTE)i;
            pCache->texAddress = 0;
            pCache->pCache = 0;
            pCache->pNextCache = 0;

            if (gGlobals.CacheArray[i])
            {
                pCache->pCache = gGlobals.CacheArray[i];
                gGlobals.CacheArray[i]->pNextCache = pCache;
                gGlobals.CacheArray[i] = pCache;
            }
            else
            {
                gGlobals.CacheArray[i] = pCache;
            }
        }
    }

    gRenderStateCache = 0;
    gPointFilteringOn = 0;

    return 1;
}

static int Init()
{
    if (!gGlideInitDone)
    {
        grGlideInit();
        gGlideInitDone = 1;
    }

    FxU32 res = FindBestResolution(gVideoDriver->FoundWidth, gVideoDriver->FoundHeight);

    if (!grSstWinOpen((FxU)gVideoDriver->hwnd, (GrScreenResolution_t)res,
                      GR_REFRESH_60Hz, GR_COLORFORMAT_ARGB,
                      GR_ORIGIN_UPPER_LEFT, 1, 1))
    {
        res = GR_RESOLUTION_640x480;
        grSstWinOpen((FxU)gVideoDriver->hwnd, res,
                     GR_REFRESH_60Hz, GR_COLORFORMAT_ARGB,
                     GR_ORIGIN_UPPER_LEFT, 1, 1);
    }

    GetScreenSize((GrScreenResolution_t)res, gScreenWidth, gScreenHeight);

    gTexMemStart = grTexMinAddress(GR_TMU0);
    gTexMemEnd = grTexMaxAddress(GR_TMU0);
    gTexMemCurrent = gTexMemStart;
    gTexMemInitialized = 1;

    DWORD totalTexMem = gTexMemEnd - gTexMemStart;
    int cacheSize = (int)(totalTexMem >> 21);

    char buffer[120];
    wsprintfA(buffer, "CacheMul = %d/TexMem %d", cacheSize, totalTexMem);
    OutputDebugStringA(buffer);

    if (cacheSize <= 0) cacheSize = 1;
    if (cacheSize > 2) cacheSize = 2;

    for (int i = 0; i < 12; i++)
    {
        gGlobals.gCacheSizes[i] = gGlobals.gCacheUnknown[i] * cacheSize;
    }

    Init2();

    for (int i = 0; i < 12; i++)
    {
        if (gGlobals.gCacheUnknown[i] && !gGlobals.gCacheSizes[i])
        {
            return 0;
        }
    }

    grCullMode(GR_CULL_DISABLE);
    grDepthBufferMode(GR_DEPTHBUFFER_DISABLE);
    grAlphaBlendFunction(GR_BLEND_ONE, GR_BLEND_ZERO, GR_BLEND_ONE, GR_BLEND_ZERO);
    grColorCombine(GR_COMBINE_FUNCTION_SCALE_OTHER, GR_COMBINE_FACTOR_ONE, GR_COMBINE_LOCAL_NONE, GR_COMBINE_OTHER_TEXTURE, FXFALSE);
    grAlphaCombine(GR_COMBINE_FUNCTION_SCALE_OTHER, GR_COMBINE_FACTOR_ONE, GR_COMBINE_LOCAL_NONE, GR_COMBINE_OTHER_TEXTURE, FXFALSE);
    grTexFilterMode(GR_TMU0, GR_TEXTUREFILTER_BILINEAR, GR_TEXTUREFILTER_BILINEAR);
    grTexClampMode(GR_TMU0, GR_TEXTURECLAMP_CLAMP, GR_TEXTURECLAMP_CLAMP);
    grDitherMode(GR_DITHER_4x4);
    grCoordinateSpace(GR_WINDOW_COORDS);

    return 0;
}

static s32 CC gbh_SetMode(Video* pVideoDriver, HWND hWnd, s32 modeId)
{
    gWindowActive = 0;

    if (gGlideInitDone)
    {
        grSstWinClose(0);
        grGlideShutdown();
        gGlideInitDone = 0;
    }

    s32 result = pOldSetMode(pVideoDriver, hWnd, modeId);

    if (result == 0)
    {
        Init();
        gWindowActive = 1;
    }

    return result;
}

void CC ConvertColourBank(s32 unknown)
{
}

int CC DrawLine(int a1, int a2, int a3, int a4, int a5)
{
    int diff = a4 - a2;
    return diff >= 0 ? diff : -diff;
}

void CC SetShadeTableA(int a1, int a2, int a3, int a4, int a5)
{
}

int* CC MakeScreenTable(int value, int elementSize, unsigned int size)
{
    gScreenTableSize = size;
    int* result = 0;
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

int CC gbh_AddLight(Light* pLight)
{
    DWORD idx = NumLights;

    Lights[idx].Flags = pLight->field_0;
    Lights[idx].Brightness = (float)((pLight->field_0 & 0xFF)) * 0.0039215689f;
    Lights[idx].X = pLight->X;
    Lights[idx].Y = pLight->Y;
    Lights[idx].Z = pLight->Z;

    Lights[idx].Red = (float)((pLight->Colour >> 16) & 0xFF) * 0.0039215689f;
    Lights[idx].Green = (float)((pLight->Colour >> 8) & 0xFF) * 0.0039215689f;
    Lights[idx].Blue = (float)(pLight->Colour & 0xFF) * 0.0039215689f;

    Lights[idx].Radius = (float)((pLight->field_0 >> 8) & 0xFF) * 0.0039215689f * 8.0f;
    Lights[idx].RadiusSquared = Lights[idx].Radius * Lights[idx].Radius;
    Lights[idx].RadiusNormalized = 1.0f / Lights[idx].Radius;

    NumLights++;

    return idx * sizeof(LightInternal);
}

char CC gbh_AssignPalette(Texture* pTexture, int palId)
{
    int needUnlock = 0;
    if (!(pTexture->Flags & 1))
    {
        gbh_LockTexture(pTexture);
        needUnlock = 1;
    }

    pTexture->pPaltData = pals[palId].mPData;
    DWORD result = pals[palId].mbLoaded;
    pTexture->PalIsValid = (u8)result;

    if (needUnlock)
    {
        gbh_UnlockTexture(pTexture);
    }
    return (char)result;
}

void CC gbh_BeginLevel()
{
}

int gbh_BeginScene()
{
    if (gVideoDriver->Flags & 1)
    {
        gbSurfaceIsFreed = 1;
        (*gVideoDriver->initDLL->pVid_FreeSurface)(gVideoDriver);
    }
    else
    {
        gbSurfaceIsFreed = 0;
    }

    memset(gGlobals.gCacheHitRates, 0, sizeof(gGlobals.gCacheHitRates));
    gGlobals.mNumBatchFlushes = 0;
    gGlobals.mNumTextureSwaps = 0;
    gGlobals.mNumPolysDrawn = 0;
    ++FrameNumber;

    grBufferClear(0, 0, GR_ZDEPTHVALUE_NEAREST);

    return 0;
}

int CC gbh_BlitBuffer(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return 0;
}

char CC gbh_BlitImage(int imageIndex, int srcLeft, int srcTop, int srcRight, int srcBottom, int dstX, int dstY)
{
    int result = 0;
    if (imageIndex > gImageTableCount) result = -1;
    if (!gImageTable[imageIndex].Loaded) return -1;

    if (srcLeft < 0 || srcTop < 0 || srcRight < 0 || srcBottom < 0 ||
        srcLeft > (int)gImageTable[imageIndex].W ||
        srcTop > (int)gImageTable[imageIndex].H ||
        srcRight > (int)gImageTable[imageIndex].W ||
        srcBottom > (int)gImageTable[imageIndex].H)
    {
        return -2;
    }

    if (dstX < 0 || dstY < 0 ||
        (dstX - srcLeft + srcRight) > (int)gVideoDriver->RectRight ||
        (dstY - srcTop + srcBottom) > (int)gVideoDriver->RectBottom)
    {
        return -3;
    }

    return 0;
}

void CC gbh_CloseDLL()
{
    Video* pVideoDriver = gVideoDriver;
    CleanUpGlide();

    if (gGlideInitDone)
    {
        grSstWinClose(0);
        grGlideShutdown();
        gGlideInitDone = 0;
    }

    if (pOldCloseScreen)
    {
        pOldCloseScreen(pVideoDriver);
    }

    if (gVideoDriver && gVideoDriver->initDLL)
    {
        *gVideoDriver->initDLL->pVid_CloseScreen = pOldCloseScreen;
        *gVideoDriver->initDLL->pVid_SetMode = pOldSetMode;
    }
}

void CC gbh_CloseScreen(Video* pVideo)
{
    CleanUpGlide();

    if (gGlideInitDone)
    {
        grSstWinClose(0);
        grGlideShutdown();
        gGlideInitDone = 0;
    }

    pOldCloseScreen(pVideo);
}

unsigned int CC gbh_Convert16BitGraphic(int a1, unsigned int a2, WORD* a3, signed int a4)
{
    return 0;
}

unsigned int CC gbh_ConvertColour(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
    return (a1 << 16) | (a2 << 8) | a3;
}

int CC gbh_DrawFlatRect(int a1, int a2)
{
    return 0;
}

void CC gbh_DrawQuad(int quadFlags, Texture* pTexture, Vert* pVerts, int baseColour)
{
    if (pVerts[0].z <= 0.0f) return;

    SetRenderStates(quadFlags);

    if (quadFlags & 0x20000)
    {
        if (!gPointFilteringOn)
        {
            gPointFilteringOn = 1;
            grTexFilterMode(GR_TMU0, GR_TEXTUREFILTER_POINT_SAMPLED, GR_TEXTUREFILTER_POINT_SAMPLED);
        }
    }
    else
    {
        if (gPointFilteringOn)
        {
            gPointFilteringOn = 0;
            grTexFilterMode(GR_TMU0, GR_TEXTUREFILTER_BILINEAR, GR_TEXTUREFILTER_BILINEAR);
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
        BYTE v9 = pTexture->Flags;
        if (quadFlags & 0x300)
        {
            pTexture->Flags &= 0xBF;
        }
        else
        {
            pTexture->Flags |= 0x40;
        }
    }

    Cache* pTextureCache = pTexture->NextCache;
    if (!pTextureCache) return;

    FxU32 texAddr = pTextureCache->texAddress;
    if (gTexMemInitialized)
    {
        GrTexInfo texInfo;
        texInfo.smallLod = GR_LOD_256;
        texInfo.largeLod = GR_LOD_256;
        texInfo.aspectRatio = GR_ASPECT_1x1;
        texInfo.format = GR_TEXFMT_P_8;
        texInfo.data = 0;
        grTexSource(GR_TMU0, texAddr, 0, &texInfo);
    }

    pTextureCache->UsedFrameNum = FrameNumber;

    float uvScale = pTextureCache->field_C;

    if (quadFlags & 0x10000)
    {
        float textureW = (float)pTexture->Width;
        float textureH = (float)pTexture->Height;
        float flt_E10830 = 0.001f;
        float v21 = pVerts[0].x + textureW;
        float v23 = pVerts[0].x + textureW - flt_E10830;
        float v24 = pVerts[0].y + textureH;

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

        pVerts[1].u = textureW;
        pVerts[1].v = 0;

        pVerts[2].u = textureW;
        pVerts[2].v = textureH;

        pVerts[3].u = 0;
        pVerts[3].v = textureH;
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
        DWORD finalDiffuse = (unsigned __int8)baseColour |
            (((unsigned __int8)baseColour | ((baseColour | 0xFFFFFF00) << 8)) << 8);
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

    GrVertex gv[4];
    for (int i = 0; i < 4; i++)
    {
        ConvertVertToGrVertex(pVerts[i], gv[i], 1.0f, pVerts[i].diff, (quadFlags & 0x8000) != 0);
    }

    grDrawTriangle(&gv[0], &gv[1], &gv[2]);
    grDrawTriangle(&gv[0], &gv[2], &gv[3]);

    gGlobals.mNumPolysDrawn += 2;
}

void CC gbh_DrawQuadClipped(int a1, int a2, int a3, int a4, int a5)
{
}

s32 CC gbh_DrawTilePart(unsigned int flags, Texture* pTexture, Vert* pData, int diffuseColour)
{
    unsigned int oldFlags = flags;

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

    struct UV { float u; float v; };
    UV uvs[4];
    for (int i = 0; i < 4; i++)
    {
        uvs[i].u = pData[i].u;
        uvs[i].v = pData[i].v;
    }

    int updated = 0;
    switch (flags & 0x60)
    {
    case 0x20:
        pData[0].u = uvs[3].u; pData[0].v = uvs[3].v;
        pData[1].u = uvs[0].u; pData[1].v = uvs[0].v;
        pData[2].u = uvs[1].u; pData[2].v = uvs[1].v;
        pData[3].u = uvs[2].u; pData[3].v = uvs[2].v;
        updated = 1;
        break;
    case 0x40:
        oldFlags = flags ^ 0x18;
        break;
    case 0x60:
        pData[0].u = uvs[1].u; pData[0].v = uvs[1].v;
        pData[1].u = uvs[2].u; pData[1].v = uvs[2].v;
        pData[2].u = uvs[3].u; pData[2].v = uvs[3].v;
        pData[3].u = uvs[0].u; pData[3].v = uvs[0].v;
        updated = 1;
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

    if (oldFlags & 8)
    {
        pData[0].u = uvs[1].u; pData[0].v = uvs[1].v;
        pData[1].u = uvs[0].u; pData[1].v = uvs[0].v;
        pData[2].u = uvs[3].u; pData[2].v = uvs[3].v;
        pData[3].u = uvs[2].u; pData[3].v = uvs[2].v;
        if (oldFlags & 0x10)
        {
            for (int i = 0; i < 4; i++)
            {
                uvs[i].u = pData[i].u;
                uvs[i].v = pData[i].v;
            }
        }
    }

    if (oldFlags & 0x10)
    {
        pData[0].u = uvs[3].u; pData[0].v = uvs[3].v;
        pData[1].u = uvs[2].u; pData[1].v = uvs[2].v;
        pData[2].u = uvs[1].u; pData[2].v = uvs[1].v;
        pData[3].u = uvs[0].u; pData[3].v = uvs[0].v;
    }

    gbh_DrawQuad(oldFlags, pTexture, pData, diffuseColour);
    return 0;
}

void CC gbh_DrawTriangle(int triFlags, Texture* pTexture, Vert* pVerts, int diffuseColour)
{
    if (pVerts[0].z <= 0.0f) return;

    SetRenderStates(triFlags);

    if (triFlags & 0x20000)
    {
        if (!gPointFilteringOn)
        {
            gPointFilteringOn = 1;
            grTexFilterMode(GR_TMU0, GR_TEXTUREFILTER_POINT_SAMPLED, GR_TEXTUREFILTER_POINT_SAMPLED);
        }
    }
    else
    {
        if (gPointFilteringOn)
        {
            gPointFilteringOn = 0;
            grTexFilterMode(GR_TMU0, GR_TEXTUREFILTER_BILINEAR, GR_TEXTUREFILTER_BILINEAR);
        }
    }

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
        if (triFlags & 0x300)
        {
            pTexture->Flags &= 0xBF;
        }
        else
        {
            pTexture->Flags |= 0x40;
        }
    }

    Cache* pTextureCache = pTexture->NextCache;
    if (!pTextureCache) return;

    FxU32 texAddr = pTextureCache->texAddress;
    if (gTexMemInitialized)
    {
        GrTexInfo texInfo;
        texInfo.smallLod = GR_LOD_256;
        texInfo.largeLod = GR_LOD_256;
        texInfo.aspectRatio = GR_ASPECT_1x1;
        texInfo.format = GR_TEXFMT_P_8;
        texInfo.data = 0;
        grTexSource(GR_TMU0, texAddr, 0, &texInfo);
    }

    float uvScale = pTextureCache->field_C;

    pVerts[0].w = pVerts[0].z;
    pVerts[1].w = pVerts[1].z;
    pVerts[2].w = pVerts[2].z;

    pVerts[0].u *= uvScale;
    pVerts[0].v *= uvScale;
    pVerts[1].u *= uvScale;
    pVerts[1].v *= uvScale;
    pVerts[2].u *= uvScale;
    pVerts[2].v *= uvScale;

    if (!(HIBYTE(triFlags) & 0x20))
    {
        DWORD finalDiffuse = (unsigned __int8)diffuseColour |
            (((unsigned __int8)diffuseColour | ((diffuseColour | 0xFFFFFF00) << 8)) << 8);
        pVerts[0].diff = finalDiffuse;
        pVerts[1].diff = finalDiffuse;
        pVerts[2].diff = finalDiffuse;
    }

    pVerts[0].spec = 0;
    pVerts[1].spec = 0;
    pVerts[2].spec = 0;

    if (HIBYTE(triFlags) & 0x80 && gfAmbient != 255.0f)
    {
        LightVerts_new(3, pVerts, 0, diffuseColour);
    }

    GrVertex gv[3];
    for (int i = 0; i < 3; i++)
    {
        ConvertVertToGrVertex(pVerts[i], gv[i], 1.0f, pVerts[i].diff, (triFlags & 0x8000) != 0);
    }

    grDrawTriangle(&gv[0], &gv[1], &gv[2]);

    gGlobals.mNumPolysDrawn++;
}

void CC gbh_EndLevel()
{
}

double CC gbh_EndScene()
{
    if (gbSurfaceIsFreed == 1)
    {
        (*gVideoDriver->initDLL->pVid_GetSurface)(gVideoDriver);
    }

    grBufferSwap(1);

    return 0.0;
}

int CC gbh_FreeImageTable()
{
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
                gImageTable[idx].Loaded = FALSE;
            }
        }
    }
    free(gImageTable);
    gImageTable = 0;
    return 0;
}

void CC gbh_FreePalette(int a1)
{
}

void CC gbh_FreeTexture(Texture* pTexture)
{
    TextureCache(pTexture);
    free(pTexture);
}

u32* CC gbh_GetGlobals()
{
    return (u32*)&gGlobals;
}

int CC gbh_GetUsedCache(int cacheIdx)
{
    int usedCacheCount = 0;
    Cache* pCache = gGlobals.CacheArray[cacheIdx];
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

s32 CC gbh_Init(int a1)
{
    int result = Init();
    if (!result)
    {
        gbh_SetColourDepth();
    }
    return result;
}

u32 CC gbh_InitDLL(Video* pVideoDriver)
{
    gVideoDriver = pVideoDriver;

    pOldCloseScreen = *pVideoDriver->initDLL->pVid_CloseScreen;
    pOldSetMode = *pVideoDriver->initDLL->pVid_SetMode;

    *pVideoDriver->initDLL->pVid_CloseScreen = gbh_CloseScreen;
    *pVideoDriver->initDLL->pVid_SetMode = gbh_SetMode;

    return 1;
}

signed int CC gbh_InitImageTable(int tableSize)
{
    gImageTableCount = tableSize;
    gImageTable = (ImageTableEntry*)malloc(tableSize * sizeof(ImageTableEntry));
    if (!gImageTable) return -1;

    memset(gImageTable, 0, tableSize * sizeof(ImageTableEntry));
    return 0;
}

signed int CC gbh_LoadImage(Image* pImage)
{
    return 0;
}

Texture* CC gbh_LockTexture(Texture* pTexture)
{
    pTexture->pLockedPixels = pTexture->pOriginalPixelData;
    pTexture->Flags |= 1;
    pTexture->PalSize = 256;
    return TextureCache(pTexture);
}

void CC gbh_Plot(int a1, int a2, int a3, int a4)
{
}

int CC gbh_PrintBitmap(int a1, int a2)
{
    return 0;
}

unsigned int CC gbh_RegisterPalette(int a1, DWORD* a2)
{
    pals[a1].mPOriginalData = a2;

    if (a2)
    {
        WORD* pConv = (WORD*)malloc(256 * sizeof(WORD));
        for (int i = 0; i < 256; i++)
        {
            pConv[i] = (WORD)Convert32To1555(a2[i]);
        }
        pals[a1].mPData = pConv;
        pals[a1].mbLoaded = 1;
    }
    else
    {
        pals[a1].mPData = 0;
        pals[a1].mbLoaded = 0;
    }

    return (unsigned int)&pals[a1];
}

Texture* CC gbh_RegisterTexture(__int16 width, __int16 height, BYTE* pData, int pal_idx, char a5)
{
    Texture* result = (Texture*)malloc(sizeof(Texture));
    if (!result) return 0;

    memset(result, 0, sizeof(Texture));

    result->ID = (unsigned short)gTextureId++;
    result->field_2 = 0;
    result->PalIsTrans = LOBYTE(pals[pal_idx].mPData);
    result->Width = (unsigned short)width;
    result->PalSize = 0;
    result->pLockedPixels = 0;
    result->field_C = 0;
    result->field_D = 0;
    result->Height = (unsigned short)height;
    result->PalIsValid = (u8)pals[pal_idx].mbLoaded;
    result->Flags = 0;
    result->pOriginalPixelData = pData;
    result->pPaltData = pals[pal_idx].mPData;
    result->NextCache = 0;

    return result;
}

void CC gbh_ResetLights()
{
    NumLights = 0;
}

void CC gbh_SetAmbient(float ambient)
{
    gfAmbient = ambient * 255.0f;
}

int CC gbh_SetCamera(float a1, float a2, float a3, float a4)
{
    return 0;
}

int CC gbh_SetColourDepth()
{
    return 0;
}

float CC gbh_SetWindow(float left, float top, float right, float bottom)
{
    gWindowLeft = left;
    gWindowRight = right;
    gWindowTop = top;
    gWindowBottom = bottom;
    return bottom;
}

Texture* CC gbh_UnlockTexture(Texture* pTexture)
{
    pTexture->PalSize = 0;
    pTexture->pLockedPixels = 0;
    pTexture->Flags &= 0xFE;
    return pTexture;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        memset(&gGlobals, 0, sizeof(gGlobals));
        gTextureId = 1;
        NumLights = 0;
        gfAmbient = 255.0f;
        FrameNumber = 0;
        gbSurfaceIsFreed = 0;
        gWindowActive = 0;
        gGlideInitDone = 0;
        gTexMemInitialized = 0;
        gRenderStateCache = 0;
        gPointFilteringOn = 0;
        gVideoDriver = 0;
        pOldCloseScreen = 0;
        pOldSetMode = 0;
        gImageTable = 0;
        gImageTableCount = 0;

        gGlobals.gCacheUnknown[0] = 20;
        gGlobals.gCacheUnknown[1] = 20;
        gGlobals.gCacheUnknown[2] = 20;
        gGlobals.gCacheUnknown[3] = 20;
        gGlobals.gCacheUnknown[4] = 20;
        gGlobals.gCacheUnknown[5] = 20;
        gGlobals.gCacheUnknown[6] = 16;
        gGlobals.gCacheUnknown[7] = 16;
        gGlobals.gCacheUnknown[8] = 8;
        gGlobals.gCacheUnknown[9] = 8;
        gGlobals.gCacheUnknown[10] = 4;
        gGlobals.gCacheUnknown[11] = 4;
    }
    return TRUE;
}
