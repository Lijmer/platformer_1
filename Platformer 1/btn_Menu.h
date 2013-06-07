#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
class btn_Menu
{
public:
	btn_Menu(void);
	~btn_Menu(void);

	void Update(void);
	void Draw(void);
	void Init(float x, float y, int kind);
	void Execute();
	bool CheckMouseCollision(void);

	void SetSelected(bool selected)		{btn_Menu::selected = selected;}
	void SetAlive(bool alive)			{btn_Menu::alive = alive;}
	
	bool GetAlive()						{return alive;}

	enum
	{
		NEW_GAME,
		NEW_GAME1,
		NEW_GAME2,
		NEW_GAME3,
		DIFFICULTY,
		START,
		LOAD_GAME,
		LOAD_GAME1,
		LOAD_GAME2,
		LOAD_GAME3,
		SETTINGS,
		TOGGLE_MUSIC,
		MUSIC_VOLUME,
		TOGGLE_SOUND,
		SOUND_VOLUME,
		TOGGLE_FULLSCREEN,
		TOGGLE_DROP_FRAMES,
		HELP,
		EXIT,
		BACK
	};

private:
	int kind;
	float x,y;
	int boundUp, boundDown, boundLeft, boundRight;
	bool selected; //only for drawing
	bool alive;
	
	ALLEGRO_BITMAP *image;

	void DrawTextOutline(ALLEGRO_FONT *font, ALLEGRO_COLOR innerColor,	ALLEGRO_COLOR outerColor,
		float x, float y, int flags, int radius, const char* text);
};

