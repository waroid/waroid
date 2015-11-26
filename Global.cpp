/*
 * Global.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syslog.h>

#include "Global.h"

const char* g_robotName[EROBOT::TOTAL] =
{ "Unknown", "Crab", "Hydra", "Turtle", "Toad", "Scorpio" };

const float g_speedScale[ROBOT_MAX_SPEED] =
{ 0.0, 0.4, 0.6, 0.8, 1.0 };
