#include "PortScanner.h"

CPortScanner::CPortScanner()
{
	SW=NULL;
	PingBeforeScan=TRUE;
	ScanForCommonPorts=FALSE;
}

CPortScanner::CPortScanner(CPortScanner&)
{
}

CPortScanner::~CPortScanner()
{
	if(SW!=NULL)
		delete SW;
}

CPortScanner& CPortScanner::get_Instance()
{
	if(m_Instance==NULL)
	{
		m_Instance=new CPortScanner();
		CHECK_ALOC(m_Instance);
		return *m_Instance;
	}
	else
		return *m_Instance;
}

void CPortScanner::DestroyInstance()
{
	if(m_Instance!=NULL)
	{
		delete m_Instance;
		m_Instance=NULL;
	}
}


void CPortScanner::scan(const char *ipAddress,const char* port,Type tip,Grupare tip_grupare)
{
	switch (tip)
	{
	case TCP:
		SW=new CScanWorkerTCP;
		SW->setPingBeforeScan(PingBeforeScan);
		SW->setScanForCommonPorts(ScanForCommonPorts);
		SW->scan(ipAddress,port,tip_grupare);
		break;
	case UDP:
		SW=new CScanWorkerUDP;
		SW->setPingBeforeScan(PingBeforeScan);
		SW->setScanForCommonPorts(ScanForCommonPorts);
		SW->scan(ipAddress,port,tip_grupare);
		break;
	//case RAW:
	default:
		throw new Exception(ERR_TECHNIQUE_UNKNOWN,"tehnica necunoscuta");
		break;
	}
}

void CPortScanner::scan(const char *ipAddress, Type tip, int nr_requesturi, int procent_minim)
{
	CScanWorkerPS P;
	switch (tip)
	{
	case PING:
		P.SimpleScan(ipAddress,nr_requesturi,procent_minim);
		break;
	case ADV_PING:
		P.AdvancedScan(ipAddress,nr_requesturi,procent_minim);
		break;
	default:
		throw new Exception(ERR_TECHNIQUE_UNKNOWN,"tehnica necunoscuta");
		break;
	}
}

void CPortScanner::setPingBeforeScan(bool value)
{
	PingBeforeScan=value;
}

void CPortScanner::setScanForCommonPorts(bool value)
{
	ScanForCommonPorts=value;
}
