#pragma once
#include "dynamicobject.h"
#include "FileManager.h"
class Save : public DynamicObject
{
public:
	Save();
	void Init(float x,float y,char difficulty);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);

private:
	bool active;
	int count;

};
