/*
 * Robot.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <stdlib.h>
#include "core/Logger.h"
#include "Robot.h"

namespace ROBOT
{

}
using namespace ROBOT;

Robot::Robot(EROBOT::ETYPE erobot, int index)
		: m_erobot(erobot), m_index(index)
{
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
	GLOG("start %s", g_robotName[m_erobot]);
	return true;
}

void Robot::onStop()
{
	GLOG("stop %s", g_robotName[m_erobot]);
}

void Robot::onReset()
{
	system("killall raspivid");
	system("killall nc");

	GLOG("reset %s", g_robotName[m_erobot]);
}

void Robot::onToggleCamera(int data0, int data1)
{
	bool onoff = (data0 == 1);
	if (onoff)
	{
		system("raspivid -o - -rot 90 -t 0 -fps 20 -b 2500000 -h 1280 -w 720 | nc -l -p 5001 &");
	}
	else
	{
		system("killall raspivid");
		system("killall nc");
	}
}

void Robot::onFire(int data0, int data1)
{
	GLOG("[%s]fire %d,%d", g_robotName[m_erobot], data0, data1);
}

void Robot::onMove(int data0, int data1)
{
	GLOG("[%s]Move %d,%d", g_robotName[m_erobot], data0, data1);
}

void Robot::onControlTurret(int data0, int data1)
{
	GLOG("[%s]control turret %d,%d", g_robotName[m_erobot], data0, data1);
}
