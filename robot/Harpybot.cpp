/*
 * Harpybot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "../Global.h"
#include "Harpybot.h"

namespace HARPYBOT
{
	//roll, pitch, yaw
	const char DIRECTION_DATA[EDIRECTION::TOTAL][3] =
	{
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//idle
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE + 5, DRON_IDEL_VALUE },	//forward
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//right forward
	{ DRON_IDEL_VALUE + 5, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//right
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//right backward
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE - 5, DRON_IDEL_VALUE },	//backward
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//left backward
	{ DRON_IDEL_VALUE - 5, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//left
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE },	//left forward
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE + 5 },	//turn right
	{ DRON_IDEL_VALUE, DRON_IDEL_VALUE, DRON_IDEL_VALUE - 5 },	//turn left
	};
}
using namespace HARPYBOT;

Harpybot::Harpybot(char team)
		: Robot(EROBOT::HARPYBOT, team)
{
	// TODO Auto-generated constructor stub

}

Harpybot::~Harpybot()
{
	// TODO Auto-generated destructor stub
}

bool Harpybot::onStart()
{
	GCHECK_RETFALSE(m_dronBoard.open());

	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Harpybot::onStop()
{
	m_dronBoard.close();
	Robot::onStop();
}

void Harpybot::onReset()
{
	m_dronBoard.init();
	Robot::onReset();
}

void Harpybot::onMove(int data0, int data1)
{
	int dir = data0;
	if (dir < 0 || dir >= EDIRECTION::TOTAL) dir = EDIRECTION::IDLE;

	int speed = data1;
	if (speed < 0 || speed >= ESPEED::TOTAL) speed = ESPEED::NONE;

	m_dronBoard.command(DRON_COMMAND_CONTROL, 1, DIRECTION_DATA[dir][0], DIRECTION_DATA[dir][1], DIRECTION_DATA[dir][2]);

}

void Harpybot::onControlThrottle(int data0, int data1)
{
	m_dronBoard.command(DRON_COMMAND_CONTROL, data0);
}
