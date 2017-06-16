#pragma once
#include"Coada.h"
typedef enum
{
	IP,PORT
}WType;
class CStringWorker
{
protected:
	WType workType;
public:
	CStringWorker();
	CStringWorker(WType tip);
	virtual void genereaza(const char *)=0;
	virtual ~CStringWorker();
};