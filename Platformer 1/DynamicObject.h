#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject 
{
public:
	DynamicObject(void);

	void Init(float x, float y, float velX, float velY, int ID = UNDEFINED, int depth = 0);
	void virtual Update();
	void virtual Draw();
	void virtual Destroy();

	//get variables
	float GetVelX()						{return velX;}
	float GetVelY()						{return velY;}
	float GetX_previous()				{return x_previous;}
	float GetY_previous()				{return y_previous;}

	void SetVelX(float velX)			{DynamicObject::velX=velX;}
	void SetVelY(float velY)			{DynamicObject::velY = velY;}

	//check for collisions
	bool CheckCollision(GameObject *other);
	//what to do when collided
	void virtual Collided(GameObject *other);
	
protected:
	float velX;
	float velY;
	float x_previous;
	float y_previous;

private:
	bool inline Is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py);
	bool inline Is_p_in_circle(float xCircle, float yCircle, float radiusCircle, float Px, float Py);
};

