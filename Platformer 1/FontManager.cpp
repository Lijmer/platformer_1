#include "FontManager.h"


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
}


void FontManager::init()
{
	al_init_font_addon();
	al_init_ttf_addon();
	nokiafc22_18 = al_load_font("fonts/nokiafc22.ttf", 18, 0);
}

void FontManager::clean()
{
	al_destroy_font(nokiafc22_18);
}

ALLEGRO_FONT* FontManager::getFont(char ID)
{
	switch(ID)
	{
	case 0:
		return nokiafc22_18;
		break;
	}
	return NULL;
}