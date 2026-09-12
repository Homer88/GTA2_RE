
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


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004C32A0: ScriptCommand::LoadFromWaypoint
    void LoadFromWaypoint();
};
#endif // !__SCRIPTCOMMAND_H_