/*
 * TestRobot.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "TestRobot.h"

TestRobot::TestRobot(int index)
: Robot(EROBOT::TEST, index)
{
	// TODO Auto-generated constructor stub

}

TestRobot::~TestRobot()
{
	// TODO Auto-generated destructor stub
}

bool TestRobot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_testModule.open());

	return true;
}

void TestRobot::onStop()
{
	m_testModule.close();
	Robot::onStop();
}

void TestRobot::onReset()
{
	m_testModule.init();
	Robot::onReset();
}

void TestRobot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ROBOT_MAX_SPEED) speed = ROBOT_MAX_SPEED - 1;

	//dir, speed => move data
	//m_testModule.move();
}
