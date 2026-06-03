#ifndef __BINK_H__
#define __BINK_H__

#include <windows.h>


struct BINKSUMMARY;

class Bink {
public:
    bool Status = NULL;
    Bink();
    ~Bink();

    void Open(const char* filename, unsigned int flags = 0);
    void Close();
    bool IsOpen() const;

    void BufferOpen(HWND hWnd, int width, int height, int flags);
    void BufferClose();
    bool IsBufferOpen() const;

    int  DoFrame();
    int  NextFrame();
    int  Wait();
    int  CopyToBuffer(void* dst, int dstPitch, int dstBpp, int srcX, int srcY, int width, int height, int flags);
    int  CopyToBufferSlow(void* dst, int dstPitch, int dstBpp, int srcX, int srcY, int width, int height, int flags);

    void BufferBlit(int flags);
    void BufferLock();
    void BufferUnlock();
    void BufferSetOffset(int x, int y);

    void GetSummary(BINKSUMMARY* pSummary);
    void SetSoundSystem(void* soundSystem, void* param);
    void SetIOSize(unsigned int ioSize);

    void* GetHandle() const { return m_hBink; }
    void* GetBufferHandle() const { return m_hBuffer; }
    int   GetOffsetX() const { return m_offsetX; }
    int   GetOffsetY() const { return m_offsetY; }

private:
    void* m_hBink;
    void* m_hBuffer;
    int   m_offsetX;
    int   m_offsetY;
};




#endif // __BINK_H__
