#pragma once
#include"CSocket.h"
#include"TCPSocket.h"
#include"UDPSocket.h"
#include"AdvancedPingSweep.h"
#include"SyntaxChecker.h"
#include"DescriptedPorts.h"
class IScanWorker
{
protected:
	IPWorker		m_IPW;
	PortWorker		m_PortW;
	CSyntaxChecker	m_Checker;
	bool PingBeforeScan;
	bool ScanForCommonPorts;

public:
	IScanWorker(void);
	virtual ~IScanWorker(void);
	virtual Status scan(const char *ipAddreses,int port)=0;
	virtual Status scan(const char *ipAddres,const char* ports)=0;
	virtual Status scan(const char *ipAddreses,const char* port,Grupare tip_de_grupare)=0;
	void setPingBeforeScan(bool value);
	void setScanForCommonPorts(bool value);
};

