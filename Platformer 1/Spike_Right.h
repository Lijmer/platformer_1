#pragma once
#include "Spike.h"
class Spike_Right : public Spike
{
public:
	Spike_Right(void);
	void init(float x, float y);
	void draw();
	void destroy();
};

