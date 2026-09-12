
#ifndef __GUI_H_
#define __GUI_H_


class GUI{
    public:
		unsigned char Element;
		unsigned char PlayerArena;
		unsigned short X;
		unsigned short Y;
		wchar_t TextMenuElementArray[50];
		unsigned short dX;
		unsigned short dY;
		unsigned int SpriteInterface;
		GUI();


    // 0x004C5FD0
    int SetInteface(void);
};

#endif // !__GUI_H_