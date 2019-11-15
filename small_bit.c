#include <stdio.h>

int main()
{
	int num = 0x01020304;
	char *pc = (char *)&num;
	int i;
	for(i = 0;i < 4;i++){
		printf("%p %x\n",pc++,*pc);	
	}
}
