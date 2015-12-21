/*
 * MissileTurret.h
 *
 *  Created on: Dec 21, 2015
 *      Author: mirime
 */

#ifndef MISSILETURRET_H_
#define MISSILETURRET_H_

#include "IModule.h"

class MissileTurret: public IModule
{
public:
	MissileTurret(int offset);
	virtual ~MissileTurret();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void rotate(int angle);

protected:
	int m_offset;
};

#endif /* MISSILETURRET_H_ */
