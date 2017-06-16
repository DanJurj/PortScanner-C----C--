#include "Sniffer.h"


CSniffer::CSniffer(SOCKET sock_raw)
{
	thread t((sniff),sock_raw);
	t.detach();
}


CSniffer::~CSniffer(void)
{
}

void CSniffer::process_packet( char* buffer, int size)
{
    //Get the IP Header part of this packet
    struct ip_hdr *iph = (struct ip_hdr*)buffer;
    struct sockaddr_in source,dest;
    unsigned short iphdrlen;
     
    if(iph->ip_protocol == 4)
    {
        iphdrlen = iph->ip_total_length;
     
        struct tcp_header *tcph=(struct tcp_header*)(buffer + iphdrlen);
             
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->ip_srcaddr;
     
        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = iph->ip_destaddr;
         
        if(tcph->syn == 1 && tcph->ack == 1 && source.sin_addr.s_addr ==  dest.sin_addr.s_addr )
        {
            printf("Port %d open \n" , ntohs(tcph->source_port));
            fflush(stdout);
        }
    }
}


int CSniffer::start_sniffer(SOCKET sock_raw)
{
     
    int saddr_size , data_size;
    struct sockaddr saddr;
     
     char *buffer = ( char *)malloc(65536); //Its Big!
     
    printf("Sniffer initialising...\n");
     

	//Create Sniffer Raw TCP Packet
	printf("\nCreating Sniffer Raw TCP Socket...");
	if((sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))==SOCKET_ERROR)
	{
		printf("Creation of Sniffer raw socket failed.");
		return 0;
	}
		printf("Sniffer Raw TCP Socket Created successfully.");

	//Put Socket in RAW Mode.
	int	optval=1;
	printf("\nSetting the socket in Sniffer RAW mode...");
	if(setsockopt(sock_raw, IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval))==SOCKET_ERROR)
	{
		printf("failed to set socket in raw mode.");
		return 0;
	}
	printf("Sniffer Successful.");
    //Create a raw socket that shall sniff
    sock_raw = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);
     
    if(sock_raw < 0)
    {
        printf("Socket Error\n");
        fflush(stdout);
        return 1;
    }
     
    saddr_size = sizeof saddr;
     
    while(1)
    {
        //Receive a packet
        data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , &saddr_size);
         
        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            fflush(stdout);
            return 1;
        }
         
        //Now process the packet
        process_packet(buffer , data_size);
    }
     
    closesocket(sock_raw);
    printf("Sniffer finished.");
    fflush(stdout);
    return 0;
}
 
void CSniffer::sniff(SOCKET sock_raw)
{
	int x;
	do
	{
		 x=start_sniffer(sock_raw);
	}while(x==0);
}