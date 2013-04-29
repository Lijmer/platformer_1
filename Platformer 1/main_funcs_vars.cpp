#include "main_funcs_vars.h"

#pragma region variables

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
obj_Treadmill_Left_Begin *obj_treadmill_left_begin = NULL;
obj_Treadmill_Left *obj_treadmill_left = NULL;
obj_Treadmill_Left_End *obj_treadmill_left_end = NULL;
obj_Treadmill_Right_Begin *obj_treadmill_right_begin = NULL;
obj_Treadmill_Right *obj_treadmill_right = NULL;
obj_Treadmill_Right_End *obj_treadmill_right_end = NULL;

Blood *blood = NULL;
Blood_Head *blood_head = NULL;
Blood_Torso *blood_torso = NULL;

#pragma endregion

#pragma region PlaceFree
bool __cdecl PlaceFree(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize)
{
	for(staticPlaceFreeIter = staticObjects.begin(); staticPlaceFreeIter != staticObjects.end(); staticPlaceFreeIter++)
	{		
		if((*staticPlaceFreeIter)->GetID() != WALL) continue;
		if(x + boundRight  > (*staticPlaceFreeIter)->GetX() - (*staticPlaceFreeIter)->GetBoundLeft() &&
			x - boundLeft  < (*staticPlaceFreeIter)->GetX() + (*staticPlaceFreeIter)->GetBoundRight() &&
			y + boundDown  > (*staticPlaceFreeIter)->GetY() - (*staticPlaceFreeIter)->GetBoundUp() &&
			y - boundUp  < (*staticPlaceFreeIter)->GetY() + (*staticPlaceFreeIter)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	for(dynamicPlaceFreeIter = dynamicObjects.begin(); dynamicPlaceFreeIter != dynamicObjects.end(); dynamicPlaceFreeIter++)
	{
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

		if(x + boundRight  > (*dynamicPlaceFreeIter)->GetX() - (*dynamicPlaceFreeIter)->GetBoundLeft() &&
			x - boundLeft  < (*dynamicPlaceFreeIter)->GetX() + (*dynamicPlaceFreeIter)->GetBoundRight() &&
			y + boundDown  > (*dynamicPlaceFreeIter)->GetY() - (*dynamicPlaceFreeIter)->GetBoundUp() &&
			y - boundUp  < (*dynamicPlaceFreeIter)->GetY() + (*dynamicPlaceFreeIter)->GetBoundDown())
		{
			return false;
		}
		else
			continue;
	}
	return true;
}
#pragma endregion Checks if there is no object blocking the player.

bool __cdecl PlaceMeeting(int otherID, float x, float y, DynamicObject *object)
{
	for(dynamicPlaceFreeIter = dynamicObjects.begin(); dynamicPlaceFreeIter != dynamicObjects.end(); dynamicPlaceFreeIter++)
	{
		if((*dynamicPlaceFreeIter)->GetInstanceID() == object->GetInstanceID())
			continue;
		if((*dynamicPlaceFreeIter)->GetID() != otherID)
			continue;
		float oldX = object->GetX();
		float oldY = object->GetY();

		object->SetX(x);
		object->SetY(y);
		
		if(object->CheckCollision(*dynamicPlaceFreeIter))
		{
			object->SetX(oldX);
			object->SetY(oldY);
			return true;
		}
		else
		{
			object->SetX(oldX);
			object->SetY(oldY);
		}
	}
	return false;
}

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
		wall_fade = new Wall_Fade(&PlaceMeeting);
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
	else if(ID==13)
	{
		obj_treadmill_left_begin = new obj_Treadmill_Left_Begin();
		obj_treadmill_left_begin->Init(x,y,-1,0);
		dynamicObjects.push_back(obj_treadmill_left_begin);
		return obj_treadmill_left_begin;
	}
	else if(ID==14)
	{
		obj_treadmill_left = new obj_Treadmill_Left();
		obj_treadmill_left->Init(x,y,-1,0);
		dynamicObjects.push_back(obj_treadmill_left);
		return obj_treadmill_left;
	}
	else if(ID==15)
	{
		obj_treadmill_left_end = new obj_Treadmill_Left_End();
		obj_treadmill_left_end->Init(x,y,-1,0);
		dynamicObjects.push_back(obj_treadmill_left_end);
		return obj_treadmill_left_end;
	}
	else if(ID==16)
	{
		obj_treadmill_right_begin = new obj_Treadmill_Right_Begin();
		obj_treadmill_right_begin->Init(x,y,1,0);
		dynamicObjects.push_back(obj_treadmill_right_begin);
		return obj_treadmill_right_begin;
	}
	else if(ID==17)
	{
		obj_treadmill_right = new obj_Treadmill_Right();
		obj_treadmill_right->Init(x,y,1,0);
		dynamicObjects.push_back(obj_treadmill_right);
		return obj_treadmill_right;
	}
	else if(ID==18)
	{
		obj_treadmill_right_end = new obj_Treadmill_Right_End();
		obj_treadmill_right_end->Init(x,y,1,0);
		dynamicObjects.push_back(obj_treadmill_right_end);
		return obj_treadmill_right_end;
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
		player = new Player(&PlaceFree, &PlaceMeeting, &CreateObject, &ReserveSpace, &Shoot);
		player->Init(x,y);
		dynamicObjects.push_back(player);
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

void StressTest()
{
	for(unsigned int i=0; i<1000000; i++)
	{
		blood = new Blood();
		blood->Init(_SCREEN_WIDTH/2,_SCREEN_HEIGHT/2,rand()%260,((float)rand()/(float)RAND_MAX)*10+5);
		particles.push_back(blood);
	}
}