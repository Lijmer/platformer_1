#pragma once
#include "Spike.h"
class Spike_Left : public Spike
{
public:
	Spike_Left(void);
	void init(float x, float y);
	void draw();
	void destroy();
};

