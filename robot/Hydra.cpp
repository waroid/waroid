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
	const int TURRET_OFFSET_ANGLE = 0;
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
	GCHECK_RETFALSE(Robot::onStart());
	GCHECK_RETFALSE(m_picoBorgReverse.open());
	GCHECK_RETFALSE(m_missileTurret.open());

	return true;
}

void Hydra::onStop()
{
	m_missileTurret.close();
	m_picoBorgReverse.close();
	Robot::onStop();
}

void Hydra::onReset()
{
	m_picoBorgReverse.init();
	m_missileTurret.init();
	Robot::onReset();
}

void Hydra::onMove(int data0, int data1)
{
	m_picoBorgReverse.move(data0 / 100.0f, data1 / 100.0f);
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
