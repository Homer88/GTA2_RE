#include "Movie.h"

Movie* gMovie;

Movie::Movie() {}
Movie::~Movie() {}

void Movie::Vid_FlipBuffers() {}
void Movie::Vid_FlipBuffers(int) {}
void Movie::Vid_ClearScreen(int* a, int b, int c, int d, int e, int f, int s, int t ) {}
bool Movie::CheckMode(int FullWidth, int FullHeight, int ColorBit) {
	VideoMode pVideoMode;
	pVideoMode.FullWidth = FullWidth;
	pVideoMode.FullHeight = FullHeight;
	pVideoMode.ColorBit = ColorBit;
	return &pVideoMode;
}
bool Movie::SetMode(HWND pHWND, bool pVideoMode) {
	return true;
}