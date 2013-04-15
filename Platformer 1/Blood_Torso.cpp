#include "Blood_Torso.h"


Blood_Torso::Blood_Torso(void)
{
	boundUp=0;
	boundDown=0;
	boundLeft=0;
	boundRight=0;
	SetCollisionType(BB);
	SetID(PARTICLE);
	gravity=.62;
	collided=false;
}


Blood_Torso::~Blood_Torso(void)
{
}

void Blood_Torso::Init(float x, float y, float dir, float spd)
{
	image = ImageManager::GetInstance().GetImage(102);
	Particle::init(x,y,(cos(dir*PI/180.0))*spd,(sin(dir*PI/180.0))*spd);
	direction = rand()%360;
}

void Blood_Torso::Update()
{
	direction+=7;
	if(velY>7)
		velY=7;

	x+=velX;
	y+=velY;
	if(!collided)
		velY+=gravity;
}

void Blood_Torso::Draw()
{
	al_draw_rotated_bitmap(image,1,4,x-_camX,y-_camY,direction*PI/180.0,0);
}

void Blood_Torso::Destroy()
{}

void Blood_Torso::Collided(GameObject *other)
{
	if((other->GetID() == WALL || other->GetID() == WALL_FADE))
	{
		collided=true;
		velX=0;
		velY=0;
	}
	else if(other->GetID() == SPIKE)
	{
		velX/=1.5;
		velY/=1.5;
	}
}