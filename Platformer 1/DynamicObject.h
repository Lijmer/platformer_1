#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject 
{
public:
	DynamicObject(void);

	void init(float x, float y, float velX, float velY, int ID = global::UNDEFINED, int depth = 0);
	void virtual update(bool *keys, bool *keys_pressed);
	void virtual draw();
	void virtual destroy();

	//get variables
	float getVelX()						{return velX;}
	float getVelY()						{return velY;}
	float getX_previous()				{return x_previous;}
	float getY_previous()				{return y_previous;}

	void setVelX(float velX)			{DynamicObject::velX=velX;}
	void setVelY(float velY)			{DynamicObject::velY = velY;}

	//check for collisions
	bool checkCollision(GameObject *other);
	//what to do when collided
	void virtual Collided(GameObject *other);
	
protected:
	float velX;
	float velY;
	float x_previous;
	float y_previous;

private:
	bool inline is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py);
	bool inline is_p_in_circle(float xCircle, float yCircle, float radiusCircle, float Px, float Py);
};

