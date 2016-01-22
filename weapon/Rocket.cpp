/*
 * Rocket.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include <softPwm.h>
#include "../core/Logger.h"
#include "Rocket.h"

namespace ROCKET
{
	const int GPIO_NUM = 18;
	const int PWM_RANGE = 200;
	const int PWM_MIN = 5;
	const int PWM_NEUTRAL = 15;
	const int PWM_MAX = 25;
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
		int pwm = (PWM_MAX - PWM_MIN) * (angle + m_offset) / 180 + PWM_NEUTRAL;
		softPwmWrite(GPIO_NUM, pwm);
	}
}

bool Rocket::onOpen()
{
	if (isReal())
	{
		pinMode(GPIO_NUM, OUTPUT);
		digitalWrite(GPIO_NUM, 0);
		softPwmCreate(GPIO_NUM, PWM_NEUTRAL, PWM_RANGE);
	}

	return true;
}

void Rocket::onClose()
{
	if (isReal()) softPwmStop(GPIO_NUM);
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
