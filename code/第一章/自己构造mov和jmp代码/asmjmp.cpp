// asmjmp.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <malloc.h>

int gi;
void * address;

void * buildCode()
{
	//����Ҫ�����Ĵ�������
	// mov gi, 18
	// jmp address;

	//mov gi, ����ֵ������ָ����10���ֽ����C7 05 gi�ĵ�ַ���ֽ� ����ֵ�������ֽ�
	//jmp address;6�ֽڣ�ǰ����Ϊff 25����4�ֽ�Ϊ��ַ
	//���������Ҫ����16���ֽ�
	char * code = (char *)malloc(16);
	char * pMov = code;
	char * pJmp = code + 10;
	char * pAddress;
	//mov gi, 18
	pMov[0] = 0xc7;
	pMov[1] = 0x05;
	pAddress = pMov + 2;
	*((int *)pAddress) = (int)&gi;
	*((int *)(pAddress + 4)) = 18;
	//jmp address
	pJmp[0] = 0xff;
	pJmp[1] = 0x25;
	*((int *)(&pJmp[2])) = (int)&address;
	return code;
}

void main()
{	
	void * code = buildCode();
	_asm {
		mov address, offset _lb1;	
	}
	gi = 12;
	printf("gi = %d\n", gi);
	_asm jmp code;//ִ�������Լ������Ĵ���
	gi = 13;
	_lb1:
	printf("gi = %d\n", gi);//��ӡ�Ľ��Ϊ18��������12
	getchar();
}

