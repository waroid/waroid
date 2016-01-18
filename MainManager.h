/*
 * MainManager.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef MAINMANAGER_H_
#define MAINMANAGER_H_

#include "Global.h"
#include "module/BatteryChecker.h"

class Robot;

class MainManager
{
public:
	MainManager();
	virtual ~MainManager();

public:
	bool start(EROBOT::ETYPE erobot, char team);
	void stop();

private:
	Robot* createRobot(EROBOT::ETYPE erobot, char team);

	bool tcpListen();
	void tcpLoop();
	void tcpSend(int socket, EMESSAGE::ETYPE emessage, signed char data0, signed char data1);
	void tcpSend(int socket, EMESSAGE::ETYPE emessage, unsigned short data);
	void tcpDisconnect(int socket);

	bool infoInit();
	void infoLoop();

	void onProcess(const ROBOT_DATA& robotData);

private:
	Robot* m_robot;
	BatteryChecker m_batteryChecker;

	int m_listenSocket;
	int m_ownerSocket;
	pthread_t m_networkThread;

	bool m_infoEnableSend;
	pthread_t m_infoThread;

protected:
	static void* networkWorker(void* param);
	static void* infoWorker(void* param);
};

#endif /* MAINMANAGER_H_ */
