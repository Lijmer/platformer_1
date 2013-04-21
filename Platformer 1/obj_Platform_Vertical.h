#pragma once
#include "DynamicObject.h"
class obj_Platform_Vertical : public DynamicObject
{
public:
	obj_Platform_Vertical(bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize));
	~obj_Platform_Vertical(void);

	void Update();
	void Draw();
	void Destroy();

private:
	int exceptionIDs[4];
	int exceptionIDsSize;
	
	bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize);
	bool isGoingUp;
};

