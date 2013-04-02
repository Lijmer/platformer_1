#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_image.h>
#include "ImageManager.h"
#include "globals.h"
class GameObject
{
public:
	GameObject();

	enum COLLISION_TYPE{BB, TBB, CBB , PPC};
	/*BB = Bounding Box
	 *TBB = Triangle Bounding Box
	 *CBB = Circle Bouding Box
	 *PPC = Pixel Perfect Collision
	*/

	void init(float x, float y, int ID, int depth);
	void activate();
	void deactivate();
	void virtual draw();
	void virtual destroy();

	static int lastID;

	//get variables
	float getX()								{return x;}
	float getY()								{return y;}
	int getBoundUp()							{return boundUp;}
	int getBoundDown()							{return boundDown;}
	int getBoundLeft()							{return boundLeft;}
	int getBoundRight()							{return boundRight;}
	float getXPoint1()							{return xPoint1;}
	float getYPoint1()							{return yPoint1;}
	float getXPoint2()							{return xPoint2;}
	float getYPoint2()							{return yPoint2;}
	float getXPoint3()							{return xPoint3;}
	float getYPoint3()							{return yPoint3;}
	float getRadius()							{return radius;}
	int getID()									{return ID;}
	int getDepth()								{return depth;}
	bool getAlive()								{return alive;}
	bool getActivated()							{return activated;}
	bool getCollidable()						{return collidable;}
	int getCollisionType()						{return collisionType;}

	//set variables
	void setX(float x)							{GameObject::x = x;}
	void setY(float y)							{GameObject::y = y;}
	void setBoundUp(int boundUp)				{GameObject::boundUp = boundUp;}
	void setBoundDown(int boundDown)			{GameObject::boundDown = boundDown;}
	void setBoundLeft(int boundLeft)			{GameObject::boundLeft = boundLeft;}
	void setBoundRight(int boundRight)			{GameObject::boundRight = boundRight;}
	void setID(int ID)							{GameObject::ID = ID;}
	void setDepth(int depth)					{GameObject::depth = depth;}
	void setAlive(bool alive)					{GameObject::alive = alive;}
	void setActivated(bool activated)			{GameObject::activated = activated;}
	void setCollidable(bool collidable)			{GameObject::collidable = collidable;}
	void setCollisionType(int collisionType)	{GameObject::collisionType = collisionType;}

	
protected:
	float x;
	float y;
	int boundUp;
	int boundDown;
	int boundLeft;
	int boundRight;
	float xPoint1;
	float yPoint1;
	float xPoint2;
	float yPoint2;
	float xPoint3;
	float yPoint3;
	float radius;
	ALLEGRO_BITMAP *image;
private:
	int ID;
	int instanceID;
	int depth;
	bool alive;
	bool activated;
	bool collidable;
	int collisionType;
};

