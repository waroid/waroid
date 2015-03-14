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
#include <sys/sysinfo.h>

#include "Crab.h"
#include "Hydra.h"
#include "Turtle.h"
#include "Toad.h"
#include "MainManager.h"

namespace MAIN_MANAGER
{
	const int MAX_BUFFER_SIZE = 128;
}
using namespace MAIN_MANAGER;

MainManager::MainManager()
		: m_robot(NULL), m_listenSocket(-1), m_ownerSocket(-1), m_networkThreadId(-1), m_infoThreadId(-1)
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

	pthread_create(&m_networkThreadId, NULL, networkThread, this);
	printf("create network thread\n");

	pthread_join(m_networkThreadId, NULL);

	return true;
}

void MainManager::stop()
{
	if (pthread_cancel(m_networkThreadId) == 0)
	{
		pthread_join(m_networkThreadId, NULL);
	}
	printf("cancel network thread\n");

	if (pthread_cancel(m_infoThreadId) == 0)
	{
		pthread_join(m_infoThreadId, NULL);
	}
	printf("cancel info thread\n");

	if (m_ownerSocket != -1)
	{
		close(m_ownerSocket);
		m_ownerSocket = -1;
		printf("close owner socket\n");
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

	struct sockaddr_in sockaddrIn;
	memset(&sockaddrIn, 0, sizeof(sockaddrIn));
	sockaddrIn.sin_family = AF_INET;
	sockaddrIn.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddrIn.sin_port = htons(5002);

	if (bind(s, (struct sockaddr*) &sockaddrIn, sizeof(sockaddrIn)) < 0)
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

void MainManager::tcpLoop()
{
	fd_set master_fds;
	FD_ZERO(&master_fds);
	FD_SET(m_listenSocket, &master_fds);
	int fd_max = m_listenSocket;
	fd_set read_fds;
	for (;;)
	{
		read_fds = master_fds;
		int ret = select(fd_max + 1, &read_fds, 0, 0, 0);
		if (ret == -1)
		{
			printf("failed select. err=%s(%d)\n", strerror(errno), errno);
			return;
		}

		if (FD_ISSET(m_listenSocket, &read_fds))
		{
			struct sockaddr_in sockaddrIn;
			socklen_t socklen = sizeof(sockaddrIn);
			int s = accept(m_listenSocket, (struct sockaddr*) &sockaddrIn, &socklen);
			printf("new connection. socket=%d addr=%s\n", s, inet_ntoa(sockaddrIn.sin_addr));
			if (m_ownerSocket == -1)
			{
				m_ownerSocket = s;
				FD_SET(s, &master_fds);
				if (s > fd_max) fd_max = s;
				tcpSend(s, EMESSAGE::ROBOT_INDEX_ACK, m_robot->getIndex(), 0);
			}
			else
			{
				printf("close connection. reason=EXIST_OWNER, socket=%d addr=%s\n", s, inet_ntoa(sockaddrIn.sin_addr));
				tcpSend(s, EMESSAGE::ERROR_ACK, EERROR::EXIST_OWNER, 0);
				tcpDisconnect(s);
			}
		}

		if (m_ownerSocket != -1 && FD_ISSET(m_ownerSocket, &read_fds))
		{
			ROBOT_DATA robotData;
			int recvLen = recv(m_ownerSocket, &robotData, sizeof(robotData), 0);
			if (recvLen <= 0)
			{
				printf("disconnect. recv=%d err=%s(%d)\n", recvLen, strerror(errno), errno);
				FD_CLR(m_ownerSocket, &master_fds);
				tcpDisconnect(m_ownerSocket);
			}
			else if (recvLen == ROBOT_DATA_SIZE)
			{
				onProcess(robotData);
			}
			else
			{
				printf("invalid packet size. size=%d\n", recvLen);
				tcpDisconnect(m_ownerSocket);
			}

		}
	}
}

void MainManager::tcpSend(int socket, EMESSAGE::ETYPE emessage, signed char data0, signed char data1)
{
	ROBOT_DATA robotData;
	robotData.ID = (signed char) emessage;
	robotData.Data0 = data0;
	robotData.Data1 = data1;
	send(socket, &robotData, ROBOT_DATA_SIZE, 0);
}

void MainManager::tcpSend(int socket, EMESSAGE::ETYPE emessage, unsigned short data)
{
	ROBOT_DATA robotData;
	robotData.ID = (signed char) emessage;
	robotData.Data = data;
	send(socket, &robotData, ROBOT_DATA_SIZE, 0);
}

void MainManager::tcpDisconnect(int socket)
{
	close(socket);
	if (m_ownerSocket == socket)
	{
		m_ownerSocket = -1;

		if (m_robot)
		{
			m_robot->reset();
		}
	}
}

void MainManager::infoLoop()
{
	for (;;)
	{
		struct sysinfo si;
		if (sysinfo(&si) == 0)
		{
			unsigned short upTime = si.uptime / 60;
			tcpSend(m_ownerSocket, EMESSAGE::UP_TIME_ACK, upTime);

			unsigned short usageCpu = si.loads[0] / 100;
			tcpSend(m_ownerSocket, EMESSAGE::USAGE_CPU_ACK, upTime);

			unsigned short freeRam = si.freeram * 10 / 1024 / 1024;
			tcpSend(m_ownerSocket, EMESSAGE::FREE_RAM_ACK, upTime);
		}
		usleep(1000000);
	}
}

void MainManager::onProcess(const ROBOT_DATA& robotData)
{
	printf("recv message. %d %d %d\n", robotData.ID, robotData.Data0, robotData.Data1);
	switch (robotData.ID)
	{
		case EMESSAGE::INFO:
		{
			if (robotData.Data0 == 1)
			{
				if (m_infoThreadId != (pthread_t)-1)
				{
					printf("info thread already on. \n");
					return;
				}
				else
				{
					pthread_create(&m_infoThreadId, NULL, infoThread, this);
					printf("create info thread\n");
				}
			}
			else
			{
				pthread_cancel(m_infoThreadId);
				m_infoThreadId = -1;
			}
		}
		break;

		default:
		{
			m_robot->process(robotData);
		}
	}
}

void* MainManager::networkThread(void* param)
{
	MainManager* mainManager = (MainManager*) param;
	mainManager->tcpLoop();

	return NULL;
}

void* MainManager::infoThread(void* param)
{
	MainManager* mainManager = (MainManager*) param;
	mainManager->infoLoop();

	return NULL;
}
