#ifndef __MOVIE_H_
#define __MOVIE_H_
class Movie{
	public:
	int WindowWidth;
	int WindowHeight;
	Movie();
	~Movie();
	void Vid_FlipBuffers();
	void Vid_FlipBuffers(int);
	void Vid_ClearScreen(int*, int, int, int, int, int, int, int);
	
	
	
};


extern Movie gMovie;
#endif