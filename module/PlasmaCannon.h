/*
 * PlasmaCannon.h
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#ifndef PLASMACANNON_H_
#define PLASMACANNON_H_

#include <pthread.h>
#include "IModule.h"

class PlasmaCannon: public IModule
{
public:
	PlasmaCannon();
	virtual ~PlasmaCannon();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void on();
	void off();

protected:
	void loop();
	void shoot();

protected:
	bool m_repeat;
	pthread_t m_thread;
	pthread_mutex_t m_threadMutex;
	pthread_cond_t m_threadCond;

protected:
	static void* worker(void* param);

};

#endif /* PLASMACANNON_H_ */
