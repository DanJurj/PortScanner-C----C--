#pragma once
#include"IPWorker.h"
IPWorker::IPWorker():CStringWorker(IP)
{
	first=NULL;
}

void IPWorker::genereaza(const char * rangeIP)
{
	char *p,*IPadress,*copie1,*copie2;
	copie1=new char[strlen(rangeIP)+2];
	CHECK_ALOC(copie1);
	strcpy(copie1,rangeIP);
	copie2=new char[strlen(rangeIP)+1];
	CHECK_ALOC(copie2);
	strcpy(copie2,rangeIP);
	p=strtok(copie2,"- ");//rangeip de forma 198... - 198..
	if(strlen(p)==strlen(rangeIP))
	{
		p=strtok(copie1,", ");//inseamna ca e o lista desp prin ,
		if(strlen(p)==strlen(rangeIP))//un sg IP
		{
			delete []copie1;
			delete []copie2;
			return;
		}
		first = new Coada <char *>;
		IPadress=new char[strlen(p)+1];
		strcpy(IPadress,p);
		first->addElem(IPadress);
		while(p)
		{
			p=strtok(NULL,", ");
			if(p==NULL)
				break;
			IPadress=new char[strlen(p)+1];
			strcpy(IPadress,p);
			first->addNext(IPadress);
		}
		delete []copie1;
		delete []copie2;
		return;
	}

	first = new Coada <char *>;
	int x=0,y=0,contor=0;//x-y
	copie1[strlen(rangeIP)]='.';
	copie1[strlen(rangeIP)+1]='\0';
	p=strtok(copie1,".");

	delete []copie2;
	copie2=new char[strlen(rangeIP)+1];
	strcpy(copie2,p);
	copie2[strlen(p)]='.';
	copie2[strlen(p)+1]='\0';

	while(p)//extrag ultimul camp
	{
		contor++;
		if(contor==4)
		{
			x=atoi(p);
		}
		if(contor<=3 && contor!=1)
		{
			strcpy(copie2+strlen(copie2),p);
			copie2[strlen(copie2)+1]='\0';
			copie2[strlen(copie2)]='.';
		}
		if(contor==8)
		{
			y=atoi(p);
		}
		p=strtok(NULL,".- ");
	}
	
	char sir[4];
	int n=strlen(copie2);
	bool ok=false;
	for(int i=x;i<=y;i++)
	{
		_itoa(i,sir,10);
		IPadress=new char[n+4];
		strcpy(copie2+n,sir);
		strcpy(IPadress,copie2);
		if(ok==false)
			first->addElem(IPadress);
		else
			first->addNext(IPadress);
		ok=true;
	}
	delete []copie1;
	delete []copie2;
}

Coada<char *> *IPWorker::getList()
{
	return first;
}

IPWorker::~IPWorker()
{
	if(first!=NULL)
		first->destroy();
	first=NULL;
}
		

	