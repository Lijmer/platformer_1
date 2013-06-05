#include "Spike_Right.h"

Spike_Right::Spike_Right(void)
{
	SetDepth(0);
}

void Spike_Right::Init(float x,float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x;
	yPoint1 = y;
	xPoint2 = x+32;
	yPoint2 = y+16;
	xPoint3 = x;
	yPoint3 = y+32;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SPIKE_RIGHT);
}

void Spike_Right::Destroy()
{

}