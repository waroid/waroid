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
	char wavFile[100];
};

extern const char* g_soundDir;
extern const char* g_robotTypeNames[EROBOT::TOTAL];
extern WEAPON_DATA g_weaponDatas[EWEAPON::TOTAL];

const int ROBOT_MAX_WEAPON_SLOT = 2;

//aduino motion
#define ARDUINO_MOT_BASIC		0x00
#define ARDUINO_MOT_FORWARD		0x01
#define ARDUINO_MOT_BACKWARD	0x02
#define ARDUINO_MOT_LEFT_SLIDE	0x03
#define ARDUINO_MOT_RIGHT_SLIDE	0x04
#define ARDUINO_MOT_LEFT_TURN	0x05
#define ARDUINO_MOT_RIGHT_TURN	0x06

//drop command
#define DRON_COMMAND_ACK		0x01
#define DRON_COMMAND_REQUEST	0x02
#define DRON_COMMAND_START		0x03
#define DRON_COMMAND_STOP		0x04
#define DRON_COMMAND_CONTROL	0x05
#define DRON_COMMAND_ULTRASONIC	0x06
#define DRON_COMMAND_REMOTE		0x07

#define DRON_IDEL_VALUE	0x7f


#endif /* GLOBAL_H_ */
