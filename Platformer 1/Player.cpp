#include "Player.h"

Player::Player(bool(*PlaceFree)(float x, float y), void(*CreateObject)(int ID, int x, int y), void(*ReserveSpace)(char ID, int size))
{
	//All var inits;
	collisionWallUp = false;
	collisionWallDown = false;
	collisionWallLeft = false;
	collisionWallRight = false;

	gravity=0.62;

	boundUp=10;
	boundDown=10;
	boundLeft=7;
	boundRight=7;
	jump=false;
	direction = 270;

	velX=0;
	velY=0;

	dir=true;
	vertical_dir=true;
	Player::PlaceFree = PlaceFree;
	Player::CreateObject = CreateObject;
	Player::ReserveSpace = ReserveSpace;

	SetCollisionType(BB);

	SetID(PLAYER);
	SetDepth(-11);
}

Player::~Player()
{
	
}

void Player::Init(float x, float y)
{
	Player::x=x;
	Player::y=y;
	
	if(image!=NULL)
		sprite.Init(ImageManager::GetInstance().GetImage(0), 28, 26, 0, 2);

	jump=false;
	direction = 270;
	dir=true;
	gravity=0.62;

	velX=0;
	velY=0;
}


void Player::Update()
{

	x_previous = x;
	y_previous = y;
	//If collided with block and the y of the block is greater, than put gravity at 0 and allow reset double jump.
	//Else put the gravity to 0.62 px/(frame^2)
	if(vertical_dir)
	{
		if(collisionWallDown)
		{
			gravity = 0;
			jump=true;
		}
		else
			gravity=.62;
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

	//Add gravity to velocity
	velY+=gravity;

	//Move Left
	if(_keys[LEFT] && !_keys[RIGHT])
	{
		sprite.SetDirection(false);
		dir=false;
		idle=false;
		int i = 0;
		while(PlaceFree(x-3,y) == 1 && i<1)
		{
			x-=3;
			i++;
		}

	}

	//Move Right
	if(_keys[RIGHT] && !_keys[LEFT])
	{
		sprite.SetDirection(true);
		idle=false;
		dir=true;
		int i = 0;
		while(PlaceFree(x+3,y) == 1 && i <1)
		{
			x+=3;
			i++;
		}
	}

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

	if(_keys[SPACE])
	{
		if(vertical_dir && collisionWallDown)
			vertical_dir=false;
		else if(!vertical_dir && collisionWallUp)
			vertical_dir=true;
	}

	//Maximum velocity for going down.
	if(velY>7)
		velY=7;
	if(velY<-7)
		velY=-7;

	if(velY==0)
		if(idle)
			sprite.SetRow(2);
		else
			sprite.SetRow(3);
	else if(velY>0)
		sprite.SetRow(1);
	else if(velY<0)
		sprite.SetRow(0);
	
	//Reset Collision Vars
	collisionWallUp = false;
	collisionWallDown = false;
	collisionWallLeft = false;
	collisionWallRight = false;
	idle = true;

	//Move vertical
	y+=velY;

	//Update Sprite
	sprite.Update();

	//Update Cam
	_camX = int(x/_SCREEN_WIDTH)*_SCREEN_WIDTH;
	_camY = int(y/_SCREEN_HEIGHT)*_SCREEN_HEIGHT;

	sprite.SetVertical_Direction(vertical_dir);
}

void Player::Draw()
{
	sprite.Draw(x,y);
}

void Player::Kill()
{
	SoundManager::GetInstance().Play(SPLAT);
	//Create normal blood
	for(int i=0; i<125; i++)
		CreateObject(100,x,y);
	//create head, torso, arms and feet
	CreateObject(101,x,y);
	CreateObject(102,x,y);
	Destroy();
}

void Player::Destroy()
{
	GameObject::Destroy();
}

void Player::Collided(GameObject *other)
{
	if(other->GetID()==WALL || other->GetID()==WALL_FADE || other->GetID()==SAVE)
	{
		if(y >= other->GetY())
			collisionWallUp = true;

		if(y <= other->GetY())
			collisionWallDown = true;
		
		int i=0;
		if(velY<0)
		{
			while(y-boundUp <= other->GetY() + other->GetBoundDown() && i<120)
			{
				i++;
				y+=.1;
			}
			if(i>=120)
				y-=12;
		}
		else if(velY>0)
		{
			while(y+boundDown 
				>= other->GetY() - other->GetBoundUp() && i<120)
			{
				i++;
				y-=.1;
			}
			if(i>=120)
				y+=12;
		}

		velY=0;
	}
	else if(other->GetID() == SPIKE || other->GetID() == SAW)
	{
		Kill();
		SetAlive(false);
	}
}