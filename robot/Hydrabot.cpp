/*
 * Hydrabot.cpp
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Hydrabot.h"

namespace HYDRABOT
{
	const int TURRET_OFFSET_ANGLE = 5;

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
	{ 0.0, 0.25, 0.5, 1.0 };
}
using namespace HYDRABOT;

Hydrabot::Hydrabot(char team)
		: Robot(EROBOT::HYDRABOT, team), m_missileTurret(TURRET_OFFSET_ANGLE)
{
	// TODO Auto-generated constructor stub

}

Hydrabot::~Hydrabot()
{
	// TODO Auto-generated destructor stub
}

bool Hydrabot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_picoBorgReverse.open());
	GCHECK_RETFALSE(m_missileTurret.open());

	return true;
}

void Hydrabot::onStop()
{
	m_missileTurret.close();
	m_picoBorgReverse.close();
	Robot::onStop();
}

void Hydrabot::onReset()
{
	m_picoBorgReverse.init();
	m_missileTurret.init();
	Robot::onReset();
}

void Hydrabot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
}

void Hydrabot::onControlTurret(int data0, int data1)
{
	controlTurret(data0);
}

void Hydrabot::controlTurret(int angle)
{
	if (angle < ROBOT_MIN_TURRET_ANGLE) angle = ROBOT_MIN_TURRET_ANGLE;
	else if (angle > ROBOT_MAX_TURRET_ANGLE) angle = ROBOT_MAX_TURRET_ANGLE;

	m_missileTurret.rotate(angle);
}
