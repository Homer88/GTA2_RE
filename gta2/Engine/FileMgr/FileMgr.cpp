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