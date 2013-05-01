#pragma once
#include "DynamicObject.h"
class obj_Platform_Vertical : public DynamicObject
{
public:
	obj_Platform_Vertical();
	~obj_Platform_Vertical(void);

	void Update();
	void Draw();
	void Destroy();

private:
	int exceptionIDs[4];
	int exceptionIDsSize;
	
	bool isGoingUp;
};

