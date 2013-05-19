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
}

SoundManager::~SoundManager(void)
{
	DestroyAllSounds();
}

void SoundManager::Init()
{
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(4);
}

void SoundManager::Play(int num)
{
	try
	{
		if(num == SHOOT)
		{
			if(snd_shoot!=NULL)
				al_play_sample(snd_shoot,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_shoot";
		}
		else if(num==JUMP1)
		{
			if(snd_jump1!=NULL)
				al_play_sample(snd_jump1,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_jump1";
		}
		else if(num==JUMP2)
		{
			if(snd_jump2!=NULL)
				al_play_sample(snd_jump2,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
			else
				throw "snd_jump2";
		}
		else if(num==SPLAT)
		{
			if(snd_splat!=NULL)
				al_play_sample(snd_splat,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
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