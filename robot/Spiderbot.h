/*
 * Spiderbot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef SPIDERBOT_H_
#define SPIDERBOT_H_

#include "../module/ArduinoBoard.h"
#include "Robot.h"

class Spiderbot: public Robot
{
public:
	Spiderbot(char team);
	virtual ~Spiderbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	ArduinoBoard	m_arduinoBoard;
};

#endif /* SPIDERBOT_H_ */
