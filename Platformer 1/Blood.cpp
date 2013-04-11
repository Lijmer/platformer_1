#include "Blood.h"


Blood::Blood(void)
{
	collided = false;
	setAlive(true);

	boundUp=0;
	boundDown=0;
	boundLeft=0;
	boundRight=0;
	gravity = 1;
	x = 0;
	y = 0;
	setID(PARTICLE);
	setCollisionType(BB);
	kind=rand()%2;
	frame=rand()%2;
}


Blood::~Blood(void)
{
	
}

void Blood::init(float x, float y, float dir, float spd)
{
	image = ImageManager::getInstance().getImage(100);
	frameCount=0;
	frameDelay=rand()%5+5;
	Particle::init(x,y,(cos(dir*PI/180.0))*spd,(sin(dir*PI/float(180.0)))*spd);
	direction = rand()%360;
}

void Blood::update()
{
	if(!collided)	
		velY+=gravity;
	x+=velX;
	y+=velY;

}

void Blood::draw()
{
	//if(++frameCount > frameDelay)
	//{
		//frameCount=0;
		//if(frame)
		//	frame=false;
		//else if(!frame)
		//	frame=true;
	//}
	
	if(kind)
		al_draw_tinted_scaled_rotated_bitmap_region(image,8*frame,0,8,8,al_map_rgba(255,255,255,255),4,4,x-_camX,y-_camY,1,1,direction*PI/180,0);
	else if(!kind)
		al_draw_tinted_scaled_rotated_bitmap_region(image,12*frame,8,12,16,al_map_rgba(255,255,255,255),6,8,x-_camX,y-_camY,1,1,direction*PI/180,0);
}

void Blood::destroy()
{

}

void Blood::Collided(GameObject *other)
{
	if(other->getID() == WALL || other->getID() == WALL_FADE)
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