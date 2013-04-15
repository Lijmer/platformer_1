#pragma once
#include "DynamicObject.h"
class obj_Saw : public DynamicObject
{
public:
	obj_Saw(void);
	~obj_Saw(void);
	void Init(float x, float y);
	void Update();
	void Draw();
	void Destroy();
private:
	float direction;
};
