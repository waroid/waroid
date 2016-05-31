/*
 * Warbot2.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef WARBOT2_H_
#define WARBOT2_H_

#include "../module/PololuQik.h"
#include "Robot.h"

class Warbot2: public Robot
{
public:
	Warbot2(char team);
	virtual ~Warbot2();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PololuQik m_pololuQik;
};

#endif /* WARBOT2_H_ */
