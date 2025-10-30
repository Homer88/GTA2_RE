#ifndef __S36_H_
#define __S36_H_

#include <assert.h>


struct  S36{
	int uns;
	int uns1;
	int uns2;
};

static_assert (sizeof(S36) == 0xc, "ERROR SIZE STRUCTURE S36");




#endif // !__S36_H_

