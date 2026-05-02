#ifndef __MOVIE__H_
#define __MOVIE__H_

class Movie {

public:
	bool Status;
	int field4;

	void CloseScreen();
	bool CheckMode(int FullWidth, int FullHeight, int Bit);
	bool SetMode(HWND hWND, bool param);

};
#endif // !_Movie__H_

