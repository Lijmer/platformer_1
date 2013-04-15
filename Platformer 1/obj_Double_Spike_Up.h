#pragma once
#include "DynamicObject.h"
#include "ImageManager.h"
class obj_Double_Spike_Up : public DynamicObject
{
public:
	obj_Double_Spike_Up(void);
	~obj_Double_Spike_Up(void);

	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();
	
	void Collided(GameObject *other);

	void Activate();

private:
	float startY;

};

