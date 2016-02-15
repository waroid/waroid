/*
 * AduinoBoard.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include <wiringSerial.h>
#include "../core/Logger.h"
#include "AduinoBoard.h"

namespace ADUINO_BOARD
{
	const char PREFIX = 0xff;
	const char POSTFIX = 0xfe;
}
using namespace ADUINO_BOARD;

AduinoBoard::AduinoBoard()
		: m_fd(-1)
{
	// TODO Auto-generated constructor stub

}

AduinoBoard::~AduinoBoard()
{
	// TODO Auto-generated destructor stub
}

const char* AduinoBoard::getDescription() const
{
	return "Aduino board Controller";
}

bool AduinoBoard::open()
{
	m_fd = serialOpen("/dev/ttyAMA0", 115200);
	GCHECK_RETFALSE(m_fd != -1);

	init();

	return true;
}

void AduinoBoard::close()
{
	if (m_fd != -1)
	{
		serialClose(m_fd);
		m_fd = -1;
	}
}

void AduinoBoard::init()
{
	motion(AUDUINO_MOT_BASIC, 0);
}

void AduinoBoard::motion(char command, char option)
{
	serialPutchar(m_fd, PREFIX);
	serialPutchar(m_fd, command);
	serialPutchar(m_fd, option);
	serialPutchar(m_fd, POSTFIX);
}
