/*
 * Robot.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef ROBOT_H_
#define ROBOT_H_

class Robot
{
public:
	Robot(const char* name);
	virtual ~Robot();

public:
	bool start()
	{
		if (onStart() == false)
			return false;

		onReset();
		return true;
	}

	void stop()
	{
		onReset();
		onStop();
	}

	void reset()
	{
		onReset();
	}

	void process(int message, int data0, int data1);

protected:
	virtual bool onStart();
	virtual void onStop();
	virtual void onReset();

	virtual void onToggleCamera(int data0, int data1);
	virtual void onFire(int data0, int data1);
	virtual void onMove(int data0, int data1);
	virtual void onControlTurret(int data0, int data1);

protected:
	char m_name[100];
};

#endif /* ROBOT_H_ */
