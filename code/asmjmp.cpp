// asmjmp.cpp : �������̨Ӧ�ó������ڵ㡣
//

int i, gi;
void * address;
void main()
{	  		
		_asm {
			mov address, offset _lb1;
			jmp address;
			}
		i = 2;
		_lb1:
		gi = 12;
}

