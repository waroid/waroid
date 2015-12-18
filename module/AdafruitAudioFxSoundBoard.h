/*
 * AdafruitAudioFxSoundBoard.h
 *
 *  Created on: Dec 18, 2015
 *      Author: mirime
 */

#ifndef ADAFRUITAUDIOFXSOUNDBOARD_H_
#define ADAFRUITAUDIOFXSOUNDBOARD_H_

#include <pthread.h>
#include "IModule.h"

class AdafruitAudioFxSoundBoard: public IModule
{
public:
	AdafruitAudioFxSoundBoard();
	virtual ~AdafruitAudioFxSoundBoard();

public:
	virtual const char* getDescription() const;
	virtual bool open();
	virtual void close();
	virtual void init();

	void play(int track);
	void volumeUp();
	void volumeDown();

protected:
	void loop();

protected:
	int m_fd;
	pthread_t m_thread;

protected:
	static void* worker(void* param);

};

#endif /* ADAFRUITAUDIOFXSOUNDBOARD_H_ */
