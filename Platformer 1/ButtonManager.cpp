#include "ButtonManager.h"
#include <allegro5/allegro_native_dialog.h>
#include "DisplayManager.h"
#include "globals.h"
#include "btn_Menu.h"
#include "SoundManager.h"
#include "obj_Help_Text.h"
#include "Transformer.h"
using namespace Transformer;

#include <iostream>

ButtonManager::ButtonManager(void)
{
	selectedButton=0;
	//numButtons=0;
	btn_menu = NULL;
	obj_help_text = NULL;
	currentMenu=MAIN_MENU;

}
ButtonManager::~ButtonManager(void)
{
	DestroyButtons();
	Clean();
}
void ButtonManager::Init()
{
	mainCanvas = al_create_bitmap(_SCREEN_WIDTH, _SCREEN_HEIGHT);
}
void ButtonManager::TimerEvent(void)
{
	Update();
	Clean();
}
void ButtonManager::Draw(void)
{
	al_set_target_bitmap(mainCanvas);
	al_clear_to_color(al_map_rgba(0,0,0,0));
	std::vector<btn_Menu*>::iterator iter;
	for(iter = buttons.begin(); iter!=buttons.end(); iter++)
	{
		(*iter)->Draw();
	}
	std::vector<obj_Help_Text*>::iterator iter2;
	for(iter2 = helpTexts.begin(); iter2!=helpTexts.end(); iter2++)
	{
		(*iter2)->Draw();
	}
	al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
	al_draw_scaled_bitmap(mainCanvas, 0,0,_SCREEN_WIDTH,_SCREEN_HEIGHT,
		TranslateDisplayX(0), TranslateDisplayY(0), ScaleDisplay(_SCREEN_WIDTH), ScaleDisplay(_SCREEN_HEIGHT),0);
}
void ButtonManager::CreateButton(float x, float y, int kind)
{
	btn_menu = new btn_Menu;
	btn_menu->Init(x,y,kind);
	pendingButtons.push_back(btn_menu);
	btn_menu = NULL;
}
void ButtonManager::CreateHelpText(float x, float y)
{
	obj_help_text = new obj_Help_Text;
	obj_help_text->Init(x,y);
	helpTexts.push_back(obj_help_text);
	obj_help_text = NULL;
}
void ButtonManager::DestroyButtons(void)
{
	std::vector<btn_Menu*>::iterator iter;
	for(iter = buttons.begin(); iter!=buttons.end();)
	{
		(*iter)->SetAlive(false);
		destroyedButtons.push_back(*iter);
		iter = buttons.erase(iter);
	}
	selectedButton=0;
}
void ButtonManager::DestroyHelpText(void)
{
	std::vector<obj_Help_Text *>::iterator iter;
	for(iter = helpTexts.begin(); iter!=helpTexts.end();)
	{
		delete (*iter);
		iter = helpTexts.erase(iter);
	}
}

void ButtonManager::LoadNewGameMenu()
{
	currentMenu=NEW_GAME_MENU;
	DestroyButtons();
	CreateButton(512,128,btn_Menu::NEW_GAME1);
	CreateButton(512,208,btn_Menu::NEW_GAME2);
	CreateButton(512,288,btn_Menu::NEW_GAME3);
	CreateButton(512,640,btn_Menu::BACK);
}
void ButtonManager::LoadNewGame1Menu()
{
	//Set Save Num
	currentMenu=NEW_GAME1_MENU;
	DestroyButtons();
	CreateButton(512,128,btn_Menu::DIFFICULTY);
	CreateButton(512,208,btn_Menu::START);
	CreateButton(512,288,btn_Menu::BACK);
}
void ButtonManager::LoadNewGame2Menu()
{
	//Set Save num
	currentMenu=NEW_GAME2_MENU;
	DestroyButtons();
	CreateButton(512,128,btn_Menu::DIFFICULTY);
	CreateButton(512,208,btn_Menu::START);
	CreateButton(512,288,btn_Menu::BACK);
}
void ButtonManager::LoadNewGame3Menu()
{
	//Set save num
	currentMenu=NEW_GAME3_MENU;
	DestroyButtons();
	CreateButton(512,128,btn_Menu::DIFFICULTY);
	CreateButton(512,208,btn_Menu::START);
	CreateButton(512,288,btn_Menu::BACK);
}
void ButtonManager::LoadLoadGameMenu()
{
	currentMenu=LOAD_GAME_MENU;
	DestroyButtons();
	CreateButton(512,128,btn_Menu::LOAD_GAME1);
	CreateButton(512,208,btn_Menu::LOAD_GAME2);
	CreateButton(512,288,btn_Menu::LOAD_GAME3);
	CreateButton(512,640,btn_Menu::BACK);
}
void ButtonManager::LoadLoadGame1Menu()
{
	currentMenu=LOAD_GAME1_MENU;
	DestroyButtons();
	//Set save num
	//Load save game and level
}
void ButtonManager::LoadLoadGame2Menu()
{
	currentMenu=LOAD_GAME2_MENU;
	DestroyButtons();
	//Set save num
	//Load save game and level
}
void ButtonManager::LoadLoadGame3Menu()
{
	currentMenu=LOAD_GAME3_MENU;
	DestroyButtons();
	//Set save num
	//Load save game and level
}
void ButtonManager::LoadHelpMenu()
{
	currentMenu=HELP_MENU;
	DestroyButtons();
	CreateHelpText(512,128);
	CreateButton(512,640,btn_Menu::BACK);
}
void ButtonManager::LoadOptionsMenu()
{
	currentMenu=OPTIONS_MENU;
	DestroyButtons();
	CreateButton(512,128,btn_Menu::TOGGLE_MUSIC);
	CreateButton(512,208,btn_Menu::MUSIC_VOLUME);
	CreateButton(512,288,btn_Menu::TOGGLE_SOUND);
	CreateButton(512,368,btn_Menu::SOUND_VOLUME);
	CreateButton(512,448,btn_Menu::TOGGLE_FULLSCREEN);
	CreateButton(512,528,btn_Menu::TOGGLE_DROP_FRAMES);
	CreateButton(512,640,btn_Menu::BACK);
}
void ButtonManager::LoadMainMenu()
{
	currentMenu=MAIN_MENU;
	DestroyHelpText();
	DestroyButtons();
	CreateButton(512,128,btn_Menu::NEW_GAME);
	CreateButton(512,208,btn_Menu::LOAD_GAME);
	CreateButton(512,288,btn_Menu::HELP);
	CreateButton(512,368,btn_Menu::OPTIONS);
	CreateButton(512,448,btn_Menu::EXIT);
}

void ButtonManager::PreviousMenu()
{
	if(currentMenu == NEW_GAME_MENU || currentMenu == NEW_GAME_MENU || currentMenu == LOAD_GAME_MENU
		|| currentMenu == HELP_MENU || currentMenu == OPTIONS_MENU)
	{
		LoadMainMenu();
	}
	else if(currentMenu == NEW_GAME1_MENU || currentMenu == NEW_GAME2_MENU || currentMenu == NEW_GAME3_MENU)
	{
		LoadNewGameMenu();
	}
	else if(currentMenu == LOAD_GAME1_MENU || currentMenu == LOAD_GAME2_MENU || currentMenu == LOAD_GAME3_MENU)
	{
		LoadLoadGameMenu();
	}
}

inline void ButtonManager::Update(void)
{
	std::vector<btn_Menu*>::iterator iter;
	for(iter = pendingButtons.begin(); iter!=pendingButtons.end(); )
	{
		buttons.push_back(*iter);
		iter = pendingButtons.erase(iter);
	}

	if(buttons.size()==0)
		return;
	
	for(iter = buttons.begin(); iter != buttons.end(); iter++)
	{
		(*iter)->SetSelected(false);
		(*iter)->SetSelected((*iter)->CheckMouseCollision());
	}

	if(_keys_pressed[UP])
		PreviousButton();
	else if(_keys_pressed[DOWN])
		NextButton();

	buttons[selectedButton]->SetSelected(true);

	if((_keys_pressed[ENTER] && !_keys[ALT]) || _keys_pressed[Z_KEY])
	{
		SoundManager::GetInstance().Play(SoundManager::CLICK);
		buttons[selectedButton]->Execute();
	}
	else if(_keys_pressed[X_KEY])
	{
		SoundManager::GetInstance().Play(SoundManager::CLICK);
		PreviousMenu();
	}
}
inline void ButtonManager::Clean(void)
{
	std::vector<btn_Menu*>::iterator iter;
	for(iter = buttons.begin(); iter != buttons.end(); )
	{
		//notice the !
		if(!(*iter)->GetAlive())
		{
			destroyedButtons.push_back(*iter);
			iter = buttons.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	for(iter = destroyedButtons.begin(); iter != destroyedButtons.end();)
	{
		delete (*iter);
		iter = destroyedButtons.erase(iter);
	}
	//buttons.shrink_to_fit();
}

inline void ButtonManager::NextButton(void)
{
	if(++selectedButton>=buttons.size())
	{
		selectedButton=0;
	}
}
inline void ButtonManager::PreviousButton(void)
{
	if(selectedButton==0)
	{
		selectedButton = buttons.size()-1;
	}
	else
		--selectedButton;
}