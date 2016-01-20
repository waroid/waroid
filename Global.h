/*
 * Global.h
 *
 *  Created on: Mar 3, 2015
 *      Author: mirime
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "share/defines.h"
#include "share/enums.h"

namespace EWEAPONKIND
{
	enum ETYPE
	{
		NONE = 0, GATLING, CANNON, ROCKET,
		//----------
		TOTAL
	};
}

struct WEAPON_DATA
{
	EWEAPON::ETYPE weapon;
	EWEAPONKIND::ETYPE weaponKind;
	char name[100];
};

extern const char* g_robotTypeNames[EROBOT::TOTAL];
extern WEAPON_DATA g_weaponDatas[EWEAPON::TOTAL];

const int ROBOT_MAX_WEAPON_SLOT = 2;

#endif /* GLOBAL_H_ */
