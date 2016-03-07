/*
 * DronBoard.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef DRONBOARD_H_
#define DRONBOARD_H_

#include "Module.h"
#include "../Global.h"

class DronBoard: public IModule
{
public:
	DronBoard();
	virtual ~DronBoard();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void active();
	void deactive();
	void command(char cmd, char throttle=DRON_IDLE_VALUE, char roll=DRON_IDLE_VALUE, char pitch=DRON_IDLE_VALUE, char yaw=DRON_IDLE_VALUE);

protected:
	int m_fd;
	bool m_active;
};

#endif /* DRONBOARD_H_ */
