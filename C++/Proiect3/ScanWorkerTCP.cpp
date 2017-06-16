#include "ScanWorkerTCP.h"

CScanWorkerTCP::CScanWorkerTCP(void)
{
	DP=new CDescriptedPorts("CommonPorts.txt");
}

CScanWorkerTCP::~CScanWorkerTCP(void)
{
	delete DP;
}

Status CScanWorkerTCP::scan(const char *ipAddress,int port)
{
	IPWorker w;
	w.genereaza(ipAddress);//genereaza rangul de IP-uri
	TCPSocket s;
	Coada<char *> *first=w.getList(),*p;
	cout<<"PORT:"<<port<<"\n";
	if(first!=NULL)
	{
		p=first;
		while(p)
		{
			if(PingBeforeScan==TRUE && CPingSweep::Ping(p->getElem())==false)
				cout<<"IP: "<<p->getElem()<<" -All Ports are CLOSED"<<endl;
			else
			{
				s.createSocket();
				cout<<"   IP: "<<p->getElem()<<"\n";
				if(s.conectToServer(p->getElem(),port)==DONE)//se seteaza si adr tinta+port
					cout<<"   "<<port<<" OPEN\n";
				else
					cout<<"   "<<port<<" CLOSED\n";
				s.CloseConnection();
			}
			p=p->getNext();
		}
	}
	else //am doar un IP tinta
	{
		if(PingBeforeScan==TRUE && CPingSweep::Ping(ipAddress)==false)
				cout<<ipAddress<<"-All Ports are CLOSED"<<endl;
		else
		{
			s.createSocket();
			cout<<"   IP: "<<ipAddress<<"\n";
			if(s.conectToServer(ipAddress,port)==DONE)
				cout<<"   "<<port<<" OPEN\n";
			else
				cout<<"   "<<port<<" CLOSED\n";
			s.CloseConnection();
		}
	}
	return DONE;
}

Status CScanWorkerTCP::scan(const char *ipAddres,const char* ports)
{
	
	if(PingBeforeScan==TRUE && CPingSweep::Ping(ipAddres)==false)
		cout<<ipAddres<<"-All Ports are CLOSED"<<endl;
	else
	{
		cout<<"IP: "<<ipAddres<<"\n";
		TCPSocket s;
		PortWorker pw;
		pw.genereaza(ports);
		Coada<int> *first=pw.getList() , *p;
		if(first!=NULL)
		{
			p=first;
			while(p)//pt fiecare port
			{
				s.createSocket();
				int port_number=p->getElem();
				if(s.conectToServer(ipAddres,port_number)==DONE)
					cout<<port_number<<" OPEN\n";
				else
					cout<<port_number<<" CLOSED\n";
				s.CloseConnection();
				p=p->getNext();
			}
		}
	}
	return DONE;
}

Status CScanWorkerTCP::scan(const char *ipAddreses,const char* port,Grupare tip_de_grupare)
{
	//pt fiercare port apelam scanRange(ipAdress,int port);
	//generam porturile

	if(m_Checker.CheckIP_range(ipAddreses)==false || m_Checker.CheckPorts(port)==false)
		throw new Exception(ERR_INCORECT_SYNTAX,"sintaxa incorecta");

	if(ScanForCommonPorts==FALSE)
	{
		if(tip_de_grupare==Group_Port)
		{
			PortWorker w;
			w.genereaza(port);
			Coada<int>* first=w.getList(),*p;
			if(first!=NULL)
			{
				p=first;
				while(p)//pt fiecare port
				{
					scan(ipAddreses,p->getElem());
					p=p->getNext();
				}
			}
			return DONE;
		}
		else
			if(tip_de_grupare==Group_IP)
			{
				IPWorker IPs;
				IPs.genereaza(ipAddreses);
				Coada<char*>* first=IPs.getList(),*p;
				if(first!=NULL)
				{
					p=first;
					while(p)//pt fiecare IP
					{
						scan(p->getElem(),port);
						p=p->getNext();
					}
				}
				else
					scan(ipAddreses,port);
				return DONE;
			}
			else
				throw new Exception(ERR_INCORECT_GROUPING_CHOICE,"tip de grupare inexistent");
	}
	else
		Desciptedscan(ipAddreses);
}

Status CScanWorkerTCP::Desciptedscan(const char *ipAddresses)
{
	//scanarea porturilor comune din COMMONPORTS.TXT
	IPWorker IPs;
	IPs.genereaza(ipAddresses);
	Coada<char*>* first=IPs.getList(),*p;
	TCPSocket s;
	p=first;
	if(first!=NULL)//avem un range de IP-uri
	{
		p=first;
		while(p)//pt fiecare IP
		{
			if(PingBeforeScan==TRUE && CPingSweep::Ping(p->getElem())==false)
			{
				cout<<"\nIP: "<<p->getElem()<<" -All Ports are CLOSED"<<endl;
				return DONE;
			}
			cout<<"IP: "<<p->getElem()<<"\n";
			for(DescriptedPort* aux=DP->firstPort;aux;aux=aux->next)
			{
				int portNumber=aux->m_PortNumber;
				s.createSocket();
				if(s.conectToServer(p->getElem(),portNumber)==DONE)
					cout<<portNumber<<" OPEN :"<<aux->m_description;
				else
					cout<<portNumber<<" CLOSED :"<<aux->m_description;
				s.CloseConnection();
			}
			p=p->getNext();
		}
	}
	else
		if(PingBeforeScan==TRUE && CPingSweep::Ping(ipAddresses)==false)
		{
			cout<<"\nIP: "<<p->getElem()<<" -All Ports are CLOSED"<<endl;
			return DONE;
		}
		else
		{
			cout<<"IP: "<<ipAddresses<<"\n";
			for(DescriptedPort* aux=DP->firstPort;aux;aux=aux->next)
			{
				int portNumber=aux->m_PortNumber;
				s.createSocket();
				if(s.conectToServer(ipAddresses,portNumber)==DONE)
					cout<<portNumber<<" OPEN :"<<aux->m_description;
				else
					cout<<portNumber<<" CLOSED :"<<aux->m_description;
				s.CloseConnection();
			}
		 }

	return DONE;
}

