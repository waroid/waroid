/*
 * Taurusbot.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Taurusbot.h"

namespace TAURUSBOT
{
	const int MOTOR_COUNT = 2;
	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//motor0, motor1
	{ 0.0, 0.0 },	//idle
	{ 1.0, 1.0 },	//forward
	{ 1.0, 0.5 },	//right forward
	{ 1.0, -1.0 },	//right
	{ -1.0, -0.5 },	//right backward
	{ -1.0, -1.0 },	//backward
	{ -0.5, -1.0 },	//left backward
	{ -1.0, 1.0 },	//left
	{ 0.5, 1.0 },	//left forward
	{ 0.0, 0.0 },	//turn right
	{ 0.0, 0.0 },	//turn left
	};
	const float SPEED_DATA[ESPEED::TOTAL] =
	{ 0.0, 0.25, 0.5, 1.0 };
}
using namespace TAURUSBOT;

Taurusbot::Taurusbot(char team)
		: Robot(EROBOT::TAURUSBOT, team)
{
	// TODO Auto-generated constructor stub

}

Taurusbot::~Taurusbot()
{
	// TODO Auto-generated destructor stub
}

bool Taurusbot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_gatlingGun.open());
	GCHECK_RETFALSE(m_picoBorgReverse.open());

	return true;
}

void Taurusbot::onStop()
{
	m_picoBorgReverse.close();
	m_gatlingGun.close();
	Robot::onStop();
}

void Taurusbot::onReset()
{
	m_gatlingGun.init();
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Taurusbot::onFire(int data0, int data1)
{
	(data0 == 1) ? m_gatlingGun.on() : m_gatlingGun.off();
}

void Taurusbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
}

