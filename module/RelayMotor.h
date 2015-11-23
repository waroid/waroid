/*
 * RelayMotor.h
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#ifndef RELAYMOTOR_H_
#define RELAYMOTOR_H_

#include "IModule.h"

class RelayMotor: public IModule
{
public:
	RelayMotor();
	virtual ~RelayMotor();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void on();
	void off();
};

#endif /* RELAYMOTOR_H_ */
