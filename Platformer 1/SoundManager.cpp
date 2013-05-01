#include "SoundManager.h"

SoundManager &SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
	al_destroy_sample(snd_shoot);
	al_destroy_sample(snd_jump1);
	al_destroy_sample(snd_jump2);
	al_destroy_sample(snd_splat);
	//al_destroy_sample(music_level1);
}

void SoundManager::Init()
{
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(4);
	SoundManager::snd_shoot = al_load_sample("snd/player/shoot.wav");
	SoundManager::snd_jump1 = al_load_sample("snd/player/jump1.wav");
	SoundManager::snd_jump2 = al_load_sample("snd/player/jump2.wav");
	SoundManager::snd_splat = al_load_sample("snd/player/splat.wav");
	//SoundManager::music_level1 = al_load_sample("snd/music/level1.ogg");
}

void SoundManager::Play(int num)
{
	if(num == SHOOT)
	al_play_sample(snd_shoot,1,0,1,ALLEGRO_PLAYMODE_ONCE,0); 
	else if(num==JUMP1)
		al_play_sample(snd_jump1,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
	else if(num==JUMP2)
		al_play_sample(snd_jump2,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
	else if(num==SPLAT)
		al_play_sample(snd_splat,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
	//else if(num==50)
	//	al_play_sample(music_level1,.5,0,1,ALLEGRO_PLAYMODE_LOOP,0);
}