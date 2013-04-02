#pragma once
#include "StaticObject.h"
class Spike : public StaticObject
{
public:
	Spike(void);

	void virtual draw();
	void virtual destroy();
};

