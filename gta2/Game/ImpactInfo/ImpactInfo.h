
#ifndef __IMPACTINFO_H_
#define __IMPACTINFO_H_


class ImpactInfo{
    public:

    // 0x0045BF50
    int Lighting(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x0045AD00: ImpactInfo::Clear
    void Clear();
};
extern ImpactInfo* gImpactInfo;
#endif // !__IMPACTINFO_H_