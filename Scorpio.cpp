/*
 * Scorpio.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include "Scorpio.h"

namespace SCORPIO
{
	const int DIRECTION_COUNT = 11;
	const float DIRECTION_DATA[DIRECTION_COUNT][4] =
	{
	//move matrix
	//[-0.333, -0.577, 0.333]
	//[-0.333, 0.577, 0.333]
	//[0.667, 0.0, 0.333]
	//A:motor0, A:motor1, B:motor0, B:motor1
	{ 0.0, 0.0, 0.0, 0.0 },		//idle
	{ -0.577, 0.577, 0.0, 0.0 },	//forward
	{ -0.910, 0.244, 0.667, 0 },	//right forward
	{ -0.333, -0.333, 0.667, 0 },	//right
	{ 0.244, -0.910, 0.667, 0 },	//right backward
	{ 0.577, -0.577, 0, 0 },	//backward
	{ 0.910, -0.244, -0.667, 0 },	//left backward
	{ 0.333, 0.333, -0.667, 0 },	//left
	{ -0.244, 0.910, -0.677, 0 },	//left forward
	{ -0.333, -0.333, -0.333, 0 },	//turn right
	{ 0.333, 0.333, 0.333, 0 },		//turn left
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
	else if (speed >= ROBOT_MAX_SPEED) speed = 0;

	m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * g_speedScale[speed], DIRECTION_DATA[dir][1] * g_speedScale[speed]);
	m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * g_speedScale[speed], DIRECTION_DATA[dir][3] * g_speedScale[speed]);
}

