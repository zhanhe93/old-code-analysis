#include <stdio.h>
#include <windows.h>

int gi = 0;


EXCEPTION_DISPOSITION __stdcall ErrorHandler(PEXCEPTION_RECORD PtrExceptionRecord, void * PtrSEH, PCONTEXT PtrContext, void * PtrDispatcherContext)
{
	printf("hello error\n");
	DWORD pjmp = *(DWORD *)((char *)PtrSEH + 4);	
	DWORD p = pjmp + 5;
	PtrContext->Eip = p;
	return ExceptionContinueExecution;
	//_asm jmp p
}

void main()
{
		__asm
	{  //��ջ�������쳣����ڵ�*************************

		xor eax, eax
		push exc;
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
gotoNormal:
	_asm jmp Normal
exc:
	_asm jmp ErrorHandler

Normal:
	__asm
	{
		pop ecx //��ǰһ���ڵ�ĵ�ַ����ecx
			xor eax , eax
			mov fs:[eax], ecx //��ǰһ���ڵ�ĵ�ַ��Ϊ�׽ڵ��ַ����fs:[0]
			pop ecx		
			//pop ecx
			//****************************
	};
	getchar();
}

