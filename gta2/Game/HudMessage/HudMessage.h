
#ifndef __HUDMESSAGE_H_
#define __HUDMESSAGE_H_


class HudMessage{
    public:

    // 0x004C5FE0
    int ShowBigOnScreenLabel_0(void);
    // 0x004C60B0
    int DicrementTimeToShow(void);
    // 0x004C8A40
    int Draw(void);
    // 0x004C8AA0
    int CreateMessage(void);
};

#endif // !__HUDMESSAGE_H_