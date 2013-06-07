#pragma once
#include "DynamicObject.h"
class StaticObject;
class Save : public DynamicObject
{
public:
	Save();
	~Save();
	void Init(float x,float y,char difficulty);
	void Update();
	void Draw();
	void Collided(GameObject *other);

private:
	bool active;
	bool visible;
	int count;
	StaticObject *wall;
};
