/*
 * MainManager.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef MAINMANAGER_H_
#define MAINMANAGER_H_

class Robot;

class MainManager
{
public:
	MainManager();
	virtual ~MainManager();

public:
	bool start(const char* robotName);
	void stop();
	void loop();

private:
	Robot* createRobot(const char* robotName);
	int tcpListen();
	bool tcpAccept();
	void tcpProcess();
	void tcpDisconnect();

private:
	Robot* m_robot;
	int m_listenSocket;
	int m_clientSocket;
	pthread_t m_threadId;

protected:
	static void* networkThread(void* param);
};

#endif /* MAINMANAGER_H_ */
