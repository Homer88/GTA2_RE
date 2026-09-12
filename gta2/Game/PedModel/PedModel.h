
#ifndef __PEDMODEL_H_
#define __PEDMODEL_H_


class PedModel{
    public:

    // 0x004C4B80
    int Push(void);
    // 0x004C4BA0
    int Pop(void);
    // 0x004C4BC0
    int IsEmpty(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004C4D20: PedModel::RenderAll
    void RenderAll();
};
#endif // !__PEDMODEL_H_