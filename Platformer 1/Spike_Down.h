#pragma once
#include "Spike.h"
class Spike_Down : public Spike
{
public:
	Spike_Down(void);
	void Init(float x, float y);
	void Destroy();
};

