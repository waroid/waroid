/*
 * ArduinoBoard.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef ARDUINOBOARD_H_
#define ARDUINOBOARD_H_

#include "Module.h"
#include "../Global.h"

class ArduinoBoard: public IModule
{
public:
	ArduinoBoard();
	virtual ~ArduinoBoard();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void motion(char command, char option);

protected:
	int m_fd;
};

#endif /* ARDUINOBOARD_H_ */
