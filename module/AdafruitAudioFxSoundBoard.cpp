/*
 * AdafruitAudioFxSoundBoard.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: mirime
 */

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Logger.h"
#include "AdafruitAudioFxSoundBoard.h"

namespace ADAFRUIT_AUDIO_FX_SOUND_BOARD
{
	const int GPIO_RESET = 27;
}
using namespace ADAFRUIT_AUDIO_FX_SOUND_BOARD;

AdafruitAudioFxSoundBoard::AdafruitAudioFxSoundBoard(int volume)
		: m_fd(-1), m_volume(volume), m_currentVolume(0), m_thread(-1)
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

	pullUpDnControl(GPIO_RESET, PUD_UP);
	delay(10);
	pullUpDnControl(GPIO_RESET, PUD_OFF);
	delay(10);
	pinMode(GPIO_RESET, INPUT);
	delay(10);
	serialPuts(m_fd, "L\n");
	delay(1000);

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
	m_currentVolume = 0;
	volumeUp();
	delay(1000);
	if (m_currentVolume > 0)
	{
		int count = (m_volume - m_currentVolume) / 2;
		if (count > 0)
		{
			for (int i = 0; i < count; ++i)
			{
				volumeUp();
				delay(100);
			}
		}
		else
		{
			count *= -1;
			for (int i = 0; i < count; ++i)
			{
				volumeDown();
				delay(100);
			}
		}
	}
}

void AdafruitAudioFxSoundBoard::play(int track)
{
	char buffer[32] =
	{ 0 };
	sprintf(buffer, "#%d\n", track);
	serialPuts(m_fd, buffer);
}

void AdafruitAudioFxSoundBoard::play(const char* trackName)
{
	char buffer[32] =
	{ 0 };
	sprintf(buffer, "P%s\n", trackName);
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

					if (len == 5 && buffer[0] == '0' && buffer[1] == '0')
					{
						m_currentVolume = atoi(buffer);
					}
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
