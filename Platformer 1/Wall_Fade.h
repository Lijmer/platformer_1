#pragma once
#include "DynamicObject.h"
class Wall_Fade : public DynamicObject
{
public:
	Wall_Fade(void);

	void Init(float x, float y);

	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);
private:
	bool activated;
	float opacity;
};

