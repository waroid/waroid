/*
 * Robot.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "../Global.h"

class Robot
{
public:
	Robot(EROBOT::ETYPE erobot, int index);
	virtual ~Robot();

public:
	bool start()
	{
		if (onStart() == false) return false;

		onReset();
		return true;
	}

	void stop()
	{
		onStop();
	}

	void reset()
	{
		onReset();
	}

	EROBOT::ETYPE getType() const
	{
		return m_erobot;
	}

	int getIndex() const
	{
		return m_index;
	}

	void process(const ROBOT_DATA& robotData);

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();

	virtual void onToggleCamera(int data0, int data1);
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);
	virtual void onControlTurret(int data0, int data1);

protected:
	EROBOT::ETYPE m_erobot;
	int m_index;
};

#endif /* ROBOT_H_ */
