#ifndef __FILEMANAGER_H_
#define __FILEMANAGER_H_

#include <windows.h>
#include <stdio.h> 


class FileMgr {
public:
	bool Status;

	FileMgr();
	~FileMgr();
	FILE* FileOpen(char* filename, char * mode);
	FILE* FileOpen(char* filename);
	void ReadFile(void * outbuffer, void * inBuffer);
	void ReadFile(void* buffer, size_t SizeRead);
	int SetFilePath(char* filename);
	FILE* WriteReadFile(const char* filename, const char* mode);
	void LoadFronSprites();
	int  ReadToken(FILE* f, WORD* out);
};


extern FileMgr* gFileMgr;
#endif // !__FILEMANAGER_H_