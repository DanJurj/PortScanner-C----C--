#pragma once
#include"CSocket.h"
class TCPSocket:public CSocket
{
public:
	TCPSocket();
	Status createSocket();
	Status SendData(const char*,int );
	Status RecvData();
	Status conectToServer(const char *ipAddress,int port);
	~TCPSocket();
};