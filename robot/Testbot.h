/*
 * TestRobot.h
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#ifndef TESTBOT_H_
#define TESTBOT_H_

#include "../module/TestModule.h"
#include "Robot.h"

class Testbot: public Robot
{
public:
	Testbot(int index);
	virtual ~Testbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	TestModule m_testModule;
};

#endif /* TESTBOT_H_ */
