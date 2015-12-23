/*
 * GatlingGun.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "GatlingGun.h"

namespace GATLING_GUN
{
	const int GPIO_NUM = 7;
}
using namespace GATLING_GUN;

GatlingGun::GatlingGun()
{
	// TODO Auto-generated constructor stub

}

GatlingGun::~GatlingGun()
{
	// TODO Auto-generated destructor stub
}

const char* GatlingGun::getDescription() const
{
	return "gatling gun Controller";
}

bool GatlingGun::open()
{
	pinMode(GPIO_NUM, OUTPUT);

	delay(10);
	on();
	delay(500);
	off();

	init();

	return true;
}

void GatlingGun::close()
{
}

void GatlingGun::init()
{
	off();
}

void GatlingGun::on()
{
	digitalWrite(GPIO_NUM, 1);
}

void GatlingGun::off()
{
	digitalWrite(GPIO_NUM, 0);
}
