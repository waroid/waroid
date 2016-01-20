/*
 * Crabbot.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef CRABBOT_H_
#define CRABBOT_H_

#include "../module/PicoBorgReverse.h"
#include "Robot.h"

class Crabbot: public Robot
{
public:
	Crabbot(char team);
	virtual ~Crabbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PicoBorgReverse m_picoBorgReverse;
};

#endif /* CRABBOT_H_ */
