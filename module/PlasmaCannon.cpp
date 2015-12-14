/*
 * PlasmaCannon.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "../core/Logger.h"
#include "PlasmaCannon.h"

namespace PLASMA_CANNON
{
	const int GPIO_NUM = 7;
}
using namespace PLASMA_CANNON;

PlasmaCannon::PlasmaCannon()
		: m_repeat(false)
{
	// TODO Auto-generated constructor stub
}

PlasmaCannon::~PlasmaCannon()
{
	// TODO Auto-generated destructor stub
}

const char* PlasmaCannon::getDescription() const
{
	return "Plasma Cannon Controller";
}

bool PlasmaCannon::open()
{
	pinMode(GPIO_NUM, OUTPUT);

	GCHECK_RETFALSE(pthread_mutex_init(&m_threadMutex, NULL)==0);
	GCHECK_RETFALSE(pthread_cond_init(&m_threadCond, NULL)==0);
	GCHECK_RETFALSE(pthread_create(&m_thread, NULL, worker, this)==0);

	init();

	return true;
}

void PlasmaCannon::close()
{
	init();

	if (m_thread >= 0)
	{
		if (pthread_cancel(m_thread) == 0)
		{
			pthread_join(m_thread, NULL);
		}
		GLOG("cancel PlasmaCannon thread");
	}

}

void PlasmaCannon::init()
{
	off();
}

void PlasmaCannon::on()
{
	m_repeat = true;
	pthread_mutex_lock(&m_threadMutex);
	pthread_cond_signal(&m_threadCond);
	pthread_mutex_unlock(&m_threadMutex);
}

void PlasmaCannon::off()
{
	m_repeat = false;
}

void PlasmaCannon::loop()
{
	for (int i = 0; i < 3; ++ i)
	{
		shoot();
	}

	for (;;)
	{
		pthread_mutex_lock(&m_threadMutex);
		pthread_cond_wait(&m_threadCond, &m_threadMutex);
		pthread_mutex_unlock(&m_threadMutex);

		while (m_repeat)
		{
			shoot();
			delay(500);
		}
	}
}

void PlasmaCannon::shoot()
{
	digitalWrite(GPIO_NUM, 1);
	delay(50);
	digitalWrite(GPIO_NUM, 0);
}

void* PlasmaCannon::worker(void* param)
{
	GLOG("start PlasmaCannon thread");
	((PlasmaCannon*) param)->loop();
	GLOG("stop PlasmaCannon thread");

	return NULL;
}
