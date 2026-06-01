#include "TGA.h"
#include <cstring>

cTGA::cTGA()
{
  m_Data      = NULL;
  m_Palette   = NULL;
  m_Width     = 0;
  m_Height    = 0;
  m_BPP       = 0;
  m_ImageType = 0;
  m_DataSize  = 0;
}

cTGA::~cTGA()
{
  Free();
}

void cTGA::Free()
{
  delete[] m_Data;
  delete[] m_Palette;
  m_Data      = NULL;
  m_Palette   = NULL;
  m_Width     = 0;
  m_Height    = 0;
  m_BPP       = 0;
  m_ImageType = 0;
  m_DataSize  = 0;
}

long cTGA::GetWidth()
{
  return m_Width;
}

long cTGA::GetHeight()
{
  return m_Height;
}

BYTE cTGA::GetBPP()
{
  return m_BPP;
}

BYTE *cTGA::GetData()
{
  return m_Data;
}

BYTE *cTGA::GetPalette()
{
  return m_Palette;
}

BOOL cTGA::IsCompressed()
{
  return (m_ImageType == TGA_RLE_TRUECOLOR ||
          m_ImageType == TGA_RLE_COLORMAP ||
          m_ImageType == TGA_RLE_GRAYSCALE);
}

BOOL cTGA::Load(char *Filename)
{
  FILE *fp;
  TGAHeader header;

  Free();

  fp = fopen(Filename, "rb");
  if (fp == NULL)
    return FALSE;

  if (fread(&header, sizeof(TGAHeader), 1, fp) != 1) {
    fclose(fp);
    return FALSE;
  }

  m_Width     = header.width;
  m_Height    = header.height;
  m_BPP       = header.bpp;
  m_ImageType = header.image_type;

  if (header.id_length > 0)
    fseek(fp, header.id_length, SEEK_CUR);

  switch (header.image_type) {
    case TGA_TRUECOLOR:
      if (!LoadUncompressed(fp, header.bpp / 8)) {
        fclose(fp);
        return FALSE;
      }
      break;

    case TGA_RLE_TRUECOLOR:
      if (!LoadRLE(fp, header.bpp / 8)) {
        fclose(fp);
        return FALSE;
      }
      break;

    case TGA_COLORMAP:
      if (!LoadColormap(fp, header.color_map_start, header.color_map_length, header.color_map_bpp, FALSE)) {
        fclose(fp);
        return FALSE;
      }
      break;

    case TGA_RLE_COLORMAP:
      if (!LoadColormap(fp, header.color_map_start, header.color_map_length, header.color_map_bpp, TRUE)) {
        fclose(fp);
        return FALSE;
      }
      break;

    case TGA_GRAYSCALE:
    case TGA_RLE_GRAYSCALE:
      m_BPP = 8;
      m_DataSize = m_Width * m_Height;
      m_Data = new BYTE[m_DataSize];
      if (m_Data == NULL) {
        fclose(fp);
        return FALSE;
      }
      if (header.image_type == TGA_RLE_GRAYSCALE) {
        long pixels = m_Width * m_Height;
        long index = 0;
        BYTE packet, value, count;
        while (index < pixels) {
          if (fread(&packet, 1, 1, fp) != 1) {
            fclose(fp);
            return FALSE;
          }
          count = (packet & 0x7F) + 1;
          if (packet & 0x80) {
            if (fread(&value, 1, 1, fp) != 1) {
              fclose(fp);
              return FALSE;
            }
            for (BYTE i = 0; i < count && index < pixels; i++)
              m_Data[index++] = value;
          } else {
            if (fread(m_Data + index, 1, count, fp) != count) {
              fclose(fp);
              return FALSE;
            }
            index += count;
          }
        }
      } else {
        if (fread(m_Data, 1, m_DataSize, fp) != m_DataSize) {
          fclose(fp);
          return FALSE;
        }
      }
      break;

    default:
      fclose(fp);
      return FALSE;
  }

  fclose(fp);

  if (!(header.descriptor & 0x20))
    FlipVertical();

  return TRUE;
}

BOOL cTGA::LoadUncompressed(FILE *fp, long bytes_per_pixel)
{
  m_DataSize = m_Width * m_Height * bytes_per_pixel;
  m_Data = new BYTE[m_DataSize];
  if (m_Data == NULL)
    return FALSE;

  if (fread(m_Data, 1, m_DataSize, fp) != (size_t)m_DataSize)
    return FALSE;

  for (DWORD i = 0; i < m_DataSize; i += bytes_per_pixel)
  {
    BYTE temp = m_Data[i];
    m_Data[i] = m_Data[i + 2];
    m_Data[i + 2] = temp;
  }

  return TRUE;
}

BOOL cTGA::LoadRLE(FILE *fp, long bytes_per_pixel)
{
  long pixels = m_Width * m_Height;
  long index = 0;

  m_DataSize = pixels * bytes_per_pixel;
  m_Data = new BYTE[m_DataSize];
  if (m_Data == NULL)
    return FALSE;

  BYTE packet[4];
  BYTE pixel[4];
  BYTE count;

  while (index < pixels) {
    if (fread(packet, 1, 1, fp) != 1)
      return FALSE;

    count = (packet[0] & 0x7F) + 1;

    if (packet[0] & 0x80) {
      if (fread(pixel, 1, bytes_per_pixel, fp) != (size_t)bytes_per_pixel)
        return FALSE;

      for (BYTE i = 0; i < count && index < pixels; i++) {
        m_Data[index * bytes_per_pixel + 0] = pixel[2];
        m_Data[index * bytes_per_pixel + 1] = pixel[1];
        m_Data[index * bytes_per_pixel + 2] = pixel[0];
        if (bytes_per_pixel == 4)
          m_Data[index * bytes_per_pixel + 3] = pixel[3];
        index++;
      }
    } else {
      for (BYTE i = 0; i < count && index < pixels; i++) {
        if (fread(pixel, 1, bytes_per_pixel, fp) != (size_t)bytes_per_pixel)
          return FALSE;
        m_Data[index * bytes_per_pixel + 0] = pixel[2];
        m_Data[index * bytes_per_pixel + 1] = pixel[1];
        m_Data[index * bytes_per_pixel + 2] = pixel[0];
        if (bytes_per_pixel == 4)
          m_Data[index * bytes_per_pixel + 3] = pixel[3];
        index++;
      }
    }
  }

  return TRUE;
}

BOOL cTGA::LoadColormap(FILE *fp, WORD color_map_start, WORD color_map_length, BYTE color_map_bpp, BOOL rle)
{
  long palette_bytes = color_map_length * (color_map_bpp / 8);
  m_Palette = new BYTE[palette_bytes];
  if (m_Palette == NULL)
    return FALSE;

  fseek(fp, color_map_start * (color_map_bpp / 8), SEEK_CUR);

  if (fread(m_Palette, 1, palette_bytes, fp) != (size_t)palette_bytes)
    return FALSE;

  m_BPP = 8;
  m_DataSize = m_Width * m_Height;
  m_Data = new BYTE[m_DataSize];
  if (m_Data == NULL)
    return FALSE;

  if (rle) {
    long pixels = m_Width * m_Height;
    long index = 0;
    BYTE packet, value, count;
    while (index < pixels) {
      if (fread(&packet, 1, 1, fp) != 1)
        return FALSE;
      count = (packet & 0x7F) + 1;
      if (packet & 0x80) {
        if (fread(&value, 1, 1, fp) != 1)
          return FALSE;
        for (BYTE i = 0; i < count && index < pixels; i++)
          m_Data[index++] = value;
      } else {
        if (fread(m_Data + index, 1, count, fp) != count)
          return FALSE;
        index += count;
      }
    }
  } else {
    if (fread(m_Data, 1, m_DataSize, fp) != (size_t)m_DataSize)
      return FALSE;
  }

  return TRUE;
}

BOOL cTGA::Save(char *Filename)
{
  FILE *fp;
  TGAHeader header;

  if (m_Data == NULL || m_Width == 0 || m_Height == 0)
    return FALSE;

  fp = fopen(Filename, "wb");
  if (fp == NULL)
    return FALSE;

  ZeroMemory(&header, sizeof(TGAHeader));
  header.image_type = 2;
  header.width  = (WORD)m_Width;
  header.height = (WORD)m_Height;
  header.bpp    = m_BPP;
  header.descriptor = 0x20;

  if (fwrite(&header, sizeof(TGAHeader), 1, fp) != 1) {
    fclose(fp);
    return FALSE;
  }

  long bytes_per_pixel = m_BPP / 8;
  long data_size = m_Width * m_Height * bytes_per_pixel;
  BYTE *swap = new BYTE[data_size];
  if (swap == NULL) {
    fclose(fp);
    return FALSE;
  }

  for (long i = 0; i < m_Width * m_Height; i++) {
    swap[i * bytes_per_pixel + 0] = m_Data[i * bytes_per_pixel + 2];
    swap[i * bytes_per_pixel + 1] = m_Data[i * bytes_per_pixel + 1];
    swap[i * bytes_per_pixel + 2] = m_Data[i * bytes_per_pixel + 0];
    if (bytes_per_pixel == 4)
      swap[i * bytes_per_pixel + 3] = m_Data[i * bytes_per_pixel + 3];
  }

  if (fwrite(swap, 1, data_size, fp) != (size_t)data_size) {
    delete[] swap;
    fclose(fp);
    return FALSE;
  }

  delete[] swap;
  fclose(fp);
  return TRUE;
}

BOOL cTGA::FlipVertical()
{
  if (m_Data == NULL || m_Width == 0 || m_Height == 0)
    return FALSE;

  long bytes_per_pixel = m_BPP / 8;
  long pitch = m_Width * bytes_per_pixel;
  BYTE *line = new BYTE[pitch];
  if (line == NULL)
    return FALSE;

  for (long y = 0; y < m_Height / 2; y++) {
    BYTE *top = m_Data + y * pitch;
    BYTE *bottom = m_Data + (m_Height - 1 - y) * pitch;
    memcpy(line, top, pitch);
    memcpy(top, bottom, pitch);
    memcpy(bottom, line, pitch);
  }

  delete[] line;
  return TRUE;
}

BOOL cTGA::FlipHorizontal()
{
  if (m_Data == NULL || m_Width == 0 || m_Height == 0)
    return FALSE;

  long bytes_per_pixel = m_BPP / 8;

  for (long y = 0; y < m_Height; y++) {
    BYTE *row = m_Data + y * m_Width * bytes_per_pixel;
    for (long x = 0; x < m_Width / 2; x++) {
      for (long b = 0; b < bytes_per_pixel; b++) {
        BYTE temp = row[x * bytes_per_pixel + b];
        row[x * bytes_per_pixel + b] = row[(m_Width - 1 - x) * bytes_per_pixel + b];
        row[(m_Width - 1 - x) * bytes_per_pixel + b] = temp;
      }
    }
  }

  return TRUE;
}

BOOL cTGA::ConvertTo32()
{
  if (m_Data == NULL || m_BPP == 32)
    return TRUE;

  if (m_BPP != 24)
    return FALSE;

  long pixels = m_Width * m_Height;
  BYTE *new_data = new BYTE[pixels * 4];
  if (new_data == NULL)
    return FALSE;

  for (long i = 0; i < pixels; i++) {
    new_data[i * 4 + 0] = m_Data[i * 3 + 0];
    new_data[i * 4 + 1] = m_Data[i * 3 + 1];
    new_data[i * 4 + 2] = m_Data[i * 3 + 2];
    new_data[i * 4 + 3] = 255;
  }

  delete[] m_Data;
  m_Data = new_data;
  m_BPP = 32;
  m_DataSize = pixels * 4;

  return TRUE;
}
