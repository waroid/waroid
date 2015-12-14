/*
 * GatlingGun.h
 *
 *  Created on: Dec 14, 2015
 *      Author: mirime
 */

#ifndef GATLINGGUN_H_
#define GATLINGGUN_H_

#include "IModule.h"

class GatlingGun: public IModule
{
public:
	GatlingGun();
	virtual ~GatlingGun();

	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void on();
	void off();
};

#endif /* GATLINGGUN_H_ */
