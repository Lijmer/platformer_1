#pragma once
#include "dynamicobject.h"
class Save : public DynamicObject
{
public:
	Save(void(*CreateObject)(int ID, int x, int y));
	void Init(float x,float y,char difficulty);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);

private:
	bool active;
	int count;

	void(*CreateObject)(int ID, int x, int y);
};

