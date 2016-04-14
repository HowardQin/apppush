#if !defined(DealENERGYDataThread_H_ZZG)
#define DealENERGYDataThread_H_ZZG

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dealMainServiceThread.h"

class DealENERGYDataThread : public DealMainServiceThread  
{
public:
	DealENERGYDataThread();
	virtual ~DealENERGYDataThread();
	void stop();


public:

private:
	virtual void run();

};

#endif // DealENERGYDataThread_H_ZZG
