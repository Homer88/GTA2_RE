#include "AudioSourceParams.h"

//=============================================================================
// AudioSourceParams::sub_41F9D0
// Returns the x coordinate (first field)
//=============================================================================
int AudioSourceParams::sub_41F9D0(AudioSourceParams* p)
{
    return p->field;
}

//=============================================================================
// AudioSourceParams::SetCameraBounds
// TODO: implement based on IDA dump
//=============================================================================
void AudioSourceParams::SetCameraBounds(AudioSourceParams* p)
{
    (void)p;
}

//=============================================================================
// ProjectPointToScreen
// TODO: implement based on IDA dump
//=============================================================================
int ProjectPointToScreen(AudioSourceParams* p)
{
    (void)p;
    return 0;
}
