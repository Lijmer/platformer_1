#pragma once
#include "DynamicObject.h"
class obj_Saw_Small : public DynamicObject
{
public:
	obj_Saw_Small(void);
	~obj_Saw_Small(void);
	
	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();

private:
	float direction;
};
