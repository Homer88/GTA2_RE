#ifndef __STREAMWRITER_H_
#define __STREAMWRITER_H_

class StreamWriter{

    public:

    // 0x00461590 void __thiscall
    void Allocate(int param_1);
    // 0x004615B0 void __thiscall
    void WriteTimestampDivider(void);
    // 0x004D4ECA void __thiscall
    void FlushAndCheckErrors(void);
};

#endif // !__STREAMWRITER_H_
