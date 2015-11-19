/*
 * Scorpio.h
 *
 *  Created on: Nov 19, 2015
 *      Author: mirime
 */

#ifndef SCORPIO_H_
#define SCORPIO_H_

#include "module/PicoBorgReverse.h"
#include "Robot.h"

class Scorpio: public Robot
{
public:
	Scorpio(int index);
	virtual ~Scorpio();

public:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PicoBorgReverse m_picoBorgReverse0;
	PicoBorgReverse m_picoBorgReverse1;
};

#endif /* SCORPIO_H_ */
