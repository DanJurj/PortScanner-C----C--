#pragma once
#include"TCPSocket.h"

TCPSocket::TCPSocket():CSocket(TCP)
{
}

Status TCPSocket::createSocket()
{
	if((Socket= socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
    {
       cout<<"Could not create socket : "<<WSAGetLastError();
	   throw new Exception(ERR_SOCKET,"eroare la crearea socket-ului");
    }
	return DONE;//socket-ul a fost creat
}

Status TCPSocket::SendData(const char*,int )
{
	return DONE;
}

Status TCPSocket::RecvData()
{
	return DONE;
}

Status TCPSocket::conectToServer(const char *ipAddress, int port)
{ 
	//"216.58.214.195"
	setAddrTinta(ipAddress,port);
	if(connect(Socket,(struct sockaddr *)&addrTinta,sizeof(addrTinta))<0)
    {
		return EROARE;
    }
	return DONE;
}

TCPSocket::~TCPSocket()
{
	CloseConnection();
}
