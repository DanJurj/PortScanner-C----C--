#include "ScanWorkerUDP.h"

CScanWorkerUDP::CScanWorkerUDP(void)
{
	DP=new CDescriptedPorts("CommonPortsUDP.txt");
}

CScanWorkerUDP::~CScanWorkerUDP(void)
{
	delete DP;
}

Status CScanWorkerUDP::scan(const char *ipAddress,int port)
{
	IPWorker w;
	w.genereaza(ipAddress);
	UDPSocket s;
	char mesaj[24]="Are you open?";
	Coada<char *> *first=w.getList(),*p;
	cout<<"PORT "<<port<<"\n";
	if(first!=NULL)
	{
		p=first;
		while(p)
		{
			s.createSocket();
			s.setAddrTinta(p->getElem(),port);//setam adrs tinta
			if(s.SendData(mesaj,24)==EROARE)//trimitem mesaj proba
				return EROARE;
			cout<<" IP: "<<p->getElem()<<"\n";
			Status status=s.RecvData();//vedem ce primim
			if(status==EROARE)
				return EROARE;
			else
			{
				if(status==DISCONNECTED) //eroarea 10054
					cout<<"   "<<port<<" CLOSED\n";
				else
					cout<<"   "<<port<<" OPEN\n";//eroare 10060=timeout sau am primit mesaj raspuns
			}
			p=p->getNext();
			s.CloseConnection();
		}
	}
	else//un sg IP
	{
		s.createSocket();
		s.setAddrTinta(ipAddress,port);
		if(s.SendData(mesaj,24)==EROARE)
			return EROARE;
		cout<<"   IP: "<<ipAddress<<"\n";
		Status status=s.RecvData();//vedem ce primim
		if(status==EROARE)
			return EROARE;
		else
		{
			if(status==DISCONNECTED) //eroarea 10054
				cout<<"   "<<port<<" CLOSED\n";
			else
				cout<<"   "<<port<<" OPEN\n";//eroare 10060=timeout sau am primit mesaj raspuns
		}//!! timeout-ul l-am setat eu la 10 sec..ca daca portul e deschis exista posibilitatea sa nu trim nici un ICMP
		s.CloseConnection();
	}
	return DONE;
}

Status CScanWorkerUDP::scan(const char *ipAddress,const char* ports)
{
	if(PingBeforeScan==TRUE && CPingSweep::Ping(ipAddress)==false)
	{
		cout<<ipAddress<<"-All Ports are CLOSED"<<endl;
		return DONE;
	}
	UDPSocket s;
	PortWorker w;
	w.genereaza(ports);
	Coada<int>* first=w.getList(),*p;
	char mesaj[24]="Are you open?";
	cout<<"IP: "<<ipAddress<<"\n";
	if(first!=NULL)
	{
		p=first;
		while(p)//pt fiecare port
		{
			int port_number=p->getElem();
			s.createSocket();
			s.setAddrTinta(ipAddress,port_number);
			if(s.SendData(mesaj,24)==EROARE)
				return EROARE;
				
			Status status=s.RecvData();//vedem ce primim
			if(status==EROARE)
				return EROARE;
			else
			{
				if(status==DISCONNECTED) //eroarea 10054
					cout<<port_number<<" CLOSED\n";
				else
					cout<<port_number<<" OPEN\n";//eroare 10060=timeout sau am primit mesaj raspuns
			}//!! timeout-ul l-am setat eu la 10 sec..ca daca portul e deschis exista posibilitatea sa nu trim nici un ICMP
			s.CloseConnection();
			p=p->getNext();
		}
	}
	return DONE;
}

Status CScanWorkerUDP::scan(const char *ipAddress,const char* ports,Grupare tip_de_grupare)
{
	//pt fiercare port apelam scanRange(ipAdress,int port);
	//generam porturile
	if(m_Checker.CheckIP_range(ipAddress)==false || m_Checker.CheckPorts(ports)==false)
		throw new Exception(ERR_INCORECT_SYNTAX,"sintaxa incorecta");
	if(ScanForCommonPorts==FALSE)
	{
		if(tip_de_grupare==Group_Port)
		{	
			PortWorker w;
			w.genereaza(ports);
			Coada<int>* first=w.getList(),*p;
			if(first!=NULL)
			{
				p=first;
				while(p)//pt fiecare port
				{
					scan(ipAddress,p->getElem());
					p=p->getNext();
				}
			}
			return DONE;
		}
		else
			if(tip_de_grupare==Group_IP)
			{
				IPWorker IPs;
				IPs.genereaza(ipAddress);
				Coada<char*>* first=IPs.getList(),*p;
				if(first!=NULL)
				{
					p=first;
					while(p)//pt fiecare IP
					{
						scan(p->getElem(),ports);
						p=p->getNext();
					}
				}
				else
					scan(ipAddress,ports);
				return DONE;
			}
			else
				throw new Exception(ERR_INCORECT_GROUPING_CHOICE,"tip de grupare inexistent");
	}
	else
		Desciptedscan(ipAddress);//daca e setat flagul corespunzator
}

Status CScanWorkerUDP::Desciptedscan(const char *ipAddresses)
{
	IPWorker IPs;
	IPs.genereaza(ipAddresses);
	Coada<char*>* first=IPs.getList(),*p;
	UDPSocket s;
	char mesaj[24]="Are you open?";
	p=first;
	if(first!=NULL)
	{
		p=first;
		while(p)//pt fiecare IP
		{
			if(PingBeforeScan==TRUE && CPingSweep::Ping(p->getElem())==false)
			{
				cout<<"IP: "<<p->getElem()<<" -All Ports are CLOSED"<<endl;
				return DONE;
			}
			cout<<"\nIP: "<<p->getElem()<<"\n";

			for(DescriptedPort* aux=DP->firstPort;aux;aux=aux->next)
			{
				int portNumber=aux->m_PortNumber;

				s.createSocket();
				s.setAddrTinta(p->getElem(),portNumber);
				if(s.SendData(mesaj,24)==EROARE)
					return EROARE;
				Status status=s.RecvData();//vedem ce primim
				if(status==EROARE)
					return EROARE;
				else
				{
					if(status==DISCONNECTED) //eroarea 10054
						cout<<portNumber<<" CLOSED :"<<aux->m_description;
					else
						cout<<portNumber<<" OPEN :"<<aux->m_description;//eroare 10060=timeout sau am primit mesaj raspuns
				}//!! timeout-ul l-am setat eu la 10 sec..ca daca portul e deschis exista posibilitatea sa nu trim nici un ICMP
				s.CloseConnection();
			  }

			  p=p->getNext();
		}
	}
	else
		if(PingBeforeScan==TRUE && CPingSweep::Ping(ipAddresses)==false)
		{
			cout<<"IP: "<<p->getElem()<<" -All Ports are CLOSED"<<endl;
			return DONE;
		}
		else
		{
			cout<<"IP: "<<ipAddresses<<"\n";
			for(DescriptedPort* aux=DP->firstPort;aux;aux=aux->next)
			{
				int portNumber=aux->m_PortNumber;
				s.createSocket();
				s.setAddrTinta(ipAddresses,portNumber);
				if(s.SendData(mesaj,24)==EROARE)
					return EROARE;
				Status status=s.RecvData();//vedem ce primim
				if(status==EROARE)
					return EROARE;
				else
				{
					if(status==DISCONNECTED) //eroarea 10054
						cout<<portNumber<<" CLOSED :"<<aux->m_description;
					else
						cout<<portNumber<<" OPEN :"<<aux->m_description;//eroare 10060=timeout sau am primit mesaj raspuns
				}//!! timeout-ul l-am setat eu la 10 sec..ca daca portul e deschis exista posibilitatea sa nu trim nici un ICMP
				s.CloseConnection();
			}
		 }
	cout<<"\n";
	return DONE;
}
