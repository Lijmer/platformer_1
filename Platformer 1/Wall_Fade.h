#pragma once
#include "DynamicObject.h"
class Wall_Fade : public DynamicObject
{
public:
	Wall_Fade(void);

	void init(float x, float y);

	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();
	void Collided(GameObject *other);
private:
	bool activated;
	float opacity;
};

