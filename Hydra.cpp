/*
 * Hydra.cpp
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#include <wiringPi.h>

#include "Hydra.h"
#include "softServo.h"

namespace HYDRA
{
	const int GPIO_TURRET = 23;
}
using namespace HYDRA;

Hydra::Hydra() :
		Robot("Hydra")
{
	// TODO Auto-generated constructor stub

}

Hydra::~Hydra()
{
	// TODO Auto-generated destructor stub
}

bool Hydra::onStart()
{
	if (Robot::onStart() == false)
		return false;

	if (m_pololuQik.open() == false)
		return false;

	softServoSetup(GPIO_TURRET, -1, -1, -1, -1, -1, -1, -1);
	controlTurret(0);

	return true;
}

void Hydra::onStop()
{
	m_pololuQik.close();
	Robot::onStop();
}

void Hydra::onReset()
{
	m_pololuQik.init();
	controlTurret(0);
}

void Hydra::onMove(int data0, int data1)
{
	m_pololuQik.move(data0 / 100.0f, data1 * 100.0f);
}

void Hydra::onControlTurret(int data0, int data1)
{
	controlTurret(data0);
}

void Hydra::controlTurret(int angle)
{
	if (angle < 0)
		angle = 0;
	else if (angle > 60)
		angle = 60;

	softServoWrite(GPIO_TURRET, (25 * angle) / 3 - 250);
}
