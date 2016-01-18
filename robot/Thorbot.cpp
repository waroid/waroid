/*
 * Thorbot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Thorbot.h"

namespace THORBOT
{
}
using namespace THORBOT;

Thorbot::Thorbot(char team)
		: Robot(EROBOT::THORBOT, team)
{
	// TODO Auto-generated constructor stub

}

Thorbot::~Thorbot()
{
	// TODO Auto-generated destructor stub
}

bool Thorbot::onStart()
{
	GCHECK_RETFALSE(Robot::onStart());

	return true;
}

void Thorbot::onStop()
{
	Robot::onStop();
}

void Thorbot::onReset()
{
	Robot::onReset();
}
