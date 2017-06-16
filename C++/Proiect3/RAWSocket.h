#pragma once
#include"Pachet.h"
#include"CSocket.h"
class RAWSocket:public CSocket
{
	char buf[1000];  //pachetul pe care-l construim
	int dimensiune;  //DIM pachet de date
	IPV4_HDR *v4hdr; //header IP a packetului
	TCP_HDR *tcphdr; //header TCP a pachetului
public:
	RAWSocket();
	Status createSocket();
	Status getSourceIp(char* )const;
	void createPacket(int,int);
	Status SendData(const char*,int );
	Status RecvData();
	Status conectToServer(const char *ipAddress,int port);
	~RAWSocket();
};