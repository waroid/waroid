/*
 * Hydrabot.h
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#ifndef HYDRABOT_H_
#define HYDRABOT_H_

#include "../module/PicoBorgReverse.h"
#include "../module/MissileTurret.h"
#include "Robot.h"

class Hydrabot: public Robot
{
public:
	Hydrabot(char team);
	virtual ~Hydrabot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);
	virtual void onControlTurret(int data0, int data1);

private:
	void controlTurret(int angle);

protected:
	PicoBorgReverse m_picoBorgReverse;
	MissileTurret m_missileTurret;
};

#endif /* HYDRABOT_H_ */
