#define WIN32_LEAN_AND_MEAN	
#include<windows.h>
#include<WinSock2.h>
#include <iostream>

int main()
{
    WORD ver = MAKEWORD(2, 2);
    WSADATA dat;
    WSAStartup(ver, &dat);
    SOCKET _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == _socket)
    {
        printf("建立socket失败\n");
    }
    else
    {
        printf("建立socket成功\n");
    }
    sockaddr_in _sin = { };
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(4567);
    _sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int ret = connect(_socket, (sockaddr*)&_sin, sizeof(_sin));
    if (SOCKET_ERROR == ret)
    {
        printf("socket连接失败\n");
    }
    else
    {
        printf("socket连接成功\n");
    }
    char resgbuf[256] = {};
    int nlen = recv(_socket, resgbuf, 256, 0);
    if (nlen > 0)
    {
        printf("接收到服务器数据：%s\n", resgbuf);
    }
    while (true)
    {
        char cmdbuf[128] = {};
        scanf("%s", cmdbuf);
        if (0 == strcmp(cmdbuf, "exit"))
        {
            printf("收到命令，已退出");
            break;
        }
        else
        {
            send(_socket, cmdbuf, strlen(cmdbuf)+1, 0);
        }
        char resgbuf[256] = {};
        int nlen = recv(_socket, resgbuf, 256, 0);
        if (nlen > 0)
        {
            printf("接收到服务器数据：%s\n", resgbuf);
        }
    }
    WSACleanup();
    system("pause");
    return 0;
}
