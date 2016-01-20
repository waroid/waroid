/*
 * Spiderbot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef SPIDERBOT_H_
#define SPIDERBOT_H_

#include "../module/AduinoBoard.h"
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
	AduinoBoard	m_aduinoBoard;
};

#endif /* SPIDERBOT_H_ */
