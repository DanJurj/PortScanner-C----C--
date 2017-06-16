#pragma once
#include"IPWorker.h"
class CPingSweep
{
public:
	CPingSweep();
	virtual ~CPingSweep();
	static bool Ping(const char  *IP_Calculator, int nr_requesturi=4, int procent_minim=50);
	virtual void execute(Coada<char*> *IPs, int nr_requesturi=4, int procent_minim=50);
	void WriteReport(char* filename);
	void ShowReport();

protected:
	Coada<char*> *IPs;
	bool *m_stare;
	int m_nrPCs,m_CurPC;
	bool executed;
};

