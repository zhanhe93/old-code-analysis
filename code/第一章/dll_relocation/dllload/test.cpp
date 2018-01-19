#include <stdio.h>
#include <windows.h>

typedef int (*SubPtr)(int, int);

void main()
{
	//����dll_relocation.dll��testdll.exe���Զ����ɵ�һ��Ŀ¼������dll����û��·����
	HMODULE h = LoadLibraryA("dll_relocation.dll");
	if (NULL == h)
	{
		printf("cannot load\n");
		return;
	}
	SubPtr fp = (SubPtr)GetProcAddress(h, "sub");
	if (NULL == fp)
	{
		printf("cannot get function sub\n");
		return;
	}	
	printf("3 - 2 = %d\n", fp(3, 2));
}