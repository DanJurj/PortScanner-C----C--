#pragma once
#include"RAWSocket.h"
#include<thread>
class CSniffer
{
	char buffer[64000];
public:
	CSniffer(SOCKET sock_raw);
	virtual ~CSniffer(void);
	static void sniff(SOCKET sock_raw);
	static int start_sniffer(SOCKET sock_raw);
	static	void process_packet( char* buffer, int size);
};


