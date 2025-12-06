#ifndef __TEXT_H_
#define __TEXT_H_


class Text {
public:
	char Language = 'e';
	char *Base;
	int NumberOfElements;
	Text();
	~Text();
	void* Bsearch(const void* pKey);
};

#endif
