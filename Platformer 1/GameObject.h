#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_image.h>
#include "ImageManager.h"
#include "Transformer.h"
#include "globals.h"

//using namespace Transformer;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init(float x, float y);
	void Activate();
	void Deactivate();
	void virtual Draw();
	void virtual Destroy();

	static unsigned int lastID;

	//get variables
	float GetX()				const			{return x;}
	float GetY()				const			{return y;}
	float GetVelX()				const			{return velX;}
	float GetVelY()				const			{return velY;}
	int GetBoundUp()			const			{return boundUp;}
	int GetBoundDown()			const			{return boundDown;}
	int GetBoundLeft()			const			{return boundLeft;}
	int GetBoundRight()			const			{return boundRight;}
	float GetXPoint1()			const			{return xPoint1;}
	float GetYPoint1()			const			{return yPoint1;}
	float GetXPoint2()			const			{return xPoint2;}
	float GetYPoint2()			const			{return yPoint2;}
	float GetXPoint3()			const			{return xPoint3;}
	float GetYPoint3()			const			{return yPoint3;}
	unsigned char GetRadius()	const			{return radius;}
	int GetID()					const			{return ID;}
	unsigned int GetInstanceID()const			{return instanceID;}
	int GetDepth()				const			{return depth;}
	bool GetAlive()				const			{return alive;}
	bool GetActivated()			const			{return activated;}
	bool GetCollidable()		const			{return collidable;}
	int GetCollisionType()		const			{return collisionType;}

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

