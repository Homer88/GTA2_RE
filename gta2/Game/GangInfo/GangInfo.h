
#ifndef __GANGINFO_H_
#define __GANGINFO_H_


class GangInfo{
    public:

    // 0x004BA020
    int Reset(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004B9FD0: GangInfo::CheckPlayerMatch
    void CheckPlayerMatch();
};
#endif // !__GANGINFO_H_