#pragma once
#include "DynamicObject.h"
#include "spr_Player.h"
#include "SoundManager.h"
#include <time.h>

class Player : public DynamicObject
{
public:
	Player(bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize),
		bool(*PlaceMeeting)(int otherID, float x, float y, DynamicObject *object), GameObject*(*CreateObject)(int ID, int x, int y), void(*ReserveSpace)(char ID, int size), 
		void(*Shoot)(bool dir, float x, float y, float velX));
	~Player();
	
	void Init(float x, float y);
	void UpdateBegin();
	void Update();
	void UpdateEnd();
	void Draw();
	void Kill();
	void Destroy();
	void Collided(GameObject *other);
	
	float GetGravity() const			{return gravity;}
	bool GetCollisionWallUp() const		{return collisionWallUp;}
	bool GetCollisionWallDown()	const	{return collisionWallDown;}
	bool GetDir() const					{return dir;}

private:
	bool collisionWallUp;
	bool collisionWallDown;
	bool collidedWithTreadmillLeft;
	bool collidedWithTreadmillRight;
	
	bool idle;
	bool dir;
	bool vertical_dir;

	spr_Player *sprite;

	float gravity;
	int direction;
	bool jump;

	static const int exceptionIDsSize = 6;
	int exceptionIDs[6];
	
	//Functions to make the Update() function clearer
	void Jump();
	void Move();
	void Blast();
	void InvertGravity();
	void SetGravitySpeed();
	void SetSpriteData();

	

	bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize);
	bool(*PlaceMeeting)(int otherID, float x, float y, DynamicObject *object);
	GameObject*(*CreateObject)(int ID, int x, int y);
	void(*ReserveSpace)(char ID, int size);
	void(*Shoot)(bool dir, float x, float y, float velX);
};
 