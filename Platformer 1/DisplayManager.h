#pragma once
#include <allegro5/allegro.h>

class DisplayManager
{
public:
	DisplayManager(void);
	~DisplayManager(void);

	static DisplayManager &GetInstance();

	bool CreateDisplay();
	ALLEGRO_DISPLAY* GetDisplay();

	void ChangeState();
	char GetState()			{return state;}

	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_TRANSFORM camera;

	enum STATE
	{
		WINDOWED,
		FULLSCREEN_WINDOW
	};
private:
	char state;
	int monitorWidth;
	int monitorHeight;
};

