#include "Player.h"
#include "spr_Player.h"
#include "SoundManager.h"
#include "GameObjectManager.h"

Player::Player()
{
	//Most of this function is setting default values for variables.
	collisionWallUp = false;
	collisionWallDown = false;
	collidedWithTreadmillLeft = false;
	collidedWithTreadmillRight = false;

	gravity=0.62;

	boundUp=10;
	boundDown=10;
	boundLeft=7;
	boundRight=7;
	jump=false;

	velX=0;
	velY=0;

	dir=true;
	vertical_dir=true;

	sprite = new spr_Player();

	SetCollisionType(BB);

	SetID(PLAYER);
	SetDepth(-11);

	exceptionIDs[0] = WALL_FADE;
	exceptionIDs[1] = SAVE;
	exceptionIDs[2] = HORIZONTAL_PLATFORM;
	exceptionIDs[3] = VERTICAL_PLATFORM;
	exceptionIDs[4] = TREADMILL_LEFT;
	exceptionIDs[5] = TREADMILL_RIGHT;
}
Player::~Player()
{
	delete sprite;
}

void Player::Init(float x, float y)
{
	Player::x=x;
	Player::y=y;
	sprite->Init(ImageManager::GetInstance().GetImage(0), 28, 26, 0, 2);
}

void Player::UpdateBegin()
{}
void Player::Update()
{
	collisionWallDown = !GameObjectManager::GetInstance().PlaceFree(x, y+1, boundUp, boundDown, boundLeft, boundRight, GetInstanceID(), exceptionIDs, exceptionIDsSize);
	collisionWallUp = !GameObjectManager::GetInstance().PlaceFree(x, y-1, boundUp, boundDown, boundLeft, boundRight, GetInstanceID(), exceptionIDs, exceptionIDsSize);

	//Treadmills
	if(GameObjectManager::GetInstance().PlaceMeeting(TREADMILL_LEFT, x, y+1, this))
		x-=1;
	if(GameObjectManager::GetInstance().PlaceMeeting(TREADMILL_RIGHT, x, y+1, this))
		x+=1;

	//Platforms
	if(vertical_dir)
	{
		GameObject *horizontal_platform;
		if(GameObjectManager::GetInstance().PlaceMeeting(HORIZONTAL_PLATFORM, x, y+1, this,horizontal_platform))
		{
			if(GameObjectManager::GetInstance().PlaceFree(x+horizontal_platform->GetVelX(),y,boundUp,boundDown,boundLeft,boundRight,GetInstanceID(),exceptionIDs,exceptionIDsSize))
				x+=horizontal_platform->GetVelX();
		}
		GameObject *vertical_platform;
		if(GameObjectManager::GetInstance().PlaceMeeting(VERTICAL_PLATFORM, x ,y+1, this, vertical_platform))
		{
			int i=0;
			if(GameObjectManager::GetInstance().PlaceFree(x, y+vertical_platform->GetVelY(), boundUp,boundDown,boundLeft,boundRight,GetInstanceID(),exceptionIDs,exceptionIDsSize))
				y+=vertical_platform->GetVelY();
		}
	}
	else
	{
		GameObject *horizontal_platform;
		if(GameObjectManager::GetInstance().PlaceMeeting(HORIZONTAL_PLATFORM, x, y-1, this,horizontal_platform))
		{
			if(GameObjectManager::GetInstance().PlaceFree(x+horizontal_platform->GetVelX(),y,boundUp,boundDown,boundLeft,boundRight,GetInstanceID(),exceptionIDs,exceptionIDsSize))
				x+=horizontal_platform->GetVelX();
		}
		GameObject *vertical_platform;
		if(GameObjectManager::GetInstance().PlaceMeeting(VERTICAL_PLATFORM, x ,y-1, this, vertical_platform))
		{
			if(GameObjectManager::GetInstance().PlaceFree(x, y+vertical_platform->GetVelY(), boundUp,boundDown,boundLeft,boundRight,GetInstanceID(),exceptionIDs,exceptionIDsSize))
				y+=vertical_platform->GetVelY();
		}
	}

	if(vertical_dir)
	{
		if(collisionWallDown)
		{
			gravity = 0;
			jump=true;
		}
		else
			gravity = .62;
	}
	else if(!vertical_dir)
	{
		if(collisionWallUp)
		{
			gravity = 0;
			jump=true;
		}
		else
			gravity=-.62;
	}

	
	SetGravitySpeed();
	
	//Add gravity to velocity
	velY+=gravity;

	//Stuff that depends on buttons being pressed down.
	Jump();
	Move();	
	Shoot();
	InvertGravity();
	
	//Maximum velocity for going down and going up.
	if(velY>7)
		velY=7;
	if(velY<-7)
		velY=-7;
	
	//Change coordinates based on speed
	y+=velY;
	x+=velX;
	
	//Update Sprite
	SetSpriteData();
	sprite->Update();

	//Update Cam
	_camX = int(x/_SCREEN_WIDTH)*_SCREEN_WIDTH;
	_camY = int(y/_SCREEN_HEIGHT)*_SCREEN_HEIGHT;

	//Reset Variables
	collisionWallUp = false;
	collisionWallDown = false;
	collidedWithTreadmillLeft = false;
	collidedWithTreadmillRight = false;
	idle = true;
	velX=0;
	x_previous = x;
	y_previous = y;
}
void Player::UpdateEnd()
{}
void Player::Draw()
{
	sprite->Draw(x,y);
	//al_draw_filled_rectangle(x-boundLeft-_camX,y-boundUp-_camY,x+boundRight-_camX,y+boundDown-_camY,al_map_rgb(255,0,255));
}
void Player::Kill()
{
	_deaths++;
	SetAlive(false);
	SoundManager::GetInstance().Play(SPLAT);
	//Create normal blood
	for(int i=0; i<125; i++)
		GameObjectManager::GetInstance().CreateObject(100,x,y);
	//create head, torso, arms and feet
	GameObjectManager::GetInstance().CreateObject(101,x,y);
	GameObjectManager::GetInstance().CreateObject(102,x,y);
}
void Player::Destroy()
{
}
void Player::Collided(GameObject *other)
{
	if(other->GetID()==WALL || other->GetID()==WALL_FADE || other->GetID()==SAVE || other->GetID() == VERTICAL_PLATFORM ||
		other->GetID() == HORIZONTAL_PLATFORM || other->GetID() == TREADMILL_LEFT || other->GetID() == TREADMILL_RIGHT)
	{		
		int i=0;
		if(velY<0)
		{
			while(y-boundUp < other->GetY() + other->GetBoundDown() && i<12*5)
			{
				i++;
				y+=.2;
			}
			if(i>=12*5)
				y-=12;
		}
		else if(velY>0)
		{
			while(y+boundDown > other->GetY() - other->GetBoundUp() && i<12*5)
			{
				i++;
				y-=.2;
			}
			if(i>=12*5)
				y+=12;
		}
		velY=0;
	}
	else if(other->GetID() == SPIKE || other->GetID() == SAW)
	{
		Kill();
	}
}

//Functions to make the Update() function clearer
inline void Player::Jump()
{
	//Jump
	if(_keys_pressed[Z_KEY])
	{
		if(vertical_dir)
		{
			if(collisionWallDown)
			{
				SoundManager::GetInstance().Play(JUMP1);
				velY=-6.5;
			}
			else if(jump)
			{
				SoundManager::GetInstance().Play(JUMP2);
				velY=-6.5;
				jump=false;
			}
		}
		if(!vertical_dir)
		{
			if(collisionWallUp)
			{
				SoundManager::GetInstance().Play(JUMP1);
				velY=6.5;
			}
			else if(jump)
			{
				SoundManager::GetInstance().Play(JUMP2);
				velY=6.5;
				jump=false;
			}
		}
	}
	if(vertical_dir)
	{
		if(_keys[Z_KEY] && velY<0)
			velY-=.35;
	}
	else if(!vertical_dir)
	{
		if(_keys[Z_KEY] && velY>0)
			velY+=.35;
	}
}
inline void Player::Move()
{
	//Move Left
	if(_keys[LEFT] && !_keys[RIGHT])
	{
		sprite->SetDirection(false);
		dir=false;
		idle=false;
		if(GameObjectManager::GetInstance().PlaceFree(x-3,y,boundUp, boundDown, boundLeft, boundRight, GetInstanceID(), exceptionIDs, exceptionIDsSize))
			x-=3;
		else
			idle=true;

	}

	//Move Right
	if(_keys[RIGHT] && !_keys[LEFT])
	{
		sprite->SetDirection(true);
		idle=false;
		dir=true;
		if(GameObjectManager::GetInstance().PlaceFree(x+3,y, boundUp, boundDown, boundLeft, boundRight, GetInstanceID(), exceptionIDs, exceptionIDsSize))
			x+=3;
		else
			idle=true;
	}
}
inline void Player::Shoot()
{
	if(_keys_pressed[X_KEY])
	{
		SoundManager::GetInstance().Play(SHOOT);
		if(dir)
			GameObjectManager::GetInstance().CreateDynamicObject(95,x+14,y-2,velX+10,0);
		else
			GameObjectManager::GetInstance().CreateDynamicObject(95,x-14,y-1,velX-10,0);
	}
}
inline void Player::InvertGravity()
{
	if(_keys[SPACE])
	{
		if(vertical_dir && collisionWallDown)
			vertical_dir=false;
		else if(!vertical_dir && collisionWallUp)
			vertical_dir=true;
	}
}
inline void Player::SetGravitySpeed()
{
	if(vertical_dir)
	{
		if(collisionWallDown)
		{
			gravity = 0;
			jump=true;
		}
		else
			gravity = .62;
	}
	else if(!vertical_dir)
	{
		if(collisionWallUp)
		{
			gravity = 0;
			jump=true;
		}
		else
			gravity=-.62;
	}
}
inline void Player::SetSpriteData()
{
	if(velY==0)
		if(idle)
			sprite->SetRow(2);
		else
			sprite->SetRow(3);
	else if(velY>0)
		sprite->SetRow(1);
	else if(velY<0)
		sprite->SetRow(0);
	sprite->SetVertical_Direction(vertical_dir);
}
