/*
 * Toad.cpp
 *
 *  Created on: 2015. 2. 16.
 *      Author: mirime
 */

#include "Toad.h"

namespace TOAD
{
	const int MOTOR_COUNT = 4;

	const int DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//0:motor0, 0:motor1, 1:motor0, 1:motor1
	{ 0, 0, 0, 0 },		//idle
	{ 1, 1, 1, 1 },	//forward
	{ 0, 0, 0, 0 },	//right forward
	{ 1, -1, -1, 1 },	//right
	{ 0, 0, 0, 0 },	//right backward
	{ -1, -1, -1, -1 },	//backward
	{ 0, 0, 0, 0 },	//left backward
	{ -1, 1, 1, -1 },	//left
	{ 0, 0, 0, 0 },	//left forward
	{ 1, -1, 1, -1 },		//turn right
	{ -1, 1, -1, 1 },	//turn left
	};
}
using namespace TOAD;

Toad::Toad(int index)
		: Robot(EROBOT::TOAD, index), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
{
	// TODO Auto-generated constructor stub

}

Toad::~Toad()
{
	// TODO Auto-generated destructor stub
}

bool Toad::onStart()
{
	if (Robot::onStart() == false) return false;

	if (m_picoBorgReverse0.open() == false) return false;

	if (m_picoBorgReverse1.open() == false) return false;

	return true;
}

void Toad::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();

	Robot::onStop();
}

void Toad::onReset()
{
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Toad::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ROBOT_MAX_SPEED) speed = ROBOT_MAX_SPEED - 1;

	m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * g_speedScale[speed], DIRECTION_DATA[dir][1] * g_speedScale[speed]);
	m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * g_speedScale[speed], DIRECTION_DATA[dir][3] * g_speedScale[speed]);
}
