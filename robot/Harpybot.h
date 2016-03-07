/*
 * Harpybot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef HARPYBOT_H_
#define HARPYBOT_H_

#include "../module/ArduinoBoard.h"
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
	virtual void onMove(int data0, int data1);

protected:
	ArduinoBoard m_arduinoBoard;
};

#endif /* HARPYBOT_H_ */
