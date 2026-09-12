
#ifndef __SKIDMARKINFO_H_
#define __SKIDMARKINFO_H_


class SkidmarkInfo{
    public:

    // 0x0045E000
    int UpdateFade(void);
    // 0x0045E2E0
    int ProcessFade(void);
    // 0x0045E330
    int AddEntry(void);
};

#endif // !__SKIDMARKINFO_H_