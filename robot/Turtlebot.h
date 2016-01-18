/*
 * Turtlebot.h
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#ifndef TURTLEBOT_H_
#define TURTLEBOT_H_

#include "../module/PicoBorgReverse.h"
#include "../module/PlasmaCannon.h"
#include "Robot.h"

class Turtlebot: public Robot
{
public:
	Turtlebot(char team);
	virtual ~Turtlebot();

public:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);

protected:
	PlasmaCannon m_plasmaCannon;
	PicoBorgReverse m_picoBorgReverse0;
	PicoBorgReverse m_picoBorgReverse1;
};

#endif /* TURTLEBOT_H_ */
