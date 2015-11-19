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
	const int GPIO_FIRE = 24;

	const int DIRECTION_COUNT = 11;
	const int DIRECTION_DATA[DIRECTION_COUNT][4] =
	{
	//A:motor0, A:motor1, B:motor0, B:motor1
	{ 0, 0, 0, 0 },		//idle
	{ 1, -1, 0, 0 },		//forward
	{ 1, 0, -1, 0 },	//right forward
	{ 1, -1, -1, 0 },	//right
	{ 0, 1, -1, 0 },	//right backward
	{ -1, 1, 0, 0 },	//backward
	{ -1, 0, 1, 0 },	//left backward
	{ -1, -1, 1, 0 },	//left
	{ 0, -1, 1, 0 },	//left forward
	{ 1, 1, 1, 0 },		//turn right
	{ -1, -1, -1, 0 },	//turn left
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

	if (m_picoBorgReverse0.open() == false) return false;

	if (m_picoBorgReverse1.open() == false) return false;

	return true;
}

void Scorpio::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();

	Robot::onStop();
}

void Scorpio::onReset()
{
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Scorpio::onFire(int data0, int data1)
{
	bool onoff = (data0 == 1);
	digitalWrite(GPIO_FIRE, onoff ? 1 : 0);
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

