#include "dynamicObject.h"
#include "obj_Double_Spike_Down.h"
#include "obj_Double_Spike_Up.h"
#pragma once 
class obj_Trigger_Double_Spike : public DynamicObject
{
public:
	obj_Trigger_Double_Spike(obj_Double_Spike_Down*(*create_obj_Double_Spike_Down)(float x,float y),obj_Double_Spike_Up*(*create_obj_Double_Spike_Up)(float x,float y));
	~obj_Trigger_Double_Spike(void);

	void init(float x, float y);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();
	void Collided(GameObject *other);

private:
	obj_Double_Spike_Down*(*create_obj_Double_Spike_Down)(float x,float y);
	obj_Double_Spike_Up*(*create_obj_Double_Spike_Up)(float x,float y);
	obj_Double_Spike_Down *down;
	obj_Double_Spike_Up *up;
};

