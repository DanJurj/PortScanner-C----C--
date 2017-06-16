#include "DescriptedPorts.h"
CDescriptedPorts::CDescriptedPorts(void)
{
	firstPort=NULL;
	lastPort=NULL;
}

CDescriptedPorts::CDescriptedPorts(char* filename)
{
	FILE *in=fopen(filename,"r");
	int nr;
	char buffer[1024];
	firstPort=NULL;
	lastPort=NULL;
	while(!feof(in))
	{
		fscanf(in,"%d",&nr);
		fgets(buffer,1024,in);
		addPort(nr,buffer);
	}
}


CDescriptedPorts::~CDescriptedPorts(void)
{
}

	
void CDescriptedPorts::addPort(int nr,char* descriere)
{
	if(firstPort==NULL)
	{
		firstPort=new DescriptedPort(nr,descriere);
		CHECK_ALOC(firstPort);
		lastPort=firstPort;
	}
	else
	{
		DescriptedPort* aux=new DescriptedPort(nr,descriere);
		CHECK_ALOC(aux);
		lastPort->next=aux;
		lastPort=lastPort->next;
	}
}
