/*
 * MainManager.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef MAINMANAGER_H_
#define MAINMANAGER_H_

#include "Global.h"

class Robot;

class MainManager
{
public:
	MainManager();
	virtual ~MainManager();

public:
	bool start(int robotIndex);
	void stop();

private:
	Robot* createRobot(int robotIndex);
	int tcpListen();
	void tcpLoop();
	void tcpSend(int socket, EMESSAGE::ETYPE emessage, int data0, int data1);
	void tcpDisconnect(int socket);

private:
	Robot* m_robot;
	int m_listenSocket;
	int m_ownerSocket;
	pthread_t m_threadId;

protected:
	static void* networkThread(void* param);
};

#endif /* MAINMANAGER_H_ */
