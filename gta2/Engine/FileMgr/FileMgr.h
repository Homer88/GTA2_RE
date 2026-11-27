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

	// IDA-compatible guarded wrappers over a single active FILE* stream.
	// Original uses global gFileStream/unk_5D25F4; we keep a RE-local static stream.
	static FILE* FileOpenStatic(const char* filename, const char* mode = "rb");
	static int CloseFile();
	static int Seek(int offset); // IDA: Seek(this,size*) reads *size and fseek(...,1)
	static int SeekPtr(const void* sizePtr);
	static size_t Read(void* buffer, size_t* sizePtr);
	static int ReadLine(void* buffer, size_t* sizePtr); // IDA 0x403000: Fread(buffer,gStream,*size,1)==1
	static int ReadLine(void* /*ctx*/, char* buffer, size_t* sizePtr) { return ReadLine(buffer, sizePtr); } // compat
	static size_t ReadSize(void* buffer, size_t size);
	static bool IsOpen();
	static FILE* GetStream();
	static const char* GetPath();
};


extern FileMgr* gFileMgr;
#endif // !__FILEMANAGER_H_