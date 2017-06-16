#pragma once
#include "iscanworker.h"
#include"Sniffer.h"
class CScanWorkerRAW :
	public IScanWorker
{
	CDescriptedPorts *DP;
	CSniffer* Sniffer;
public:
	CScanWorkerRAW(void);
	virtual ~CScanWorkerRAW(void);
	Status scan(const char *ipAddreses,int port);
	Status scan(const char *ipAddres,const char* ports);
	Status scan(const char *ipAddreses,const char* port,Grupare tip_de_grupare);
	Status Desciptedscan(const char *ipAddres);
};

