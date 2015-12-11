/*
 * Toad.h
 *
 *  Created on: 2015. 2. 16.
 *      Author: mirime
 */

#ifndef TOAD_H_
#define TOAD_H_

#include "module/PicoBorgReverse.h"
#include "module/PlasmaCannon.h"
#include "Robot.h"

class Toad: public Robot
{
public:
	Toad(int index);
	virtual ~Toad();

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

#endif /* TOAD_H_ */
