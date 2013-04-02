#pragma once
#include "dynamicobject.h"
class Save : public DynamicObject
{
public:
	Save(void(*createObject)(int ID, int x, int y));
	void init(float x,float y,char difficulty);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();
	void Collided(GameObject *other);

private:
	bool active;
	int count;

	void(*createObject)(int ID, int x, int y);
};

