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

	enum ECOMMAND
	{
		MOT_BASIC = 0x00,
		MOT_FORWARD = 0x01,
		MOT_BACKWARD = 0x02,
		MOT_LEFT_SLIDE = 0x03,
		MOT_RIGHT_SLIDE = 0x04,
		MOT_LEFT_TURN = 0x05,
		MOT_RIGHT_TURN = 0x06,
	};

	const ECOMMAND DIRECTION_DATA[EDIRECTION::TOTAL] =
	{ MOT_BASIC,	//idle
	MOT_FORWARD,	//forward
	MOT_BASIC,		//right forward
	MOT_RIGHT_SLIDE,	//right
	MOT_BASIC,			//right backward
	MOT_BACKWARD,		//backward
	MOT_BASIC,			//left backward
	MOT_LEFT_SLIDE,		//left
	MOT_BASIC,			//left forward
	MOT_RIGHT_TURN,		//turn right
	MOT_LEFT_TURN,		//turn left
	};
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
	motion(MOT_BASIC, 0);
}

void AduinoBoard::move(int dir, int speed)
{
	motion(DIRECTION_DATA[dir], (char) speed);
}

void AduinoBoard::motion(char command, char option)
{
	serialPutchar(m_fd, PREFIX);
	serialPutchar(m_fd, command);
	serialPutchar(m_fd, option);
	serialPutchar(m_fd, POSTFIX);
}
