#pragma once
#include "iscanworker.h"
class CScanWorkerUDP :
	public IScanWorker
{
	CDescriptedPorts *DP;
public:
	CScanWorkerUDP(void);
	virtual ~CScanWorkerUDP(void);
	Status scan(const char *ipAddreses,int port);
	Status scan(const char *ipAddres,const char* ports);
	Status scan(const char *ipAddreses,const char* port,Grupare tip_de_grupare);
	Status Desciptedscan(const char *ipAddres);
};

