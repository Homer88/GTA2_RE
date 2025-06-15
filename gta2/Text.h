#ifndef __TEXT_H_
#define __TEXT_H_


class Text {
public:
	char Language = 'e';
	char *Base;
	int NumberOfElements;

	void* Bsearch(const void* pKey);
};




#endif
