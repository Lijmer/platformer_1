//Basic Stuff
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
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
#include "Blood.h"
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

using std::vector;
using std::cout;
using std::endl;
using namespace std;

//globals
vector<DynamicObject *> dynamicObjects;
vector<DynamicObject *> deactivatedDynamicObjects;
vector<StaticObject *> staticObjects;
vector<StaticObject *> deactivatedStaticObjects;
vector<Particle *> particles;
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
Blood *blood = NULL;
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


bool keys_pressed[]		=	{false, false, false, false, false, false, false, false};
bool keys_released[]	=	{false, false, false, false, false, false, false, false};
bool keys[]				=	{false, false, false, false, false, false, false, false};

//prototypes
bool __cdecl placeFree(float x, float y);
int sortFunction(GameObject *i, GameObject *j) {return (i->getDepth()<j->getDepth());}
bool d_object_exists(int ID);
void __cdecl createObject(int ID,int x,int y);
GameObject* __cdecl createObjectWithPointer(int ID,int x,int y);
obj_Double_Spike_Down* __cdecl create_obj_Double_Spike_Down(float x,float y);
obj_Double_Spike_Up* __cdecl create_obj_Double_Spike_Up(float x,float y);
void __cdecl deleteDynamicObjects(void);
void __cdecl reserveSpace(char ID, int size);
void maxParticles();

int main(int argc, char **argv)
{
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool done = false;
	bool render = false;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;
	int APM = 0, APS = 0;


	srand(time(unsigned int(0)));
	//==============================================
	//PROJECT VARIABLES
	//==============================================
	particles.reserve(750);
	global::difficulty=0;

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_TRANSFORM camera;
	
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())	//initialize Allegro
		return -1;

	display = al_create_display(global::SCREEN_WIDTH, global::SCREEN_HEIGHT);	//create our display object

	if(!display)																//test display object
		return -1;
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
	FontManager::GetInstance().init();
	//images
	ImageManager::getInstance().init();
	//sound
	SoundManager::GetInstance().init();
	SoundManager::GetInstance().play(50);

	//Map
	FileManager fmanager(&createObject, &deleteDynamicObjects);
	fmanager.loadLevel(global::currentLevel); 
	
	
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	gameTime = al_current_time();
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==============================================
		//INPUT
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys_pressed[global::LEFT]=true;
				keys[global::LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys_pressed[global::RIGHT]=true;
				keys[global::RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[global::UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[global::DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[global::SPACE] = true;
				break;
			case ALLEGRO_KEY_Z:
				keys_pressed[global::Z_KEY]=true;
				keys[global::Z_KEY] = true;
				break;
			case ALLEGRO_KEY_X:
				keys_pressed[global::X_KEY]=true;
				keys[global::X_KEY] = true;
				if(Bullet::getNumBullets() < 10 && d_object_exists(global::PLAYER))
				{
					bool dir = player->getDir();
					bullet = new Bullet();
					SoundManager::GetInstance().play(global::SHOOT);
					if(dir)
						bullet->init(player->getX()+13,player->getY()-1,player->getVelX()+10,0,global::BULLET,0);
					else
						bullet->init(player->getX()-13,player->getY()-1,player->getVelX()-10,0,global::BULLET,0);
					dynamicObjects.push_back(bullet);
				}
				break;
			case ALLEGRO_KEY_R:
				keys_pressed[global::R_KEY]=true;
				keys[global::R_KEY]=true;
				fmanager.restartLevel(global::currentLevel);
				global::camX_prev=-1;
				global::camY_prev=-1;
				break;
			case ALLEGRO_KEY_Q:
				if(d_object_exists(global::PLAYER))
				{
					player->kill();
					player->setAlive(false);
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
				keys[global::LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[global::RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[global::UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[global::DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[global::SPACE] = false;
				break;
			case ALLEGRO_KEY_Z:
				keys_released[global::Z_KEY]=true;
				keys[global::Z_KEY] = false;
				break;
			case ALLEGRO_KEY_X:
				keys_released[global::X_KEY]=true;
				keys[global::X_KEY] = false;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done=true;
		}
		//=====================================================================================================================
		//GAME UPDATE
		//=====================================================================================================================
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//====================================
			//update
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				(*iter)->update(keys, keys_pressed);
			for(particleIter = particles.begin(); particleIter!=particles.end(); particleIter++)
				(*particleIter)->update();

			//collisions
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
			{
				for(iter2 = dynamicObjects.begin(); iter2!=dynamicObjects.end(); iter2++)
				{
					if((*iter)->getID() == (*iter2)->getID()) continue;
					if(!(*iter)->checkCollision((*iter2)))	continue;
					(*iter)->Collided(*iter2);
					(*iter2)->Collided(*iter);
				}
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					if(!(*iter)->checkCollision((*iter3)))	continue;
					(*iter)->Collided(*iter3);
				}
			}
			for(particleIter=particles.begin(); particleIter!=particles.end(); particleIter++)
			{
				for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); iter3++)
				{
					if((*particleIter)->checkCollision(*iter3))
					{
						(*particleIter)->Collided(*iter3);
					}
				}
				for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
				{
					if((*particleIter)->checkCollision(*iter))
						(*particleIter)->Collided(*iter);
				}
			}
			
			//cull the dead
			for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); )
			{
				if(!(*iter)->getAlive())
				{
					(*iter)->destroy();
					delete (*iter);
					iter = dynamicObjects.erase(iter);
				}
				else
					++iter;
			}

			for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); )
			{
				if(!(*iter3)->getAlive())
				{
					(*iter3)->destroy();
					delete (*iter3);
					iter3 = staticObjects.erase(iter3);
				}
				else
					++iter3;
			}

			//Activate and Deactivate objects when Camera has moved
			if(global::camX!=global::camX_prev || global::camY!=global::camY_prev)
			{
				//Activate
				for(iter = deactivatedDynamicObjects.begin(); iter!=deactivatedDynamicObjects.end();)
				{
					(*iter)->activate();
					if((*iter)->getActivated())
					{
						dynamicObjects.push_back((*iter));
						iter = deactivatedDynamicObjects.erase(iter);
					}
					else
						iter++;
				}
				for(iter3 = deactivatedStaticObjects.begin(); iter3!=deactivatedStaticObjects.end();)
				{
					(*iter3)->activate();
					if((*iter3)->getActivated())
					{
						staticObjects.push_back((*iter3));
						iter3 = deactivatedStaticObjects.erase(iter3);
					}
					else
						iter3++;
				}
				for(particleIter = deactivatedParticles.begin(); particleIter!=deactivatedParticles.end();)
				{
					(*particleIter)->activate();
					if((*particleIter)->getActivated())
					{
						particles.push_back((*particleIter));
						particleIter = deactivatedParticles.erase(particleIter);
					}
					else
						particleIter++;
				}

				//Deactivate
				for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end();)
				{
					if((*iter)->getID() != global::PLAYER)
					{
						(*iter)->deactivate();
						if(!(*iter)->getActivated())
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
					(*iter3)->deactivate();
					if(!(*iter3)->getActivated())
					{
						deactivatedStaticObjects.push_back((*iter3));
						iter3 = staticObjects.erase(iter3);
					}
					else
						iter3++;
				}
				for(particleIter = particles.begin(); particleIter!=particles.end();)
				{
					(*particleIter)->deactivate();
					if(!(*particleIter)->getActivated() && (*particleIter)->getVelX() == 0 && (*particleIter)->getVelY() == 0)
					{
						deactivatedParticles.push_back((*particleIter));
						particleIter = particles.erase(particleIter);
					}
					else
						particleIter++;
				}
			}
			maxParticles();
			//Move cam
			al_identity_transform(&camera);
			al_translate_transform(&camera, -global::camX, -global::camY);
			al_use_transform(&camera);

			global::camX_prev=global::camX;
			global::camY_prev=global::camY;
			//Reset keys
			for(int i=0; i<8; i++)
			{
				keys_pressed[i]=false;
				//keys_released[i]=false;
			}
		}

		//=====================================================================================================================
		//RENDER
		//=====================================================================================================================
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

			//BEGIN PROJECT RENDER=============================================================================================
			sort(staticObjects.begin(),staticObjects.end(), sortFunction);
			sort(dynamicObjects.begin(),dynamicObjects.end(), sortFunction);
			for(r_iter3 = staticObjects.rbegin(); r_iter3!=staticObjects.rend(); r_iter3++)
				(*r_iter3)->draw();
			for(r_iter = dynamicObjects.rbegin(); r_iter!=dynamicObjects.rend(); r_iter++)
				(*r_iter)->draw();
			for(particleIter = particles.begin(); particleIter!=particles.end(); particleIter++)
				(*particleIter)->draw();
			al_draw_textf(FontManager::GetInstance().getFont(0), al_map_rgb(255,0,255),global::camX+5,global::camY+5,0,"FPS: %i", gameFPS);
			if(d_object_exists(global::PLAYER))
			{
				al_draw_textf(FontManager::GetInstance().getFont(0), al_map_rgb(255,0,255),global::camX+5,global::camY+25,0,"X: %f\tY: %f", player->getX(), player->getY());
				al_draw_textf(FontManager::GetInstance().getFont(0), al_map_rgb(255,0,255),global::camX+5,global::camY+45,0,"Gravity: %f", player->getGravity());
				al_draw_textf(FontManager::GetInstance().getFont(0), al_map_rgb(255,0,255),global::camX+5,global::camY+65,0,"velY: %f\tvelX: %f", player->getVelY(), player->getVelX());
	
			}
			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(192,192,192));
		}
	}

	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================
	for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); )
	{
		(*iter)->destroy();
		delete (*iter);
		iter = dynamicObjects.erase(iter);
	}
	for(iter = deactivatedDynamicObjects.begin(); iter!=deactivatedDynamicObjects.end();)
	{
		(*iter)->destroy();
		delete(*iter);
		iter = deactivatedDynamicObjects.erase(iter);
	}
	for(iter3 = staticObjects.begin(); iter3!=staticObjects.end(); )
	{
		(*iter3)->destroy();
		delete (*iter3);
		iter3 = staticObjects.erase(iter3);
	}
	for(iter3 = deactivatedStaticObjects.begin(); iter3!=deactivatedStaticObjects.end(); )
	{
		(*iter3)->destroy();
		delete (*iter3);
		iter3 = deactivatedStaticObjects.erase(iter3);
	}
	for(particleIter = particles.begin(); particleIter !=particles.end();)
	{
		(*particleIter)->destroy();
		delete (*particleIter);
		particleIter = particles.erase(particleIter);
	}
	for(particleIter = deactivatedParticles.begin(); particleIter != deactivatedParticles.end(); )
	{
		(*particleIter)->destroy();
		delete(*particleIter);
		particleIter = deactivatedParticles.erase(particleIter);
	}

	FontManager::GetInstance().clean();
	SoundManager::GetInstance().clean();
	ImageManager::getInstance().clean();

	//SHELL OBJECTS=================================
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

//Checks if there is no object blocking the player.
bool __cdecl placeFree(float x, float y)
{
	for(iter3 = staticObjects.begin(); iter3 != staticObjects.end(); iter3++)
	{		
		if((*iter3)->getID() != global::WALL) continue;
		if(x + player->getBoundRight() >= (*iter3)->getX() - (*iter3)->getBoundLeft() &&
			x - player->getBoundLeft() <= (*iter3)->getX() + (*iter3)->getBoundRight() &&
			y + player->getBoundDown() -1 > (*iter3)->getY() - (*iter3)->getBoundUp() &&
			y - player->getBoundUp() +1 < (*iter3)->getY() + (*iter3)->getBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	for(iter2 = dynamicObjects.begin(); iter2 != dynamicObjects.end(); iter2++)
	{		
		if((*iter2)->getID() != global::WALL_FADE && (*iter2)->getID()!= global::SAVE) continue;
		if(x + player->getBoundRight() >= (*iter2)->getX() - (*iter2)->getBoundLeft() &&
			x - player->getBoundLeft() <= (*iter2)->getX() + (*iter2)->getBoundRight() &&
			y + player->getBoundDown() -1 > (*iter2)->getY() - (*iter2)->getBoundUp() &&
			y - player->getBoundUp() +1 < (*iter2)->getY() + (*iter2)->getBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	return true;
}


//Check if dynamic object with ID exists
bool d_object_exists(int ID)
{
	for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
	{
		if((*iter)->getID() == ID)
			return true;
	}
	for(iter = deactivatedDynamicObjects.begin(); iter!=deactivatedDynamicObjects.end(); iter++)
	{
		if((*iter)->getID() == ID)
			return true;
	}
	return false;
}

void __cdecl createObject(int ID,int x,int y)
{
	if(ID==0)
	{
		wall = new Wall();
		wall->init(x,y);
		staticObjects.push_back(wall);
	}
	else if(ID==1)
	{
		spike_up = new Spike_Up();
		spike_up->init(x,y);
		staticObjects.push_back(spike_up);
	}
	else if(ID==2)
	{
		spike_down = new Spike_Down();
		spike_down->init(x,y);
		staticObjects.push_back(spike_down);
	}
	else if(ID==3)
	{
		spike_left = new Spike_Left();
		spike_left->init(x,y);
		staticObjects.push_back(spike_left);
	}
	else if(ID==4)
	{
		spike_right = new Spike_Right();
		spike_right->init(x,y);
		staticObjects.push_back(spike_right);
	}
	else if(ID==5)
	{
		wall_fade = new Wall_Fade();
		wall_fade->init(x,y);
		dynamicObjects.push_back(wall_fade);
	}
	else if(ID==6)
	{
		wall_fake = new Wall_Fake();
		wall_fake->init(x,y);
		staticObjects.push_back(wall_fake);
	}
	else if(ID==7)
	{
		obj_trigger_double_spike = new obj_Trigger_Double_Spike(&create_obj_Double_Spike_Down, &create_obj_Double_Spike_Up);
		obj_trigger_double_spike->init(x,y);
		dynamicObjects.push_back(obj_trigger_double_spike);
	}
	else if(ID==8)
	{
		obj_saw = new obj_Saw();
		obj_saw->init(x,y);
		dynamicObjects.push_back(obj_saw);
	}
	else if(ID==9)
	{
		obj_saw_small = new obj_Saw_Small();
		obj_saw_small->init(x,y);
		dynamicObjects.push_back(obj_saw_small);
	}
	else if(ID==10)
	{
		obj_saw_bar = new obj_Saw_Bar(&createObjectWithPointer);
		obj_saw_bar->init(x,y);
		dynamicObjects.push_back(obj_saw_bar);
	}
	else if(ID==96)
	{
		save = new Save(&createObject);
		save->init(x,y,0);
		dynamicObjects.push_back(save);
	}
	else if(ID==97)
	{
		save = new Save(&createObject);
		save->init(x,y,1);
		dynamicObjects.push_back(save);
	}
	else if(ID==98)
	{
		save = new Save(&createObject);
		save->init(x,y,2);
		dynamicObjects.push_back(save);
	}
	else if(ID==99)
	{
		player = new Player(&placeFree, &createObject, &reserveSpace);
		player->init(x,y);
		dynamicObjects.push_back(player);
	}

	else if(ID==100)
	{
		blood = new Blood();
		blood->init(x,y,rand()%360,(((float)rand()/(float)RAND_MAX)*30.0));
		particles.push_back(blood);
	}

}

GameObject* __cdecl createObjectWithPointer(int ID,int x,int y)
{
	if(ID==0)
	{
		wall = new Wall();
		wall->init(x,y);
		staticObjects.push_back(wall);
		return wall;
	}
	else if(ID==1)
	{
		spike_up = new Spike_Up();
		spike_up->init(x,y);
		staticObjects.push_back(spike_up);
		return spike_up;
	}
	else if(ID==2)
	{
		spike_down = new Spike_Down();
		spike_down->init(x,y);
		staticObjects.push_back(spike_down);
		return spike_down;
	}
	else if(ID==3)
	{
		spike_left = new Spike_Left();
		spike_left->init(x,y);
		staticObjects.push_back(spike_left);
		return spike_left;
	}
	else if(ID==4)
	{
		spike_right = new Spike_Right();
		spike_right->init(x,y);
		staticObjects.push_back(spike_right);
		return spike_right;
	}
	else if(ID==5)
	{
		wall_fade = new Wall_Fade();
		wall_fade->init(x,y);
		dynamicObjects.push_back(wall_fade);
		return wall_fade;
	}
	else if(ID==6)
	{
		wall_fake = new Wall_Fake();
		wall_fake->init(x,y);
		staticObjects.push_back(wall_fake);
		return wall_fake;
	}
	else if(ID==7)
	{
		obj_trigger_double_spike = new obj_Trigger_Double_Spike(&create_obj_Double_Spike_Down,&create_obj_Double_Spike_Up);
		obj_trigger_double_spike->init(x,y);
		dynamicObjects.push_back(obj_trigger_double_spike);
		return obj_trigger_double_spike;
	}
	else if(ID==8)
	{
		obj_saw = new obj_Saw();
		obj_saw->init(x,y);
		dynamicObjects.push_back(obj_saw);
		return obj_saw;
	}
	else if(ID==9)
	{
		obj_saw_small = new obj_Saw_Small();
		obj_saw_small->init(x,y);
		dynamicObjects.push_back(obj_saw_small);
		return obj_saw_small;
	}
	else if(ID==10)
	{
		obj_saw_bar = new obj_Saw_Bar(&createObjectWithPointer);
		obj_saw_bar->init(x,y);
		dynamicObjects.push_back(obj_saw_bar);
		return obj_saw_bar;
	}
	else if(ID==96)
	{
		save = new Save(&createObject);
		save->init(x,y,0);
		dynamicObjects.push_back(save);
		return save;
	}
	else if(ID==97)
	{
		save = new Save(&createObject);
		save->init(x,y,1);
		dynamicObjects.push_back(save);
		return save;
	}
	else if(ID==98)
	{
		save = new Save(&createObject);
		save->init(x,y,2);
		dynamicObjects.push_back(save);
		return save;
	}
	else if(ID==99)
	{
		player = new Player(&placeFree, &createObject, &reserveSpace);
		player->init(x,y);
		dynamicObjects.push_back(player);
		return player;
	}

	else if(ID==100)
	{
		blood = new Blood();
		blood->init(x,y,rand()%360,(((float)rand()/(float)RAND_MAX)*30.0));
		particles.push_back(blood);
		return blood;
	}
	else if(ID==101)
	{
		obj_double_spike_down = new obj_Double_Spike_Down;
		obj_double_spike_down->init(x,y);
		dynamicObjects.push_back(obj_double_spike_down);
		return obj_double_spike_down;
	}
	return NULL;
}

obj_Double_Spike_Down* __cdecl create_obj_Double_Spike_Down(float x,float y)
{
	obj_double_spike_down = new obj_Double_Spike_Down;
	obj_double_spike_down->init(x,y);
	dynamicObjects.push_back(obj_double_spike_down);
	return obj_double_spike_down;
}
obj_Double_Spike_Up* __cdecl create_obj_Double_Spike_Up(float x,float y)
{
	obj_double_spike_up = new obj_Double_Spike_Up;
	obj_double_spike_up->init(x,y);
	dynamicObjects.push_back(obj_double_spike_up);
	return obj_double_spike_up;
}

void __cdecl deleteDynamicObjects(void)
{
	for(iter=dynamicObjects.begin();iter!=dynamicObjects.end();)
	{
		(*iter)->destroy();
		delete (*iter);
		iter = dynamicObjects.erase(iter);
	}
	for(iter=deactivatedDynamicObjects.begin();iter!=deactivatedDynamicObjects.end();)
	{
		(*iter)->destroy();
		delete (*iter);
		iter = deactivatedDynamicObjects.erase(iter);
	}
}

void maxParticles()
{
	while(particles.size()>1500)
	{
		particleIter = particles.begin();
		(*particleIter)->destroy();
		delete (*particleIter);
		particleIter=particles.erase(particleIter);
	}
	while(deactivatedParticles.size()>5000)
	{
		particleIter = deactivatedParticles.begin();
		(*particleIter)->destroy();
		delete (*particleIter);
		particleIter=deactivatedParticles.erase(particleIter);
	}
}

void __cdecl reserveSpace(char ID, int size)
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