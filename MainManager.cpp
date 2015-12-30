/*
 * MainManager.cpp
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <wiringPi.h>
#include "core/Logger.h"
#include "robot/Crab.h"
#include "robot/Hydra.h"
#include "robot/Turtle.h"
#include "robot/Toad.h"
#include "robot/Scorpio.h"
#include "robot/Hellcat.h"
#include "MainManager.h"

namespace MAIN_MANAGER
{
	const int MAX_BUFFER_SIZE = 128;
	const int INVALID_SOCKET = -1;
}
using namespace MAIN_MANAGER;

MainManager::MainManager()
		: m_robot(NULL), m_listenSocket(INVALID_SOCKET), m_ownerSocket(INVALID_SOCKET), m_networkThread(-1), m_infoEnableSend(false), m_infoThread(-1)
{
}

MainManager::~MainManager()
{
}

bool MainManager::start(int robotIndex)
{
	m_robot = createRobot(robotIndex);
	GCHECK_RETFALSE(m_robot);
	GCHECK_RETFALSE(m_robot->start());

	GCHECK_RETFALSE(tcpListen());
	GLOG("listened tcp");

	GCHECK_RETFALSE(m_batteryChecker.open());
	GLOG("initialized battery adc");

	GCHECK_RETFALSE(infoInit());
	GLOG("initialized info");

	pthread_join(m_networkThread, NULL);
	pthread_join(m_infoThread, NULL);

	return true;
}

void MainManager::stop()
{
	if (m_networkThread >= 0)
	{
		if (pthread_cancel(m_networkThread) == 0)
		{
			pthread_join(m_networkThread, NULL);
		}
		GLOG("cancel network thread");
	}

	if (m_infoThread >= 0)
	{
		if (pthread_cancel(m_infoThread) == 0)
		{
			pthread_join(m_infoThread, NULL);
		}
		GLOG("cancel info thread");
	}

	if (m_ownerSocket != INVALID_SOCKET)
	{
		close(m_ownerSocket);
		m_ownerSocket = INVALID_SOCKET;
		GLOG("close owner socket");
	}

	if (m_listenSocket != INVALID_SOCKET)
	{
		close(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;
		GLOG("close listen socket");
	}

	m_batteryChecker.close();

	if (m_robot)
	{
		m_robot->stop();
		delete m_robot;
		m_robot = NULL;
		GLOG("delete robot");
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

		case 9:
		case 10:
			robot = new Scorpio(robotIndex);
		break;

		case 11:
		case 12:
			robot = new Hellcat(robotIndex);
		break;
	}
	GCHECKV_RETNULL(robot, "robot index=%d", robotIndex);

	return robot;
}

bool MainManager::tcpListen()
{
	m_listenSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
	GCHECK_RETFALSE(m_listenSocket != INVALID_SOCKET);

	int optval = 1;
	setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	struct sockaddr_in sockaddrIn;
	memset(&sockaddrIn, 0, sizeof(sockaddrIn));
	sockaddrIn.sin_family = AF_INET;
	sockaddrIn.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddrIn.sin_port = htons(5002);

	GCHECK_RETFALSE(bind(m_listenSocket, (struct sockaddr* ) &sockaddrIn, sizeof(sockaddrIn)) != -1);
	GCHECK_RETFALSE(listen(m_listenSocket, 3) != -1);

	GCHECK_RETFALSE(pthread_create(&m_networkThread, NULL, networkWorker, this)==0);

	return true;
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
		GCHECK_RETURN(select(fd_max + 1, &read_fds, 0, 0, 0) != -1);

		if (FD_ISSET(m_listenSocket, &read_fds))
		{
			struct sockaddr_in sockaddrIn;
			socklen_t socklen = sizeof(sockaddrIn);
			int s = accept(m_listenSocket, (struct sockaddr*) &sockaddrIn, &socklen);
			GLOG("new connection. socket=%d addr=%s", s, inet_ntoa(sockaddrIn.sin_addr));
			if (m_ownerSocket == INVALID_SOCKET)
			{
				m_ownerSocket = s;
				FD_SET(s, &master_fds);
				if (s > fd_max) fd_max = s;
				tcpSend(s, EMESSAGE::ROBOT_INDEX_ACK, m_robot->getIndex(), 0);
			}
			else
			{
				GLOG("close connection. reason=EXIST_OWNER, socket=%d addr=%s", s, inet_ntoa(sockaddrIn.sin_addr));
				tcpSend(s, EMESSAGE::ERROR_ACK, EERROR::EXIST_OWNER, 0);
				tcpDisconnect(s);
			}
		}

		if (m_ownerSocket != INVALID_SOCKET && FD_ISSET(m_ownerSocket, &read_fds))
		{
			ROBOT_DATA robotData;
			int recvLen = recv(m_ownerSocket, &robotData, sizeof(robotData), 0);
			if (recvLen <= 0)
			{
				GLOG("disconnect. recv=%d err=%s(%d)", recvLen, strerror(errno), errno);
				FD_CLR(m_ownerSocket, &master_fds);
				tcpDisconnect(m_ownerSocket);
			}
			else if (recvLen == ROBOT_DATA_SIZE)
			{
				onProcess(robotData);
			}
			else
			{
				GLOG("invalid packet size. size=%d", recvLen);
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
		m_ownerSocket = INVALID_SOCKET;
		if (m_robot)
		{
			m_robot->reset();
		}
	}
}

bool MainManager::infoInit()
{
	GCHECK_RETFALSE(pthread_create(&m_infoThread, NULL, infoWorker, this)==0);

	return true;
}

void MainManager::infoLoop()
{
	for (;;)
	{
		if (m_infoEnableSend)
		{
			struct sysinfo si;
			if (sysinfo(&si) == 0)
			{
				unsigned short upTime = si.uptime;
				tcpSend(m_ownerSocket, EMESSAGE::UP_TIME_ACK, upTime);

				unsigned short usageCpu = si.loads[0] / 100;
				tcpSend(m_ownerSocket, EMESSAGE::USAGE_CPU_ACK, usageCpu);

				unsigned short freeRam = si.freeram * 10 / 1024 / 1024;
				tcpSend(m_ownerSocket, EMESSAGE::FREE_RAM_ACK, freeRam);
			}

			{
				FILE* fp = popen("/opt/vc/bin/vcgencmd measure_temp", "r");
				if (fp != NULL)
				{
					float temperature;
					fscanf(fp, "temp=%f'C", &temperature);
					pclose(fp);

					unsigned short temperatureCpu = (unsigned short) (temperature * 10);
					tcpSend(m_ownerSocket, EMESSAGE::TEMPERATURE_CPU_ACK, temperatureCpu);
				}
			}

			{
				unsigned short batteryVolt = (unsigned short) (m_batteryChecker.getVolts() * 100);
				tcpSend(m_ownerSocket, EMESSAGE::BATTERY_VOLT_ACK, batteryVolt);
			}
		}

		sleep(1);
	}
}

void MainManager::onProcess(const ROBOT_DATA& robotData)
{
	GLOG("recv message. %d: %d,%d or %u", robotData.ID, robotData.Data0, robotData.Data1, robotData.Data);
	switch (robotData.ID)
	{
		case EMESSAGE::INFO:
		{
			m_infoEnableSend = (robotData.Data != 0);
		}
		break;

		default:
		{
			m_robot->process(robotData);
		}
	}
}

void* MainManager::networkWorker(void* param)
{
	GLOG("start network thread");
	MainManager* mainManager = (MainManager*) param;
	mainManager->tcpLoop();
	GLOG("stop network thread");

	return NULL;
}

void* MainManager::infoWorker(void* param)
{
	GLOG("start info thread");
	MainManager* mainManager = (MainManager*) param;
	mainManager->infoLoop();
	GLOG("stop info thread");

	return NULL;
}
