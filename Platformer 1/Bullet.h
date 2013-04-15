#pragma once
#include "DynamicObject.h"
class Bullet : public DynamicObject
{
public:
	Bullet();
	void Update();
	void Draw();
	void Destroy();

	void Collided(GameObject *other);

	static int getNumBullets()	{return numBullets;}
	
private:
	int countFrame;
	int frameDelay;
	static int numBullets;
	bool color;
};

