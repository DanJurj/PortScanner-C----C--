#pragma once
#include<iostream>
#include<string.h>
#include<winsock2.h>
#include"IPWorker.h"
#include"PortWorker.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

typedef enum
{
	DONE,NOTREADY,DISCONNECTED,EROARE,TIMEOUT
}Status;
typedef enum
{
	UDP,TCP,PING,ADV_PING,RAW
}Type;
class CSocket
{
	protected:
        WSADATA wsa;
        SOCKET Socket;
        sockaddr_in addrTinta;//adresa host-ului tinta
		Type tip_protocol; //UDP sau TCP
	 public:
		CSocket();
		CSocket(Type tip);
		virtual Status createSocket()=0;
		virtual Status SendData(const char*,int)=0;
        virtual Status RecvData()=0;
		void setAddrTinta(const char *ipAddress,int port);
		virtual Status conectToServer(const char *ipAddress,int port)=0;
        void CloseConnection();
		virtual ~CSocket();
};
