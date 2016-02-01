/*
 * Scorpiobot.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Scorpiobot.h"

namespace SCORPIOBOT
{
	const int MOTOR_COUNT = 3;
	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//0:motor0, 0:motor1, 1:motor0
	{ 0.0, 0.0, 0.0 },	//idle
	{ 1.0, 1.0, 0.0 },	//forward
	{ 0.0, 0.0, 0.0 },	//right forward
	{ 0.333, -0.333, 0.667 },	//right
	{ 0.0, 0.0, 0.0 },	//right backward
	{ -1.0, -1.0, 0.0 },	//backward
	{ 0.0, 0.0, 0.0 },	//left backward
	{ -0.333, 0.333, -0.667 },	//left
	{ 0.0, 0.0, 0.0 },	//left forward
	{ 1.0, -1.0, -1.0 },	//turn right
	{ -1.0, 1.0, 1.0 },	//turn left
	};

	const float SPEED_DATA1[ESPEED::TOTAL] =
	{ 0.0, 0.35, 0.6, 0.85 };

	const float SPEED_DATA2[ESPEED::TOTAL] =
	{ 0.0, 0.6, 0.8, 1.0 };

}
using namespace SCORPIOBOT;

Scorpiobot::Scorpiobot(char team)
		: Robot(EROBOT::SCORPIOBOT, team), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
{
	// TODO Auto-generated constructor stub

}

Scorpiobot::~Scorpiobot()
{
	// TODO Auto-generated destructor stub
}

bool Scorpiobot::onStart()
{
	GCHECK_RETFALSE(m_picoBorgReverse0.open());
	GCHECK_RETFALSE(m_picoBorgReverse1.open());

	m_weapons[0] = createWeapon(EWEAPON::XM214_MICROGUN, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Scorpiobot::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();
	Robot::onStop();
}

void Scorpiobot::onReset()
{
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Scorpiobot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	if (dir == EDIRECTION::LEFT || dir == EDIRECTION::RIGHT)
	{
		m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * SPEED_DATA2[speed], DIRECTION_DATA[dir][1] * SPEED_DATA2[speed]);
		m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * SPEED_DATA2[speed], 0);
	}
	else
	{
		m_picoBorgReverse0.move(DIRECTION_DATA[dir][0] * SPEED_DATA1[speed], DIRECTION_DATA[dir][1] * SPEED_DATA1[speed]);
		m_picoBorgReverse1.move(DIRECTION_DATA[dir][2] * SPEED_DATA1[speed], 0);
	}
}

