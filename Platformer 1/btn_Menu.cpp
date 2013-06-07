#include "btn_Menu.h"
#include "ButtonManager.h"
#include "FontManager.h"
#include "ImageManager.h"
#include "DisplayManager.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "FileManager.h"
#include "globals.h"

#include <sstream>

#include "Exit.h"

btn_Menu::btn_Menu(void)
{
	x=0;
	y=0;
	kind=0;
	boundUp=32, boundDown=32, boundLeft=128, boundRight=128;
	selected=false;
	alive = true;
	image=ImageManager::GetInstance().GetImage(-2);
}
btn_Menu::~btn_Menu(void)
{
}

void btn_Menu::Update(void)
{

}

void btn_Menu::Draw(void)
{
	int fontHeight = FontManager::GetInstance().GetFont(0)->height;
	if(!selected)
		al_draw_bitmap_region(image, 0, 0, 256, 64, x-boundLeft, y-boundUp,0);
	else
		al_draw_bitmap_region(image, 0, 64, 256, 64, x-boundLeft, y-boundUp,0);

	if(kind==NEW_GAME)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "New Game");
	}
	if(kind == NEW_GAME1)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Save Game 1");
	}
	if(kind == NEW_GAME2)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Save Game 2");
	}
	if(kind == NEW_GAME3)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Save Game 3");
	}
	else if(kind==LOAD_GAME)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Load Game");
	}
	if(kind == LOAD_GAME1)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Save Game 1");
	}
	if(kind == LOAD_GAME2)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Save Game 2");
	}
	if(kind == LOAD_GAME3)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Save Game 3");
	}
	else if(kind==HELP)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f),ALLEGRO_ALIGN_CENTRE, 2, "Help");
	}
	else if(kind==SETTINGS)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, "Settings");
	}
	else if(kind==TOGGLE_MUSIC)
	{
		std::stringstream ss;
		ss << "Music: ";
		if(SoundManager::GetInstance().GetMusicEnabled())
			ss << "On";
		else
			ss << "Off";
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, ss.str().c_str());
	}
	else if(kind==MUSIC_VOLUME)
	{
		std::stringstream ss;
		ss << "Music Volume: " << (SoundManager::GetInstance().GetMusicVolume()*100);
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, ss.str().c_str());
	}
	else if(kind==TOGGLE_SOUND)
	{
		std::stringstream ss;
		ss << "Sound: ";
		if(SoundManager::GetInstance().GetSoundEnabled())
			ss << "On";
		else
			ss << "Off";
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, ss.str().c_str());
	}
	else if(kind==SOUND_VOLUME)
	{
		std::stringstream ss;
		ss << "Sound Volume: " << (SoundManager::GetInstance().GetSoundVolume()*100);
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, ss.str().c_str());
	}
	else if(kind==TOGGLE_FULLSCREEN)
	{
		std::stringstream ss;
		ss << "FullScreen: ";
		if(DisplayManager::GetInstance().GetState()==DisplayManager::WINDOWED)
			ss << "Off";
		else
			ss << "On";
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, ss.str().c_str());
	}
	else if(kind==TOGGLE_DROP_FRAMES)
	{
		std::stringstream ss;
		ss << "Drop Frames: ";
		if(GetDropFrames())
			ss << "On";
		else
			ss << "Off";
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, ss.str().c_str());
	}
	else if(kind==EXIT)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, "Exit");
	}
	else if(kind==BACK)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, "Back");
	}
}

void btn_Menu::Init(float x, float y, int kind)
{
	btn_Menu::x = x;
	btn_Menu::y = y;
	btn_Menu::kind = kind;
}

void btn_Menu::Execute(void)
{
	if(kind==NEW_GAME)
	{
		ButtonManager::GetInstance().LoadNewGameMenu();
	}
	else if(kind==NEW_GAME1)
	{
		ButtonManager::GetInstance().DestroyButtons();
		//set save num
		//save
		LevelManager::GetInstance().ChangeLevel(LevelManager::LVL_LEVEL1);
	}
	else if(kind==NEW_GAME2)
	{
		ButtonManager::GetInstance().DestroyButtons();
		//set save num
		//save
		LevelManager::GetInstance().ChangeLevel(LevelManager::LVL_LEVEL1);
	}
	else if(kind==NEW_GAME3)
	{
		ButtonManager::GetInstance().DestroyButtons();
		//set save num
		//save
		LevelManager::GetInstance().ChangeLevel(LevelManager::LVL_LEVEL1);
	}
	else if(kind==LOAD_GAME)
	{
		ButtonManager::GetInstance().LoadLoadGameMenu();
	}
	else if(kind==LOAD_GAME1)
	{
		ButtonManager::GetInstance().DestroyButtons();
		//set save num
		//load (this includes going to the loaded level
	}
	else if(kind==LOAD_GAME2)
	{
		ButtonManager::GetInstance().DestroyButtons();
		//set save num
		//load (this includes going to the loaded level
	}
	else if(kind==LOAD_GAME3)
	{
		ButtonManager::GetInstance().DestroyButtons();
		//set save num
		//load (this includes going to the loaded level
	}
	else if(kind==HELP)
	{
		ButtonManager::GetInstance().LoadHelpMenu();
	}
	else if(kind==SETTINGS)
	{
		ButtonManager::GetInstance().LoadSettingsMenu();
	}
	else if(kind==TOGGLE_MUSIC)
	{
		SoundManager::GetInstance().ToggleMusic();
		FileManager::GetInstance().SaveSettings();
	}
	else if(kind==MUSIC_VOLUME)
	{
		SoundManager::GetInstance().ChangeMusicVolume();
		FileManager::GetInstance().SaveSettings();
	}
	else if(kind==TOGGLE_SOUND)
	{
		SoundManager::GetInstance().ToggleSound();
		FileManager::GetInstance().SaveSettings();
	}
	else if(kind==SOUND_VOLUME)
	{
		SoundManager::GetInstance().ChangeSoundVolume();
		FileManager::GetInstance().SaveSettings();
	}
	else if(kind==TOGGLE_FULLSCREEN)
	{
		DisplayManager::GetInstance().ChangeState();
		FileManager::GetInstance().SaveSettings();
	}
	else if(kind==TOGGLE_DROP_FRAMES)
	{
		ToggleDropFrames();
		FileManager::GetInstance().SaveSettings();
	}
	else if(kind==EXIT)
	{
		Exit::ExitProgram();
	}
	else if(kind==BACK)
	{
		ButtonManager::GetInstance().PreviousMenu();
	}
}

bool btn_Menu::CheckMouseCollision(void)
{
	if(_mouseX > x-boundLeft && _mouseX < x+boundRight &&
		_mouseY > y-boundUp && _mouseY > y+boundDown)
		return true;
	else
		return false;
}

inline void btn_Menu::DrawTextOutline(ALLEGRO_FONT *font, ALLEGRO_COLOR innerColor,
	ALLEGRO_COLOR outerColor, float x, float y, int flags,int radius, const char* text)
{
	al_draw_text(font, outerColor, x-radius, y-radius, flags, text);
	al_draw_text(font, outerColor, x, y-radius, flags, text);
	al_draw_text(font, outerColor, x+radius, y-radius, flags, text);
	al_draw_text(font, outerColor, x-radius, y, flags, text);
	al_draw_text(font, outerColor, x, y, flags, text);
	al_draw_text(font, outerColor, x+radius, y, flags, text);
	al_draw_text(font, outerColor, x-radius, y+radius, flags, text);
	al_draw_text(font, outerColor, x, y+radius, flags, text);
	al_draw_text(font, outerColor, x+radius, y+radius, flags, text);
	
	al_draw_text(font, innerColor, x,y,flags,text);

}