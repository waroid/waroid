/*
 * Spiderbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Spiderbot.h"

namespace SPIDERBOT
{
}
using namespace SPIDERBOT;

Spiderbot::Spiderbot(char team)
		: Robot(EROBOT::SPIDERBOT, team)
{
	// TODO Auto-generated constructor stub

}

Spiderbot::~Spiderbot()
{
	// TODO Auto-generated destructor stub
}

bool Spiderbot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Spiderbot::onStop()
{
	Robot::onStop();
}

void Spiderbot::onReset()
{
	Robot::onReset();
}
