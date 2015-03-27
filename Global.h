/*
 * Global.h
 *
 *  Created on: Mar 3, 2015
 *      Author: mirime
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "share/defines.h"
#include "share/enums.h"

extern const char* g_robotName[EROBOT::TOTAL];

namespace LOG
{
	extern bool enableConsole;
	extern void line(const char* format, ...);
}



#endif /* GLOBAL_H_ */
