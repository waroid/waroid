/*
 * WavPlayer.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: mirime
 */

#include <sndfile.h>
#include "Logger.h"
#include "WavPlayer.h"

WavPlayer::WavPlayer()
		: m_pcm(NULL), m_data(NULL), m_thread(-1), m_playing(false), m_count(0)
{
	// TODO Auto-generated constructor stub
}

WavPlayer::~WavPlayer()
{
	// TODO Auto-generated destructor stub
}

bool WavPlayer::load(const char* wavFile)
{
	GCHECK_RETFALSE(m_pcm==NULL);
	GCHECK_RETFALSE(snd_pcm_open(&m_pcm, "default", SND_PCM_STREAM_PLAYBACK, 0) >= 0);

	SF_INFO info;
	SNDFILE* file = sf_open(wavFile, SFM_READ, &info);
	GCHECK_RETFALSE(file);
	GCHECK_RETFALSE((info.format & SF_FORMAT_WAV) == SF_FORMAT_WAV);

	snd_pcm_hw_params_t* params;
	GCHECK_RETFALSE(snd_pcm_hw_params_malloc(&params) >= 0);
	GCHECK_RETFALSE(snd_pcm_hw_params_any(m_pcm, params) >= 0);
	GCHECK_RETFALSE(snd_pcm_hw_params_set_access(m_pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED) >= 0);
	GCHECK_RETFALSE(snd_pcm_hw_params_set_format(m_pcm, params, SND_PCM_FORMAT_S16_LE) >= 0);
	GCHECK_RETFALSE(snd_pcm_hw_params_set_channels(m_pcm, params, info.channels) >= 0);
	unsigned int rate = info.samplerate;
	GCHECK_RETFALSE(snd_pcm_hw_params_set_rate_near(m_pcm, params, &rate, NULL)>=0);
	GCHECK_RETFALSE(snd_pcm_hw_params(m_pcm, params) >= 0);

	snd_pcm_uframes_t frames;
	GCHECK_RETFALSE(snd_pcm_hw_params_get_period_size(params, &frames, NULL)>=0);

	snd_pcm_hw_params_free(params);

	DATA** data = &m_data;
	size_t bufferSize = frames * info.channels * sizeof(short);
	short* buffer = (short*) malloc(bufferSize);
	sf_count_t readFrames = sf_readf_short(file, buffer, frames);
	while (readFrames > 0)
	{
		*data = new DATA(buffer, bufferSize, readFrames);
		data = &((*data)->next);

		readFrames = sf_readf_short(file, buffer, frames);
	}

	free(buffer);
	sf_close(file);

	strcpy(m_wavFile, wavFile);
	GCHECK_RETFALSE(pthread_mutex_init(&m_threadMutex, NULL)==0);
	GCHECK_RETFALSE(pthread_cond_init(&m_threadCond, NULL)==0);
	GCHECK_RETFALSE(pthread_create(&m_thread, NULL, worker, this)==0);

	return true;
}

void WavPlayer::close()
{
	DATA* data = m_data;
	m_data = NULL;
	while (data)
	{
		DATA* next = data->next;
		delete data;
		data = next;
	}

	if (m_pcm)
	{
		snd_pcm_drain(m_pcm);
		snd_pcm_close(m_pcm);
		m_pcm = NULL;
	}

	if (m_thread != (pthread_t) -1)
	{
		if (pthread_cancel(m_thread) == 0)
		{
			pthread_join(m_thread, NULL);
		}
		GLOG("[%s]cancel WavPlayer thread", m_wavFile);
	}
}

void WavPlayer::play(int count)
{
	m_playing = true;
	m_count = count;
	pthread_mutex_lock(&m_threadMutex);
	pthread_cond_signal(&m_threadCond);
	pthread_mutex_unlock(&m_threadMutex);
}

void WavPlayer::stop()
{
	m_playing = false;
	m_count = 0;
}

void WavPlayer::work()
{
	for (;;)
	{
		pthread_mutex_lock(&m_threadMutex);
		pthread_cond_wait(&m_threadCond, &m_threadMutex);
		pthread_mutex_unlock(&m_threadMutex);

		if (m_pcm)
		{
			for (int i = 0; i < m_count || m_count == LOOPING; ++i)
			{
				snd_pcm_sframes_t writeFrames;
				DATA* data = m_data;
				while (m_playing && data)
				{
					writeFrames = snd_pcm_writei(m_pcm, data->buffer, data->frames);
					if (writeFrames == -EPIPE)
					{
						GLOG("Underrun");
						snd_pcm_prepare(m_pcm);
					}
					else if (writeFrames < 0)
					{
						GLOG("error writing to PCM device. (%s)", snd_strerror(writeFrames));
					}
					else if (writeFrames != (snd_pcm_sframes_t) data->frames)
					{
						GLOG("write differs from read. (%s)");
					}

					data = data->next;
				}
			}
		}
	}
}

void* WavPlayer::worker(void* param)
{
	WavPlayer* wavPlayer = (WavPlayer*)param;
	GLOG("[%s]start WavPlayer thread.", wavPlayer->m_wavFile);
	wavPlayer->work();
	GLOG("[%s]stop WavPlayer thread.", wavPlayer->m_wavFile);

	return NULL;
}
