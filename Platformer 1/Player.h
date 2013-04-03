#pragma once
#include "DynamicObject.h"
#include "spr_Player.h"
#include "SoundManager.h"
#include "ImageManager.h"

class Player : public DynamicObject
{
public:
	Player(bool(*placeFree)(float x, float y), void(*createObject)(int ID, int x, int y), void(*reserveSpace)(char ID, int size));
	~Player();
	
	void init(float x, float y);
	void update(bool *keys, bool *keys_pressed);
	void draw();
	void kill();
	void destroy();
	void Collided(GameObject *other);

	bool(*placeFree)(float x, float y);

	float getGravity()				{return gravity;}
	bool getCollisionWallUp()		{return collisionWallUp;}
	bool getCollisionWallDown()		{return collisionWallDown;}
	bool getCollisionWallLeft()		{return collisionWallLeft;}
	bool getCollisionWallRight()	{return collisionWallRight;}
	bool getDir()					{return dir;}

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

	void(*createObject)(int ID, int x, int y);
	void(*reserveSpace)(char ID, int size);
};