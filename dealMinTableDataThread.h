#if !defined(DealMinTableDataThread_H_ZZG)
#define DealMinTableDataThread_H_ZZG

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dealMainServiceThread.h"

class DealMinTableDataThread : public DealMainServiceThread  
{
public:
	DealMinTableDataThread();
	virtual ~DealMinTableDataThread();
	void stop();


public:

private:
	virtual void run();

};

#endif // DealMinTableDataThread_H_ZZG
