#pragma once
#include "DynamicObject.h"
class Bullet : public DynamicObject
{
public:
	Bullet();
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void destroy();

	void Collided(GameObject *other);

	static int getNumBullets()	{return numBullets;}
	
private:
	int countFrame;
	int frameDelay;
	static int numBullets;
	bool color;
};

