/*
 * Hellcat.h
 *
 *  Created on: Dec 30, 2015
 *      Author: mirime
 */

#ifndef HELLCAT_H_
#define HELLCAT_H_

#include "../module/PicoBorgReverse.h"
#include "../module/GatlingGun.h"
#include "Robot.h"

class Hellcat: public Robot
{
public:
	Hellcat(int index);
	virtual ~Hellcat();

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

#endif /* HELLCAT_H_ */
