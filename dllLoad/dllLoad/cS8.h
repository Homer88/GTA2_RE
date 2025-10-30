#ifndef __S8__H__
#define __S8__H__

#include <assert.h>
#include "pch.h"
#include "cS9.h"


struct  S8{
	void* field_0x0;
	S9* sructurS9;
	unsigned char field_0x8;
	unsigned char field_0x9;
	unsigned char field_0xA;
	unsigned char field_0xB;
	void* field_0xC;
	void* field_0x10;
};
static_assert(sizeof(S8) == 0x14, "ERROR Size S8");


static const S8* gS8 = (S8*)0x005e4ca8;

//construct
//  надо еще реверсить
S8* constructS8(S8* thisS8);
//  тоже надо сильнее реверсить 
void S8_FUN_004b34e0(S8* thisS8, void* pararm1, void* pararm2, void* pararm3);
void S8_FUN_004b4a60(S8* thisS8);
void S8_FUN_004b4e60(S8* thisS8);

#endif // !__S8__H__
