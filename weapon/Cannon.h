/*
 * Cannon.h
 *
 *  Created on: Nov 20, 2015
 *      Author: mirime
 */

#ifndef CANNON_H_
#define CANNON_H_

#include "Weapon.h"

class Cannon: public Weapon
{
public:
	Cannon(EWEAPON::ETYPE eweapon, bool real);
	virtual ~Cannon();

protected:
	virtual bool onOpen();
	virtual void onClose();
	virtual void onInit();
	virtual void onFireStart();
	virtual void onFireEnd();
};

#endif /* CANNON_H_ */
