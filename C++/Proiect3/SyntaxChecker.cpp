#include "SyntaxChecker.h"
#include "SyntaxChecker.h"


CSyntaxChecker::CSyntaxChecker(void)
{
}


CSyntaxChecker::~CSyntaxChecker(void)
{
}

bool CSyntaxChecker::CheckIP(char* IPAdress)
{
	char *ip=new char[strlen(IPAdress)+1];
	int nr_blocuri=0;
	strcpy(ip,IPAdress);
	char *p=strtok(ip,".");
	while(p)
	{
		int x=atoi(p);
		if(x==NULL || x<0 || x>255)
			return false;
		p=strtok(NULL,".");
		nr_blocuri++;
	}
	if(nr_blocuri!=4)
		return false;
	return true;
}

bool CSyntaxChecker::CheckPort(char* portNumber)
{
	int x=atoi(portNumber);
	if (x==NULL || x<0 || x>65724)
		return false;
	else
		return true;
}

bool CSyntaxChecker::CheckIP_range(const char* IPAdresses)
{
	char *ips=new char[strlen(IPAdresses)+1];
	strcpy(ips,IPAdresses);
	char *p=strtok(ips,"-,");
	while(p)
	{
		if(CheckIP(p)==false)
			return false;
		p=strtok(NULL,"-,");
	}
	return true;
}

bool CSyntaxChecker::CheckPorts(const char* portNumbers)
{
	char *ports=new char[strlen(portNumbers)+1];
	strcpy(ports,portNumbers);
	char *p=strtok(ports,"-,");
	while(p)
	{
		if(CheckPort(p)==false)
			return false;
		p=strtok(NULL,"-,");
	}
	return true;
}