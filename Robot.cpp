/*
 * Robot.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		printf("[%s]invalid message %d(%d,%d)\n", g_robotName[m_erobot], robotData.ID, robotData.Data0, robotData.Data1);
		break;
	}
}

bool Robot::onStart()
{
	printf("start %s\n", g_robotName[m_erobot]);
	return true;
}

void Robot::onStop()
{
	printf("stop %s\n", g_robotName[m_erobot]);
}

void Robot::onReset()
{
	system("killall raspivid");
	system("killall nc");

	printf("reset %s\n", g_robotName[m_erobot]);
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
	printf("[%s]fire %d,%d", g_robotName[m_erobot], data0, data1);
}

void Robot::onMove(int data0, int data1)
{
	printf("[%s]Move %d,%d", g_robotName[m_erobot], data0, data1);
}

void Robot::onControlTurret(int data0, int data1)
{
	printf("[%s]control turret %d,%d", g_robotName[m_erobot], data0, data1);
}
