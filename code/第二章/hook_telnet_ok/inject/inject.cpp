// inject.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include <windows.h>
#include "../include/detours.h"

extern "C" BOOL __declspec(dllexport) inject(HANDLE hProcess, LPCSTR lpDllName)
{
	return DetourContinueProcessWithDllA(hProcess, lpDllName);
}


