#pragma once
#include "DynamicObject.h"
#include "spr_Player.h"
#include "SoundManager.h"
#include "ImageManager.h"

class Player : public DynamicObject
{
public:
	Player(bool(*PlaceFree)(float x, float y), void(*CreateObject)(int ID, int x, int y), void(*ReserveSpace)(char ID, int size));
	~Player();
	
	void Init(float x, float y);
	void Update();
	void Draw();
	void Kill();
	void Destroy();
	void Collided(GameObject *other);

	bool(*PlaceFree)(float x, float y);

	float GetGravity()				{return gravity;}
	bool GetCollisionWallUp()		{return collisionWallUp;}
	bool GetCollisionWallDown()		{return collisionWallDown;}
	bool GetCollisionWallLeft()		{return collisionWallLeft;}
	bool GetCollisionWallRight()	{return collisionWallRight;}
	bool GetDir()					{return dir;}

private:
	bool collisionWallUp;
	bool collisionWallDown;
	bool collisionWallLeft;
	bool collisionWallRight;
	
	bool idle;
	bool dir;
	bool vertical_dir;

	spr_Player sprite;

	float gravity;
	int direction;
	bool jump;

	void(*CreateObject)(int ID, int x, int y);
	void(*ReserveSpace)(char ID, int size);
};