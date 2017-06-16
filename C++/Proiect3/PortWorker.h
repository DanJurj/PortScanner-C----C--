#pragma once
#include"CStringWorker.h"
class PortWorker:public CStringWorker
{
	Coada<int> *first;//lista porturilor din range
public:
	PortWorker();
	void genereaza(const char *);
	Coada<int> *getList();
	~PortWorker();
};