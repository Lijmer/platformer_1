#include "Spike_Right.h"

Spike_Right::Spike_Right(void)
{
	SetDepth(0);
}

void Spike_Right::Init(float x,float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+1;
	xPoint2 = x+31;
	yPoint2 = y+15;
	xPoint3 = x+1;
	yPoint3 = y+31;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(6);
}

void Spike_Right::Draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}

void Spike_Right::Destroy()
{

}