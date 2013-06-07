#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class FontManager
{
public:
	FontManager(void);
	static FontManager& GetInstance();
	~FontManager(void);


	ALLEGRO_FONT* GetFont(char ID);

	void DrawTextOutline(int fontID, ALLEGRO_COLOR innerColor,
		ALLEGRO_COLOR outerColor,float x, float y, int flags,int radius, const char* text);
	
private:
	ALLEGRO_FONT *nokiafc22_18;
};

