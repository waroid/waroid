/*
 * Testbot.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Testbot.h"

namespace TESTBOT
{
}
using namespace TESTBOT;

Testbot::Testbot(int index)
		: Robot(EROBOT::TESTBOT, index)
{
	// TODO Auto-generated constructor stub

}

Testbot::~Testbot()
{
	// TODO Auto-generated destructor stub
}

bool Testbot::onStart()
{
	GCHECK_RETFALSE(m_testModule.open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Testbot::onStop()
{
	m_testModule.close();
	Robot::onStop();
}

void Testbot::onReset()
{
	m_testModule.init();
	Robot::onReset();
}

void Testbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	//m_testModule.move();
}
