/*
 * Thorbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Thorbot.h"

namespace THORBOT
{
}
using namespace THORBOT;

Thorbot::Thorbot(char team)
		: Robot(EROBOT::THORBOT, team)
{
	// TODO Auto-generated constructor stub

}

Thorbot::~Thorbot()
{
	// TODO Auto-generated destructor stub
}

bool Thorbot::onStart()
{
	GCHECK_RETFALSE(m_aduinoBoard.open());

	m_weapons[0] = createWeapon(EWEAPON::M61_VULCAN, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Thorbot::onStop()
{
	m_aduinoBoard.close();
	Robot::onStop();
}

void Thorbot::onReset()
{
	m_aduinoBoard.init();
	Robot::onReset();
}

void Thorbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_aduinoBoard.move(dir, speed);
}
