#pragma once
#include "DynamicObject.h"
class Wall_Fade : public DynamicObject
{
public:
	Wall_Fade();

	void Init(float x, float y);

	void Update();
	void Draw();
private:
	bool activated;
	float opacity;
};

