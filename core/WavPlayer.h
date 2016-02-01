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
public:
	static const int LOOPING = -1;

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

public:
	void play(int count=1);
	void stop();

private:
	void work();
	void writePcm();

protected:
	snd_pcm_t* m_pcm;
	DATA* m_data;

	char m_wavFile[256];
	pthread_t m_thread;
	pthread_mutex_t m_threadMutex;
	pthread_cond_t m_threadCond;
	bool m_playing;
	int m_count;

private:
	static void* worker(void* param);
};

#endif /* WAVPLAYER_H_ */
