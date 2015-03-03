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
	void loop();

private:
	Robot* createRobot(int robotIndex);
	int tcpListen();
	bool tcpAccept();
	void tcpProcess();
	void tcpDisconnect();
	void tcpSend(EMESSAGE emessage, signed char data0, signed char data1);

private:
	Robot* m_robot;
	int m_listenSocket;
	int m_clientSocket;
	pthread_t m_threadId;

protected:
	static void* networkThread(void* param);
};

#endif /* MAINMANAGER_H_ */
