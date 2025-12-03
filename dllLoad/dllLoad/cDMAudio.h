#ifndef __cDMAudio__H_
#define __cDMAudio__H_

#include <assert.h>

struct DMAudio
{
	//CameraOrPhysics* CameraOrPhysics;
	void* field0;
	char gap4;
	char field_5;
	char field_6;
	char field_7;
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	char field_C;
	char field_D;
	char field_E;
	char field_F;
	char field_10;
	char field_11;
	char field_12;
	char field_13;
	char field_0;
	char field_15[1000];
	char field_3FD[100];
	char field_461[1000];
	char field_849[500];
	char field_A3D[2000];
	char field_120D[1000];
	char field_15F5[1000];
	char field_19DD[400];
	char field_1B6D[500];
	char field_1D61[2000];
	char field_2531[1000];
	char field_2919[1000];
	char field_2D01[500];
	char field_2EF5[50];
	char field_2F27[25];
	char field_2F40[20];
	char field_2F54[10];
	char field_2F5E[10];
	char field_2F68[10];
	char field_2F72;
	char field_2F73;
	char field_2F74;
	char field_2F75;
	char field_2F76;
	char field_2F77;
	char field_2F78;

};

static_assert(sizeof(DMAudio)==12156, "Error Size MapGm");


#endif
