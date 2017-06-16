#pragma once
#include "cpingsweep.h"
#include<thread>
#include<mutex>

class CAdvancedPingSweep :
	public CPingSweep
{
	int	m_MaxThreads;
	static int counter;
	int x;
public:
	CAdvancedPingSweep(void);
	virtual ~CAdvancedPingSweep(void);
	static void Ping(char  *IP_Calculator,char* tempName, int nr_requesturi=4, int procent_minim=50);
	void execute(Coada<char*> *IPs, int nr_requesturi=4, int procent_minim=50);
	char* CreateName();
};

