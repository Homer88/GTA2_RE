#include "DrawDevice.h"
#include <cstdio>
#include <cstring>

#ifdef VIEWER_DEBUG_LOG
static void VLog(const char* s)
{
  FILE* f = fopen("C:\\Users\\Home\\AppData\\Local\\Temp\\opencode\\vcx\\viewermem.log", "a");
  if (f) { fprintf(f, "%s\n", s); fclose(f); }
}
#else
#define VLog(s) ((void)0)
#endif

static LRESULT CALLBACK ViewerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_KEYDOWN:
      if (wParam == VK_ESCAPE) {
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        return 0;
      }
      break;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

cDrawDevice::cDrawDevice()
{
  m_hWnd = NULL;
  m_hInst = NULL;
  m_Width = 640;
  m_Height = 480;
  m_Fullscreen = false;
  m_useDDraw = false;
  m_lpDD = NULL;
  m_lpPrimary = NULL;
  m_lpBack = NULL;
  m_bpp = 0;
  m_pitch = 0;
  m_locked = NULL;
  strcpy(m_Class, "Gta2ViewerClass");
}

cDrawDevice::~cDrawDevice()
{
  Destroy();
}

bool cDrawDevice::Create(HINSTANCE hInst, int nCmdShow, int w, int h, bool fullscreen,
                         bool enableDirectDraw)
{
  m_hInst = hInst;
  m_Width = w;
  m_Height = h;
  m_Fullscreen = fullscreen;

  WNDCLASSEX wc;
  ZeroMemory(&wc, sizeof(wc));
  wc.cbSize = sizeof(wc);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = ViewerWndProc;
  wc.hInstance = hInst;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszClassName = m_Class;
  RegisterClassEx(&wc);

  DWORD style = WS_OVERLAPPEDWINDOW;
  RECT rc = { 0, 0, w, h };
  AdjustWindowRect(&rc, style, FALSE);

  m_hWnd = CreateWindow(m_Class, "GTA2 Viewer",
                        style,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        rc.right - rc.left, rc.bottom - rc.top,
                        NULL, NULL, hInst, NULL);
  if (!m_hWnd)
    return false;

  ShowWindow(m_hWnd, nCmdShow);
  UpdateWindow(m_hWnd);

  VLog("Create: window created");

  // Try DirectDraw first; fall back to GDI if it fails (or is disabled).
  if (enableDirectDraw) {
    m_useDDraw = CreateDirectDraw(hInst, w, h);
    VLog(m_useDDraw ? "Create: DirectDraw OK" : "Create: DirectDraw fail -> GDI");
  } else {
    m_useDDraw = false;
    VLog("Create: DirectDraw disabled -> GDI");
  }
  return true;
}

void cDrawDevice::Destroy()
{
  DestroyDirectDraw();
  if (m_hWnd) {
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;
  }
  UnregisterClass(m_Class, m_hInst);
}

bool cDrawDevice::CreateDirectDraw(HINSTANCE hInst, int w, int h)
{
  HRESULT hr;
  VLog("DD: DirectDrawCreate...");
  hr = DirectDrawCreate(NULL, &m_lpDD, NULL);
  VLog("DD: DirectDrawCreate done");
  if (FAILED(hr))
    return false;

  if (m_Fullscreen) {
    hr = m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (FAILED(hr))
      hr = m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
    if (SUCCEEDED(hr))
      m_lpDD->SetDisplayMode(w, h, 16);
    // primary surface with back buffer in fullscreen
    ZeroMemory(&m_ddsd, sizeof(m_ddsd));
    m_ddsd.dwSize = sizeof(m_ddsd);
    m_ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    m_ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    m_ddsd.dwBackBufferCount = 1;
    hr = m_lpDD->CreateSurface(&m_ddsd, &m_lpPrimary, NULL);
    if (SUCCEEDED(hr)) {
      DDSCAPS caps;
      caps.dwCaps = DDSCAPS_BACKBUFFER;
      m_lpPrimary->GetAttachedSurface(&caps, &m_lpBack);
    }
  } else {
    VLog("DD: SetCooperativeLevel...");
    hr = m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
    VLog("DD: SetCooperativeLevel done");
    if (FAILED(hr)) {
      m_lpDD->Release();
      m_lpDD = NULL;
      return false;
    }
    // primary surface
    ZeroMemory(&m_ddsd, sizeof(m_ddsd));
    m_ddsd.dwSize = sizeof(m_ddsd);
    m_ddsd.dwFlags = DDSD_CAPS;
    m_ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    hr = m_lpDD->CreateSurface(&m_ddsd, &m_lpPrimary, NULL);
    if (FAILED(hr)) {
      m_lpDD->Release();
      m_lpDD = NULL;
      return false;
    }
  }

  if (FAILED(hr) || m_lpPrimary == NULL) {
    if (m_lpPrimary) m_lpPrimary->Release();
    m_lpPrimary = NULL;
    m_lpDD->Release();
    m_lpDD = NULL;
    return false;
  }

  // Record primary surface pixel format (for scaling blit)
  DDSURFACEDESC d;
  ZeroMemory(&d, sizeof(d));
  d.dwSize = sizeof(d);
  m_lpPrimary->GetSurfaceDesc(&d);
  m_bpp = (d.ddpfPixelFormat.dwRGBBitCount) ? (int)d.ddpfPixelFormat.dwRGBBitCount : 16;
  m_pitch = 0;

  return true;
}

void cDrawDevice::DestroyDirectDraw()
{
  if (m_lpBack) { m_lpBack->Release(); m_lpBack = NULL; }
  if (m_lpPrimary) { m_lpPrimary->Release(); m_lpPrimary = NULL; }
  if (m_lpDD) { m_lpDD->Release(); m_lpDD = NULL; }
  m_useDDraw = false;
}

void cDrawDevice::Clear()
{
  if (!m_lpPrimary)
    return;

  DDBLTFX fx;
  ZeroMemory(&fx, sizeof(fx));
  fx.dwSize = sizeof(fx);
  fx.dwFillColor = 0;
  m_lpPrimary->Blt(NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &fx);
}

// Present: scale the source RGBA image so it fits within the client area,
// centered, then blit. Works for both fullscreen flip and windowed primary.
void cDrawDevice::Present(const unsigned char* rgba, bool flipVertical)
{
  if (!m_lpPrimary || !rgba)
    return;

  // client size
  RECT cr;
  GetClientRect(m_hWnd, &cr);
  int cw = cr.right, ch = cr.bottom;

  // Build a 32bpp DC-style temp via GDI onto the window for reliability.
  // (DirectDraw windowed blit of a DIB can be fiddly; we use GDI for the
  // forward path and keep DirectDraw for future surface-based tile/sprite
  // composition.)
  HDC hdcWnd = GetDC(m_hWnd);
  if (hdcWnd) {
    // Create DIB section matching the image
    BITMAPINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = m_Width;
    bi.bmiHeader.biHeight = flipVertical ? -m_Height : m_Height; // negative = top-down
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = NULL;
    HDC hdcMem = CreateCompatibleDC(hdcWnd);
    HBITMAP hbmp = CreateDIBSection(hdcMem, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
    if (hbmp && bits) {
      memcpy(bits, rgba, (size_t)m_Width * m_Height * 4);

      // scale to fit client area, keep aspect
      double sx = (double)cw / m_Width;
      double sy = (double)ch / m_Height;
      double s = sx < sy ? sx : sy;
      int dw = (int)(m_Width * s);
      int dh = (int)(m_Height * s);
      int dx = (cw - dw) / 2;
      int dy = (ch - dh) / 2;

      HGDIOBJ old = SelectObject(hdcMem, hbmp);
      HBRUSH black = (HBRUSH)GetStockObject(BLACK_BRUSH);
      RECT full = { 0, 0, cw, ch };
      FillRect(hdcWnd, &full, black);
      SetStretchBltMode(hdcWnd, COLORONCOLOR);
      StretchBlt(hdcWnd, dx, dy, dw, dh, hdcMem, 0, 0, m_Width, m_Height, SRCCOPY);
      SelectObject(hdcMem, old);
      DeleteObject(hbmp);
    }
    DeleteDC(hdcMem);
    ReleaseDC(m_hWnd, hdcWnd);
  }
}

void cDrawDevice::BlitGDI(const unsigned char* rgb, int srcW, int srcH, int bpp,
                          bool flipVertical)
{
  HDC hdcWnd = GetDC(m_hWnd);
  if (!hdcWnd)
    return;

  RECT cr;
  GetClientRect(m_hWnd, &cr);
  int cw = cr.right, ch = cr.bottom;

  BITMAPINFO bi;
  ZeroMemory(&bi, sizeof(bi));
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = srcW;
  bi.bmiHeader.biHeight = flipVertical ? -srcH : srcH;
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = (WORD)bpp;
  bi.bmiHeader.biCompression = BI_RGB;
  void* bits = NULL;
  HDC hdcMem = CreateCompatibleDC(hdcWnd);
  HBITMAP hbmp = CreateDIBSection(hdcMem, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
  if (hbmp && bits) {
    size_t rowbytes = (size_t)srcW * (bpp / 8);
    size_t sz = rowbytes * srcH;
    memcpy(bits, rgb, sz);

    double sx = (double)cw / srcW;
    double sy = (double)ch / srcH;
    double s = sx < sy ? sx : sy;
    int dw = (int)(srcW * s);
    int dh = (int)(srcH * s);
    int dx = (cw - dw) / 2;
    int dy = (ch - dh) / 2;

    HGDIOBJ old = SelectObject(hdcMem, hbmp);
    HBRUSH black = (HBRUSH)GetStockObject(BLACK_BRUSH);
    RECT full = { 0, 0, cw, ch };
    FillRect(hdcWnd, &full, black);
    SetStretchBltMode(hdcWnd, COLORONCOLOR);
    StretchBlt(hdcWnd, dx, dy, dw, dh, hdcMem, 0, 0, srcW, srcH, SRCCOPY);
    SelectObject(hdcMem, old);
    DeleteObject(hbmp);
  }
  DeleteDC(hdcMem);
  ReleaseDC(m_hWnd, hdcWnd);
}
