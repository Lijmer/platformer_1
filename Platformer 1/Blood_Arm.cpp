#include "Blood_Arm.h"
#include "ImageManager.h"

Blood_Arm::Blood_Arm(void)
{
	gravity=.62;
	direction = 0;
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_BLOOD_ARM);
}


Blood_Arm::~Blood_Arm(void)
{
}

void Blood_Arm::Init(float x, float y, float dir, float spd)
{
	Particle::init(x,y,(cos(dir*PI/180.0))*spd,(sin(dir*PI/180.0))*spd);
	direction = rand()%360;
}


void Blood_Arm::Update()
{
	if(!collided)
		velY+=gravity;
	
	x+=velX;
	y+=velY;
}

void Blood_Arm::Draw()
{
	al_draw_rotated_bitmap(image,1,4,TranslateCameraX(x), TranslateCameraY(y),direction*PI/180.0,0);
}

void Blood_Arm::Destroy()
{

}

void Blood_Arm::Collided(GameObject *other)
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