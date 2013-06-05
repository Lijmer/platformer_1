#include "Blood.h"


Blood::Blood(void)
{
	gravity = .62;
	x = 0;
	y = 0;
}
Blood::~Blood(void)
{
	
}

void Blood::Init(float x, float y, float dir, float spd)
{
	image = ImageManager::GetInstance().GetImage(100);
	Particle::init(x,y,(cos(dir*PI/180.0))*spd,(sin(dir*PI/float(180.0)))*spd);
}
void Blood::Update()
{
	if(!collided)	
		velY+=gravity;
	x+=velX;
	y+=velY;

}
void Blood::Draw()
{
	al_draw_filled_rectangle(Transformer::TranslateCameraX(x-2), Transformer::TranslateCameraY(y-2),Transformer::TranslateCameraX(x+2), Transformer::TranslateCameraY(y+2), al_map_rgb(255,0,0));
}
void Blood::Destroy()
{

}
void Blood::Collided(GameObject *other)
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