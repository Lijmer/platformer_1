#pragma once
#include "DynamicObject.h"
class obj_Treadmill_Right : public DynamicObject
{
public:
	obj_Treadmill_Right(void);
	~obj_Treadmill_Right(void);

	void Update();
	void Draw();

protected:
	int currentFrame;
	static const int maxFrame = 7;
	int frameCount;
	static const int frameDelay = 0;
};

