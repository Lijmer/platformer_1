//All stuff that needs to be included is in this file
//#define true false //This line of code can fuck up everything ;)
#include "main_funcs_vars.h"

int stillParticlesSize = -1;

//Function that is used to sort the dynamicObjects vector
int SortFunction(GameObject *i, GameObject *j) {return (i->GetDepth()<j->GetDepth());}

int main(int argc, char *argv[]) //I have no idea why I use argc, char *argv[]  This applications doesn't take parameters...
{
	#pragma region Setup
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool done = false;
	bool render = false;
	int gameTime = 0;
	int frames = 0;
	float gameFPS = 0;
	//int APM = 0, APS = 0;
	srand(time(unsigned int(0)));

	//==============================================
	//PROJECT VARIABLES
	//==============================================
	particles.reserve(125);
	_difficulty=0;
	stillParticlesSize = stillParticles.size();

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *staticCanvas = NULL;
	ALLEGRO_BITMAP *stillParticleCanvas = NULL;
	
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())	//initialize Allegro
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "Error!", "Couldn't initialize allegro 5", "Ok Sok", 0);
		return -1;
	}
	if(!DisplayManager::GetInstance().CreateDisplay()) //Create display (if display there is a problem the application will terminate)
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_primitives_addon();
	
	//==============================================
	//PROJECT INIT
	//==============================================
	FontManager::GetInstance().Init();
	ImageManager::GetInstance().Init();
	SoundManager::GetInstance().Init();
	//Play Music
	//SoundManager::GetInstance().Play(50);
	//Map
	FileManager fmanager(&CreateObject, &DeleteDynamicObjects);
	fmanager.LoadLevel(_currentLevel);

	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);
	staticCanvas = al_create_bitmap(1024,768);
	stillParticleCanvas = al_create_bitmap(1024,768);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(DisplayManager::GetInstance().GetDisplay()));

	al_start_timer(timer);
	gameTime = al_current_time();
	#pragma endregion Setting up the game before entering the loop (declaring variables, initing allegro, installing addons, registering even sources)

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
				fmanager.RestartLevel(_currentLevel);
				_camX_prev=-1;
				_camY_prev=-1;
				break;
			case ALLEGRO_KEY_Q:
				if(D_object_exists(PLAYER))
				{
					player->Kill();
					player->SetAlive(false);
				}
				break;
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = true;
				_keys_pressed[ALT]=true;
				break;
			case ALLEGRO_KEY_ENTER:
				if(_keys[ALT])
					DisplayManager::GetInstance().ChangeState();
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
			
			//This function isn't used yet, so it's not called. But it is here just in case it will be used later.
			//(remove this code on a final build if it is not used, AND DON'T FORGET TO REMOVE THE VIRTUAL FUNCTION FROM DynamicObject!!
			/*#pragma region UpdateBegin
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				(*iter)->UpdateBegin();
			#pragma endregion*/

			#pragma region Update
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				(*iter)->Update();
			for(particleIter = particles.begin(); particleIter!=particles.end(); particleIter++)
				(*particleIter)->Update();
			#pragma endregion Run the update function for all objects

			#pragma region Collisions
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
			{
				//Check for collision with other dynamic objects
				for(iter2 = iter; iter2!=dynamicObjects.end(); iter2++)
				{
					if((*iter)->GetInstanceID() == (*iter2)->GetInstanceID()) continue;
					if((*iter)->GetID() == (*iter2)->GetID()) continue;
					if(!(*iter)->CheckCollision((*iter2)))	continue;
					(*iter)->Collided(*iter2);
					(*iter2)->Collided(*iter);
				}
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					if(!(*iter)->CheckCollision((*iter3)))
						continue;
					(*iter)->Collided(*iter3);
				}
			}
			for(particleIter=particles.begin(); particleIter!=particles.end(); particleIter++)
			{
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					if((*particleIter)->CheckCollision(*iter3))
					{
						(*particleIter)->Collided(*iter3);
					}
				}
				for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				{
					if((*particleIter)->CheckCollision(*iter))
						(*particleIter)->Collided(*iter);
				}
			}
			#pragma endregion Check for collions

			//This function isn't used yet, so it's not called. But it is here just in case it will be used later.
			//(remove this code on a final build if it is not used, AND DON'T FORGET TO REMOVE THE VIRTUAL FUNCTION FROM DynamicObject!!
			/*
			#pragma region UpdateEnd
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				(*iter)->UpdateEnd();
			#pragma endregion This is an extra update function that rusn after the collions event
			*/

			#pragma region Cleaning
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); )
			{
				if(!(*iter)->GetAlive())
				{
					(*iter)->Destroy();
					delete (*iter);
					iter = dynamicObjects.erase(iter);
				}
				else
					++iter;
			}

			for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); )
			{
				if(!(*iter3)->GetAlive())
				{
					(*iter3)->Destroy();
					delete (*iter3);
					iter3 = staticObjects.erase(iter3);
				}
				else
					++iter3;
			}

			MaxParticles();

			#pragma endregion Deletes all objects (that are not deactivated) where alive == false

			#pragma region Activate and Deactivate
			if(_camX!=_camX_prev || _camY!=_camY_prev)
			{
				//Activate
				for(iter = deactivatedDynamicObjects.begin(); iter!=deactivatedDynamicObjects.end();)
				{
					(*iter)->Activate();
					if((*iter)->GetActivated())
					{
						dynamicObjects.push_back((*iter));
						iter = deactivatedDynamicObjects.erase(iter);
					}
					else
						iter++;
				}
				for(iter3 = deactivatedStaticObjects.begin(); iter3!=deactivatedStaticObjects.end();)
				{
					(*iter3)->Activate();
					if((*iter3)->GetActivated())
					{
						staticObjects.push_back((*iter3));
						iter3 = deactivatedStaticObjects.erase(iter3);
					}
					else
						iter3++;
				}
				for(particleIter = deactivatedParticles.begin(); particleIter!=deactivatedParticles.end();)
				{
					(*particleIter)->Activate();
					if((*particleIter)->GetActivated())
					{
						stillParticles.push_back((*particleIter));
						particleIter = deactivatedParticles.erase(particleIter);
					}
					else
						particleIter++;
				}

				//Deactivate
				for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end();)
				{
					if((*iter)->GetID() != PLAYER)
					{
						(*iter)->Deactivate();
						if(!(*iter)->GetActivated())
						{
							deactivatedDynamicObjects.push_back((*iter));
							iter = dynamicObjects.erase(iter);
						}
						else
							iter++;
					}
					else
						iter++;
				}
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end();)
				{
					(*iter3)->Deactivate();
					if(!(*iter3)->GetActivated())
					{
						deactivatedStaticObjects.push_back((*iter3));
						iter3 = staticObjects.erase(iter3);
					}
					else
						iter3++;
				}
				for(particleIter = stillParticles.begin(); particleIter!=stillParticles.end();)
				{
					(*particleIter)->Deactivate();
					if(!(*particleIter)->GetActivated())
					{
						deactivatedParticles.push_back((*particleIter));
						particleIter = stillParticles.erase(particleIter);
					}
					else
						particleIter++;
				}

				//Draw all staticobjects on the staticCanvas, This is so there will be less looping through the staticObjectsvector
				sort(staticObjects.begin(),staticObjects.end(), SortFunction);
				al_set_target_bitmap(staticCanvas);
				al_clear_to_color(al_map_rgba(0,0,0,0));
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					(*iter3)->Draw();
				}
			}
			#pragma endregion All objects that are outside of the screen get put in a different vector.

			#pragma region Not moving particles
			for(particleIter=particles.begin(); particleIter!=particles.end(); )
			{
				if((*particleIter)->GetVelX() == 0 && (*particleIter)->GetVelY() == 0)
				{
					stillParticlesBuffer.push_back((*particleIter));
					particleIter = particles.erase(particleIter);
				}
				else
					particleIter++;
			}

			if(stillParticlesBuffer.size() >= 125)
			{
				for(particleIter = stillParticlesBuffer.begin(); particleIter!=stillParticlesBuffer.end(); )
				{
					stillParticles.push_back((*particleIter));
					particleIter = stillParticlesBuffer.erase(particleIter);
				}
			}

			if(stillParticlesSize != stillParticles.size())
			{
				al_set_target_bitmap(stillParticleCanvas);
				al_clear_to_color(al_map_rgba(0,0,0,0));
				for(particleIter = stillParticles.begin(); particleIter!=stillParticles.end(); particleIter++)
					(*particleIter)->Draw();
			}
			#pragma endregion Find which particles are not moving, put theme in a seperate vector and draw them on a different bitmap
			
			_camX_prev=_camX;
			_camY_prev=_camY;
			stillParticlesSize = stillParticles.size();
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
			
			sort(dynamicObjects.begin(),dynamicObjects.end(), SortFunction);
			//Draw static objects
			al_draw_bitmap(staticCanvas,0,0,0);
			
			//Draw dynamic objects
			for(r_iter = dynamicObjects.rbegin(); r_iter!=dynamicObjects.rend(); r_iter++)
				(*r_iter)->Draw();

			//Draw Particles
			for(particleIter = stillParticlesBuffer.begin(); particleIter!=stillParticlesBuffer.end(); particleIter++)
				(*particleIter)->Draw();
			for(particleIter = particles.begin(); particleIter!=particles.end(); particleIter++)
				(*particleIter)->Draw();
			al_draw_bitmap(stillParticleCanvas,0,0,0);
			
			
			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,5,0,"FPS: %f", gameFPS);
			//al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,85,0,"_camX: %i\t_camY: %i", _camX, _camY);
			
			if(D_object_exists(PLAYER))
			{
				al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,25,0,"X: %f\tY: %f", player->GetX(), player->GetY());
				al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,45,0,"Gravity: %f", player->GetGravity());
				al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,65,0,"velY: %f\tvelX: %f", player->GetVelY(), player->GetVelX());
			}
			
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
	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================
	for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); )
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = dynamicObjects.erase(iter);
	}
	for(iter = deactivatedDynamicObjects.begin(); iter!=deactivatedDynamicObjects.end();)
	{
		(*iter)->Destroy();
		delete(*iter);
		iter = deactivatedDynamicObjects.erase(iter);
	}
	for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); )
	{
		(*iter3)->Destroy();
		delete (*iter3);
		iter3 = staticObjects.erase(iter3);
	}
	for(iter3 = deactivatedStaticObjects.begin(); iter3!=deactivatedStaticObjects.end(); )
	{
		(*iter3)->Destroy();
		delete (*iter3);
		iter3 = deactivatedStaticObjects.erase(iter3);
	}
	for(particleIter = particles.begin(); particleIter !=particles.end();)
	{
		(*particleIter)->Destroy();
		delete (*particleIter);
		particleIter = particles.erase(particleIter);
	}
	for(particleIter = stillParticles.begin(); particleIter!=stillParticles.end();)
	{
		(*particleIter)->Destroy();
		delete (*particleIter);
		particleIter = stillParticles.erase(particleIter);
	}
	for(particleIter = deactivatedParticles.begin(); particleIter != deactivatedParticles.end(); )
	{
		(*particleIter)->Destroy();
		delete(*particleIter);
		particleIter = deactivatedParticles.erase(particleIter);
	}

	FontManager::GetInstance().Clean();
	SoundManager::GetInstance().Clean();
	ImageManager::GetInstance().Clean();
	DisplayManager::GetInstance().Clean();

	//SHELL OBJECTS=================================
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	#pragma endregion This destroys all objects and variables made in the platformer
	
	return 0;
}