/*
 * WavPlayer.h
 *
 *  Created on: Jan 29, 2016
 *      Author: mirime
 */

#ifndef WAVPLAYER_H_
#define WAVPLAYER_H_

#include <stdio.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

class WavPlayer
{
protected:
	struct DATA
	{
		short* buffer;
		snd_pcm_uframes_t frames;
		DATA* next;

		DATA(short* _buffer, size_t _bufferSize, snd_pcm_uframes_t _frames)
				: buffer(NULL), frames(_frames), next(NULL)
		{
			buffer = (short*) malloc(_bufferSize);
			memcpy(buffer, _buffer, _bufferSize);
		}
		~DATA()
		{
			if (buffer)
			{
				delete buffer;
				buffer = NULL;
			}
			frames = 0;
			next = NULL;
		}
	};

public:
	WavPlayer();
	virtual ~WavPlayer();

public:
	bool load(const char* wavFile);
	void close();

	void play();

protected:
	snd_pcm_t* m_pcm;
	DATA* m_data;
};

#endif /* WAVPLAYER_H_ */
