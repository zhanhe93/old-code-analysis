// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

int gi;

void testfunc()
{

}

void main()
{
	void (*f)() = testfunc;
	gi = 12;
	testfunc();
}
