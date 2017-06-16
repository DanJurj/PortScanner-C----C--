#include "ScanWorkerPS.h"


CScanWorkerPS::CScanWorkerPS(void)
{
	m_Worker=NULL;
}


CScanWorkerPS::~CScanWorkerPS(void)
{
	if(m_Worker!=NULL)
		delete m_Worker;
}
Status CScanWorkerPS::scan(const char *ipAddreses,int port)
{
	throw new Exception(ERR_WRONG_SCAN,"A-ti gresit parametrii pentri acest tip de scanare");
}

Status CScanWorkerPS::scan(const char *ipAddres,const char* ports)
{
	throw new Exception(ERR_WRONG_SCAN,"A-ti gresit parametrii pentri acest tip de scanare");
}

Status CScanWorkerPS::scan(const char *ipAddreses,const char* port,Grupare tip_de_grupare)
{
	throw new Exception(ERR_WRONG_SCAN,"A-ti gresit parametrii pentri acest tip de scanare");
}


void CScanWorkerPS::SimpleScan(const char *ipAddress,int nr_requesturi, int procent_minim)
{
	if(m_Checker.CheckIP_range(ipAddress)==false)
		throw new Exception(ERR_INCORECT_SYNTAX,"sintaxa incorecta");
	m_Worker=new CPingSweep;
	m_IPW.genereaza(ipAddress);
	if(m_IPW.getList()!=NULL)
		m_Worker->execute(m_IPW.getList(),nr_requesturi,procent_minim);
	else
	{
		Coada<char*> *ip=new Coada<char*>;
		char* aux=new char[strlen(ipAddress)+1];
		strcpy(aux,ipAddress);
		ip->addElem(aux);
		m_Worker->execute(ip,nr_requesturi,procent_minim);
	}
	m_Worker->ShowReport();
}

void CScanWorkerPS::AdvancedScan(const char *ipAddress,int nr_requesturi, int procent_minim)
{
	if(m_Checker.CheckIP_range(ipAddress)==false)
		throw new Exception(ERR_INCORECT_SYNTAX,"sintaxa incorecta");
	m_Worker=new CAdvancedPingSweep;
	m_IPW.genereaza(ipAddress);
	m_Worker->execute(m_IPW.getList(),nr_requesturi,procent_minim);
}

