/*
 * main.cpp
 *
 *  Created on: 2015. 2. 12.
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <wiringPi.h>

#include "core/Logger.h"
#include "MainManager.h"

MainManager mainManager;

bool initialize();
void cleanup(int s);

int main(int argc, char* argv[])
{
	Logger::setDev(argc > 3 ? atoi(argv[3]) == 1 : false);

	if (argc < 3)
	{
		GLOG("usage: %s <robot name> <team char> [dev 0 or 1]", argv[0]);
		return -1;
	}

	EROBOT::ETYPE erobot = EROBOT::TOTAL;
	for (int i = 0; i < EROBOT::TOTAL; ++i)
	{
		if (strcasecmp(argv[1], g_robotTypeNames[i]) == 0)
		{
			erobot = (EROBOT::ETYPE)i;
			break;
		}
	}
	if (erobot == EROBOT::TOTAL)
	{
		GLOG("invalid robot name. name=%s team=%s", argv[1], argv[2]);
		return -1;
	}

	if (isalnum(argv[2][0]) == false)
	{
		GLOG("invalid team char. name=%s team=%s", argv[1], argv[2]);
		return -1;
	}

	if (initialize() == false)
	{
		GLOG("failed initialize()");
		cleanup(0);
		return -1;
	}

	mainManager.start(erobot, argv[2][0]);

	cleanup(0);

	return 0;
}

bool initialize()
{
	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);
	signal(SIGQUIT, cleanup);
	signal(SIGHUP, cleanup);

	GCHECK_RETFALSE(wiringPiSetupGpio() != -1);

	GLOG("setup gpio of wiringPi");

	return true;
}

void cleanup(int s)
{
	mainManager.stop();
	GLOG("caught signal %d", s);
	if (s != 0) exit(-1);
}
