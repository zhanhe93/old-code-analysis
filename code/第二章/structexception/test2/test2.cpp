#include <stdio.h>
#include <windows.h>

int gi = 0;

EXCEPTION_DISPOSITION __stdcall ErrorHandler(PEXCEPTION_RECORD PtrExceptionRecord, void * PtrSEH, PCONTEXT PtrContext, void * PtrDispatcherContext)
{
	printf("hello error\n");
	PtrContext->Eax = (DWORD)&gi;
	return ExceptionContinueExecution;//�ó���������У���ֹͣ
}

void main()
{	
	char input;
	input = getchar();
	fflush(stdin);
    if (input == '1')
		goto compilerexcept;
	__asm
	{  //��ջ�������쳣����ڵ�*************************
		xor eax, eax
		push ErrorHandler;
		push fs:[eax]
		mov fs:[eax], esp//******************************

	};
	input = getchar();
	if (input != '0')
		printf("ok\n");
	else
		__asm
	{
		xor eax, eax
			mov [eax], 0;//д�յ�ַ�������쳣������������ת������
	}

Normal:
	__asm
	{
		pop ecx //��ǰһ���ڵ�ĵ�ַ����ecx
			xor eax , eax
			mov fs:[eax], ecx //��ǰһ���ڵ�ĵ�ַ��Ϊ�׽ڵ��ַ����fs:[0]
			pop ecx		
			//****************************
	};
   return;

	

compilerexcept:	
	try
	{
		throw 1;
		int i = 0;
		int b = 4 / i;
		__asm xor eax, eax
			__asm mov [eax], 0;
	}
	catch (...)
	{
		gi = 12;
	}
	
		//  Sleep(10000);
}