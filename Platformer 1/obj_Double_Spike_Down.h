#pragma once
#include "DynamicObject.h"
class obj_Double_Spike_Down : public DynamicObject
{
public:
	obj_Double_Spike_Down(void);
	~obj_Double_Spike_Down(void);

	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);

	void Activate();

private:
	float startY;
};