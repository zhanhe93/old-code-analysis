// ctrlshell.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <windows.h>


void main()
{
	STARTUPINFOA si; 	
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));	
	si.dwFlags = STARTF_USESTDHANDLES;
	//si.wShowWindow = SW_HIDE;
	si.hStdInput = (HANDLE)123456;
	si.hStdOutput = (HANDLE)888888;
	si.hStdError = (HANDLE)654321;
	//Ҫ��3��������滻��Ҫ�����滻������ֻ�滻һ���֡�
	if (!CreateProcessA(NULL, "myprg.exe", NULL, NULL, true, CREATE_DEFAULT_ERROR_MODE
		, NULL, NULL, &si, &pi))
	{
		printf("cannot create myprg.exe\n");
		return;
	}	
	getchar();
}

