/*
 * ArduinoBoard.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include <wiringSerial.h>
#include "../core/Logger.h"
#include "ArduinoBoard.h"

namespace ARDUINO_BOARD
{
	const char PREFIX = 0xff;
	const char POSTFIX = 0xfe;
}
using namespace ARDUINO_BOARD;

ArduinoBoard::ArduinoBoard()
		: m_fd(-1)
{
	// TODO Auto-generated constructor stub

}

ArduinoBoard::~ArduinoBoard()
{
	// TODO Auto-generated destructor stub
}

const char* ArduinoBoard::getDescription() const
{
	return "Aduino board Controller";
}

bool ArduinoBoard::open()
{
	m_fd = serialOpen("/dev/ttyAMA0", 115200);
	GCHECK_RETFALSE(m_fd != -1);

	init();

	return true;
}

void ArduinoBoard::close()
{
	if (m_fd != -1)
	{
		serialClose(m_fd);
		m_fd = -1;
	}
}

void ArduinoBoard::init()
{
	motion(ARDUINO_MOT_BASIC, 0);
}

void ArduinoBoard::motion(char command, char option)
{
	serialPutchar(m_fd, PREFIX);
	serialPutchar(m_fd, command);
	serialPutchar(m_fd, option);
	serialPutchar(m_fd, POSTFIX);
}
