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
	if (argc != 2)
	{
		printf("invalid arg count. argc=%d\n", argc);
		return -1;
	}

	int robotIndex = atoi(argv[1]);

	if (initialize() == false)
	{
		printf("failed initialize()\n");
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
		printf("Problem setup gpio: %d\n", errno);
		return false;
	}
	printf("setup gpio of wiringPi\n");

	return true;
}

void cleanup(int s)
{
	mainManager.stop();
	printf("caught signal %d\n", s);
	if (s != 0) exit(-1);
}
