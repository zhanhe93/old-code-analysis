// test.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "../inc/common.h"
#include <stdio.h>

void main()
{
	Parent* p = createObj();
	p->setNum(2);
	printf("num=%d\n", p->getNum());
}

