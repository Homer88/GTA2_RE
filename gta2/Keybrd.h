#ifndef __KEYBRD__H_
#define __KEYBRD__H_
#include <windows.h>
#include <winuser.h>
#include <stdio.h>

int  read_config_token(FILE* configureFile, short* token_buffer);



class Keyboard {
public:
	short CodeKey[256];
	int Layout;
	bool Status;
	Keyboard();
	int LoadKeyboard();



};




#endif // !__Keybrd__H_

