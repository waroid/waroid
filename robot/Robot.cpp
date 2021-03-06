/*
 * Robot.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "../core/Logger.h"
#include "../weapon/Gatling.h"
#include "../weapon/Cannon.h"
#include "../weapon/Rocket.h"
#include "Robot.h"

namespace ROBOT
{
	const char* TTS_WAV = "/tmp/say.wav";
}
using namespace ROBOT;

Robot::Robot(EROBOT::ETYPE erobot, char team)
		: m_erobot(erobot), m_team(toupper(team))
{
	sprintf(m_name, "%s_%c", g_robotTypeNames[m_erobot], team);

	char temp[256];
	sprintf(temp, "pico2wave --wave %s \"i'm a %s. ready!\"", TTS_WAV, g_robotTypeNames[m_erobot]);
	system(temp);

	for (int i = 0; i < ROBOT_MAX_WEAPON_SLOT; ++i)
	{
		m_weapons[i] = NULL;
	}
}

Robot::~Robot()
{
	// TODO Auto-generated destructor stub
}

bool Robot::start()
{
	char temp[256];
	sprintf(temp, "%s/startup.wav", g_soundDir);
	GCHECK_RETFALSE(m_startupWav.load(temp));
	GCHECK_RETFALSE(m_ttsWav.load(TTS_WAV));

	GCHECK_RETFALSE(onStart());
	GLOG("[%s]started", getName());

	onReset();
	GLOG("[%s]reset", getName());

	m_startupWav.play();
	usleep(500000);
	m_ttsWav.play();

	return true;
}

void Robot::stop()
{
	m_startupWav.close();
	m_ttsWav.close();

	onStop();
	GLOG("[%s]stopped", getName());
}

void Robot::reset()
{
	m_startupWav.stop();
	m_ttsWav.stop();

	onReset();
	GLOG("[%s]reset", getName());
}

void Robot::process(const ROBOT_DATA& robotData)
{
	switch (robotData.ID)
	{
		case EMESSAGE::TOGGLE_CAMERA:
		{
			GDEV("[%s]toggle camera. Data0=%d Data1=%d", getName(), robotData.Data0, robotData.Data1);
			onToggleCamera(robotData.Data0, robotData.Data1);
		}
		break;

		case EMESSAGE::FIRE:
		{
			GDEV("[%s]fire. Data0=%d Data1=%d", getName(), robotData.Data0, robotData.Data1);
			onFire(robotData.Data0, robotData.Data1);
		}
		break;

		case EMESSAGE::MOVE:
		{
			GDEV("[%s]move. Data0=%d Data1=%d", getName(), robotData.Data0, robotData.Data1);
			onMove(robotData.Data0, robotData.Data1);
		}
		break;

		case EMESSAGE::CONTROL_TURRET:
		{
			GDEV("[%s]control turret. Data0=%d Data1=%d", getName(), robotData.Data0, robotData.Data1);
			onControlTurret(robotData.Data0, robotData.Data1);
		}
		break;

		case EMESSAGE::EQUIP_WEAPON:
		{
			GDEV("[%s]equip weapon. Data0=%d Data1=%d", getName(), robotData.Data0, robotData.Data1);
			onEquipWeapon(robotData.Data0, robotData.Data1);
		}
		break;

		case EMESSAGE::CONTROL_DRON:
		{
			GDEV("[%s]control dron. Data0=%d Data1=%d", getName(), robotData.Data0, robotData.Data1);
			onControlDron(robotData.Data0, robotData.Data1);
		}
		break;

		default:
		{
			GLOG("[%s]invalid message. ID=%d Data0=%d Data1=%d", getName(), robotData.ID, robotData.Data0, robotData.Data1);
		}
		break;
	}
}

Weapon* Robot::createWeapon(EWEAPON::ETYPE eweapon, bool real)
{
	Weapon* weapon = NULL;
	switch (g_weaponDatas[eweapon].weaponKind)
	{
		case EWEAPONKIND::GATLING:
			weapon = new Gatling(eweapon, real);
		break;

		case EWEAPONKIND::CANNON:
			weapon = new Cannon(eweapon, real);
		break;

		case EWEAPONKIND::ROCKET:
			weapon = new Rocket(eweapon, real);
		break;

		default:
		break;
	}
	GCHECKV_RETNULL(weapon, "[%s]invalid weapon. weapon=%d", eweapon);

	return weapon;
}

bool Robot::onStart()
{
	return true;
}

void Robot::onStop()
{
	for (int i = 0; i < ROBOT_MAX_WEAPON_SLOT; ++i)
	{
		if (m_weapons[i] != NULL)
		{
			delete m_weapons[i];
			m_weapons[i] = NULL;
		}
	}
}

void Robot::onReset()
{
	system("killall raspivid");
	system("killall nc");

	if (m_weapons[0])
	{
		m_weapons[0]->init();
	}

	for (int i = 1; i < ROBOT_MAX_WEAPON_SLOT; ++i)
	{
		if (m_weapons[i])
		{
			m_weapons[i]->close();
			delete m_weapons[i];
			m_weapons[i] = NULL;
		}
	}
}

void Robot::onToggleCamera(int data0, int data1)
{
	bool onoff = (data0 == 1);
	if (onoff)
	{
		GLOG("[%s]open camera", getName());
		system("raspivid -o - -t 0 -fps 25 -b 2500000 -w 1280 -h 720 | nc -l -p 5001 &");
	}
	else
	{
		GLOG("[%s]close camera", getName());
		system("killall raspivid");
		system("killall nc");
	}
}

void Robot::onFire(int data0, int data1)
{
	GCHECK_RETURN(data1 >= 0 && data1 < ROBOT_MAX_WEAPON_SLOT);
	GCHECK_RETURN(m_weapons[data1]);
	m_weapons[data1]->fire(data0 == 1);
}

void Robot::onMove(int data0, int data1)
{
}

void Robot::onControlTurret(int data0, int data1)
{
}

void Robot::onEquipWeapon(int data0, int data1)
{
	GCHECK_RETURN(data0 >= 0 && data0 < EWEAPON::TOTAL);

	//secondary weapon
	if (m_weapons[1])
	{
		delete m_weapons[1];
		m_weapons[1] = NULL;
	}
	m_weapons[1] = createWeapon((EWEAPON::ETYPE) data0, false);
	GCHECK_RETURN(m_weapons[1]);
	GCHECK_RETURN(m_weapons[1]->open());

	GLOG("[%s]equiped weapon. name=%s", getName(), m_weapons[1]->getName());
}

void Robot::onControlDron(int data0, int data1)
{
}
