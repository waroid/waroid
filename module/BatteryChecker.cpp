/*
 * BatteryChecker.cpp
 *
 *  Created on: Dec 15, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <unistd.h>
#include "../core/Logger.h"
#include "BatteryChecker.h"

namespace BATTERY_CHECKER
{
	const int GPIO_SPI_CLK = 8;
	const int GPIO_SPI_MISO = 23;
	const int GPIO_SPI_MOSI = 24;
	const int GPIO_SPI_CS = 25;

	const int MIN_ADC = (6.0 * 1024 / 3.33 / 2.837);
	const int MAX_ADC = (9.0 * 1024 / 3.33 / 2.837);
}
using namespace BATTERY_CHECKER;

BatteryChecker::BatteryChecker()
		: m_volts(0.0f), m_thread(-1)
{
	// TODO Auto-generated constructor stub

}

BatteryChecker::~BatteryChecker()
{
	// TODO Auto-generated destructor stub
}

const char* BatteryChecker::getDescription() const
{
	return "battery check Controller";
}

bool BatteryChecker::open()
{
	pinMode(GPIO_SPI_CLK, OUTPUT);
	pinMode(GPIO_SPI_MISO, INPUT);
	pinMode(GPIO_SPI_MOSI, OUTPUT);
	pinMode(GPIO_SPI_CS, OUTPUT);

	GCHECK_RETFALSE(pthread_create(&m_thread, NULL, worker, this) == 0);

	return true;
}

void BatteryChecker::close()
{
	if (m_thread >= 0)
	{
		if (pthread_cancel(m_thread) == 0)
		{
			pthread_join(m_thread, NULL);
		}
		GLOG("cancel PlasmaCannon thread");
	}
}

void BatteryChecker::init()
{
	m_volts = 0.0f;
}

void BatteryChecker::loop()
{
	for (;;)
	{
		int adcTotal = 0;
		int adcCount = 0;

		for (int i = 0; i < 10; ++i)
		{
			int adcV = readAdc();
			if (adcV > MIN_ADC && adcV < MAX_ADC)
			{
				adcTotal += adcV;
				adcCount++;
			}
			delay(50);
		}

		float adcValue = (adcCount > 0) ? adcTotal / adcCount / 1.0 : 0.0;
		m_volts = adcValue * (3.33 / 1024.0) * 2.837;
		GLOG("adc=%f volt=%f count=%d", adcValue, m_volts, adcCount);

		sleep(30);
	}
}

int BatteryChecker::readAdc()
{
	digitalWrite(GPIO_SPI_CS, 1);
	delay(1);
	digitalWrite(GPIO_SPI_CLK, 0);
	delay(1);
	digitalWrite(GPIO_SPI_CS, 0);
	delay(1);

	int commandOut = (0x6 << 5);

	for (int i = 0; i < 3; ++i)
	{
		digitalWrite(GPIO_SPI_MOSI, (commandOut & 0x80) == 0x80 ? 1 : 0);
		delay(1);
		commandOut <<= 1;
		digitalWrite(GPIO_SPI_CLK, 1);
		delay(1);
		digitalWrite(GPIO_SPI_CLK, 0);
		delay(1);
	}

	int adcOut = 0;
	for (int i = 0; i < 12; ++i)
	{
		digitalWrite(GPIO_SPI_CLK, 1);
		delay(1);
		digitalWrite(GPIO_SPI_CLK, 0);
		delay(1);

		adcOut <<= 1;
		if (digitalRead(GPIO_SPI_MISO)) adcOut |= 0x1;
		delay(1);
	}
	digitalWrite(GPIO_SPI_CS, 1);
	delay(1);

	adcOut /= 2;
	return adcOut;
}

void* BatteryChecker::worker(void* param)
{
	GLOG("start BatteryChecker thread");
	((BatteryChecker*) param)->loop();
	GLOG("stop BatteryChecker thread");

	return NULL;
}
