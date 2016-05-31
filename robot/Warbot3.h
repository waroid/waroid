/*
 * Warbot3.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef WARBOT3_H_
#define WARBOT3_H_

#include "../module/PololuQik.h"
#include "Robot.h"

class Warbot3: public Robot
{
public:
	Warbot3(char team);
	virtual ~Warbot3();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PololuQik m_pololuQik;
};

#endif /* WARBOT3_H_ */
