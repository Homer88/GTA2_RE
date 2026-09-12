
#ifndef __CAMERA_H_
#define __CAMERA_H_


class Camera{
    public:

    // 0x0045BEC0
    int S115(void);
    // 0x0045BEE0
    int S117(void);
    // 0x0045BF00
    int S129(void);
    // 0x0045BF30
    int FreeCamera(void);
    // 0x00476760
    int PopViewport(void);
    // 0x00476780
    int ChainViewport(void);


// ==== импорт имён из gm ====
    // 9 функций
    // 0x0046C2C0: Camera::RenderLeft
    void RenderLeft();
    // 0x0046C7F0: Camera::RenderRight
    void RenderRight();
    // 0x0046CE30: Camera::RenderTop
    void RenderTop();
    // 0x0046D360: Camera::RenderFront
    void RenderFront();
    // 0x0046D4F0: Camera::RenderBack
    void RenderBack();
    // 0x0046D680: Camera::RenderNear
    void RenderNear();
    // 0x0046D810: Camera::RenderFar
    void RenderFar();
    // 0x0046D9A0: Camera::RenderBottom
    void RenderBottom();
    // 0x0046DFE0: Camera::RenderLid
    void RenderLid();
};
#endif // !__CAMERA_H_