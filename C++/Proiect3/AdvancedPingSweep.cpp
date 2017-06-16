#include "AdvancedPingSweep.h"
int CAdvancedPingSweep::counter=0;
mutex mu;
CAdvancedPingSweep::CAdvancedPingSweep(void)
{
	m_MaxThreads=std::thread::hardware_concurrency()/2;
}


CAdvancedPingSweep::~CAdvancedPingSweep(void)
{
}

void  CAdvancedPingSweep::Ping(char  *IP_Calculator,char* tempName, int nr_requesturi, int procent_minim)
{
	char command[1024]="ping -n ";
	char aux[10];
	_itoa(nr_requesturi,aux,10);
	strcat(command,aux);
	strcat(command," ");
	strcat(command,IP_Calculator);
	strcat(command,">");
	strcat(command,tempName);
	system(command);
	FILE *out=fopen("rez.txt","w");
	CHECK_OPEN(out);
	FILE *in=fopen(tempName,"r");
	CHECK_OPEN(in);
	char buffer[1024];
	while (!feof(in))
	{
		fgets(buffer,1024,in);
		if(strstr(buffer,"host unreachable"))
		{	
			mu.lock();
			cout<<IP_Calculator<<" Closed PC"<<endl;
			fprintf(out,"%s CLOSED PC \n",IP_Calculator);
			mu.unlock();
			counter++;
			fclose(in);
			return ;
		}
		if(strchr(buffer,'%'))
		{
			char*p=strtok(buffer,"(%");
			p=strtok(NULL,"(%");
			int x=atoi(p);
			if(100-x>procent_minim)
			{
				mu.lock();
				cout<<IP_Calculator<<"	OPEN PC"<<endl;
				fprintf(out,"%s OPEN PC \n",IP_Calculator);
				mu.unlock();
				counter++;
				fclose(in);
				return;
			}
		}
	}
	fclose(in);
	mu.lock();
	cout<<IP_Calculator<<" CLOSED PC"<<endl;
	fprintf(out,"%s CLOSED PC \n",IP_Calculator);
	mu.unlock();
	fclose(out);
	fclose(in);
	counter++;
	return ;
}

void CAdvancedPingSweep::execute(Coada<char*> *IPs, int nr_requesturi, int procent_minim)
{
	this->IPs=IPs;
	m_nrPCs=IPs->get_lenght();
	m_stare=new bool[m_nrPCs];
	m_CurPC=0;
	counter=0;
	x=0;
	int old_counter=counter;
	Coada<char*> *aux=IPs;
	while(aux!=NULL)
	{
		if(old_counter!=counter)
		{
			x=x-counter;
			old_counter=counter;
		}
		if(x<m_MaxThreads)  //daca mai sunt thread-uri ...se creaza un thread nou
		{
			char *nume=CreateName(); //se creeaza numele fisierului de care sa se foloseasca thread-ul
			thread t((Ping),aux->getElem(),nume,4,50);
			t.detach();
			aux=aux->getNext();
		}
	}
	while(counter<m_nrPCs)
		std::this_thread::sleep_for(chrono::milliseconds(10));
	executed=true;
	system("del /q temp*");
}

char* CAdvancedPingSweep::CreateName()
{
	char aux[30],*nume=new char[30];
	CHECK_ALOC(nume);
	_itoa(m_CurPC,aux,10);
	strcpy(nume,"temp");
	strcat(nume,aux);
	strcat(nume,".txt");
	m_CurPC++;
	x++;
	return nume;
}
