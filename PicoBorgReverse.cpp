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
#include "PicoBorgReverse.h"

namespace PICO_BORG_REVERSE
{
	const int PICOBORGREVERSE_ID = 0x15;
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

PicoBorgReverse::PicoBorgReverse(int i2cAddress) :
		m_fd(-1), m_i2cAddress(i2cAddress)
{
}

PicoBorgReverse::~PicoBorgReverse()
{
}

bool PicoBorgReverse::open()
{
	m_fd = wiringPiI2CSetup(m_i2cAddress);
	if (m_fd == -1)
	{
		printf("[I2C(%d)]unable to initialize : %s", m_i2cAddress, strerror(errno));
		return false;
	}

//	READDATA readData;
//	readBlock(COMMAND_GET_ID, readData);
//	if (readData.value == -1 || readData.data[1] != PICOBORGREVERSE_ID)
//	{
//		printf("[I2C(%d)]failed get id. id=%d", m_i2cAddress, readData.data[1]);
//		return false;
//	}

	if (wiringPiI2CWriteReg8(m_fd, COMMAND_RESET_EPO, 0) == -1)
	{
		printf("[I2C(%d)]failed reset", m_i2cAddress);
		return false;
	}

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

void PicoBorgReverse::readBlock(int command, READDATA& readData)
{
	const int I2C_SMBUS_BLOCK_MAX = 32;
	const int I2C_SMBUS_READ = 1;
	const int I2C_SMBUS_BLOCK_DATA = 5;
	const int I2C_SMBUS = 0x0720;

	union i2c_smbus_data
	{
		unsigned char byte;
		unsigned short word;
		unsigned char block[I2C_SMBUS_BLOCK_MAX + 2]; // block [0] is used for length + one more for PEC
	};

	struct i2c_smbus_ioctl_data
	{
		char read_write;
		unsigned char command;
		int size;
		union i2c_smbus_data *data;
	};

	i2c_smbus_data data;
	struct i2c_smbus_ioctl_data args;

	args.read_write = I2C_SMBUS_READ;
	args.command = command;
	args.size = I2C_SMBUS_BLOCK_DATA;
	args.data = &data;
	if (ioctl(m_fd, I2C_SMBUS, &args))
		return;

	if (data.block[0] != 4)
		return;

	for (int i = 0; i < 4; ++i)
	{
		readData.data[i] = data.block[i + 1];
	}
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

	if (power > PWM_MAX)
		power = PWM_MAX;

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

	if (power > PWM_MAX)
		power = PWM_MAX;
	wiringPiI2CWriteReg8(m_fd, command, power);
}
