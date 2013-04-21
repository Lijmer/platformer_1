#pragma region Include
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
//Basic Stuff
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

//Backgroundstuff Objects
#include "FileManager.h"
#include "SoundManager.h"
#include "imageManager.h"
#include "FontManager.h"
#include "DisplayManager.h"

//Game Objects:
#include "GameObject.h"
#include "DynamicObject.h"
#include "Particle.h"
#include "StaticObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Wall_Fake.h"
#include "Wall_Fade.h"
#include "Spike_Up.h"
#include "Spike_Down.h"
#include "Spike_Left.h"
#include "Spike_Right.h"
#include "Save.h"
#include "obj_Trigger_Double_Spike.h"
#include "obj_Double_Spike_Down.h"
#include "obj_Double_Spike_Up.h"
#include "obj_Saw.h"
#include "obj_Saw_Small.h"
#include "obj_Saw_Bar.h"
#include "obj_Platform_Vertical.h"
#include "obj_Platform_Horizontal.h"
#include "obj_Treadmill_Left.h"

#include "Blood.h"
#include "Blood_Head.h"
#include "Blood_Torso.h"

using std::vector;
using std::cout;
using std::endl;
using namespace std;

#pragma endregion All include and using stuff is in here

#pragma region Variables
vector<DynamicObject *> dynamicObjects;
vector<DynamicObject *> deactivatedDynamicObjects;
vector<StaticObject *> staticObjects;
vector<StaticObject *> deactivatedStaticObjects;
vector<Particle *> particles;
vector<Particle *> stillParticles;
vector<Particle *> stillParticlesBuffer;
vector<Particle *> deactivatedParticles;


vector<DynamicObject *>::iterator iter;
vector<DynamicObject *>::iterator iter2;
vector<DynamicObject *>::iterator dynamicPlaceFreeIter;
vector<DynamicObject *>::reverse_iterator r_iter; 
vector<DynamicObject *>::reverse_iterator r_iter2;
vector<StaticObject *>::iterator iter3;
vector<StaticObject *>::iterator iter4;
vector<StaticObject *>::iterator staticPlaceFreeIter;
vector<StaticObject *>::reverse_iterator r_iter3;
vector<Particle *>::iterator particleIter;

Player *player = NULL;
Bullet *bullet = NULL;
Wall *wall = NULL;
Wall_Fake *wall_fake = NULL;
Wall_Fade *wall_fade = NULL;
Spike_Up *spike_up = NULL;
Spike_Down *spike_down = NULL;
Spike_Left *spike_left = NULL;
Spike_Right *spike_right = NULL;
Save *save = NULL;
obj_Trigger_Double_Spike *obj_trigger_double_spike = NULL;
obj_Double_Spike_Down *obj_double_spike_down = NULL;
obj_Double_Spike_Up *obj_double_spike_up = NULL;
obj_Saw *obj_saw = NULL;
obj_Saw_Small *obj_saw_small = NULL;
obj_Saw_Bar *obj_saw_bar = NULL;
obj_Platform_Vertical *obj_platform_vertical = NULL;
obj_Platform_Horizontal *obj_platform_horizontal = NULL;
obj_Treadmill_Left *obj_treadmill_left = NULL;

Blood *blood = NULL;
Blood_Head *blood_head = NULL;
Blood_Torso *blood_torso = NULL;

int stillParticlesSize = -1;

#pragma endregion All vectors, object pointers and other variables are declared in here

#pragma region Prototypes
//prototypes
bool __cdecl PlaceFree(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, 
	unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize);
int SortFunction(GameObject *i, GameObject *j) {return (i->GetDepth()<j->GetDepth());}
bool D_object_exists(int ID);
//void __cdecl CreateObject(int ID,int x,int y);
GameObject* __cdecl CreateObject(int ID,int x,int y);
obj_Double_Spike_Down* __cdecl Create_obj_Double_Spike_Down(float x,float y);
obj_Double_Spike_Up* __cdecl Create_obj_Double_Spike_Up(float x,float y);
void __cdecl DeleteDynamicObjects(void);
void __cdecl ReserveSpace(char ID, int size);
void MaxParticles();
void __cdecl Shoot(bool dir, float x, float y, float velX);
#pragma endregion All protypes are in here

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

			#pragma region UpdateEnd
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				(*iter)->UpdateEnd();
			#pragma endregion This is an extra update function that rusn after the collions event

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
			al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,85,0,"_camX: %i\t_camY: %i", _camX, _camY);
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

#pragma region Functions

#pragma region PlaceFree
bool __cdecl PlaceFree(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize)
{
	for(staticPlaceFreeIter = staticObjects.begin(); staticPlaceFreeIter != staticObjects.end(); staticPlaceFreeIter++)
	{		
		if((*staticPlaceFreeIter)->GetID() != WALL) continue;
		if(x + boundRight  >= (*staticPlaceFreeIter)->GetX() - (*staticPlaceFreeIter)->GetBoundLeft() &&
			x - boundLeft  <= (*staticPlaceFreeIter)->GetX() + (*staticPlaceFreeIter)->GetBoundRight() &&
			y + boundDown  >= (*staticPlaceFreeIter)->GetY() - (*staticPlaceFreeIter)->GetBoundUp() &&
			y - boundUp  <= (*staticPlaceFreeIter)->GetY() + (*staticPlaceFreeIter)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	for(dynamicPlaceFreeIter = dynamicObjects.begin(); dynamicPlaceFreeIter != dynamicObjects.end(); dynamicPlaceFreeIter++)
	{		
		/*if((*dynamicPlaceFreeIter)->GetID() != WALL_FADE && (*dynamicPlaceFreeIter)->GetID()!= SAVE && (*dynamicPlaceFreeIter)->GetID()!=PLAYER &&
		(*dynamicPlaceFreeIter)->GetID()!=HORIZONTAL_PLATFORM && (*dynamicPlaceFreeIter)->GetID()!=VERTICAL_PLATFORM 
			|| (*dynamicPlaceFreeIter)->GetInstanceID() == instanceID)
		continue;*/
		bool cont = true;

		for(int i=0; i<exceptionIDsSize; i++)
		{
			if((*dynamicPlaceFreeIter)->GetID() == exceptionIDs[i])
			{
				cont = false;
				break;
			}
		}

		if(cont || instanceID == (*dynamicPlaceFreeIter)->GetInstanceID())
			continue;


		if(x + boundRight  >= (*dynamicPlaceFreeIter)->GetX() - (*dynamicPlaceFreeIter)->GetBoundLeft() &&
			x - boundLeft  <= (*dynamicPlaceFreeIter)->GetX() + (*dynamicPlaceFreeIter)->GetBoundRight() &&
			y + boundDown  >= (*dynamicPlaceFreeIter)->GetY() - (*dynamicPlaceFreeIter)->GetBoundUp() &&
			y - boundUp  <= (*dynamicPlaceFreeIter)->GetY() + (*dynamicPlaceFreeIter)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	return true;
}
#pragma endregion Checks if there is no object blocking the player.

#pragma region D_object_exists
bool D_object_exists(int ID)
{
	for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
	{
		if((*iter)->GetID() == ID)
			return true;
	}
	for(iter = deactivatedDynamicObjects.begin(); iter!=deactivatedDynamicObjects.end(); iter++)
	{
		if((*iter)->GetID() == ID)
			return true;
	}
	return false;
}
#pragma endregion Check if dynamic object with ID exists

#pragma region CreateObject

GameObject* __cdecl CreateObject(int ID,int x,int y)
{
	if(ID==0)
	{
		wall = new Wall();
		wall->Init(x,y);
		staticObjects.push_back(wall);
		return wall;
	}
	else if(ID==1)
	{
		spike_up = new Spike_Up();
		spike_up->Init(x,y);
		staticObjects.push_back(spike_up);
		return spike_up;
	}
	else if(ID==2)
	{
		spike_down = new Spike_Down();
		spike_down->Init(x,y);
		staticObjects.push_back(spike_down);
		return spike_down;
	}
	else if(ID==3)
	{
		spike_left = new Spike_Left();
		spike_left->Init(x,y);
		staticObjects.push_back(spike_left);
		return spike_left;
	}
	else if(ID==4)
	{
		spike_right = new Spike_Right();
		spike_right->Init(x,y);
		staticObjects.push_back(spike_right);
		return spike_right;
	}
	else if(ID==5)
	{
		wall_fade = new Wall_Fade();
		wall_fade->Init(x,y);
		dynamicObjects.push_back(wall_fade);
		return wall_fade;
	}
	else if(ID==6)
	{
		wall_fake = new Wall_Fake();
		wall_fake->Init(x,y);
		staticObjects.push_back(wall_fake);
		return wall_fake;
	}
	else if(ID==7)
	{
		obj_trigger_double_spike = new obj_Trigger_Double_Spike(&Create_obj_Double_Spike_Down,&Create_obj_Double_Spike_Up);
		obj_trigger_double_spike->Init(x,y);
		dynamicObjects.push_back(obj_trigger_double_spike);
		return obj_trigger_double_spike;
	}
	else if(ID==8)
	{
		obj_saw = new obj_Saw();
		obj_saw->Init(x,y);
		dynamicObjects.push_back(obj_saw);
		return obj_saw;
	}
	else if(ID==9)
	{
		obj_saw_small = new obj_Saw_Small();
		obj_saw_small->Init(x,y);
		dynamicObjects.push_back(obj_saw_small);
		return obj_saw_small;
	}
	else if(ID==10)
	{
		obj_saw_bar = new obj_Saw_Bar(&CreateObject);
		obj_saw_bar->Init(x,y);
		dynamicObjects.push_back(obj_saw_bar);
		return obj_saw_bar;
	}
	else if(ID==11)
	{
		obj_platform_vertical = new obj_Platform_Vertical(&PlaceFree);
		obj_platform_vertical->Init(x,y,0,-2);
		dynamicObjects.push_back(obj_platform_vertical);
		return obj_platform_vertical;
	}
	else if(ID==12)
	{
		obj_platform_horizontal = new obj_Platform_Horizontal(&PlaceFree);
		obj_platform_horizontal->Init(x,y,2,0);
		dynamicObjects.push_back(obj_platform_horizontal);
		return obj_platform_horizontal;
	}
	else if(ID==14)
	{
		obj_treadmill_left = new obj_Treadmill_Left();
		obj_treadmill_left->Init(x,y,-2,0);
		dynamicObjects.push_back(obj_treadmill_left);
		return obj_treadmill_left;
	}
	else if(ID==96)
	{
		save = new Save(&CreateObject);
		save->Init(x,y,0);
		dynamicObjects.push_back(save);
		return save;
	}
	else if(ID==97)
	{
		save = new Save(&CreateObject);
		save->Init(x,y,1);
		dynamicObjects.push_back(save);
		return save;
	}
	else if(ID==98)
	{
		save = new Save(&CreateObject);
		save->Init(x,y,2);
		dynamicObjects.push_back(save);
		return save;
	}
	else if(ID==99)
	{
		player = new Player(&PlaceFree, &CreateObject, &ReserveSpace, &Shoot);
		player->Init(x,y);
		dynamicObjects.push_back(player);
		return player;
	}

	else if(ID==100)
	{
		blood = new Blood();
		blood->Init(x,y,rand()%360,(((float)rand()/(float)RAND_MAX)*30.0));
		particles.push_back(blood);
		return blood;
	}
	else if(ID==101)
	{
		blood_head = new Blood_Head();
		blood_head->Init(x,y,270,20);
		particles.push_back(blood_head);
		return blood_head;
	}
	else if(ID==102)
	{
		blood_torso = new Blood_Torso();
		blood_torso->Init(x,y,rand()%360,((float)rand()/(float)RAND_MAX)*30.0);
		particles.push_back(blood_torso);
		return blood_torso;
	}
	return NULL;
}
#pragma endregion

#pragma region Double_Spike
obj_Double_Spike_Down* __cdecl Create_obj_Double_Spike_Down(float x,float y)
{
	obj_double_spike_down = new obj_Double_Spike_Down;
	obj_double_spike_down->Init(x,y);
	dynamicObjects.push_back(obj_double_spike_down);
	return obj_double_spike_down;
}
obj_Double_Spike_Up* __cdecl Create_obj_Double_Spike_Up(float x,float y)
{
	obj_double_spike_up = new obj_Double_Spike_Up;
	obj_double_spike_up->Init(x,y);
	dynamicObjects.push_back(obj_double_spike_up);
	return obj_double_spike_up;
}

#pragma endregion

#pragma region deleteDynamicObjects
void __cdecl DeleteDynamicObjects(void)
{
	for(iter=dynamicObjects.begin();iter!=dynamicObjects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = dynamicObjects.erase(iter);
	}
	for(iter=deactivatedDynamicObjects.begin();iter!=deactivatedDynamicObjects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = deactivatedDynamicObjects.erase(iter);
	}
}
#pragma endregion

#pragma region MaxParticles()
void MaxParticles()
{
	while(particles.size()>1500)
	{
		particleIter = particles.begin();
		(*particleIter)->Destroy();
		delete (*particleIter);
		particleIter=particles.erase(particleIter);
	}
	while(deactivatedParticles.size()>5000)
	{
		particleIter = deactivatedParticles.begin();
		(*particleIter)->Destroy();
		delete (*particleIter);
		particleIter=deactivatedParticles.erase(particleIter);
	}
}
#pragma endregion

#pragma region ReserveSpace()
void __cdecl ReserveSpace(char ID, int size)
{
	if(ID==0) //Dynamic Objects
	{
		dynamicObjects.reserve(size);
	}
	else if(ID==1) //Deactivated DynamicObjects
	{
		deactivatedDynamicObjects.reserve(size);
	}
	else if(ID==2) //Static Objects
	{
		staticObjects.reserve(size);
	}
	else if(ID==3) //Deactivated Static Objects
	{
		deactivatedStaticObjects.reserve(size);
	}
	else if(ID==4) //Particles
	{
		particles.reserve(size);
	}

}
#pragma endregion

#pragma region Shoot
void __cdecl Shoot(bool dir, float x, float y, float velX)
{
	bullet = new Bullet();
	if(dir)
		bullet->Init(x+13, y-1, velX+10);
	else
		bullet->Init(x-13, y-1, velX-10);
	dynamicObjects.push_back(bullet);
}
#pragma endregion This functions will be called by the player object and shoot a bullet

#pragma endregion All functions (except for main) in this file are here :D
