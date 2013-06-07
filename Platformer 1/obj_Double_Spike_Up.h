#pragma once
#include "DynamicObject.h"
class obj_Double_Spike_Up : public DynamicObject
{
public:
	obj_Double_Spike_Up(void);
	~obj_Double_Spike_Up(void);

	void Init(float x, float y);
	void Update();

	void Activate();

private:
	float startY;

};

