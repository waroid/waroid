/*
 * Weapon.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: mirime
 */

#include "../core/Logger.h"
#include "Weapon.h"

Weapon::Weapon(EWEAPON::ETYPE eweapon, bool real)
		: m_eweapon(eweapon), m_real(real)
{
	// TODO Auto-generated constructor stub

}

Weapon::~Weapon()
{
	// TODO Auto-generated destructor stub
}

const char* Weapon::getName() const
{
	return g_weaponDatas[m_eweapon].name;
}

EWEAPONKIND::ETYPE Weapon::getKind() const
{
	return g_weaponDatas[m_eweapon].weaponKind;
}

bool Weapon::open()
{
	GCHECK_RETFALSE(onOpen());
	GLOG("[%s]opened", getName());

	onInit();
	GLOG("[%s]initialized", getName());

	return true;
}

void Weapon::close()
{
	onClose();
	GLOG("[%s]closed", getName());
}

void Weapon::init()
{
	onInit();
	GLOG("[%s]initialized", getName());
}

void Weapon::fire(bool on)
{
	GDEV("[%s]fire. on=%s", getName(), on ? "true" : "false");
	if (on) onFireStart();
	else onFireEnd();
}
