#include "obj_Help_Text.h"
#include "FontManager.h"

obj_Help_Text::obj_Help_Text(void)
{
}


obj_Help_Text::~obj_Help_Text(void)
{
}

void obj_Help_Text::Init(float x, float y)
{
	obj_Help_Text::x = x;
	obj_Help_Text::y = y;
}

void obj_Help_Text::Draw()
{
	DrawTextOutline(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),
		x, y, ALLEGRO_ALIGN_CENTRE, 2, "No help will be given MUHAHAHAHAHAHA!");
}

inline void obj_Help_Text::DrawTextOutline(ALLEGRO_FONT *font, ALLEGRO_COLOR innerColor,
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