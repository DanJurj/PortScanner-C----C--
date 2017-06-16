#pragma once
#include"CSocket.h"

CSocket::CSocket()
{
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cout<<"Failed. Error Code : "<<WSAGetLastError();
		throw new Exception(ERR_SOCKET,"eroare la initializarea Winsock-ului");
    }
     
}

CSocket::CSocket(Type tip)
{
	tip_protocol=tip;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cout<<"Failed. Error Code : "<<WSAGetLastError();
		throw new Exception(ERR_SOCKET,"eroare la initializarea Winsock-ului");
    }
}

void CSocket::setAddrTinta(const char *ipAddress,int port)
{
	addrTinta.sin_addr.s_addr = inet_addr(ipAddress);
    addrTinta.sin_family = AF_INET;
    addrTinta.sin_port = htons(port);
}

void CSocket::CloseConnection()
{
	closesocket(Socket);
}

CSocket::~CSocket()
{
	WSACleanup();
}
