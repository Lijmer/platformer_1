#include "FontManager.h"
#include "DisplayManager.h"
#include <allegro5/allegro_native_dialog.h>


FontManager& FontManager::GetInstance()
{
	static FontManager instance;
	return instance;
}

FontManager::FontManager(void)
{
}


FontManager::~FontManager(void)
{
	al_destroy_font(nokiafc22_18);
}


void FontManager::Init()
{
	al_init_font_addon();
	al_init_ttf_addon();
	nokiafc22_18 = al_load_font("fonts/nokiafc22.ttf", 18, 0);
	if(nokiafc22_18 == NULL)
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),"Error!", "FontManager", "Couldn't load nokiafc22.tff", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
}

ALLEGRO_FONT* FontManager::GetFont(char ID)
{
	switch(ID)
	{
	case 0:
		return nokiafc22_18;
		break;
	}
	return NULL;
}