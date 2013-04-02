#pragma once
#include "Spike.h"
class Spike_Down : public Spike
{
public:
	Spike_Down(void);
	void Spike_Down::init(float x, float y);
	void draw();
	void destroy();
};

