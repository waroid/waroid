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
		: Robot(EROBOT::CRAB, index), m_picoBorgReverse0(10), m_picoBorgReverse1(11)
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
	if (m_relayMotor.open() == false) return false;
	if (m_picoBorgReverse0.open() == false) return false;
	if (m_picoBorgReverse1.open() == false) return false;

	return true;
}

void Crab::onStop()
{
	m_picoBorgReverse0.close();
	m_picoBorgReverse1.close();
	m_relayMotor.close();
	Robot::onStop();
}

void Crab::onReset()
{
	m_relayMotor.init();
	m_picoBorgReverse0.init();
	m_picoBorgReverse1.init();
	Robot::onReset();
}

void Crab::onFire(int data0, int data1)
{
	(data0 == 1) ? m_relayMotor.on() : m_relayMotor.off();
}

void Crab::onMove(int data0, int data1)
{
	m_picoBorgReverse0.move(data0 / 100.0f, data1 / 100.0f);
	m_picoBorgReverse1.move(data0 / 100.0f, data1 / 100.0f);
}
