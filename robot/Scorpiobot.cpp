/*
 * Scorpiobot.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Scorpiobot.h"

namespace SCORPIOBOT
{
	const int MOTOR_COUNT = 3;
	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//0:motor0, 0:motor1, 1:motor0
	{ 0.0, 0.0, 0.0 },	//idle
	{ 1.0, -1.0, 0.0 },	//forward
	{ 0.0, 0.0, 0.0 },	//right forward
	{ 0.0, 0.0, 0.0 },	//right
	{ 0.0, 0.0, 0.0 },	//right backward
	{ -1.0, 1.0, 0.0 },	//backward
	{ 0.0, 0.0, 0.0 },	//left backward
	{ 0.0, 0.0, 0.0 },	//left
	{ 0.0, 0.0, 0.0 },	//left forward
	{ 1.0, 1.0, 1.0 },	//turn right
	{ -1.0, -1.0, -1.0 },	//turn left
	};

	const float SPEED_DATA[ESPEED::TOTAL] =
	{ 0.0, 0.25, 0.5, 1.0 };
}
using namespace SCORPIOBOT;

Scorpiobot::Scorpiobot(char team)
		: Robot(EROBOT::SCORPIOBOT, team), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
{
	// TODO Auto-generated constructor stub

}

Scorpiobot::~Scorpiobot()
{
	// TODO Auto-generated destructor stub
}

bool Scorpiobot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_gatlingGun.open());
	GCHECK_RETFALSE(m_picoBorgReverse0.open());
	GCHECK_RETFALSE(m_picoBorgReverse1.open());

	return true;
}

void Scorpiobot::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();
	m_gatlingGun.close();
	Robot::onStop();
}

void Scorpiobot::onReset()
{
	m_gatlingGun.init();
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Scorpiobot::onFire(int data0, int data1)
{
	(data0 == 1) ? m_gatlingGun.on() : m_gatlingGun.off();
}

void Scorpiobot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
	m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * SPEED_DATA[speed], 0);
}

