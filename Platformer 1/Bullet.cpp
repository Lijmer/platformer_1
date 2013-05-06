#include "Bullet.h"

int Bullet::numBullets=0;

Bullet::Bullet(void)
{
	SetAlive(true);
	SetDepth(-100);
	SetID(BULLET);
	countFrame=0;
	frameDelay=12;
	color=true;
	boundUp=2;
	boundDown=2;
	boundLeft=2;
	boundRight=2;
	SetCollisionType(BB);
	numBullets++;
}

void Bullet::Init(float x, float y, float velX)
{
	Bullet::x = x;
	Bullet::y = y;
	Bullet::velX = velX;
}

void Bullet::Update()
{
	x_previous = x;
	y_previous = y;
	x+=velX;
	if(x<_camX-32 || x>_camX+_SCREEN_WIDTH+32 || y<_camY-32 || y>_camY+_SCREEN_HEIGHT+32)
		SetAlive(false);
}

void Bullet::Draw()
{
	if(++countFrame >= frameDelay)
	{
		if(color)
			color=false;
		else if(!color)
			color=true;
		countFrame=0;
	}
	al_draw_filled_circle(x-_camX,y-_camY,2,al_map_rgb(0,0,0));
	if(color)
		al_draw_filled_circle(x-_camX,y-_camY,1,al_map_rgb(255,255,255));
	else
		al_draw_filled_circle(x-_camX,y-_camY,1,al_map_rgb(239,227,0));
}

void Bullet::Destroy()
{
	numBullets--;
}

void Bullet::Collided(GameObject *other)
{
	if(other->GetID() == WALL || other->GetID()==SPIKE || other->GetID()==SAVE || other->GetID()==SAW)
	{
		SetAlive(false);
	}
}