/*
 * Hydra.cpp
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#include <wiringPi.h>
#include "../core/Logger.h"
#include "Hydra.h"

namespace HYDRA
{
	const int TURRET_OFFSET_ANGLE = 5;

	const int MOTOR_COUNT = 2;
	const int DIRECTION_DATA[EDIRECTION::TOTAL][MOTOR_COUNT] =
	{
	//0:motor0, 0:motor1
	{ 0, 0 },	//idle
	{ 1, 1 },	//forward
	{ 0, 0 },	//right forward
	{ 1, -1 },	//right
	{ 0, 0 },	//right backward
	{ -1, -1 },	//backward
	{ 0, 0 },	//left backward
	{ -1, 1 },	//left
	{ 0, 0 },	//left forward
	{ 0, 0 },	//turn right
	{ 0, 0 },	//turn left
	};
}
using namespace HYDRA;

Hydra::Hydra(int index)
		: Robot(EROBOT::HYDRA, index), m_missileTurret(TURRET_OFFSET_ANGLE)
{
	// TODO Auto-generated constructor stub

}

Hydra::~Hydra()
{
	// TODO Auto-generated destructor stub
}

bool Hydra::onStart()
{
	//GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_picoBorgReverse.open());
	GCHECK_RETFALSE(m_missileTurret.open());
	GCHECK_RETFALSE(m_adfruitAudioFxSoundBoard.open());

	m_adfruitAudioFxSoundBoard.play("01BOOT__WAV");

	return true;
}

void Hydra::onStop()
{
	m_adfruitAudioFxSoundBoard.close();
	m_missileTurret.close();
	m_picoBorgReverse.close();
	Robot::onStop();
}

void Hydra::onReset()
{
	m_adfruitAudioFxSoundBoard.init();
	m_picoBorgReverse.init();
	m_missileTurret.init();
	Robot::onReset();
}

void Hydra::onMove(int data0, int data1)
{
	if (data0 >= EDIRECTION::TOTAL || data0 < 0 || data1 >= ROBOT_MAX_SPEED || data1 < 0)
	{
		GLOG("move %d %d", data0, data1);
		m_picoBorgReverse.move(data0 / 100.f, data1 / 100.f);
		return;
	} 

	int dir = data0;
	if (dir < 0) dir = 0;
	else if (dir >= EDIRECTION::TOTAL) dir = 0;

	int speed = data1;
	if (speed < 0) speed = 0;
	else if (speed >= ROBOT_MAX_SPEED) speed = ROBOT_MAX_SPEED - 1;

	m_picoBorgReverse.move(DIRECTION_DATA[dir][0] * g_speedScale[speed], DIRECTION_DATA[dir][1] * g_speedScale[speed]);
}

void Hydra::onControlTurret(int data0, int data1)
{
	controlTurret(data0);
}

void Hydra::controlTurret(int angle)
{
	if (angle < ROBOT_MIN_TURRET_ANGLE) angle = ROBOT_MIN_TURRET_ANGLE;
	else if (angle > ROBOT_MAX_TURRET_ANGLE) angle = ROBOT_MAX_TURRET_ANGLE;

	m_missileTurret.rotate(angle);
}
