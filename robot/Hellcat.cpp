/*
 * Hellcat.cpp
 *
 *  Created on: Dec 30, 2015
 *      Author: mirime
 */

#include "Hellcat.h"

#include <wiringPi.h>
#include "../core/Logger.h"
namespace HELLCAT
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
using namespace HELLCAT;

Hellcat::Hellcat(int index)
: Robot(EROBOT::HELLCAT, index)
{
	// TODO Auto-generated constructor stub

}

Hellcat::~Hellcat()
{
	// TODO Auto-generated destructor stub
}

bool Hellcat::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_gatlingGun.open());
	GCHECK_RETFALSE(m_picoBorgReverse.open());

	return true;
}

void Hellcat::onStop()
{
	m_picoBorgReverse.close();
	m_gatlingGun.close();
	Robot::onStop();
}

void Hellcat::onReset()
{
	m_gatlingGun.init();
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Hellcat::onFire(int data0, int data1)
{
	(data0 == 1) ? m_gatlingGun.on() : m_gatlingGun.off();
}

void Hellcat::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ROBOT_MAX_SPEED) speed = ROBOT_MAX_SPEED - 1;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * g_speedScale[speed], DIRECTION_DATA[dir][1] * g_speedScale[speed]);
}
