#pragma once
#include "Spike.h"
class Spike_Up : public Spike
{
public:
	Spike_Up(void);
	void Spike_Up::Init(float x, float y);
	void Draw();
	void Destroy();

};