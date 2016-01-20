/*
 * Weapon.h
 *
 *  Created on: Jan 20, 2016
 *      Author: mirime
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include "../Global.h"

class Weapon
{
public:
	Weapon(EWEAPON::ETYPE eweapon, bool real);
	virtual ~Weapon();

public:
	const char* getName() const;
	EWEAPONKIND::ETYPE getKind() const;

	bool open();
	void close();
	void init();
	void fire(bool on);

protected:
	bool isReal() const
	{
		return m_real;
	}

	virtual bool onOpen() = 0;
	virtual void onClose() = 0;
	virtual void onInit() = 0;
	virtual void onFireStart() = 0;
	virtual void onFireEnd() = 0;

protected:
	EWEAPON::ETYPE m_eweapon;
	bool m_real;
};

#endif /* WEAPON_H_ */
