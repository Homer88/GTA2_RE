#ifndef __COLLIDE__H__
#define __COLLIDE__H__

#include <assert.h>

struct Collide{
	unsigned int count;
	int field_0x4;
	int field_0x8;
};

static_assert(sizeof(Collide)==0xC, "ERROR SIZE COLLIDE");

static  Collide* gCollede = (Collide*)0x005e6680;

// надо доконца реверсить
Collide* constructCollide(Collide* thisCollide);
void Collide_SetParam(Collide* thisCollide);
Collide* DestructCollide(Collide* thisCollide, unsigned char  param_2);


#endif // !__Collide__H__

