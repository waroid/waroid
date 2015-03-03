/*
 * Crab.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef CRAB_H_
#define CRAB_H_

#include "PololuQik.h"
#include "Robot.h"

class Crab: public Robot
{
public:
	Crab(int index);
	virtual ~Crab();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);

protected:
	PololuQik m_pololuQik;
};

#endif /* CRAB_H_ */
