#pragma once
#include"CSocket.h"
class UDPSocket:public CSocket
{
public:
	UDPSocket();
	Status createSocket();
	Status SendData(const char*,int );
	Status RecvData();
	Status conectToServer(const char *ipAddress,int port);
	~UDPSocket();
};