#pragma once
#include "DynamicObject.h"
class obj_Platform_Horizontal : public DynamicObject
{
public:
	obj_Platform_Horizontal();
	~obj_Platform_Horizontal(void);

	void Update();
	void Draw();
	void Destroy();

private:
	int exceptionIDs[5];
	int exceptionIDsSize;
};

