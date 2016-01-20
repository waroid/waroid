/*
 * AduinoBoard.h
 *
 *  Created on: Jan 18, 2016
 *      Author: mirime
 */

#ifndef ADUINOBOARD_H_
#define ADUINOBOARD_H_

#include "Module.h"

class AduinoBoard: public IModule
{
public:
	AduinoBoard();
	virtual ~AduinoBoard();

	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

protected:
	int m_fd;
};

#endif /* ADUINOBOARD_H_ */
