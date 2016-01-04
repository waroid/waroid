/*
 * Taurus.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Taurus.h"

namespace TAURUS
{
	const int MOTOR_COUNT = 2;
	const int DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//0:motor0, 0:motor1
	{ 0, 0 },		//idle
	{ 1, 1 },	//forward
	{ 0, 0 },	//right forward
	{ 1, -1 },	//right
	{ 0, 0 },	//right backward
	{ -1, -1 },	//backward
	{ 0, 0 },	//left backward
	{ -1, 1 },	//left
	{ 0, 0 },	//left forward
	{ 0, 0 },		//turn right
	{ 0, 0 },	//turn left
	};
}
using namespace TAURUS;

Taurus::Taurus(int index)
		: Robot(EROBOT::TAURUS, index)
{
	// TODO Auto-generated constructor stub

}

Taurus::~Taurus()
{
	// TODO Auto-generated destructor stub
}

bool Taurus::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_gatlingGun.open());
	GCHECK_RETFALSE(m_picoBorgReverse.open());

	return true;
}

void Taurus::onStop()
{
	m_picoBorgReverse.close();
	m_gatlingGun.close();
	Robot::onStop();
}

void Taurus::onReset()
{
	m_gatlingGun.init();
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Taurus::onFire(int data0, int data1)
{
	(data0 == 1) ? m_gatlingGun.on() : m_gatlingGun.off();
}

void Taurus::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ROBOT_MAX_SPEED) speed = ROBOT_MAX_SPEED - 1;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * g_speedScale[speed], DIRECTION_DATA[dir][1] * g_speedScale[speed]);
}

