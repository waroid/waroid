/*
 * Harpybot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef HARPYBOT_H_
#define HARPYBOT_H_

#include "Robot.h"

class Harpybot: public Robot
{
public:
	Harpybot(char team);
	virtual ~Harpybot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
};

#endif /* HARPYBOT_H_ */
