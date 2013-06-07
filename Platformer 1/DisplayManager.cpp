#include "DisplayManager.h"
#include <allegro5/allegro_native_dialog.h>
#include "globals.h"

#include "Exit.h"

DisplayManager::DisplayManager(void)
{
	display = NULL;
	state = FULLSCREEN_WINDOW;
	monitorWidth=0;
	monitorHeight=0;
}


DisplayManager::~DisplayManager(void)
{
	al_destroy_display(display);
}

DisplayManager &DisplayManager::GetInstance()
{
	static DisplayManager instance;
	return instance;
}

void DisplayManager::CreateDisplay()
{

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME);
	//al_toggle_display_flag(display, ALLEGRO_NOFRAME, false);
	float scaleScreenWidth = disp_data.width / (float)_SCREEN_WIDTH;
	float scaleScreenHeight = disp_data.height / (float)_SCREEN_HEIGHT;
	_scaleScreen = min(scaleScreenWidth, scaleScreenHeight);
	_monitorWidth = disp_data.width;
	_monitorHeight = disp_data.height;

	
	display = al_create_display(disp_data.width, disp_data.height);	//create our display object

	if(!display) //test display object
	{
		al_show_native_message_box(NULL, "Error!", "DisplayManager", "Couldn't create display", "Ok Sok", 0);
		Exit::ExitProgram(-2);
	}
}

ALLEGRO_DISPLAY* DisplayManager::GetDisplay()
{
	return display;
}

void DisplayManager::ChangeState()
{
	if(state == FULLSCREEN_WINDOW)
	{
		SetState(WINDOWED);
	}
	else if(state == WINDOWED)
	{
		SetState(FULLSCREEN_WINDOW);
	}
}
void DisplayManager::SetState(int state)
{
	DisplayManager::state=state;
	if(state == WINDOWED)
	{
		al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false);
		al_toggle_display_flag(display, ALLEGRO_NOFRAME, false);
		al_resize_display(display, _SCREEN_WIDTH, _SCREEN_HEIGHT);
	}
	else if(state == FULLSCREEN_WINDOW)
	{
		al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);
		al_toggle_display_flag(display, ALLEGRO_NOFRAME, true);
	}
}
/*
void DisplayManager::UseFinalTransform()
{
	al_use_transform(&CombineTransform(TransformCamera(), TransformDisplay()));
}
void DisplayManager::UseCameraTransform()
{
	al_use_transform(&TransformCamera());
}
void DisplayManager::UseDisplayTransform()
{
	al_use_transform(&TransformDisplay());
}

void DisplayManager::ResetFinalTransform()
{
	al_identity_transform(&finalTransform);
	al_use_transform(&finalTransform);
}

ALLEGRO_TRANSFORM& DisplayManager::TransformCamera()
{
	al_identity_transform(&cameraTransform);
	al_translate_transform(&cameraTransform, -_camX, -_camY);
	return cameraTransform;
}
ALLEGRO_TRANSFORM& DisplayManager::TransformDisplay()
{
	al_identity_transform(&displayTransform);
	if(state == FULLSCREEN_WINDOW)
	{
		al_identity_transform(&displayTransform);
		al_scale_transform(&displayTransform, _scaleScreen, _scaleScreen);
		al_translate_transform(&displayTransform, (disp_data.width - (_SCREEN_WIDTH * _scaleScreen))/2.0, (disp_data.height - (_SCREEN_HEIGHT * _scaleScreen))/2.0);
	}
	return displayTransform;
}

ALLEGRO_TRANSFORM& DisplayManager::CombineTransform(ALLEGRO_TRANSFORM &trans1, ALLEGRO_TRANSFORM &trans2)
{
	al_compose_transform(&finalTransform, &trans1);
	al_compose_transform(&finalTransform, &trans2);
	return finalTransform;
}

*/