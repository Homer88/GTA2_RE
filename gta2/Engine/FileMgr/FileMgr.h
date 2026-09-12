#ifndef __FILEMANAGER_H_
#define __FILEMANAGER_H_

#include <stdio.h> 


class FileMgr {
public:
	bool Status;

	FileMgr();
	~FileMgr();
	void FileOpen(char* filename, char * mode);
	void ReadFile(void * outbuffer, void * inBuffer);
	void ReadFile(void* buffer, size_t SizeRead);
	int SetFilePath(char* filename);
	FILE* WriteReadFile(const char* filename, const char* mode);
};
#endif // !__FILEMANAGER_H_