/*
 * MainManager.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#include "Crab.h"
#include "Hydra.h"
#include "Turtle.h"
#include "Toad.h"
#include "MainManager.h"

namespace MAIN_MANAGER
{
	const int MESSAGE_SIZE = 3;
}
using namespace MAIN_MANAGER;

MainManager::MainManager()
		: m_robot(NULL), m_listenSocket(-1), m_clientSocket(-1), m_threadId(-1)
{
}

MainManager::~MainManager()
{
}

bool MainManager::start(int robotIndex)
{
	m_robot = createRobot(robotIndex);
	if (m_robot == NULL) return false;
	if (m_robot->start() == false) return false;

	m_listenSocket = tcpListen();
	if (m_listenSocket == -1) return false;
	printf("tcp listen\n");

	pthread_create(&m_threadId, NULL, networkThread, this);
	printf("create network thread\n");

	return true;
}

void MainManager::stop()
{
	if (pthread_cancel(m_threadId) == 0)
	{
		pthread_join(m_threadId, NULL);
	}
	printf("cancel network thread\n");

	if (m_clientSocket != -1)
	{
		close(m_clientSocket);
		m_clientSocket = -1;
		printf("close client socket\n");
	}

	if (m_listenSocket != -1)
	{
		close(m_listenSocket);
		m_listenSocket = -1;
		printf("close listen socket\n");
	}

	if (m_robot)
	{
		m_robot->stop();
		delete m_robot;
		m_robot = NULL;
		printf("delete robot\n");
	}
}

void MainManager::loop()
{
	for (;;)
	{
		usleep(50000);
	}
}

Robot* MainManager::createRobot(int robotIndex)
{
	Robot* robot = NULL;
	switch (robotIndex)
	{
	case 1:
	case 2:
		robot = new Crab(robotIndex);
		break;

	case 3:
	case 4:
		robot = new Hydra(robotIndex);
		break;

	case 5:
	case 6:
		robot = new Turtle(robotIndex);
		break;

	case 7:
	case 8:
		robot = new Toad(robotIndex);
		break;
	}

	if (robot == NULL)
	{
		printf("invalid robot. index=%d\n", robotIndex);
	}

	return robot;
}

int MainManager::tcpListen()
{
	int s = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
	if (s == -1)
	{
		printf("failed create socket. err=%s(%d)", strerror(errno), errno);
		return -1;
	}

	int optval = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	struct sockaddr_in sockAddrIn;
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	sockAddrIn.sin_family = AF_INET;
	sockAddrIn.sin_addr.s_addr = htonl(INADDR_ANY);
	sockAddrIn.sin_port = htons(5002);

	if (bind(s, (struct sockaddr*) &sockAddrIn, sizeof(sockAddrIn)) < 0)
	{
		printf("failed bind(). err=%s(%d)\n", strerror(errno), errno);
		close(s);
		return -1;
	}

	if (listen(s, 3) == -1)
	{
		printf("failed listen(). err=%s(%d)\n", strerror(errno), errno);
		close(s);
		return -1;
	}

	return s;
}

bool MainManager::tcpAccept()
{
	static struct sockaddr_in sockAddrIn;
	static socklen_t sockAddrlen = sizeof(sockAddrIn);
	m_clientSocket = accept(m_listenSocket, (struct sockaddr*) &sockAddrIn, &sockAddrlen);
	if (m_clientSocket != -1)
	{
		tcpSend(MSG_ROBOT_INDEX_ACK, m_robot->getIndex(), 0);
		printf("connected. addr=%s:%d\n", inet_ntoa(sockAddrIn.sin_addr), ntohs(sockAddrIn.sin_port));
	}

	return (m_clientSocket != -1);
}

void MainManager::tcpProcess()
{
	if (m_clientSocket != -1)
	{
		signed char message[MESSAGE_SIZE];
		for (;;)
		{
			int res = recv(m_clientSocket, message, MESSAGE_SIZE, 0);
			if (res < 0)
			{
				printf("failed recv. err=%s(%d)\n", strerror(errno), errno);
				tcpDisconnect();
				return;
			}
			else if (res == 0)
			{
				printf("disconnect.\n");
				tcpDisconnect();
				return;
			}
			else if (res == MESSAGE_SIZE)
			{
				printf("recv message. %d %d %d\n", message[0], message[1], message[2]);
				m_robot->process(message[0], message[1], message[2]);
			}
			else
			{
				printf("invalid packet size. size=%d\n", res);
				return;
			}
		}
	}
}

void MainManager::tcpDisconnect()
{
	if (m_clientSocket != -1)
	{
		close(m_clientSocket);
		m_clientSocket = -1;
		printf("close client socket\n");
	}

	if (m_robot)
	{
		m_robot->reset();
	}
}

void MainManager::tcpSend(EMESSAGE emessage, signed char data0, signed char data1)
{
	if (m_clientSocket != -1)
	{
		signed char message[MESSAGE_SIZE] = {(signed char)emessage, data0, data1};
		send(m_clientSocket, message, MESSAGE_SIZE, 0);
	}
}

void* MainManager::networkThread(void* param)
{
	MainManager* mainManager = (MainManager*) param;

	for (;;)
	{
		if (mainManager->tcpAccept())
		{
			mainManager->tcpProcess();
		}

		usleep(100000);
	}

	return NULL;
}
