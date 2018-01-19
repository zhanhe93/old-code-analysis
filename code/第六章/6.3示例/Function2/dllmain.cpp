// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"

#include <windows.h>
#include <iostream>
using namespace std;

const int FUNC_ID = 2;

extern "C" __declspec(dllexport) void Print(void)
{
	cout << "Hello China!" << endl;
}

extern "C" __declspec(dllexport) void Help(void)
{
	cout << "Function ID " << FUNC_ID << " : This function will print hello china." << endl;
}

extern "C" __declspec(dllexport) int GetID(void)
{
	return FUNC_ID;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) 
{
	HANDLE g_hModule;
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = (HINSTANCE)hModule;
		break;

	case DLL_PROCESS_DETACH:
		g_hModule=NULL;
		break;

	case DLL_THREAD_ATTACH:
		g_hModule = (HINSTANCE)hModule;
		break;

	case DLL_THREAD_DETACH:
		g_hModule = NULL;
		break;
	}
	return true;
}