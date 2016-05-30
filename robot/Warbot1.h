/*
 * Warbot1.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef WARBOT1_H_
#define WARBOT1_H_

#include "../module/PololuQik.h"
#include "Robot.h"

class Warbot1: public Robot
{
public:
	Warbot1(char team);
	virtual ~Warbot1();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PololuQik m_pololuQik;
};

#endif /* WARBOT1_H_ */
