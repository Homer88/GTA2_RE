#include <windows.h>
#include "Game/global.h"

class cApp : public cApplication
{
  public:
    BOOL Init()
    {
      strcpy(m_Caption, "GTA2");
      m_Width  = 640;
      m_Height = 480;
      m_XPos   = 100;
      m_YPos   = 100;
      return TRUE;
    }

    BOOL Frame()
    {
      return TRUE;
    }
};

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

DWORD *pMajorVersion; 
DWORD *pMinorVersion;

  gWinApi.GetVersion(pMajorVersion, pMinorVersion);
  cApp App;
  return App.Run();
}
