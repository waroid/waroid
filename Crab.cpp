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
}
using namespace CRAB;

Crab::Crab(int index)
		: Robot(EROBOT::CRAB, index)
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
	if (m_gatlingGun.open() == false) return false;
	if (m_picoBorgReverse.open() == false) return false;

	return true;
}

void Crab::onStop()
{
	m_picoBorgReverse.close();
	m_gatlingGun.close();
	Robot::onStop();
}

void Crab::onReset()
{
	m_gatlingGun.init();
	m_picoBorgReverse.init();
	Robot::onReset();
}

void Crab::onFire(int data0, int data1)
{
	(data0 == 1) ? m_gatlingGun.on() : m_gatlingGun.off();
}

void Crab::onMove(int data0, int data1)
{
	m_picoBorgReverse.move(data0 / 100.0f, data1 / 100.0f);
}
