/*
 * ServoMotor.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: mirime
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include "ServoMotor.h"

namespace SERVO_MOTOR
{
	const int GPIO_NUM = 18;
	const int PWM_CLOCK = 400;
	const int PWM_RANGE = 1024;
}
using namespace SERVO_MOTOR;

ServoMotor::ServoMotor(int offset)
		: m_offset(offset)
{
	// TODO Auto-generated constructor stub

}

ServoMotor::~ServoMotor()
{
	// TODO Auto-generated destructor stub
}

const char* ServoMotor::getDescription() const
{
	return "Common Server Motor Controller";
}

bool ServoMotor::open()
{
	pinMode(GPIO_NUM, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(PWM_CLOCK);
	pwmSetRange(PWM_RANGE);

	init();

	return true;
}

void ServoMotor::close()
{
	init();
}

void ServoMotor::init()
{
	rotate(0);
}

void ServoMotor::rotate(int angle)
{
	if ((angle < 0) || (angle > 180)) return;

	int v = (angle + m_offset + 45) * PWM_RANGE / 1800;
	pwmWrite(GPIO_NUM, v);
}
