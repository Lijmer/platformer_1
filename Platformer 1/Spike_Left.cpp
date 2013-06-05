#include "Spike_Left.h"


Spike_Left::Spike_Left(void)
{
	SetDepth(0);
}

void Spike_Left::Init(float x,float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x;
	yPoint1 = y+16;
	xPoint2 = x+32;
	yPoint2 = y;
	xPoint3 = x+32;
	yPoint3 = y+32;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SPIKE_LEFT);
}

void Spike_Left::Destroy()
{

}