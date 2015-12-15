/*
 * BatteryChecker.h
 *
 *  Created on: Dec 15, 2015
 *      Author: mirime
 */

#ifndef BATTERYCHECKER_H_
#define BATTERYCHECKER_H_

#include <pthread.h>
#include "IModule.h"

class BatteryChecker: public IModule
{
public:
	BatteryChecker();
	virtual ~BatteryChecker();

	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	float getVolts() const
	{
		return m_volts;
	}

protected:
	void loop();
	int readAdc();

protected:
	float m_volts;
	pthread_t m_thread;

protected:
	static void* worker(void* param);
};

#endif /* BATTERYCHECKER_H_ */
