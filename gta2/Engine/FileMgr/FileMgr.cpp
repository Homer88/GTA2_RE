#include "FileMgr.h"

FileMgr *gFileMgr;


FileMgr::FileMgr() {
};
FileMgr::~FileMgr() {};

int FileMgr::SetFilePath(char* filename) {

	return 0;
}
void FileMgr::LoadFronSprites() {

}
FILE* FileMgr::WriteReadFile(const char* filename, const char* mode) {

	FILE* file=fopen(filename,mode);
	

	return file;
};
FILE* FileMgr::FileOpen(char* filename, char* mode) {
	return (FILE*)NULL;
};
FILE* FileMgr::FileOpen(char* filename) {
	return (FILE*)NULL;
};
void FileMgr::ReadFile(void* outbuffer, void* inBuffer) {};
void FileMgr::ReadFile(void* buffer, size_t SizeRead) {};