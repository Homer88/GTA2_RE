#ifndef __VERTEXBUFFER_H_
#define __VERTEXBUFFER_H_

class VertexBuffer{

    public:

    // 0x0049C6E0
    int InitBuffer(void);
    // 0x0049C700
    int ResetBuffer(void);
    // 0x0049C740
    int VertexBufferReleasePassenger(void);
    // 0x0049C760
    int CheckBuffer(void);
    // 0x0049C820
    int AddPassenger(void);
    // 0x0049CB40 bool __thiscall
    bool GetFlame(int param_1,int param_2);
    // 0x0049CF10
    int Update(void);
    // 0x0049CF70
    int VertexBufferFindPath(void);
};

#endif // !__VERTEXBUFFER_H_
