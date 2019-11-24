#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void hander(int sig){
    printf("recv sig = %d\n");
    exit(EXIT_SUCCESS);
}

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

    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        char recvbuf[1024] = {0};
        while (1) {
           memset(recvbuf,0,sizeof(recvbuf));
           int ret = read(sock,recvbuf,sizeof(recvbuf));
           if(ret < 0){
               perror("recv");
               exit(EXIT_FAILURE);
           }
           else if(ret == 0){
               printf("peer close");
               break;
           }
           fputs(recvbuf,stdout);
        }
        printf("child process exit\n");
        kill(getppid(),SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    else if(pid > 0){
        signal(SIGUSR1,hander);
        char sendbuf[1024] = {0};
        while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
        {
            write(sock,sendbuf,strlen(sendbuf));
            memset(sendbuf,0,sizeof(sendbuf));
        }
        printf("parent process exit\n");
        exit(EXIT_SUCCESS);
    }

    close(sock);
    return 0;
}
