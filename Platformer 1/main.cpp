#pragma region includes
//All stuff that needs to be included is in this file
//#define true false //This line of code can fuck up everything ;)
//#define if else //this on too xD
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "globals.h"
#include "Transformer.h"

#include "Background.h"

//Backgroundstuff Objects
#include "FileManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "DisplayManager.h"
#include "GameObjectManager.h"
#include "ButtonManager.h"
#include "LevelManager.h"

#include "Exit.h"

#include <iostream>
using namespace Transformer;
#pragma endregion

float mX=0;
float mY=0;
int gameTime = 0;
int frames = 0;
float gameFPS = 0;
bool render = false;

void GetInput(const ALLEGRO_EVENT &ev);
void DrawBorders();
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
inline void ResetKeys()
{
	for(int i=0; i<KEYS_SIZE; i++)
	{
		_keys_pressed[i]=false;
		_keys_released[i]=false;
	}
	for(int i=0; i<M_SIZE; i++)
	{
		_mouse_pressed[i]=false;
	}
}
inline void UpdateFPS()
{
	frames++;
	if(al_current_time() - gameTime >= 1)
	{
		gameTime = al_current_time();
		gameFPS = frames;
		frames = 0;
	}
}

int main(int argc, char *argv[]) //I have no idea why I use argc, char *argv[]  This applications doesn't take parameters...
{
	#pragma region Setup
	#pragma region Init Allegro, create display and install addons
	//Initialize allegro and create a display
	if(!al_init())	//initialize Allegro (if it fails to do, show error message and terminate
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "Error!", "Couldn't initialize allegro 5", "Ok Sok", 0);
		return -1;
	}
	DisplayManager::GetInstance().CreateDisplay();
	
	//install addons
	al_install_keyboard();
	al_install_mouse();
	al_install_joystick();
	al_reconfigure_joysticks();

	al_init_primitives_addon();
	#pragma endregion
	#pragma region Init Managers
	//Initialize managers
	GameObjectManager::GetInstance().Init();
	ButtonManager::GetInstance().Init();
	LevelManager::GetInstance().Init();
	#pragma endregion
	gameTime = al_get_time();
	srand(time(unsigned int(0)));
	#pragma region Events and Timers
	//Create event_queue and timer
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(DisplayManager::GetInstance().GetDisplay()));

	al_start_timer(timer);
	#pragma endregion
	
	#pragma endregion Setting up the game before entering the loop (declaring variables, initing allegro, installing addons, registering event sources)

	#pragma region Main Game Loop
	while(!Exit::GetDone())
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		GetInput(ev);
		#pragma region Timer event
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			UpdateTime();
			if(_keys_pressed[R_KEY])
				LevelManager::GetInstance().RestartLevel();

			if(_keys_pressed[Q_KEY] && GameObjectManager::GetInstance().D_object_exists(PLAYER))
				GameObjectManager::GetInstance().KillPlayer();

			Background::GetInstance().Update();
			GameObjectManager::GetInstance().TimerEvent();
			ButtonManager::GetInstance().TimerEvent();
			SoundManager::GetInstance().Update();
			
			CheckIfCamIsChanged();

			_camX_prev=_camX;
			_camY_prev=_camY;

			if(DisplayManager::GetInstance().GetState() == DisplayManager::WINDOWED)
			{
				_mouseX=mX+_camX;
				_mouseY=mY+_camY;
			}
			else if(DisplayManager::GetInstance().GetState() == DisplayManager::FULLSCREEN_WINDOW)
			{
				_mouseX = ((mX - (_monitorWidth - (_SCREEN_WIDTH * _scaleScreen))/2.0)/_scaleScreen)+_camX;
				_mouseY = ((mY - (_monitorHeight - (_SCREEN_HEIGHT * _scaleScreen))/2.0)/_scaleScreen)+_camY;
			}

			ResetKeys();	
		}
		#pragma endregion This is where the magic happens ;)
		#pragma region Draw
		if(render && al_is_event_queue_empty(event_queue) || (render && !GetDropFrames()))
		{
			UpdateFPS();
			render = false;
			
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			al_clear_to_color(al_map_rgb(192,192,192));

			//Draw all the objects
			Background::GetInstance().Draw();
			GameObjectManager::GetInstance().Draw();
			ButtonManager::GetInstance().Draw();

			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,255,255), 10, 10, 0, "FPS: %f", gameFPS);

			DrawBorders();

			al_flip_display();
		}
		#pragma endregion All drawing stuff happens in here
	}
	#pragma endregion
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	
	return Exit::GetReturnValue();
}

inline void GetInput(const ALLEGRO_EVENT &ev)
{
	#pragma region key down
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch(ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			Exit::ExitProgram();
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
		case ALLEGRO_KEY_L:
			_keys_pressed[L_KEY]=true;
			_keys[L_KEY]=true;
			//FileManager::GetInstance().Load();
			break;
		case ALLEGRO_KEY_M:
			SoundManager::GetInstance().ToggleMusic();
			break;
		case ALLEGRO_KEY_Q:
			_keys_pressed[Q_KEY]=true;
			_keys[Q_KEY]=true;
			break;
		case ALLEGRO_KEY_R:
			_keys_pressed[R_KEY]=true;
			_keys[R_KEY]=true;
			break;
		case ALLEGRO_KEY_S:
			SoundManager::GetInstance().ToggleSound();
			break;
		case ALLEGRO_KEY_X:
			_keys_pressed[X_KEY]=true;
			_keys[X_KEY] = true;
			break;
		case ALLEGRO_KEY_Z:
			_keys_pressed[Z_KEY]=true;
			_keys[Z_KEY] = true;
			break;
		case ALLEGRO_KEY_ENTER:
			_keys_pressed[ENTER]=true;
			_keys[ENTER]=true;
			if(_keys[ALT])
				DisplayManager::GetInstance().ChangeState();
			break;
		case ALLEGRO_KEY_ALT:
			_keys_pressed[ALT]=true;
			_keys[ALT] = true;
			break;
		case ALLEGRO_KEY_ALTGR:
			_keys_pressed[ALTGR]=true;
			_keys[ALTGR]=true;
			break;
		}
	}
	#pragma endregion
	#pragma region key up
	else if(ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch(ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			Exit::ExitProgram(0);
			break;
		case ALLEGRO_KEY_LEFT:
			_keys_released[LEFT]=true;
			_keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			_keys_released[RIGHT]=true;
			_keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_UP:
			_keys_released[UP]=true;
			_keys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			_keys_released[DOWN]=true;
			_keys[DOWN] = false;
			break;
		case ALLEGRO_KEY_SPACE:
			_keys_released[SPACE]=true;
			_keys[SPACE] = false;
			break;
		case ALLEGRO_KEY_L:
			_keys_released[L_KEY]=true;
			_keys[L_KEY]=false;
			break;
		case ALLEGRO_KEY_Q:
			_keys_released[Q_KEY]=true;
			_keys[Q_KEY]=false;
			break;
		case ALLEGRO_KEY_R:
			_keys_released[R_KEY]=true;
			_keys[R_KEY]=false;
			break;
		case ALLEGRO_KEY_X:
			_keys_released[X_KEY]=true;
			_keys[X_KEY] = false;
			break;
		case ALLEGRO_KEY_Z:
			_keys_released[Z_KEY]=true;
			_keys[Z_KEY] = false;
			break;
		case ALLEGRO_KEY_ENTER:
			_keys_released[ENTER]=true;
			_keys[ENTER]=false;
			break;
		case ALLEGRO_KEY_ALT:
			_keys_released[ALT]=true;
			_keys[ALT] = false;
			break;
		case ALLEGRO_KEY_ALTGR:
			_keys_released[ALTGR]=true;
			_keys[ALTGR]=false;
			break;
		}
	}
	#pragma endregion
	#pragma region Mouse Input
	else if(ev.type==ALLEGRO_EVENT_MOUSE_AXES)
	{
		mX=ev.mouse.x;
		mY=ev.mouse.y;			
	}
	else if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(ev.mouse.button & 1)
		{
			_mouse_pressed[M_LEFT]=true;
		}
		else if(ev.mouse.button & 2)
		{
			_mouse_pressed[M_RIGHT]=true;
		}
	}
	#pragma endregion
	#pragma region Joystick Input

	#pragma region Joystick Button Down
	else if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
	{
		if(ev.joystick.button == 0 || ev.joystick.button == 1||
			ev.joystick.button == 2 || ev.joystick.button == 3)
		{
			_keys[Z_KEY]=true;
			_keys_pressed[Z_KEY]=true;
		}
		else if(ev.joystick.button == 4 || ev.joystick.button == 5 ||
			ev.joystick.button == 6 || ev.joystick.button == 7)
		{
			_keys[X_KEY]=true;
			_keys_pressed[X_KEY]=true;
		}
		else if(ev.joystick.button == 8)
		{
			_keys[R_KEY]=true;
			_keys_pressed[R_KEY]=true;
		}
		else if(ev.joystick.button == 9)
		{
			_keys[ENTER]=true;
			_keys_pressed[ENTER]=true;
		}
		else if(ev.joystick.button == 10)
		{
			_keys[ESCAPE]=true;
			_keys_pressed[ESCAPE]=true;
		}
	}
	#pragma endregion
	#pragma region Joystick Button Up
	else if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
	{
		if(ev.joystick.button == 0 || ev.joystick.button == 1||
			ev.joystick.button == 2 || ev.joystick.button == 3)
		{
			_keys[Z_KEY]=false;
			_keys_released[Z_KEY]=true;
		}
		else if(ev.joystick.button == 4 || ev.joystick.button == 5 ||
			ev.joystick.button == 6 || ev.joystick.button == 7)
		{
			_keys[X_KEY]=false;
			_keys_released[X_KEY]=true;
		}
		else if(ev.joystick.button == 8)
		{
			_keys[R_KEY]=false;
			_keys_released[R_KEY]=true;
		}
		else if(ev.joystick.button == 9)
		{
			_keys[ENTER]=false;
			_keys_released[ENTER]=true;
		}
		else if(ev.joystick.button == 10)
		{
			_keys[ESCAPE]=false;
			_keys_released[ESCAPE]=true;
		}
	}
	#pragma endregion
	#pragma region Joystick axis
	else if(ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
	{
		#pragma region D-pad
		if(ev.joystick.stick == 2)
		{
			if(ev.joystick.axis == 0)
			{
				//left
				if(ev.joystick.pos == -1)
				{
					_keys[LEFT]=true;
					_keys_pressed[LEFT]=true;
				}
				//right
				else if(ev.joystick.pos == 1)
				{
					_keys[RIGHT]=true;
					_keys_pressed[RIGHT]=true;
				}
				//middle
				else if(ev.joystick.pos == 0)
				{
					_keys[LEFT]=false;
					_keys[RIGHT]=false;
					_keys_released[LEFT]=true;
					_keys_released[RIGHT]=true;
				}
			}
			else if(ev.joystick.axis == 1)
			{
				//up
				if(ev.joystick.pos == -1)
				{
					_keys[UP]=true;
					_keys_pressed[UP]=true;
				}
				//down
				else if(ev.joystick.pos == 1)
				{
					_keys[DOWN]=true;
					_keys_pressed[DOWN]=true;
				}
				//middle
				else if(ev.joystick.pos == 0)
				{
					_keys[UP]=false;
					_keys[DOWN]=false;
					_keys_released[UP]=true;
					_keys_released[DOWN]=true;
				}
			}
		}
		#pragma endregion
		
		#pragma region Left joystick
		else if(ev.joystick.stick==0)
		{
			if(ev.joystick.axis==0)
			{
				//left
				if(ev.joystick.pos <= -0.3)
				{
					if(!_keys[LEFT])
						_keys_pressed[LEFT]=true;
					_keys[LEFT]=true;
					_keys[RIGHT]=false;
					_keys_released[RIGHT]=true;
				}
				//right
				else if(ev.joystick.pos >= .3)
				{
					if(!_keys[RIGHT])
						_keys_pressed[RIGHT]=true; 
					_keys[RIGHT]=true;
						
					_keys[LEFT]=false;
					_keys_released[LEFT]=true;
				}
				//middle
				else if(ev.joystick.pos > -0.3 && ev.joystick.pos < 0.3)
				{
					_keys[LEFT]=false;
					_keys[RIGHT]=false;
					_keys_released[LEFT]=true;
					_keys_released[RIGHT]=true;
				}
			}
			else if(ev.joystick.axis==1)
			{
				//up
				if(ev.joystick.pos <= -0.3)
				{
					if(!_keys[UP])
						_keys_pressed[UP]=true;
					_keys[UP]=true;
					_keys[DOWN]=false;
					_keys_released[DOWN]=true;
				}
				//down
				else if(ev.joystick.pos >= .3)
				{
					if(!_keys[DOWN])
						_keys_pressed[DOWN]=true; 
					_keys[DOWN]=true;
						
					_keys[UP]=false;
					_keys_released[UP]=true;
				}
				//middle
				else if(ev.joystick.pos > -0.3 && ev.joystick.pos < 0.3)
				{
					_keys[UP]=false;
					_keys[DOWN]=false;
					_keys_released[UP]=true;
					_keys_released[DOWN]=true;
				}
			}
		}
		#pragma endregion
	}
	#pragma endregion

	#pragma endregion
	#pragma region otherinput
	else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		Exit::ExitProgram();
	}
	#pragma endregion
}

inline void DrawBorders()
{
	al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
	float lbX1 = TransformDisplayX(-(_monitorWidth - (_SCREEN_WIDTH * _scaleScreen))/2.0);
	float lbX2 = TransformDisplayX(0);
	float lbY1 = TransformDisplayY(0);
	float lbY2 = TransformDisplayY(_SCREEN_HEIGHT);
	float rbX1 = TransformDisplayX(_SCREEN_WIDTH + (_monitorWidth - (_SCREEN_WIDTH * _scaleScreen))/2.0);
	float rbX2 = TransformDisplayX(_SCREEN_WIDTH);
	float rbY1 = TransformDisplayY(0);
	float rbY2 = TransformDisplayY(_SCREEN_HEIGHT);
	float ubX1 = TransformDisplayX(0);
	float ubX2 = TransformDisplayX(_SCREEN_WIDTH);
	float ubY1 = TransformDisplayY(-(_monitorHeight - (_SCREEN_HEIGHT * _scaleScreen))/2.0);
	float ubY2 = TransformDisplayY(0);
	float dbX1 = TransformDisplayX(0);
	float dbX2 = TransformDisplayX(_SCREEN_WIDTH);
	float dbY1 = TransformDisplayY(_SCREEN_HEIGHT + (_monitorHeight - (_SCREEN_HEIGHT * _scaleScreen))/2.0);
	float dbY2 = TransformDisplayY(_SCREEN_HEIGHT);

	//Draw borders
	al_draw_filled_rectangle(lbX1, lbY1, lbX2, lbY2,al_map_rgb(0,0,0));
	al_draw_filled_rectangle(rbX1, rbY1, rbX2, rbY2, al_map_rgb(0,0,0));
	al_draw_filled_rectangle(ubX1, ubY1, ubX2, ubY2, al_map_rgb(0,0,0));
	al_draw_filled_rectangle(dbX1, dbY1, dbX2, dbY2, al_map_rgb(0,0,0));
}

