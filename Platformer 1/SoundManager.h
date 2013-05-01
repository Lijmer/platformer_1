#pragma once
#include "globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
class SoundManager
{
public:
	~SoundManager(void);
	static SoundManager &GetInstance();

	void Init();
	void Play(int num);


private:
	SoundManager(void);
	SoundManager(SoundManager const&);
	
	ALLEGRO_SAMPLE *snd_shoot;
	ALLEGRO_SAMPLE *snd_jump1;
	ALLEGRO_SAMPLE *snd_jump2;
	ALLEGRO_SAMPLE *snd_splat;

	ALLEGRO_SAMPLE *music_level1;
	double diffclock(clock_t clock1, clock_t clock2)
	{
		double diffticks = clock1 - clock2;
		double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
		return diffms;
	}

};

