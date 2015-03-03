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

Robot::Robot(EROBOT erobot, const char* name, int index)
		: m_erobot(erobot), m_index(index)
{
	strncpy(m_name, name, sizeof(m_name));
}

Robot::~Robot()
{
	// TODO Auto-generated destructor stub
}

void Robot::process(int message, int data0, int data1)
{
	switch (message)
	{
	case MSG_TOGGLE_CAMERA:
		onToggleCamera(data0, data1);
		break;
	case MSG_FIRE:
		onFire(data0, data1);
		break;
	case MSG_MOVE:
		onMove(data0, data1);
		break;
	case MSG_CONTROL_TURRET:
		onControlTurret(data0, data1);
		break;
	default:
		printf("[%s]invalid message %d(%d,%d)\n", m_name, message, data0, data1);
		break;
	}
}

bool Robot::onStart()
{
	printf("start %s\n", m_name);
	return true;
}

void Robot::onStop()
{
	printf("stop %s\n", m_name);
}

void Robot::onReset()
{
	system("killall raspivid");
	system("killall nc");

	printf("reset %s\n", m_name);
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
	printf("[%s]fire %d,%d", m_name, data0, data1);
}

void Robot::onMove(int data0, int data1)
{
	printf("[%s]Move %d,%d", m_name, data0, data1);
}

void Robot::onControlTurret(int data0, int data1)
{
	printf("[%s]control turret %d,%d", m_name, data0, data1);
}
