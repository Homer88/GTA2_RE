// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <iostream>
//#include <cstdlib>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//#include <assert.h>

#include "detours.h"
#include "pch.h"
//  файлы конфигурации 
#include "InitMapGM.h"

#include "cDirectX.h"
#include "cGang.h"
#include "cGangs.h"
#include "cMapGm.h"
#include "cPed.h"

#include "cS8.h"
#include "cS19.h"
#include "cS20.h"
#include "cText.h"

#include "cWeapon.h"
#include "cWindow.h"

int FunMapGM();




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    LPVOID _InfoVersion = (LPVOID)0x004d0920;
    LPVOID _CopyNameGang= (LPVOID)0x0045DB40;
    //DirectX
    LPVOID _InitDiretX = (LPVOID)0x004031c0;
    //S20
    LPVOID _SetPararm_0x2ee0 = (LPVOID)0x004c4b70;
    ///S19
    LPVOID _SetPararam_0 = (LPVOID)0x004c4d60;
    
    //cText
    LPVOID _GetLanguageJapan = (LPVOID)0x00452E60;
    // Weapons
    LPVOID _FUN_00433810 = (LPVOID)0x00433810;
    LPVOID _Weapon_FUN_004cca10 = (LPVOID)0x004cca10;
    //LPVOID _constructS8 = (PVOID)0x0045DB40;
   // PVOID a, d;

    switch (ul_reason_for_call)
    {
        
    case DLL_PROCESS_ATTACH:
        MessageBox(0, "Load Dll!", 0, 0);
        DetourAttach(&_SetPararam_0, (PVOID)SetPararam_0);

        DetourAttach(&_InfoVersion, (PVOID)GetVersionLaunch);

        DetourAttach(&_CopyNameGang, (PVOID)CopyNameGang);
        DetourAttach(&_SetPararm_0x2ee0, (PVOID)SetPararm_0x2ee0);
        DetourAttach(&_SetPararam_0, (PVOID)SetPararam_0);
        DetourAttach(&_GetLanguageJapan, (PVOID)GetLanguageJapan);
        DetourAttach(&_FUN_00433810, (PVOID)SetTypeWeapons);
        DetourAttach(&_Weapon_FUN_004cca10, (PVOID)Weapon_FUN_004cca10);

        DetourAttach(&_InitDiretX, (PVOID)InitDiretX);
        FunMapGM();
        
        // Требуется реверсить
        //DetourAttach(&_constructS8, (PVOID)constructS8);
        //DetourAttach(&a, d);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



int FunMapGM()
{
    DetourAttach(&_LoadFileResurce     ,  (PVOID)LoadFileResurce);
    DetourAttach(&_SetSaveFile         ,  (PVOID)SetSaveFile);
    DetourAttach(&_SetPlayerArena      ,  (PVOID)SetPlayerArena);
    DetourAttach(&_SetSaveFile         ,  (PVOID)SetSaveFile);
    DetourAttach(&_SetPlayerArena      ,  (PVOID)SetPlayerArena);
    DetourAttach(&_SetBonusStage       ,  (PVOID)SetBonusStage);
    DetourAttach(&_Set_FUN_0045E4B0    ,  (PVOID)Set_FUN_0045E4B0);
    DetourAttach(&_SetPlayerSlotSave   ,  (PVOID)SetPlayerSlotSave);
    DetourAttach(&_SetBonus            ,  (PVOID)SetBonus);
    return 0;
};