#pragma once
#include"PortWorker.h"
PortWorker::PortWorker():CStringWorker(PORT)
{
}

void PortWorker::genereaza(const char *portRange)
{
	char *p,*copie1,*copie2;
	copie1=new char[strlen(portRange)+2];
	CHECK_ALOC(copie1);
	strcpy(copie1,portRange);
	copie2=new char[strlen(portRange)+1];
	CHECK_ALOC(copie2);
	strcpy(copie2,portRange);
	int port;
	first = new Coada <int>;

	p=strtok(copie2,"- ");
	if(strlen(p)==strlen(portRange))
	{
		p=strtok(copie1,", ");//inseamna ca e o lista desp prin ,
		port=atoi(p);
		first->addElem(port);
		while(p)
		{
			p=strtok(NULL,", ");
			if(p==NULL)
				break;
			port=atoi(p);
			first->addNext(port);
		}
		delete []copie1;
		delete []copie2;
		return;
	}
	int x,y;// x<=port<=y
	x=atoi(p);
	p=strtok(NULL,"- ");
	y=atoi(p);
	bool ok=false;
	for(int i=x;i<=y;i++)
	{
		if(ok==false)
			first->addElem(i);
		else
			first->addNext(i);
		ok=true;
	}
	delete []copie1;
	delete []copie2;
}

Coada<int> *PortWorker::getList()
{
	return first;
}

PortWorker::~PortWorker()
{
	if(first!=NULL)
		first->destroy();
	first=NULL;
}