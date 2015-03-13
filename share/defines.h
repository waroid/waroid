/* --------------------------------------------------
*
*	Copyright 2015 by Rhaon Ent.
*
* --------------------------------------------------
*/
#pragma once

// ===== 중요 =====
// defines.cs 도 같이 수정해 주어야 한다.
// ====================

const int ROBOT_SEND_BUFFER_SIZE = 1024;
const int ROBOT_RECEIVE_BUFFER_SIZE = 1024;
const int ROBOT_DATA_SIZE = 3;

struct ROBOT_DATA
{
	signed char ID;
	signed char Data0;
	signed char Data1;
};