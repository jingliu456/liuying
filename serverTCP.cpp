#define WIN32_LEAN_AND_MEAN	
#include<windows.h>
#include<WinSock2.h>
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
int main()
{
    WORD ver = MAKEWORD(2, 2);
    WSADATA dat;
    WSAStartup(ver, &dat);
    SOCKET _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in _sin = { };
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(4567);
    _sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if (SOCKET_ERROR == bind(_socket, (sockaddr*)&_sin, sizeof(_sin)))
    {
        printf("服务器绑定端口失败\n");
    }
    else
    {
        printf("111服务器绑定端口成功\n");
    }
    if (SOCKET_ERROR == listen(_socket,5))
    {
        printf("服务器监听失败\n");
    }
    else
    {
        printf("服务器监听成功\n");
    }
    sockaddr_in clientaddr = { };
    int caddr_len = sizeof(clientaddr);
    SOCKET  csock = INVALID_SOCKET;
    char msgbuf[256] = "hello, this is server\n";
    csock = accept(_socket, (sockaddr*)&clientaddr, &caddr_len);
    if (INVALID_SOCKET == csock)
    {
        printf("错误，接收到无效客户端SOCKET\n");
    }
    printf("新客户端加入，IP=%s\n", inet_ntoa(clientaddr.sin_addr));
    send(csock, msgbuf, strlen(msgbuf) + 1, 0);
    char recvbuf[128] = {};
    while (true)
    {
        int nlen = recv(csock, recvbuf, 128, 0);
        printf("接收到客户端命令：%s\n", recvbuf);
        if (nlen <= 0)
        {
            printf("客户端已经退出\n");
            break;
        }
        if (0 == strcmp(recvbuf, "getname"))
        {
            char cmpbuf[] = "liuying";
            send(csock, cmpbuf, strlen(cmpbuf) + 1, 0);
        }
        else if (0 == strcmp(recvbuf, "getage"))
        {
            char cmpbuf[] = "80";
            send(csock, cmpbuf, strlen(cmpbuf) + 1, 0);
        }
        else
        {
            char cmpbuf[] = "???";
            send(csock, cmpbuf, strlen(cmpbuf) + 1, 0);
        }
        
    }
    
    WSACleanup();
    return 0;
}
