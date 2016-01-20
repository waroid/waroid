/*
 * Testbot.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Testbot.h"

namespace TESTBOT
{
}
using namespace TESTBOT;

Testbot::Testbot(char team)
		: Robot(EROBOT::TESTBOT, team)
{
	// TODO Auto-generated constructor stub

}

Testbot::~Testbot()
{
	// TODO Auto-generated destructor stub
}

bool Testbot::onStart()
{
	GCHECK_RETFALSE(m_testModule.open());
	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Testbot::onStop()
{
	m_testModule.close();
	Robot::onStop();
}

void Testbot::onReset()
{
	m_testModule.init();
	Robot::onReset();
}

void Testbot::onToggleCamera(int data0, int data1)
{
	GDEV("[%s]camera is %s", getName(), (data0==1)?"on":"off");
}

void Testbot::onFire(int data0, int data1)
{
	GDEV("[%s]fire switch of %d slot weapon is %s", getName(), data1, (data0==1)?"on":"off");
}

void Testbot::onMove(int data0, int data1)
{
	GDEV("[%s]move to %d. speed is %d", getName(), data0, data1);
}

void Testbot::onControlTurret(int data0, int data1)
{
	GDEV("[%s]turret angle is %d", getName(), data0);
}

void Testbot::onEquipWeapon(int data0, int data1)
{
	GLOG("[%s]%d weapon is equip ", getName(), data0);
}
