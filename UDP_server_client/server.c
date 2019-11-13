//UDP都是以数据报的形式进行发送和接收的，而TCP是以数据流的形式进行发送和接收的。
//数据报和数据流，这两者要区分开来。

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UDP_TEST_PORT 50001

int main(int argc,char **argv)
{
    struct sockaddr_in addr;
    int sockfd,len = 0;
    int addr_len = sizeof(struct sockaddr_in);
    char buffer[256];

    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
        perror("socket");
        exit(1);
    }

    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_TEST_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd,(struct sockaddr *)&addr,sizeof(addr)) < 0){
        perror("bind");
        exit(1);
    }

    while(1){
        bzero(buffer,sizeof(buffer));
        len = recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&addr_len);

        printf("Received a string from client %s,string is : %s\n",inet_ntoa(addr.sin_addr),buffer);

        sendto(sockfd,buffer,len,0,(struct sockaddr *)&addr,addr_len);
    }

    return 0;
}
