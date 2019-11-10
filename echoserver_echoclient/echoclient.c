#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int sock;
    if((sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in seraddr;
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(5188);
    //seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1",&servaddr.sin_addr);

    if(connect(sock,(struct sockaddr *)&seraddr,sizeof(seraddr)) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
    {
        write(sock,sendbuf,strlen(sendbuf));
        read(sock,recvbuf,sizeof(recvbuf));
        fputs(recvbuf,stdout);
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
    }
    close(sock);
    return 0;
}
