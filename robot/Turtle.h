/*
 * Turtle.h
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#ifndef TURTLE_H_
#define TURTLE_H_

#include "../module/PicoBorgReverse.h"
#include "../module/PlasmaCannon.h"
#include "Robot.h"

class Turtle: public Robot
{
public:
	Turtle(int index);
	virtual ~Turtle();

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

#endif /* TURTLE_H_ */