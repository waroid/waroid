/*
 * PololuQik.h
 *
 *  Created on: 2015. 2. 12.
 *      Author: mirime
 */

#ifndef POLOLUQIK_H_
#define POLOLUQIK_H_

#include "IModule.h"

class PololuQik: public IModule
{
public:
	PololuQik();
	virtual ~PololuQik();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void move(float power0, float power1);

protected:
	void setMotor0(int power);
	void setMotor1(int power);

protected:
	int m_fd;
};

#endif /* POLOLUQIK_H_ */
