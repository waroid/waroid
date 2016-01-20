/*
 * Taurusbot.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Taurusbot.h"

namespace TAURUSBOT
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
	{ 0.0, 0.4, 0.7, 1.0 };
}
using namespace TAURUSBOT;

Taurusbot::Taurusbot(char team)
		: Robot(EROBOT::TAURUSBOT, team)
{
	// TODO Auto-generated constructor stub

}

Taurusbot::~Taurusbot()
{
	// TODO Auto-generated destructor stub
}

bool Taurusbot::onStart()
{
	GCHECK_RETFALSE(m_picoBorgReverse.open());

	m_weapons[0] = createWeapon(EWEAPON::GAU_19_B_HMG, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Taurusbot::onStop()
{
	m_picoBorgReverse.close();
	Robot::onStop();
}

void Taurusbot::onReset()
{
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Taurusbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
}

