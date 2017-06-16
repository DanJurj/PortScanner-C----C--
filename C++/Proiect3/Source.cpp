#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<ifaddrs.h>

#define TRUE  1
#define FALSE 0

#define SOURCE_PORT 48419  
#define SRC_INTERFACE "eth0"

#define PACKET_BUFFER_SIZE 512

#define INTERNET_HEADER_LEN 5
#define IPV4_VERSION 4
#define MAX_TCP_WINDOW_SIZE 14600

#define STATUS_SUCCESS 0

#define ERROR_BASE 100
#define ERR_SOCKET_CREATE          ( ERROR_BASE + 1 )
#define ERR_INVALID_ARGS_NR        ( ERROR_BASE + 2 )
#define ERR_INVALID_ARG_IP_VALUE   ( ERROR_BASE + 3 )
#define ERR_INVALID_ARG_PORT_VALUE ( ERROR_BASE + 4 )
#define ERR_ROOT_PRIVILEGE_NEEDED  ( ERROR_BASE + 5 )
#define ERR_IP_ADDRESS_INVALID     ( ERROR_BASE + 6 )
#define ERR_IP_HEADER_INCLUDED     ( ERROR_BASE + 7 )
#define ERR_SNIFFER_THREAD         ( ERROR_BASE + 8 )
#define ERR_SEND_SYN_PACKET        ( ERROR_BASE + 9 )
#define ERR_RECEIVE_PACKETS        ( ERROR_BASE + 10)


struct pseudoheader {
	unsigned int src_address;
 	unsigned int dst_address;
	unsigned char placeholder;
	unsigned char proto;
	unsigned short lengthTCP;
	struct tcphdr tcpHeader;
};


unsigned long destAddr;
int numberOfPorts;
pthread_t threadSniffer;
unsigned char port_status[65536];

void checkArgs(int argc,char** argv);
void raiseError(int errorcode);
void extractDestIp(char* argv,char **destIp);
void extractDestPorts(char *argv,int **destPorts,int *portsNr);
int checkPort(char* port,int digitnr);
char* getLocalIpAddress();
void* fillIpHeader(char* packetDGRAM,char* sourceIp);
unsigned short calculateChecksum(unsigned short* p,int n);
void  fillTcpHeader(struct tcphdr* tcpHeader);
void informKernelHeadersIncluded(int sock);
void* sniffer_thread_callback(void* pointer);
void sniffNetworkTraffic();
void createSnifferThread();
void sendSYNpackets(int portsNr,int *ports,char* packetDGRAM,int sock,char* sourceIp);
void printPortStatuses(int *ports,int nr);


int main(int argc,char **argv) 
{ 


   checkArgs(argc,argv);

   int sock;
   
 	   
   char packet[PACKET_BUFFER_SIZE];

   char* sourceIp  = NULL;
   char *destIp    = NULL;
   int *destPorts  = NULL;	   
   int portsNr     = 0;


   struct tcphdr	 *tcpHeader = NULL;

   memset(packet,0,PACKET_BUFFER_SIZE);

   extractDestIp(argv[1],&destIp);
   extractDestPorts(argv[2],&destPorts,&portsNr);

   destAddr = inet_addr (destIp);

   sock = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
   if (sock < 0 ) 
	raiseError(ERR_SOCKET_CREATE);

   tcpHeader = (struct tcphdr*) (packet + sizeof(struct ip));
   	
   sourceIp = getLocalIpAddress();

   fillIpHeader(packet,sourceIp);
   
   fillTcpHeader(tcpHeader);

   informKernelHeadersIncluded(sock);
   
   createSnifferThread();

   sendSYNpackets(portsNr,destPorts,packet,sock,sourceIp);

   pthread_join(threadSniffer,NULL);
 
   printPortStatuses(destPorts,portsNr);

   free(destPorts);
   free(sourceIp);
   return STATUS_SUCCESS;
}






void raiseError(int errorcode)
{
    printf("ERROR\n");
    switch(errorcode) {
	case ERR_SOCKET_CREATE:     	  printf("Could not create RAW SOCKET");
				    	  break;

        case ERR_INVALID_ARGS_NR:   	  printf("Invalid number of arguments");
				    	  break;

	case ERR_ROOT_PRIVILEGE_NEEDED:   printf("Root privilege is needed");
					  break;

  	case ERR_INVALID_ARG_IP_VALUE:    printf("Invalid destination Ip argument");
				          break;

        case ERR_INVALID_ARG_PORT_VALUE:  printf("Invalid port argument");
				   	  break;

 	case ERR_IP_ADDRESS_INVALID:   	  printf("Destination IP address is invalid");
					  break;
	
	case ERR_IP_HEADER_INCLUDED:	  printf("Could not inform kernel that IP header is included in packet");
					  break;

	case ERR_SNIFFER_THREAD:	  printf("Could not create the sniffer thread");
					  break;

	case ERR_SEND_SYN_PACKET:	  printf("Could not send the SYN packet");
					  break;
	
	case ERR_RECEIVE_PACKETS:	  printf("Could not receive packets");
					  break;

	default: 			  printf("Unknown error");
    }

    printf("\n");
    exit(errorcode);
}





void checkArgs(int argc,char** argv)
{
    if (argc !=3)
  	  raiseError(ERR_INVALID_ARGS_NR);
}




void extractDestIp(char *argv,char** destIp)
{

    if (strncmp("-ip=",argv,4)!=0)
         raiseError(ERR_INVALID_ARG_IP_VALUE);



    if ( inet_addr(argv+4) ==-1)
         raiseError(ERR_IP_ADDRESS_INVALID);

     (*destIp) = strdup(argv+4);

}





void extractDestPorts(char* argv,int** destPorts,int *portsNr)
{
    int totalPortsNr = 0 ;
    int i,idx = 0;
    int low,high;
    
    char* p	        = NULL;
    char* tok           = NULL;
    char* anothertok    = NULL;
    char* argccopy      = strdup(argv);


    if ( strncmp("-p=",argv,3) !=0)
	 raiseError(ERR_INVALID_ARG_PORT_VALUE);

    
     if ( strcmp(argv+3,"") == 0)
	 raiseError(ERR_INVALID_ARG_PORT_VALUE);

  
    tok = strtok(argv+3,",");
    while (tok != NULL) 
  	{
	   
           if (strcmp(tok,"")==0)
		raiseError(ERR_INVALID_ARG_PORT_VALUE);

	   if (strchr(tok,'-') == NULL)
   		{
 
	            if ( checkPort(tok,strlen(tok)) == FALSE )
				raiseError(ERR_INVALID_ARG_PORT_VALUE);
                    
                    totalPortsNr++;
		}
           else 
	        {  
		    
                    p = strchr(tok,'-');
  
		    i = p - tok;

		     if (i == 0)
			raiseError(ERR_INVALID_ARG_PORT_VALUE);	

		    anothertok = strndup(tok,i+1);

		    strncpy(anothertok,tok,i);

                    if ( checkPort(anothertok,i) == FALSE)
			   raiseError(ERR_INVALID_ARG_PORT_VALUE);    				

		    low  = atoi(anothertok);

		    if ( checkPort(p+1,strlen(p+1)) == FALSE)
			   raiseError(ERR_INVALID_ARG_PORT_VALUE);

		    high = atoi(p+1);

		    if ( low > high)
 		          raiseError(ERR_INVALID_ARG_PORT_VALUE);
                   
		    totalPortsNr += high-low + 1;

		    free(anothertok);
		}

	   tok = strtok(NULL,",");		
	}	

    

    (*portsNr)    = totalPortsNr;
    numberOfPorts = totalPortsNr;
    (*destPorts) = (int*) malloc(sizeof(int)* totalPortsNr);
    idx = 0;

    tok = strtok(argccopy+3,",");
    while (tok != NULL) 
  	{
	   if (strchr(tok,'-') == NULL)
   		{
	            (*destPorts)[idx++] = atoi(tok);

		}
           else 
	        {
                    
                    p = strchr(tok,'-');
		    i = p - tok;
		    
		    anothertok = strndup(tok,i+1);
                    
		    strncpy(anothertok,tok,i);
	            
                    
		    low  = atoi(anothertok);
                    
		    
		    high = atoi(p+1);
     	       	    
		    for (i=low;i<=high;i++)
 			   (*destPorts)[idx++]=i;
		    
		    free(anothertok);

		}

	   tok = strtok(NULL,",");		
	}

   free(argccopy);
}




int checkPort(char* port,int digitnr)
{
  int i = 0;

  for (i=0;i<digitnr;i++)
         if (!isdigit(port[i]))
                 return FALSE;
  	
  return TRUE;
}




char* getLocalIpAddress()
{
   char *address = (char*) malloc (sizeof(char)*INET_ADDRSTRLEN);
   
   struct ifaddrs *ifAddresses;
   struct ifaddrs *ifit;
   struct in_addr *addrPtr;

   getifaddrs(&ifAddresses);

   for( ifit = ifAddresses; ifit !=NULL; ifit = ifit->ifa_next) 
			{
			  if (!ifit->ifa_addr)
				continue;
                          if (ifit->ifa_addr->sa_family == AF_INET)
				{
				   addrPtr = &((struct sockaddr_in*)ifit->ifa_addr)->sin_addr;
 				   
				   inet_ntop(AF_INET,addrPtr,address,INET_ADDRSTRLEN);
				   
                                   if (strcmp(SRC_INTERFACE,ifit->ifa_name) ==0)
					return address;
				}
			}

   return address;
}


void* fillIpHeader(char* packetDGRAM,char* sourceIp)
{
   struct iphdr *ipHeader=(struct iphdr*) packetDGRAM;
   
   ipHeader->ihl     	 = INTERNET_HEADER_LEN;
   ipHeader->version 	 = IPV4_VERSION; 
   ipHeader->tos     	 = 0;
   ipHeader->tot_len 	 = sizeof(struct tcphdr) + sizeof(struct ip);
   ipHeader->id          = 49728;
   ipHeader->frag_off    = htons(16384);
   ipHeader->ttl	 = 64;
   ipHeader->protocol    = IPPROTO_TCP;
   ipHeader->check 	 = 0;
   ipHeader->saddr       = inet_addr(sourceIp);
   ipHeader->daddr       = destAddr;
   
   ipHeader->check       = calculateChecksum((unsigned short*) packetDGRAM,ipHeader->tot_len >>1);
}


unsigned short calculateChecksum(unsigned short* p,int n)
{
    register long sum;

    unsigned short odd;
    
    sum=0;
    while (n >1) 
   	{
          sum =sum +  *p++;
          n= n - 2;
	}
   
    if (n == 1)
	{
	  odd =0;
          *((u_char*)&odd)=*(u_char*)p;
  	  sum= sum + odd;
	}
  
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum <<16);

    return (short)~sum; 
}


void fillTcpHeader(struct tcphdr* tcpHeader)
{
  tcpHeader->source 	= htons(SOURCE_PORT);
  tcpHeader->seq	= htonl(1074853483);
  tcpHeader->ack_seq    = 0;
  tcpHeader->doff	= sizeof(struct tcphdr)/4;
  tcpHeader->fin	= 0;
  tcpHeader->syn	= 1;
  tcpHeader->rst	= 0;
  tcpHeader->psh	= 0;
  tcpHeader->ack	= 0;
  tcpHeader->urg	= 0;
  tcpHeader->window 	= htons( MAX_TCP_WINDOW_SIZE);
  tcpHeader->check      = 0;
  tcpHeader->urg_ptr    = 0;
}



void informKernelHeadersIncluded(int sock)
{
   int unu = 1;
   const int *pUnu = &unu;

   if ( setsockopt(sock,IPPROTO_IP,IP_HDRINCL, pUnu,sizeof(unu)) <0)
            raiseError(ERR_IP_HEADER_INCLUDED);
}


void createSnifferThread()
{
    if ( pthread_create(&threadSniffer,NULL,sniffer_thread_callback,NULL) <0 )
  		 raiseError(ERR_SNIFFER_THREAD);
}


void* sniffer_thread_callback(void* pointer)
{
   sniffNetworkTraffic();
}



void sendSYNpackets(int portsNr,int *ports,char* packetDGRAM,int sock,char* sourceIp)
{
     int i,port;

     struct sockaddr_in destination;
     struct pseudoheader pseudoHeader;
     struct tcphdr *tcpHeader = (struct tcphdr*) (packetDGRAM+ sizeof(struct ip));

     destination.sin_family = AF_INET;
     destination.sin_addr.s_addr = destAddr;
   
     for (i=0;i<portsNr;i++) 
	{
           port = ports[i];
           
           tcpHeader->dest    = htons(port);
           tcpHeader->check   = 0;
     
           pseudoHeader.src_address    = inet_addr(sourceIp);
           pseudoHeader.dst_address    = destAddr;
           pseudoHeader.placeholder    = 0;
   	   pseudoHeader.proto          = IPPROTO_TCP;
           pseudoHeader.lengthTCP      = htons(sizeof(struct tcphdr));

           memcpy(&pseudoHeader.tcpHeader,tcpHeader,sizeof(struct tcphdr));
   
           tcpHeader->check = calculateChecksum((unsigned short*)&pseudoHeader,sizeof(struct pseudoheader));

           if (sendto(sock,packetDGRAM,sizeof(struct iphdr) + sizeof(struct tcphdr),0,(struct sockaddr*)& destination,sizeof(destination)) <0)
		raiseError(ERR_SEND_SYN_PACKET);
          usleep(1);
	}

   close(sock);
     
}


void sniffNetworkTraffic()
{
  int rawSock;

  int portAnswerNr = 0;  

  int dataSize,saddrSize;
  struct sockaddr saddr;

  struct iphdr*  ipHeader;
  struct tcphdr* tcpHeader;

  saddrSize = sizeof(saddr);

  unsigned char* buffer = (unsigned char*) malloc(65536);

  rawSock = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
   if (rawSock < 0 ) 
	raiseError(ERR_SOCKET_CREATE);
  
  while(1)
 	{ 

	  dataSize = recvfrom(rawSock,buffer,65536,0,&saddr,&saddrSize);
  
          if (dataSize <0)
              raiseError(ERR_RECEIVE_PACKETS);
          
          ipHeader = (struct iphdr*) buffer;

          tcpHeader = (struct tcphdr*) (buffer+ (ipHeader->ihl*4));

          if (ipHeader->saddr == destAddr)
 		{
			if (tcpHeader->syn==1 && tcpHeader->ack==1 )
		                 port_status[ntohs(tcpHeader->source)] = 1;
                   
                   portAnswerNr++;
                   
                   if (portAnswerNr == numberOfPorts)                          
			    break;
		         
		}
	}

   free(buffer);
   close(rawSock);
}


void printPortStatuses(int*ports ,int nr)
{
    int i;
    
    for (i=0;i<nr;i++)
          	{
	            printf("%d - ",ports[i]);
                    if ( port_status[ports[i]] == 1)
				printf("OPEN\n");
                    else
				printf("CLOSED\n");
		}
}

