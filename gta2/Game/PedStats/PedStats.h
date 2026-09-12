
#ifndef __PEDSTATS_H_
#define __PEDSTATS_H_


class PedStats{
    public:

    // 0x00401B10
    int EncodedFloatToRegularFloat(void);
    // 0x0045B040
    int ClearGroundList(void);
    // 0x0046B440
    int IsTileBlockedPedStats(void);
    // 0x0046B620
    int Defaut(void);
    // 0x0046BB40
    int ResetTriangleCount(void);
    // 0x004720E0
    int RenderGroundList(void);
    // 0x00472110
    int RenderGround(void);
    // 0x004725B0
    int GetStatById(void);


// ==== импорт имён из gm ====
    // 2 функций
    // 0x0046B5E0: PedStats::GetStat
    void GetStat();
    // 0x0046C0C0: PedStats::SetCachedField
    void SetCachedField();
};
#endif // !__PEDSTATS_H_