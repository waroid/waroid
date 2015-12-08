/*
 * Scorpio.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include "core/Logger.h"
#include "Scorpio.h"

namespace SCORPIO
{
	const int DIRECTION_COUNT = 11;

	const float DIRECTION_SPEED[ROBOT_MAX_SPEED][5] =
	{
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },			//speed 0
	{ 0.0, 0.31, -0.291, 0.21, -0.197 },	//speed 1
	{ 0.0, 0.505, -0.495, 0.31, -0.291 },	//speed 1
	{ 0.0, 0.776, -0.747, 0.40, -0.39 },	//speed 1
	{ 0.0, 0.997, -0.992, 0.505, -0.495 },	//speed 1
	};

	const int DIRECTION_DATA[DIRECTION_COUNT][3] =
	{
	{ 0, 0, 0 },			//idle
	{ 1, 1, 0 },			//forward
	{ 1, 0, 1 },	//right forward
	{ 3, 4, 1 },		//right
	{ 0, 2, 1 },	//right backward
	{ 2, 2, 0 },		//backward
	{ 2, 0, 2 },	//left backward
	{ 3, 4, 2 },	//left
	{ 0, 1, 2 },	//left forward
	{ 1, 2, 2 },	//turn right
	{ 2, 1, 1 },	//turn left
	};

}
using namespace SCORPIO;

Scorpio::Scorpio(int index)
		: Robot(EROBOT::SCORPIO, index), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
{
	// TODO Auto-generated constructor stub

}

Scorpio::~Scorpio()
{
	// TODO Auto-generated destructor stub
}

bool Scorpio::onStart()
{
	if (Robot::onStart() == false) return false;
	if (m_relayMotor.open() == false) return false;
	if (m_picoBorgReverse0.open() == false) return false;
	if (m_picoBorgReverse1.open() == false) return false;

	return true;
}

void Scorpio::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();
	m_relayMotor.close();
	Robot::onStop();
}

void Scorpio::onReset()
{
	m_relayMotor.init();
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Scorpio::onFire(int data0, int data1)
{
	(data0 == 1) ? m_relayMotor.on() : m_relayMotor.off();
}

void Scorpio::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= DIRECTION_COUNT) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ROBOT_MAX_SPEED) speed = ROBOT_MAX_SPEED - 1;

	float motor[3] =
	{ 0.0, 0.0, 0.0 };
	for (int i = 0; i < 3; ++i)
	{
		motor[i] =  DIRECTION_SPEED[speed][DIRECTION_DATA[dir][i]];
	}
	m_picoBorgReverse0.move(motor[0], motor[1]);
	m_picoBorgReverse1.move(motor[2], 0);

	GLOG("motor=%f,%f,%f", motor[0], motor[1], motor[2]);
}

