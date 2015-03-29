/*
 * PicoBorgReverse.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../core/Logger.h"
#include "PicoBorgReverse.h"

namespace PICO_BORG_REVERSE
{
	const int PWM_MAX = 255;

	enum ECOMMAND
	{
		COMMAND_SET_MOTOR_1_FORWARD = 3,
		COMMAND_SET_MOTOR_1_BACKWARD = 4,
		COMMAND_SET_MOTOR_0_FORWARD = 6,
		COMMAND_SET_MOTOR_0_BACKWARD = 7,
		COMMAND_ALL_OFF = 9,
		COMMAND_RESET_EPO = 10,

		COMMAND_GET_ID = 0x99,
	};

}
using namespace PICO_BORG_REVERSE;

PicoBorgReverse::PicoBorgReverse(int i2cAddress)
		: m_fd(-1), m_i2cAddress(i2cAddress)
{
}

PicoBorgReverse::~PicoBorgReverse()
{
}

const char* PicoBorgReverse::getDescription() const
{
	return "PicoBorg Reverse - Advanced motor control for your Raspberry Pi";
}

bool PicoBorgReverse::open()
{
	m_fd = wiringPiI2CSetup(m_i2cAddress);
	GCHECKV_RETFALSE(m_fd!=-1, "I2C address=%d", m_i2cAddress);

	GCHECKV_RETFALSE(wiringPiI2CWriteReg8(m_fd, COMMAND_RESET_EPO, 0)!=-1, "I2C address=%d", m_i2cAddress);

	init();

	return true;
}

void PicoBorgReverse::close()
{
	init();
	m_fd = -1;
}

void PicoBorgReverse::init()
{
	if (m_fd != -1)
	{
		wiringPiI2CWriteReg8(m_fd, COMMAND_ALL_OFF, 0);
	}
}

void PicoBorgReverse::move(float power0, float power1)
{
	setMotor0(power0 * PWM_MAX);
	setMotor1(power1 * PWM_MAX);
}

void PicoBorgReverse::setMotor0(int power)
{
	int command = 0;
	if (power < 0)
	{
		command = COMMAND_SET_MOTOR_0_BACKWARD;
		power *= (-1);
	}
	else
	{
		command = COMMAND_SET_MOTOR_0_FORWARD;
	}

	if (power > PWM_MAX) power = PWM_MAX;

	wiringPiI2CWriteReg8(m_fd, command, power);
}

void PicoBorgReverse::setMotor1(int power)
{
	int command = 0;
	if (power < 0)
	{
		command = COMMAND_SET_MOTOR_1_BACKWARD;
		power *= (-1);
	}
	else
	{
		command = COMMAND_SET_MOTOR_1_FORWARD;
	}

	if (power > PWM_MAX) power = PWM_MAX;
	wiringPiI2CWriteReg8(m_fd, command, power);
}
