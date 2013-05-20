#pragma region Includes
#include "GameObjectManager.h"

#include <algorithm>
#include "globals.h"
#include "FontManager.h"

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
#include "obj_Treadmill_Left_Begin.h"
#include "obj_Treadmill_Left.h"
#include "obj_Treadmill_Left_End.h"
#include "obj_Treadmill_Right_Begin.h"
#include "obj_Treadmill_Right.h"
#include "obj_Treadmill_Right_end.h"

#include "Blood.h"
#include "Blood_Head.h"
#include "Blood_Torso.h"

#include "obj_Menu_Button.h"
#include "obj_Menu_Initer.h"

#pragma endregion
//Public
GameObjectManager::GameObjectManager(void)
{
	player = NULL;
	bullet = NULL;
	wall = NULL;
	wall_fake = NULL;
	wall_fade = NULL;
	spike_up = NULL;
	spike_down = NULL;
	spike_left = NULL;
	spike_right = NULL;
	save = NULL;
	obj_trigger_double_spike = NULL;
	obj_double_spike_down = NULL;
	obj_double_spike_up = NULL;
	obj_saw = NULL;
	obj_saw_small = NULL;
	obj_saw_bar = NULL;
	obj_platform_vertical = NULL;
	obj_platform_horizontal = NULL;
	obj_treadmill_left_begin = NULL;
	obj_treadmill_left = NULL;
	obj_treadmill_left_end = NULL;
	obj_treadmill_right_begin = NULL;
	obj_treadmill_right = NULL;
	obj_treadmill_right_end = NULL;

	blood = NULL;
	blood_head = NULL;
	blood_torso = NULL;

	staticCanvas = NULL;
	stillParticleCanvas = NULL;


	stillParticlesSize = stillParticles.size();
}
GameObjectManager::~GameObjectManager(void)
{
	std::vector<DynamicObject *>::iterator iter;
	std::vector<StaticObject *>::iterator iter2;
	std::vector<Particle *>::const_iterator particleIter;
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
	for(iter2 = staticObjects.begin(); iter2!=staticObjects.end(); )
	{
		(*iter2)->Destroy();
		delete (*iter2);
		iter2 = staticObjects.erase(iter2);
	}
	for(iter2 = deactivatedStaticObjects.begin(); iter2!=deactivatedStaticObjects.end(); )
	{
		(*iter2)->Destroy();
		delete (*iter2);
		iter2 = deactivatedStaticObjects.erase(iter2);
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
}

GameObjectManager& GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return instance;
}

void GameObjectManager::Init()
{
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	staticCanvas = al_create_bitmap(1024,768);
	stillParticleCanvas = al_create_bitmap(1024,768);
}

void GameObjectManager::TimerEvent()
{
	Update();
	Collisions();
	Clean();
	ActivateDeactivate();
	MotionlessParticles();
}
void GameObjectManager::Draw()
{
	std::vector<DynamicObject *>::reverse_iterator r_iter;
	std::vector<Particle *>::iterator particleIter;
	//Draw static objects
	al_draw_bitmap(staticCanvas,0,0,0);
			
	//Draw dynamic objects
	for(r_iter = dynamicObjects.rbegin(); r_iter!=dynamicObjects.rend(); r_iter++)
		(*r_iter)->Draw();

	//Draw Particles
	al_draw_bitmap(stillParticleCanvas,0,0,0);
	for(particleIter = stillParticlesBuffer.begin(); particleIter!=stillParticlesBuffer.end(); particleIter++)
		(*particleIter)->Draw();
	for(particleIter = particles.begin(); particleIter!=particles.end(); particleIter++)
		(*particleIter)->Draw();

	std::vector<obj_Menu_Button*>::iterator btnIter;
	for(btnIter = buttons.begin(); btnIter!=buttons.end(); btnIter++)
	{
		(*btnIter)->Draw();
	}
	/*
	if(D_object_exists(PLAYER))
	{
		al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,25,0,"X: %f\tY: %f", player->GetX(), player->GetY());
		al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,45,0,"Gravity: %f", player->GetGravity());
		al_draw_textf(FontManager::GetInstance().GetFont(0), al_map_rgb(255,0,255),5,65,0,"velY: %f\tvelX: %f", player->GetVelY(), player->GetVelX());
	}
	*/
}

bool GameObjectManager::PlaceFree(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize)
{
	std::vector<StaticObject *>::iterator iter;
	std::vector<DynamicObject *>::iterator iter2;
	for(iter = staticObjects.begin(); iter != staticObjects.end(); iter++)
	{		
		if((*iter)->GetID() != WALL) continue;
		if(x + boundRight  > (*iter)->GetX() - (*iter)->GetBoundLeft() &&
			x - boundLeft  < (*iter)->GetX() + (*iter)->GetBoundRight() &&
			y + boundDown  > (*iter)->GetY() - (*iter)->GetBoundUp() &&
			y - boundUp  < (*iter)->GetY() + (*iter)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	for(iter2 = dynamicObjects.begin(); iter2 != dynamicObjects.end(); iter2++)
	{
		bool cont = true;

		for(int i=0; i<exceptionIDsSize; i++)
		{
			if((*iter2)->GetID() == exceptionIDs[i])
			{
				cont = false;
				break;
			}
		}

		if(cont || instanceID == (*iter2)->GetInstanceID())
			continue;

		if(x + boundRight  > (*iter2)->GetX() - (*iter2)->GetBoundLeft() &&
			x - boundLeft  < (*iter2)->GetX() + (*iter2)->GetBoundRight() &&
			y + boundDown  > (*iter2)->GetY() - (*iter2)->GetBoundUp() &&
			y - boundUp  < (*iter2)->GetY() + (*iter2)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	return true;
}
bool GameObjectManager::PlaceMeeting(int otherID, float x, float y, DynamicObject *object)
{
	std::vector<DynamicObject *>::iterator iter;
	float oldX = object->GetX();
	float oldY = object->GetY();

	object->SetX(x);
	object->SetY(y);

	for(iter = dynamicObjects.begin(); iter != dynamicObjects.end(); iter++)
	{
		if((*iter)->GetInstanceID() == object->GetInstanceID())
			continue;
		if((*iter)->GetID() != otherID)
			continue;
				
		if(object->CheckCollision(*iter))
		{
			object->SetX(oldX);
			object->SetY(oldY);
			return true;
		}
	}
	object->SetX(oldX);
	object->SetY(oldY);
	return false;
}
bool GameObjectManager::PlaceMeeting(int otherID, float x, float y, DynamicObject *object, GameObject *&other)
{
	std::vector<DynamicObject *>::iterator iter;
	float oldX = object->GetX();
	float oldY = object->GetY();

	object->SetX(x);
	object->SetY(y);

	for(iter = dynamicObjects.begin(); iter != dynamicObjects.end(); iter++)
	{
		if((*iter)->GetInstanceID() == object->GetInstanceID())
			continue;
		if((*iter)->GetID() != otherID)
			continue;
				
		if(object->CheckCollision(*iter))
		{
			object->SetX(oldX);
			object->SetY(oldY);
			other = (*iter);
			return true;
		}
	}
	object->SetX(oldX);
	object->SetY(oldY);
	return false;
}

bool GameObjectManager::D_object_exists(int ID)
{
	std::vector<DynamicObject*>::iterator iter;
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

GameObject* GameObjectManager::CreateObject(int ID,int x,int y)
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
		pendingDynamicObjects.push_back(wall_fade);
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
		obj_trigger_double_spike = new obj_Trigger_Double_Spike();
		obj_trigger_double_spike->Init(x,y);
		pendingDynamicObjects.push_back(obj_trigger_double_spike);
		return obj_trigger_double_spike;
	}
	else if(ID==8)
	{
		obj_saw = new obj_Saw();
		obj_saw->Init(x,y);
		pendingDynamicObjects.push_back(obj_saw);
		return obj_saw;
	}
	else if(ID==9)
	{
		obj_saw_small = new obj_Saw_Small();
		obj_saw_small->Init(x,y);
		pendingDynamicObjects.push_back(obj_saw_small);
		return obj_saw_small;
	}
	else if(ID==10)
	{
		obj_saw_bar = new obj_Saw_Bar();
		obj_saw_bar->Init(x,y);
		pendingDynamicObjects.push_back(obj_saw_bar);
		return obj_saw_bar;
	}
	else if(ID==11)
	{
		obj_platform_vertical = new obj_Platform_Vertical();
		obj_platform_vertical->Init(x,y,0,-2);
		pendingDynamicObjects.push_back(obj_platform_vertical);
		return obj_platform_vertical;
	}
	else if(ID==12)
	{
		obj_platform_horizontal = new obj_Platform_Horizontal();
		obj_platform_horizontal->Init(x,y,2,0);
		pendingDynamicObjects.push_back(obj_platform_horizontal);
		return obj_platform_horizontal;
	}
	else if(ID==13)
	{
		obj_treadmill_left_begin = new obj_Treadmill_Left_Begin();
		obj_treadmill_left_begin->Init(x,y,-1,0);
		pendingDynamicObjects.push_back(obj_treadmill_left_begin);
		return obj_treadmill_left_begin;
	}
	else if(ID==14)
	{
		obj_treadmill_left = new obj_Treadmill_Left();
		obj_treadmill_left->Init(x,y,-1,0);
		pendingDynamicObjects.push_back(obj_treadmill_left);
		return obj_treadmill_left;
	}
	else if(ID==15)
	{
		obj_treadmill_left_end = new obj_Treadmill_Left_End();
		obj_treadmill_left_end->Init(x,y,-1,0);
		pendingDynamicObjects.push_back(obj_treadmill_left_end);
		return obj_treadmill_left_end;
	}
	else if(ID==16)
	{
		obj_treadmill_right_begin = new obj_Treadmill_Right_Begin();
		obj_treadmill_right_begin->Init(x,y,1,0);
		pendingDynamicObjects.push_back(obj_treadmill_right_begin);
		return obj_treadmill_right_begin;
	}
	else if(ID==17)
	{
		obj_treadmill_right = new obj_Treadmill_Right();
		obj_treadmill_right->Init(x,y,1,0);
		pendingDynamicObjects.push_back(obj_treadmill_right);
		return obj_treadmill_right;
	}
	else if(ID==18)
	{
		obj_treadmill_right_end = new obj_Treadmill_Right_End();
		obj_treadmill_right_end->Init(x,y,1,0);
		pendingDynamicObjects.push_back(obj_treadmill_right_end);
		return obj_treadmill_right_end;
	}
	else if(ID==96)
	{
		save = new Save();
		save->Init(x,y,0);
		pendingDynamicObjects.push_back(save);
		return save;
	}
	else if(ID==97)
	{
		save = new Save();
		save->Init(x,y,1);
		pendingDynamicObjects.push_back(save);
		return save;
	}
	else if(ID==98)
	{
		save = new Save();
		save->Init(x,y,2);
		pendingDynamicObjects.push_back(save);
		return save;
	}
	else if(ID==99)
	{
		player = new Player();
		player->Init(x,y);
		pendingDynamicObjects.push_back(player);
		return player;
	}

	else if(ID==100)
	{
		blood = new Blood();
		blood->Init(x,y,rand()%360,(((float)rand()/(float)RAND_MAX)*30.0));
		particles.push_back(blood);
		return NULL;
	}
	else if(ID==101)
	{
		blood_head = new Blood_Head();
		blood_head->Init(x,y,270,10);
		particles.push_back(blood_head);
		return NULL;
	}
	else if(ID==102)
	{
		blood_torso = new Blood_Torso();
		blood_torso->Init(x,y,rand()%360,((float)rand()/(float)RAND_MAX)*30.0);
		particles.push_back(blood_torso);
		return NULL;
	}
	else if(ID==-2)
	{
		obj_menu_initer = new obj_Menu_Initer;
		obj_menu_initer->Init();
		staticObjects.push_back(obj_menu_initer);
		return obj_menu_initer;
	}
	return NULL;
}
DynamicObject* GameObjectManager::CreateDynamicObject(int ID, float x, float y, float velX, float velY)
{
	if(ID==5)
	{
		wall_fade = new Wall_Fade;
		wall_fade->Init(x,y);
		pendingDynamicObjects.push_back(wall_fade);
		return wall_fade;
	}
	else if(ID==7)
	{
		obj_trigger_double_spike = new obj_Trigger_Double_Spike;
		obj_trigger_double_spike->Init(x,y);
		pendingDynamicObjects.push_back(obj_trigger_double_spike);
		return obj_trigger_double_spike;
	}
	else if(ID==8)
	{
		obj_saw = new obj_Saw;
		obj_saw->Init(x,y);
		pendingDynamicObjects.push_back(obj_saw);
		return obj_saw;
	}
	else if(ID==9)
	{
		obj_saw_small = new obj_Saw_Small;
		obj_saw_small->Init(x,y);
		pendingDynamicObjects.push_back(obj_saw_small);
		return obj_saw;
	}
	else if(ID==10)
	{
		obj_saw_bar = new obj_Saw_Bar;
		obj_saw_bar->Init(x,y);
		pendingDynamicObjects.push_back(obj_saw_bar);
		return obj_saw_bar;
	}
	else if(ID==11)
	{
		obj_platform_vertical = new obj_Platform_Vertical;
		obj_platform_vertical->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_platform_vertical);
		return obj_platform_vertical;
	}
	else if(ID==12)
	{
		obj_platform_horizontal = new obj_Platform_Horizontal;
		obj_platform_horizontal->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_platform_horizontal);
		return obj_platform_horizontal;
	}
	else if(ID==13)
	{
		obj_treadmill_left_begin = new obj_Treadmill_Left_Begin;
		obj_treadmill_left_begin->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_treadmill_left_begin);
		return obj_treadmill_left_begin;
	}
	else if(ID==14)
	{
		obj_treadmill_left = new obj_Treadmill_Left;
		obj_treadmill_left->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_treadmill_left);
		return obj_treadmill_left;
	}
	else if(ID==15)
	{
		obj_treadmill_left_end = new obj_Treadmill_Left_End;
		obj_treadmill_left_end->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_treadmill_left_end);
		return obj_treadmill_left_end;
	}
	else if(ID==16)
	{
		obj_treadmill_right_begin = new obj_Treadmill_Right_Begin;
		obj_treadmill_right_begin->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_treadmill_right_begin);
		return obj_treadmill_right_begin;
	}
	else if(ID==17)
	{
		obj_treadmill_right = new obj_Treadmill_Right;
		obj_treadmill_right->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_treadmill_right);
		return obj_treadmill_right;
	}
	else if(ID==18)
	{
		obj_treadmill_right_end = new obj_Treadmill_Right_End;
		obj_treadmill_right->Init(x,y,velX,velY);
		pendingDynamicObjects.push_back(obj_treadmill_right_end);
		return obj_treadmill_right;
	}
	else if(ID==95)
	{
		bullet = new Bullet;
		bullet->Init(x,y,velX);
		pendingDynamicObjects.push_back(bullet);
		return bullet;
	}
	else if(ID==96)
	{
		save = new Save;
		save->Init(x,y,0);
		pendingDynamicObjects.push_back(save);
		return save;
	}
	else if(ID==97)
	{
		save = new Save;
		save->Init(x,y,1);
		pendingDynamicObjects.push_back(save);
		return save;
	}
	else if(ID==98)
	{
		save = new Save;
		save->Init(x,y,2);
		pendingDynamicObjects.push_back(save);
		return save;
	}
	else if(ID==99)
	{
		player = new Player;
		player->Init(x,y);
		pendingDynamicObjects.push_back(player);
		return player;
	}
	return NULL;
}
obj_Menu_Button* GameObjectManager::CreateButton(float x, float y, int kind)
{
	obj_menu_button = new obj_Menu_Button;
	obj_menu_button->Init(x,y,kind);
	buttons.push_back(obj_menu_button);
	return obj_menu_button;
}

void GameObjectManager::KillPlayer()
{
	if(player!=NULL)
		player->Kill();
}
void GameObjectManager::GetPlayerData(float &x, float &y, float &velX, float &velY, float &gravity, bool &dir, bool &vertical_dir, bool &jump, bool &idle)
{
	if(player!=NULL)
	{
		x = player->GetX();
		y = player->GetY();
		velX = player->GetVelX();
		velY = player->GetVelY();
		gravity = player->GetGravity();
		dir = player->GetDir();
		vertical_dir = player->GetVerticalDir();
		jump = player->GetJump();
		idle = player->GetIdle();
	}
}
void GameObjectManager::SetPlayerData(float x, float y, float velX, float velY, float gravity, bool dir, bool vertical_dir, bool jump, bool idle)
{
	if(player!=NULL)
	{
		player->SetX(x);
		player->SetY(y);
		player->SetVelX(velX);
		player->SetVelY(velY);
		player->SetGravity(gravity);
		player->SetDir(dir);
		player->SetVerticalDir(vertical_dir);
		player->SetJump(jump);
		player->SetIdle(idle);
	}
}

obj_Double_Spike_Down* GameObjectManager::Create_obj_Double_Spike_Down(float x,float y)
{
	obj_double_spike_down = new obj_Double_Spike_Down;
	obj_double_spike_down->Init(x,y);
	dynamicObjects.push_back(obj_double_spike_down);
	return obj_double_spike_down;
}
obj_Double_Spike_Up* GameObjectManager::Create_obj_Double_Spike_Up(float x,float y)
{
	obj_double_spike_up = new obj_Double_Spike_Up;
	obj_double_spike_up->Init(x,y);
	dynamicObjects.push_back(obj_double_spike_up);
	return obj_double_spike_up;
}


void GameObjectManager::ReserveSpace(char ID, int size)
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

void GameObjectManager::DeleteDynamicObjects(void)
{
	std::vector<DynamicObject *>::iterator iter;
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
void GameObjectManager::DeleteStaticObjects(void)
{
	std::vector<StaticObject *>::iterator iter;
	//static
	for(iter = staticObjects.begin(); iter!=staticObjects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = staticObjects.erase(iter);
	}
	for(iter = deactivatedStaticObjects.begin(); iter!=deactivatedStaticObjects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = deactivatedStaticObjects.erase(iter);
	}
}
void GameObjectManager::DeleteParticles(void)
{
	std::vector<Particle *>::iterator pIter;
	for(pIter = particles.begin(); pIter!=particles.end();)
	{
		(*pIter)->Destroy();
		delete (*pIter);
		pIter = particles.erase(pIter);
	}
	for(pIter = stillParticles.begin(); pIter!=stillParticles.end();)
	{
		(*pIter)->Destroy();
		delete (*pIter);
		pIter = stillParticles.erase(pIter);
	}
	for(pIter = stillParticlesBuffer.begin(); pIter!=stillParticlesBuffer.end();)
	{
		(*pIter)->Destroy();
		delete (*pIter);
		pIter = stillParticlesBuffer.erase(pIter);
	}
	for(pIter = deactivatedParticles.begin(); pIter!=deactivatedParticles.end();)
	{
		(*pIter)->Destroy();
		delete (*pIter);
		pIter = deactivatedParticles.erase(pIter);
	}

}
void GameObjectManager::DeleteButtons(void)
{
	std::vector<obj_Menu_Button *>::iterator iter;
	for(iter = buttons.begin(); iter!=buttons.end();)
	{
		delete (*iter);
		iter = buttons.erase(iter);
	}
}
void GameObjectManager::DeleteAllObjects(void)
{
	DeleteDynamicObjects();
	DeleteStaticObjects();
	DeleteParticles();
	DeleteButtons();
}

//Private
inline void GameObjectManager::Update()
{
	std::vector<DynamicObject *>::iterator iter;
	std::vector<Particle *>::iterator particleIter;
	//manage objects
	if(dynamicObjects.capacity() > dynamicObjects.size()+100)
		dynamicObjects.shrink_to_fit();
	sort(dynamicObjects.begin(),dynamicObjects.end(), SortFunction);

	for(iter=dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
		(*iter)->Update();
	for(iter = pendingDynamicObjects.begin(); iter!=pendingDynamicObjects.end();)
	{
		dynamicObjects.push_back(*iter);
		iter = pendingDynamicObjects.erase(iter);
	}
	for(particleIter=particles.begin(); particleIter!=particles.end(); particleIter++)
		(*particleIter)->Update();
}
inline void GameObjectManager::Collisions()
{
	std::vector<DynamicObject *>::iterator iter;
	std::vector<DynamicObject *>::iterator iter2;
	std::vector<StaticObject *>::iterator iter3;
	std::vector<Particle *>::iterator particleIter;
	for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); iter++)
	{
		//Check for collision with other dynamic objects
		for(iter2 = iter+1; iter2!=dynamicObjects.end(); iter2++)
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
}
inline void GameObjectManager::Clean()
{
	std::vector<DynamicObject *>::iterator iter;
	std::vector<StaticObject *>::iterator iter2;
	for(iter = dynamicObjects.begin(); iter!=dynamicObjects.end(); )
	{
		if(!(*iter)->GetAlive())
		{
			//(*iter)->Destroy();
			delete (*iter);
			iter = dynamicObjects.erase(iter);
		}
		else
			++iter;
	}

	for(iter2 = staticObjects.begin(); iter2!=staticObjects.end(); )
	{
		if(!(*iter2)->GetAlive())
		{
			//(*iter)->Destroy();
			delete (*iter2);
			iter2 = staticObjects.erase(iter2);
		}
		else
			++iter2;
	}
}
inline void GameObjectManager::ActivateDeactivate()
{
	std::vector<DynamicObject *>::iterator iter;
	std::vector<StaticObject *>::iterator iter2;
	std::vector<Particle *>::iterator particleIter;
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
		for(iter2 = deactivatedStaticObjects.begin(); iter2!=deactivatedStaticObjects.end();)
		{
			(*iter2)->Activate();
			if((*iter2)->GetActivated())
			{
				staticObjects.push_back((*iter2));
				iter2 = deactivatedStaticObjects.erase(iter2);
			}
			else
				iter2++;
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
		for(iter2 = staticObjects.begin(); iter2!=staticObjects.end();)
		{
			(*iter2)->Deactivate();
			if(!(*iter2)->GetActivated())
			{
				deactivatedStaticObjects.push_back((*iter2));
				iter2 = staticObjects.erase(iter2);
			}
			else
				iter2++;
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
		sort(staticObjects.begin(),staticObjects.end(), &GameObjectManager::SortFunction);
		al_set_target_bitmap(staticCanvas);
		al_clear_to_color(al_map_rgba(0,0,0,0));
		for(iter2 = staticObjects.begin(); iter2!=staticObjects.end(); iter2++)
		{
			(*iter2)->Draw();
		}
	}
}
inline void GameObjectManager::MotionlessParticles()
{
	std::vector<Particle *>::iterator particleIter;
	for(particleIter=particles.begin(); particleIter!=particles.end(); )
	{
		//if((*particleIter)->GetVelX() >= -0.1 && (*particleIter)->GetVelX() <= 0.1 && (*particleIter)->GetVelY() >= -0.1 && (*particleIter)->GetVelY() <= 0.1)
		if((*particleIter)->GetCollided())
		{
			if((*particleIter)->GetX() >= _camX && (*particleIter)->GetX() <= _camX+_SCREEN_WIDTH &&
				(*particleIter)->GetY() >= _camY && (*particleIter)->GetY() <= _camY+_SCREEN_HEIGHT )
			{
				stillParticlesBuffer.push_back((*particleIter));
			}
			else
			{
				deactivatedParticles.push_back((*particleIter));
			}
			particleIter = particles.erase(particleIter);
		}
		else if((*particleIter)->GetX() < _camX || (*particleIter)->GetX() > _camX+_SCREEN_WIDTH ||
				(*particleIter)->GetY() < _camY || (*particleIter)->GetY() > _camY+_SCREEN_HEIGHT )
		{
			delete (*particleIter);
			particleIter = particles.erase(particleIter);
		}
		else
			particleIter++;
	}
	if(stillParticlesBuffer.size() >= 100)
	{
		for(particleIter = stillParticlesBuffer.begin(); particleIter!=stillParticlesBuffer.end(); )
		{
			stillParticles.push_back((*particleIter));
			particleIter = stillParticlesBuffer.erase(particleIter);
		}
	}
	//If the size of the stillParticle vector has changed
	if(stillParticlesSize != stillParticles.size())
	{
		al_set_target_bitmap(stillParticleCanvas);
		al_clear_to_color(al_map_rgba(0,0,0,0));
		for(particleIter = stillParticles.begin(); particleIter!=stillParticles.end(); particleIter++)
		{
			//if((*particleIter)->GetX() >= _camX && (*particleIter)->GetX() <= _camX + _SCREEN_WIDTH &&
			//	(*particleIter)->GetY() >= _camY && (*particleIter)->GetY() <= _camY + _SCREEN_HEIGHT)
			(*particleIter)->Draw();
		}
	}
	stillParticlesSize = stillParticles.size();
}
inline void GameObjectManager::UpdateButtons()
{
	std::vector<obj_Menu_Button *>::iterator iter;
	for(iter = buttons.begin(); iter!=buttons.end(); iter++)
	{
		(*iter)->Update();
	}
	if(_keys_pressed[UP])
		obj_Menu_Button::PreviousButton();
	if(_keys_pressed[DOWN])
		obj_Menu_Button::NextButton();
	if(_keys_pressed[ENTER])
	{
		buttons[obj_Menu_Button::GetSelectedButton()]->Execute();
	}

}

inline int GameObjectManager::SortFunction(GameObject *i, GameObject *j)
{
	return (i->GetDepth()<j->GetDepth());
}
