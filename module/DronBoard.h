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

	void command(char cmd, char throttlef=DRON_IDEL_VALUE, char roll=DRON_IDEL_VALUE, char pitch=DRON_IDEL_VALUE, char yaw=DRON_IDEL_VALUE);

protected:
	int m_fd;
};

#endif /* DRONBOARD_H_ */
