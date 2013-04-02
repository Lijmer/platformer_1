#pragma once
#include "GameObject.h"
class StaticObject : public GameObject 
{
public:
	StaticObject(void);

	void init(float x, float y);
	void virtual draw();
	void virtual destroy();

	//what to do when collided
	//void virtual Collided(StaticObject *other);
	
};

