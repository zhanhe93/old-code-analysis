// testscanf.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include<stdio.h>

void main()
{
	char cmd[30];
	while (1)
	{
		scanf("%[^\n]", cmd);
		printf("%s\n", cmd);
	}
}

