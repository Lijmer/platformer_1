#pragma region Includes
#include "LevelManager.h"
#include <allegro5/allegro_native_dialog.h>
#include "GameObjectManager.h"
#include "FileManager.h"
#include "DisplayManager.h"
#include "ImageManager.h"
#include "SoundManager.h"

#include <sstream>
#pragma endregion

//Public
LevelManager::LevelManager(void)
{
	currentLevel=-1;
	saveNum=-1;
}
LevelManager::~LevelManager(void)
{
}

void LevelManager::Init(void)
{
	currentLevel=LVL_LEVEL1;
	saveNum=0;
	LoadLevel(currentLevel);
}

void LevelManager::Save()
{
	FileManager::GetInstance().Save(saveNum);
}

void LevelManager::NextLevel()
{
	if(++currentLevel>=LVL_SIZE)
	{
		std::stringstream ss;
		ss << "There is no level " << currentLevel;
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "LevelManager", ss.str().c_str(), "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		currentLevel=LVL_SIZE-1;
		return;
	}
	LoadLevel(currentLevel);
}
void LevelManager::PreviousLevel()
{
	if(--currentLevel<LVL_MENU)
	{
		std::stringstream ss;
		ss << "There is no level " << currentLevel;
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "LevelManager", ss.str().c_str(), "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		currentLevel=LVL_MENU;
		return;
	}
	LoadLevel(currentLevel);
}
void LevelManager::RestartLevel()
{
	ReloadLevel();
}
void LevelManager::ChangeLevel(int level)
{
	if(level<LVL_MENU || level>=LVL_SIZE)
	{
		std::stringstream ss;
		ss << "There is no level " << level;
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "LevelManager", ss.str().c_str(), "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}
	if(currentLevel==level)
	{
		GameObjectManager::GetInstance().DeleteParticles();
		ReloadLevel();
	}
	else
	{
		currentLevel=level;
		LoadLevel(currentLevel);
	}
}

//Private
inline void LevelManager::LoadLevel(int level)
{
	LoadImages(level);
	LoadSounds(level);
	GameObjectManager::GetInstance().DeleteAllObjects();
	FileManager::GetInstance().LoadStaticObjects(level);
	FileManager::GetInstance().LoadDynamicObjects(level);
}

inline void LevelManager::ReloadLevel()
{
	GameObjectManager::GetInstance().DeleteDynamicObjects();
	FileManager::GetInstance().LoadDynamicObjects(currentLevel);
	if(currentLevel!=LVL_MENU)
		FileManager::GetInstance().Load(saveNum);
}

inline void LevelManager::LoadImages(int level)
{
	ImageManager::GetInstance().LoadImages(level);
}
inline void LevelManager::LoadSounds(int level)
{
	SoundManager::GetInstance().LoadSounds(level);
}

inline void LevelManager::DeleteDynamicObjects()
{
	GameObjectManager::GetInstance().DeleteDynamicObjects();
}
inline void LevelManager::DeleteStaticObjects()
{
	GameObjectManager::GetInstance().DeleteStaticObjects();
}
inline void LevelManager::DeleteParticles()
{
	GameObjectManager::GetInstance().DeleteParticles();
}
inline void LevelManager::DeleteAllObjects()
{
	DeleteDynamicObjects();
	DeleteStaticObjects();
	DeleteParticles();
}