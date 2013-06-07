#pragma once
#include "DynamicObject.h"
class StaticObject;
class obj_Saw_Bar : public DynamicObject
{
public:
	obj_Saw_Bar();
	~obj_Saw_Bar(void);

	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();

private:
	float direction;
	GameObject *saw;
	StaticObject *wall;
};

