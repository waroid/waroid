/*
 * main.cpp
 *
 *  Created on: 2015. 2. 12.
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>

#include "core/Logger.h"
#include "MainManager.h"

MainManager mainManager;

bool initialize();
void cleanup(int s);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("usage: %s <robot index> [console log on or off]", argv[0]);
		return -1;
	}

	int robotIndex = atoi(argv[1]);
	if (argc > 2)
	{
		Logger::setConsole(atoi(argv[2]) == 1);
	}

	if (initialize() == false)
	{
		GLOG("failed initialize()");
		cleanup(0);
		return -1;
	}

	mainManager.start(robotIndex);

	cleanup(0);

	return 0;
}

bool initialize()
{
	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);
	signal(SIGQUIT, cleanup);
	signal(SIGHUP, cleanup);

	GCHECK_RETFALSE(wiringPiSetupGpio()!=-1);

	GLOG("setup gpio of wiringPi");

	return true;
}

void cleanup(int s)
{
	mainManager.stop();
	GLOG("caught signal %d", s);
	if (s != 0) exit(-1);
}
