/*
 * Thorbot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef THORBOT_H_
#define THORBOT_H_

#include "../module/AduinoBoard.h"
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
	virtual void onMove(int data0, int data1);

protected:
	AduinoBoard m_aduinoBoard;
};

#endif /* THORBOT_H_ */
