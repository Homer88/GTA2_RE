#ifndef __PEDMANAGER__H__
#define __PEDMANAGER__H__

#include <assert.h>
#include <Windows.h>

#include "cPed.h"

struct PedManager{
	Ped* FirstPed;
	Ped* NextPed;
	Ped	 Ped[200];
	unsigned short CountPed;
	char uns;
	char uns2;
};

static_assert(sizeof(PedManager) == 0x203AC, "ERROR PED Manager");

static const  PedManager* ptrPedManager =(PedManager*)0x005e5bbc;


#endif