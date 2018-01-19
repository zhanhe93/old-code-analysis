// ThreadClass.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "Thread.h"
#include <stdio.h>
#include <windows.h>

class TPrintThread : public TThread{
protected:
	void Execute() {
		Sleep(5000);
		printf("hello I am in a thread\n");
		FReturnValue = 1;
	};
public:
	TPrintThread(): TThread(){};
};



void main()
{
	TPrintThread * Thd;
	Thd = new TPrintThread();
	printf("please input\n");
	Thd->Run();
	getchar();
	printf("I am in main thread\n");
	getchar();
	delete Thd;//we don't use waitfor, because we wait it in destructor.
}

