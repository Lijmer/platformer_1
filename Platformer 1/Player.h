#pragma once
#include "DynamicObject.h"
class spr_Player;

class Player : public DynamicObject
{
public:
	Player();
	~Player();
	
	void Init(float x, float y);
	void UpdateBegin();
	void Update();
	void UpdateEnd();
	void Draw();
	void Kill();
	void Destroy();
	void Collided(GameObject *other);
	
	float GetGravity()			const	{return gravity;}
	bool GetCollisionWallUp()	const	{return collisionWallUp;}
	bool GetCollisionWallDown()	const	{return collisionWallDown;}
	bool GetDir()				const	{return dir;}
	bool GetVerticalDir()		const	{return vertical_dir;}
	bool GetJump()				const	{return jump;}
	bool GetIdle()				const	{return idle;}

	void SetGravity(float gravity)			{Player::gravity = gravity;}
	void SetDir(bool dir)					{Player::dir = dir;}
	void SetVerticalDir(bool vertical_dir)	{Player::vertical_dir = vertical_dir;}
	void SetJump(bool jump)					{Player::jump = jump;}
	void SetIdle(bool idle)					{Player::idle = idle;}

private:
	bool collisionWallUp;
	bool collisionWallDown;
	bool collidedWithTreadmillLeft;
	bool collidedWithTreadmillRight;
	
	bool idle;
	bool dir;
	bool vertical_dir;
	bool jump;
	float gravity;

	spr_Player *sprite;


	static const int exceptionIDsSize = 6;
	int exceptionIDs[6];
	
	//Functions to make the Update() function clearer
	void Jump();
	void Move();
	void Shoot();
	void InvertGravity();
	void SetGravitySpeed();
	void SetSpriteData();
};
 