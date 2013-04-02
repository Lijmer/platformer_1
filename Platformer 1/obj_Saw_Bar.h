#pragma once
#include "DynamicObject.h"
class obj_Saw_Bar : public DynamicObject
{
public:
	obj_Saw_Bar(GameObject*(*createObjectWithPointer)(int ID, int x, int y));
	~obj_Saw_Bar(void);

	void init(float x, float y);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();

private:
	GameObject*(*createObjectWithPointer)(int ID, int x, int y);
	float direction;
	GameObject *saw;
};

