
#ifndef __ARROWTRACE_H_
#define __ARROWTRACE_H_


class ArrowTrace{
    public:

    // 0x004767F0
    int GetParam(void);
    // 0x00476810
    int ResetParam(void);
    // 0x004820A0
    int SetPlayer(void);
    // 0x004C6F20
    int SetDefaultType(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x00476830: ArrowTrace::Reset
    void Reset();
};
#endif // !__ARROWTRACE_H_