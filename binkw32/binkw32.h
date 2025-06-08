#ifndef ___BINKW_32_H_
#define ___BINKW_32_H_

#define BINKMAJORVERSION 0
#define BINKMINORVERSION 0
#define BINKSUBVERSION 11
#define BINKVERSION "0.0"
#define BINKDATE    "2025-06-08"

struct BINKIO;
typedef S32  (RADLINK PTR4* BINKIOOPEN)         (struct BINKIO PTR4* Bnkio, const char PTR4 *name, U32 flags);
typedef U32  (RADLINK PTR4* BINKIOREADHEADER)   (struct BINKIO PTR4* Bnkio, S32 Offset, void PTR4* Dest,U32 Size);
typedef U32  (RADLINK PTR4* BINKIOREADFRAME)    (struct BINKIO PTR4* Bnkio, U32 Framenum,S32 origofs,void PTR4* dest,U32 size);
typedef U32  (RADLINK PTR4* BINKIOGETBUFFERSIZE)(struct BINKIO PTR4* Bnkio, U32 Size);
typedef void (RADLINK PTR4* BINKIOSETINFO)      (struct BINKIO PTR4* Bnkio, void PTR4* Buf,U32 Size,U32 FileSize,U32 simulate);
typedef U32  (RADLINK PTR4* BINKIOIDLE)         (struct BINKIO PTR4* Bnkio);
typedef void (RADLINK PTR4* BINKIOCLOSE)        (struct BINKIO PTR4* Bnkio);

typedef void (RADLINK PTR4* BINKCBSUSPEND)    (struct BINKIO PTR4* Bnkio);
typedef S32  (RADLINK PTR4* BINKCBTRYSUSPEND) (struct BINKIO PTR4* Bnkio);
typedef void (RADLINK PTR4* BINKCBRESUME)     (struct BINKIO PTR4* Bnkio);
typedef void (RADLINK PTR4* BINKCBIDLE)       (struct BINKIO PTR4* Bnkio);

typedef struct BINKIO {
  BINKIOREADHEADER ReadHeader;
  BINKIOREADFRAME  ReadFrame;
  BINKIOGETBUFFERSIZE GetBufferSize;
  BINKIOSETINFO SetInfo;
  BINKIOIDLE Idle;
  BINKIOCLOSE Close;
  HBINK bink;
  volatile U32 ReadError;
  volatile U32 DoingARead;
  volatile U32 BytesRead;
  volatile U32 Working;
  volatile U32 TotalTime;
  volatile U32 ForegroundTime;
  volatile U32 IdleTime;
  volatile U32 ThreadTime;
  volatile U32 BufSize;
  volatile U32 BufHighUsed;
  volatile U32 CurBufSize;
  volatile U32 CurBufUsed;
  volatile U8 iodata[128+32];

  // filled in by the caller
  BINKCBSUSPEND suspend_callback;
  BINKCBTRYSUSPEND try_suspend_callback;
  BINKCBRESUME resume_callback;
  BINKCBIDLE idle_on_callback;
  volatile U32 callback_control[16];  // buffer for background IO callback
} BINKIO;

struct BINKSND;
typedef S32  (RADLINK PTR4* BINKSNDOPEN)       (struct BINKSND PTR4* BnkSnd, U32 freq, S32 bits, S32 chans, U32 flags, HBINK bink);
typedef S32  (RADLINK PTR4* BINKSNDREADY)      (struct BINKSND PTR4* BnkSnd);
typedef S32  (RADLINK PTR4* BINKSNDLOCK)       (struct BINKSND PTR4* BnkSnd, U8 PTR4* PTR4* addr, U32 PTR4* len);
typedef S32  (RADLINK PTR4* BINKSNDUNLOCK)     (struct BINKSND PTR4* BnkSnd, U32 filled);
typedef void (RADLINK PTR4* BINKSNDVOLUME)     (struct BINKSND PTR4* BnkSnd, S32 volume);
typedef void (RADLINK PTR4* BINKSNDPAN)        (struct BINKSND PTR4* BnkSnd, S32 pan);
typedef void (RADLINK PTR4* BINKSNDMIXBINS)    (struct BINKSND PTR4* BnkSnd, U32 PTR4* mix_bins, U32 total);
typedef void (RADLINK PTR4* BINKSNDMIXBINVOLS) (struct BINKSND PTR4* BnkSnd, U32 PTR4* vol_mix_bins, S32 PTR4* volumes, U32 total );
typedef S32  (RADLINK PTR4* BINKSNDONOFF)      (struct BINKSND PTR4* BnkSnd, S32 status);
typedef S32  (RADLINK PTR4* BINKSNDPAUSE)      (struct BINKSND PTR4* BnkSnd, S32 status);
typedef void (RADLINK PTR4* BINKSNDCLOSE)      (struct BINKSND PTR4* BnkSnd);

typedef BINKSNDOPEN  (RADLINK PTR4* BINKSNDSYSOPEN) (U32 param);

typedef struct BINKSND {
  BINKSNDREADY Ready;
  BINKSNDLOCK Lock;
  BINKSNDUNLOCK Unlock;
  BINKSNDVOLUME Volume;
  BINKSNDPAN Pan;
  BINKSNDPAUSE Pause;
  BINKSNDONOFF SetOnOff;
  BINKSNDCLOSE Close;
  BINKSNDMIXBINS MixBins;
  BINKSNDMIXBINVOLS MixBinVols;

  U32 sndbufsize;             // sound buffer size
  U8 PTR4* sndbuf;            // sound buffer
  U8 PTR4* sndend;            // end of the sound buffer
  U8 PTR4* sndwritepos;       // current write position
  U8 PTR4* sndreadpos;        // current read position
  U32 sndcomp;                // sound compression handle
  U32 sndamt;                 // amount of sound currently in the buffer
  U32 sndconvert8;            // convert back to 8-bit sound at runtime
  U32 sndendframe;            // frame number that the sound ends on
  U32 sndprime;               // amount of data to prime the playahead
  U32 sndpad;                 // padded this much audio

  U32 BestSizeIn16;
  U32 BestSizeMask;
  U32 SoundDroppedOut;
  S32 OnOff;
  U32 Latency;
  U32 VideoScale;
  U32 freq;
  S32 bits,chans;
  U8 snddata[256];
} BINKSND;

typedef struct BINKRECT {
  S32 Left,Top,Width,Height;
} BINKRECT;

#define BINKMAXDIRTYRECTS 8

typedef struct BUNDLEPOINTERS {
  void* typeptr;
  void* type16ptr;
  void* colorptr;
  void* bits2ptr;
  void* motionXptr;
  void* motionYptr;
  void* dctptr;
  void* mdctptr;
  void* patptr;
} BUNDLEPOINTERS;


typedef struct BINK {
  U32 Width;             // Width (1 based, 640 for example)
  U32 Height;            // Height (1 based, 480 for example)
  U32 Frames;            // Number of frames (1 based, 100 = 100 frames)
  U32 FrameNum;          // Frame to *be* displayed (1 based)
  U32 LastFrameNum;      // Last frame decompressed or skipped (1 based)

  U32 FrameRate;         // Frame Rate Numerator
  U32 FrameRateDiv;      // Frame Rate Divisor (frame rate=numerator/divisor)

  U32 ReadError;         // Non-zero if a read error has ocurred
  U32 OpenFlags;         // flags used on open
  U32 BinkType;          // Bink flags

  U32 Size;              // size of file
  U32 FrameSize;         // The current frame's size in bytes
  U32 SndSize;           // The current frame sound tracks' size in bytes

  BINKRECT FrameRects[BINKMAXDIRTYRECTS];// Dirty rects from BinkGetRects
  S32 NumRects;

  U32 PlaneNum;          // which set of planes is current
  void PTR4* YPlane[2];  // pointer to the uncompressed Y (Cr and Cr follow)
  void PTR4* APlane[2];  // decompressed alpha plane (if present)
  U32 YWidth;            // widths and heights of the video planes
  U32 YHeight;
  U32 UVWidth;
  U32 UVHeight;

  void PTR4* MaskPlane;  // pointer to the mask plane (Ywidth/16*Yheight/16)
  U32 MaskPitch;         // Mask Pitch
  U32 MaskLength;        // total length of the mask plane

  U32 LargestFrameSize;  // Largest frame size
  U32 InternalFrames;    // how many frames were potentially compressed

  S32 NumTracks;         // how many tracks

  U32 Highest1SecRate;   // Highest 1 sec data rate
  U32 Highest1SecFrame;  // Highest 1 sec data rate starting frame

  S32 Paused;            // is the bink movie paused?

  U32 BackgroundThread;  // handle to background thread

  // everything below is for internal Bink use

  void PTR4* compframe;       // compressed frame data
  void PTR4* preloadptr;      // preloaded compressed frame data
  U32* frameoffsets;          // offsets of each of the frames

  BINKIO bio;                 // IO structure
  U8 PTR4* ioptr;             // io buffer ptr
  U32 iosize;                 // io buffer size
  U32 decompwidth;            // width not include scaling
  U32 decompheight;           // height not include scaling

  S32 PTR4* trackindexes;     // track indexes
  U32 PTR4* tracksizes;       // largest single frame of track
  U32 PTR4* tracktypes;       // type of each sound track
  S32 PTR4* trackIDs;         // external track numbers

  U32 numrects;               // number of rects from BinkGetRects

  U32 playedframes;           // how many frames have we played
  U32 firstframetime;         // very first frame start
  U32 startframetime;         // start frame start
  U32 startblittime;          // start of blit period
  U32 startsynctime;          // start of synched time
  U32 startsyncframe;         // frame of startsynctime
  U32 twoframestime;          // two frames worth of time
  U32 entireframetime;        // entire frame time

  U32 slowestframetime;       // slowest frame in ms
  U32 slowestframe;           // slowest frame number
  U32 slowest2frametime;      // second slowest frame in ms
  U32 slowest2frame;          // second slowest frame

  U32 soundon;                // sound turned on?
  U32 videoon;                // video turned on?

  U32 totalmem;               // total memory used
  U32 timevdecomp;            // total time decompressing video
  U32 timeadecomp;            // total time decompressing audio
  U32 timeblit;               // total time blitting
  U32 timeopen;               // total open time

  U32 fileframerate;          // frame rate originally in the file
  U32 fileframeratediv;

  U32 runtimeframes;          // max frames for runtime analysis
  U32 runtimemoveamt;         // bytes to move each frame
  U32 PTR4* rtframetimes;     // start times for runtime frames
  U32 PTR4* rtadecomptimes;   // decompress times for runtime frames
  U32 PTR4* rtvdecomptimes;   // decompress times for runtime frames
  U32 PTR4* rtblittimes;      // blit times for runtime frames
  U32 PTR4* rtreadtimes;      // read times for runtime frames
  U32 PTR4* rtidlereadtimes;  // idle read times for runtime frames
  U32 PTR4* rtthreadreadtimes;// thread read times for runtime frames

  U32 lastblitflags;          // flags used on last blit
  U32 lastdecompframe;        // last frame number decompressed

  U32 lastresynctime;         // last loop point that we did a resync on
  U32 doresync;               // should we do a resync in the next doframe?

  U32 playingtracks;          // how many tracks are playing
  U32 soundskips;             // number of sound stops
  BINKSND PTR4* bsnd;         // SND structures
  U32 skippedlastblit;        // skipped last frame?
  U32 skipped_this_frame;     // skipped the current frame?
  U32 skippedblits;           // how many blits were skipped

  BUNDLEPOINTERS bunp;        // pointers to internal temporary memory
  U32 skipped_in_a_row;       // how many frames have we skipped in a row
  U32 big_sound_skip_adj;     // adjustment for large skips
  U32 big_sound_skip_reduce;  // amount to reduce large skips by each frame
  U32 last_time_almost_empty; // time of last almost empty IO buffer
  U32 last_read_count;        // counter to keep track of the last bink IO
  U32 last_sound_count;       // counter to keep track of the last bink sound
  U32 snd_callback_buffer[16]; // buffer for background sound callback
} BINK;


typedef struct BINKSUMMARY {
  U32 Width;                  // Width of frames
  U32 Height;                 // Height of frames
  U32 TotalTime;              // total time (ms)
  U32 FileFrameRate;          // frame rate
  U32 FileFrameRateDiv;       // frame rate divisor
  U32 FrameRate;              // frame rate
  U32 FrameRateDiv;           // frame rate divisor
  U32 TotalOpenTime;          // Time to open and prepare for decompression
  U32 TotalFrames;            // Total Frames
  U32 TotalPlayedFrames;      // Total Frames played
  U32 SkippedFrames;          // Total number of skipped frames
  U32 SkippedBlits;           // Total number of skipped blits
  U32 SoundSkips;             // Total number of sound skips
  U32 TotalBlitTime;          // Total time spent blitting
  U32 TotalReadTime;          // Total time spent reading
  U32 TotalVideoDecompTime;   // Total time spent decompressing video
  U32 TotalAudioDecompTime;   // Total time spent decompressing audio
  U32 TotalIdleReadTime;      // Total time spent reading while idle
  U32 TotalBackReadTime;      // Total time spent reading in background
  U32 TotalReadSpeed;         // Total io speed (bytes/second)
  U32 SlowestFrameTime;       // Slowest single frame time (ms)
  U32 Slowest2FrameTime;      // Second slowest single frame time (ms)
  U32 SlowestFrameNum;        // Slowest single frame number
  U32 Slowest2FrameNum;       // Second slowest single frame number
  U32 AverageDataRate;        // Average data rate of the movie
  U32 AverageFrameSize;       // Average size of the frame
  U32 HighestMemAmount;       // Highest amount of memory allocated
  U32 TotalIOMemory;          // Total extra memory allocated
  U32 HighestIOUsed;          // Highest extra memory actually used
  U32 Highest1SecRate;        // Highest 1 second rate
  U32 Highest1SecFrame;       // Highest 1 second start frame
} BINKSUMMARY;


typedef struct BINKREALTIME {
  U32 FrameNum;               // Current frame number
  U32 FrameRate;              // frame rate
  U32 FrameRateDiv;           // frame rate divisor
  U32 Frames;                 // frames in this sample period
  U32 FramesTime;             // time is ms for these frames
  U32 FramesVideoDecompTime;  // time decompressing these frames
  U32 FramesAudioDecompTime;  // time decompressing these frames
  U32 FramesReadTime;         // time reading these frames
  U32 FramesIdleReadTime;     // time reading these frames at idle
  U32 FramesThreadReadTime;   // time reading these frames in background
  U32 FramesBlitTime;         // time blitting these frames
  U32 ReadBufferSize;         // size of read buffer
  U32 ReadBufferUsed;         // amount of read buffer currently used
  U32 FramesDataRate;         // data rate for these frames
} BINKREALTIME;

#define BINKMARKER1 'fKIB'
#define BINKMARKER2 'gKIB'    // new Bink files use this tag
#define BINKMARKER3 'hKIB'    // newer Bink files use this tag
#define BINKMARKER4 'iKIB'    // even newer Bink files use this tag

typedef struct BINKHDR {
  U32 Marker;                 // Bink marker
  U32 Size;                   // size of the file-8
  U32 Frames;                 // Number of frames (1 based, 100 = 100 frames)
  U32 LargestFrameSize;       // Size in bytes of largest frame
  U32 InternalFrames;         // Number of internal frames

  U32 Width;                  // Width (1 based, 640 for example)
  U32 Height;                 // Height (1 based, 480 for example)
  U32 FrameRate;              // frame rate
  U32 FrameRateDiv;           // frame rate divisor (framerate/frameratediv=fps)

  U32 Flags;                  // height compression options
  U32 NumTracks;              // number of tracks
} BINKHDR;



//=======================================================================
#define BINKFRAMERATE         0x00001000L // Override fr (call BinkFrameRate first)
#define BINKPRELOADALL        0x00002000L // Preload the entire animation
#define BINKSNDTRACK          0x00004000L // Set the track number to play
#define BINKOLDFRAMEFORMAT    0x00008000L // using the old Bink frame format (internal use only)
#define BINKRBINVERT          0x00010000L // use reversed R and B planes (internal use only)
#define BINKGRAYSCALE         0x00020000L // Force Bink to use grayscale
#define BINKNOMMX             0x00040000L // Don't use MMX
#define BINKNOSKIP            0x00080000L // Don't skip frames if falling behind
#define BINKALPHA             0x00100000L // Decompress alpha plane (if present)
#define BINKNOFILLIOBUF       0x00200000L // Fill the IO buffer in SmackOpen
#define BINKSIMULATE          0x00400000L // Simulate the speed (call BinkSim first)
#define BINKFILEHANDLE        0x00800000L // Use when passing in a file handle
#define BINKIOSIZE            0x01000000L // Set an io size (call BinkIOSize first)
#define BINKIOPROCESSOR       0x02000000L // Set an io processor (call BinkIO first)
#define BINKFROMMEMORY        0x04000000L // Use when passing in a pointer to the file
#define BINKNOTHREADEDIO      0x08000000L // Don't use a background thread for IO

#define BINKSURFACEFAST       0x00000000L
#define BINKSURFACESLOW       0x08000000L
#define BINKSURFACEDIRECT     0x04000000L

#define BINKCOPYALL           0x80000000L // copy all pixels (not just changed)
#define BINKCOPY2XH           0x10000000L // Force doubling height scaling
#define BINKCOPY2XHI          0x20000000L // Force interleaving height scaling
#define BINKCOPY2XW           0x30000000L // copy the width zoomed by two
#define BINKCOPY2XWH          0x40000000L // copy the width and height zoomed by two
#define BINKCOPY2XWHI         0x50000000L // copy the width and height zoomed by two
#define BINKCOPY1XI           0x60000000L // copy the width and height zoomed by two
#define BINKCOPYNOSCALING     0x70000000L // Force scaling off

//#define BINKALPHA           0x00100000L // Decompress alpha plane (if present)
//#define BINKNOSKIP          0x00080000L // don't skip the blit if behind in sound
//#define BINKNOMMX           0x00040000L // Don't skip frames if falling behind
//#define BINKGRAYSCALE       0x00020000L // force Bink to use grayscale
//#define BINKRBINVERT        0x00010000L // use reversed R and B planes

#define BINKSURFACE8P          0
#define BINKSURFACE24          1
#define BINKSURFACE24R         2
#define BINKSURFACE32          3
#define BINKSURFACE32R         4
#define BINKSURFACE32A         5
#define BINKSURFACE32RA        6
#define BINKSURFACE4444        7
#define BINKSURFACE5551        8
#define BINKSURFACE555         9
#define BINKSURFACE565        10
#define BINKSURFACE655        11
#define BINKSURFACE664        12
#define BINKSURFACEYUY2       13
#define BINKSURFACEUYVY       14
#define BINKSURFACEYV12       15
#define BINKSURFACEMASK       15

#ifdef __RADXBOX__

#define BINKSURFACESALL        32
#define BINKCONVERTERSMONO     64
#define BINKCONVERTERS2X      256

#define BINKCONVERTERSALL (BINKSURFACESALL|BINKCONVERTERSMONO|BINKCONVERTERS2X)

#define BinkLoad() BinkLoadUnload(1)
#define BinkUnload() BinkLoadUnload(0)

#define BinkLoadConverter(val) BinkLoadUnloadConverter(val,1)
#define BinkUnloadConverter(val) BinkLoadUnloadConverter(val,0)

RADEXPFUNC void RADEXPLINK BinkLoadUnload( S32 inout );
RADEXPFUNC void RADEXPLINK BinkLoadUnloadConverter( U32 surfaces, S32 inout );

#endif

#define BINKGOTOQUICK          1
#define BINKGOTOQUICKSOUND     2

#define BINKGETKEYPREVIOUS     0
#define BINKGETKEYNEXT         1
#define BINKGETKEYCLOSEST      2
#define BINKGETKEYNOTEQUAL   128

//=======================================================================







//прототипы
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
BOOL __stdcall DllEntryPoint(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);
int __stdcall BinkCheckCursor(HWND hWnd, LONG a2, LONG a3, int a4, int a5);
int __stdcall BinkRestoreCursor(int restoreCount);
void* __stdcall radmalloc(size_t size);
void __stdcall radfree(void* aligned_ptr);
void __stdcall BinkOpenMiles(void*);
void __stdcall BinkSetSoundSystem(void*, void*);
void __stdcall BinkSetIOSize(void*);
void __stdcall BinkOpen(void*, void*);
void __stdcall BinkBufferSetDDPrimary(void*);
int __stdcall BinkWait(_DWORD);
int __stdcall BinkDoFrame(HBINK bnk);
int __stdcall BinkCopyToBuffer(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
int __stdcall BinkBufferLock(_DWORD);
int __cdecl BinkBufferBlit(_DWORD, _DWORD, _DWORD);
int __stdcall BinkBufferUnlock(_DWORD);
void __stdcall BinkBufferOpen(void*, void*,void*, void*);
int __stdcall BinkNextFrame(_DWORD);
int __stdcall BinkClose(HBINK bnk);
int __stdcall BinkBufferSetOffset(_DWORD, _DWORD, _DWORD);
int __stdcall BinkBufferCheckWinPos(_DWORD, _DWORD, _DWORD);
int __stdcall BinkBufferClose(_DWORD);
int __stdcall BinkGetSummary(_DWORD, _DWORD);

#endif
