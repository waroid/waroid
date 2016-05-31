/*
 * Warbot3.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Warbot3.h"

namespace WARBOT3
{
	const int MOTOR_COUNT = 2;
	const float DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//motor0, motor1
	{ 0.0, 0.0 },	//idle
	{ 1.0, 1.0 },	//forward
	{ 1.0, 0.75 },	//right forward
	{ 1.0, -1.0 },	//right
	{ -1.0, -0.75 },	//right backward
	{ -1.0, -1.0 },	//backward
	{ -0.75, -1.0 },	//left backward
	{ -1.0, 1.0 },	//left
	{ 0.75, 1.0 },	//left forward
	{ 0.0, 0.0 },	//turn right
	{ 0.0, 0.0 },	//turn left
	};
	const float SPEED_DATA[ESPEED::TOTAL] =
	{ 0.0, 0.85, 0.9, 0.95 };
}
using namespace WARBOT3;

Warbot3::Warbot3(char team)
		: Robot(EROBOT::WARBOT3, team)
{
	// TODO Auto-generated constructor stub

}

Warbot3::~Warbot3()
{
	// TODO Auto-generated destructor stub
}

bool Warbot3::onStart()
{
	GCHECK_RETFALSE(m_pololuQik.open());

	m_weapons[0] = createWeapon(EWEAPON::M134D_MINIGUN, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Warbot3::onStop()
{
	m_pololuQik.close();
	Robot::onStop();
}

void Warbot3::onReset()
{
	m_pololuQik.init();
	Robot::onReset();
}

void Warbot3::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_pololuQik.move(DIRECTION_DATA[dir][0] * SPEED_DATA[speed], DIRECTION_DATA[dir][1] * SPEED_DATA[speed]);
}
