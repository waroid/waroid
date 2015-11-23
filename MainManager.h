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

	bool tcpListen();
	void tcpLoop();
	void tcpSend(int socket, EMESSAGE::ETYPE emessage, signed char data0, signed char data1);
	void tcpSend(int socket, EMESSAGE::ETYPE emessage, unsigned short data);
	void tcpDisconnect(int socket);

	bool batteryInitAdc();
	int batteryReadAdc();
	void batteryLoop();

	bool infoInit();
	void infoLoop();

	void onProcess(const ROBOT_DATA& robotData);

private:
	Robot* m_robot;

	int m_listenSocket;
	int m_ownerSocket;
	pthread_t m_networkThreadId;

	float m_batteryVolts;
	pthread_t m_batteryThreadId;

	bool m_infoEnableSend;
	pthread_t m_infoThreadId;

protected:
	static void* networkThread(void* param);
	static void* batteryThread(void* param);
	static void* infoThread(void* param);
};

#endif /* MAINMANAGER_H_ */
