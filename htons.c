#include <arpa/inet.h>
#include <stdio.h>

int main()
{
	short port = 10000;
	short big_port = htons(port);
	printf("port = %d,big_port = %d\n",port,big_port);

	short small_port = ntohs(big_port);
	printf("big_port = %d,small_port = %d\n",big_port,small_port);
	

}
