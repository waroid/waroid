/*
 * main.cpp
 *
 *  Created on: 2015. 2. 12.
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <wiringPi.h>

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
		LOG::enableConsole = atoi(argv[2]) == 1;
	}

	if (initialize() == false)
	{
		LOG::line("failed initialize()");
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

	if (wiringPiSetupGpio() == -1)
	{
		LOG::line("Problem setup gpio: %d", errno);
		return false;
	}
	LOG::line("setup gpio of wiringPi");

	return true;
}

void cleanup(int s)
{
	mainManager.stop();
	LOG::line("caught signal %d", s);
	if (s != 0) exit(-1);
}
