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
#include "Robot.h"

namespace ROBOT
{

}
using namespace ROBOT;

Robot::Robot(EROBOT::ETYPE erobot, char team)
		: m_erobot(erobot), m_team(toupper(team))
{
	sprintf(m_robotName, "%s_%c", g_robotName[m_erobot], team);
}

Robot::~Robot()
{
	// TODO Auto-generated destructor stub
}

void Robot::process(const ROBOT_DATA& robotData)
{
	switch (robotData.ID)
	{
	case EMESSAGE::TOGGLE_CAMERA:
		onToggleCamera(robotData.Data0, robotData.Data1);
		break;
	case EMESSAGE::FIRE:
		onFire(robotData.Data0, robotData.Data1);
		break;
	case EMESSAGE::MOVE:
		onMove(robotData.Data0, robotData.Data1);
		break;
	case EMESSAGE::CONTROL_TURRET:
		onControlTurret(robotData.Data0, robotData.Data1);
		break;
	default:
		GLOG("[%s]invalid message %d(%d,%d)", g_robotName[m_erobot], robotData.ID, robotData.Data0, robotData.Data1);
		break;
	}
}

bool Robot::onStart()
{
	GLOG("start %s", m_robotName);
	system("aplay /usr/local/share/waroid/boot_sentrymode_active.wav");
	return true;
}

void Robot::onStop()
{
	GLOG("stop %s", m_robotName);
}

void Robot::onReset()
{
	system("killall raspivid");
	system("killall nc");

	GLOG("reset %s", m_robotName);
}

void Robot::onToggleCamera(int data0, int data1)
{
	bool onoff = (data0 == 1);
	if (onoff)
	{
		GLOG("open camera");
		system("raspivid -o - -t 0 -fps 25 -b 2500000 -w 1280 -h 720 | nc -l -p 5001 &");
	}
	else
	{
		GLOG("close camera");
		system("killall raspivid");
		system("killall nc");
	}
}

void Robot::onFire(int data0, int data1)
{
	GLOG("fire %d,%d", data0, data1);
}

void Robot::onMove(int data0, int data1)
{
	GLOG("Move %d,%d", data0, data1);
}

void Robot::onControlTurret(int data0, int data1)
{
	GLOG("control turret %d,%d", data0, data1);
}
