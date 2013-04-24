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

	

	void Init(float x, float y);
	void Activate();
	void Deactivate();
	void virtual Draw();
	void virtual Destroy();

	static unsigned int lastID;

	//get variables
	float GetX()								{return x;}
	float GetY()								{return y;}
	float GetVelX()								{return velX;}
	float GetVelY()								{return velY;}
	int GetBoundUp()							{return boundUp;}
	int GetBoundDown()							{return boundDown;}
	int GetBoundLeft()							{return boundLeft;}
	int GetBoundRight()							{return boundRight;}
	float GetXPoint1()							{return xPoint1;}
	float GetYPoint1()							{return yPoint1;}
	float GetXPoint2()							{return xPoint2;}
	float GetYPoint2()							{return yPoint2;}
	float GetXPoint3()							{return xPoint3;}
	float GetYPoint3()							{return yPoint3;}
	unsigned char GetRadius()					{return radius;}
	int GetID()									{return ID;}
	unsigned int GetInstanceID()				{return instanceID;}
	int GetDepth()								{return depth;}
	bool GetAlive()								{return alive;}
	bool GetActivated()							{return activated;}
	bool GetCollidable()						{return collidable;}
	int GetCollisionType()						{return collisionType;}

	//set variables
	void SetX(float x)							{GameObject::x = x;}
	void SetY(float y)							{GameObject::y = y;}
	void SetVelX(float velX)					{GameObject::velX=velX;}
	void SetVelY(float velY)					{GameObject::velY = velY;}
	void SetBoundUp(int boundUp)				{GameObject::boundUp = boundUp;}
	void SetBoundDown(int boundDown)			{GameObject::boundDown = boundDown;}
	void SetBoundLeft(int boundLeft)			{GameObject::boundLeft = boundLeft;}
	void SetBoundRight(int boundRight)			{GameObject::boundRight = boundRight;}
	void SetID(int ID)							{GameObject::ID = ID;}
	void SetDepth(int depth)					{GameObject::depth = depth;}
	void SetAlive(bool alive)					{GameObject::alive = alive;}
	void SetActivated(bool activated)			{GameObject::activated = activated;}
	void SetCollidable(bool collidable)			{GameObject::collidable = collidable;}
	void SetCollisionType(int collisionType)	{GameObject::collisionType = collisionType;}

	
protected:
	float x;
	float y;
	float velX;
	float velY;
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
	unsigned char radius;
	ALLEGRO_BITMAP *image;
private:
	int ID;
	unsigned int instanceID;
	int depth;
	bool alive;
	bool activated;
	bool collidable;
	int collisionType;
};

