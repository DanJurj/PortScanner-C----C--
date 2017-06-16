#include"PortScanner.h"
#include"RAWSocket.h"
#include"ScanWorkerUDP.h"
CPortScanner* CPortScanner::m_Instance=NULL;

int main()
{
	try
	{
		CPortScanner &PS=CPortScanner::get_Instance();
		
		cout<<"Scanare UDP \nIP-uri:192.168.114.1 si 127.0.0.1 \nPorturi:135-140\nTip Grupare:Port\n\n";
		PS.scan("192.168.114.1,127.0.0.1","135-140",UDP,Group_Port);

		cout<<"\nScanare UDP \nIP-uri:192.168.114.1 si 127.0.0.1 \nPorturi:135-140\nTip Grupare:IP\n\n";
		PS.scan("192.168.114.1,127.0.0.1","135-140",UDP,Group_IP);
		
		PS.setScanForCommonPorts(TRUE);
		cout<<"\n\n";
		PS.scan("172.16.15.70","135,139,445,446",TCP,Group_IP);
		/*
		cout<<"Scanare TCP \nIP-uri:192.168.2.1,172.16.15.70 \nPorturi:80,135,139,445,446\nTip Grupare:IP\n\n";
		PS.setScanForCommonPorts(FALSE);
		PS.scan("192.168.2.1,172.16.15.70","80,135,139,445,446",TCP,Group_IP);
		
		cout<<"Scanare TCP \nIP-uri:192.168.2.1,172.16.15.70 \nPorturi:Porturi des utilizate\nTip Grupare:IP\n\n";
		PS.setScanForCommonPorts(TRUE);
		PS.scan("192.168.2.1,172.16.15.70","80",TCP,Group_IP);
		
		cout<<"Scanare UDP \nIP-uri:192.168.2.1,172.16.15.70 \nPorturi:Porturi des utilizate\nTip Grupare:IP\n\n";
		PS.setScanForCommonPorts(TRUE);
		PS.scan("192.168.2.1,172.16.15.70","80",UDP,Group_IP);
		

		cout<<"Scanare ICMP \nIP-uri:192.168.2.1,192.168.2.179,192.168.2.180\n\n";
		PS.scan("192.168.2.1,172.16.15.70,192.168.2.180",PING);
		
		cout<<"Scanare Advanced ICMP(MultiThread) \nIP-uri:192.168.1.95-192.168.1.105\n\n";
		PS.scan("172.16.15.70-172.16.15.77",ADV_PING);

		*/

		RAWSocket s;
		SOCKET ss=socket(AF_INET,SOCK_STREAM,0);
		CSniffer* C=new CSniffer(ss);
		//s.createSocket();
		//s.setAddrTinta("192.168.0.106",10);
		//s.SendData("mesaj",5);
		CPortScanner::DestroyInstance();
	}
	catch(Exception *e)
	{
		e->message();
		int cod=e->get_cod();
		delete e;
		return cod;
	}
	return 0;
}