// directchangeprivatemember.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdio.h>

class MyTest
{
private:
	int a;
	int b;
public:
	void setB(int v){ 
		b = v;
	}
	int getB(){
		return b;
	}
};
void main()
{
	MyTest o;
	o.setB(2);
	printf("b is %d\n", o.getB());
	*((int *)&o + 1) = 3;
	printf("b is %d\n", o.getB());
}

