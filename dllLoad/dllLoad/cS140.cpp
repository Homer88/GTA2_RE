#include <string.h>
#include "cS140.h"





void consS140(S140* pS140) {

	pS140->field0 = 0;
	pS140->field2 = 0;
	pS140->field4 = 0;
	pS140->field6 = 0;
	memset(pS140->str, 0, sizeof(pS140->str));
}