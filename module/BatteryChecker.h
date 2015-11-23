/*
 * BatteryChecker.h
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#ifndef BATTERYCHECKER_H_
#define BATTERYCHECKER_H_

#include "IModule.h"

class BatteryChecker: public IModule
{
public:
	BatteryChecker();
	virtual ~BatteryChecker();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	float volt();

protected:
	int	read();
};

#endif /* BATTERYCHECKER_H_ */
