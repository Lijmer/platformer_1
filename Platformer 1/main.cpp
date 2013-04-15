#pragma region Include
#include <allegro5/allegro_native_dialog.h>
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
vector<DynamicObject *>::reverse_iterator r_iter; 
vector<DynamicObject *>::reverse_iterator r_iter2;
vector<StaticObject *>::iterator iter3;
vector<StaticObject *>::iterator iter4;
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

Blood *blood = NULL;
Blood_Head *blood_head = NULL;
Blood_Torso *blood_torso = NULL;

int stillParticlesSize = -1;

#pragma endregion All vectors, object pointers and other variables are declared in here

#pragma region Prototypes
//prototypes
bool __cdecl PlaceFree(float x, float y);
int SortFunction(GameObject *i, GameObject *j) {return (i->GetDepth()<j->GetDepth());}
bool D_object_exists(int ID);
void __cdecl CreateObject(int ID,int x,int y);
GameObject* __cdecl CreateObjectWithPointer(int ID,int x,int y);
obj_Double_Spike_Down* __cdecl Create_obj_Double_Spike_Down(float x,float y);
obj_Double_Spike_Up* __cdecl Create_obj_Double_Spike_Up(float x,float y);
void __cdecl DeleteDynamicObjects(void);
void __cdecl ReserveSpace(char ID, int size);
void MaxParticles();
#pragma endregion All protypes are in here

int main(int argc, char *argv[])
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
	int APM = 0, APS = 0;


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
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_TRANSFORM camera;
	ALLEGRO_BITMAP *staticCanvas = NULL;
	ALLEGRO_BITMAP *stillParticleCanvas = NULL;
	
	al_show_native_message_box(NULL, "Test!", "Test!", "Test", "Ok Sok", 0);

	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())	//initialize Allegro
	{
		al_show_native_message_box(NULL, "Error!", "Error!", "Couldn't init allegro 5", "Ok Sok", 0);
		return -1;
	}
	#pragma region Display
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);	//create our display object

	float scaleScreenWidth = disp_data.width / (float)_SCREEN_WIDTH;
	float scaleScreenHeight = disp_data.height / (float)_SCREEN_HEIGHT;
	float scaleScreen = min(scaleScreenWidth, scaleScreenHeight);

	al_identity_transform(&camera);
	al_scale_transform(&camera, scaleScreen, scaleScreen);
	al_translate_transform(&camera, (disp_data.width - (_SCREEN_WIDTH * scaleScreen))/2.0, (disp_data.height - (_SCREEN_HEIGHT * scaleScreen))/2.0);
	al_use_transform(&camera);

	if(!display)			//test display object
	{
		al_show_native_message_box(NULL, "Error!", "Error!", "Couldn't create display", "Ok Sok", 0);
		return -1;
	}

	#pragma endregion

	//
	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_primitives_addon();
	//al_install_joystick();
	//al_reconfigure_joysticks();
    //joystick=al_get_joystick(al_get_num_joysticks()-1);

	//==============================================
	//PROJECT INIT
	//==============================================
	
	//font
	FontManager::GetInstance().Init();
	//images
	ImageManager::GetInstance().Init();
	//sound
	SoundManager::GetInstance().Init();
	SoundManager::GetInstance().Play(50);

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
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	gameTime = al_current_time();
	#pragma endregion Setting up the game before entering the loop (declaring variables, initing allegro, installing addons, registering even sources)
	
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
				_keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				_keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				_keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_Z:
				_keys_pressed[Z_KEY]=true;
				_keys[Z_KEY] = true;
				break;
			case ALLEGRO_KEY_X:
				_keys_pressed[X_KEY]=true;
				_keys[X_KEY] = true;
				if(Bullet::getNumBullets() < 10 && D_object_exists(PLAYER))
				{
					bool dir = player->GetDir();
					bullet = new Bullet();
					SoundManager::GetInstance().Play(SHOOT);
					if(dir)
						bullet->Init(player->GetX()+13,player->GetY()-1,player->GetVelX()+10,0,BULLET,0);
					else
						bullet->Init(player->GetX()-13,player->GetY()-1,player->GetVelX()-10,0,BULLET,0);
					dynamicObjects.push_back(bullet);
				}
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

			#pragma region Update
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				(*iter)->Update();
			for(particleIter = particles.begin(); particleIter!=particles.end(); particleIter++)
				(*particleIter)->Update();
			#pragma endregion

			#pragma region Collisions
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
			{
				for(iter2 = dynamicObjects.begin(); iter2!=dynamicObjects.end(); iter2++)
				{
					if((*iter)->GetID() == (*iter2)->GetID()) continue;
					if(!(*iter)->CheckCollision((*iter2)))	continue;
					(*iter)->Collided(*iter2);
					(*iter2)->Collided(*iter);
				}
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					if(!(*iter)->CheckCollision((*iter3)))	continue;
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
			#pragma endregion

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
				al_set_target_bitmap(staticCanvas);
				al_clear_to_color(al_map_rgba(0,0,0,0));
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					(*iter3)->Draw();
				}
			}
			#pragma endregion

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
			#pragma endregion

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

			#pragma endregion
			
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
			
			al_set_target_backbuffer(display);
			al_clear_to_color(al_map_rgb(192,192,192));

			//BEGIN PROJECT RENDER=============================================================================================
			//sort(staticObjects.begin(),staticObjects.end(), sortFunction);
			sort(dynamicObjects.begin(),dynamicObjects.end(), SortFunction);
			al_draw_bitmap(staticCanvas,0,0,0);
			for(r_iter = dynamicObjects.rbegin(); r_iter!=dynamicObjects.rend(); r_iter++)
				(*r_iter)->Draw();
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
			al_draw_filled_rectangle(-(disp_data.width - (_SCREEN_WIDTH * scaleScreen))/2.0, 0, 0, _SCREEN_HEIGHT,al_map_rgb(0,0,0));
			al_draw_filled_rectangle(_SCREEN_WIDTH + (disp_data.width - (_SCREEN_WIDTH * scaleScreen))/2.0, 0, _SCREEN_WIDTH, _SCREEN_HEIGHT, al_map_rgb(0,0,0));
			al_draw_filled_rectangle(0, -(disp_data.height - (_SCREEN_HEIGHT * scaleScreen))/2.0, _SCREEN_WIDTH, 0, al_map_rgb(0,0,0));
			al_draw_filled_rectangle(0, _SCREEN_HEIGHT + (disp_data.height - (_SCREEN_HEIGHT * scaleScreen))/2.0, _SCREEN_WIDTH, _SCREEN_HEIGHT, al_map_rgb(0,0,0));

			//FLIP BUFFERS========================
			al_flip_display();
		}
		#pragma endregion All drawing stuff happens in here
	}

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

	//SHELL OBJECTS=================================
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	#pragma endregion This destroys all objects and variables made in the platformer

	return 0;
}

#pragma region Functions

#pragma region PlaceFree
bool __cdecl PlaceFree(float x, float y)
{
	for(iter3 = staticObjects.begin(); iter3 != staticObjects.end(); iter3++)
	{		
		if((*iter3)->GetID() != WALL) continue;
		if(x + player->GetBoundRight() >= (*iter3)->GetX() - (*iter3)->GetBoundLeft() &&
			x - player->GetBoundLeft() <= (*iter3)->GetX() + (*iter3)->GetBoundRight() &&
			y + player->GetBoundDown() -1 > (*iter3)->GetY() - (*iter3)->GetBoundUp() &&
			y - player->GetBoundUp() +1 < (*iter3)->GetY() + (*iter3)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	for(iter2 = dynamicObjects.begin(); iter2 != dynamicObjects.end(); iter2++)
	{		
		if((*iter2)->GetID() != WALL_FADE && (*iter2)->GetID()!= SAVE) continue;
		if(x + player->GetBoundRight() >= (*iter2)->GetX() - (*iter2)->GetBoundLeft() &&
			x - player->GetBoundLeft() <= (*iter2)->GetX() + (*iter2)->GetBoundRight() &&
			y + player->GetBoundDown() -1 > (*iter2)->GetY() - (*iter2)->GetBoundUp() &&
			y - player->GetBoundUp() +1 < (*iter2)->GetY() + (*iter2)->GetBoundDown())
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
void __cdecl CreateObject(int ID,int x,int y)
{
	if(ID==0)
	{
		wall = new Wall();
		wall->Init(x,y);
		staticObjects.push_back(wall);
	}
	else if(ID==1)
	{
		spike_up = new Spike_Up();
		spike_up->Init(x,y);
		staticObjects.push_back(spike_up);
	}
	else if(ID==2)
	{
		spike_down = new Spike_Down();
		spike_down->Init(x,y);
		staticObjects.push_back(spike_down);
	}
	else if(ID==3)
	{
		spike_left = new Spike_Left();
		spike_left->Init(x,y);
		staticObjects.push_back(spike_left);
	}
	else if(ID==4)
	{
		spike_right = new Spike_Right();
		spike_right->Init(x,y);
		staticObjects.push_back(spike_right);
	}
	else if(ID==5)
	{
		wall_fade = new Wall_Fade();
		wall_fade->Init(x,y);
		dynamicObjects.push_back(wall_fade);
	}
	else if(ID==6)
	{
		wall_fake = new Wall_Fake();
		wall_fake->Init(x,y);
		staticObjects.push_back(wall_fake);
	}
	else if(ID==7)
	{
		obj_trigger_double_spike = new obj_Trigger_Double_Spike(&Create_obj_Double_Spike_Down, &Create_obj_Double_Spike_Up);
		obj_trigger_double_spike->Init(x,y);
		dynamicObjects.push_back(obj_trigger_double_spike);
	}
	else if(ID==8)
	{
		obj_saw = new obj_Saw();
		obj_saw->Init(x,y);
		dynamicObjects.push_back(obj_saw);
	}
	else if(ID==9)
	{
		obj_saw_small = new obj_Saw_Small();
		obj_saw_small->Init(x,y);
		dynamicObjects.push_back(obj_saw_small);
	}
	else if(ID==10)
	{
		obj_saw_bar = new obj_Saw_Bar(&CreateObjectWithPointer);
		obj_saw_bar->Init(x,y);
		dynamicObjects.push_back(obj_saw_bar);
	}
	else if(ID==96)
	{
		save = new Save(&CreateObject);
		save->Init(x,y,0);
		dynamicObjects.push_back(save);
	}
	else if(ID==97)
	{
		save = new Save(&CreateObject);
		save->Init(x,y,1);
		dynamicObjects.push_back(save);
	}
	else if(ID==98)
	{
		save = new Save(&CreateObject);
		save->Init(x,y,2);
		dynamicObjects.push_back(save);
	}
	else if(ID==99)
	{
		player = new Player(&PlaceFree, &CreateObject, &ReserveSpace);
		player->Init(x,y);
		dynamicObjects.push_back(player);
	}

	else if(ID==100)
	{
		blood = new Blood();
		blood->Init(x,y,rand()%360,(((float)rand()/(float)RAND_MAX)*30.0));
		particles.push_back(blood);
	}
	else if(ID==101)
	{
		blood_head = new Blood_Head();
		blood_head->Init(x,y,270,10);
		particles.push_back(blood_head);
	}
	else if(ID==102)
	{
		blood_torso = new Blood_Torso();
		blood_torso->Init(x,y,rand()%360,((float)rand()/(float)RAND_MAX)*30.0);
		particles.push_back(blood_torso);
	}
}

GameObject* __cdecl CreateObjectWithPointer(int ID,int x,int y)
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
		obj_saw_bar = new obj_Saw_Bar(&CreateObjectWithPointer);
		obj_saw_bar->Init(x,y);
		dynamicObjects.push_back(obj_saw_bar);
		return obj_saw_bar;
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
		player = new Player(&PlaceFree, &CreateObject, &ReserveSpace);
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
#pragma endregion
