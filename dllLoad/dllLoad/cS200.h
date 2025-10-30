#ifndef __S200_H_
#define __S200_H_

#include <assert.h>

struct  S200{
	unsigned char X;
	unsigned char Y;
	unsigned char Z;
};

static_assert (sizeof(S200) == 0x3, "ERROR SIZE S200");


#endif // !__S200_H_

