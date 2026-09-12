
#ifndef __JUNCIDS_H_
#define __JUNCIDS_H_


class JuncIds{
    public:

    // 0x0040C690
    int Init(void);
    // 0x0040CB60
    int ClearJunctionId(void);
    // 0x0040CD70
    int PrintJunctions(void);
    // 0x0040D120
    int Display(void);
    // 0x0040D250
    int Load(void);
    // 0x0040E030
    int FindJunction(void);
    // 0x0044B970
    int S19(void);
};

#endif // !__JUNCIDS_H_