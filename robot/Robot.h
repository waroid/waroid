/*
 * Robot.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "../core/WavPlayer.h"
#include "../weapon/Weapon.h"
#include "../Global.h"

class Robot
{
public:
	Robot(EROBOT::ETYPE erobot, char team);
	virtual ~Robot();

public:
	EROBOT::ETYPE getRobot() const
		{
			return m_erobot;
		}

		char getTeam() const
		{
			return m_team;
		}

		const char* getName() const
		{
			return m_name;
		}

	bool start();
	void stop();
	void reset();
	void process(const ROBOT_DATA& robotData);

protected:
	Weapon* createWeapon(EWEAPON::ETYPE eweapon, bool real);

	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();

	virtual void onToggleCamera(int data0, int data1);
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);
	virtual void onControlTurret(int data0, int data1);
	virtual void onEquipWeapon(int data0, int data1);

protected:
	EROBOT::ETYPE m_erobot;
	char m_team;
	char m_name[100];
	WavPlayer m_startupWav;
	WavPlayer m_ttsWav;
	Weapon* m_weapons[ROBOT_MAX_WEAPON_SLOT];
};

#endif /* ROBOT_H_ */
