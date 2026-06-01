#ifndef _TGA_H_
#define _TGA_H_

#include <windows.h>
#include <cstdio>

#pragma pack(push, 1)
typedef struct {
    BYTE  id_length;
    BYTE  color_map_type;
    BYTE  image_type;
    WORD  color_map_start;
    WORD  color_map_length;
    BYTE  color_map_bpp;
    WORD  x_origin;
    WORD  y_origin;
    WORD  width;
    WORD  height;
    BYTE  bpp;
    BYTE  descriptor;
} TGAHeader;
#pragma pack(pop)

enum TGAImageType {
    TGA_NODATA           = 0,
    TGA_COLORMAP         = 1,
    TGA_TRUECOLOR        = 2,
    TGA_GRAYSCALE        = 3,
    TGA_RLE_COLORMAP     = 9,
    TGA_RLE_TRUECOLOR    = 10,
    TGA_RLE_GRAYSCALE    = 11
};

class cTGA
{
  protected:
    BYTE  *m_Data;
    BYTE  *m_Palette;
    long   m_Width;
    long   m_Height;
    BYTE   m_BPP;
    BYTE   m_ImageType;
    DWORD  m_DataSize;

    BOOL LoadUncompressed(FILE *fp, long bytes_per_pixel);
    BOOL LoadRLE(FILE *fp, long bytes_per_pixel);
    BOOL LoadColormap(FILE *fp, WORD color_map_start, WORD color_map_length, BYTE color_map_bpp, BOOL rle);

  public:
    cTGA();
    ~cTGA();

    BOOL  Load(char *Filename);
    BOOL  Save(char *Filename);

    void  Free();

    long  GetWidth();
    long  GetHeight();
    BYTE  GetBPP();
    BYTE *GetData();
    BYTE *GetPalette();
    BOOL  IsCompressed();
    BOOL  FlipVertical();
    BOOL  FlipHorizontal();
    BOOL  ConvertTo32();
};

#endif
