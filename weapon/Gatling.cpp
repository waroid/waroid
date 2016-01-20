/*
 * GatlingGun.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "Gatling.h"

namespace GATLING
{
	const int GPIO_NUM = 7;
}
using namespace GATLING;

Gatling::Gatling(EWEAPON::ETYPE eweapon, bool real)
		: Weapon(eweapon, real)
{
	// TODO Auto-generated constructor stub
}

Gatling::~Gatling()
{
	// TODO Auto-generated destructor stub
}

bool Gatling::onOpen()
{
	if (isReal())
	{
		pinMode(GPIO_NUM, OUTPUT);
		delay(10);
		digitalWrite(GPIO_NUM, 1);
		delay(500);
		digitalWrite(GPIO_NUM, 0);
	}

	return true;
}

void Gatling::onClose()
{
	if (isReal()) digitalWrite(GPIO_NUM, 0);
}

void Gatling::onInit()
{
	if (isReal()) digitalWrite(GPIO_NUM, 0);
}

void Gatling::onFireStart()
{
	if (isReal()) digitalWrite(GPIO_NUM, 1);
}

void Gatling::onFireEnd()
{
	if (isReal()) digitalWrite(GPIO_NUM, 0);
}

