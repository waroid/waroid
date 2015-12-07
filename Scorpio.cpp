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
	const float DIRECTION_DATA[DIRECTION_COUNT][3] =
	{
	//move matrix
	//[-1.0, -1.732, 1.0]
	//[-1.0, 1.732, 1.0]
	//[2.0, 0.0, 1.0]
	//A:motor0, A:motor1, B:motor0, Scale
	//{ 0.0, 0.0, 0.0, 1.0 },			//idle
	//{ -1.732, 1.732, 0.0, 1.732 },	//forward
	//{ -2.732, 0.732, 2.0,  2.732 },	//right forward
	//{ -1.0, -1.0, 2.0, 2.0 },		//right
	//{ 0.732, -2.732, 2.0, 2.732 },	//right backward
	//{ 1.732, -1.732, 0, 1.732 },	//backward
	//{ 2.732, -0.732, -2.0, 2.732 },	//left backward
	//{ 1.0, 1.0, -2.0, 2.0 },		//left
	//{ -0.732, 2.732, -2.0, 2.732 },	//left forward
	//{ -1.0, -1.0, -1.0, 1.0 },		//turn right
	//{ 1.0, 1.0, 1.0, 1.0 },			//turn left
	{ 0.0, 0.0, 0.0 },			//idle
	{ 1.0, 1.0, 0.0 },		//forward
	{ 0.995, 0.316, 0.746 },	//right forward
	{ 0.509, -0.5, 0.995 },		//right
	{ -0.3, -0.99, 0.746 },	//right backward
	{ -1.0, -1.0, 0 },		//backward
	{ -0.99, -0.3, -0.733 },	//left backward
	{ -0.5, 0.509, -0.99 },	//left
	{ 0.316, 0.995, -0.733 },	//left forward
	{ 0.995, -0.99, -0.99 },	//turn right
	{ -0.99, 0.995, 0.995 },	//turn left
	};
	const float DIRECTION_SPEED[DIRECTION_COUNT][ROBOT_MAX_SPEED] =
	{
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },			//idle
	{ 0.0, 0.25, 0.5, 0.75, 1.0 },		//forward
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//right forward
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },		//right
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//right backward
	{ 0.0, 0.25, 0.5, 0.75, 1.0 },		//backward
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//left backward
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//left
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//left forward
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//turn right
	{ 0.0, 1.0, 1.0, 1.0, 1.0 },	//turn left
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
		motor[i] = DIRECTION_DATA[dir][i] * DIRECTION_SPEED[dir][speed];
	}
	m_picoBorgReverse0.move(motor[0], motor[1]);
	m_picoBorgReverse1.move(motor[2], 0);

	GLOG("motor=%f,%f,%f", motor[0], motor[1], motor[2]);
}

