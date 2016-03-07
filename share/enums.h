/* --------------------------------------------------
 *
 *	Copyright 2015 by Rhaon Ent.
 *
 * --------------------------------------------------
 */
#pragma once

// ===== 중요 =====
// enums.cs도 같이 수정해 주어야 한다.
// ====================

namespace EMESSAGE
{
	enum ETYPE
	{
		NONE = 0,
		ROBOT_ACK,
		TOGGLE_CAMERA,
		FIRE,
		MOVE,
		CONTROL_TURRET,
		ERROR_ACK,
		INFO,
		UP_TIME_ACK,
		USAGE_CPU_ACK,
		FREE_RAM_ACK,
		TEMPERATURE_CPU_ACK,
		BATTERY_VOLT_ACK,
		PING,
		PING_ACK,
		EQUIP_WEAPON,
		CONTROL_THROTTLE,
		//----------
		TOTAL,
	};
}

namespace EROBOT
{
	enum ETYPE
	{
		TESTBOT = 0,
		CRABBOT,
		HYDRABOT,
		TAURUSBOT,
		TURTLEBOT,
		SCORPIOBOT,
		TOADBOT,
		WARTHOGBOT,
		SPIDERBOT,
		THORBOT,
		HARPYBOT,
		//----------
		TOTAL,
	};
}

namespace EWEAPON
{
	enum ETYPE
	{
		NONE = 0,
		M134D_MINIGUN,
		STARSTREAK_AVENGER,
		GAU_19_B_HMG,
		_2A72_AUTOCANNON,
		XM214_MICROGUN,
		M242_CHAINGUN,
		BOFORS_L60,
		M61_VULCAN,
		PLASMA_GUN,
		ENERGY_CANNON,
		LASER_CANNON,
		//----------
		TOTAL
	};
}

namespace EDIRECTION
{
	enum ETYPE
	{
		IDLE = 0,
		FORWARD,
		RIGHT_FORWARD,
		RIGHT,
		RIGHT_BACKWARD,
		BACKWARD,
		LEFT_BACKWARD,
		LEFT,
		LEFT_FORWARD,
		TURN_RIGHT,
		TURN_LEFT,
		//----------
		TOTAL,
	};
}

namespace ESPEED
{
	enum ETYPE
	{
		NONE = 0, SNAKE, NORMAL, BOOST,
		//----------
		TOTAL,
	};
}

namespace EERROR
{
	enum ETYPE
	{
		SUCCESS = 0, EXIST_OWNER,
		//----------
		TOTAL,
	};
}

