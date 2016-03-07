/*
 * DronBoard.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include <wiringSerial.h>
#include "../core/Logger.h"
#include "DronBoard.h"

namespace DRON_BOARD
{
	const char HEADER = 0x00;
}
using namespace DRON_BOARD;

DronBoard::DronBoard()
		: m_fd(-1)
{
	// TODO Auto-generated constructor stub

}

DronBoard::~DronBoard()
{
	// TODO Auto-generated destructor stub
}

const char* DronBoard::getDescription() const
{
	return "Dron board Controller";
}

bool DronBoard::open()
{
	m_fd = serialOpen("/dev/ttyAMA0", 115200);
	GCHECK_RETFALSE(m_fd != -1);

	init();

	return true;
}

void DronBoard::close()
{
	command(DRON_COMMAND_STOP);
	if (m_fd != -1)
	{
		serialClose(m_fd);
		m_fd = -1;
	}
}

void DronBoard::init()
{
	command(DRON_COMMAND_START);
	command(DRON_COMMAND_CONTROL, 1);
}

void DronBoard::command(char cmd, char throttle, char roll, char pitch, char yaw)
{
	serialPutchar(m_fd, HEADER);
	serialPutchar(m_fd, cmd);
	serialPutchar(m_fd, throttle);
	serialPutchar(m_fd, roll);
	serialPutchar(m_fd, pitch);
	serialPutchar(m_fd, yaw);
}
