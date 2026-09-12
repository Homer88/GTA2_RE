
#ifndef __SCRIPTVAR_H_
#define __SCRIPTVAR_H_


class ScriptVar{
    public:

    // 0x004C3380
    int VarAllocateCommand(void);
    // 0x004C3470
    int SetupCommand(void);
    // 0x004C3490
    int FreeScriptVar(void);
    // 0x004C3500
    int ScriptVarProcessCommands(void);
};

#endif // !__SCRIPTVAR_H_