#ifndef __GLIDE3_H__
#define __GLIDE3_H__

#include <windows.h>
#include <stdint.h>

typedef uint8_t   FxU8;
typedef int8_t    FxI8;
typedef uint16_t  FxU16;
typedef int16_t   FxI16;
typedef uint32_t  FxU32;
typedef int32_t   FxI32;
typedef uint64_t  FxU64;
typedef int64_t   FxI64;
typedef int       FxBool;
typedef float     FxFloat;
typedef double    FxDouble;
typedef uintptr_t FxU;
typedef intptr_t  FxI;

#define FXTRUE    1
#define FXFALSE   0
#define FXBIT(i)  (1L << (i))

#define FX_ENTRY extern
#define FX_CALL  __stdcall

#define GLIDE_NUM_TMU 2

typedef FxI32 GrScreenRefresh_t;
#define GR_REFRESH_60Hz   0x0
#define GR_REFRESH_70Hz   0x1
#define GR_REFRESH_72Hz   0x2
#define GR_REFRESH_75Hz   0x3
#define GR_REFRESH_80Hz   0x4
#define GR_REFRESH_90Hz   0x5
#define GR_REFRESH_100Hz  0x6
#define GR_REFRESH_85Hz   0x7
#define GR_REFRESH_120Hz  0x8
#define GR_REFRESH_NONE   0xff

typedef FxI32 GrScreenResolution_t;
#define GR_RESOLUTION_320x200   0x0
#define GR_RESOLUTION_320x240   0x1
#define GR_RESOLUTION_400x256   0x2
#define GR_RESOLUTION_512x384   0x3
#define GR_RESOLUTION_640x200   0x4
#define GR_RESOLUTION_640x350   0x5
#define GR_RESOLUTION_640x400   0x6
#define GR_RESOLUTION_640x480   0x7
#define GR_RESOLUTION_800x600   0x8
#define GR_RESOLUTION_960x720   0x9
#define GR_RESOLUTION_856x480   0xa
#define GR_RESOLUTION_512x256   0xb
#define GR_RESOLUTION_1024x768  0xC
#define GR_RESOLUTION_1280x1024 0xD
#define GR_RESOLUTION_1600x1200 0xE
#define GR_RESOLUTION_400x300   0xF
#define GR_RESOLUTION_NONE      0xff

typedef FxU32 GrColor_t;
typedef FxU8  GrAlpha_t;
typedef FxU32 GrMipMapId_t;
typedef FxU8  GrFog_t;

#define MAX_NUM_SST            4
#define GR_NULL_MIPMAP_HANDLE  ((GrMipMapId_t) -1)
#define GR_ZDEPTHVALUE_NEAREST  0xFFFF
#define GR_ZDEPTHVALUE_FARTHEST 0x0000

typedef FxI32 GrChipID_t;
#define GR_TMU0  0x0
#define GR_TMU1  0x1
#define GR_TMU2  0x2
#define GR_FBI   0x3

typedef FxI32 GrCombineFunction_t;
#define GR_COMBINE_FUNCTION_ZERO        0x0
#define GR_COMBINE_FUNCTION_NONE        GR_COMBINE_FUNCTION_ZERO
#define GR_COMBINE_FUNCTION_LOCAL       0x1
#define GR_COMBINE_FUNCTION_LOCAL_ALPHA 0x2
#define GR_COMBINE_FUNCTION_SCALE_OTHER 0x3
#define GR_COMBINE_FUNCTION_BLEND_OTHER GR_COMBINE_FUNCTION_SCALE_OTHER
#define GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL 0x4
#define GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL_ALPHA 0x5
#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL 0x6
#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL 0x7
#define GR_COMBINE_FUNCTION_BLEND GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL
#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL_ALPHA 0x8
#define GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL 0x9
#define GR_COMBINE_FUNCTION_BLEND_LOCAL GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL
#define GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL_ALPHA 0x10

typedef FxI32 GrCombineFactor_t;
#define GR_COMBINE_FACTOR_ZERO          0x0
#define GR_COMBINE_FACTOR_NONE          GR_COMBINE_FACTOR_ZERO
#define GR_COMBINE_FACTOR_LOCAL         0x1
#define GR_COMBINE_FACTOR_OTHER_ALPHA   0x2
#define GR_COMBINE_FACTOR_LOCAL_ALPHA   0x3
#define GR_COMBINE_FACTOR_TEXTURE_ALPHA 0x4
#define GR_COMBINE_FACTOR_TEXTURE_RGB   0x5
#define GR_COMBINE_FACTOR_DETAIL_FACTOR GR_COMBINE_FACTOR_TEXTURE_ALPHA
#define GR_COMBINE_FACTOR_LOD_FRACTION  0x5
#define GR_COMBINE_FACTOR_ONE           0x8
#define GR_COMBINE_FACTOR_ONE_MINUS_LOCAL 0x9
#define GR_COMBINE_FACTOR_ONE_MINUS_OTHER_ALPHA 0xa
#define GR_COMBINE_FACTOR_ONE_MINUS_LOCAL_ALPHA 0xb
#define GR_COMBINE_FACTOR_ONE_MINUS_TEXTURE_ALPHA 0xc
#define GR_COMBINE_FACTOR_ONE_MINUS_DETAIL_FACTOR GR_COMBINE_FACTOR_ONE_MINUS_TEXTURE_ALPHA
#define GR_COMBINE_FACTOR_ONE_MINUS_LOD_FRACTION 0xd

typedef FxI32 GrCombineLocal_t;
#define GR_COMBINE_LOCAL_ITERATED 0x0
#define GR_COMBINE_LOCAL_CONSTANT 0x1
#define GR_COMBINE_LOCAL_NONE GR_COMBINE_LOCAL_CONSTANT
#define GR_COMBINE_LOCAL_DEPTH  0x2

typedef FxI32 GrCombineOther_t;
#define GR_COMBINE_OTHER_ITERATED 0x0
#define GR_COMBINE_OTHER_TEXTURE 0x1
#define GR_COMBINE_OTHER_CONSTANT 0x2
#define GR_COMBINE_OTHER_NONE GR_COMBINE_OTHER_CONSTANT

typedef FxI32 GrAlphaBlendFnc_t;
#define GR_BLEND_ZERO 0x0
#define GR_BLEND_SRC_ALPHA 0x1
#define GR_BLEND_SRC_COLOR 0x2
#define GR_BLEND_DST_COLOR GR_BLEND_SRC_COLOR
#define GR_BLEND_DST_ALPHA 0x3
#define GR_BLEND_ONE 0x4
#define GR_BLEND_ONE_MINUS_SRC_ALPHA 0x5
#define GR_BLEND_ONE_MINUS_SRC_COLOR 0x6
#define GR_BLEND_ONE_MINUS_DST_COLOR GR_BLEND_ONE_MINUS_SRC_COLOR
#define GR_BLEND_ONE_MINUS_DST_ALPHA 0x7
#define GR_BLEND_ALPHA_SATURATE 0xf

typedef FxI32 GrAspectRatio_t;
#define GR_ASPECT_8x1 0x0
#define GR_ASPECT_4x1 0x1
#define GR_ASPECT_2x1 0x2
#define GR_ASPECT_1x1 0x3
#define GR_ASPECT_1x2 0x4
#define GR_ASPECT_1x4 0x5
#define GR_ASPECT_1x8 0x6

typedef FxI32 GrBuffer_t;
#define GR_BUFFER_FRONTBUFFER   0x0
#define GR_BUFFER_BACKBUFFER    0x1
#define GR_BUFFER_AUXBUFFER     0x2
#define GR_BUFFER_DEPTHBUFFER   0x3
#define GR_BUFFER_ALPHABUFFER   0x4
#define GR_BUFFER_TRIPLEBUFFER  0x5

typedef FxI32 GrCmpFnc_t;
#define GR_CMP_NEVER    0x0
#define GR_CMP_LESS     0x1
#define GR_CMP_EQUAL    0x2
#define GR_CMP_LEQUAL   0x3
#define GR_CMP_GREATER  0x4
#define GR_CMP_NOTEQUAL 0x5
#define GR_CMP_GEQUAL   0x6
#define GR_CMP_ALWAYS   0x7

typedef FxI32 GrColorFormat_t;
#define GR_COLORFORMAT_ARGB 0x0
#define GR_COLORFORMAT_ABGR 0x1
#define GR_COLORFORMAT_RGBA 0x2
#define GR_COLORFORMAT_BGRA 0x3

typedef FxI32 GrCullMode_t;
#define GR_CULL_DISABLE  0x0
#define GR_CULL_NEGATIVE 0x1
#define GR_CULL_POSITIVE 0x2

typedef FxI32 GrDepthBufferMode_t;
#define GR_DEPTHBUFFER_DISABLE                0x0
#define GR_DEPTHBUFFER_ZBUFFER                0x1
#define GR_DEPTHBUFFER_WBUFFER                0x2
#define GR_DEPTHBUFFER_ZBUFFER_COMPARE_TO_BIAS 0x3
#define GR_DEPTHBUFFER_WBUFFER_COMPARE_TO_BIAS 0x4

typedef FxI32 GrDitherMode_t;
#define GR_DITHER_DISABLE 0x0
#define GR_DITHER_2x2     0x1
#define GR_DITHER_4x4     0x2

typedef FxI32 GrFogMode_t;
#define GR_FOG_DISABLE             0x0
#define GR_FOG_WITH_ITERATED_ALPHA 0x1
#define GR_FOG_WITH_TABLE          0x2
#define GR_FOG_WITH_ITERATED_Z     0x3
#define GR_FOG_MULT2               0x100
#define GR_FOG_ADD2                0x200

typedef FxU32 GrLock_t;
#define GR_LFB_READ_ONLY  0x00
#define GR_LFB_WRITE_ONLY 0x01
#define GR_LFB_IDLE       0x00
#define GR_LFB_NOIDLE     0x10

typedef FxI32 GrLfbWriteMode_t;
#define GR_LFBWRITEMODE_565  0x0
#define GR_LFBWRITEMODE_555  0x1
#define GR_LFBWRITEMODE_1555 0x2
#define GR_LFBWRITEMODE_888  0x4
#define GR_LFBWRITEMODE_8888 0x5
#define GR_LFBWRITEMODE_ANY  0xFF

typedef FxI32 GrOriginLocation_t;
#define GR_ORIGIN_UPPER_LEFT 0x0
#define GR_ORIGIN_LOWER_LEFT 0x1
#define GR_ORIGIN_ANY        0xFF

typedef struct {
    int                size;
    void               *lfbPtr;
    FxU32              strideInBytes;
    GrLfbWriteMode_t   writeMode;
    GrOriginLocation_t origin;
} GrLfbInfo_t;

typedef FxI32 GrLOD_t;
#define GR_LOD_256 0x0
#define GR_LOD_128 0x1
#define GR_LOD_64  0x2
#define GR_LOD_32  0x3
#define GR_LOD_16  0x4
#define GR_LOD_8   0x5
#define GR_LOD_4   0x6
#define GR_LOD_2   0x7
#define GR_LOD_1   0x8

typedef FxI32 GrMipMapMode_t;
#define GR_MIPMAP_DISABLE         0x0
#define GR_MIPMAP_NEAREST         0x1
#define GR_MIPMAP_NEAREST_DITHER  0x2

typedef FxI32 GrTextureClampMode_t;
#define GR_TEXTURECLAMP_WRAP  0x0
#define GR_TEXTURECLAMP_CLAMP 0x1

typedef FxI32 GrTextureFilterMode_t;
#define GR_TEXTUREFILTER_POINT_SAMPLED 0x0
#define GR_TEXTUREFILTER_BILINEAR      0x1

typedef FxI32 GrTextureFormat_t;
#define GR_TEXFMT_8BIT        0x0
#define GR_TEXFMT_RGB_332     GR_TEXFMT_8BIT
#define GR_TEXFMT_YIQ_422     0x1
#define GR_TEXFMT_ALPHA_8     0x2
#define GR_TEXFMT_INTENSITY_8 0x3
#define GR_TEXFMT_ALPHA_INTENSITY_44 0x4
#define GR_TEXFMT_P_8         0x5
#define GR_TEXFMT_16BIT       0x8
#define GR_TEXFMT_ARGB_8332   GR_TEXFMT_16BIT
#define GR_TEXFMT_AYIQ_8422   0x9
#define GR_TEXFMT_RGB_565     0xa
#define GR_TEXFMT_ARGB_1555   0xb
#define GR_TEXFMT_ARGB_4444   0xc
#define GR_TEXFMT_ALPHA_INTENSITY_88 0xd
#define GR_TEXFMT_AP_88       0xe
#define GR_TEXFMT_BGRA_8888   0x10

typedef FxU32 GrTexTable_t;
#define GR_TEXTABLE_NCC0    0x0
#define GR_TEXTABLE_NCC1    0x1
#define GR_TEXTABLE_PALETTE 0x2

typedef FxU32 GrNCCTable_t;
#define GR_NCCTABLE_NCC0 0x0
#define GR_NCCTABLE_NCC1 0x1

typedef FxU32 GrEnableMode_t;
#define GR_MODE_DISABLE 0x0
#define GR_MODE_ENABLE  0x1

typedef FxU32 GrCoordinateSpaceMode_t;
#define GR_WINDOW_COORDS 0x00
#define GR_CLIP_COORDS   0x01

typedef struct {
    GrLOD_t           smallLod;
    GrLOD_t           largeLod;
    GrAspectRatio_t   aspectRatio;
    GrTextureFormat_t format;
    void              *data;
} GrTexInfo;

typedef struct {
    float sow;
    float tow;
    float oow;
} GrTmuVertex;

typedef struct {
    float x, y;
    float ooz;
    float oow;
    float r, g, b, a;
    float z;
    GrTmuVertex tmuvtx[GLIDE_NUM_TMU];
} GrVertex;

typedef FxU32 GrLfbSrcFmt_t;
#define GR_LFB_SRC_FMT_565   0x00
#define GR_LFB_SRC_FMT_555   0x01
#define GR_LFB_SRC_FMT_1555  0x02
#define GR_LFB_SRC_FMT_888   0x04
#define GR_LFB_SRC_FMT_8888  0x05
#define GR_LFB_SRC_FMT_RLE16 0x80

typedef FxU32 GrHint_t;
#define GR_HINTTYPE_MIN           0
#define GR_HINT_STWHINT           0
#define GR_HINT_FIFOCHECKHINT     1
#define GR_HINT_FPUPRECISION      2

typedef FxU32 GrControl_t;
#define GR_CONTROL_ACTIVATE   0x1
#define GR_CONTROL_DEACTIVATE 0x2
#define GR_CONTROL_RESIZE     0x3
#define GR_CONTROL_MOVE       0x4

typedef int GrSstType;
#define GR_SSTTYPE_VOODOO   0
#define GR_SSTTYPE_SST96    1
#define GR_SSTTYPE_AT3D     2
#define GR_SSTTYPE_Voodoo2  3

typedef struct GrTMUConfig_St {
    int tmuRev;
    int tmuRam;
} GrTMUConfig_t;

typedef struct GrVoodooConfig_St {
    int          fbRam;
    int          fbiRev;
    int          nTexelfx;
    FxBool       sliDetect;
    GrTMUConfig_t tmuConfig[GLIDE_NUM_TMU];
} GrVoodooConfig_t;

typedef GrVoodooConfig_t GrVoodoo2Config_t;

typedef struct {
    int num_sst;
    struct {
        GrSstType type;
        union {
            GrVoodooConfig_t  VoodooConfig;
        } sstBoard;
    } SSTs[MAX_NUM_SST];
} GrHwConfiguration;

typedef struct {
    FxU32 pixelsIn;
    FxU32 chromaFail;
    FxU32 zFuncFail;
    FxU32 aFuncFail;
    FxU32 pixelsOut;
} GrSstPerfStats_t;

#define GR_STATE_PAD_SIZE 312

typedef struct _GrState_s {
    char pad[GR_STATE_PAD_SIZE];
} GrState;

typedef void (*GrErrorCallbackFnc_t)(const char *string, FxBool fatal);

#ifdef __cplusplus
extern "C" {
#endif

FX_ENTRY void FX_CALL grGlideInit(void);
FX_ENTRY void FX_CALL grGlideShutdown(void);
FX_ENTRY void FX_CALL grGlideGetState(GrState *state);
FX_ENTRY void FX_CALL grGlideSetState(const GrState *state);

FX_ENTRY FxBool FX_CALL grSstWinOpen(FxU hWnd, GrScreenResolution_t screen_resolution, GrScreenRefresh_t refresh_rate, GrColorFormat_t color_format, GrOriginLocation_t origin_location, int nColBuffers, int nAuxBuffers);
FX_ENTRY void FX_CALL grSstWinClose(FxU32 context);
FX_ENTRY FxBool FX_CALL grSstControl(FxU32 code);
FX_ENTRY void FX_CALL grSstOrigin(GrOriginLocation_t origin);
FX_ENTRY void FX_CALL grSstSelect(int which_sst);

FX_ENTRY void FX_CALL grDrawTriangle(void *a, void *b, void *c);
FX_ENTRY void FX_CALL grDrawPoint(void *pt);
FX_ENTRY void FX_CALL grDrawLine(void *v1, void *v2);

FX_ENTRY void FX_CALL grBufferClear(GrColor_t color, GrAlpha_t alpha, FxU16 depth);
FX_ENTRY void FX_CALL grBufferSwap(int swap_interval);
FX_ENTRY void FX_CALL grRenderBuffer(GrBuffer_t buffer);

FX_ENTRY void FX_CALL grAlphaBlendFunction(GrAlphaBlendFnc_t rgb_sf, GrAlphaBlendFnc_t rgb_df, GrAlphaBlendFnc_t alpha_sf, GrAlphaBlendFnc_t alpha_df);
FX_ENTRY void FX_CALL grAlphaCombine(GrCombineFunction_t function, GrCombineFactor_t factor, GrCombineLocal_t local, GrCombineOther_t other, FxBool invert);
FX_ENTRY void FX_CALL grAlphaTestFunction(GrCmpFnc_t function);
FX_ENTRY void FX_CALL grAlphaTestReferenceValue(GrAlpha_t value);
FX_ENTRY void FX_CALL grClipWindow(FxU32 minx, FxU32 miny, FxU32 maxx, FxU32 maxy);
FX_ENTRY void FX_CALL grColorCombine(GrCombineFunction_t function, GrCombineFactor_t factor, GrCombineLocal_t local, GrCombineOther_t other, FxBool invert);
FX_ENTRY void FX_CALL grColorMask(FxBool rgb, FxBool a);
FX_ENTRY void FX_CALL grCullMode(GrCullMode_t mode);
FX_ENTRY void FX_CALL grConstantColorValue(GrColor_t value);
FX_ENTRY void FX_CALL grConstantColorValue4(float a, float r, float g, float b);
FX_ENTRY void FX_CALL grDisableAllEffects(void);
FX_ENTRY void FX_CALL grDitherMode(GrDitherMode_t mode);
FX_ENTRY void FX_CALL grFogMode(GrFogMode_t mode);
FX_ENTRY void FX_CALL grFogColorValue(GrColor_t fogcolor);
FX_ENTRY void FX_CALL grGammaCorrectionValue(float value);
FX_ENTRY void FX_CALL grSplash(float x, float y, float width, float height, FxU32 frame);

FX_ENTRY void FX_CALL grTexSource(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo *info);
FX_ENTRY void FX_CALL grTexClampMode(GrChipID_t tmu, GrTextureClampMode_t s_clampmode, GrTextureClampMode_t t_clampmode);
FX_ENTRY void FX_CALL grTexCombine(GrChipID_t tmu, GrCombineFunction_t rgb_function, GrCombineFactor_t rgb_factor, GrCombineFunction_t alpha_function, GrCombineFactor_t alpha_factor, FxBool rgb_invert, FxBool alpha_invert);
FX_ENTRY void FX_CALL grTexFilterMode(GrChipID_t tmu, GrTextureFilterMode_t minfilter_mode, GrTextureFilterMode_t magfilter_mode);
FX_ENTRY void FX_CALL grTexLodBiasValue(GrChipID_t tmu, float bias);
FX_ENTRY void FX_CALL grTexDownloadMipMap(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo *info);
FX_ENTRY void FX_CALL grTexDownloadMipMapLevel(GrChipID_t tmu, FxU32 startAddress, GrLOD_t thisLod, GrLOD_t largeLod, GrAspectRatio_t aspectRatio, GrTextureFormat_t format, FxU32 evenOdd, void *data);
FX_ENTRY void FX_CALL grTexDownloadTable(FxU32, FxU32 *);
FX_ENTRY void FX_CALL grTexMipMapMode(GrChipID_t tmu, GrMipMapMode_t mode, FxBool lodBlend);
FX_ENTRY FxU32 FX_CALL grTexMinAddress(GrChipID_t tmu);
FX_ENTRY FxU32 FX_CALL grTexMaxAddress(GrChipID_t tmu);
FX_ENTRY FxU32 FX_CALL grTexTextureMemRequired(FxU32 evenOdd, GrTexInfo *info);

FX_ENTRY FxBool FX_CALL grLfbLock(GrLock_t type, GrBuffer_t buffer, GrLfbWriteMode_t writeMode, GrOriginLocation_t origin, FxBool pixelPipeline, GrLfbInfo_t *info);
FX_ENTRY FxBool FX_CALL grLfbUnlock(GrLock_t type, GrBuffer_t buffer);
FX_ENTRY FxBool FX_CALL grLfbWriteRegion(GrBuffer_t dst_buffer, FxU32 dst_x, FxU32 dst_y, GrLfbSrcFmt_t src_format, FxU32 src_width, FxU32 src_height, FxBool pixelPipeline, FxI32 src_stride, void *src_data);
FX_ENTRY FxBool FX_CALL grLfbReadRegion(GrBuffer_t src_buffer, FxU32 src_x, FxU32 src_y, FxU32 src_width, FxU32 src_height, FxU32 dst_stride, void *dst_data);

FX_ENTRY void FX_CALL grDepthBufferFunction(GrCmpFnc_t function);
FX_ENTRY void FX_CALL grDepthBufferMode(GrDepthBufferMode_t mode);
FX_ENTRY void FX_CALL grDepthMask(FxBool mask);
FX_ENTRY void FX_CALL grDepthBiasLevel(FxI16 level);

FX_ENTRY void FX_CALL grErrorSetCallback(GrErrorCallbackFnc_t fnc);
FX_ENTRY void FX_CALL grFinish(void);
FX_ENTRY void FX_CALL grFlush(void);

FX_ENTRY FxBool FX_CALL grGet(FxU32 pname, FxU32 plength, FxI32 *params);
FX_ENTRY const char * FX_CALL grGetString(FxU32 pname);
FX_ENTRY FxBool FX_CALL grReset(FxU32 what);
FX_ENTRY void FX_CALL grEnable(GrEnableMode_t mode);
FX_ENTRY void FX_CALL grDisable(GrEnableMode_t mode);
FX_ENTRY void FX_CALL grCoordinateSpace(GrCoordinateSpaceMode_t mode);
FX_ENTRY void FX_CALL grViewport(FxI32 x, FxI32 y, FxI32 width, FxI32 height);
FX_ENTRY void FX_CALL grDepthRange(FxFloat n, FxFloat f);

FX_ENTRY void FX_CALL grVertexLayout(FxU32 param, FxI32 offset, FxU32 mode);
FX_ENTRY void FX_CALL grDrawVertexArray(FxU32 mode, FxU32 Count, void *pointers);
FX_ENTRY void FX_CALL grDrawVertexArrayLinear(FxU32 mode, FxU32 Count, void *pointers, FxU32 stride);

FX_ENTRY void FX_CALL grHints(GrHint_t hintType, FxU32 hintMask);

#ifdef __cplusplus
}
#endif

#endif
