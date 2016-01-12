/*
 * TestModule.h
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#ifndef TESTMODULE_H_
#define TESTMODULE_H_

#include "IModule.h"

class TestModule: public IModule
{
public:
	TestModule();
	virtual ~TestModule();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void move();

protected:
	int m_fd;
};

#endif /* TESTMODULE_H_ */
