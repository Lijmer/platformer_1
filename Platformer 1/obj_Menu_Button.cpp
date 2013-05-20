#include "obj_Menu_Button.h"
#include "ImageManager.h"
#include "GameObjectManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "globals.h"
#include "Exit.h"

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
	numButtons++;
	selected=false;
}


obj_Menu_Button::~obj_Menu_Button(void)
{
	numButtons--;
}

void obj_Menu_Button::Init(float x, float y, int kind)
{
	obj_Menu_Button::x = x;
	obj_Menu_Button::y = y;
	obj_Menu_Button::kind = kind;
}

void obj_Menu_Button::Update()
{
	
}

void obj_Menu_Button::Execute()
{
	if(kind==NEW_GAME)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		GameObjectManager::GetInstance().CreateButton(512,128,NEW_GAME1);
		GameObjectManager::GetInstance().CreateButton(512,256,NEW_GAME2);
		GameObjectManager::GetInstance().CreateButton(512,384,NEW_GAME3);
		GameObjectManager::GetInstance().CreateButton(512,640,BACK);
	}
	else if(kind==NEW_GAME1)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		//save
		//goto level 1
	}
	else if(kind==NEW_GAME2)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		//save
		//goto level 1
	}
	else if(kind==NEW_GAME3)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		//save
		//goto level 1
	}
	else if(kind==LOAD_GAME)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		GameObjectManager::GetInstance().CreateButton(512,128,LOAD_GAME1);
		GameObjectManager::GetInstance().CreateButton(512,192,LOAD_GAME2);
		GameObjectManager::GetInstance().CreateButton(512,256,LOAD_GAME3);
		GameObjectManager::GetInstance().CreateButton(512,640,BACK);
	}
	else if(kind==LOAD_GAME1)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		//load (this includes going to the loaded level
	}
	else if(kind==LOAD_GAME2)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		//load (this includes going to the loaded level
	}
	else if(kind==LOAD_GAME3)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		//load (this includes going to the loaded level
	}
	else if(kind==HELP)
	{
		GameObjectManager::GetInstance().DeleteButtons();
	}
	else if(kind==OPTIONS)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		GameObjectManager::GetInstance().CreateButton(512,128,TOGGLE_MUSIC);
		GameObjectManager::GetInstance().CreateButton(512,192,MUSIC_VOLUME);
		GameObjectManager::GetInstance().CreateButton(512,256,TOGGLE_SOUND);
		GameObjectManager::GetInstance().CreateButton(512,320,SOUND_VOLUME);
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
	else if(kind==EXIT)
	{
		Exit::ExitProgram();
	}
	else if(kind==BACK)
	{
		GameObjectManager::GetInstance().DeleteButtons();
		GameObjectManager::GetInstance().CreateButton(512,128,NEW_GAME);
		GameObjectManager::GetInstance().CreateButton(512,192,LOAD_GAME);
		GameObjectManager::GetInstance().CreateButton(512,256,HELP);
		GameObjectManager::GetInstance().CreateButton(512,320,OPTIONS);
		GameObjectManager::GetInstance().CreateButton(512,384,EXIT);
	}
}

void obj_Menu_Button::Draw()
{
	if(!selected)
		al_draw_bitmap_region(image, 0, 0, 256, 64, x-boundLeft-_camX, y-boundUp-_camY,0);
	else
		al_draw_bitmap_region(image, 0, 64, 256, 64, x-boundLeft-_camX, y-boundUp-_camY,0);

	if(kind==NEW_GAME)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y,ALLEGRO_ALIGN_CENTRE, 2, "New Game");
	}
	else if(kind==LOAD_GAME)
	{
		DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255),
			al_map_rgb(0,0,0), x,y,ALLEGRO_ALIGN_CENTRE, 2, "Load Game");
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