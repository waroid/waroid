/*
 * Warthogbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "../Global.h"
#include "Warthogbot.h"

namespace WARTHOGBOT
{
	const char DIRECTION_DATA[EDIRECTION::TOTAL] =
	{
	ARDUINO_MOT_BASIC,			//idle
	ARDUINO_MOT_FORWARD,		//forward
	ARDUINO_MOT_BASIC,			//right forward
	ARDUINO_MOT_RIGHT_SLIDE,	//right
	ARDUINO_MOT_BASIC,			//right backward
	ARDUINO_MOT_BACKWARD,		//backward
	ARDUINO_MOT_BASIC,			//left backward
	ARDUINO_MOT_LEFT_SLIDE,		//left
	ARDUINO_MOT_BASIC,			//left forward
	ARDUINO_MOT_RIGHT_TURN,		//turn right
	ARDUINO_MOT_LEFT_TURN,		//turn left
	};

	const char SPEED_DATA[ESPEED::TOTAL] =
	{ 0x00, 0x01, 0x02, 0x03 };
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
	GCHECK_RETFALSE(m_arduinoBoard.open());

	m_weapons[0] = createWeapon(EWEAPON::GAU_19_B_HMG, true);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Warthogbot::onStop()
{
	m_arduinoBoard.close();
	Robot::onStop();
}

void Warthogbot::onReset()
{
	m_arduinoBoard.init();
	Robot::onReset();
}

void Warthogbot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_arduinoBoard.motion(DIRECTION_DATA[dir], SPEED_DATA[speed]);
}

