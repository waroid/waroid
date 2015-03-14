/* --------------------------------------------------
*
*	Copyright 2015 by Rhaon Ent.
*
* --------------------------------------------------
*/
#pragma once

// ===== �߿� =====
// defines.cs �� ���� ������ �־�� �Ѵ�.
// ====================

const int ROBOT_SEND_BUFFER_SIZE = 1024;
const int ROBOT_RECEIVE_BUFFER_SIZE = 1024;
const int ROBOT_DATA_SIZE = 3;

struct ROBOT_DATA
{
	signed char ID;
	union
	{
		unsigned short Data;
		struct
		{
			signed char Data0;
			signed char Data1;
		};
	};
	
};
