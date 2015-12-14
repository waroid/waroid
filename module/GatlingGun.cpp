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

	init();

	on();
	delay(500);
	off();

	return true;
}

void GatlingGun::close()
{
	init();
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
