/*
 * Thorbot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef THORBOT_H_
#define THORBOT_H_

#include "Robot.h"

class Thorbot: public Robot
{
public:
	Thorbot(char team);
	virtual ~Thorbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
};

#endif /* THORBOT_H_ */
