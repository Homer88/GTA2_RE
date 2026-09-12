
#ifndef __RECT2D_H_
#define __RECT2D_H_


class Rect2D{
    public:

    // 0x004B34E0
    int Rect2DValidateCarForRecycling(void);
    // 0x004B4A60
    int CheckCarRecyclingLimit(void);
    // 0x004B4E60
    int UpdateRecycling(void);


// ==== импорт имён из gm ====
    // 2 функций
    // 0x004B3020: Rect2D::Clear
    void Clear();
    // 0x004B4A00: Rect2D::SetScale
    void SetScale();
};
#endif // !__RECT2D_H_