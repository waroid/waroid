/*
 * Toad.cpp
 *
 *  Created on: 2015. 2. 16.
 *      Author: mirime
 */

#include "Toad.h"

namespace TOAD
{
	const int DIRECTION_COUNT = 11;
	const int SPEED_COUNT = 3;

	const int DIRECTION_DATA[DIRECTION_COUNT][4] =
	{
	//0:motor0, 0:motor1, 1:motor0, 1:motor1
	{ 0, 0, 0, 0 },		//idle
	{ -1, -1, 1, 1 },	//forward
	{ 0, 0, 0, 0 },	//right forward
	{ 1, -1, -1, 1 },	//right
	{ 0, 0, 0, 0 },	//right backward
	{ 1, 1, -1, -1 },	//backward
	{ 0, 0, 0, 0 },	//left backward
	{ -1, 1, 1, -1 },	//left
	{ 0, 0, 0, 0 },	//left forward
	{ 1, 1, 1, 1 },		//turn right
	{ -1, -1, -1, -1 },	//turn left
	};

	const float SPEED_DATA[SPEED_COUNT] =
	{ 0.4, 0.6, 0.8 };
}
using namespace TOAD;

Toad::Toad() :
		Robot("Toad"), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
{
	// TODO Auto-generated constructor stub

}

Toad::~Toad()
{
	// TODO Auto-generated destructor stub
}

bool Toad::onStart()
{
	if (Robot::onStart() == false)
		return false;

	if (m_picoBorgReverse0.open() == false)
		return false;

	if (m_picoBorgReverse1.open() == false)
		return false;

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
}

void Toad::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0)
		dir = 0;
	else if (dir >= DIRECTION_COUNT)
		dir = 0;

	int speed = data1;
	if (speed < 0)
		speed = 0;
	else if (speed >= SPEED_COUNT)
		speed = 0;

	m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
	m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * SPEED_DATA[speed], DIRECTION_DATA[dir][3] * SPEED_DATA[speed]);
}