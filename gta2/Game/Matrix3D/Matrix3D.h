#ifndef __MATRIX3D_H_
#define __MATRIX3D_H_

class Matrix3D{

    public:

    // 0x004BB860
    int TestCollisionPoint(void);
    // 0x004BB910 bool __thiscall
    bool TestCollisionQuad(int param_1,int param_2,int param_3);
    // 0x004BB9C0 byte __thiscall
    unsigned char TestCollisionComplex(int param_1,int param_2);
    // 0x004BBD10
    int DESTRUC(void);
    // 0x004BCCC0
    int Detach(void);
};

#endif // !__MATRIX3D_H_
