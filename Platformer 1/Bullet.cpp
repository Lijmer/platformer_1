#include "Bullet.h"

int Bullet::numBullets=0;

Bullet::Bullet(void)
{
	setAlive(true);
	countFrame=0;
	frameDelay=12;
	color=true;
	boundUp=2;
	boundDown=2;
	boundLeft=2;
	boundRight=2;
	setCollisionType(BB);
	numBullets++;
}

void Bullet::update(bool *keys, bool *keys_pressed)
{
	x_previous = x;
	y_previous = y;
	x+=velX;
	if(x<global::camX || x>global::camX+global::SCREEN_WIDTH || y<global::camY || y>global::camY+global::SCREEN_HEIGHT)
		setAlive(false);
}

void Bullet::draw()
{
	if(++countFrame >= frameDelay)

		if(color=true)
			color=false;
		else if(color=false)
			color=true;

	al_draw_filled_circle(x,y,2,al_map_rgb(0,0,0));
	if(color)
		al_draw_filled_circle(x,y,1,al_map_rgb(255,255,255));
	else
		al_draw_filled_circle(x,y,1,al_map_rgb(239,227,0));
}

void Bullet::destroy()
{
	numBullets--;
}

void Bullet::Collided(GameObject *other)
{
	if(other->getID() == global::WALL || other->getID()==global::SPIKE || other->getID()==global::SAVE || other->getID()==global::SAW)
	{
		setAlive(false);
	}
}