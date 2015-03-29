/*
 * PicoBorgReverse.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef PICOBORGREVERSE_H_
#define PICOBORGREVERSE_H_

#include "IModule.h"

class PicoBorgReverse: public IModule
{
protected:
	union READDATA
	{
		int value;
		unsigned char data[4];

		READDATA()
				: value(-1)
		{
		}
	};
public:
	PicoBorgReverse(int i2cAddress);
	virtual ~PicoBorgReverse();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void move(float power0, float power1);

protected:
	void setMotor0(int power);
	void setMotor1(int power);

protected:
	int m_fd;
	int m_i2cAddress;
};

#endif /* PICOBORGREVERSE_H_ */
