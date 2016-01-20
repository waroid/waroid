/*
 * Toadbot.h
 *
 *  Created on: 2015. 2. 16.
 *      Author: mirime
 */

#ifndef TOADBOT_H_
#define TOADBOT_H_

#include "../module/PicoBorgReverse.h"
#include "Robot.h"

class Toadbot: public Robot
{
public:
	Toadbot(char team);
	virtual ~Toadbot();

public:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PicoBorgReverse m_picoBorgReverse0;
	PicoBorgReverse m_picoBorgReverse1;
};

#endif /* TOADBOT_H_ */
