#include "obj_Trigger_Double_Spike.h"


obj_Trigger_Double_Spike::obj_Trigger_Double_Spike(obj_Double_Spike_Down*(*Create_obj_Double_Spike_Down)(float x,float y),obj_Double_Spike_Up*(*Create_obj_Double_Spike_Up)(float x,float y))
{
	SetID(TRIGGER_DOUBLE_SPIKE);
	obj_Trigger_Double_Spike::Create_obj_Double_Spike_Down = Create_obj_Double_Spike_Down;
	obj_Trigger_Double_Spike::Create_obj_Double_Spike_Up = Create_obj_Double_Spike_Up;
	boundUp = 0;
	boundDown = 128;
	boundLeft = 0;
	boundRight = 32;
	down=NULL;
	up=NULL;
}


obj_Trigger_Double_Spike::~obj_Trigger_Double_Spike(void)
{
}


void obj_Trigger_Double_Spike::Init(float x, float y)
{
	image = NULL;
	DynamicObject::Init(x,y,0,0,GetID(),0);
	down = Create_obj_Double_Spike_Down(x,y);
	up = Create_obj_Double_Spike_Up(x,y+96);
}

void obj_Trigger_Double_Spike::Update()
{

}

void obj_Trigger_Double_Spike::Draw()
{
}

void obj_Trigger_Double_Spike::Destroy()
{
}

void obj_Trigger_Double_Spike::Collided(GameObject *other)
{
	if(other->GetID() == PLAYER)
	{
		down->Activate();
		up->Activate();
	}
}

