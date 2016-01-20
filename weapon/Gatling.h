/*
 * Gatling.h
 *
 *  Created on: Dec 14, 2015
 *      Author: mirime
 */

#ifndef GATLING_H_
#define GATLING_H_

#include "Weapon.h"

class Gatling: public Weapon
{
public:
	Gatling(EWEAPON::ETYPE eweapon, bool real);
	virtual ~Gatling();

protected:
	virtual bool onOpen();
	virtual void onClose();
	virtual void onInit();
	virtual void onFireStart();
	virtual void onFireEnd();
};

#endif /* GATLING_H_ */
