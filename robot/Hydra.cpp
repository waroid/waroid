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
	const int TURRET_OFFSET_ANGLE = 14;
	const int TURRET_MAX_ANGLE = 30;
}
using namespace HYDRA;

Hydra::Hydra(int index)
		: Robot(EROBOT::HYDRA, index), m_servoMotor(TURRET_OFFSET_ANGLE)
{
	// TODO Auto-generated constructor stub

}

Hydra::~Hydra()
{
	// TODO Auto-generated destructor stub
}

bool Hydra::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_pololuQik.open());
	GCHECK_RETFALSE(m_servoMotor.open());

	return true;
}

void Hydra::onStop()
{
	m_servoMotor.close();
	m_pololuQik.close();
	Robot::onStop();
}

void Hydra::onReset()
{
	m_pololuQik.init();
	m_servoMotor.init();
	Robot::onReset();
}

void Hydra::onMove(int data0, int data1)
{
	m_pololuQik.move(data0 / 100.0f, data1 / 100.0f);
}

void Hydra::onControlTurret(int data0, int data1)
{
	controlTurret(data0);
}

void Hydra::controlTurret(int angle)
{
	if (angle < 0) angle = 0;
	else if (angle > TURRET_MAX_ANGLE) angle = TURRET_MAX_ANGLE;

	m_servoMotor.rotate(angle);
}
