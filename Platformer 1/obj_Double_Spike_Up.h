#pragma once
#include "DynamicObject.h"
#include "ImageManager.h"
class obj_Double_Spike_Up : public DynamicObject
{
public:
	obj_Double_Spike_Up(void);
	~obj_Double_Spike_Up(void);

	void init(float x, float y);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();
	
	void Collided(GameObject *other);

	void activate();

private:
	float startY;

};

