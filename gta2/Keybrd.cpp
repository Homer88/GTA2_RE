
#include "Global.h"


#include "Keybrd.h"

Keyboard gKeyboard;

enum  Layout {
	ENGLISH_LAYOUT = 0u,
	FRENCH_LAYOUT = 1u,
	GERMAN_LAYOUT = 2u,
	ITALIAN_LAYOUT = 3u,
	SPANISH_LAYOUT = 4u,
	PORTUGUESE_LAYOUT = 5u,
	jap_kb = 6u, //под вопросом
	rus_kb = 7u,  ///добавляем новый 
};

enum KEYBOARD {
	KEYBOARD_GERMAN=7,
	KEYBOARD_SPANISH=10,
	KEYBOARD_FRENCH=12,
	KEYBOARD_ITALIAN=16,
	KEYBOARD_PORTUGUESE=22,
};

Keyboard::Keyboard() {

	this->Status = true;
	this->Layout = 0;
	memset(this->CodeKey, 0, 512);
}

int Keyboard::LoadKeyboard() {
	
	this->Layout = ENGLISH_LAYOUT;
	LPSTR pwszKLID;
	char layoutName[KL_NAMELENGTH];

	GetKeyboardLayoutNameA(layoutName);
	int layoutId;

	sscanf(layoutName, "%x", &layoutId);

	char *keyboardConfigPath;
	switch (layoutId) {
	case KEYBOARD_GERMAN:
		this->Layout = GERMAN_LAYOUT;
		keyboardConfigPath = "data\\keyboard\\ger_kb.cfg";
		break;
	case KEYBOARD_SPANISH:
		this->Layout = SPANISH_LAYOUT;
		keyboardConfigPath = "data\\keyboard\\spa_kb.cfg";
		break;
	case KEYBOARD_FRENCH:
		this->Layout = FRENCH_LAYOUT;
		keyboardConfigPath = "data\\keyboard\\fre_kb.cfg";
		break;

	case KEYBOARD_ITALIAN:
		this->Layout = ITALIAN_LAYOUT;
		keyboardConfigPath = "data\\keyboard\\ita_kb.cfg";
		break;

	case KEYBOARD_PORTUGUESE:
		this->Layout = PORTUGUESE_LAYOUT;
		keyboardConfigPath = "data\\keyboard\\por_kb.cfg";
		break;

	default:  // Английский как вариант по умолчанию
		this->Layout = ENGLISH_LAYOUT;
		keyboardConfigPath = "data\\keyboard\\eng_kb.cfg";
		break;

	}

	FILE *configureFile = fopen(keyboardConfigPath, "r");
	if (!configureFile) {
		DebugLog(0x97u, "keybrd.cpp", 172);
		return -1;
	}
	
	short v11[6];

	int count = 256;
	do
	{
		read_config_token(configureFile, v11);
		if (v11[0] == 126)
			this->CodeKey[0] = 0;
		else
			this->CodeKey[0] = v11[0] != 96 ? 0 : v11[1];
		//pKeyboard = (Keybord*)((char*)pKeyboard + 2);
		--count;
	} while (count);

	fclose(configureFile);

	return 0;
}


int  read_config_token(FILE *configureFile, short *token_buffer){
	int c = 0;
	int i=0;

	while (i < 255) {
		c = getc(configureFile);
		// Условия остановки: EOF, перевод строки (10), пробел (32)
		if (c == EOF || c == 10 || c == 32)
			break;
		token_buffer[i++] = (short)c;
	}
	token_buffer[i] = 0;

	return c;
}

