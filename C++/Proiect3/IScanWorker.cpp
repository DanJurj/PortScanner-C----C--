#include "IScanWorker.h"


IScanWorker::IScanWorker(void)
{
	PingBeforeScan=TRUE;
	ScanForCommonPorts=FALSE;
}


IScanWorker::~IScanWorker(void)
{

}

void IScanWorker::setPingBeforeScan(bool value)
{
	PingBeforeScan=value;
}

void IScanWorker::setScanForCommonPorts(bool value)
{
	ScanForCommonPorts=value;
}

