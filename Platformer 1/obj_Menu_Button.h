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
	void Click();
	void Draw();

	static void NextButton();
	static void PreviousButton();
	void Execute();
	void ExecuteBack();

	static int GetNumButtons()		{return numButtons;}
	static int GetSelectedButton()	{return selectedButton;}
	int GetBoundUp()				{return boundUp;}
	int GetBoundDown()				{return boundDown;}
	int GetBoundLeft()				{return boundLeft;}
	int GetBoundRight()				{return boundRight;}
	float GetX()					{return x;}
	float GetY()					{return y;}
	bool GetAlive()					{return alive;}
	bool GetSelected()				{return selected;}

	static void SetNumButtons(int numButtons)			{obj_Menu_Button::numButtons=numButtons;}
	static void SetSelectedButton(int selectedButton)	{obj_Menu_Button::selectedButton = selectedButton;}

	void SetSelected(bool selected)						{obj_Menu_Button::selected = selected;}
	void SetAlive(bool alive)							
	{
		if(alive == false)
		{
			numButtons--;
			selectedButton=0;
		}
		obj_Menu_Button::alive = alive;
	}

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
		TOGGLE_FULLSCREEN,
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
	bool alive;

	ALLEGRO_BITMAP *image;

	int buttonID;

	static int numButtons;
	static int selectedButton;
};
