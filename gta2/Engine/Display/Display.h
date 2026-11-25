#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "../../Game/Viewport/Viewport.h"
class Display {
// TODO ���� ������ ��� ������ ���  � ����� ����� ������ � ��������.


public:
	Display();
	~Display();
    void initModes(void);
};

extern Display *gDisplay;



#endif // !__Display_H__

