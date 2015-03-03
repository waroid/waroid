/*
 * Global.h
 *
 *  Created on: Mar 3, 2015
 *      Author: mirime
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

enum EMESSAGE
{
	MSG_NONE = 0,
	MSG_ROBOT_INDEX_ACK,
	MSG_TOGGLE_CAMERA,
	MSG_FIRE,
	MSG_MOVE,
	MSG_CONTROL_TURRET,
};

enum EROBOT
{
	ROBOT_NONE = 0, ROBOT_CRAB, ROBOT_HYDRA, ROBOT_TURTLE, ROBOT_TOAD,
};

#endif /* GLOBAL_H_ */
