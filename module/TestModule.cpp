/*
 * TestModule.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "../core/Logger.h"
#include "TestModule.h"

TestModule::TestModule()
		: m_fd(-1)
{
	// TODO Auto-generated constructor stub

}

TestModule::~TestModule()
{
	// TODO Auto-generated destructor stub
}

const char* TestModule::getDescription() const
{
	return "Test Module";
}

bool TestModule::open()
{
	m_fd = serialOpen("/dev/ttyAMA0", 9600);
	GCHECK_RETFALSE(m_fd != -1);

	init();

	return true;
}

void TestModule::close()
{
	if (m_fd != -1)
	{
		serialClose(m_fd);
		m_fd = -1;
	}
}

void TestModule::init()
{
	if (m_fd != -1)
	{
	}
}

void TestModule::move()
{
}

