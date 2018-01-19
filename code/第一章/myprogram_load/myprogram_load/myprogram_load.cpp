// myprogram_load.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdio.h>
#include <malloc.h>
#include <memory.h>

#define RELOCATION_ITEM_SIZE sizeof(int)
#define RELOCATION_ITEMS_SIZE RELOCATION_ITEM_SIZE * 1 //ֻ��һ���ض�λ��
#define DATA_SEGMENT_LEN 1 * sizeof(int)//ֻ��һ������
#define CODE_SEGMENT_LEN MOV_CODE_LEN + RET_LEN //movָ��Ϊ1����һ��retָ��
#define MOV_CODE_LEN 10
#define RET_LEN 1
#define RET_CODE 0xc3
#define PROGRAM_LEN sizeof(PrgHdr) + RELOCATION_ITEMS_SIZE + DATA_SEGMENT_LEN + CODE_SEGMENT_LEN

struct PrgHdr{
	int imageBase;//����ϣ�������صĵ�ַ
	int mainEntryOffset;//��������Գ���ͷ����ƫ����
	int relocationCount;//�ض�λ����Ŀ  
};


void buildCode(char * codeStart, int varAddress)
{
	//mov [00403374h],12345678h�Ļ����� C7 05 74 33 50 00 78 56 34 12������c7 05��ʾmov����3~6�Լ�Ϊ����ֵ��ַ����4�Լ�Ϊ������ֵ��
	//����movָ����---
	codeStart[0] = 0xc7;
	codeStart[1] = 0x05;
	//----
	int * pVarAddr;
	pVarAddr = (int *)&codeStart[2];
	*pVarAddr = varAddress;//������ַ����
	int * pVar;
	pVar = (int *)&codeStart[6];
	*pVar = 0x12345678;//��������ֵ
    *(codeStart + MOV_CODE_LEN) = RET_CODE;//����retָ��
}

//����һ������飬����ͷ�����ض�λ�����ݶΡ������
void * makeProgram(int expectedBase)
{
	int relocationTbLen;
	struct PrgHdr * prg = (struct PrgHdr *)malloc(PROGRAM_LEN);
	prg->imageBase = expectedBase;
	prg->relocationCount = 1;
	relocationTbLen = (prg->relocationCount * RELOCATION_ITEM_SIZE);
	prg->mainEntryOffset = sizeof(struct PrgHdr) + relocationTbLen + DATA_SEGMENT_LEN;
	
	*(int *)(prg + 1) = prg->mainEntryOffset + 2;//��д�ض�λ�movָ�����Ϊc7 05�����ֽ����Լ�2
	char * codeStart = (char *)prg + prg->mainEntryOffset;	
	int expectedGlobalVarAddress = expectedBase + sizeof(PrgHdr) + relocationTbLen;
	buildCode(codeStart, expectedGlobalVarAddress);    
	int * pGlobalVar = (int *)((char *)prg +  sizeof(PrgHdr) + relocationTbLen);
    * pGlobalVar = 1;//��ȫ�ֱ�������ֵΪ1�� �൱��c������int gi = 1;��������غ�ִ��main֮ǰ��ֵ
	return (void *)prg;
}

char gProgramLocation[PROGRAM_LEN];

void * makeProgramWillRelocate()
{
	return makeProgram(0x00400000);
}

void * makeProgramWithoutRelocate()
{
	return makeProgram((int)gProgramLocation);
}

//prgLoaded�������صĳ���ģ�����ʼ��ַ��prgInMem�������ص��ڴ����ʼ��ַ
void loadProgram(void * prgLoaded, void * prgInMem)
{
	memcpy(prgInMem, prgLoaded, PROGRAM_LEN);
	struct PrgHdr * prgHdr = (struct PrgHdr *)prgInMem;
	int expectedBase = prgHdr->imageBase;
	if (expectedBase == (int)prgInMem)
	{
		printf("need not relocate\n");
		return;
	}
	else
	{
		printf("need relocate, expected address is 0x%x, but actualAdress is 0x%x\n", expectedBase, prgInMem);
		printf("relocation count is %d\n", prgHdr->relocationCount);
		int *pRelocationItem = (int *)(prgHdr + 1);
		int offsetLoad = (int)prgInMem - expectedBase;
		for (int i = 0; i < prgHdr->relocationCount; i++)
		{
			int * pRelocateAddress = (int *)((char *)prgInMem + *pRelocationItem);
			int oldValue = * pRelocateAddress;
			* pRelocateAddress = oldValue + offsetLoad;
			pRelocationItem ++;
			printf("make a relocation, the value from 0x%x to 0x%x\n", oldValue, * pRelocateAddress);
		}
		return;
	}
}

void runProgram(void * prgInMem)
{
	struct PrgHdr * prgHdr = (struct PrgHdr *)prgInMem;
	void * mainFunctionAddress = (void *)((char *)prgInMem + prgHdr->mainEntryOffset);
	_asm call mainFunctionAddress;
}

void printTheGlobalVar(void * prgInMem)
{
	int * pGlobalVar = (int *)((char *)prgInMem + sizeof(struct PrgHdr) + RELOCATION_ITEMS_SIZE);
	printf("global varable in the loaded program is 0x%x\n", * pGlobalVar);
}

void main()
{
	//������ӽ�չʾ�����Լ��ض�λ��Ч��
	void * prgLoaded = makeProgramWillRelocate();
	char prgLocation[PROGRAM_LEN];
	loadProgram(prgLoaded, prgLocation);
	printTheGlobalVar(prgLocation);
	runProgram(prgLocation);
	printTheGlobalVar(prgLocation);
	free(prgLoaded);
	//-------------

	//������ӽ�չʾ�����Լ����ض�λ��Ч��
	prgLoaded = makeProgramWithoutRelocate();
	loadProgram(prgLoaded, gProgramLocation);
	printTheGlobalVar(gProgramLocation);
	runProgram(gProgramLocation);
	printTheGlobalVar(gProgramLocation);
	free(prgLoaded);
	//-------------
}

