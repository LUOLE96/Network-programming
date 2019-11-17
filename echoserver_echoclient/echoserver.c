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
    int listenfd;
    if((listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in seraddr;
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(5188);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1",&servaddr.sin_addr);

	int on = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) < 0){
		perror("setsockopt");
		exit(EXIT_FAILURE);	
	}

    if(bind(listenfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(listenfd,SOMAXCONN) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    int conn;
    if((conn = accept(listenfd,(struct sockaddr *)&peeraddr,&peerlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char recvbuf[1024] = {0};
    while(1)
    {
        memset(recvbuf,0,sizeof(recvbuf));
        int ret = read(conn,recvbuf,sizeof(recvbuf));
        fputs(recvbuf,stdout);
        write(conn,recvbuf,ret);
    }
    close(conn);
    close(listenfd);
    return 0;
}
