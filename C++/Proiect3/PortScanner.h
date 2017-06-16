#pragma once
#include"ScanWorkerPS.h"
#include"ScanWorkerTCP.h"
#include"ScanWorkerUDP.h"
#include"ScanWorkerRAW.h"
class CPortScanner
{
	static CPortScanner *m_Instance;
	CPortScanner();
	CPortScanner(CPortScanner&);
	virtual ~CPortScanner();
	IScanWorker *SW;
	bool PingBeforeScan;
	bool ScanForCommonPorts;

public:
	static CPortScanner& get_Instance();
	static void DestroyInstance();
	void scan(const char *ipAddress,const char* port,Type tip,Grupare tip_grupare);
	void scan(const char *ipAddress, Type tip, int nr_requesturi=4, int procent_minim=50);
	void setPingBeforeScan(bool value);
	void setScanForCommonPorts(bool value);
};

