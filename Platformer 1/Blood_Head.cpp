#include "Blood_Head.h"


Blood_Head::Blood_Head(void)
{
	boundUp=0;
	boundDown=0;
	boundLeft=0;
	boundRight=0;
	setCollisionType(BB);
	setID(PARTICLE);
	gravity=.62;
	collided=false;
}


Blood_Head::~Blood_Head(void)
{
}

void Blood_Head::init(float x, float y, float dir, float spd)
{
	image = ImageManager::getInstance().getImage(101);
	Particle::init(x,y,(cos(dir*PI/180.0))*spd,(sin(dir*PI/180.0))*spd);
	direction = rand()%360;
}

void Blood_Head::update()
{
	direction+=7;
	if(velY>7)
		velY=7;

	x+=velX;
	y+=velY;
	if(!collided)
		velY+=gravity;
}

void Blood_Head::draw()
{
	al_draw_rotated_bitmap(image,5,8,x-_camX,y-_camY,direction*PI/180.0,0);
}

void Blood_Head::destroy()
{}

void Blood_Head::Collided(GameObject *other)
{
	if((other->getID() == WALL || other->getID() == WALL_FADE))
	{
		collided=true;
		velX=0;
		velY=0;
	}
	else if(other->getID() == SPIKE)
	{
		velX/=1.5;
		velY/=1.5;
	}
}