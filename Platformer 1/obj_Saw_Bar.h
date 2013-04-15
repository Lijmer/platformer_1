#pragma once
#include "DynamicObject.h"
class obj_Saw_Bar : public DynamicObject
{
public:
	obj_Saw_Bar(GameObject*(*CreateObjectWithPointer)(int ID, int x, int y));
	~obj_Saw_Bar(void);

	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();

private:
	GameObject*(*CreateObjectWithPointer)(int ID, int x, int y);
	float direction;
	GameObject *saw;
};

