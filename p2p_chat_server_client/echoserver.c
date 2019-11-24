#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/*
 *实现点对点聊天,服务器或客户端其中一个退出，对方也能立即退出
 * /
void hander(int sig)
{
    printf("recv a sig = %d\n",sig);
    exit(EXIT_SUCCESS);
}

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
	pid_t pid;

	if((conn = accept(listenfd,(struct sockaddr *)&peeraddr,&peerlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("connect ip : %s,port : %d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
	
	pid = fork();
	if(pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(pid == 0){
                signal(SIGUSR1,hander);
		char sendbuf[1024] = {0};
                while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL){
                    write(conn,sendbuf,strlen(sendbuf));
                    memset(sendbuf,0,sizeof(sendbuf));
		}
                printf("child process exit\n");
		exit(EXIT_SUCCESS);
	}
	else{
		char recvbuf[1024];
		while(1){
			memset(recvbuf,0,sizeof(recvbuf));
			int ret = read(conn,recvbuf,sizeof(recvbuf));
			if(ret == -1){
				perror("read");
				exit(EXIT_FAILURE);			
			}
                        else if(ret == 0){
                                printf("peer close\n");
                                break;
                         }
			fputs(recvbuf,stdout);
		}
                printf("parent process exit\n");
                kill(pid,SIGUSR1);
                exit(EXIT_SUCCESS);
	}
	close(conn);
        close(listenfd);
    		
    return 0;
}
