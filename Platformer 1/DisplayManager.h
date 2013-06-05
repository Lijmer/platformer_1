#pragma once
#include <allegro5/allegro.h>

class DisplayManager
{
public:
	DisplayManager(void);
	~DisplayManager(void);

	static DisplayManager &GetInstance();

	void CreateDisplay();
	ALLEGRO_DISPLAY* GetDisplay();
	/*
	void UseFinalTransform();
	void UseCameraTransform();
	void UseDisplayTransform();
	void ResetFinalTransform();
	*/
	void ChangeState();
	char GetState()			{return state;}


	enum STATE
	{
		WINDOWED,
		FULLSCREEN_WINDOW
	};
private:
	/*
	ALLEGRO_TRANSFORM& TransformCamera();
	ALLEGRO_TRANSFORM& TransformDisplay();
	ALLEGRO_TRANSFORM& CombineTransform(ALLEGRO_TRANSFORM &trans1, ALLEGRO_TRANSFORM &trans2);
	*/
	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY_MODE disp_data;
	//ALLEGRO_TRANSFORM cameraTransform;
	//ALLEGRO_TRANSFORM displayTransform;
	//ALLEGRO_TRANSFORM finalTransform;

	char state;
	int monitorWidth;
	int monitorHeight;
};

