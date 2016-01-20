/*
 * Spiderbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Spiderbot.h"

namespace SPIDERBOT
{
}
using namespace SPIDERBOT;

Spiderbot::Spiderbot(char team)
		: Robot(EROBOT::SPIDERBOT, team)
{
	// TODO Auto-generated constructor stub
}

Spiderbot::~Spiderbot()
{
	// TODO Auto-generated destructor stub
}

bool Spiderbot::onStart()
{
	GCHECK_RETFALSE(m_aduinoBoard.open());

	m_weapons[0] = createWeapon(EWEAPON::BOFORS_L60, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Spiderbot::onStop()
{
	m_aduinoBoard.close();
	Robot::onStop();
}

void Spiderbot::onReset()
{
	m_aduinoBoard.init();
	Robot::onReset();
}

void Spiderbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	//m_aduinoBoard.move(dir, speed);
}
