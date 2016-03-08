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
	const char OFFSET = 15;
	//roll, pitch, yaw
	const char DIRECTION_DATA[EDIRECTION::TOTAL][3] =
	{
	{ DRON_IDLE_VALUE, DRON_IDLE_VALUE, DRON_IDLE_VALUE },	//idle
	{ DRON_IDLE_VALUE, DRON_IDLE_VALUE + OFFSET, DRON_IDLE_VALUE },	//forward
	{ DRON_IDLE_VALUE + OFFSET, DRON_IDLE_VALUE + OFFSET, DRON_IDLE_VALUE },//right forward
	{ DRON_IDLE_VALUE + OFFSET, DRON_IDLE_VALUE, DRON_IDLE_VALUE },	//right
	{ DRON_IDLE_VALUE + OFFSET, DRON_IDLE_VALUE - OFFSET, DRON_IDLE_VALUE },//right backward
	{ DRON_IDLE_VALUE, DRON_IDLE_VALUE - OFFSET, DRON_IDLE_VALUE },	//backward
	{ DRON_IDLE_VALUE - OFFSET, DRON_IDLE_VALUE - OFFSET, DRON_IDLE_VALUE },//left backward
	{ DRON_IDLE_VALUE - OFFSET, DRON_IDLE_VALUE, DRON_IDLE_VALUE },	//left
	{ DRON_IDLE_VALUE - OFFSET, DRON_IDLE_VALUE + OFFSET, DRON_IDLE_VALUE },//left forward
	{ DRON_IDLE_VALUE, DRON_IDLE_VALUE, DRON_IDLE_VALUE + OFFSET },	//turn right
	{ DRON_IDLE_VALUE, DRON_IDLE_VALUE, DRON_IDLE_VALUE - OFFSET },	//turn left
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

	m_dronBoard.command(DRON_COMMAND_ULTRASONIC, 1, DIRECTION_DATA[dir][0], DIRECTION_DATA[dir][1], DIRECTION_DATA[dir][2]);
}

void Harpybot::onControlDron(int data0, int data1)
{
	switch (data0)
	{
		case 1:
		{
			data1 ? m_dronBoard.active() : m_dronBoard.deactive();
		}
		break;

		case 2:
		{
			GCHECK_RETURN(data1 == 1 || data1 == -1 || data1 == 0);
			m_dronBoard.command(DRON_COMMAND_ULTRASONIC, (char) (DRON_IDLE_VALUE + OFFSET * data1));
		}
		break;

		default:
		{
			bool f = false;
			GCHECK_RETURN(f);
		}
		break;
	}
}
