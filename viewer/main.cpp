// GTA2 Viewer - displays GTA2 menu artwork (frontend/*.tga) and, later,
// map tiles / sprites from the .sty style files.
//
// Controls:
//   Left / Right  - previous / next menu image
//   F11           - switch DirectDraw fullscreen / windowed
//   Esc           - quit

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "DrawDevice.h"
#include "TGA.h"

static const char* g_FrontendDir = "C:\\work\\GTA2_RE\\bin\\data\\frontend";

static std::vector<std::string> ListTgaFiles(const char* dir)
{
  std::vector<std::string> files;
  std::string pattern = std::string(dir) + "\\*.tga";
  WIN32_FIND_DATAA fd;
  HANDLE h = FindFirstFileA(pattern.c_str(), &fd);
  if (h == INVALID_HANDLE_VALUE)
    return files;
  do {
    if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      files.push_back(std::string(dir) + "\\" + fd.cFileName);
  } while (FindNextFileA(h, &fd));
  FindClose(h);

  // simple sort
  for (size_t i = 0; i + 1 < files.size(); i++)
    for (size_t j = i + 1; j < files.size(); j++)
      if (files[j] < files[i]) { std::string t = files[i]; files[i] = files[j]; files[j] = t; }
  return files;
}

static bool LoadImageToRGBA(const char* path, std::vector<unsigned char>& rgba,
                            int& w, int& h)
{
  cTGA tga;
  if (!tga.Load((char*)path)) {
    printf("load fail: %s\n", path);
    return false;
  }
  w = (int)tga.GetWidth();
  h = (int)tga.GetHeight();
  unsigned char* d = tga.GetData();
  if (!d || tga.GetBPP() != 32) {
    printf("bad format: %s\n", path);
    return false;
  }
  rgba.assign(d, d + (size_t)w * h * 4);
  return true;
}

// SEH-guarded render: a transient GDI/DirectDraw fault under RDP/VM must not
// kill the whole app - just skip this frame. No C++ destructible locals here
// so __try/__except is legal with /EHsc.
static void RenderFrameGuarded(cDrawDevice& dev, const unsigned char* rgba)
{
  __try {
    if (!rgba)
      dev.Clear();
    else
      dev.Present(rgba, false);
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    // ignore one-off render faults (RDP display hiccup)
  }
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
  // parse -gdi to force the GDI-only path (avoids DirectDraw under RDP/VM)
  bool forceGDI = false;
  if (lpCmdLine && strstr(lpCmdLine, "-gdi") != NULL)
    forceGDI = true;

  std::vector<std::string> files = ListTgaFiles(g_FrontendDir);
  if (files.empty()) {
    MessageBoxA(NULL, "No .tga files found in frontend dir", "GTA2 Viewer", MB_OK);
    return 1;
  }
  printf("found %d menu images\n", (int)files.size());

  cDrawDevice dev;
  if (!dev.Create(hInst, nCmdShow, 640, 480, false, !forceGDI)) {
    MessageBoxA(NULL, "Failed to create window", "GTA2 Viewer", MB_OK);
    return 1;
  }

  int cur = 0;
  std::vector<unsigned char> rgba;
  int w = 0, h = 0;
  if (!LoadImageToRGBA(files[cur].c_str(), rgba, w, h)) {
    DestroyWindow(dev.GetHWND());
    return 1;
  }
  char title[512];
  sprintf(title, "GTA2 Viewer - %s  [%d/%d]  (Left/Right=switch, F11=fullscreen, Esc=quit)",
          files[cur].c_str(), cur + 1, (int)files.size());
  SetWindowTextA(dev.GetHWND(), title);

  bool wantsFull = false;

  MSG msg;
  ZeroMemory(&msg, sizeof(msg));
  bool done = false;
  while (!done) {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) { done = true; break; }
      // intercept navigation keys globally handled in loop below
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    if (done) break;

    // navigation
    bool nav = false;
    for (int i = 0; i < 256; i++) {
      if (GetAsyncKeyState(i) & 1) {
        if (i == VK_RIGHT || i == VK_NEXT) { cur = (cur + 1) % (int)files.size(); nav = true; }
        if (i == VK_LEFT || i == VK_PRIOR) { cur = (cur - 1 + (int)files.size()) % (int)files.size(); nav = true; }
        if (i == VK_F11) { wantsFull = !wantsFull; nav = false; }
      }
    }
    if (nav) {
      if (!LoadImageToRGBA(files[cur].c_str(), rgba, w, h)) {
        // keep previous
        nav = false;
      } else {
        sprintf(title, "GTA2 Viewer - %s  [%d/%d]  (Left/Right=switch, F11=fullscreen, Esc=quit)",
                files[cur].c_str(), cur + 1, (int)files.size());
        SetWindowTextA(dev.GetHWND(), title);
      }
    }

    // SEH guard is inside RenderFrameGuarded.
    RenderFrameGuarded(dev, rgba.empty() ? (const unsigned char*)NULL : rgba.data());

    Sleep(16);
  }

  dev.Destroy();
  return 0;
}
