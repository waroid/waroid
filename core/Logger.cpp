/*
 * Logger.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: mirime
 */

#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

#include "Logger.h"

namespace LOGGER
{
	const int MAX_BUFFER_SIZE = 1024;
	const int MAX_BUFFER_COUNT = 8;
	char buffer[MAX_BUFFER_COUNT][MAX_BUFFER_SIZE];
	int hint = 0;
}
using namespace LOGGER;

bool Logger::s_enableConsole = false;

void Logger::write(const char* format, ...)
{
	int idx = __sync_fetch_and_add(&hint, 1) & MAX_BUFFER_COUNT;
	char* temp = buffer[idx];
	va_list vl;
	va_start(vl, format);
	int len = vsnprintf(temp, MAX_BUFFER_SIZE - 2, format, vl);
	va_end(vl);

	if (len > 0)
	{
		temp[len] = 0;
		syslog(LOG_INFO | LOG_USER, temp);
		if (s_enableConsole)
		{
			printf("%s\n", temp);
		}
	}
}
