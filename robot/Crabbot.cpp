/*
 * Crabbot.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Crabbot.h"

namespace CRABBOT
{
	const int MOTOR_COUNT = 2;
	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//motor0, motor1
	{ 0.0, 0.0 },	//idle
	{ 1.0, 1.0 },	//forward
	{ 1.0, 0.5 },	//right forward
	{ 1.0, -1.0 },	//right
	{ -1.0, -0.5 },	//right backward
	{ -1.0, -1.0 },	//backward
	{ -0.5, -1.0 },	//left backward
	{ -1.0, 1.0 },	//left
	{ 0.5, 1.0 },	//left forward
	{ 0.0, 0.0 },	//turn right
	{ 0.0, 0.0 },	//turn left
	};
	const float SPEED_DATA[ESPEED::TOTAL] =
	{ 0.0, 0.35, 0.6, 0.85 };
}
using namespace CRABBOT;

Crabbot::Crabbot(char team)
		: Robot(EROBOT::CRABBOT, team)
{
	// TODO Auto-generated constructor stub

}

Crabbot::~Crabbot()
{
	// TODO Auto-generated destructor stub
}

bool Crabbot::onStart()
{
	GCHECK_RETFALSE(m_picoBorgReverse.open());

	m_weapons[0] = createWeapon(EWEAPON::M134D_MINIGUN, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Crabbot::onStop()
{
	m_picoBorgReverse.close();
	Robot::onStop();
}

void Crabbot::onReset()
{
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Crabbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
}
