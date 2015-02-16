/*
 * PololuQik.cpp
 *
 *  Created on: 2015. 2. 12.
 *      Author: mirime
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "PololuQik.h"

namespace POLOLU_QIK
{
	const int PWM_MAX = 127;

	enum ECOMMAND
	{
		COMMAND_SET_MOTOR_0_FORWARD = 0x8C,
		COMMAND_SET_MOTOR_0_BACKWARD = 0x8E,
		COMMAND_SET_MOTOR_1_FORWARD = 0x88,
		COMMAND_SET_MOTOR_1_BACKWARD = 0x8A,
	};

}
using namespace POLOLU_QIK;

PololuQik::PololuQik() :
		m_fd(-1)
{
}

PololuQik::~PololuQik()
{
}

const char* PololuQik::getDescription() const
{
	return "Pololu Qik 2s9v1 Dual Serial Motor Controller";
}

bool PololuQik::open()
{
	m_fd = serialOpen("/dev/ttyAMA0", 38400);
	if (m_fd == -1)
	{
		printf("Problem opening serial port: %d\n", errno);
		return false;
	}

	// set timeout to 262ms
	serialPutchar(m_fd, 0x84);
	serialPutchar(m_fd, 0x03);
	serialPutchar(m_fd, 0x01);
	serialPutchar(m_fd, 0x55);
	serialPutchar(m_fd, 0x2a);

	init();

	return true;
}

void PololuQik::close()
{
	init();
	if (m_fd != -1)
	{
		serialClose(m_fd);
		m_fd = -1;
	}
}

void PololuQik::init()
{
	if (m_fd != -1)
	{
		serialPutchar(m_fd, COMMAND_SET_MOTOR_0_FORWARD);
		serialPutchar(m_fd, 0);

		serialPutchar(m_fd, COMMAND_SET_MOTOR_1_FORWARD);
		serialPutchar(m_fd, 0);
	}
}

void PololuQik::move(float power0, float power1)
{
	setMotor0(power0 * PWM_MAX);
	setMotor1(power1 * PWM_MAX);
}

void PololuQik::setMotor0(int power)
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

	if (power > PWM_MAX)
		power = PWM_MAX;

	serialPutchar(m_fd, command);
	serialPutchar(m_fd, power);
}

void PololuQik::setMotor1(int power)
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

	if (power > PWM_MAX)
		power = PWM_MAX;

	serialPutchar(m_fd, command);
	serialPutchar(m_fd, power);
}

