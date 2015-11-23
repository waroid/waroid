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
		ROBOT_INDEX_ACK,
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
		//----------
		TOTAL,
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
	};
}

namespace EROBOT
{
	enum ETYPE
	{
		NONE = 0,
		CRAB,
		HYDRA,
		TURTLE,
		TOAD,
		SCORPIO,
		//----------
		TOTAL,
	};
}

namespace EERROR
{
	enum ETYPE
	{
		SUCCESS = 0,
		EXIST_OWNER,
		//----------
		TOTAL,
	};
}

