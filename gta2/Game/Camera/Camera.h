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
};

#endif // !__CAMERA_H_
