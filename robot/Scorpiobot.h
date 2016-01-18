/*
 * Scorpiobot.h
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#ifndef SCORPIOBOT_H_
#define SCORPIOBOT_H_

#include "../module/PicoBorgReverse.h"
#include "../module/GatlingGun.h"
#include "Robot.h"

class Scorpiobot: public Robot
{
public:
	Scorpiobot(char team);
	virtual ~Scorpiobot();

public:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);

protected:
	GatlingGun m_gatlingGun;
	PicoBorgReverse m_picoBorgReverse0;
	PicoBorgReverse m_picoBorgReverse1;
};

#endif /* SCORPIOBOT_H_ */
