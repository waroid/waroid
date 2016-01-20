/*
 * Taurusbot.h
 *
 *  Created on: Jan 4, 2016
 *      Author: mirime
 */

#ifndef TAURUSBOT_H_
#define TAURUSBOT_H_

#include "../module/PicoBorgReverse.h"
#include "Robot.h"

class Taurusbot: public Robot
{
public:
	Taurusbot(char team);
	virtual ~Taurusbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);

protected:
	PicoBorgReverse m_picoBorgReverse;
};

#endif /* TAURUSBOT_H_ */
