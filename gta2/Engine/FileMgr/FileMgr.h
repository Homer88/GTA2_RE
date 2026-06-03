#ifndef __FILEMANAGER_H_
#define __FILEMANAGER_H_

#include <stdio.h> 


class FileMgr {
public:
	bool Status;

	FileMgr();
	~FileMgr();

	int SetFilePath(char* filename);
	FILE* WriteReadFile(const char* filename, const char* mode);
};
#endif // !__FILEMANAGER_H_