#ifndef __MOVIE_H_
#define __MOVIE_H_
#include <windows.h>
struct VideoMode
{
	int FullWidth, FullHeight, ColorBit;
};
class Movie
{
	public:
	int WindowWidth;
	int WindowHeight;
	int Status;
	int field4;
	Movie();
	~Movie();

	void Vid_FlipBuffers();
	void Vid_FlipBuffers(int);
	void Vid_ClearScreen(int*, int, int, int, int, int, int, int);
	bool CheckMode(int FullWidth, int FullHeight, int ColorBit);
	bool SetMode(HWND pHWND, bool pVideoMode);
};

extern Movie* gMovie;
#endif