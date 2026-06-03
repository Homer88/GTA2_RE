#include "Bink.h"
#include "..\..\..\binkw32\binkw32.h"


void* gBinkBuffer;
int   gBinkBufferOffset;
BINKSUMMARY* gBinkSummary;

Bink gBink;

typedef HBINK (__stdcall *BinkOpenProc)(const char*, U32);
typedef void (__stdcall *BinkBufferOpenProc)(HBINK, HWND, void*, void*);
typedef int (__stdcall *BinkBufferCloseProc)(U32);
typedef int (__stdcall *BinkCloseProc)(HBINK);
typedef int (__stdcall *BinkDoFrameProc)(HBINK);
typedef int (__stdcall *BinkNextFrameProc)(U32);
typedef int (__stdcall *BinkWaitProc)(U32);
typedef int (__stdcall *BinkCopyToBufferProc)(U32, U32, U32, U32, U32, U32, U32);
typedef void (__stdcall *BinkGetSummaryProc)(U32, U32);
typedef int (__stdcall *BinkBufferSetOffsetProc)(U32, U32, U32);
typedef int (__stdcall *BinkBufferLockProc)(U32);
typedef int (__cdecl   *BinkBufferBlitProc)(U32, U32, U32);
typedef int (__stdcall *BinkBufferUnlockProc)(U32);
typedef void (__stdcall *BinkSetSoundSystemProc)(void*, void*);
typedef void (__stdcall *BinkSetIOSizeProc)(void*);

Bink::Bink()
    : m_hBink(0)
    , m_hBuffer(0)
    , m_offsetX(0)
    , m_offsetY(0)
{
}

Bink::~Bink()
{
    BufferClose();
    Close();
}

void Bink::Open(const char* filename, unsigned int flags)
{
    if (m_hBink)
        Close();
    BinkOpenProc realBinkOpen = (BinkOpenProc)&BinkOpen;
    HBINK handle = realBinkOpen(filename, (U32)flags);
    m_hBink = (void*)handle;
}

void Bink::Close()
{
    if (m_hBink)
    {
        BinkCloseProc realBinkClose = (BinkCloseProc)&BinkClose;
        realBinkClose((HBINK)m_hBink);
        m_hBink = 0;
    }
}

bool Bink::IsOpen() const
{
    return m_hBink != 0;
}

void Bink::BufferOpen(HWND hWnd, int width, int height, int flags)
{
    BufferClose();
    BinkBufferOpenProc realBinkBufferOpen = (BinkBufferOpenProc)&BinkBufferOpen;
    realBinkBufferOpen((HBINK)m_hBink, hWnd, (void*)width, (void*)height);
    m_hBuffer = (void*)1;
}

void Bink::BufferClose()
{
    if (m_hBuffer)
    {
        BinkBufferCloseProc realBinkBufferClose = (BinkBufferCloseProc)&BinkBufferClose;
        realBinkBufferClose(0);
        m_hBuffer = 0;
        m_offsetX = 0;
        m_offsetY = 0;
    }
}

bool Bink::IsBufferOpen() const
{
    return m_hBuffer != 0;
}

int Bink::DoFrame()
{
    BinkDoFrameProc realBinkDoFrame = (BinkDoFrameProc)&BinkDoFrame;
    return realBinkDoFrame((HBINK)m_hBink);
}

int Bink::NextFrame()
{
    BinkNextFrameProc realBinkNextFrame = (BinkNextFrameProc)&BinkNextFrame;
    return realBinkNextFrame(0);
}

int Bink::Wait()
{
    BinkWaitProc realBinkWait = (BinkWaitProc)&BinkWait;
    return realBinkWait(0);
}

int Bink::CopyToBuffer(void* dst, int dstPitch, int dstBpp, int srcX, int srcY, int width, int height, int flags)
{
    BinkCopyToBufferProc realBinkCopy = (BinkCopyToBufferProc)&BinkCopyToBuffer;
    return realBinkCopy((U32)m_hBink, (U32)dst, (U32)dstPitch, (U32)dstBpp, (U32)m_offsetX, (U32)m_offsetY, (U32)flags);
}

int Bink::CopyToBufferSlow(void* dst, int dstPitch, int dstBpp, int srcX, int srcY, int width, int height, int flags)
{
    BinkCopyToBufferProc realBinkCopy = (BinkCopyToBufferProc)&BinkCopyToBuffer;
    return realBinkCopy((U32)m_hBink, (U32)dst, (U32)dstPitch, (U32)dstBpp, (U32)m_offsetX, (U32)m_offsetY, (U32)flags);
}

void Bink::BufferBlit(int flags)
{
    BinkBufferBlitProc realBinkBufferBlit = (BinkBufferBlitProc)&BinkBufferBlit;
    realBinkBufferBlit(0, m_offsetX, m_offsetY);
}

void Bink::BufferLock()
{
    BinkBufferLockProc realBinkBufferLock = (BinkBufferLockProc)&BinkBufferLock;
    realBinkBufferLock(0);
}

void Bink::BufferUnlock()
{
    BinkBufferUnlockProc realBinkBufferUnlock = (BinkBufferUnlockProc)&BinkBufferUnlock;
    realBinkBufferUnlock(0);
}

void Bink::BufferSetOffset(int x, int y)
{
    m_offsetX = x;
    m_offsetY = y;
    BinkBufferSetOffsetProc realBinkSetOff = (BinkBufferSetOffsetProc)&BinkBufferSetOffset;
    realBinkSetOff(0, x, y);
}

void Bink::GetSummary(BINKSUMMARY* pSummary)
{
    if (m_hBink && pSummary)
    {
        BinkGetSummaryProc realBinkGetSummary = (BinkGetSummaryProc)&BinkGetSummary;
        realBinkGetSummary((U32)m_hBink, (U32)pSummary);
    }
}

void Bink::SetSoundSystem(void* soundSystem, void* param)
{
    BinkSetSoundSystemProc realBinkSetSound = (BinkSetSoundSystemProc)&BinkSetSoundSystem;
    realBinkSetSound(soundSystem, param);
}

void Bink::SetIOSize(unsigned int ioSize)
{
    BinkSetIOSizeProc realBinkSetIOSize = (BinkSetIOSizeProc)&BinkSetIOSize;
    realBinkSetIOSize((void*)ioSize);
}


