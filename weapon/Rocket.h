/*
 * Rocket.h
 *
 *  Created on: Jan 20, 2016
 *      Author: mirime
 */

#ifndef ROCKET_H_
#define ROCKET_H_

#include "Weapon.h"

class Rocket: public Weapon
{
public:
	Rocket(EWEAPON::ETYPE eweapon, bool real);
	virtual ~Rocket();

public:
	void tilt(int angle);

protected:
	virtual bool onOpen();
	virtual void onClose();
	virtual void onInit();
	virtual void onFireStart();
	virtual void onFireEnd();
};

#endif /* ROCKET_H_ */
