#ifndef __SCRIPTTHREAD_H_
#define __SCRIPTTHREAD_H_

class ScriptThread{

    public:

    // 0x00420F10
    int GetPedID(void);
    // 0x0045AA70
    int S37(void);
    // 0x0045AA90
    int S53(void);
    // 0x0045AAD0
    int S81(void);
    // 0x004B98D0
    int SetPedID(void);
    // 0x004B9980
    int FreeScriptThread(void);
};

#endif // !__SCRIPTTHREAD_H_
