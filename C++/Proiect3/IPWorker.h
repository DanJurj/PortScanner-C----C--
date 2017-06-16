#pragma once
#include"CStringWorker.h"
class IPWorker:public CStringWorker
{
	Coada<char *> *first;//lista IP-urilor din range
public:
	IPWorker();
	void genereaza(const char *);
	Coada<char *> *getList();
	~IPWorker();
};