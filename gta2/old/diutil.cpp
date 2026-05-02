#include <dinput.h>
#include "Global.h"
#include "diutil.h"


#define DIRECTINPUT_VERSION 0x0800

LPVOID* gDirectInput8;
REFIID  gREFIID = IID_IDirectInput8A;

HRESULT initDirectInput(HINSTANCE hInstance) {

    HRESULT result;

    result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, gREFIID, gDirectInput8, NULL);
    if (result < 0)
        DebugLog(8u, "diutil.cpp", 138);
    return result;
}