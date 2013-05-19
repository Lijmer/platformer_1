#pragma once
#include "GameObject.h"
class StaticObject : public GameObject 
{
public:
	StaticObject(void);
	virtual ~StaticObject(void);

	void Init(float x, float y);
	void virtual Draw();
	void virtual Destroy();

	//what to do when collided
	//void virtual Collided(StaticObject *other);
	
};

