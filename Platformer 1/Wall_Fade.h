#pragma once
#include "DynamicObject.h"
class Wall_Fade : public DynamicObject
{
public:
	Wall_Fade(bool(*PlaceMeeting)(int otherID, float x, float y, DynamicObject *object));

	void Init(float x, float y);

	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);
private:
	bool activated;
	float opacity;

	bool(*PlaceMeeting)(int otherID, float x, float y, DynamicObject *object);
};

