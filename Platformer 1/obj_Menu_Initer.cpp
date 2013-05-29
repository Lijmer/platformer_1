#include "obj_Menu_Initer.h"
#include "GameObjectManager.h"
#include "obj_Menu_Button.h"
obj_Menu_Initer::obj_Menu_Initer(void)
{
}

obj_Menu_Initer::~obj_Menu_Initer(void)
{
}

void obj_Menu_Initer::Init(void)
{
	GameObjectManager::GetInstance().CreateButton(512,128,obj_Menu_Button::NEW_GAME);
	GameObjectManager::GetInstance().CreateButton(512,208,obj_Menu_Button::LOAD_GAME);
	GameObjectManager::GetInstance().CreateButton(512,288,obj_Menu_Button::HELP);
	GameObjectManager::GetInstance().CreateButton(512,368,obj_Menu_Button::OPTIONS);
	GameObjectManager::GetInstance().CreateButton(512,448,obj_Menu_Button::EXIT);
	SetAlive(false);
}