/*
 * Cannon.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "../core/Logger.h"
#include "Cannon.h"

namespace CANNON
{
	const int GPIO_NUM = 7;
}
using namespace CANNON;

Cannon::Cannon(EWEAPON::ETYPE eweapon, bool real)
		: Weapon(eweapon, real)
{
	// TODO Auto-generated constructor stub
}

Cannon::~Cannon()
{
	// TODO Auto-generated destructor stub
}

bool Cannon::onOpen()
{
	if (isReal())
	{
		pinMode(GPIO_NUM, OUTPUT);
		delay(10);
		for (int i = 0; i < 3; ++i)
		{
			digitalWrite(GPIO_NUM, 1);
			delay(50);
			digitalWrite(GPIO_NUM, 0);
			delay(500);
		}
	}

	return true;
}

void Cannon::onClose()
{
	if (isReal()) digitalWrite(GPIO_NUM, 0);
}

void Cannon::onInit()
{
	if (isReal()) digitalWrite(GPIO_NUM, 0);
}

void Cannon::onFireStart()
{
	if (isReal())
	{
		digitalWrite(GPIO_NUM, 1);
		delay(50);
		digitalWrite(GPIO_NUM, 0);
	}
}

void Cannon::onFireEnd()
{
}

