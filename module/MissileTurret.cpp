/*
 * MissileTurret.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include "MissileTurret.h"

namespace MISSILE_TURRET
{
	const int GPIO_NUM = 18;
	const int PWM_CLOCK = 400;
	const int PWM_RANGE = 1024;
}
using namespace MISSILE_TURRET;

MissileTurret::MissileTurret(int offset)
		: m_offset(offset)
{
	// TODO Auto-generated constructor stub

}

MissileTurret::~MissileTurret()
{
	// TODO Auto-generated destructor stub
}

const char* MissileTurret::getDescription() const
{
	return "Missile turret Controller";
}

bool MissileTurret::open()
{
	pinMode(GPIO_NUM, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(PWM_CLOCK);
	pwmSetRange(PWM_RANGE);

	init();

	return true;
}

void MissileTurret::close()
{
	init();
}

void MissileTurret::init()
{
	rotate(0);
}

void MissileTurret::rotate(int angle)
{
	if ((angle < 0) || (angle > 180)) return;

	int v = (angle + m_offset + 45) * PWM_RANGE / 1800;
	pwmWrite(GPIO_NUM, v);
}
