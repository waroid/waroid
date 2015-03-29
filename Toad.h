/*
 * Toad.h
 *
 *  Created on: 2015. 2. 16.
 *      Author: mirime
 */

#ifndef TOAD_H_
#define TOAD_H_

#include "module/PicoBorgReverse.h"
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
	virtual void onMove(int data0, int data1);

protected:
	PicoBorgReverse m_picoBorgReverse0;
	PicoBorgReverse m_picoBorgReverse1;
};

#endif /* TOAD_H_ */
