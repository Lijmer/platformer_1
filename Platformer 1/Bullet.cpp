#include "Bullet.h"

int Bullet::numBullets=0;

Bullet::Bullet(void)
{
	SetAlive(true);
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

void Bullet::Update()
{
	x_previous = x;
	y_previous = y;
	x+=velX;
	if(x<_camX || x>_camX+_SCREEN_WIDTH || y<_camY || y>_camY+_SCREEN_HEIGHT)
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