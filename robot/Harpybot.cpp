/*
 * Harpybot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Harpybot.h"

namespace HARPYBOT
{
}
using namespace HARPYBOT;

Harpybot::Harpybot(char team)
		: Robot(EROBOT::HARPYBOT, team)
{
	// TODO Auto-generated constructor stub

}

Harpybot::~Harpybot()
{
	// TODO Auto-generated destructor stub
}

bool Harpybot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Harpybot::onStop()
{
	Robot::onStop();
}

void Harpybot::onReset()
{
	Robot::onReset();
}
