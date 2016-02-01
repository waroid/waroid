/*
 * TestRobot.h
 *
 *  Created on: Jan 12, 2016
 *      Author: mirime
 */

#ifndef TESTBOT_H_
#define TESTBOT_H_

#include "../core/WavPlayer.h"
#include "../module/TestModule.h"
#include "Robot.h"

class Testbot: public Robot
{
public:
	Testbot(char team);
	virtual ~Testbot();

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();
	virtual void onToggleCamera(int data0, int data1);
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);
	virtual void onControlTurret(int data0, int data1);
	virtual void onEquipWeapon(int data0, int data1);

protected:
	TestModule m_testModule;
	WavPlayer m_testWav;
};

#endif /* TESTBOT_H_ */
