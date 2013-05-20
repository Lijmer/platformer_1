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
	void LoadMusic(int levelNum);
		
	void Update();
	void Pause();
	void ChangeMusicVolume();
	void ChangeSoundVolume();
	void ToggleMusic()
		{if(musicEnabled){musicEnabled=false;} else {musicEnabled=true;}}
	void ToggleSound()
		{if(soundEnabled){soundEnabled=false;} else {soundEnabled=true;}}

	void Play(int num);
	void PlayMusic(int num, bool loop);

private:
	void DestroyAllSounds();
	void DestroyMusic();
	void DestroyMixer();
	void DestroyVoice();

	ALLEGRO_VOICE *voice;
	ALLEGRO_MIXER *mixer;

	ALLEGRO_SAMPLE *snd_shoot;
	ALLEGRO_SAMPLE *snd_jump1;
	ALLEGRO_SAMPLE *snd_jump2;
	ALLEGRO_SAMPLE *snd_splat;

	ALLEGRO_AUDIO_STREAM *music;

	bool musicEnabled;
	bool soundEnabled;
	bool paused;

	float musicVolume;
	float soundVolume;

};

