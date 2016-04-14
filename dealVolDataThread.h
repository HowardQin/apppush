#if !defined(DealVolDataThread_H_ZZG)
#define DealVolDataThread_H_ZZG

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dealMainServiceThread.h"

class DealVolDataThread : public DealMainServiceThread  
{
public:
	DealVolDataThread();
	virtual ~DealVolDataThread();
	void stop();


public:

private:
	virtual void run();

};

#endif // DealVolDataThread_H_ZZG
