
#ifndef __TEXTLABELPOOL_H_
#define __TEXTLABELPOOL_H_


class TextLabelPool{
    public:

    // 0x004CD9F0 void __fastcall
    // (new_class) старый: TextLabel::DestructTextLabel -> DestroyAll
    void DestroyAll(void *arg0);

    // 0x004D07E0 void * __thiscall
    // (new_class) старый: App::DeleteTextLabel -> Delete
    void* Delete(void *arg0,int arg1);

};
#endif // !__TEXTLABELPOOL_H_
