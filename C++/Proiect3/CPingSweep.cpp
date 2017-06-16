#include"CPingSweep.h"

CPingSweep::CPingSweep()
{
	executed=false;
}

CPingSweep::~CPingSweep()
{
}
bool  CPingSweep::Ping(const char  *IP_Calculator, int nr_requesturi, int procent_minim)
{
	char command[1024]="ping -n ";
	char aux[10];
	_itoa(nr_requesturi,aux,10);
	strcat(command,aux);
	strcat(command," ");
	strcat(command,IP_Calculator);
	strcat(command,">temp.txt");
	system(command);
	FILE *in=fopen("temp.txt","r");
	char buffer[1024];
	while (!feof(in))
	{
		fgets(buffer,1024,in);
		if(strstr(buffer,"host unreachable") || strstr(buffer,"Request timed out"))
			return false;
		if(strchr(buffer,'%'))
		{
			char*p=strtok(buffer,"(%");
			p=strtok(NULL,"(%");
			int x=atoi(p);
			if(100-x>procent_minim)
				return true;
			break;
		}
	}
	fclose(in);
	return false;
}

void CPingSweep::execute(Coada<char*> *IPs, int nr_requesturi, int procent_minim)
{
	this->IPs=IPs;
	m_nrPCs=IPs->get_lenght();
	m_stare=new bool[m_nrPCs];
	m_CurPC=0;
	for(Coada<char*> *aux=IPs;aux!=NULL;aux=aux->getNext(),m_CurPC++)
	{
		if(Ping(aux->getElem(),nr_requesturi,procent_minim)==true)
		{
			m_stare[m_CurPC]=true;
		}
		else
		{		
			m_stare[m_CurPC]=false;
		}
	}
	executed=true;
}

void CPingSweep::WriteReport(char* filename)
{
	FILE *out=fopen(filename,"r");
	CHECK_OPEN(out);
	if(executed)
	{
		int i=0;
		for(Coada<char*> *aux=IPs;aux!=NULL;aux=aux->getNext(),i++)
		{
			if(m_stare[i])
				fprintf(out,"%s - OPEN PC\n",aux->getElem());
			else
				fprintf(out,"%s - CLOSED PC\n",aux->getElem());
		
		}
	}
}

void CPingSweep::ShowReport()
{
	if(executed)
	{
		int i=0;
		for(Coada<char*> *aux=IPs;aux!=NULL;aux=aux->getNext(),i++)
		{
			if(m_stare[i])
				printf("%s - OPEN PC\n",aux->getElem());
			else
				printf("%s - CLOSED PC\n",aux->getElem());
		
		}
	}
}
