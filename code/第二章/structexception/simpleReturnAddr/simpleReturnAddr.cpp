#include <stdio.h>
#include <windows.h>

int gi = 0;

DWORD normalAddr;

EXCEPTION_DISPOSITION __stdcall ErrorHandler(PEXCEPTION_RECORD PtrExceptionRecord, void * PtrSEH, PCONTEXT PtrContext, void * PtrDispatcherContext)
{
	printf("hello error\n");
	PtrContext->Eip = normalAddr;
	return ExceptionContinueExecution;//�ó���������У���ֹͣ
}

void main()
{
	_asm mov normalAddr, offset Normal
	__asm
	{  //��ջ�������쳣����ڵ�*************************
		xor eax, eax
		push ErrorHandler;
		push fs:[eax]
		mov fs:[eax], esp//******************************
	};
	char input;

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
	getchar();
}

