#pragma once
#include "globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
class SoundManager
{
public:
	~SoundManager(void);
	static SoundManager &GetInstance();

	void Init();
	void Clean();
	void Play(int num);

	

private:
	SoundManager(void);
	SoundManager(SoundManager const&);
	
	ALLEGRO_SAMPLE *snd_shoot;
	ALLEGRO_SAMPLE *snd_jump1;
	ALLEGRO_SAMPLE *snd_jump2;
	ALLEGRO_SAMPLE *snd_splat;

	ALLEGRO_SAMPLE *music_level1;
};

