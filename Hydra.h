/*
 * Hydra.h
 *
 *  Created on: 2015. 2. 14.
 *      Author: mirime
 */

#ifndef HYDRA_H_
#define HYDRA_H_

#include "PololuQik.h"
#include "ServoMotor.h"
#include "Robot.h"

class Hydra: public Robot
{
public:
	Hydra(int index);
	virtual ~Hydra();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onMove(int data0, int data1);
	virtual void onControlTurret(int data0, int data1);

private:
	void controlTurret(int angle);

protected:
	PololuQik m_pololuQik;
	ServoMotor m_servoMotor;
};

#endif /* HYDRA_H_ */
