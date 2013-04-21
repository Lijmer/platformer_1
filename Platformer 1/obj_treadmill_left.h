#pragma once
#include "DynamicObject.h"
class obj_Treadmill_Left : public DynamicObject
{
public:
	obj_Treadmill_Left(void);
	~obj_Treadmill_Left(void);

	void Update();
	void Draw();

private:
	int currentFrame;
	static const int maxFrame = 7;
	int frameCount;
	static const int frameDelay = 0;
};

