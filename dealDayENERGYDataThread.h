#if !defined(DealDayENERGYDataThread_H_ZZG)
#define DealDayENERGYDataThread_H_ZZG

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dealMainServiceThread.h"

class DealDayENERGYDataThread : public DealMainServiceThread  
{
public:
	DealDayENERGYDataThread();
	virtual ~DealDayENERGYDataThread();
	void stop();


public:

private:
	virtual void run();

};

#endif // DealDayENERGYDataThread_H_ZZG
