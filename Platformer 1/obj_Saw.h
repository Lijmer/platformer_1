#pragma once
#include "DynamicObject.h"
class obj_Saw : public DynamicObject
{
public:
	obj_Saw(void);
	~obj_Saw(void);
	void init(float x, float y);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();
private:
	float direction;
};
