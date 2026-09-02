#ifndef GTA2VIEWER_DRAWDEVICE_H
#define GTA2VIEWER_DRAWDEVICE_H

#include <windows.h>
#include <ddraw.h>

#pragma comment(lib,"ddraw.lib")
#pragma comment(lib,"dxguid.lib")

// GTA2 Viewer render device.
// Uses DirectDraw (primary + backbuffer) for presentation, with a GDI
// fallback so the viewer always works even if DirectDraw fails to init
// (e.g. inside VM / RDP / no video acceleration).
class cDrawDevice
{
  public:
    cDrawDevice();
    ~cDrawDevice();

    // Create the window and device. Fullscreen toggles exclusive mode.
    // If enableDirectDraw is false, only the GDI path is used (useful under
    // RDP / VM where DirectDraw surface access can fault).
    bool Create(HINSTANCE hInst, int nCmdShow, int w, int h, bool fullscreen,
                bool enableDirectDraw = true);
    void Destroy();

    // Present the current full-window framebuffer (RGBA32) to the screen.
    void Present(const unsigned char* rgba, bool flipVertical);

    // GDI blit of an RGB(A) bitmap to the window DC (fallback path).
    void BlitGDI(const unsigned char* rgb, int srcW, int srcH, int bpp,
                 bool flipVertical);

    HWND GetHWND() const { return m_hWnd; }
    bool UsingDirectDraw() const { return m_useDDraw; }

    void Clear();

  private:
    bool CreateDirectDraw(HINSTANCE hInst, int w, int h);
    void DestroyDirectDraw();

    HWND                  m_hWnd;
    HINSTANCE             m_hInst;
    int                   m_Width;
    int                   m_Height;
    bool                  m_Fullscreen;

    // DirectDraw
    bool                  m_useDDraw;
    LPDIRECTDRAW          m_lpDD;
    LPDIRECTDRAWSURFACE   m_lpPrimary;
    LPDIRECTDRAWSURFACE   m_lpBack;
    DDSURFACEDESC         m_ddsd;
    int                   m_bpp;
    DWORD                 m_pitch;
    // Backbuffer locked pointer (only valid between Lock/Unlock)
    unsigned char*        m_locked;

    char                  m_Class[256];
};

#endif
