#include "Player.h"

Player::Player(bool(*placeFree)(float x, float y), void(*createObject)(int ID, int x, int y), void(*reserveSpace)(char ID, int size))
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
	Player::placeFree = placeFree;
	Player::createObject = createObject;
	Player::reserveSpace = reserveSpace;

	setCollisionType(BB);

	setID(PLAYER);
	setDepth(-11);
}

Player::~Player()
{
	
}

void Player::init(float x, float y)
{
	Player::x=x;
	Player::y=y;
	
	if(image!=NULL)
	{
		sprite.init(ImageManager::getInstance().getImage(0), 28, 26, 0, 2);
	}

	jump=false;
	direction = 270;
	dir=true;
	gravity=0.62;

	velX=0;
	velY=0;
}


void Player::update(bool *keys, bool *keys_pressed)
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
	if(keys[LEFT] && !keys[RIGHT])
	{
		sprite.setDirection(false);
		dir=false;
		idle=false;
		int i = 0;
		while(placeFree(x-3,y) == 1 && i<1)
		{
			x-=3;
			i++;
		}

	}

	//Move Right
	if(keys[RIGHT] && !keys[LEFT])
	{
		sprite.setDirection(true);
		idle=false;
		dir=true;
		int i = 0;
		while(placeFree(x+3,y) == 1 && i <1)
		{
			x+=3;
			i++;
		}
	}

	//Jump
	if(keys_pressed[Z_KEY])
	{
		if(vertical_dir)
		{
			if(collisionWallDown)
			{
				SoundManager::GetInstance().play(JUMP1);
				velY=-6.5;
			}
			else if(jump)
			{
				SoundManager::GetInstance().play(JUMP2);
				velY=-6.5;
				jump=false;
			}
		}
		if(!vertical_dir)
		{
			if(collisionWallUp)
			{
				SoundManager::GetInstance().play(JUMP1);
				velY=6.5;
			}
			else if(jump)
			{
				SoundManager::GetInstance().play(JUMP2);
				velY=6.5;
				jump=false;
			}
		}
	}
	if(vertical_dir)
	{
		if(keys[Z_KEY] && velY<0)
			velY-=.35;
	}
	else if(!vertical_dir)
	{
		if(keys[Z_KEY] && velY>0)
			velY+=.35;
	}

	if(keys[SPACE])
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
			sprite.setRow(2);
		else
			sprite.setRow(3);
	else if(velY>0)
		sprite.setRow(1);
	else if(velY<0)
		sprite.setRow(0);
	
	//Reset Collision Vars
	collisionWallUp = false;
	collisionWallDown = false;
	collisionWallLeft = false;
	collisionWallRight = false;
	idle = true;

	//Move vertical
	y+=velY;

	//Update Sprite
	sprite.update();

	//Update Cam
	_camX = int(x/_SCREEN_WIDTH)*_SCREEN_WIDTH;
	_camY = int(y/_SCREEN_HEIGHT)*_SCREEN_HEIGHT;

	sprite.setVertical_Direction(vertical_dir);
}

void Player::draw()
{
	sprite.draw(x,y);
}

void Player::kill()
{
	SoundManager::GetInstance().play(SPLAT);
	for(int i=0; i<125; i++)
	{
		createObject(100,x,y);
	}
	destroy();
}

void Player::destroy()
{
	GameObject::destroy();
}

void Player::Collided(GameObject *other)
{
	if(other->getID()==WALL || other->getID()==WALL_FADE || other->getID()==SAVE)
	{
		if(y >= other->getY())
			collisionWallUp = true;

		if(y <= other->getY())
			collisionWallDown = true;
		
		int i=0;
		if(velY<0)
		{
			while(y-boundUp <= other->getY() + other->getBoundDown() && i<120)
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
				>= other->getY() - other->getBoundUp() && i<120)
			{
				i++;
				y-=.1;
			}
			if(i>=120)
				y+=12;
		}

		velY=0;
	}
	else if(other->getID() == SPIKE || other->getID() == SAW)
	{
		kill();
		setAlive(false);
	}
}