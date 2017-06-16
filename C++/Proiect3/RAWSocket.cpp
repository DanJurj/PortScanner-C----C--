#pragma once
#include"RAWSocket.h"

RAWSocket::RAWSocket():CSocket(RAW)
{
	IPV4_HDR *v4hdr=NULL;
	TCP_HDR *tcphdr=NULL;
	dimensiune=512;
}

Status RAWSocket::createSocket()
{
	if((Socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))==SOCKET_ERROR)
	{
	    throw new Exception(ERR_SOCKET,"eroare la crearea socket-ului");
	}
	//RAW Mode (optiunea crearii pachetului de catre aplicatie).
	int optval=1;
	if(setsockopt(Socket, IPPROTO_IP,IP_HDRINCL, (char *)&optval, sizeof(optval))==SOCKET_ERROR)
	{
		 throw new Exception(ERR_SOCKET,"eroare la crearea socket-ului");
	}
	return DONE;
}

Status RAWSocket::getSourceIp(char *buffer)const
{
	//obtinere adresa IP a sursei
	SOCKET sock;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
	{
		throw new Exception(ERR_SOCKET,"eroare la crearea socket-ului");
	}
	const char* kGoogleDnsIp = "8.8.8.8";
    int dns_port = 53;

	struct sockaddr_in serv;
	memset( &serv,0,sizeof(serv) );
    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=inet_addr(kGoogleDnsIp);
    serv.sin_port=htons(dns_port);
 
    int err=connect(sock,(const struct sockaddr*) &serv ,sizeof(serv));
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err=getsockname(sock, (struct sockaddr*) &name, &namelen);
    const char *p=inet_ntop(AF_INET, &name.sin_addr, buffer, 100);
	strcpy(buffer,p);
    closesocket(sock);
	return DONE;
}

void RAWSocket::createPacket(int portSursa,int portDestinatie)
{
	memset(buf,0,1000);
	char *data=NULL,source_ip[20];
	getSourceIp(source_ip); //obtine adresa IP sursa--locala
	
	v4hdr = (IPV4_HDR *)buf; //lets point to the ip header portion
	v4hdr->ip_version=4;
	v4hdr->ip_header_len=5;
	v4hdr->ip_tos=0;
	v4hdr->ip_total_length=htons(sizeof(IPV4_HDR)+sizeof(TCP_HDR)+dimensiune);
	v4hdr->ip_id=htons(2);
	v4hdr->ip_frag_offset=0;
	v4hdr->ip_frag_offset1=0;
	v4hdr->ip_reserved_zero=0;
	v4hdr->ip_dont_fragment=1;
	v4hdr->ip_more_fragment=0;
	v4hdr->ip_ttl=8;
	v4hdr->ip_protocol=IPPROTO_TCP;
	v4hdr->ip_srcaddr=inet_addr(source_ip);   //adresa sursa
	v4hdr->ip_destaddr=inet_addr(inet_ntoa(addrTinta.sin_addr));//adresa tinta
	v4hdr->ip_checksum=0;

	tcphdr = (TCP_HDR *)&buf[sizeof(IPV4_HDR)]; //obtinerea headerului din pachetul care urmeaza a fi transmis
 
	tcphdr->source_port=htons(portSursa);
	tcphdr->dest_port=htons(portDestinatie);
 
	tcphdr->cwr=0;
	tcphdr->ecn=1;
	tcphdr->urg=0;
	tcphdr->ack=0;
	tcphdr->psh=0;
	tcphdr->rst=0;
	tcphdr->syn=1; //pt scanarea sin setam flag SIN (daca raspunsul e SYN\ACK PORT-OPEN daca e RST-INCHIS)
	tcphdr->fin=0;
	tcphdr->ns=1;
	tcphdr->checksum = 0;

	//datele din pachet de dim
	data = &buf[sizeof(IPV4_HDR)+sizeof(TCP_HDR)];
	memset(data,'^',dimensiune); //umplem bufferul de date
}

Status RAWSocket::SendData(const char *data,int l)
{
	createPacket(80,120);
	if((sendto(Socket,buf,sizeof(IPV4_HDR)+sizeof(TCP_HDR)+dimensiune,0,(SOCKADDR *)&addrTinta, sizeof(addrTinta)))==SOCKET_ERROR)
	{
		throw new Exception(ERR_SEND,"eroare la TRIMITEREA mesajului");
	}
	return DONE;
}

Status RAWSocket::RecvData()
{
	return DONE;
}

Status RAWSocket::conectToServer(const char *ipAddress,int port)
{
	return DONE;
}

RAWSocket::~RAWSocket()
{
	CloseConnection();
}