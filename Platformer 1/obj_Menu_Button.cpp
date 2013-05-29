#include "obj_Menu_Button.h"
#include "ImageManager.h"
#include "GameObjectManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "DisplayManager.h"
#include "LevelManager.h"
#include "globals.h"
#include <sstream>
#include "Exit.h"
#include <iostream>
int obj_Menu_Button::numButtons=0;
int obj_Menu_Button::selectedButton=0;

obj_Menu_Button::obj_Menu_Button(void)
{
	x=0;
	y=0;
	kind=0;

	boundUp=32;
	boundDown=32;
	boundLeft=128;
	boundRight=128;
	
	image = ImageManager::GetInstance().GetImage(-2);
	buttonID = numButtons;
	std::cout << buttonID;
	selectedButton=0;
	numButtons++;
	selected=false;
	alive = true;
}


obj_Menu_Button::~obj_Menu_Button(void)
{
}

void obj_Menu_Button::Init(float x, float y, int kind)
{
	obj_Menu_Button::x = x;
	obj_Menu_Button::y = y;
	obj_Menu_Button::kind = kind;
}

void obj_Menu_Button::Update()
{
	if(_mouseX >  x-boundLeft && _mouseX < x+boundRight &&
		_mouseY > y-boundUp && _mouseY < y+boundDown)
	{
		selectedButton=buttonID;
	}
	if(selectedButton == buttonID)
		selected=true;
	else
		selected=false;
}
void obj_Menu_Button::Click()
{
	if(_mouseX >  x-boundLeft && _mouseX < x+boundRight &&
		_mouseY > y-boundUp && _mouseY < y+boundDown)
	{
		if(_mouse_pressed[M_LEFT])
			Execute();
	}
}

void obj_Menu_Button::NextButton()
{
	if(++selectedButton>numButtons-1)
		selectedButton=0;
}
void obj_Menu_Button::PreviousButton()
{
	if(--selectedButton<0)
		selectedButton=numButtons-1;
}

void obj_Menu_Button::Execute()
{
	if(kind==NEW_GAME)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		GameObjectManager::GetInstance().CreateButton(512,128,NEW_GAME1);
		GameObjectManager::GetInstance().CreateButton(512,208,NEW_GAME2);
		GameObjectManager::GetInstance().CreateButton(512,288,NEW_GAME3);
		GameObjectManager::GetInstance().CreateButton(512,640,BACK);
	}
	else if(kind==NEW_GAME1)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		//set save num
		//save
		LevelManager::GetInstance().ChangeLevel(LevelManager::LVL_LEVEL1);
	}
	else if(kind==NEW_GAME2)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		//set save num
		//save
		LevelManager::GetInstance().ChangeLevel(LevelManager::LVL_LEVEL1);
	}
	else if(kind==NEW_GAME3)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		//set save num
		//save
		LevelManager::GetInstance().ChangeLevel(LevelManager::LVL_LEVEL1);
	}
	else if(kind==LOAD_GAME)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		GameObjectManager::GetInstance().CreateButton(512,128,LOAD_GAME1);
		GameObjectManager::GetInstance().CreateButton(512,208,LOAD_GAME2);
		GameObjectManager::GetInstance().CreateButton(512,288,LOAD_GAME3);
		GameObjectManager::GetInstance().CreateButton(512,640,BACK);
	}
	else if(kind==LOAD_GAME1)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		//set save num
		//load (this includes going to the loaded level
	}
	else if(kind==LOAD_GAME2)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		//set save num
		//load (this includes going to the loaded level
	}
	else if(kind==LOAD_GAME3)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		//set save num
		//load (this includes going to the loaded level
	}
	else if(kind==HELP)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		GameObjectManager::GetInstance().CreateObjectHelpText(512,128);
		GameObjectManager::GetInstance().CreateButton(512,640,BACK);
	}
	else if(kind==OPTIONS)
	{
		GameObjectManager::GetInstance().SetButtonsAliveFalse();
		GameObjectManager::GetInstance().CreateButton(512,128,TOGGLE_MUSIC);
		GameObjectManager::GetInstance().CreateButton(512,208,MUSIC_VOLUME);
		GameObjectManager::GetInstance().CreateButton(512,288,TOGGLE_SOUND);
		GameObjectManager::GetInstance().CreateButton(512,368,SOUND_VOLUME);
		GameObjectManager::GetInstance().CreateButton(512,448,TOGGLE_FULLSCREEN);
		GameObjectManager::GetInstance().CreateButton(512,640,BACK);
	}
	else if(kind==TOGGLE_MUSIC)
	{
		SoundManager::GetInstance().ToggleMusic();
	}
	else if(kind==MUSIC_VOLUME)
	{
		SoundManager::GetInstance().ChangeMusicVolume();
	}
	else if(kind==TOGGLE_SOUND)
	{
		SoundManager::GetInstance().ToggleSound();
	}
	else if(kind==SOUND_VOLUME)
	{
		SoundManager::GetInstance().ChangeSoundVolume();
	}
	else if(kind==TOGGLE_FULLSCREEN)
	{
		DisplayManager::GetInstance().ChangeState();
	}
	else if(kind==EXIT)
	{
		Exit::ExitProgram();
	}
	else if(kind==BACK)
	{
		ExecuteBack();
	}
	SoundManager::GetInstance().Play(SoundManager::CLICK);
}

void obj_Menu_Button::ExecuteBack()
{
	GameObjectManager::GetInstance().DeleteObjHelpText();
	GameObjectManager::GetInstance().SetButtonsAliveFalse();
	GameObjectManager::GetInstance().CreateButton(512,128,NEW_GAME);
	GameObjectManager::GetInstance().CreateButton(512,208,LOAD_GAME);
	GameObjectManager::GetInstance().CreateButton(512,288,HELP);
	GameObjectManager::GetInstance().CreateButton(512,368,OPTIONS);
	GameObjectManager::GetInstance().CreateButton(512,448,EXIT);
}

void obj_Menu_Button::Draw()
{
	int fontHeight = FontManager::GetInstance().GetFont(0)->height;
	if(!selected)
		al_draw_bitmap_region(image, 0, 0, 256, 64, x-boundLeft-_camX, y-boundUp-_camY,0);
	else
		al_draw_bitmap_region(image, 0, 64, 256, 64, x-boundLeft-_camX, y-boundUp-_camY,0);

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
	else if(kind==OPTIONS)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x, y-(fontHeight/2.0f), ALLEGRO_ALIGN_CENTRE, 2, "Options");
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

inline void obj_Menu_Button::DrawTextOutline(ALLEGRO_FONT *font, ALLEGRO_COLOR innerColor,
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