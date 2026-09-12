#include "FileMgr.h"

FileMgr gFileMgr;


FileMgr::FileMgr() {
};
FileMgr::~FileMgr() {};

int FileMgr::SetFilePath(char* filename) {

	return 0;
}

FILE* FileMgr::WriteReadFile(const char* filename, const char* mode) {

	FILE* file=fopen(filename,mode);
	

	return file;
};
void FileMgr::FileOpen(char* filename, char* mode) {};

void FileMgr::ReadFile(void* outbuffer, void* inBuffer) {};
void FileMgr::ReadFile(void* buffer, size_t SizeRead) {};