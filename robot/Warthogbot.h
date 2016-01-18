/*
 * Warthogbot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef WARTHOGBOT_H_
#define WARTHOGBOT_H_

#include "Robot.h"

class Warthogbot: public Robot
{
public:
	Warthogbot(char team);
	virtual ~Warthogbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
};

#endif /* WARTHOGBOT_H_ */
