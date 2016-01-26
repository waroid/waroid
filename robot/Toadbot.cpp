/*
 * Toadbot.cpp
 *
 *  Created on: 2015. 2. 16.
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Toadbot.h"

namespace TOADBOT
{
	const int MOTOR_COUNT = 4;

	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//0:motor0, 0:motor1, 1:motor0, 1:motor1
	{ 0.0, 0.0, 0.0, 0.0 },		//idle
	{ 1.0, 1.0, 1.0, 1.0 },		//forward
	{ 0.0, 0.0, 0.0, 0.0 },		//right forward
	{ 1.0, -1.0, -1.0, 1.0 },	//right
	{ 0.0, 0.0, 0.0, 0.0 },		//right backward
	{ -1.0, -1.0, -1.0, -1.0 },	//backward
	{ 0.0, 0.0, 0.0, 0.0 },		//left backward
	{ -1.0, 1.0, 1.0, -1.0 },	//left
	{ 0.0, 0.0, 0.0, 0.0 },		//left forward
	{ 1.0, -1.0, 1.0, -1.0 },	//turn right
	{ -1.0, 1.0, -1.0, 1.0 },	//turn left
	};
	const float SPEED_DATA[ESPEED::TOTAL] =
	{ 0.0, 0.45, 0.7, 0.95 };
}
using namespace TOADBOT;

Toadbot::Toadbot(char team)
		: Robot(EROBOT::TOADBOT, team), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
{
	// TODO Auto-generated constructor stub

}

Toadbot::~Toadbot()
{
	// TODO Auto-generated destructor stub
}

bool Toadbot::onStart()
{
	GCHECK_RETFALSE(m_picoBorgReverse0.open());
	GCHECK_RETFALSE(m_picoBorgReverse1.open());

	m_weapons[0] = createWeapon(EWEAPON::M242_CHAINGUN, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Toadbot::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();
	Robot::onStop();
}

void Toadbot::onReset()
{
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Toadbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
	m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * SPEED_DATA[speed], DIRECTION_DATA[dir][3] * SPEED_DATA[speed]);
}
