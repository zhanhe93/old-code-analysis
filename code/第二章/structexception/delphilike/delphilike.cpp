#include <stdio.h>
#include <windows.h>

int gi = 0;


EXCEPTION_DISPOSITION __stdcall ErrorHandler(PEXCEPTION_RECORD PtrExceptionRecord, void * PtrSEH, PCONTEXT PtrContext, void * PtrDispatcherContext)
{
	printf("hello error\n");
	DWORD * pCatchAddr = (DWORD *)((char *)PtrSEH + 8);	
	DWORD CatchAddr = *pCatchAddr;
	_asm
	{
		mov esp, PtrSEH;
		jmp CatchAddr;
	}
	return ExceptionContinueExecution;//�ó���������У���ֹͣ
}

void main()
{
	int i;
	__asm
	{  //��ջ�������쳣����ڵ�*************************

		xor eax, eax
		push ebp
		push offset Catch
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
	i = 0;
	__asm
	{
		pop ecx //��ǰһ���ڵ�ĵ�ַ����ecx
		xor eax , eax
		mov fs:[eax], ecx //��ǰһ���ڵ�ĵ�ַ��Ϊ�׽ڵ��ַ����fs:[0]
		pop ecx		
		pop ecx
		pop ecx
			//****************************
	};
	_asm jmp Ok;
Catch:
	__asm
	{
		pop ecx //��ǰһ���ڵ�ĵ�ַ����ecx
		xor eax , eax
		mov fs:[eax], ecx //��ǰһ���ڵ�ĵ�ַ��Ϊ�׽ڵ��ַ����fs:[0]
		pop ecx		
		pop ecx
		pop ebp //�ָ�ebp��i������Ѱַ��
			//****************************
	};
	i = 1;
Ok:
	printf("i = %d\n", i);
	getchar();
}

