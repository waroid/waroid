/*
 * Taurus.h
 *
 *  Created on: Jan 4, 2016
 *      Author: mirime
 */

#ifndef TAURUS_H_
#define TAURUS_H_

#include "../module/PicoBorgReverse.h"
#include "../module/GatlingGun.h"
#include "Robot.h"

class Taurus: public Robot
{
public:
	Taurus(int index);
	virtual ~Taurus();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);

protected:
	GatlingGun m_gatlingGun;
	PicoBorgReverse m_picoBorgReverse;
};

#endif /* TAURUS_H_ */
