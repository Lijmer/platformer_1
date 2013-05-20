#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
class obj_Menu_Button
{
public:
	obj_Menu_Button(void);
	~obj_Menu_Button(void);
	
	void Init(float x, float y, int kind);
	void Update();
	void Draw();

	static void NextButton();
	static void PreviousButton();
	void Execute();

	static int GetNumButtons()		{return numButtons;}
	static int GetSelectedButton()	{return selectedButton;}

	enum
	{
		NEW_GAME,
		NEW_GAME1,
		NEW_GAME2,
		NEW_GAME3,
		LOAD_GAME,
		LOAD_GAME1,
		LOAD_GAME2,
		LOAD_GAME3,
		OPTIONS,
		TOGGLE_MUSIC,
		MUSIC_VOLUME,
		TOGGLE_SOUND,
		SOUND_VOLUME,
		HELP,
		EXIT,
		BACK
	};

private:
	void DrawTextOutline(ALLEGRO_FONT *font, ALLEGRO_COLOR innerColor,	ALLEGRO_COLOR outerColor,
		float x, float y, int flags, int radius, const char* text);

	float x,y;
	int boundUp, boundDown, boundLeft, boundRight;
	int kind;
	bool selected;

	ALLEGRO_BITMAP *image;

	int buttonID;

	static int numButtons;
	static int selectedButton;
};
