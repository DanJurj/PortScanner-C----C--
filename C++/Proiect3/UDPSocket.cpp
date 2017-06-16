#pragma once
#include"UDPSocket.h"

UDPSocket::UDPSocket():CSocket(UDP)
{
}

Status UDPSocket::createSocket()
{
	if((Socket=socket(AF_INET,SOCK_DGRAM,0))==INVALID_SOCKET)
    {
       cout<<"Could not create socket : "<<WSAGetLastError();
	   throw new Exception(ERR_SOCKET,"eroare la crearea socket-ului");
		return EROARE;
    }
	return DONE;//socket creat
}

Status UDPSocket::SendData(const char* mesaj,int len)
{
	int rez;
	rez=sendto(Socket,mesaj,len,0,(SOCKADDR *)& addrTinta,sizeof(addrTinta));
    if(rez==SOCKET_ERROR)
	{
       throw new Exception(ERR_SEND,"eroare la TRIMITEREA mesajului");
    }
	return DONE;
}

Status UDPSocket::RecvData()
{
	timeval tv;
	tv.tv_sec=10000;//10 sec
	int rez;
	rez=setsockopt(Socket,SOL_SOCKET,SO_RCVTIMEO,(const char *) &tv,sizeof(tv));
    if (rez==SOCKET_ERROR)
	{
      cout<<"Setare timeout pt recvfrom eroare: "<<WSAGetLastError()<<"\n";
	  return EROARE;
    }
	char recvMsg[24];
	int lunMsg=24;
	int len=sizeof(addrTinta);
    rez=recvfrom(Socket,recvMsg,lunMsg,0,(SOCKADDR *)& addrTinta,&len);
    if(rez==SOCKET_ERROR) 
	{
        //cout<<"recvfrom s-a terminat cu eroarea: "<<WSAGetLastError()<<"\n";
		if(WSAGetLastError()==WSAETIMEDOUT)
			return TIMEOUT;
		else
			if(WSAGetLastError()==WSAECONNRESET)
				return DISCONNECTED;
		return EROARE;
    }
	return DONE;//primeste raspuns
}

Status UDPSocket::conectToServer(const char *ipAddress,int port)
{
	return DONE;
}

UDPSocket::~UDPSocket()
{
	CloseConnection();
}
