#pragma once
#include "Spike.h"
class Spike_Down : public Spike
{
public:
	Spike_Down(void);
	void Spike_Down::Init(float x, float y);
	void Draw();
	void Destroy();
};

