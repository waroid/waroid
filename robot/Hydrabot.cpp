/*
 * Hydrabot.cpp
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "../weapon/Rocket.h"
#include "Hydrabot.h"

namespace HYDRABOT
{
	const int MOTOR_COUNT = 2;
	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//motor0, motor1
	{ 0.0, 0.0 },	//idle
	{ 1.0, 1.0 },	//forward
	{ 1.25, 0.75 },	//right forward
	{ 1.0, -1.0 },	//right
	{ -1.25, -0.75 },	//right backward
	{ -1.0, -1.0 },	//backward
	{ -0.75, -1.25 },	//left backward
	{ -1.0, 1.0 },	//left
	{ 0.75, 1.25 },	//left forward
	{ 0.0, 0.0 },	//turn right
	{ 0.0, 0.0 },	//turn left
	};
	const float SPEED_DATA[ESPEED::TOTAL] =
	{ 0.0, 0.45, 0.55, 0.65 };
}
using namespace HYDRABOT;

Hydrabot::Hydrabot(char team)
		: Robot(EROBOT::HYDRABOT, team)
{
	// TODO Auto-generated constructor stub

}

Hydrabot::~Hydrabot()
{
	// TODO Auto-generated destructor stub
}

bool Hydrabot::onStart()
{
	GCHECK_RETFALSE(m_picoBorgReverse.open());

	m_weapons[0] = createWeapon(EWEAPON::STARSTREAK_AVENGER, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Hydrabot::onStop()
{
	m_picoBorgReverse.close();
	Robot::onStop();
}

void Hydrabot::onReset()
{
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Hydrabot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
}

void Hydrabot::onControlTurret(int data0, int data1)
{
	GCHECK_RETURN(data0 >= ROBOT_MIN_TURRET_ANGLE && data0 <= ROBOT_MAX_TURRET_ANGLE);
	GCHECK_RETURN(m_weapons[0] && m_weapons[0]->getKind() == EWEAPONKIND::ROCKET);
	((Rocket*) m_weapons[0])->tilt(data0);
}
