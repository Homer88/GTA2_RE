#ifndef __SCRIPTCOMMAND_H_
#define __SCRIPTCOMMAND_H_

class ScriptCommand{

    public:

    // 0x004C3240
    int RegisterTileAnim(void);
    // 0x004C3260
    int ChangeTile(void);
    // 0x004C3300
    int ScriptCommandAnimate(void);
};

#endif // !__SCRIPTCOMMAND_H_
