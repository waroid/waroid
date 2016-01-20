/*
 * Warthogbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Warthogbot.h"

namespace WARTHOGBOT
{
}
using namespace WARTHOGBOT;

Warthogbot::Warthogbot(char team)
		: Robot(EROBOT::WARTHOGBOT, team)
{
	// TODO Auto-generated constructor stub

}

Warthogbot::~Warthogbot()
{
	// TODO Auto-generated destructor stub
}

bool Warthogbot::onStart()
{
	GCHECK_RETFALSE(m_aduinoBoard.open());

	m_weapons[0] = createWeapon(EWEAPON::GAU_19_B_HMG, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Warthogbot::onStop()
{
	m_aduinoBoard.close();
	Robot::onStop();
}

void Warthogbot::onReset()
{
	m_aduinoBoard.init();
	Robot::onReset();
}

void Warthogbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	//m_aduinoBoard.move(dir, speed);
}


