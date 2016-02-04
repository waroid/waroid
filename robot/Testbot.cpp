/*
 * Testbot.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	srand(time(NULL));
}

Testbot::~Testbot()
{
	// TODO Auto-generated destructor stub
}

bool Testbot::onStart()
{
	char temp[256];
	sprintf(temp, "%s/test.wav", g_soundDir);
	GCHECK_RETFALSE(m_testWav.load(temp));

	GCHECK_RETFALSE(m_testModule.open());

	//EWEAPON::ETYPE randomWeapon = EWEAPON::M134D_MINIGUN;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::STARSTREAK_AVENGER;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::GAU_19_B_HMG;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::_2A72_AUTOCANNON;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::XM214_MICROGUN;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::M242_CHAINGUN;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::BOFORS_L60;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::M61_VULCAN;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::PLASMA_GUN;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::ENERGY_CANNON;
	//EWEAPON::ETYPE randomWeapon = EWEAPON::LASER_CANNON;
	EWEAPON::ETYPE randomWeapon = (EWEAPON::ETYPE) ((rand() % (EWEAPON::TOTAL - 1)) + 1);
	m_weapons[0] = createWeapon(randomWeapon, false);
	GCHECK_RETFALSE(m_weapons[0]);
	GCHECK_RETFALSE(m_weapons[0]->open());

	GCHECK_RETFALSE(Robot::onStart());

	sleep(1);
	m_testWav.play();

	return true;
}

void Testbot::onStop()
{
	m_testWav.close();
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
	Robot::onToggleCamera(data0, data1);
	GDEV("[%s]camera is %s", getName(), (data0 == 1) ? "on" : "off");
}

void Testbot::onFire(int data0, int data1)
{
	Robot::onFire(data0, data1);
	GDEV("[%s]fire switch of %d slot weapon is %s", getName(), data1,
	        (data0 == 1) ? "on" : "off");
	//if (data0 == 1) m_testWav.play();
	//else m_testWav.stop();

}

void Testbot::onMove(int data0, int data1)
{
	Robot::onMove(data0, data1);
	GDEV("[%s]move to %d. speed is %d", getName(), data0, data1);
}

void Testbot::onControlTurret(int data0, int data1)
{
	Robot::onControlTurret(data0, data1);
	GDEV("[%s]turret angle is %d", getName(), data0);
}

void Testbot::onEquipWeapon(int data0, int data1)
{
	Robot::onEquipWeapon(data0, data1);
	GLOG("[%s]%d weapon is equip ", getName(), data0);
}
