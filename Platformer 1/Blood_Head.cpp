#include "Blood_Head.h"


Blood_Head::Blood_Head(void)
{
	gravity=.62;
	collided=false;
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_BLOOD_HEAD);
}


Blood_Head::~Blood_Head(void)
{
}

void Blood_Head::Init(float x, float y, float dir, float spd)
{
	Particle::init(x,y,(cos(dir*PI/180.0))*spd,(sin(dir*PI/180.0))*spd);
	direction = rand()%360;
}

void Blood_Head::Update()
{
	if(velY>7)
		velY=7;

	x+=velX;
	y+=velY;
	if(!collided)
	{
		velY+=gravity;
	}
}

void Blood_Head::Draw()
{
	al_draw_rotated_bitmap(image,5,8,Transformer::TranslateCameraX(x), Transformer::TranslateCameraY(y),direction*PI/180.0,0);
}

void Blood_Head::Destroy()
{}

void Blood_Head::Collided(GameObject *other)
{
	if(other->GetID() == WALL)
	{
		collided=true;
		velX=0;
		velY=0;
	}
	else if(other->GetID() == SPIKE || other->GetID() == WALL_FADE || other->GetID() == TREADMILL_LEFT ||
		other->GetID() == TREADMILL_RIGHT || other->GetID() == SAVE || other->GetID() == SAW)
	{
		velX/=2;
		velY=0;
	}
}