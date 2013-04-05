#pragma once
#include "DynamicObject.h"
class obj_Saw_Small : public DynamicObject
{
public:
	obj_Saw_Small(void);
	~obj_Saw_Small(void);
	
	void init(float x, float y);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();

private:
	float direction;
};
