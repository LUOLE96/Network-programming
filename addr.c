#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	if(argc < 3)
	{
		perror("param must >= 3");
		return -1;
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	char ipbuf[16] = {0};
	inet_ntop(AF_INET,&addr.sin_addr.s_addr,ipbuf,sizeof(ipbuf));
	printf("ip = %s,port = %d\n",ipbuf,ntohs(addr.sin_port));

}
