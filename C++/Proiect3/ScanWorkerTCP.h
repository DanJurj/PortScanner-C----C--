#pragma once
#include "iscanworker.h"
class CScanWorkerTCP :public IScanWorker
{
	CDescriptedPorts *DP;
public:
	CScanWorkerTCP(void);
	virtual ~CScanWorkerTCP(void);
	Status scan(const char *ipAddreses,int port);
	Status scan(const char *ipAddres,const char* ports);
	Status scan(const char *ipAddreses,const char* port,Grupare tip_de_grupare);
	Status Desciptedscan(const char *ipAddres);
};

