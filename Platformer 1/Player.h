#pragma once
#include "DynamicObject.h"
#include "spr_Player.h"
#include "SoundManager.h"
#include "ImageManager.h"

class Player : public DynamicObject
{
public:
	Player(bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs), 
		GameObject*(*CreateObject)(int ID, int x, int y), void(*ReserveSpace)(char ID, int size), void(*Shoot)(bool dir, float x, float y, float velX));
	~Player();
	
	void Init(float x, float y);
	void Update();
	void Draw();
	void Kill();
	void Destroy();
	void Collided(GameObject *other);


	float GetGravity()				{return gravity;}
	bool GetCollisionWallUp()		{return collisionWallUp;}
	bool GetCollisionWallDown()		{return collisionWallDown;}
	bool GetDir()					{return dir;}

private:
	bool collisionWallUp;
	bool collisionWallDown;
	
	bool idle;
	bool dir;
	bool vertical_dir;

	spr_Player sprite;

	float gravity;
	int direction;
	bool jump;

	int exceptionIDs[4];
	
	bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs);
	GameObject*(*CreateObject)(int ID, int x, int y);
	void(*ReserveSpace)(char ID, int size);
	void(*Shoot)(bool dir, float x, float y, float velX);
};