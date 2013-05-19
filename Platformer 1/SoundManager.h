#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
class SoundManager
{
public:
	
	SoundManager(void);
	~SoundManager(void);
	static SoundManager &GetInstance();

	void LoadSounds(int levelNum);

	void Init();
	void Play(int num);

private:
	void DestroyAllSounds();


	ALLEGRO_SAMPLE *snd_shoot;
	ALLEGRO_SAMPLE *snd_jump1;
	ALLEGRO_SAMPLE *snd_jump2;
	ALLEGRO_SAMPLE *snd_splat;

};

