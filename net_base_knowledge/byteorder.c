#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
    unsigned int x = 0x12345678;
    unsigned char *p = (unsigned char*)&x;

    printf("%0x_%0x_%0x_%0x_%0x\n",p[0],p[1],p[2],p[3]);//小端字节序(x86)

    unsigned int y = htonl(x);
    p = (unsigned char*)&y;
    printf("%0x_%0x_%0x_%0x\n",p[0],p[1],p[2],p[3]);//网络字节序总是规定为大端字节序

    unsigned long addr = inet_addr("192.168.0.100");
    printf("addr = %ud\n",ntohl(addr));

    struct in_addr ipaddr;
    ipaddr.s_addr = addr;
    printf("%s\n",inet_ntoa(ipaddr));

    return 0;
}
