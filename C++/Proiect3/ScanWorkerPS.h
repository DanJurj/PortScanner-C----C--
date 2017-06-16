#pragma once
#include "iscanworker.h"
class CScanWorkerPS :
	public IScanWorker
{
	CPingSweep	*m_Worker;
public:
	CScanWorkerPS(void);
	virtual ~CScanWorkerPS(void);
	Status scan(const char *ipAddress,int port);
	Status scan(const char *ipAddres,const char* ports);
	Status scan(const char *ipAddress,const char* port,Grupare tip_de_grupare);
	void SimpleScan(const char *ipAddress,int nr_requesturi=4, int procent_minim=50);
	void AdvancedScan(const char *ipAddress,int nr_requesturi=4, int procent_minim=50);
};

