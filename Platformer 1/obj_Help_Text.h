#pragma once
#include <allegro5/allegro_font.h>
class obj_Help_Text
{
public:
	obj_Help_Text(void);
	~obj_Help_Text(void);

	void Init(float x, float y);
	void Draw();

	void SetAlive(bool alive)	{obj_Help_Text::alive = alive;}
	bool GetAlive()				{return alive;}

private:
	float x, y;
	bool alive;

	void DrawTextOutline(ALLEGRO_FONT *font, ALLEGRO_COLOR innerColor,
		ALLEGRO_COLOR outerColor, float x, float y, int flags,int radius, const char* text);
};
