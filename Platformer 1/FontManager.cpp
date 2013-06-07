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
	al_init_font_addon();
	al_init_ttf_addon();
	nokiafc22_18 = al_load_font("fonts/nokiafc22.ttf", 18, 0);
	if(nokiafc22_18 == NULL)
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
		"Error!", "FontManager", "Couldn't load nokiafc22.tff", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
}


FontManager::~FontManager(void)
{
	al_destroy_font(nokiafc22_18);
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

void FontManager::DrawTextOutline(int fontID, ALLEGRO_COLOR innerColor,
	ALLEGRO_COLOR outerColor, float x, float y, int flags,int radius, const char* text)
{
	ALLEGRO_FONT* font = GetFont(fontID);
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