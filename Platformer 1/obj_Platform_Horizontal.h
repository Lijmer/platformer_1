#pragma once
#include "DynamicObject.h"
class obj_Platform_Horizontal : public DynamicObject
{
public:
	obj_Platform_Horizontal(bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs));
	~obj_Platform_Horizontal(void);

	void Update();
	void Draw();
	void Destroy();

private:
	int exceptionIDs[5];

	bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs);
};

