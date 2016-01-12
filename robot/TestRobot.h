/*
 * TestRobot.h
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#ifndef TESTROBOT_H_
#define TESTROBOT_H_

#include "../module/TestModule.h"
#include "Robot.h"

class TestRobot: public Robot
{
public:
	TestRobot(int index);
	virtual ~TestRobot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);

protected:
	TestModule m_testModule;
};

#endif /* TESTROBOT_H_ */
