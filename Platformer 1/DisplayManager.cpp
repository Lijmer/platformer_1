#include "DisplayManager.h"


DisplayManager::DisplayManager(void)
{
	display = NULL;
	state = WINDOWED;
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

bool DisplayManager::CreateDisplay()
{

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(_SCREEN_WIDTH, _SCREEN_HEIGHT);	//create our display object
	//al_toggle_display_flag(display, ALLEGRO_NOFRAME, false);
	float scaleScreenWidth = disp_data.width / (float)_SCREEN_WIDTH;
	float scaleScreenHeight = disp_data.height / (float)_SCREEN_HEIGHT;
	_scaleScreen = min(scaleScreenWidth, scaleScreenHeight);
	_monitorWidth = disp_data.width;
	_monitorHeight = disp_data.height;

	al_identity_transform(&camera);
	al_scale_transform(&camera, 1, 1);
	al_translate_transform(&camera, 0, 0);
	al_use_transform(&camera);

	if(!display) //test display object
	{
		al_show_native_message_box(NULL, "Error!", "DisplayManager", "Couldn't create display", "Ok Sok", 0);
		return false;
	}
	return true;
}


ALLEGRO_DISPLAY* DisplayManager::GetDisplay()
{
	return display;
}

void DisplayManager::ChangeState()
{
	if(state == FULLSCREEN_WINDOW)
	{
		state = WINDOWED;

		al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false);
		al_toggle_display_flag(display, ALLEGRO_NOFRAME, false);
		al_resize_display(display, _SCREEN_WIDTH, _SCREEN_HEIGHT);

		//Reset transformation
		al_identity_transform(&camera);
		//al_scale_transform(&camera, 1, 1);
		//al_translate_transform(&camera, 0, 0);
		al_use_transform(&camera);
	}
	else if(state == WINDOWED)
	{
		state = FULLSCREEN_WINDOW;

		al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);
		al_toggle_display_flag(display, ALLEGRO_NOFRAME, true);
		al_resize_display(display, _monitorWidth, _monitorHeight);

		al_identity_transform(&camera);
		al_scale_transform(&camera, _scaleScreen, _scaleScreen);
		al_translate_transform(&camera, (disp_data.width - (_SCREEN_WIDTH * _scaleScreen))/2.0, (disp_data.height - (_SCREEN_HEIGHT * _scaleScreen))/2.0);
		al_use_transform(&camera);
	}
}
