#pragma once
#include "dynamicObject.h"
#include "obj_Double_Spike_Down.h"
#include "obj_Double_Spike_Up.h"
class obj_Trigger_Double_Spike : public DynamicObject
{
public:
	obj_Trigger_Double_Spike(void);
	~obj_Trigger_Double_Spike(void);

	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);

private:
	obj_Double_Spike_Down *down;
	obj_Double_Spike_Up *up;
};

