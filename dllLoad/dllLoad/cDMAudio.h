#ifndef __cDMAudio__H_
#define __cDMAudio__H_

#include <assert.h>

// One 0x10-byte slot of the gDMAudio table (observed in game dump).
// Layout confirmed from logs (frame 0 = empty, later frames = loaded):
//   +0x00 u32 pData   -- heap buffer (0x06...) or in-global buffer ptr; while
//                        empty it is a self pointer: base + off + 4
//   +0x04 u32 size    -- small size/type (0..9 at loaded slots: 1,6,7,8,9,...)
//   +0x08 u32 zero    -- always 0
//   +0x0C u32 index   -- global running index (2,4,5,6,... 138...)
struct DMAudioChannel
{
	unsigned int pData;
	unsigned int size;
	unsigned int zero;
	unsigned int index;
};

// gDMAudio @0x005D85A0, next global unk_5DC424 @0x005DC424 -> 0x3E84 bytes.
// Real layout: table of 1000 x 0x10 records (0x3E80) + 4 tail bytes.
struct DMAudio
{
	DMAudioChannel channel[1000];
	char gap_E80[4];
};

static_assert(sizeof(DMAudio) == 0x3E84, "Error Size DMAudio");


#endif
