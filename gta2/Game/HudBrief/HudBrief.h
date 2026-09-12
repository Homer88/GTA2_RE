
#ifndef __HUDBRIEF_H_
#define __HUDBRIEF_H_


class HudBrief{
    public:

    // 0x004768A0
    int IsMessageVisible(void);
    // 0x004C62D0
    int ShowMessageToPlayer_0(void);
    // 0x004C62F0
    int FreeNode(void);
    // 0x004C6310
    int DequeueNode(void);
    // 0x004C6340
    int EnqueueToEnd(void);
    // 0x004C6380
    int GetFreeMessageNode(void);
    // 0x004C6470
    int MainLogic(void);
    // 0x004C6640
    int PrepareDisplay(void);
    // 0x004C6690
    int ShowMessageWithParam(void);
    // 0x004C6830
    int CheckQueue(void);
};

#endif // !__HUDBRIEF_H_