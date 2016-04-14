#include "dealMainServiceThread.h"
#include <qdatetime.h>

#include "SQLFuncPublic.h"

DealMainServiceThread::DealMainServiceThread()
{
	m_bPause = false;
	m_iCommitedLine = 0 ;
	m_iCommitedSize = 0 ; 
}

DealMainServiceThread::~DealMainServiceThread()
{

}

void DealMainServiceThread::stop()
{

}

void DealMainServiceThread::run()
{ 	
 
}


