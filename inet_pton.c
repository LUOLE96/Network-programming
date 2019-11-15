#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

int main()
{
	const char *ipstr = "192.168.1.111";
	unsigned long lip = 0;
	if(inet_pton(AF_INET,ipstr,&lip) < 0){
		perror("inet_pton");
		return -1;
	}
	printf("ipstr = %s lip = %ld\n",ipstr,lip);

	char ipbuf[16] = {0};
	inet_ntop(AF_INET,&lip,ipbuf,sizeof(ipbuf));
	printf("lip = %ld,ipbuf = %s\n",lip,ipbuf);

	long net_ip = inet_addr(ipstr);
	printf("lip = %ld,net_ip = %ld\n",lip,net_ip);


}
