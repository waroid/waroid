/*
 * Scorpio.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#include "Scorpio.h"

namespace SCORPIO
{
	const int DIRECTION_COUNT = 11;
	const int SPEED_COUNT = 3;

	const int DIRECTION_DATA[DIRECTION_COUNT][4] =
	{
	//0:motor0, 0:motor1, 1:motor0, 1:motor1
	{ 0, 0, 0, 0 },		//idle
	{ -1, -1, 1, 1 },	//forward
	{ 0, -1, 0, 1 },	//right forward
	{ 1, -1, -1, 1 },	//right
	{ 1, 0, -1, 0 },	//right backward
	{ 1, 1, -1, -1 },	//backward
	{ 0, 1, 0, -1 },	//left backward
	{ -1, 1, 1, -1 },	//left
	{ -1, 0, 1, 0 },	//left forward
	{ 1, 1, 1, 1 },		//turn right
	{ -1, -1, -1, -1 },	//turn left
	};

	const float SPEED_DATA[SPEED_COUNT] =
	{ 0.4, 0.6, 0.8 };
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

void Scorpio::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= DIRECTION_COUNT) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= SPEED_COUNT) speed = 0;

	m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
	m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * SPEED_DATA[speed], DIRECTION_DATA[dir][3] * SPEED_DATA[speed]);
}

