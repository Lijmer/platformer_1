#pragma once
#include "Spike.h"
class Spike_Up : public Spike
{
public:
	Spike_Up(void);
	void Spike_Up::init(float x, float y);
	void draw();
	void destroy();

};