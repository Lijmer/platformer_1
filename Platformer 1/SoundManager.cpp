#include "SoundManager.h"
#include "FileManager.h"
#include "DisplayManager.h"

#include <allegro5/allegro_native_dialog.h>

#include <vector>
#include <sstream>
#include "globals.h"

#include "Exit.h"

SoundManager &SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

SoundManager::SoundManager(void)
{
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(4);
	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	snd_click=NULL;
	snd_shoot=NULL;
	snd_jump1=NULL;
	snd_jump2=NULL;
	snd_splat=NULL;

	musicEnabled = true;
	soundEnabled = true;
	paused=false;

	musicVolume = 1.0f;
	soundVolume = 1.0f;
}
SoundManager::~SoundManager(void)
{
	DestroyAllSounds();
	DestroyMusic();
	DestroyMixer();
	DestroyVoice();
	al_uninstall_audio();
}

void SoundManager::Update()
{
	if(music==NULL)
		return;
	if(musicEnabled && !paused)
		al_set_audio_stream_playing(music, true);
	else if(!musicEnabled || paused)
		al_set_audio_stream_playing(music, false);
	al_set_audio_stream_gain(music, musicVolume);
}

void SoundManager::Pause()
{
	if(paused)
		paused=false;
	if(!paused)
		paused=true;
}
void SoundManager::ChangeMusicVolume()
{
	musicVolume+=0.1;
	if(musicVolume>=1.1)
		musicVolume=0;
}
void SoundManager::ChangeSoundVolume()
{
	soundVolume+=0.1;
	if(soundVolume>=1.1)
		soundVolume=0;
}

void SoundManager::Play(int num)
{
	if(!soundEnabled)
		return;
	try
	{
		if(num == CLICK)
		{
			if(snd_click!=NULL)
				al_play_sample(snd_click,soundVolume,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_click";
		}
		else if(num == SHOOT)
		{
			if(snd_shoot!=NULL)
				al_play_sample(snd_shoot,soundVolume,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_shoot";
		}
		else if(num==JUMP1)
		{
			if(snd_jump1!=NULL)
				al_play_sample(snd_jump1,soundVolume,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_jump1";
		}
		else if(num==JUMP2)
		{
			if(snd_jump2!=NULL)
				al_play_sample(snd_jump2,soundVolume,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_jump2";
		}
		else if(num==SPLAT)
		{
			if(snd_splat!=NULL)
				al_play_sample(snd_splat,soundVolume,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_splat";
		}
		else
			throw 0;
	}
	catch(char const* error)
	{
		std::stringstream ss;
		ss << error << " isn't loaded, please add the corresponding number in the sounds section of the level file";
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "SoundManager", ss.str().c_str(), "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}
	catch(int errorNum)
	{
		if(errorNum==0)
		{
			al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "SoundManager", "Unknown sound ID", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		}
		else
		{
			std::stringstream ss;
			ss << "Unknown error: " << errorNum;
			al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "SoundManager", ss.str().c_str(), "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		}
	}
}

void SoundManager::PlayMusic(int num, bool loop)
{
	DestroyMusic();
	if(num==-1)
		return;
	else if(num==0)
		music = al_load_audio_stream("music/menu.ogg", 4, 2048);
	else if(num==1)
		music = al_load_audio_stream("music/level1.ogg", 4, 2048);

	if(music==NULL)
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "SoundManager", "Couldn't load music", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	if(music==NULL)
		return;

	al_set_audio_stream_loop_secs(music, .0f, al_get_audio_stream_length_secs(music));
	if(loop)
		al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
	else
		al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_ONCE);
	al_attach_audio_stream_to_mixer(music, mixer);
	al_attach_mixer_to_voice(mixer,voice);

}

void SoundManager::LoadSounds(int levelNum)
{
	DestroyAllSounds();
	std::vector<int> soundNums = FileManager::GetInstance().LoadSoundNums(levelNum);
	std::vector<int>::iterator iter;

	for(iter = soundNums.begin(); iter!= soundNums.end(); iter++)
	{
		try
		{
			switch(*iter)
			{
			case -2:
				SoundManager::snd_click = al_load_sample("snd/click.wav");
				if(!snd_click)
					throw "snd_click";
				break;
			case 0:
				SoundManager::snd_shoot = al_load_sample("snd/player/shoot.wav");
				if(!snd_shoot)
					throw "snd_shoot";
				break;
			case 1:
				SoundManager::snd_jump1 = al_load_sample("snd/player/jump1.wav");
				if(!snd_jump1)
					throw "snd_jump1";
				break;
			case 2:
				SoundManager::snd_jump2 = al_load_sample("snd/player/jump2.wav");
				if(!snd_jump2)
					throw "snd_jump2";
				break;
			case 3:
				SoundManager::snd_splat = al_load_sample("snd/player/splat.wav");
				if(!snd_splat)
					throw "snd_splat";
				break;
			}
		}
		catch(char const* error)
		{
			std::stringstream ss;
			ss << "Coudn't open " << error;
			al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
				"Error!", "SoundManager", ss.str().c_str(),"Ok", ALLEGRO_MESSAGEBOX_ERROR);
			Exit::ExitProgram(-11);
		}
	}
}

//Private
inline void SoundManager::DestroyAllSounds()
{
	if(snd_shoot)
		al_destroy_sample(snd_shoot);
	if(snd_jump1)
		al_destroy_sample(snd_jump1);
	if(snd_jump2)
		al_destroy_sample(snd_jump2);
	if(snd_splat)
		al_destroy_sample(snd_splat);
}
inline void SoundManager::DestroyMusic()
{
	if(music!=NULL)
	{
		al_detach_audio_stream(music);
		al_destroy_audio_stream(music);
	}
}
inline void SoundManager::DestroyMixer()
{
	if(mixer!=NULL)
	{
		al_detach_mixer(mixer);
		al_destroy_mixer(mixer);
	}
}
inline void SoundManager::DestroyVoice()
{
	if(voice!=NULL)
	{
		al_detach_voice(voice);
		al_destroy_voice(voice);
	}
}