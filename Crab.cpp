/*
 * Crab.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <wiringPi.h>

#include "Crab.h"

namespace CRAB
{
	const int GPIO_FIRE = 24;
}
using namespace CRAB;

Crab::Crab(int index)
		: Robot(ROBOT_CRAB, "Crab", index)
{
	// TODO Auto-generated constructor stub

}

Crab::~Crab()
{
	// TODO Auto-generated destructor stub
}

bool Crab::onStart()
{
	if (Robot::onStart() == false) return false;

	if (m_pololuQik.open() == false) return false;

	pinMode(GPIO_FIRE, OUTPUT);

	return true;
}

void Crab::onStop()
{
	m_pololuQik.close();
	Robot::onStop();
}

void Crab::onReset()
{
	m_pololuQik.init();
	digitalWrite(GPIO_FIRE, 0);
	Robot::onReset();
}

void Crab::onFire(int data0, int data1)
{
	bool onoff = (data0 == 1);
	digitalWrite(GPIO_FIRE, onoff ? 1 : 0);
}

void Crab::onMove(int data0, int data1)
{
	m_pololuQik.move(data0 / 100.0f, data1 / 100.0f);
}
