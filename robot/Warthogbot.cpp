/*
 * Warthogbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Warthogbot.h"

namespace WARTHOGBOT
{
}
using namespace WARTHOGBOT;

Warthogbot::Warthogbot(char team)
		: Robot(EROBOT::WARTHOGBOT, team)
{
	// TODO Auto-generated constructor stub

}

Warthogbot::~Warthogbot()
{
	// TODO Auto-generated destructor stub
}

bool Warthogbot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Warthogbot::onStop()
{
	Robot::onStop();
}

void Warthogbot::onReset()
{
	Robot::onReset();
}


