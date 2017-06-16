#pragma once
#include"Exception.h"
class CSyntaxChecker
{
	bool CheckIP(char* IPAdress);
	bool CheckPort(char* portNumber);
public:
	CSyntaxChecker(void);
	virtual ~CSyntaxChecker(void);
	bool CheckIP_range(const char* IPAdresses);
	bool CheckPorts(const char* portNumbers);
};

