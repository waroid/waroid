/*
 * BatteryChecker.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "BatteryChecker.h"

namespace BATTERY_CHECKER
{
	const int GPIO_SPI_CLK = 8;
	const int GPIO_SPI_MISO = 23;
	const int GPIO_SPI_MOSI = 24;
	const int GPIO_SPI_CS = 25;
}
using namespace BATTERY_CHECKER;

BatteryChecker::BatteryChecker()
{
	// TODO Auto-generated constructor stub
}

BatteryChecker::~BatteryChecker()
{
	// TODO Auto-generated destructor stub
}

const char* BatteryChecker::getDescription() const
{
	return "Common Battery Checker";
}

bool BatteryChecker::open()
{
	pinMode(GPIO_SPI_CLK, OUTPUT);
	pinMode(GPIO_SPI_MISO, INPUT);
	pinMode(GPIO_SPI_MOSI, OUTPUT);
	pinMode(GPIO_SPI_CS, OUTPUT);

	init();

	return true;
}

void BatteryChecker::close()
{
	init();
}

void BatteryChecker::init()
{

}

float BatteryChecker::volt()
{
	int adcTotal = 0;
	for (int i = 0; i < 10; ++ i)
	{
		adcTotal += read();
		usleep(50000);
	}
	return (static_cast<float>(adcTotal) / 10.0) * (3.33 / 1024.0) * 2.837;
}

int BatteryChecker::read()
{
	digitalWrite(GPIO_SPI_CS, 1);

	digitalWrite(GPIO_SPI_CLK, 0);
	digitalWrite(GPIO_SPI_CS, 0);


	int commandOut = (0x6 << 5);

	for (int i = 0; i < 3; ++ i)
	{
		digitalWrite(GPIO_SPI_MOSI, (commandOut & 0x80)==0x80?1:0);
		commandOut <<= 1;
		digitalWrite(GPIO_SPI_CLK, 1);
		digitalWrite(GPIO_SPI_CLK, 0);
	}

	int adcOut = 0;
	for (int i = 0; i < 12; ++ i)
	{
		digitalWrite(GPIO_SPI_CLK, 0);
		digitalWrite(GPIO_SPI_CLK, 1);

		adcOut <<= 1;
		if (digitalRead(GPIO_SPI_MISO) != 0)
		{
			adcOut |= 0x1;
		}
	}

	digitalWrite(GPIO_SPI_CS, 1);

	return (adcOut / 2);
}
