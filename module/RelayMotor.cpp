/*
 * RelayMotor.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "RelayMotor.h"

namespace RELAY_MOTOR
{
	const int GPIO_NUM = 7;
}
using namespace RELAY_MOTOR;

RelayMotor::RelayMotor()
{
	// TODO Auto-generated constructor stub

}

RelayMotor::~RelayMotor()
{
	// TODO Auto-generated destructor stub
}

const char* RelayMotor::getDescription() const
{
	return "Common Relay Motor Controller";
}

bool RelayMotor::open()
{
	pinMode(GPIO_NUM, OUTPUT);

	init();

	on();
	sleep(1);
	off();

	return true;
}

void RelayMotor::close()
{
	init();
}

void RelayMotor::init()
{
	off();
}

void RelayMotor::on()
{
	digitalWrite(GPIO_NUM, 1);
}

void RelayMotor::off()
{
	digitalWrite(GPIO_NUM, 0);
}
