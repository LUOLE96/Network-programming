#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UDP_TEST_PORT 50001
#define UDP_SERVER_IP "127.0.0.1"

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
    addr.sin_addr.s_addr = inet_addr(UDP_SERVER_IP);

    while(1){
        bzero(buffer,sizeof(buffer));
        printf("please enter a string to send to server\n");

        len = read(STDIN_FILENO,buffer,sizeof(buffer));

        sendto(sockfd,buffer,len,0,(struct sockaddr *)&addr,addr_len);

        len = recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&addr_len);

        printf("Receive from server : %s\n",buffer);
    }
    return 0;
}
