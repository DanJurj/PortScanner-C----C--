#pragma once
#include"Exception.h"
struct DescriptedPort
{
	int		m_PortNumber;
	char*	m_description;
	DescriptedPort* next;
	DescriptedPort()
	{
		m_description=NULL;
		next=NULL;
	}
	DescriptedPort(int nr,char* description)
	{
		m_PortNumber=nr;
		m_description=_strdup(description);
		CHECK_ALOC(m_description);
		next=NULL;
	}
	~DescriptedPort()
	{
		if(m_description)
			delete[]m_description;
	}
};
class CDescriptedPorts
{
	public:
	DescriptedPort *firstPort , *lastPort;
	CDescriptedPorts(void);
	CDescriptedPorts(char* filename);
	virtual ~CDescriptedPorts(void);
	void addPort(int nr,char* descriere);
};

