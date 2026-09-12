
#ifndef __PICKUPINFO_H_
#define __PICKUPINFO_H_


class PickupInfo{
    public:

    // 0x00447350
    int AllocateSprite(void);
    // 0x00447360
    int FreeSprite(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004468A0: PickupInfo::ResetFreeList
    void ResetFreeList();
};
#endif // !__PICKUPINFO_H_