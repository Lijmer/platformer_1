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

	void Init();

	ALLEGRO_FONT* GetFont(char ID);
	
private:
	ALLEGRO_FONT *nokiafc22_18;
};

