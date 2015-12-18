/*
 * AdafruitAudioFxSoundBoard.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include "../core/Logger.h"
#include "AdafruitAudioFxSoundBoard.h"

AdafruitAudioFxSoundBoard::AdafruitAudioFxSoundBoard()
		: m_fd(-1), m_thread(-1)
{
	// TODO Auto-generated constructor stub

}

AdafruitAudioFxSoundBoard::~AdafruitAudioFxSoundBoard()
{
	// TODO Auto-generated destructor stub
}

const char* AdafruitAudioFxSoundBoard::getDescription() const
{
	return "Adafruit Autio Fx Sound Board";
}

bool AdafruitAudioFxSoundBoard::open()
{
	m_fd = serialOpen("/dev/ttyAMA0", 9600);
	GCHECK_RETFALSE(m_fd != -1);

	GCHECK_RETFALSE(pthread_create(&m_thread, NULL, worker, this) == 0);

	init();

	return true;
}

void AdafruitAudioFxSoundBoard::close()
{
	init();
	if (m_fd != -1)
	{
		serialClose(m_fd);
		m_fd = -1;
	}
}

void AdafruitAudioFxSoundBoard::init()
{
	serialPuts(m_fd, "L\n");
}

void AdafruitAudioFxSoundBoard::play(int track)
{
	char buffer[32] = {0};
	sprintf(buffer, "#%d\n", track);
	serialPuts(m_fd, buffer);
}

void AdafruitAudioFxSoundBoard::volumeUp()
{
	serialPuts(m_fd, "+\n");
}

void AdafruitAudioFxSoundBoard::volumeDown()
{
	serialPuts(m_fd, "-\n");
}

void AdafruitAudioFxSoundBoard::loop()
{
	int len = 0;
	char buffer[256];
	for (;;)
	{
		int ch = serialGetchar(m_fd);
		switch (ch)
		{
			case '\r':
			case '\n':
			{
				if (len > 0)
				{
					buffer[len] = 0;
					GLOG("%s", buffer);
					len = 0;
				}
			}
			break;
			default:
			{
				buffer[len++] = ch;
			}
			break;
		}
	}
}

void* AdafruitAudioFxSoundBoard::worker(void* param)
{
	GLOG("start AdafruitAudioFxSoundBoard thread");
	((AdafruitAudioFxSoundBoard*) param)->loop();
	GLOG("stop AdafruitAudioFxSoundBoard thread");

	return NULL;
}
