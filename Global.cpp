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
{ "Unknown", "Crab", "Hydra", "Turtle", "Toad" };

namespace LOG
{
	bool enableConsole;
	void line(const char* format, ...)
	{
		char buffer[512] =
		{ 0 };
		va_list vl;
		va_start(vl, format);
		int len = vsnprintf(buffer, sizeof(buffer) - 2, format, vl);
		va_end(vl);
		if (len > 0)
		{
			buffer[len] = '\n';
			buffer[len + 1] = 0;
			syslog(LOG_INFO | LOG_USER, buffer);
			if (enableConsole)
			{
				printf(buffer);
			}
		}
	}
}
