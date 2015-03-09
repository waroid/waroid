/*
 * ServoMotor.h
 *
 *  Created on: Mar 9, 2015
 *      Author: mirime
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "IModule.h"

class ServoMotor: public IModule
{
public:
	ServoMotor();
	virtual ~ServoMotor();

	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void rotate(int angle);
};

#endif /* SERVOMOTOR_H_ */
