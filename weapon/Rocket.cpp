/*
 * Rocket.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Rocket.h"

namespace ROCKET
{
	const int GPIO_NUM = 18;
	const int PWM_CLOCK = 400;
	const int PWM_RANGE = 1024;
}
using namespace ROCKET;

Rocket::Rocket(EWEAPON::ETYPE eweapon, bool real, int offset)
		: Weapon(eweapon, real), m_offset(offset)
{
	// TODO Auto-generated constructor stub

}

Rocket::~Rocket()
{
	// TODO Auto-generated destructor stub
}

void Rocket::tilt(int angle)
{
	if ((angle < ROBOT_MIN_TURRET_ANGLE) || (angle > ROBOT_MAX_TURRET_ANGLE))
	    return;

	if (isReal())
	{
		int v = (angle + m_offset + 45) * PWM_RANGE / 1800;
		pwmWrite(GPIO_NUM, v);
	}
}

bool Rocket::onOpen()
{
	if (isReal())
	{
		pinMode(GPIO_NUM, PWM_OUTPUT);
		pwmSetMode(PWM_MODE_MS);
		pwmSetClock(PWM_CLOCK);
		pwmSetRange(PWM_RANGE);
	}

	return true;
}

void Rocket::onClose()
{

}

void Rocket::onInit()
{
	tilt(0);
}

void Rocket::onFireStart()
{
}

void Rocket::onFireEnd()
{
}
