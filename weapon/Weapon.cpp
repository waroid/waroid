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
	char temp[256];
	sprintf(temp, "%s/%s", g_soundDir, g_weaponDatas[m_eweapon].wavFile);
	GCHECK_RETFALSE(m_weaponWav.load(temp));

	GCHECK_RETFALSE(onOpen());

	GLOG("[%s]opened", getName());

	return true;
}

void Weapon::close()
{
	m_weaponWav.close();

	onClose();

	GLOG("[%s]closed", getName());
}

void Weapon::init()
{
	m_weaponWav.stop();

	onInit();

	GLOG("[%s]initialized", getName());
}

void Weapon::fire(bool on)
{
	GDEV("[%s]fire. on=%s", getName(), on ? "true" : "false");
	if (on)onFireStart();
	else onFireEnd();
}
