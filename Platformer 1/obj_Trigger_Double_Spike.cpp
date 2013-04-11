#include "obj_Trigger_Double_Spike.h"


obj_Trigger_Double_Spike::obj_Trigger_Double_Spike(obj_Double_Spike_Down*(*create_obj_Double_Spike_Down)(float x,float y),obj_Double_Spike_Up*(*create_obj_Double_Spike_Up)(float x,float y))
{
	setID(TRIGGER_DOUBLE_SPIKE);
	obj_Trigger_Double_Spike::create_obj_Double_Spike_Down = create_obj_Double_Spike_Down;
	obj_Trigger_Double_Spike::create_obj_Double_Spike_Up = create_obj_Double_Spike_Up;
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


void obj_Trigger_Double_Spike::init(float x, float y)
{
	image = NULL;
	DynamicObject::init(x,y,0,0,getID(),0);
	down = create_obj_Double_Spike_Down(x,y);
	up = create_obj_Double_Spike_Up(x,y+96);
}

void obj_Trigger_Double_Spike::update(bool *keys, bool *keys_pressed)
{

}

void obj_Trigger_Double_Spike::draw()
{
}

void obj_Trigger_Double_Spike::destroy()
{
}

void obj_Trigger_Double_Spike::Collided(GameObject *other)
{
	if(other->getID() == PLAYER)
	{
		down->activate();
		up->activate();
	}
}

