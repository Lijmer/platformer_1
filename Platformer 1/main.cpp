//All stuff that needs to be included is in this file
//#define true false //This line of code can fuck up everything ;)
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "globals.h"
//Backgroundstuff Objects
#include "FileManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "DisplayManager.h"
#include "GameObjectManager.h"


//Function that is used to calculate the time it takes to run a certain piece of code
inline double diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = clock1 - clock2;
	double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
	return diffms;
}
inline void UpdateTime()
{
	if(++_steps > 60)
	{
		_steps-=60;
		if(++_seconds>60)
		{
			_seconds-=60;
			if(++_minutes>60)
			{
				_minutes-=60;
				_hours++;
			}
		}
	}
}

int main(int argc, char *argv[]) //I have no idea why I use argc, char *argv[]  This applications doesn't take parameters...
{
	#pragma region Setup

	//==============================================
	//PROJECT VARIABLES
	//==============================================
	bool done = false;
	bool render = false;
	int gameTime = 0;
	int frames = 0;
	float gameFPS = 0;
	srand(time(unsigned int(0)));
	_difficulty=0;

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())	//initialize Allegro (if it fails to do, show error message and terminate
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "Error!", "Couldn't initialize allegro 5", "Ok Sok", 0);
		return -1;
	}
	if(!DisplayManager::GetInstance().CreateDisplay()) //Create display, if it fails to create a display, show error message en terminate (error message is in function)
		return -1;
	
	al_install_keyboard();
	al_init_primitives_addon();

	//==============================================
	//PROJECT INIT
	//==============================================
	FontManager::GetInstance().Init();
	ImageManager::GetInstance().Init();
	SoundManager::GetInstance().Init();
	GameObjectManager::GetInstance().Init();
	//Play Music
	//SoundManager::GetInstance().Play(50);
	//Map
	FileManager::GetInstance().LoadLevel(_currentLevel);
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(DisplayManager::GetInstance().GetDisplay()));

	al_start_timer(timer);
	gameTime = al_current_time();
	#pragma endregion Setting up the game before entering the loop (declaring variables, initing allegro, installing addons, registering event sources)
	
	#pragma region Main Game Loop
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		#pragma region Input
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				_keys_pressed[LEFT]=true;
				_keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				_keys_pressed[RIGHT]=true;
				_keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				_keys_pressed[UP] = true;
				_keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				_keys_pressed[DOWN] = true;
				_keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				_keys_pressed[SPACE] = true;
				_keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_Z:
				_keys_pressed[Z_KEY]=true;
				_keys[Z_KEY] = true;
				break;
			case ALLEGRO_KEY_X:
				_keys_pressed[X_KEY]=true;
				_keys[X_KEY] = true;
				break;
			case ALLEGRO_KEY_R:
				_keys_pressed[R_KEY]=true;
				_keys[R_KEY]=true;
				FileManager::GetInstance().RestartLevel(_currentLevel);
				_camX_prev=-1;
				_camY_prev=-1;
				break;
			case ALLEGRO_KEY_Q:
				if(GameObjectManager::GetInstance().D_object_exists(PLAYER))
				{
					GameObjectManager::GetInstance().KillPlayer();
				}
				break;
			case ALLEGRO_KEY_L:
				FileManager::GetInstance().Load();
				break;
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = true;
				_keys_pressed[ALT]=true;
				break;
			case ALLEGRO_KEY_ENTER:
				if(_keys[ALT])
					DisplayManager::GetInstance().ChangeState();
				break;
			case ALLEGRO_KEY_ALTGR:
				GameObjectManager::GetInstance().StressTest();
				break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				_keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				_keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				_keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				_keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				_keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_Z:
				_keys_released[Z_KEY]=true;
				_keys[Z_KEY] = false;
				break;
			case ALLEGRO_KEY_X:
				_keys_released[X_KEY]=true;
				_keys[X_KEY] = false;
				break;
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = false;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done=true;
		}
		#pragma endregion Get input from the user

		#pragma region Timer event
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;			
			UpdateTime();
			/*GameObjectManager::GetInstance().Update();
			GameObjectManager::GetInstance().Collisions();
			GameObjectManager::GetInstance().Clean();
			GameObjectManager::GetInstance().ActivateDeactivate();
			GameObjectManager::GetInstance().MotionlessParticles();
			*/
			GameObjectManager::GetInstance().TimerEvent();
			_camX_prev=_camX;
			_camY_prev=_camY;
			//stillParticlesSize = stillParticles.size();
			//Reset keys
			for(int i=0; i<8; i++)
				_keys_pressed[i]=false;
		}
		#pragma endregion This is where the magic happens ;)

		#pragma region Draw
		if(render && al_is_event_queue_empty(event_queue))
		{
			//UPDATE FPS=======================================================================================================
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			
			render = false;
			
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			al_clear_to_color(al_map_rgb(192,192,192));
			
			//BEGIN PROJECT RENDER=============================================================================================
			//Draw all the objects
			GameObjectManager::GetInstance().Draw();
			//Draw text
			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,5,0,"FPS: %f", gameFPS);
			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,85,0,"_camX: %i\t_camY: %i", _camX, _camY);
			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,105,0,"hours: %i\tminutes: %i\tseconds: %i\tsteps: %i", _hours, _minutes, _seconds, _steps);
			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,125,0,"Deaths: %i", _deaths);
			//Draw borders
			al_draw_filled_rectangle(-(_monitorWidth - (_SCREEN_WIDTH * _scaleScreen))/2.0, 0, 0, _SCREEN_HEIGHT,al_map_rgb(0,0,0));
			al_draw_filled_rectangle(_SCREEN_WIDTH + (_monitorWidth - (_SCREEN_WIDTH * _scaleScreen))/2.0, 0, _SCREEN_WIDTH, _SCREEN_HEIGHT, al_map_rgb(0,0,0));
			al_draw_filled_rectangle(0, -(_monitorHeight - (_SCREEN_HEIGHT * _scaleScreen))/2.0, _SCREEN_WIDTH, 0, al_map_rgb(0,0,0));
			al_draw_filled_rectangle(0, _SCREEN_HEIGHT + (_monitorHeight - (_SCREEN_HEIGHT * _scaleScreen))/2.0, _SCREEN_WIDTH, _SCREEN_HEIGHT, al_map_rgb(0,0,0));

			//FLIP BUFFERS========================
			al_flip_display();
		}
		#pragma endregion All drawing stuff happens in here
	}
	#pragma endregion

	#pragma region Clean up
	//SHELL OBJECTS=================================
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	#pragma endregion This destroys all objects and variables made in the platformer
	return 0;
}
